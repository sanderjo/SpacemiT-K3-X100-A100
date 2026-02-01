# How to run process on the higher ("AI"?) cores

## TLDR
```
superkoning@spacemit:~$ cat /usr/local/bin/run_on_ai_cores 
#!/bin/bash
echo $$ > /proc/set_ai_thread && exec "$@"
```

Then run like
```
run_on_ai_cores stress make -j16
```
and
```
run_on_ai_cores stress --cpu 20 --io 4 --vm 2 --vm-bytes 128M --timeout 30s
```

## Long

A SpacemiT person said:

> Use `ps` to find the current bash process ID (PID).
> Then, use `echo $pid > /proc/set_ai_thread` to bind the bash process to the A100 GPU. Any programs launched by this bash process afterward will then run on the A100.

So:
```
superkoning@spacemit:~$ ps
    PID TTY          TIME CMD
 179205 pts/1    00:00:00 bash
 183056 pts/1    00:00:00 ps
superkoning@spacemit:~$ echo 179205 > /proc/set_ai_thread
superkoning@spacemit:~$
```
EDIT: shorter

```
echo $$ > /proc/set_ai_thread
```

and indeed, now a `make -j16` of the python3 sourcecode runs on cores 8-15:

<img width="1147" height="735" alt="image" src="https://github.com/user-attachments/assets/59b22464-71ae-48cf-9aa6-6deefa0373ba" />



Or in text: See column 7 = "PSR       processor that process last executed on.": the gcc stuff is running on cores 8 - 15.

```
superkoning@spacemit:~$ ps -eF
UID          PID    PPID  C    SZ   RSS PSR STIME TTY          TIME CMD
root           1       0  0  5293 13788   0 Jan20 ?        00:00:31 /sbin/init splash
root           2       0  0     0     0   1 Jan20 ?        00:00:00 [kthreadd]
...
...
root      183385       2  0     0     0   5 08:16 ?        00:00:00 [kworker/5:0-events_freezable_pwr_efficient]
root      183389       2  0     0     0   7 08:16 ?        00:00:00 [kworker/7:1-mm_percpu_wq]
superko+  184068  179205  0  4811 12304   9 08:17 pts/1    00:00:00 make -j8
superko+  184073  184068  0   539  1180  14 08:17 pts/1    00:00:00 /bin/sh -e -c gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-par
superko+  184074  184073  0  2585  3044  15 08:17 pts/1    00:00:00 gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall -std=c11 -Wextra -Wno-unused-parameter -Wno-missi
superko+  184078  184074 99 70812 228052 11 08:17 pts/1    00:00:49 /usr/libexec/gcc/riscv64-linux-gnu/15/cc1 -quiet -I ./Include/internal -I ./Include/internal/mimalloc -I . -I ./In
superko+  184212  184068  0   539  1172  14 08:18 pts/1    00:00:00 /bin/sh -e -c gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-par
superko+  184213  184212  0  2585  3056  14 08:18 pts/1    00:00:00 gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall -std=c11 -Wextra -Wno-unused-parameter -Wno-missi
superko+  184214  184213 99 45932 150208 12 08:18 pts/1    00:00:21 /usr/libexec/gcc/riscv64-linux-gnu/15/cc1 -quiet -I ./Include/internal -I ./Include/internal/mimalloc -I . -I ./In
superko+  184215  184068  0   539  1188   8 08:18 pts/1    00:00:00 /bin/sh -e -c gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-par
superko+  184216  184215  0  2585  3012  14 08:18 pts/1    00:00:00 gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall -std=c11 -Wextra -Wno-unused-parameter -Wno-missi
superko+  184218  184216 99 49715 159008 14 08:18 pts/1    00:00:21 /usr/libexec/gcc/riscv64-linux-gnu/15/cc1 -quiet -I ./Include/internal -I ./Include/internal/mimalloc -I . -I ./In
superko+  184244  184068  0   539  1068   8 08:18 pts/1    00:00:00 /bin/sh -e -c gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-par
superko+  184245  184244  0  2585  3228   8 08:18 pts/1    00:00:00 gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall -std=c11 -Wextra -Wno-unused-parameter -Wno-missi
superko+  184246  184245 99 43333 137992  8 08:18 pts/1    00:00:13 /usr/libexec/gcc/riscv64-linux-gnu/15/cc1 -quiet -I ./Include/internal -I ./Include/internal/mimalloc -I . -I ./In
superko+  184256  184068  0   539  1240  10 08:18 pts/1    00:00:00 /bin/sh -e -c gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-par
superko+  184257  184256  0  2585  3052  10 08:18 pts/1    00:00:00 gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall -std=c11 -Wextra -Wno-unused-parameter -Wno-missi
superko+  184258  184257 99 34272 102904 10 08:18 pts/1    00:00:08 /usr/libexec/gcc/riscv64-linux-gnu/15/cc1 -quiet -I ./Include/internal -I ./Include/internal/mimalloc -I . -I ./In
root      184267       2  0     0     0   4 08:18 ?        00:00:00 [kworker/4:0]
superko+  184281  184068  0   539  1184  15 08:18 pts/1    00:00:00 /bin/sh -e -c gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-par
superko+  184282  184281  0  2585  3052  15 08:18 pts/1    00:00:00 gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall -std=c11 -Wextra -Wno-unused-parameter -Wno-missi
superko+  184283  184282 99 30858 84776  15 08:18 pts/1    00:00:03 /usr/libexec/gcc/riscv64-linux-gnu/15/cc1 -quiet -I ./Include/internal -I ./Include/internal/mimalloc -I . -I ./In
superko+  184285  184068  0   539  1192   9 08:18 pts/1    00:00:00 /bin/sh -e -c gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-par
superko+  184286  184285  0  2585  2936   9 08:18 pts/1    00:00:00 gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall -std=c11 -Wextra -Wno-unused-parameter -Wno-missi
superko+  184287  184286 99 34594 88092   9 08:18 pts/1    00:00:02 /usr/libexec/gcc/riscv64-linux-gnu/15/cc1 -quiet -I ./Include/internal -I ./Include/internal/mimalloc -I . -I ./In
superko+  184289  184068  0   539  1216  13 08:18 pts/1    00:00:00 /bin/sh -e -c gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-par
superko+  184290  184289  0  2585  3152  13 08:18 pts/1    00:00:00 gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall -std=c11 -Wextra -Wno-unused-parameter -Wno-missi
superko+  184291  184290 99 30407 80884  13 08:18 pts/1    00:00:02 /usr/libexec/gcc/riscv64-linux-gnu/15/cc1 -quiet -I ./Include/internal -I ./Include/internal/mimalloc -I . -I ./In
superko+  184294  179296  0  3018  3852   3 08:18 pts/3    00:00:00 ps -eF
superkoning@spacemit:~$ 
```

