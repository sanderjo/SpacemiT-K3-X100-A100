# run_on_ai_cores

## Start

Bruce Hoult has created program and a wrapper script to run commands on the AI cores:
```
superkoning@spacemit:~ ls -al /usr/local/bin/ai*
-rwxr-xr-x 1 root root   73 Jan 29 03:58 /usr/local/bin/ai
-rwxr-xr-x 1 root root 6520 Jan 29 03:09 /usr/local/bin/aix
```
That works on the K3 provided by `SpacemiT`. The shell script `ai` is the wrapper for `aix`. I think `aix` is written in assembly, but I've no source code and I don't understand RISC-V assembly

## C program run_on_ai_cores

So I used a certain tool to create a C program that does the same: run a commandline on the AI cores (Core 8 -15). See source code [run_on_ai_cores/run_on_ai_cores.c](https://github.com/sanderjo/SpacemiT-K3-X100-A100/blob/main/run_on_ai_cores/run_on_ai_cores.c)
```
superkoning@spacemit:~/run_on_ai_cores$ ll
total 32
drwxrwxr-x  3 superkoning superkoning  4096 Jan 31 11:30 ./
drwxr-x--- 30 superkoning superkoning  4096 Jan 31 11:29 ../
drwxrwxr-x  2 superkoning superkoning  4096 Jan 31 11:05 old/
-rwxrwxr-x  1 superkoning superkoning 14088 Jan 31 11:30 run_on_ai_cores*
-rw-rw-r--  1 superkoning superkoning  1731 Jan 31 11:23 run_on_ai_cores.c
superkoning@spacemit:~/run_on_ai_cores$ 

```

```
superkoning@spacemit:~/run_on_ai_cores$ ./run_on_ai_cores stress --cpu 20 --io 4 --vm 2 --vm-bytes 128M --timeout 60s
stress: info: [950537] dispatching hogs: 20 cpu, 4 io, 2 vm, 0 hdd
stress: info: [950537] successful run completed in 60s
superkoning@spacemit:~/run_on_ai_cores$ 

```

And into `/usr/local/bin/` so it's available for all users on this remote K3 provided by SpacemiT.


```
superkoning@spacemit:~/run_on_ai_cores$ sudo cp run_on_ai_cores /usr/local/bin/
superkoning@spacemit:~/run_on_ai_cores$ 
```

```
# normal commands
superkoning@spacemit:~$ run_on_ai_cores
run_on_ai_cores
superkoning@spacemit:~$ run_on_ai_cores echo $$
952505
superkoning@spacemit:~$ run_on_ai_cores uptime
 11:49:06 up 11 days,  1:31, 10 users,  load average: 0.02, 0.33, 1.02
superkoning@spacemit:~$ 

# interesting command
superkoning@spacemit:~$ run_on_ai_cores stress --cpu 20 --io 4 --vm 2 --vm-bytes 128M --timeout 5s
stress: info: [952729] dispatching hogs: 20 cpu, 4 io, 2 vm, 0 hdd
stress: info: [952729] successful run completed in 5s
superkoning@spacemit:~$ 


```


<img width="1076" height="738" alt="image" src="https://github.com/user-attachments/assets/c8a365f2-5695-4309-94f2-157a5cf149d5" />
