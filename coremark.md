With -march=rv64gcb

```
superkoning@spacemit:~/git/coremark$ rm coremark.exe 

superkoning@spacemit:~/git/coremark$ make XCFLAGS="-O3 -march=rv64gcb" compile
cc -O2 -Ilinux -Iposix -I. -DFLAGS_STR=\""-O2 -O3 -march=rv64gcb  -lrt"\" -DITERATIONS=0 -O3 -march=rv64gcb core_list_join.c core_main.c core_matrix.c core_state.c core_util.c posix/core_portme.c -o ./coremark.exe -lrt

superkoning@spacemit:~/git/coremark$ ./coremark.exe 
2K performance run parameters for coremark.
CoreMark Size    : 666
Total ticks      : 13777
Total time (secs): 13.777000
Iterations/Sec   : 14516.948537
Iterations       : 200000
Compiler version : GCC15.2.0
Compiler flags   : -O2 -O3 -march=rv64gcb  -lrt
Memory location  : Please put data memory location here
                        (e.g. code in flash, data on heap etc)
seedcrc          : 0xe9f5
[0]crclist       : 0xe714
[0]crcmatrix     : 0x1fd7
[0]crcstate      : 0x8e3a
[0]crcfinal      : 0x4983
Correct operation validated. See README.md for run and reporting rules.
CoreMark 1.0 : 14516.948537 / GCC15.2.0 -O2 -O3 -march=rv64gcb  -lrt / Heap
superkoning@spacemit:~/git/coremark$
```

With -march=rv64gcb_zicond 


```
superkoning@spacemit:~/git/coremark$ rm coremark.exe

superkoning@spacemit:~/git/coremark$ make XCFLAGS="-O3 -march=rv64gcb_zicond" compile
cc -O2 -Ilinux -Iposix -I. -DFLAGS_STR=\""-O2 -O3 -march=rv64gcb_zicond  -lrt"\" -DITERATIONS=0 -O3 -march=rv64gcb_zicond core_list_join.c core_main.c core_matrix.c core_state.c core_util.c posix/core_portme.c -o ./coremark.exe -lrt

superkoning@spacemit:~/git/coremark$ ./coremark.exe 
2K performance run parameters for coremark.
CoreMark Size    : 666
Total ticks      : 13330
Total time (secs): 13.330000
Iterations/Sec   : 15003.750938
Iterations       : 200000
Compiler version : GCC15.2.0
Compiler flags   : -O2 -O3 -march=rv64gcb_zicond  -lrt
Memory location  : Please put data memory location here
                        (e.g. code in flash, data on heap etc)
seedcrc          : 0xe9f5
[0]crclist       : 0xe714
[0]crcmatrix     : 0x1fd7
[0]crcstate      : 0x8e3a
[0]crcfinal      : 0x4983
Correct operation validated. See README.md for run and reporting rules.
CoreMark 1.0 : 15003.750938 / GCC15.2.0 -O2 -O3 -march=rv64gcb_zicond  -lrt / Heap
superkoning@spacemit:~/git/coremark$ 
```
