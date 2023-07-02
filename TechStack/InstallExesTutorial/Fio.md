## 下载安装

```sh
[root@Centos8 lx]# pwd
/opt/lx
1.下载
[root@Centos8 lx]# wget https://git.kernel.dk/cgit/fio/snapshot/fio-3.32.tar.gz
[root@Centos8 lx]# ll
总用量 307932
-rw-r--r--  1 root  root    6182071 9月  30 10:36 fio-3.32.tar.gz
2.解压缩
[root@Centos8 lx]# tar -zxvf fio-3.32.tar.gz 
[root@Centos8 lx]# ll
总用量 307940
drwxrwxr-x 18 root  root       4096 8月  31 00:51 fio-3.32
[root@Centos8 lx]# cd fio-3.32/
[root@Centos8 fio-3.32]# ls
arch                  doc              gclient.h         init.c         oslib           STEADYSTATE-TODO
backend.c             engines          gcompat.c         io_ddir.h      parse.c         t
blktrace_api.h        err.h            gcompat.h         ioengines.c    parse.h         td_error.c
blktrace.c            eta.c            gerror.c          ioengines.h    printing.c      td_error.h
blktrace.h            examples         gerror.h          iolog.c        printing.h      thread_options.h
cairo_text_helpers.c  exp              gettime.c         iolog.h        profile.c       tickmarks.c
cairo_text_helpers.h  fifo.c           gettime.h         io_u.c         profile.h       tickmarks.h
cconv.c               fifo.h           gettime-thread.c  io_u.h         profiles        time.c
cgroup.c              file.h           gfio.c            io_u_queue.c   pshared.c       tools
cgroup.h              filehash.c       gfio.h            io_u_queue.h   pshared.h       trim.c
ci                    filehash.h       GFIO-TODO         json.c         rate-submit.c   trim.h
CITATION.cff          filelock.c       ghelpers.c        json.h         rate-submit.h   unittests
client.c              filelock.h       ghelpers.h        lib            README.rst      verify.c
client.h              filesetup.c      goptions.c        libfio.c       REPORTING-BUGS  verify.h
compiler              fio.1            goptions.h        log.c          rwlock.c        verify-state.h
configure             fio.c            graph.c           log.h          rwlock.h        workqueue.c
COPYING               fio.h            graph.h           Makefile       server.c        workqueue.h
crc                   fio_sem.c        hash.h            memory.c       server.h        zbd.c
debug.c               fio_sem.h        helpers.c         minmax.h       SERVER-TODO     zbd.h
debug.h               fio_time.h       helpers.h         MORAL-LICENSE  smalloc.c       zbd_types.h
dedupe.c              FIO-VERSION-GEN  helper_thread.c   optgroup.c     smalloc.h       zone-dist.c
dedupe.h              flist.h          helper_thread.h   optgroup.h     stat.c          zone-dist.h
DEDUPE-TODO           flow.c           HOWTO.rst         options.c      stat.h
diskutil.c            flow.h           idletime.c        options.h      steadystate.c
diskutil.h            gclient.c        idletime.h        os             steadystate.h
[root@Centos8 fio-3.32]# ./configure 
[root@Centos8 fio-3.32]# make
[root@Centos8 fio-3.32]# make install
[root@Centos8 fio-3.32]# ls
arch                  diskutil.h        flow.h            ioengines.c    os              steadystate.h
backend.c             diskutil.o        flow.o            ioengines.d    oslib           steadystate.o
backend.d             doc               gclient.c         ioengines.h    parse.c         STEADYSTATE-TODO
backend.o             engines           gclient.h         ioengines.o    parse.d         t
blktrace_api.h        err.h             gcompat.c         iolog.c        parse.h         td_error.c
blktrace.c            eta.c             gcompat.h         iolog.d        parse.o         td_error.d
blktrace.d            eta.d             gerror.c          iolog.h        printing.c      td_error.h
blktrace.h            eta.o             gerror.h          iolog.o        printing.h      td_error.o
blktrace.o            examples          gettime.c         io_u.c         profile.c       thread_options.h
cairo_text_helpers.c  exp               gettime.d         io_u.d         profile.d       tickmarks.c
cairo_text_helpers.h  fifo.c            gettime.h         io_u.h         profile.h       tickmarks.h
cconv.c               fifo.d            gettime.o         io_u.o         profile.o       time.c
cconv.d               fifo.h            gettime-thread.c  io_u_queue.c   profiles        time.d
cconv.o               fifo.o            gettime-thread.d  io_u_queue.d   pshared.c       time.o
cgroup.c              file.h            gettime-thread.o  io_u_queue.h   pshared.d       tools
cgroup.d              filehash.c        gfio.c            io_u_queue.o   pshared.h       trim.c
cgroup.h              filehash.d        gfio.h            json.c         pshared.o       trim.d
cgroup.o              filehash.h        GFIO-TODO         json.d         rate-submit.c   trim.h
ci                    filehash.o        ghelpers.c        json.h         rate-submit.d   trim.o
CITATION.cff          filelock.c        ghelpers.h        json.o         rate-submit.h   unittests
client.c              filelock.d        goptions.c        lib            rate-submit.o   verify.c
client.d              filelock.h        goptions.h        libfio.c       README.rst      verify.d
client.h              filelock.o        graph.c           libfio.d       REPORTING-BUGS  verify.h
client.o              filesetup.c       graph.h           libfio.o       rwlock.c        verify.o
compiler              filesetup.d       hash.h            log.c          rwlock.d        verify-state.h
config-host.h         filesetup.o       helpers.c         log.d          rwlock.h        workqueue.c
config-host.mak       fio               helpers.d         log.h          rwlock.o        workqueue.d
config.log            fio.1             helpers.h         log.o          server.c        workqueue.h
configure             fio.c             helpers.o         Makefile       server.d        workqueue.o
COPYING               fio.d             helper_thread.c   memory.c       server.h        zbd.c
crc                   fio.h             helper_thread.d   memory.d       server.o        zbd.d
debug.c               fio.o             helper_thread.h   memory.o       SERVER-TODO     zbd.h
debug.d               fio_sem.c         helper_thread.o   minmax.h       smalloc.c       zbd.o
debug.h               fio_sem.d         HOWTO.rst         MORAL-LICENSE  smalloc.d       zbd_types.h
debug.o               fio_sem.h         idletime.c        optgroup.c     smalloc.h       zone-dist.c
dedupe.c              fio_sem.o         idletime.d        optgroup.d     smalloc.o       zone-dist.d
dedupe.d              fio_time.h        idletime.h        optgroup.h     stat.c          zone-dist.h
dedupe.h              FIO-VERSION-FILE  idletime.o        optgroup.o     stat.d          zone-dist.o
dedupe.o              FIO-VERSION-GEN   init.c            options.c      stat.h
DEDUPE-TODO           flist.h           init.d            options.d      stat.o
diskutil.c            flow.c            init.o            options.h      steadystate.c
diskutil.d            flow.d            io_ddir.h         options.o      steadystate.d
[root@Centos8 fio-3.32]# 
[root@Centos8 fio-3.32]# fio --version
fio-3.32
[root@Centos8 fio-3.32]# 


```

