# Further reading

- [remlab.net: RISC-V XSTIME](https://www.remlab.net/op/riscv-xstime.shtml) —
  independent writeup of SpacemiT's `xstime` extension and `vmadot`
  ("widening integer matrix multiply and accumulate"): matrix
  dimensions, register data layouts, and assembly usage.

- [spacemit-com/riscv-ime-extension-spec: instruction-func.adoc](https://github.com/spacemit-com/riscv-ime-extension-spec/blob/master/src/instruction-func.adoc) —
  SpacemiT's own IME (Integer Matrix Extension) instruction spec,
  including `vmadot`'s pseudocode. Note: it documents plain
  `C[...] += int32(A[...] * B[...])` accumulation with no bias/offset
  term — the constant **-1 accumulator bias** this repo works around
  is not in the spec, so it's either silicon-specific behavior or an
  undocumented corner of the real hardware.

- [Bruno Verachten: Benchmarking llama.cpp on SpacemiT K3 RISC-V AI cores vs standard RVV (Part 4)](https://bruno.verachten.fr/2026/03/12/benchmarking-llama.cpp-on-spacemit-k3-risc-v-ai-cores-vs-standard-rvv-part-4/) —
  the A100 "AI" cores run 30-34x *slower* than the X100 cores on
  generic RVV code, but become the fastest option once llama.cpp is
  built against SpacemiT's proprietary IME2 matrix extension. Also
  notes that the IME2 toolchain needed to compile that path isn't
  publicly available, which is the same gap this repo's hand-written
  `vmadot` inline asm works around for the base (non-IME2) instruction.
