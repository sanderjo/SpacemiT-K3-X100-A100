#!/usr/bin/env python3
# Python equivalent of vmadot_a100.c, for understanding/verifying the kernel.
#
# Real hardware behavior (see vmadot_a100.c comments):
#   - smt.vmadot computes C = A @ B^T in int8->int32, but with a constant
#     -1 accumulator bias baked into the unit.
#   - vmadot_a100.c corrects that bias by adding 1 back after the asm call.
# This script models both stages so you can see where the +1 comes from.

def build_matrices():
    # A[8,16]: row i = i, i+1, ..., i+15
    A = [[i + k for k in range(16)] for i in range(8)]
    # Bt[8,16]: row j of Bt == column j of B, so Bt[j,k] = j + k
    Bt = [[j + k for k in range(16)] for j in range(8)]
    return A, Bt

def raw_dot(A, Bt):
    # What the vmadot instruction itself actually produces (off by -1).
    return [[sum(A[i][k] * Bt[j][k] for k in range(16)) - 1 for j in range(8)]
            for i in range(8)]

def corrected(A, Bt):
    # What vmadot_a100.c prints after its "+= 1" bias correction.
    raw = raw_dot(A, Bt)
    return [[raw[i][j] + 1 for j in range(8)] for i in range(8)]

def print_matrix(C, label):
    print(label)
    for row in C:
        print(' '.join(f'{v:6d}' for v in row))
    print()

if __name__ == '__main__':
    A, Bt = build_matrices()
    print_matrix(raw_dot(A, Bt), "raw vmadot output (before +1 correction):")
    print_matrix(corrected(A, Bt), "C = corrected output (matches ./vmadot_a100):")