## FIO测试
### 参数

```sh
-filename=/dev/sdb1       测试文件名称，通常选择需要测试的盘的data目录。 只能是分区，不能是目录，会破坏数据
-direct=1                 测试过程绕过机器自带的buffer。使测试结果更真实。
-rw=randrw                测试随机写和读的I/O
-rw=rw/readwrite          测试顺序读写的I/O
-rw=read                  顺序读
-rw=write                 顺序写
-rw=randread              随机读
-rw=randwrite             随机写
-iodepth=1                队列深度，只有使用libaio时才有意义，这是一个可以影响IOPS的参数，通常情况下为1。
-ioengine=psync/libaio    io引擎使用pync方式
-bs=4k                    单次io的块文件大小为4k (单次IO越小的时候，单次IO所耗费的时间也越少，相应的IOPS也就越大)
-size=2G                  测试文件大小为2g，以每次4k的io进行测试,此大小不能超过filename的大小，否则会报错。
-numjobs=10               测试线程为10.
-runtime=10               测试时间为10秒，如果不写则一直将2g文件分4k每次写完为止。
-lockmem=1g               只使用1g内存进行测试。
-rwmixwrite=30            在混合读写的模式下，写占30% 
-group_reporting          关于显示结果的，汇总每个进程的信息。
-name=name                直接测试读会在测试设备写入name.*文件
-output=rw.txt            将输出内容写入文件
```

### 顺序读

