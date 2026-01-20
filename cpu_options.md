What's in `/proc/cpuinfo`: what options:
```
superkoning@spacemit:~$ cat /proc/cpuinfo | grep isa | head -1 | awk '{ print $NF }' | sed 's/_/ " -e "/g'
rv64imafdcv " -e "zicbom " -e "zicboz " -e "zicntr " -e "zicond " -e "zicsr " -e "zifencei " -e "zihintntl " -e "zihintpause " -e "zihpm " -e "zimop " -e "zawrs " -e "zfa " -e "zfh " -e "zfhmin " -e "zca " -e "zcb " -e "zcd " -e "zcmop " -e "zba " -e "zbb " -e "zbc " -e "zbs " -e "zkt " -e "zvbb " -e "zvbc " -e "zve32f " -e "zve32x " -e "zve64d " -e "zve64f " -e "zve64x " -e "zvfh " -e "zvfhmin " -e "zvkb " -e "zvkg " -e "zvkned " -e "zvknha " -e "zvknhb " -e "zvksed " -e "zvksh " -e "zvkt " -e "sdtrig " -e "smaia " -e "smstateen " -e "ssaia " -e "sscofpmf " -e "sstc " -e "svinval " -e "svnapot " -e "svpbmt


```
Let clang explain what those options mean

