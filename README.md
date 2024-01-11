## Testing Data

Do not call `fsync` (or `fflush` when using C library) after write:
```sh
./test.sh
```

```
[     write]line size:       8, lines per second:   3378378, speed:     25.77 MiB/s, sync:0
[    fwrite]line size:       8, lines per second:  30864198, speed:    235.48 MiB/s, sync:0

[     write]line size:      64, lines per second:   1475579, speed:     90.06 MiB/s, sync:0
[    fwrite]line size:      64, lines per second:  26109660, speed:   1593.61 MiB/s, sync:0

[     write]line size:     128, lines per second:   2102607, speed:    256.67 MiB/s, sync:0
[    fwrite]line size:     128, lines per second:  15503876, speed:   1892.56 MiB/s, sync:0

[     write]line size:    1024, lines per second:   1147315, speed:   1120.43 MiB/s, sync:0
[    fwrite]line size:    1024, lines per second:   2366304, speed:   2310.84 MiB/s, sync:0

[     write]line size:    2048, lines per second:    932053, speed:   1820.42 MiB/s, sync:0
[    fwrite]line size:    2048, lines per second:   1185255, speed:   2314.95 MiB/s, sync:0

[     write]line size:    4096, lines per second:    472992, speed:   1847.63 MiB/s, sync:0
[    fwrite]line size:    4096, lines per second:    607496, speed:   2373.03 MiB/s, sync:0

[     write]line size:    8192, lines per second:    380402, speed:   2971.89 MiB/s, sync:0
[    fwrite]line size:    8192, lines per second:    299823, speed:   2342.37 MiB/s, sync:0

[     write]line size:   16384, lines per second:    185154, speed:   2893.04 MiB/s, sync:0
[    fwrite]line size:   16384, lines per second:    162745, speed:   2542.88 MiB/s, sync:0

[     write]line size:   32768, lines per second:    110802, speed:   3462.57 MiB/s, sync:0
[    fwrite]line size:   32768, lines per second:     83786, speed:   2618.33 MiB/s, sync:0

[     write]line size:   65536, lines per second:     59577, speed:   3723.56 MiB/s, sync:0
[    fwrite]line size:   65536, lines per second:     43649, speed:   2728.07 MiB/s, sync:0

[     write]line size:  131072, lines per second:     26897, speed:   3362.18 MiB/s, sync:0
[    fwrite]line size:  131072, lines per second:     22055, speed:   2756.93 MiB/s, sync:0

[     write]line size:  262144, lines per second:     10767, speed:   2691.85 MiB/s, sync:0
[    fwrite]line size:  262144, lines per second:      9841, speed:   2460.16 MiB/s, sync:0
```

Call `fsync` (and `fflush` when using C library) after write:
```sh
./test.sh sync
```

```
[     write]line size:       8, lines per second:   2852253, speed:     21.76 MiB/s, sync:1
[    fwrite]line size:       8, lines per second:  18867924, speed:    143.95 MiB/s, sync:1

[     write]line size:      64, lines per second:   1577785, speed:     96.30 MiB/s, sync:1
[    fwrite]line size:      64, lines per second:  15290520, speed:    933.26 MiB/s, sync:1

[     write]line size:     128, lines per second:   1113710, speed:    135.95 MiB/s, sync:1
[    fwrite]line size:     128, lines per second:   9319664, speed:   1137.65 MiB/s, sync:1

[     write]line size:    1024, lines per second:    791578, speed:    773.03 MiB/s, sync:1
[    fwrite]line size:    1024, lines per second:    891981, speed:    871.08 MiB/s, sync:1

[     write]line size:    2048, lines per second:    440703, speed:    860.75 MiB/s, sync:1
[    fwrite]line size:    2048, lines per second:    637511, speed:   1245.14 MiB/s, sync:1

[     write]line size:    4096, lines per second:    346176, speed:   1352.25 MiB/s, sync:1
[    fwrite]line size:    4096, lines per second:    477281, speed:   1864.38 MiB/s, sync:1

[     write]line size:    8192, lines per second:    220138, speed:   1719.83 MiB/s, sync:1
[    fwrite]line size:    8192, lines per second:    226362, speed:   1768.45 MiB/s, sync:1

[     write]line size:   16384, lines per second:    127538, speed:   1992.78 MiB/s, sync:1
[    fwrite]line size:   16384, lines per second:    126592, speed:   1978.00 MiB/s, sync:1

[     write]line size:   32768, lines per second:     77398, speed:   2418.69 MiB/s, sync:1
[    fwrite]line size:   32768, lines per second:     62126, speed:   1941.45 MiB/s, sync:1

[     write]line size:   65536, lines per second:     39851, speed:   2490.70 MiB/s, sync:1
[    fwrite]line size:   65536, lines per second:     31132, speed:   1945.74 MiB/s, sync:1

[     write]line size:  131072, lines per second:     19975, speed:   2496.88 MiB/s, sync:1
[    fwrite]line size:  131072, lines per second:     14381, speed:   1797.62 MiB/s, sync:1

[     write]line size:  262144, lines per second:      9183, speed:   2295.68 MiB/s, sync:1
[    fwrite]line size:  262144, lines per second:      7020, speed:   1755.06 MiB/s, sync:1
```