```sh
[root@Centos8 fio-3.32]# fio -fimename=/dev/sdc1 -direct=1 -rw=read -iodepth=1 -ioengine=psync -bs=4k -size=2G -numjobs=1 -runtime=10 -group_reporting -name=name
name: (g=0): rw=read, bs=(R) 4096B-4096B, (W) 4096B-4096B, (T) 4096B-4096B, ioengine=psync, iodepth=1
fio-3.32
Starting 1 process
name: Laying out IO file (1 file / 2048MiB)
3;fio-3.32;name;0;0;132160;13209;3302;10005;0;0;0.000000;0.000000;105;30823;301.964763;973.421730;1.000000%=110;5.000000%=113;10.000000%=115;20.000000%=118;30.000000%=120;40.000000%=122;50.000000%=124;60.000000%=127;70.000000%=132;80.000000%=140;90.000000%=166;95.000000%=236;99.000000%=6455;99.500000%=6520;99.900000%=7700;99.950000%=8585;99.990000%=10944;0%=0;0%=0;0%=0;105;30823;302.054914;973.424289;9732;26864;99.570070%;13152.210526;4290.142507;0;0;0;0;0;0;0.000000;0.000000;0;0;0.000000;0.000000;1.000000%=0;5.000000%=0;10.000000%=0;20.000000%=0;30.000000%=0;40.000000%=0;50.000000%=0;60.000000%=0;70.000000%=0;80.000000%=0;90.000000%=0;95.000000%=0;99.000000%=0;99.500000%=0;99.900000%=0;99.950000%=0;99.990000%=0;0%=0;0%=0;0%=0;0;0;0.000000;0.000000;0;0;0.000000%;0.000000;0.000000;0.479808%;3.028788%;33040;0;13;100.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;95.13%;0.90%;0.41%;0.21%;0.32%;0.58%;2.43%;0.02%;0.01%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;vda;32948;3;0;0;11703;18;11720;93.61%

name: (groupid=0, jobs=1): err= 0: pid=1302977: Fri Sep 30 11:41:06 2022
  read: IOPS=3302, BW=12.9MiB/s (13.5MB/s)(129MiB/10005msec)
    clat (usec): min=105, max=30823, avg=301.96, stdev=973.42
     lat (usec): min=105, max=30823, avg=302.05, stdev=973.42
    clat percentiles (usec):
     |  1.00th=[  111],  5.00th=[  114], 10.00th=[  116], 20.00th=[  119],
     | 30.00th=[  121], 40.00th=[  123], 50.00th=[  125], 60.00th=[  128],
     | 70.00th=[  133], 80.00th=[  141], 90.00th=[  167], 95.00th=[  237],
     | 99.00th=[ 6456], 99.50th=[ 6521], 99.90th=[ 7701], 99.95th=[ 8586],
     | 99.99th=[10945]
   bw (  KiB/s): min= 9732, max=26864, per=99.57%, avg=13152.21, stdev=4290.14, samples=19
   iops        : min= 2433, max= 6716, avg=3288.00, stdev=1072.56, samples=19
  lat (usec)   : 250=95.13%, 500=0.90%, 750=0.41%, 1000=0.21%
  lat (msec)   : 2=0.32%, 4=0.58%, 10=2.43%, 20=0.02%, 50=0.01%
  cpu          : usr=0.48%, sys=3.03%, ctx=33040, majf=0, minf=13
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued rwts: total=33040,0,0,0 short=0,0,0,0 dropped=0,0,0,0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: bw=12.9MiB/s (13.5MB/s), 12.9MiB/s-12.9MiB/s (13.5MB/s-13.5MB/s), io=129MiB (135MB), run=10005-10005msec

Disk stats (read/write):
  vda: ios=32948/3, merge=0/0, ticks=11703/18, in_queue=11720, util=93.61%
[root@Centos8 fio-3.32]# 
[root@Centos8 fio-3.32]# 
```

### 顺序写

