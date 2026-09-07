CC      = gcc
CFLAGS  = -march=rv64gcv_xsmtvdotii -mabi=lp64d -O2

TARGETS = vmadot_a100_tricky_A100_assignment vmadot_a100_better_A100_core_using BAD_BAD_vmadot_x100

all: $(TARGETS)

vmadot_a100_tricky_A100_assignment: vmadot_a100_tricky_A100_assignment.c
	$(CC) $(CFLAGS) $< -o $@

vmadot_a100_better_A100_core_using: vmadot_a100_better_A100_core_using.c
	$(CC) $(CFLAGS) $< -o $@

BAD_BAD_vmadot_x100: BAD_BAD_vmadot_x100.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
