```
superkoning@spacemit:~$ openssl speed -multi 4 -evp aes-256-gcm 2>&1 | tail -5
built on: Tue Sep 30 18:47:50 2025 UTC
options: bn(64,64)
compiler: gcc -fPIC -pthread -Wa,--noexecstack -Wall -fzero-call-used-regs=used-gpr -Wa,--noexecstack -g -O2 -Werror=implicit-function-declaration -fno-omit-frame-pointer -ffile-prefix-map=/build/openssl-FDQ0xR/openssl-3.5.3=. -fstack-protector-strong -Wformat -Werror=format-security -fno-stack-clash-protection -fdebug-prefix-map=/build/openssl-FDQ0xR/openssl-3.5.3=/usr/src/openssl-3.5.3-1ubuntu2 -DOPENSSL_USE_NODELETE -DOPENSSL_PIC -DOPENSSL_BUILDING_OPENSSL -DZLIB -DZSTD -DNDEBUG -Wdate-time -D_FORTIFY_SOURCE=3
CPUINFO: OPENSSL_riscvcap=ZBA_ZBB_ZBC_ZBS_ZKT_V_ZVBB_ZVBC_ZVKB_ZVKG_ZVKNED_ZVKNHA_ZVKNHB_ZVKSED_ZVKSH
AES-256-GCM      88486.50k   318543.85k  1208611.75k  3362257.24k  6994550.78k  7578408.28k

```

```
superkoning@spacemit:~$ openssl speed -multi 8 -evp aes-256-gcm 2>&1 | tail -5
built on: Tue Sep 30 18:47:50 2025 UTC
options: bn(64,64)
compiler: gcc -fPIC -pthread -Wa,--noexecstack -Wall -fzero-call-used-regs=used-gpr -Wa,--noexecstack -g -O2 -Werror=implicit-function-declaration -fno-omit-frame-pointer -ffile-prefix-map=/build/openssl-FDQ0xR/openssl-3.5.3=. -fstack-protector-strong -Wformat -Werror=format-security -fno-stack-clash-protection -fdebug-prefix-map=/build/openssl-FDQ0xR/openssl-3.5.3=/usr/src/openssl-3.5.3-1ubuntu2 -DOPENSSL_USE_NODELETE -DOPENSSL_PIC -DOPENSSL_BUILDING_OPENSSL -DZLIB -DZSTD -DNDEBUG -Wdate-time -D_FORTIFY_SOURCE=3
CPUINFO: OPENSSL_riscvcap=ZBA_ZBB_ZBC_ZBS_ZKT_V_ZVBB_ZVBC_ZVKB_ZVKG_ZVKNED_ZVKNHA_ZVKNHB_ZVKSED_ZVKSH
AES-256-GCM     156355.55k   556088.09k  2109776.47k  5871751.17k 12233815.38k 13258801.15k

```

```
superkoning@spacemit:~$ openssl speed -multi 16 -evp aes-256-gcm 2>&1 | tail -5
built on: Tue Sep 30 18:47:50 2025 UTC
options: bn(64,64)
compiler: gcc -fPIC -pthread -Wa,--noexecstack -Wall -fzero-call-used-regs=used-gpr -Wa,--noexecstack -g -O2 -Werror=implicit-function-declaration -fno-omit-frame-pointer -ffile-prefix-map=/build/openssl-FDQ0xR/openssl-3.5.3=. -fstack-protector-strong -Wformat -Werror=format-security -fno-stack-clash-protection -fdebug-prefix-map=/build/openssl-FDQ0xR/openssl-3.5.3=/usr/src/openssl-3.5.3-1ubuntu2 -DOPENSSL_USE_NODELETE -DOPENSSL_PIC -DOPENSSL_BUILDING_OPENSSL -DZLIB -DZSTD -DNDEBUG -Wdate-time -D_FORTIFY_SOURCE=3
CPUINFO: OPENSSL_riscvcap=ZBA_ZBB_ZBC_ZBS_ZKT_V_ZVBB_ZVBC_ZVKB_ZVKG_ZVKNED_ZVKNHA_ZVKNHB_ZVKSED_ZVKSH
AES-256-GCM     163969.22k   599370.66k  2276838.51k  6316781.06k 13118496.28k 14222035.80k

```