```sh
[root@Centos8 fio-3.32]# fio -fimename=/dev/sdc1 -direct=1 -rw=write -iodepth=1 -ioengine=psync -bs=4k -size=2G -numjobs=1 -runtime=10 -group_reporting -name=name
name: (g=0): rw=write, bs=(R) 4096B-4096B, (W) 4096B-4096B, (T) 4096B-4096B, ioengine=psync, iodepth=1
fio-3.32
Starting 1 process
3;fio-3.32;name;0;0;0;0;0;0;0;0;0.000000;0.000000;0;0;0.000000;0.000000;1.000000%=0;5.000000%=0;10.000000%=0;20.000000%=0;30.000000%=0;40.000000%=0;50.000000%=0;60.000000%=0;70.000000%=0;80.000000%=0;90.000000%=0;95.000000%=0;99.000000%=0;99.500000%=0;99.900000%=0;99.950000%=0;99.990000%=0;0%=0;0%=0;0%=0;0;0;0.000000;0.000000;0;0;0.000000%;0.000000;0.000000;134036;13402;3350;10001;0;0;0.000000;0.000000;139;20761;297.476504;755.833998;1.000000%=146;5.000000%=148;10.000000%=150;20.000000%=154;30.000000%=156;40.000000%=160;50.000000%=164;60.000000%=168;70.000000%=177;80.000000%=185;90.000000%=201;95.000000%=268;99.000000%=5079;99.500000%=5472;99.900000%=6586;99.950000%=8355;99.990000%=10682;0%=0;0%=0;0%=0;139;20761;297.621334;755.840060;10786;20912;100.000000%;13490.947368;3024.208427;0.700000%;3.120000%;33509;0;12;100.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;94.51%;1.66%;0.50%;0.30%;0.36%;0.82%;1.82%;0.01%;0.01%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;vda;40;33240;0;0;76;8686;8762;93.18%

name: (groupid=0, jobs=1): err= 0: pid=1304816: Fri Sep 30 11:45:19 2022
  write: IOPS=3350, BW=13.1MiB/s (13.7MB/s)(131MiB/10001msec); 0 zone resets
    clat (usec): min=139, max=20761, avg=297.48, stdev=755.83
     lat (usec): min=139, max=20761, avg=297.62, stdev=755.84
    clat percentiles (usec):
     |  1.00th=[  147],  5.00th=[  149], 10.00th=[  151], 20.00th=[  155],
     | 30.00th=[  157], 40.00th=[  161], 50.00th=[  165], 60.00th=[  169],
     | 70.00th=[  178], 80.00th=[  186], 90.00th=[  202], 95.00th=[  269],
     | 99.00th=[ 5080], 99.50th=[ 5473], 99.90th=[ 6587], 99.95th=[ 8356],
     | 99.99th=[10683]
   bw (  KiB/s): min=10786, max=20912, per=100.00%, avg=13490.95, stdev=3024.21, samples=19
   iops        : min= 2696, max= 5228, avg=3372.68, stdev=756.08, samples=19
  lat (usec)   : 250=94.51%, 500=1.66%, 750=0.50%, 1000=0.30%
  lat (msec)   : 2=0.36%, 4=0.82%, 10=1.82%, 20=0.01%, 50=0.01%
  cpu          : usr=0.70%, sys=3.12%, ctx=33509, majf=0, minf=12
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued rwts: total=0,33509,0,0 short=0,0,0,0 dropped=0,0,0,0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
  WRITE: bw=13.1MiB/s (13.7MB/s), 13.1MiB/s-13.1MiB/s (13.7MB/s-13.7MB/s), io=131MiB (137MB), run=10001-10001msec

Disk stats (read/write):
  vda: ios=40/33240, merge=0/0, ticks=76/8686, in_queue=8762, util=93.18%
[root@Centos8 fio-3.32]# 
[root@Centos8 fio-3.32]# 
```

### 随机读

```sh
[root@Centos8 fio-3.32]# fio -fimename=/dev/sdc1 -direct=1 -rw=randread -iodepth=1 -ioengine=psync -bs=4k -size=2G -numjobs=1 -runtime=10 -group_reporting -name=name
name: (g=0): rw=randread, bs=(R) 4096B-4096B, (W) 4096B-4096B, (T) 4096B-4096B, ioengine=psync, iodepth=1
fio-3.32
Starting 1 process
3;fio-3.32;name;0;0;133532;13351;3337;10001;0;0;0.000000;0.000000;189;14700;298.421947;348.277458;1.000000%=205;5.000000%=214;10.000000%=220;20.000000%=228;30.000000%=234;40.000000%=244;50.000000%=254;60.000000%=264;70.000000%=272;80.000000%=284;90.000000%=313;95.000000%=350;99.000000%=1351;99.500000%=2998;99.900000%=4947;99.950000%=5734;99.990000%=8585;0%=0;0%=0;0%=0;189;14700;298.527259;348.284972;9536;15608;99.468205%;13280.000000;1775.100874;0;0;0;0;0;0;0.000000;0.000000;0;0;0.000000;0.000000;1.000000%=0;5.000000%=0;10.000000%=0;20.000000%=0;30.000000%=0;40.000000%=0;50.000000%=0;60.000000%=0;70.000000%=0;80.000000%=0;90.000000%=0;95.000000%=0;99.000000%=0;99.500000%=0;99.900000%=0;99.950000%=0;99.990000%=0;0%=0;0%=0;0%=0;0;0;0.000000;0.000000;0;0;0.000000%;0.000000;0.000000;0.650000%;3.130000%;33383;0;10;100.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;45.23%;51.86%;1.04%;0.61%;0.48%;0.57%;0.22%;0.01%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;vda;33035;0;0;0;8597;0;8597;92.61%

name: (groupid=0, jobs=1): err= 0: pid=1305109: Fri Sep 30 11:45:59 2022
  read: IOPS=3337, BW=13.0MiB/s (13.7MB/s)(130MiB/10001msec)
    clat (usec): min=189, max=14700, avg=298.42, stdev=348.28
     lat (usec): min=189, max=14700, avg=298.53, stdev=348.28
    clat percentiles (usec):
     |  1.00th=[  206],  5.00th=[  215], 10.00th=[  221], 20.00th=[  229],
     | 30.00th=[  235], 40.00th=[  245], 50.00th=[  255], 60.00th=[  265],
     | 70.00th=[  273], 80.00th=[  285], 90.00th=[  314], 95.00th=[  351],
     | 99.00th=[ 1352], 99.50th=[ 2999], 99.90th=[ 4948], 99.95th=[ 5735],
     | 99.99th=[ 8586]
   bw (  KiB/s): min= 9536, max=15608, per=99.46%, avg=13280.00, stdev=1775.10, samples=19
   iops        : min= 2384, max= 3902, avg=3320.00, stdev=443.78, samples=19
  lat (usec)   : 250=45.23%, 500=51.86%, 750=1.04%, 1000=0.61%
  lat (msec)   : 2=0.48%, 4=0.57%, 10=0.22%, 20=0.01%
  cpu          : usr=0.65%, sys=3.13%, ctx=33383, majf=0, minf=10
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued rwts: total=33383,0,0,0 short=0,0,0,0 dropped=0,0,0,0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: bw=13.0MiB/s (13.7MB/s), 13.0MiB/s-13.0MiB/s (13.7MB/s-13.7MB/s), io=130MiB (137MB), run=10001-10001msec

Disk stats (read/write):
  vda: ios=33035/0, merge=0/0, ticks=8597/0, in_queue=8597, util=92.61%
[root@Centos8 fio-3.32]# 
[root@Centos8 fio-3.32]# 
```

