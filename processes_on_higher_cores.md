# How to run process on the higher ("AI"?) cores

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
