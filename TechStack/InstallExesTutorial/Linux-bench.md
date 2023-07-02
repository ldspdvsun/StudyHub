## 下载安装

```sh
[root@Centos8 lx]# git clone https://github.com/aquasecurity/linux-bench.git

 'linux-bench'...
remote: Enumerating objects: 547, done.
remote: Counting objects:   0% (1/130)
...
[root@Centos8 lx]# ll

145336
-rw-r--r-- 1 root root 148820241 9   7 00:18 go1.19.1.linux-amd64.tar.gz
drwxr-xr-x 2 root root       118 9  20 16:32 lineuse
drwxr-xr-x 6 root root       174 9  20 13:20 linkbench
drwxr-xr-x 6 root root       266 9  20 17:04 linux-bench
drwxr-xr-x 3 root root       117 9  16 15:00 yet-another-bench-script

[root@Centos8 lx]# cd linux-bench/
```

## 构建

```sh
[root@Centos8 linux-bench]# go build -o linux-bench .

go: downloading github.com/aquasecurity/bench-common v0.4.4
go: downloading github.com/golang/glog v0.0.0-20160126235308-23def4e6c14b
...
```

## 运行

```sh
[root@Centos8 linux-bench]# ./linux-bench
[INFO] 1 Initial Setup
[INFO] 1.1 Filesystem Configuration
[WARN] 1.1.1 Disable unused filesystems
[FAIL] 1.1.1.1.a Ensure mounting of cramfs filesystems is disabled
[PASS] 1.1.1.1.b Ensure mounting of cramfs filesystems is disabled
== Summary ==
81 checks PASS
165 checks FAIL
107 checks WARN
0 checks INFO

[root@Centos8 linux-bench]#
```