### 随机写

```sh
[root@Centos8 fio-3.32]# fio -fimename=/dev/sdc1 -direct=1 -rw=randwrite -iodepth=1 -ioengine=psync -bs=4k -size=2G -numjobs=1 -runtime=10 -group_reporting -name=name
name: (g=0): rw=randwrite, bs=(R) 4096B-4096B, (W) 4096B-4096B, (T) 4096B-4096B, ioengine=psync, iodepth=1
fio-3.32
Starting 1 process
3;fio-3.32;name;0;0;0;0;0;0;0;0;0.000000;0.000000;0;0;0.000000;0.000000;1.000000%=0;5.000000%=0;10.000000%=0;20.000000%=0;30.000000%=0;40.000000%=0;50.000000%=0;60.000000%=0;70.000000%=0;80.000000%=0;90.000000%=0;95.000000%=0;99.000000%=0;99.500000%=0;99.900000%=0;99.950000%=0;99.990000%=0;0%=0;0%=0;0%=0;0;0;0.000000;0.000000;0;0;0.000000%;0.000000;0.000000;134196;13418;3354;10001;0;0;0.000000;0.000000;141;12568;296.852976;718.281384;1.000000%=148;5.000000%=150;10.000000%=154;20.000000%=158;30.000000%=160;40.000000%=164;50.000000%=168;60.000000%=175;70.000000%=181;80.000000%=189;90.000000%=209;95.000000%=284;99.000000%=4751;99.500000%=5472;99.900000%=6848;99.950000%=7700;99.990000%=10682;0%=0;0%=0;0%=0;141;12568;297.003431;718.287242;11224;20224;100.000000%;13453.894737;2598.393818;0.670000%;3.360000%;33549;0;11;100.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;94.15%;1.93%;0.47%;0.40%;0.38%;1.14%;1.52%;0.01%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;vda;24;33267;0;1;57;8488;8546;91.95%

name: (groupid=0, jobs=1): err= 0: pid=1305264: Fri Sep 30 11:46:20 2022
  write: IOPS=3354, BW=13.1MiB/s (13.7MB/s)(131MiB/10001msec); 0 zone resets
    clat (usec): min=141, max=12568, avg=296.85, stdev=718.28
     lat (usec): min=141, max=12568, avg=297.00, stdev=718.29
    clat percentiles (usec):
     |  1.00th=[  149],  5.00th=[  151], 10.00th=[  155], 20.00th=[  159],
     | 30.00th=[  161], 40.00th=[  165], 50.00th=[  169], 60.00th=[  176],
     | 70.00th=[  182], 80.00th=[  190], 90.00th=[  210], 95.00th=[  285],
     | 99.00th=[ 4752], 99.50th=[ 5473], 99.90th=[ 6849], 99.95th=[ 7701],
     | 99.99th=[10683]
   bw (  KiB/s): min=11224, max=20224, per=100.00%, avg=13453.89, stdev=2598.39, samples=19
   iops        : min= 2806, max= 5056, avg=3363.47, stdev=649.60, samples=19
  lat (usec)   : 250=94.15%, 500=1.93%, 750=0.47%, 1000=0.40%
  lat (msec)   : 2=0.38%, 4=1.14%, 10=1.52%, 20=0.01%
  cpu          : usr=0.67%, sys=3.36%, ctx=33549, majf=0, minf=11
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued rwts: total=0,33549,0,0 short=0,0,0,0 dropped=0,0,0,0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
  WRITE: bw=13.1MiB/s (13.7MB/s), 13.1MiB/s-13.1MiB/s (13.7MB/s-13.7MB/s), io=131MiB (137MB), run=10001-10001msec

Disk stats (read/write):
  vda: ios=24/33267, merge=0/1, ticks=57/8488, in_queue=8546, util=91.95%
[root@Centos8 fio-3.32]# 
[root@Centos8 fio-3.32]# 
```

