Bruce Hoult has created program and a wrapper script to run commands on the AI cores:
```
superkoning@spacemit:~/to_ai_cores$ ls -al /usr/local/bin/ai*
-rwxr-xr-x 1 root root   73 Jan 29 03:58 /usr/local/bin/ai
-rwxr-xr-x 1 root root 6520 Jan 29 03:09 /usr/local/bin/aix
```

I used a certain tool to create a C program that does the same. See https://github.com/sanderjo/SpacemiT-K3-X100-A100/blob/main/to_ai_cores/to_ai_cores.c

```
superkoning@spacemit:~/to_ai_cores$ ll
total 28
drwxrwxr-x  3 superkoning superkoning  4096 Jan 31 11:06 ./
drwxr-x--- 30 superkoning superkoning  4096 Jan 31 11:02 ../
drwxrwxr-x  2 superkoning superkoning  4096 Jan 31 11:05 old/
-rwxrwxr-x  1 superkoning superkoning 10640 Jan 31 11:06 to_ai_cores*
-rw-rw-r--  1 superkoning superkoning  1725 Jan 31 10:52 to_ai_cores.c
superkoning@spacemit:~/to_ai_cores$ 
```

```
superkoning@spacemit:~/to_ai_cores$ ./to_ai_cores stress --cpu 20 --io 4 --vm 2 --vm-bytes 128M --timeout 60s
stress: info: [950537] dispatching hogs: 20 cpu, 4 io, 2 vm, 0 hdd
stress: info: [950537] successful run completed in 60s
superkoning@spacemit:~/to_ai_cores$ 

```


<img width="1076" height="738" alt="image" src="https://github.com/user-attachments/assets/c8a365f2-5695-4309-94f2-157a5cf149d5" />