```

superkoning@spacemit:~$ clang --target=riscv64 --print-supported-extensions | grep -e "rv64imafdcv " -e "zicbom " -e "zicboz " -e "zicntr " -e "zicond " -e "zicsr " -e "zifencei " -e "zihintntl " -e "zihintpause " -e "zihpm " -e "zimop " -e "zawrs " -e "zfa " -e "zfh " -e "zfhmin " -e "zca " -e "zcb " -e "zcd " -e "zcmop " -e "zba " -e "zbb " -e "zbc " -e "zbs " -e "zkt " -e "zvbb " -e "zvbc " -e "zve32f " -e "zve32x " -e "zve64d " -e "zve64f " -e "zve64x " -e "zvfh " -e "zvfhmin " -e "zvkb " -e "zvkg " -e "zvkned " -e "zvknha " -e "zvknhb " -e "zvksed " -e "zvksh " -e "zvkt " -e "sdtrig " -e "smaia " -e "smstateen " -e "ssaia " -e "sscofpmf " -e "sstc " -e "svinval " -e "svnapot " -e "svpbmt "
Ubuntu clang version 21.1.6 (3ubuntu1)
Target: riscv64
Thread model: posix
InstalledDir: /usr/lib/llvm-21/bin
    zicbom               1.0       'Zicbom' (Cache-Block Management Instructions)
    zicboz               1.0       'Zicboz' (Cache-Block Zero Instructions)
    zicntr               2.0       'Zicntr' (Base Counters and Timers)
    zicond               1.0       'Zicond' (Integer Conditional Operations)
    zicsr                2.0       'Zicsr' (CSRs)
    zifencei             2.0       'Zifencei' (fence.i)
    zihintntl            1.0       'Zihintntl' (Non-Temporal Locality Hints)
    zihintpause          2.0       'Zihintpause' (Pause Hint)
    zihpm                2.0       'Zihpm' (Hardware Performance Counters)
    zimop                1.0       'Zimop' (May-Be-Operations)
    zawrs                1.0       'Zawrs' (Wait on Reservation Set)
    zfa                  1.0       'Zfa' (Additional Floating-Point)
    zfh                  1.0       'Zfh' (Half-Precision Floating-Point)
    zfhmin               1.0       'Zfhmin' (Half-Precision Floating-Point Minimal)
    zca                  1.0       'Zca' (part of the C extension, excluding compressed floating point loads/stores)
    zcb                  1.0       'Zcb' (Compressed basic bit manipulation instructions)
    zcd                  1.0       'Zcd' (Compressed Double-Precision Floating-Point Instructions)
    zcmop                1.0       'Zcmop' (Compressed May-Be-Operations)
    zba                  1.0       'Zba' (Address Generation Instructions)
    zbb                  1.0       'Zbb' (Basic Bit-Manipulation)
    zbc                  1.0       'Zbc' (Carry-Less Multiplication)
    zbs                  1.0       'Zbs' (Single-Bit Instructions)
    zkt                  1.0       'Zkt' (Data Independent Execution Latency)
    zvbb                 1.0       'Zvbb' (Vector basic bit-manipulation instructions)
    zvbc                 1.0       'Zvbc' (Vector Carryless Multiplication)
    zve32f               1.0       'Zve32f' (Vector Extensions for Embedded Processors with maximal 32 EEW and F extension)
    zve32x               1.0       'Zve32x' (Vector Extensions for Embedded Processors with maximal 32 EEW)
    zve64d               1.0       'Zve64d' (Vector Extensions for Embedded Processors with maximal 64 EEW, F and D extension)
    zve64f               1.0       'Zve64f' (Vector Extensions for Embedded Processors with maximal 64 EEW and F extension)
    zve64x               1.0       'Zve64x' (Vector Extensions for Embedded Processors with maximal 64 EEW)
    zvfh                 1.0       'Zvfh' (Vector Half-Precision Floating-Point)
    zvfhmin              1.0       'Zvfhmin' (Vector Half-Precision Floating-Point Minimal)
    zvkb                 1.0       'Zvkb' (Vector Bit-manipulation used in Cryptography)
    zvkg                 1.0       'Zvkg' (Vector GCM instructions for Cryptography)
    zvkned               1.0       'Zvkned' (Vector AES Encryption & Decryption (Single Round))
    zvknha               1.0       'Zvknha' (Vector SHA-2 (SHA-256 only))
    zvknhb               1.0       'Zvknhb' (Vector SHA-2 (SHA-256 and SHA-512))
    zvksed               1.0       'Zvksed' (SM4 Block Cipher Instructions)
    zvksh                1.0       'Zvksh' (SM3 Hash Function Instructions)
    zvkt                 1.0       'Zvkt' (Vector Data-Independent Execution Latency)
    sdtrig               1.0       'Sdtrig' (Debugger triggers)
    smaia                1.0       'Smaia' (Advanced Interrupt Architecture Machine Level)
    smstateen            1.0       'Smstateen' (Machine-mode view of the state-enable extension)
    ssaia                1.0       'Ssaia' (Advanced Interrupt Architecture Supervisor Level)
    sscofpmf             1.0       'Sscofpmf' (Count Overflow and Mode-Based Filtering)
    sstc                 1.0       'Sstc' (Supervisor-mode timer interrupts)
    svinval              1.0       'Svinval' (Fine-Grained Address-Translation Cache Invalidation)
    svnapot              1.0       'Svnapot' (NAPOT Translation Contiguity)
    svpbmt               1.0       'Svpbmt' (Page-Based Memory Types)
superkoning@spacemit:~$ 


```

Or fully automated:

