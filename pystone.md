# pystone performance 

... so probably single-core (because of python3's GIL):

```
superkoning@spacemit:~$ wget -qO- https://raw.githubusercontent.com/sabnzbd/sabnzbd/develop/sabnzbd/utils/pystone.py | python3
Pystone(1.1) time for 50000 passes = 0.437191
This machine benchmarks at 114366 pystones/second
superkoning@spacemit:~$ 
```
with python 3.13 (which can matter a bit):
```

superkoning@spacemit:~$ python3 --version
Python 3.13.11
```

For reference: on an i5 from 2017:

```
sander@x360:~$ cat /proc/cpuinfo | grep "model name" | head -1
model name	: Intel(R) Core(TM) i5-8250U CPU @ 1.60GHz
sander@x360:~$ wget -qO- https://raw.githubusercontent.com/sabnzbd/sabnzbd/develop/sabnzbd/utils/pystone.py | python3.13
Pystone(1.1) time for 50000 passes = 0.213982
This machine benchmarks at 233664 pystones/second
sander@x360:~$
```

and a Celeron J4105 (also from 2017):

```
sander@brixit:~$ cat /proc/cpuinfo | grep "model name" | head -1
model name	: Intel(R) Celeron(R) J4105 CPU @ 1.50GHz

sander@brixit:~$ wget -qO- https://raw.githubusercontent.com/sabnzbd/sabnzbd/develop/sabnzbd/utils/pystone.py | python3.11
Pystone(1.1) time for 50000 passes = 0.280877
This machine benchmarks at 178014 pystones/second
sander@brixit:~$ wget -qO- https://raw.githubusercontent.com/sabnzbd/sabnzbd/develop/sabnzbd/utils/pystone.py | python3.12
Pystone(1.1) time for 50000 passes = 0.28376
This machine benchmarks at 176205 pystones/second
sander@brixit:~$ wget -qO- https://raw.githubusercontent.com/sabnzbd/sabnzbd/develop/sabnzbd/utils/pystone.py | python3.14
Pystone(1.1) time for 50000 passes = 0.265322


```