# Ugly randomizer

How about this: 
- Start `make -j16`, which will start the gcc processes on the first 8 cores, 16 processes in parallel, and a new after one has finishes
- Continously run a seperate script that moves some of those processes to the AI cores

Bingo ... some processes still on the first 8 cores, but also processes on the higher 8 cores!

<img width="2016" height="1366" alt="image" src="https://github.com/user-attachments/assets/cf6c6ecb-dbb1-4479-bdca-13d5bd1ca688" />


Hacky: just move the first 15 processes with `gcc` in it to the AI cores:
```
superkoning@spacemit:~$ cat randomize_gcc.sh
ps -eF | grep  -e gcc | grep -vi grep |  awk '{ print "echo " $2 " > /proc/set_ai_thread " }'   | head -15 | sh
```
and run that script:
```
superkoning@spacemit:~$ while true; do ./randomize_gcc.sh; sleep 0.2; done
```
Then start `make clean && make -j16`


But ... does it work reliably? No: an `internal compiler error: Segmentation fault`:

```
gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wstrict-prototypes -Werror=implicit-function-declaration -fvisibility=hidden  -I./Include/internal -I./Include/internal/mimalloc  -I. -I./Include    -DPy_BUILD_CORE -o Objects/classobject.o Objects/classobject.c
during RTL pass: final
Parser/pegen.c: In function ‘_PyPegen_new_identifier’:
Parser/pegen.c:569:1: internal compiler error: Segmentation fault
  569 | }
      | ^
gcc -c -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O3 -Wall    -std=c11 -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wstrict-prototypes -Werror=implicit-function-declaration -fvisibility=hidden  -I./Include/internal -I./Include/internal/mimalloc  -I. -I./Include    -DPy_BUILD_CORE -o Objects/codeobject.o Objects/codeobject.c
```


# Randomizer with 'stress'

```
superkoning@spacemit:~$ stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
stress: info: [242563] dispatching hogs: 16 cpu, 4 io, 2 vm, 0 hdd
```

```
superkoning@spacemit:~$ cat randomize_stress.sh
ps -eF | grep  -e stress | grep -vi grep |  awk '{ print "echo " $2 " > /proc/set_ai_thread " }'   | head -10 | sh
```
After running that: some `stress` processes on higher cores, some on the lower cores

```
superkoning@spacemit:~$ ps -eF | grep  -e stress | grep -vi grep
superko+  242563  189526  0   653  1168   0 10:27 pts/5    00:00:00 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242564  242563 88   653   404   9 10:27 pts/5    00:04:20 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242565  242563  8   653   404  13 10:27 pts/5    00:00:26 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242566  242563 83 33422 104748 11 10:27 pts/5    00:04:06 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242567  242563 88   653   404  12 10:27 pts/5    00:04:21 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242568  242563  9   653   404  13 10:27 pts/5    00:00:27 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242569  242563 84 33422 89436  14 10:27 pts/5    00:04:09 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242570  242563 83   653   404  15 10:27 pts/5    00:04:04 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242571  242563  9   653   404  13 10:27 pts/5    00:00:26 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242572  242563 82   653   404   8 10:27 pts/5    00:04:02 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242573  242563 11   653   404   1 10:27 pts/5    00:00:32 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242574  242563 58   653   404   2 10:27 pts/5    00:02:52 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242575  242563 61   653   404   3 10:27 pts/5    00:03:00 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242576  242563 56   653   404   7 10:27 pts/5    00:02:46 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242577  242563 57   653   404   4 10:27 pts/5    00:02:49 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242578  242563 54   653   404   0 10:27 pts/5    00:02:41 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242579  242563 57   653   404   4 10:27 pts/5    00:02:49 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242580  242563 56   653   404   6 10:27 pts/5    00:02:47 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242581  242563 63   653   404   1 10:27 pts/5    00:03:07 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242582  242563 59   653   404   5 10:27 pts/5    00:02:53 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242583  242563 56   653   404   3 10:27 pts/5    00:02:45 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242584  242563 59   653   404   7 10:27 pts/5    00:02:56 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superko+  242585  242563 59   653   404   2 10:27 pts/5    00:02:56 stress --cpu 16 --io 4 --vm 2 --vm-bytes 128M --timeout 1000s
superkoning@spacemit:~$
```



<img width="2001" height="1650" alt="image" src="https://github.com/user-attachments/assets/5875a9f5-1ef4-404e-acd9-fde3e6823785" />

