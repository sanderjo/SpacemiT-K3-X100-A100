// BAD_BAD_vmadot_x100.c
// Same as vmadot_a100.c but WITHOUT route_to_a100(): run from a normal
// login session, the thread stays on an X100 core, so vmadot silently
// no-ops and C comes out all zeros instead of the real matmul result.
//
// See compile.md / vmadot_a100.c for the real, correct version.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

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
