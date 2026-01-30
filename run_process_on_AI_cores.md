# Run process on the AI cores

If you use the bash trick `echo $$ > /proc/set_ai_thread` ... all following (sub)processes run on the AI cores. Handy.

If you only want to start & run one process (or progam) on the AI cores, @brucehoult has made a method for that:

<img width="793" height="816" alt="image" src="https://github.com/user-attachments/assets/2e0885f8-4526-494c-9492-7d99bcdff883" />


So: with that tool `ai` installed, prepend `ai` to your command line, and ... bingo

```
superkoning@spacemit:~$ ai stress --cpu 20 --io 4 --vm 2 --vm-bytes 128M --timeout 30s
stress: info: [934918] dispatching hogs: 20 cpu, 4 io, 2 vm, 0 hdd
stress: info: [934918] successful run completed in 30s
superkoning@spacemit:~$ 
```

<img width="1088" height="846" alt="image" src="https://github.com/user-attachments/assets/6999ee6d-44f3-4dc0-b4a6-1a09a545a2c1" />



# All cores? Yes

To put all cores under load, run stress on the normal cores and at the same time on the ai cores:


```
superkoning@spacemit:~$ stress --cpu 20 --io 4 --vm 2 --vm-bytes 128M --timeout 60s &
[1] 935255
superkoning@spacemit:~$ stress: info: [935255] dispatching hogs: 20 cpu, 4 io, 2 vm, 0 hdd

superkoning@spacemit:~$ ai stress --cpu 20 --io 4 --vm 2 --vm-bytes 128M --timeout 60s 
stress: info: [935290] dispatching hogs: 20 cpu, 4 io, 2 vm, 0 hdd
```



<img width="1088" height="846" alt="image" src="https://github.com/user-attachments/assets/628b2f81-8d44-432f-a633-af9defca3395" />



