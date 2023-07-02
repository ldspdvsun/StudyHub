## 下载地址

> https://nmon.sourceforge.net/pmwiki.php?n=Site.Download

## 上传并解压

```sh
[admin@Centos8 nmon]$ ll | grep nmon16m
总用量 7056
-rw-rw-r-- 1 admin admin 7222481 2月  24 2020 nmon16m_helpsystems.tar.gz
[admin@Centos8 nmon]$
[admin@Centos8 nmon]$ tar -zxvf nmon16m_helpsystems.tar.gz
…
-rwxr----- 1 admin admin  350222 2月  20 2020 nmon_x86_64_centos6
-rwxr----- 1 admin admin  404896 2月  20 2020 nmon_x86_64_centos7
-rwxr----- 1 admin admin  472080 2月  20 2020 nmon_x86_64_centos8
…
[admin@Centos8 nmon]
[admin@Centos8 nmon]$ ./nmon_x86_64_centos8 -f -s 5 -c 12 -m ./report/
```

## 查看脚本运行结果

```sh
[admin@Centos8 nmon]$ cd report/
[admin@Centos8 report]$ ll
-rw-rw-r-- 1 admin admin 31408 9月  26 10:07 Centos8_220926_1006.nmon
```

## 数据采集完关闭进程

```sh
[admin@Centos8 report]$ ps -ef | grep nmon
admin      12378   11982  0 10:11 pts/2    00:00:00 grep --color=auto nmon
[admin@Centos8 report]$ kill -9 12378
[admin@Centos8 report]$
```