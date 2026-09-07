CC      = gcc
CFLAGS  = -march=rv64gcv_xsmtvdotii -mabi=lp64d -O2

TARGETS = vmadot_a100 BAD_BAD_vmadot_x100

all: $(TARGETS)

vmadot_a100: vmadot_a100.c
	$(CC) $(CFLAGS) $< -o $@

BAD_BAD_vmadot_x100: BAD_BAD_vmadot_x100.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
