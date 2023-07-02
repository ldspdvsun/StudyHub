## Unixbench安装

```sh
[admin@Centos8 bench_scripts]$ git clone https://github.com/kdlucas/byte-unixbench.git
[admin@Centos8 bench_scripts]$ ll
drwxrwxr-x  4 admin admin     89 9月  28 22:45 byte-unixbench
[admin@Centos8 bench_scripts]$ cd byte-unixbench/
[admin@Centos8 byte-unixbench]$ ll
总用量 28
-rw-rw-r-- 1 admin admin 18092 9月  28 22:45 LICENSE.txt
-rw-rw-r-- 1 admin admin  6331 9月  28 22:45 README.md
drwxrwxr-x 5 admin admin   152 9月  28 22:45 UnixBench
[admin@Centos8 byte-unixbench]$ cd UnixBench/
[admin@Centos8 UnixBench]$ ll
总用量 124
-rw-rw-r-- 1 admin admin 10794 9月  28 22:45 Makefile
drwxrwxr-x 2 admin admin    91 9月  28 22:45 pgms
-rw-rw-r-- 1 admin admin 17753 9月  28 22:45 README
-rwxrwxr-x 1 admin admin 63802 9月  28 22:45 Run
drwxrwxr-x 2 admin admin   291 9月  28 22:45 src
drwxrwxr-x 2 admin admin    69 9月  28 22:45 testdir
-rw-rw-r-- 1 admin admin 18259 9月  28 22:45 USAGE
-rw-rw-r-- 1 admin admin  4622 9月  28 22:45 WRITING_TESTS

# 最新版本UnixBench5.1.3，包含system和graphic测试，如果你需要测试graphic，则需要修改Makefile,不要注释掉”GRAPHIC_TESTS = defined”，同时需要系统提供x11perf命令gl_glibs库，
# 使用下列单元格中的命令安装图形库

[admin@Centos8 UnixBench]$ vim Makefile 
[admin@Centos8 UnixBench]$ make
```

* make过程中可能会提示如下错误，可通过以下命令完成更正

```sh
# 错误1
make: gcc：命令未找到
make: *** [pgms/arithoh] 错误 127

# 错误2
gcc -o ./pgms/ubgears -DTIME -Wall -pedantic -ansi -O2 -fomit-frame-pointer -fforce-addr -ffast-math -Wall ./src/ubgears.c -lGL -lXext -lX11 -lm
./src/ubgears.c:51:19: 致命错误：GL/gl.h：没有那个文件或目录
#include <GL/gl.h>
 
# 错误3
Run: "2D graphics: rectangles": Can't exec "x11perf": No such file or directory at /tmp/soft/Unixbench/byte-unixbench-5.1.3/UnixBench/pgms/gfx-x11 line 381.
Run: exec() failed (returned); aborting

```

* 解决方法

```sh
# 1
[root@SqaServer UnixBench]# yum install -y gcc

# 2
[root@SqaServer UnixBench]# yum install -y SDL-devel mesa-libGL-devel

# 3
[root@SqaServer UnixBench]# yum install -y x11perf
```

### system测试