### 混合顺序读写

```sh
[root@Centos8 fio-3.32]# fio -fimename=/dev/sdc1 -direct=1 -rw=rw -iodepth=1 -ioengine=psync -bs=4k -size=2G -numjobs=1 -runtime=10 -group_reporting -name=name
name: (g=0): rw=rw, bs=(R) 4096B-4096B, (W) 4096B-4096B, (T) 4096B-4096B, ioengine=psync, iodepth=1
fio-3.32
Starting 1 process
3;fio-3.32;name;0;0;65592;6558;1639;10001;0;0;0.000000;0.000000;104;10993;347.669977;795.991522;1.000000%=109;5.000000%=114;10.000000%=117;20.000000%=120;30.000000%=124;40.000000%=127;50.000000%=132;60.000000%=140;70.000000%=164;80.000000%=199;90.000000%=333;95.000000%=2023;99.000000%=4227;99.500000%=5472;99.900000%=6651;99.950000%=7372;99.990000%=9502;0%=0;0%=0;0%=0;104;10993;347.776933;795.998578;3472;11912;100.000000%;6618.947368;2283.989041;65572;6556;1639;10001;0;0;0.000000;0.000000;139;12143;260.127496;626.014086;1.000000%=144;5.000000%=148;10.000000%=152;20.000000%=156;30.000000%=158;40.000000%=162;50.000000%=166;60.000000%=173;70.000000%=181;80.000000%=189;90.000000%=207;95.000000%=257;99.000000%=4079;99.500000%=5472;99.900000%=6979;99.950000%=8585;99.990000%=11337;0%=0;0%=0;0%=0;140;12143;260.289793;626.018167;3744;12136;100.000000%;6594.052632;2297.365653;0.650000%;3.420000%;32791;0;15;100.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;90.51%;3.88%;0.67%;1.02%;0.55%;2.27%;1.08%;0.01%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;vda;16314;16279;0;0;5087;3625;8711;93.07%

name: (groupid=0, jobs=1): err= 0: pid=1305489: Fri Sep 30 11:46:50 2022
  read: IOPS=1639, BW=6559KiB/s (6716kB/s)(64.1MiB/10001msec)
    clat (usec): min=104, max=10993, avg=347.67, stdev=795.99
     lat (usec): min=104, max=10993, avg=347.78, stdev=796.00
    clat percentiles (usec):
     |  1.00th=[  110],  5.00th=[  115], 10.00th=[  118], 20.00th=[  121],
     | 30.00th=[  125], 40.00th=[  128], 50.00th=[  133], 60.00th=[  141],
     | 70.00th=[  165], 80.00th=[  200], 90.00th=[  334], 95.00th=[ 2024],
     | 99.00th=[ 4228], 99.50th=[ 5473], 99.90th=[ 6652], 99.95th=[ 7373],
     | 99.99th=[ 9503]
   bw (  KiB/s): min= 3472, max=11912, per=100.00%, avg=6618.95, stdev=2283.99, samples=19
   iops        : min=  868, max= 2978, avg=1654.74, stdev=571.00, samples=19
  write: IOPS=1639, BW=6557KiB/s (6714kB/s)(64.0MiB/10001msec); 0 zone resets
    clat (usec): min=139, max=12143, avg=260.13, stdev=626.01
     lat (usec): min=140, max=12143, avg=260.29, stdev=626.02
    clat percentiles (usec):
     |  1.00th=[  145],  5.00th=[  149], 10.00th=[  153], 20.00th=[  157],
     | 30.00th=[  159], 40.00th=[  163], 50.00th=[  167], 60.00th=[  174],
     | 70.00th=[  182], 80.00th=[  190], 90.00th=[  208], 95.00th=[  258],
     | 99.00th=[ 4080], 99.50th=[ 5473], 99.90th=[ 6980], 99.95th=[ 8586],
     | 99.99th=[11338]
   bw (  KiB/s): min= 3744, max=12136, per=100.00%, avg=6594.05, stdev=2297.37, samples=19
   iops        : min=  936, max= 3034, avg=1648.47, stdev=574.39, samples=19
  lat (usec)   : 250=90.51%, 500=3.88%, 750=0.67%, 1000=1.02%
  lat (msec)   : 2=0.55%, 4=2.27%, 10=1.08%, 20=0.01%
  cpu          : usr=0.65%, sys=3.42%, ctx=32791, majf=0, minf=15
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued rwts: total=16398,16393,0,0 short=0,0,0,0 dropped=0,0,0,0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: bw=6559KiB/s (6716kB/s), 6559KiB/s-6559KiB/s (6716kB/s-6716kB/s), io=64.1MiB (67.2MB), run=10001-10001msec
  WRITE: bw=6557KiB/s (6714kB/s), 6557KiB/s-6557KiB/s (6714kB/s-6714kB/s), io=64.0MiB (67.1MB), run=10001-10001msec

Disk stats (read/write):
  vda: ios=16314/16279, merge=0/0, ticks=5087/3625, in_queue=8711, util=93.07%
[root@Centos8 fio-3.32]# 
```

