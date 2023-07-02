## 下载Go压缩包

```sh
[root@Centos8 lx]# pwd
/opt/lx
[root@Centos8 lx]# wget https://golang.google.cn/dl/go1.19.1.linux-amd64.tar.gz
--2022-09-20 16:44:52--  https://golang.google.cn/dl/go1.19.1.linux-amd64.tar.gz
正在解析主机 golang.google.cn (golang.google.cn)... 220.181.174.226
正在连接 golang.google.cn (golang.google.cn)|220.181.174.226|:443... 已连接。
已发出 HTTP 请求，正在等待回应... 302 Found
位置：https://dl.google.com/go/go1.19.1.linux-amd64.tar.gz [跟随至新的 URL]
--2022-09-20 16:44:52--  https://dl.google.com/go/go1.19.1.linux-amd64.tar.gz
正在解析主机 dl.google.com (dl.google.com)... 220.181.174.33
正在连接 dl.google.com (dl.google.com)|220.181.174.33|:443... 已连接。
已发出 HTTP 请求，正在等待回应... 200 OK
长度：148820241 (142M) [application/x-gzip]
正在保存至: “go1.19.1.linux-amd64.tar.gz”

go1.19.1.linux-amd64. 100%[========================>] 141.93M  11.7MB/s  用时 11s

2022-09-20 16:45:04 (12.6 MB/s) - 已保存 “go1.19.1.linux-amd64.tar.gz” [148820241/148820241])

[root@Centos8 lx]# ls
go1.19.1.linux-amd64.tar.gz  lineuse  linkbench  yet-another-bench-script
```

## 解压Go压缩包

```sh
[root@Centos8 lx]# tar -zxvf go1.19.1.linux-amd64.tar.gz
go/
go/CONTRIBUTING.md
go/LICENSE
...
[root@Centos8 lx]# ll
总用量 145336
drwxr-xr-x 8 root root       199 9月   1 01:41 go
-rw-r--r-- 1 root root 148820241 9月   7 00:18 go1.19.1.linux-amd64.tar.gz
drwxr-xr-x 2 root root       118 9月  20 16:32 lineuse
drwxr-xr-x 6 root root       174 9月  20 13:20 linkbench
drwxr-xr-x 3 root root       117 9月  16 15:00 yet-another-bench-script
```

## 移动至用户的程序目录

```sh
[root@Centos8 lx]# mv go /usr/local
```

## 添加环境到配置文件

```sh
export GOROOT=/usr/local/go
export PATH=$PATH:$GOROOT/bin
[root@Centos8 lx]# vim /etc/profile
```

## 重新加载配置文件

```sh
[root@Centos8 lx]# source /etc/profile
```

## 验证是否配置成功

```sh
[root@Centos8 lx]# go version
go version go1.19.1 linux/amd64
[root@Centos8 lx]#
```