```
superkoning@spacemit:~/clang$ clang --target=riscv64 --print-supported-extensions  > clang_options.txt
Ubuntu clang version 21.1.6 (3ubuntu1)
Target: riscv64
Thread model: posix
InstalledDir: /usr/lib/llvm-21/bin

superkoning@spacemit:~/clang$ cat /proc/cpuinfo | grep isa | head -1 | awk '{ print $NF }' | tr "_" "\n" | awk '{ print "grep \"" $1 " \" clang_options.txt " }' | sh | sort 
    sdtrig               1.0       'Sdtrig' (Debugger triggers)
    smaia                1.0       'Smaia' (Advanced Interrupt Architecture Machine Level)
    smstateen            1.0       'Smstateen' (Machine-mode view of the state-enable extension)
    ssaia                1.0       'Ssaia' (Advanced Interrupt Architecture Supervisor Level)
    sscofpmf             1.0       'Sscofpmf' (Count Overflow and Mode-Based Filtering)
    sstc                 1.0       'Sstc' (Supervisor-mode timer interrupts)
    svinval              1.0       'Svinval' (Fine-Grained Address-Translation Cache Invalidation)
    svnapot              1.0       'Svnapot' (NAPOT Translation Contiguity)
    svpbmt               1.0       'Svpbmt' (Page-Based Memory Types)
    zawrs                1.0       'Zawrs' (Wait on Reservation Set)
    zba                  1.0       'Zba' (Address Generation Instructions)
    zbb                  1.0       'Zbb' (Basic Bit-Manipulation)
    zbc                  1.0       'Zbc' (Carry-Less Multiplication)
    zbs                  1.0       'Zbs' (Single-Bit Instructions)
    zca                  1.0       'Zca' (part of the C extension, excluding compressed floating point loads/stores)
    zcb                  1.0       'Zcb' (Compressed basic bit manipulation instructions)
    zcd                  1.0       'Zcd' (Compressed Double-Precision Floating-Point Instructions)
    zcmop                1.0       'Zcmop' (Compressed May-Be-Operations)
    zfa                  1.0       'Zfa' (Additional Floating-Point)
    zfh                  1.0       'Zfh' (Half-Precision Floating-Point)
    zfhmin               1.0       'Zfhmin' (Half-Precision Floating-Point Minimal)
    zicbom               1.0       'Zicbom' (Cache-Block Management Instructions)
    zicboz               1.0       'Zicboz' (Cache-Block Zero Instructions)
    zicntr               2.0       'Zicntr' (Base Counters and Timers)
    zicond               1.0       'Zicond' (Integer Conditional Operations)
    zicsr                2.0       'Zicsr' (CSRs)
    zifencei             2.0       'Zifencei' (fence.i)
    zihintntl            1.0       'Zihintntl' (Non-Temporal Locality Hints)
    zihintpause          2.0       'Zihintpause' (Pause Hint)
    zihpm                2.0       'Zihpm' (Hardware Performance Counters)
    zimop                1.0       'Zimop' (May-Be-Operations)
    zkt                  1.0       'Zkt' (Data Independent Execution Latency)
    zvbb                 1.0       'Zvbb' (Vector basic bit-manipulation instructions)
    zvbc                 1.0       'Zvbc' (Vector Carryless Multiplication)
    zve32f               1.0       'Zve32f' (Vector Extensions for Embedded Processors with maximal 32 EEW and F extension)
    zve32x               1.0       'Zve32x' (Vector Extensions for Embedded Processors with maximal 32 EEW)
    zve64d               1.0       'Zve64d' (Vector Extensions for Embedded Processors with maximal 64 EEW, F and D extension)
    zve64f               1.0       'Zve64f' (Vector Extensions for Embedded Processors with maximal 64 EEW and F extension)
    zve64x               1.0       'Zve64x' (Vector Extensions for Embedded Processors with maximal 64 EEW)
    zvfh                 1.0       'Zvfh' (Vector Half-Precision Floating-Point)
    zvfhmin              1.0       'Zvfhmin' (Vector Half-Precision Floating-Point Minimal)
    zvkb                 1.0       'Zvkb' (Vector Bit-manipulation used in Cryptography)
    zvkg                 1.0       'Zvkg' (Vector GCM instructions for Cryptography)
    zvkned               1.0       'Zvkned' (Vector AES Encryption & Decryption (Single Round))
    zvknha               1.0       'Zvknha' (Vector SHA-2 (SHA-256 only))
    zvknhb               1.0       'Zvknhb' (Vector SHA-2 (SHA-256 and SHA-512))
    zvksed               1.0       'Zvksed' (SM4 Block Cipher Instructions)
    zvksh                1.0       'Zvksh' (SM3 Hash Function Instructions)
    zvkt                 1.0       'Zvkt' (Vector Data-Independent Execution Latency)
superkoning@spacemit:~/clang$ 


```


