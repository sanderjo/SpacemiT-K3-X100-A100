To use all cores: how about using distcc?

Clean up:
```
killall -9 distccd
ps -eF | grep distcc # check no distccd processes anymore
```
Start a distccd dameon on X100 cores, and one on A100 cores:
```
distccd --daemon -p 3632
ps -eF | grep distccd $ yes, on X100 cores
echo $$ >  /proc/set_ai_thread # proceed bash shell on AI core 
distccd --daemon -p 3633 # yes, on A100 cores
ps -eF | grep distccd # yes!
```
ANd use them:
```
export DISTCC_HOSTS='localhost:3632 localhost:3633'
printenv | grep -i distcc # check
make -j16 CC=distcc
```

```
superkoning@spacemit:~/python-source/Python-3.14.2$ ps -eF | grep distccd
superko+  457706       1  0  1524   836  14 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457707  457706  0  1524   664  15 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457708  457706  0  1524   664   8 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457709  457706  0  1524   664   9 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457710  457706  0  1524   664  10 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457711  457706  0  1524   664  11 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457712  457706  0  1524   664  12 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457713  457706  0  1524   664  12 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457714  457706  0  1524   664  15 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457715  457706  0  1524   664   8 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457716  457706  0  1524   664   9 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457717  457706  0  1524   664  10 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457718  457706  0  1524   664  11 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457719  457706  0  1524   664  13 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457720  457706  0  1524   664  13 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457721  457706  0  1524   664  13 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457722  457706  0  1524   664  13 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457723  457706  0  1524   664  12 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457724  457706  0  1524   664  11 16:17 ?        00:00:00 /usr/bin/distccd --daemon -p 3632
superko+  457800       1  0  1524   792  15 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457801  457800  0  1524   924   8 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457802  457800  0  1524   924   9 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457803  457800  0  1524   924  10 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457804  457800  0  1524   924  11 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457805  457800  0  1524   924  12 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457806  457800  0  1524   924  13 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457807  457800  0  1524   924  13 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457808  457800  0  1524   924   9 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457809  457800  0  1524   924  10 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457810  457800  0  1524   924  11 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457811  457800  0  1524   924  12 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457812  457800  0  1524   924   8 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457813  457800  0  1524   924  14 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457814  457800  0  1524   924  14 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457815  457800  0  1524   924  14 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457816  457800  0  1524   924  14 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457817  457800  0  1524   924  13 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457818  457800  0  1524   924   8 16:18 ?        00:00:00 /usr/bin/distccd --daemon -p 3633
superko+  457826  381613  0  2255  1600  15 16:18 pts/3    00:00:00 grep --color=auto distccd
```