### 混合随机读写

```sh
[root@Centos8 fio-3.32]# fio -fimename=/dev/sdc1 -direct=1 -rw=randrw -iodepth=1 -ioengine=psync -bs=4k -size=2G -numjobs=1 -runtime=10 -group_reporting -name=name
name: (g=0): rw=randrw, bs=(R) 4096B-4096B, (W) 4096B-4096B, (T) 4096B-4096B, ioengine=psync, iodepth=1
fio-3.32
Starting 1 process
3;fio-3.32;name;0;0;67084;6707;1676;10001;0;0;0.000000;0.000000;184;11595;338.259882;502.670713;1.000000%=209;5.000000%=216;10.000000%=222;20.000000%=230;30.000000%=236;40.000000%=244;50.000000%=257;60.000000%=268;70.000000%=272;80.000000%=284;90.000000%=313;95.000000%=415;99.000000%=3424;99.500000%=4292;99.900000%=5210;99.950000%=5799;99.990000%=8716;0%=0;0%=0;0%=0;184;11595;338.352392;502.677982;4864;8712;100.000000%;6748.631579;1116.102156;67080;6707;1676;10001;0;0;0.000000;0.000000;147;9523;255.826808;510.299103;1.000000%=152;5.000000%=156;10.000000%=160;20.000000%=162;30.000000%=166;40.000000%=171;50.000000%=173;60.000000%=177;70.000000%=183;80.000000%=191;90.000000%=207;95.000000%=257;99.000000%=3358;99.500000%=4112;99.900000%=5931;99.950000%=7241;99.990000%=8224;0%=0;0%=0;0%=0;148;9523;255.970946;510.303799;4760;8888;100.000000%;6727.578947;1176.439748;0.650000%;3.220000%;33542;0;11;100.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.0%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;69.55%;26.73%;0.86%;0.43%;0.47%;1.36%;0.60%;0.01%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;0.00%;vda;16626;16627;0;0;5066;3686;8753;93.53%

name: (groupid=0, jobs=1): err= 0: pid=1347755: Fri Sep 30 13:24:41 2022
  read: IOPS=1676, BW=6708KiB/s (6869kB/s)(65.5MiB/10001msec)
    clat (usec): min=184, max=11595, avg=338.26, stdev=502.67
     lat (usec): min=184, max=11595, avg=338.35, stdev=502.68
    clat percentiles (usec):
     |  1.00th=[  210],  5.00th=[  217], 10.00th=[  223], 20.00th=[  231],
     | 30.00th=[  237], 40.00th=[  245], 50.00th=[  258], 60.00th=[  269],
     | 70.00th=[  273], 80.00th=[  285], 90.00th=[  314], 95.00th=[  416],
     | 99.00th=[ 3425], 99.50th=[ 4293], 99.90th=[ 5211], 99.95th=[ 5800],
     | 99.99th=[ 8717]
   bw (  KiB/s): min= 4864, max= 8712, per=100.00%, avg=6748.63, stdev=1116.10, samples=19
   iops        : min= 1216, max= 2178, avg=1687.16, stdev=279.03, samples=19
  write: IOPS=1676, BW=6707KiB/s (6868kB/s)(65.5MiB/10001msec); 0 zone resets
    clat (usec): min=147, max=9523, avg=255.83, stdev=510.30
     lat (usec): min=148, max=9523, avg=255.97, stdev=510.30
    clat percentiles (usec):
     |  1.00th=[  153],  5.00th=[  157], 10.00th=[  161], 20.00th=[  163],
     | 30.00th=[  167], 40.00th=[  172], 50.00th=[  174], 60.00th=[  178],
     | 70.00th=[  184], 80.00th=[  192], 90.00th=[  208], 95.00th=[  258],
     | 99.00th=[ 3359], 99.50th=[ 4113], 99.90th=[ 5932], 99.95th=[ 7242],
     | 99.99th=[ 8225]
   bw (  KiB/s): min= 4760, max= 8888, per=100.00%, avg=6727.58, stdev=1176.44, samples=19
   iops        : min= 1190, max= 2222, avg=1681.89, stdev=294.11, samples=19
  lat (usec)   : 250=69.55%, 500=26.73%, 750=0.86%, 1000=0.43%
  lat (msec)   : 2=0.47%, 4=1.36%, 10=0.60%, 20=0.01%
  cpu          : usr=0.65%, sys=3.22%, ctx=33542, majf=0, minf=11
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued rwts: total=16771,16770,0,0 short=0,0,0,0 dropped=0,0,0,0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: bw=6708KiB/s (6869kB/s), 6708KiB/s-6708KiB/s (6869kB/s-6869kB/s), io=65.5MiB (68.7MB), run=10001-10001msec
  WRITE: bw=6707KiB/s (6868kB/s), 6707KiB/s-6707KiB/s (6868kB/s-6868kB/s), io=65.5MiB (68.7MB), run=10001-10001msec

Disk stats (read/write):
  vda: ios=16626/16627, merge=0/0, ticks=5066/3686, in_queue=8753, util=93.53%
[root@Centos8 fio-3.32]# 
```