```sh
[admin@Centos8 UnixBench]$ ./Run
make all
make[1]: Entering directory '/opt/lx/bench_scripts/byte-unixbench/UnixBench'
make distr
make[2]: Entering directory '/opt/lx/bench_scripts/byte-unixbench/UnixBench'
Checking distribution of files
./pgms  exists
./src  exists
./testdir  exists
./tmp  exists
./results  exists
make[2]: Leaving directory '/opt/lx/bench_scripts/byte-unixbench/UnixBench'
make programs
make[2]: Entering directory '/opt/lx/bench_scripts/byte-unixbench/UnixBench'
make[2]: Nothing to be done for 'programs'.
make[2]: Leaving directory '/opt/lx/bench_scripts/byte-unixbench/UnixBench'
make[1]: Leaving directory '/opt/lx/bench_scripts/byte-unixbench/UnixBench'
sh: 3dinfo: command not found

   #    #  #    #  #  #    #          #####   ######  #    #   ####   #    #
   #    #  ##   #  #   #  #           #    #  #       ##   #  #    #  #    #
   #    #  # #  #  #    ##            #####   #####   # #  #  #       ######
   #    #  #  # #  #    ##            #    #  #       #  # #  #       #    #
   #    #  #   ##  #   #  #           #    #  #       #   ##  #    #  #    #
    ####   #    #  #  #    #          #####   ######  #    #   ####   #    #

   Version 5.1.3                      Based on the Byte Magazine Unix Benchmark

   Multi-CPU version                  Version 5 revisions by Ian Smith,
                                      Sunnyvale, CA, USA
   January 13, 2011                   johantheghost at yahoo period com

------------------------------------------------------------------------------
   Use directories for:
      * File I/O tests (named fs***) = /opt/lx/bench_scripts/byte-unixbench/UnixBench/tmp
      * Results                      = /opt/lx/bench_scripts/byte-unixbench/UnixBench/results
------------------------------------------------------------------------------

Wide character in print at ./Run line 1643.
Wide character in printf at ./Run line 1674.

1 x Dhrystone 2 using register variables  1 2 3 4 5 6 7 8 9 10

1 x Double-Precision Whetstone  1 2 3 4 5 6 7 8 9 10

1 x Execl Throughput  1 2 3

1 x File Copy 1024 bufsize 2000 maxblocks  1 2 3

1 x File Copy 256 bufsize 500 maxblocks  1 2 3

1 x File Copy 4096 bufsize 8000 maxblocks  1 2 3

1 x Pipe Throughput  1 2 3 4 5 6 7 8 9 10

1 x Pipe-based Context Switching  1 2 3 4 5 6 7 8 9 10

1 x Process Creation  1 2 3

1 x System Call Overhead  1 2 3 4 5 6 7 8 9 10

1 x Shell Scripts (1 concurrent)  1 2 3

1 x Shell Scripts (8 concurrent)  1 2 3
Wide character in printf at ./Run line 1574.

========================================================================
   BYTE UNIX Benchmarks (Version 5.1.3)

   System: Centos8: GNU/Linux
   OS: GNU/Linux -- 4.18.0-348.7.1.el8_5.x86_64 -- #1 SMP Wed Dec 22 13:25:12 UTC 2021
   Machine: x86_64 (x86_64)
   Language: en_US.utf8 (charmap="UTF-8", collate="UTF-8")
   CPU 0: Intel(R) Xeon(R) Platinum 8163 CPU @ 2.50GHz (5000.1 bogomips)
          Hyper-Threading, x86-64, MMX, Physical Address Ext, SYSENTER/SYSEXIT, SYSCALL/SYSRET
   15:52:57 up 4 days, 27 min,  3 users,  load average: 1.35, 0.51, 0.27; runlevel 2022-09-26

------------------------------------------------------------------------
Benchmark Run: 五 9月 30 2022 15:52:57 - 16:20:54
1 CPU in system; running 1 parallel copy of tests

Dhrystone 2 using register variables       30533182.3 lps   (10.0 s, 7 samples)
Double-Precision Whetstone                     5262.3 MWIPS (8.7 s, 7 samples)
Execl Throughput                               2308.0 lps   (29.8 s, 2 samples)
File Copy 1024 bufsize 2000 maxblocks        402528.4 KBps  (30.0 s, 2 samples)
File Copy 256 bufsize 500 maxblocks          105800.9 KBps  (30.0 s, 2 samples)
File Copy 4096 bufsize 8000 maxblocks       1274830.3 KBps  (30.0 s, 2 samples)
Pipe Throughput                              525172.7 lps   (10.0 s, 7 samples)
Pipe-based Context Switching                 147504.8 lps   (10.0 s, 7 samples)
Process Creation                               8027.9 lps   (30.0 s, 2 samples)
Shell Scripts (1 concurrent)                   3421.2 lpm   (60.0 s, 2 samples)
Shell Scripts (8 concurrent)                    461.3 lpm   (60.1 s, 2 samples)
System Call Overhead                         264662.3 lps   (10.0 s, 7 samples)

System Benchmarks Index Values               BASELINE       RESULT    INDEX
Dhrystone 2 using register variables         116700.0   30533182.3   2616.4
Double-Precision Whetstone                       55.0       5262.3    956.8
Execl Throughput                                 43.0       2308.0    536.7
File Copy 1024 bufsize 2000 maxblocks          3960.0     402528.4   1016.5
File Copy 256 bufsize 500 maxblocks            1655.0     105800.9    639.3
File Copy 4096 bufsize 8000 maxblocks          5800.0    1274830.3   2198.0
Pipe Throughput                               12440.0     525172.7    422.2
Pipe-based Context Switching                   4000.0     147504.8    368.8
Process Creation                                126.0       8027.9    637.1
Shell Scripts (1 concurrent)                     42.4       3421.2    806.9
Shell Scripts (8 concurrent)                      6.0        461.3    768.9
System Call Overhead                          15000.0     264662.3    176.4
                                                                   ========
System Benchmarks Index Score                                         724.3

[admin@Centos8 UnixBench]$ 

```

>https://blog.csdn.net/xzm_0602/article/details/109736916



### graphics测试
 
