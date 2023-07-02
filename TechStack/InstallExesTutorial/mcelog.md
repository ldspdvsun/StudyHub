## 下载

```sh
[root@Centos8 lx]# pwd
/opt/lx
[root@Centos8 lx]# git clone git://git.kernel.org/pub/scm/utils/cpu/mce/mcelog.git
[root@Centos8 lx]# ll
总用量 301888
drwxr-xr-x  6 root  root       4096 9月  30 09:34 mcelog
```

## 安装

```sh
[root@Centos8 lx]# cd mcelog/
[root@Centos8 mcelog]# make
[root@Centos8 mcelog]# make install
[root@Centos8 mcelog]# cp mcelog.init /etc/init.d/mcelog
[root@Centos8 mcelog]# chkconfig mcelog on
[root@Centos8 mcelog]# cp mcelog.init /etc/init.d/mcelog
[root@Centos8 mcelog]# chkconfig mcelog on
```

## 验证版本

```sh
[root@Centos8 mcelog]# mcelog --version
mcelog v189
[root@Centos8 mcelog]# 
```