### 参数解释

```sh
iops ：磁盘的每秒读写次数，这个是随机读写考察的重点  
bw   ：磁盘的吞吐量，这个是顺序读写考察的重点，类似于下载速度  
avg  ：每个IO请求的平均相应时间
io   ：总的输入输出量 
runt ：总运行时间
msec ：毫秒
usec ：微秒
lat (msec)：延迟(毫秒)

-rw=randwrite：定义测试时的读写策略，可选值如下：随机读：randread，随机写：randwrite，顺序读： read，顺序写：write，混合随机读写：randrw0
-ioengine=libaio：libaio指的是异步模式，如果是同步就要用sync。定义fio如何下发IO请求，通常有同步IO和异步IO：同步IO一次只能发出一个IO请求， 等待内核完成后才返回。这样对于单个线程IO队列深度总是小于1，但是可以透过多个线程并发执行来解决。通常会用16~32个线程同时工作把IO队列深度塞满。异步IO则通常使用libaio这样的方式一次提交一批IO 请求，然后等待一批的完成，减少交互的次 数，会更有效率
-direct=1：定义是否使用direct IO，可选值如下：值为0，表示使用buffered IO；值为1，表示使用 direct IO
-thread：使用pthread_create创建线程，另一种是fork创建进程。进程的开销比线程要大，一般都采用thread测试。
–numjobs=1：定义测试的并发线程数
-iodepth=64：定义测试时的IO队列深度，默认为1。此处定义的队列深度是指每个线程的队列深度， 如果有多个线程测试，意味着每个线程都是此处定义的队列深度。fio总的IO并发数 =iodepth * numjobs。
-filename：定义测试文件（设备）的名称。此处选择文件，则代表测试文件系统的性能，例如：- filename=/opt/fiotest/fiotest.txt；此处选择设备名称，则代表测试裸盘的性能，例：-filename=/dev/vdb1
。如果在已经分区、并创建文件系统，且已写入数据的磁盘上进行性能测试，请注意
filename选择指定文件，以避免覆盖文件系统和原有数据。
-size=100M：定义测试IO操作的数据量，若未指定runtime这类参数，fio会将指定大小的数据量全部 读/写完成，然后才停止测试。该参数的值，可以是带单位的数字，比如size=10G，表
示读/写的数据量为10GB；也可是百分数，比如size=20%，表示读/写的数据量占该设
备总文件的20%的空间。建议测试数据量为内存两倍大，尽量避免缓存影响。
-name=job1：定义测试任务名称。
-bs=4k：定义IO的块大小(block size)，单位是k、K、m和M等，默认IO块大小为4 KB。
–output TestResult.log：日志输出到TestResult.log。
-runtime：定义测试时间。如果未配置，则持续将size指定的文件大小，以每次bs值为分块大小读/ 写完。
-group_reporting：定义测试结果显示模式，group_reporting 表示汇总每个进程的统计信息，而非以不同 job汇总展示信息。
```

## 问题及解决方案

> fio: engine libaio not loadable

```sh
在线
yum install -y libaio-devel
离线
rpm -ivh 
```

> https://blog.csdn.net/Q0717168/article/details/127480289

## 参考链接

> https://git.kernel.dk/cgit/fio/

> https://blog.csdn.net/u012503639/article/details/125393328

> https://blog.csdn.net/BBJG_001/article/details/125025164

> http://t.zoukankan.com/hiyang-p-12764088.html

> https://blog.csdn.net/u012503639/article/details/125393328

> https://blog.csdn.net/u012503639/article/details/125393328

> http://t.zoukankan.com/dongdongwq-p-5390353.html