```sh
 # 最新版本UnixBench5.1.3，包含system和graphic测试，如果你需要测试graphic，则需要修改Makefile,不要注释掉”GRAPHIC_TESTS = defined”，同时需要系统提供x11perf命令gl_glibs库，
# 使用以下命令安装图形库
yum -y install gcc automake autoconf libtool make 
yum install perl-Time-HiRes –y 
yum install mesa* -y 
yum install glut –y
yum install –y xorg-x11*
 ```
 

 ```sh
[root@centos7 soft]# cd byte-unixbench-5.1.3/UnixBench/
[root@centos7 UnixBench]# make all
[root@centos7 UnixBench]# ./Run graphics
make all
make[1]: Entering directory `/tmp/soft/byte-unixbench-5.1.3/UnixBench'
Checking distribution of files
./pgms  exists
./src  exists
./testdir  exists
./tmp  exists
./results  exists
make[1]: Leaving directory `/tmp/soft/byte-unixbench-5.1.3/UnixBench'
sh: 3dinfo: command not found

   #    #  #    #  #  #    #          #####   ######  #    #   ####   #    #
   #    #  ##   #  #   #  #           #    #  #       ##   #  #    #  #    #
   #    #  # #  #  #    ##            #####   #####   # #  #  #       ######
   #    #  #  # #  #    ##            #    #  #       #  # #  #       #    #
   #    #  #   ##  #   #  #           #    #  #       #   ##  #    #  #    #
    ####   #    #  #  #    #          #####   ######  #    #   ####   #    #

   Version 5.1.3                      Based on the Byte Magazine Unix Benchmark

   Multi-CPU version                  Version 5 revisions by Ian Smith,
                                      Sunnyvale, CA, USA
   January 13, 2011                   johantheghost at yahoo period com


1 x 2D graphics: rectangles  1 2 3

1 x 2D graphics: ellipses  1 2 3

1 x 2D graphics: aa polygons  1 2 3

```

### 3D测试

```sh
[root@SqaServer UnixBench]# ./Run ubgears
make all
make[1]: Entering directory `/tmp/soft/unixbench/byte-unixbench-5.1.3/UnixBench'
Checking distribution of files
./pgms  exists
./src  exists
./testdir  exists
./tmp  exists
./results  exists
make[1]: Leaving directory `/tmp/soft/unixbench/byte-unixbench-5.1.3/UnixBench'
sh: 3dinfo: command not found

   #    #  #    #  #  #    #          #####   ######  #    #   ####   #    #
   #    #  ##   #  #   #  #           #    #  #       ##   #  #    #  #    #
   #    #  # #  #  #    ##            #####   #####   # #  #  #       ######
   #    #  #  # #  #    ##            #    #  #       #  # #  #       #    #
   #    #  #   ##  #   #  #           #    #  #       #   ##  #    #  #    #
    ####   #    #  #  #    #          #####   ######  #    #   ####   #    #

   Version 5.1.3                      Based on the Byte Magazine Unix Benchmark

   Multi-CPU version                  Version 5 revisions by Ian Smith,
                                      Sunnyvale, CA, USA
   January 13, 2011                   johantheghost at yahoo period com


1 x 3D graphics: gears  1 2 3

========================================================================
   BYTE UNIX Benchmarks (Version 5.1.3)

   System: SqaServer: GNU/Linux
   OS: GNU/Linux -- 3.10.0-1160.71.1.el7.x86_64 -- #1 SMP Tue Jun 28 15:37:28 UTC 2022
   Machine: x86_64 (x86_64)
   Language: en_US.utf8 (charmap="UTF-8", collate="UTF-8")
   CPU 0: 12th Gen Intel(R) Core(TM) i7-12700 (4223.9 bogomips)
          Hyper-Threading, x86-64, MMX, Physical Address Ext, SYSENTER/SYSEXIT, SYSCALL/SYSRET
   CPU 1: 12th Gen Intel(R) Core(TM) i7-12700 (4223.9 bogomips)
          Hyper-Threading, x86-64, MMX, Physical Address Ext, SYSENTER/SYSEXIT, SYSCALL/SYSRET
   CPU 2: 12th Gen Intel(R) Core(TM) i7-12700 (4223.9 bogomips)
          Hyper-Threading, x86-64, MMX, Physical Address Ext, SYSENTER/SYSEXIT, SYSCALL/SYSRET
   CPU 3: 12th Gen Intel(R) Core(TM) i7-12700 (4223.9 bogomips)
          Hyper-Threading, x86-64, MMX, Physical Address Ext, SYSENTER/SYSEXIT, SYSCALL/SYSRET
   14:03:11 up  8:58,  2 users,  load average: 0.22, 0.20, 0.15; runlevel 5

------------------------------------------------------------------------
Benchmark Run: 一 11月 21 2022 14:03:11 - 14:04:35
4 CPUs in system; running 1 parallel copy of tests

3D graphics: gears                              114.5 fps   (20.2 s, 2 samples)

3D Graphics Benchmarks Index Values          BASELINE       RESULT    INDEX
3D graphics: gears                               33.4        114.5     34.3
                                                                   ========
3D Graphics Benchmarks Index Score                                     34.3

------------------------------------------------------------------------
Benchmark Run: 一 11月 21 2022 14:04:35 - 14:04:35
4 CPUs in system; running 4 parallel copies of tests

[root@SqaServer UnixBench]#
```


### Centos安装X11perf工具

```sh
#tar -xvf x11perf-1.5.tar.gz
1）解压x11perf-1.5.tar.gz，
2）安装：#cd x11perf-1.5

[root@centos7 x11perf-1.6.1]# ./configure --build=x86_64-linux（我的机器是X86架构的）

[root@centos7 x11perf-1.6.1]# make
# make过程中有warning，不用管
[root@centos7 x11perf-1.6.1]# make install
执行完后回到UnixBench下执行./Run graphics测试
```

## 参考链接

>https://www.x.org/archive/individual/app/x11perf-1.6.1.tar.gz