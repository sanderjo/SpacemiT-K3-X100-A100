# compile

gcc -march=rv64gcv_xsmtvdotii -mabi=lp64d -O2 vmadot_a100.c -o vmadot_a100

# note: /proc/set_ai_thread

The K3 is heterogeneous (X100 cores 0-7, A100 cores 8-15); a normal login
session's affinity is locked to the X100 cores, and vmadot silently no-ops
there. A thread only reaches the real A100 matrix unit after routing itself
with:

    echo $$ > /proc/set_ai_thread

(world-writable, no root needed). `vmadot_a100.c` does this itself at
startup via `route_to_a100()`, so `./vmadot_a100` works standalone. Any new
standalone test program using `vmadot` needs to do the same before calling
it, or it'll silently no-op instead of computing anything.


