// vmadot_a100_tricky_A100_assignment.c
// Int8 matrix multiply using SpacemiT XSMTVDotII (IME) on the K3's A100 core.
// Tile shape for the base vmadot path on A100: M=N=8, K=16.
//   C[8x8] (int32) = A[8x16] (int8) * B^T  (B stored column-major, i.e. Bt[8x16])
//
// vs1 = A tile   (1 vector reg,  8*16 = 128 int8 elements = 1024 bits = VLEN)
// vs2 = B tile   (1 vector reg,  same layout, column-major)
// vd  = C tile   (MUL_C=2 -> v16,v17; 64 int32 elements)
//
// The K3 is heterogeneous (X100 cores 0-7, A100 cores 8-15); a thread only
// actually reaches the A100 matrix unit after routing itself there via
// /proc/set_ai_thread -- on any other core vmadot silently no-ops. The unit
// also has a constant -1 accumulator bias, corrected below.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static void route_to_a100(void) {
    FILE *f = fopen("/proc/set_ai_thread", "w");
    if (!f || fprintf(f, "%d", getpid()) < 0) {
        perror("routing thread to A100 core via /proc/set_ai_thread");
        exit(1);
    }
    fclose(f);
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

int main(void) {
    route_to_a100();

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
