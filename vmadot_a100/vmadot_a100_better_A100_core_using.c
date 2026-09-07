// vmadot_a100_better_A100_core_using.c
//
// Same vmadot A100 int8 matmul kernel as vmadot_a100.c, but routes to the
// A100 core the way brucehoult's `aix` launcher does:
//   https://github.com/brucehoult/k3_ai/blob/main/aix.S
// instead of the in-process fopen("/proc/set_ai_thread") trick.
//
// Why that trick is worth avoiding: vmadot_a100.c calls route_to_a100()
// from *inside* the very process that goes on to run vmadot. By the time
// that fopen()/fprintf() call happens, glibc's startup code, the dynamic
// linker, and stdio have already executed on the X100 core (256-bit
// VLEN). None of that is expected to touch a vector register, but
// nothing guarantees it either -- and upstream is explicit that moving a
// thread between X100 and A100 (different VLEN) after it has already run
// is dangerous.
//
// aix.S sidesteps the whole question: it's a tiny raw-syscall program
// (no libc, no dynamic linker -- guaranteed not to touch a single vector
// register) that writes its own PID to /proc/set_ai_thread and *only
// then* execve()s the real target program. execve() replaces the process
// image wholesale, so the target's own crt/libc startup -- and every
// instruction it ever executes -- runs after the thread is already
// parked on an A100 core. No vector instruction can execute at the
// "wrong" VLEN, by construction.
//
// This file reproduces that ordering without needing a separate aix
// binary: on first run it writes /proc/set_ai_thread using bare
// syscall()s (no stdio, no FILE*), then execve()s *itself* via
// /proc/self/exe. That re-exec is the part that matters -- it guarantees
// matmul_a100() below only ever runs inside a freshly loaded process
// image that was already routed to the A100 core before its very first
// instruction, exactly like aix.S's target program.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

extern char **environ;

// Set once we're running post-routing, so the re-exec'd copy of this same
// binary knows not to route (and re-exec) again.
#define ROUTED_ENV "VMADOT_A100_ROUTED"

// Write our PID to /proc/set_ai_thread using only raw syscalls -- nothing
// buffered, nothing that plausibly touches a vector register -- then
// execve() this same binary again so that everything from crt0 onward
// runs on the A100 core from its first instruction, mirroring aix.S.
static void route_to_a100_then_reexec(char *argv[]) {
    char pidbuf[16];
    int len = snprintf(pidbuf, sizeof(pidbuf), "%d", (int)syscall(SYS_getpid));

    long fd = syscall(SYS_openat, AT_FDCWD, "/proc/set_ai_thread", O_WRONLY, 0600);
    if (fd < 0) {
        perror("openat /proc/set_ai_thread");
        exit(1);
    }
    if (syscall(SYS_write, fd, pidbuf, len) < 0) {
        perror("write /proc/set_ai_thread");
        exit(1);
    }
    syscall(SYS_close, fd);

    setenv(ROUTED_ENV, "1", 1);
    execve("/proc/self/exe", argv, environ);
    perror("execve /proc/self/exe");   // only reached on failure
    exit(1);
}

void matmul_a100(const int8_t *A, const int8_t *Bt, int32_t *C) {
    __asm__ volatile(
        "vsetvli    t0, zero, e8, m1     \n\t"
        "vle8.v     v0, (%[A])           \n\t"
        "vle8.v     v1, (%[B])           \n\t"
        "vmadot     v16, v0, v1          \n\t"   // vd, vs1(A), vs2(B^T) -- int8 inferred from SEW=e8
        "vsetvli    t0, zero, e32, m2    \n\t"
        "vse32.v    v16, (%[C])          \n\t"
        : [A] "+r"(A), [B] "+r"(Bt), [C] "+r"(C)
        :
        : "cc", "memory", "t0", "v0", "v1", "v16", "v17"
    );
    for (int i = 0; i < 8 * 8; i++)
        C[i] += 1;   // compensate the unit's constant -1 accumulator bias
}

int main(int argc __attribute__((unused)), char *argv[]) {
    if (!getenv(ROUTED_ENV))
        route_to_a100_then_reexec(argv);   // does not return

    // Reached only in the re-exec'd copy: this whole process image was
    // loaded after the thread was already routed to the A100 core.

    // A[8,16]: row i = i, i+1, ..., i+15
    int8_t A[8 * 16];
    for (int i = 0; i < 8; i++)
        for (int k = 0; k < 16; k++)
            A[i * 16 + k] = (int8_t)(i + k);

    // B stored as Bt[8,16] (column-major B, i.e. row j of Bt == column j of B)
    int8_t Bt[8 * 16];
    for (int j = 0; j < 8; j++)
        for (int k = 0; k < 16; k++)
            Bt[j * 16 + k] = (int8_t)(j + k);

    int32_t C[8 * 8] = {0};

    matmul_a100(A, Bt, C);

    printf("C =\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            printf("%6d ", C[i * 8 + j]);
        printf("\n");
    }
    return 0;
}
