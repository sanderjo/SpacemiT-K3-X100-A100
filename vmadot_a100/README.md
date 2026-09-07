# vmadot on the K3 A100

`vmadot` is SpacemiT's custom RISC-V vector instruction (extension
`xsmtvdotii`, part of their "IME"/matrix unit) for int8 matrix
multiply-accumulate: it takes two int8 vector registers holding tile
data and accumulates an int32 dot-product result into a vector
register group.

For the base path used here:

- `vs1` = A tile — 1 vector register, 8x16 int8 (128 elements = 1024
  bits = VLEN)
- `vs2` = B tile — 1 vector register, same layout, but **B stored
  column-major** (i.e. `Bt[8,16]`, row j of `Bt` = column j of `B`)
- `vd`  = C tile — with `MUL_C=2`, spans two registers (`v16`,`v17`),
  64 int32 elements

So one `vmadot` computes `C[8x8] (int32) = A[8x16] (int8) @ B^T`.

## Heterogeneous cores: X100 vs A100

The K3 has 16 cores split into two clusters:

- cores 0-7: **X100** (normal RV64GCV cores)
- cores 8-15: **A100** (same ISA, plus the matrix/IME unit)

A normal login shell's thread affinity defaults to the X100 cores. On
those cores `vmadot` does not fault or trap — it just doesn't do real
matrix math, so results come out wrong/garbage instead of erroring.

A thread only reaches the real A100 unit after routing itself there:

```
echo $$ > /proc/set_ai_thread
```

This file is world-writable, no root required. `vmadot_a100.c` does
this itself at startup (`route_to_a100()`), so it works standalone.
`BAD_BAD_vmadot_x100.c` is the same kernel with that call removed, to
show what happens if you forget it.

The A100 matrix unit also has a constant **-1 accumulator bias**,
which both `vmadot_a100.c` and `simulate_vmadot.py` correct for by
adding 1 back to every output element after the multiply.

## Files

- `vmadot_a100.c` — the real kernel: routes to an A100 core, runs the
  8x16 · 8x16^T int8 matmul via inline `vmadot` asm, corrects the -1
  bias, prints the 8x8 int32 result.
- `BAD_BAD_vmadot_x100.c` — same kernel, but **without** the A100
  routing step, left running on an X100 core. Demonstrates the
  silent-no-op failure mode: no crash, just wrong output.
- `simulate_vmadot.py` — pure-Python reference model of the same
  computation (raw vs. bias-corrected), used to independently verify
  the C/asm output.
- `Makefile` — builds both `vmadot_a100` and `BAD_BAD_vmadot_x100`.

## Building and running

```
make
./vmadot_a100
```

## Correct output

`A[8,16]` has row i = `i, i+1, ..., i+15`; `Bt[8,16]` has row j =
`j, j+1, ..., j+15` (so `B`'s column j is that same sequence). Running
`./vmadot_a100` on an A100 core prints:

```
C =
  1240   1360   1480   1600   1720   1840   1960   2080
  1360   1496   1632   1768   1904   2040   2176   2312
  1480   1632   1784   1936   2088   2240   2392   2544
  1600   1768   1936   2104   2272   2440   2608   2776
  1720   1904   2088   2272   2456   2640   2824   3008
  1840   2040   2240   2440   2640   2840   3040   3240
  1960   2176   2392   2608   2824   3040   3256   3472
  2080   2312   2544   2776   3008   3240   3472   3704
```

`python3 simulate_vmadot.py` reproduces this exact matrix (labeled
"corrected output"), confirming the kernel and the -1 bias correction
are right.

By contrast, `./BAD_BAD_vmadot_x100` (no A100 routing, run on an X100
core) prints a different, incorrect matrix — the failure mode you get
if `route_to_a100()` is skipped or forgotten.
