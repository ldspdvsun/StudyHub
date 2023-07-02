## Centos8

### 以 root 用户通过 CentOS 软件包管理器来安装

```sh
sudo dnf install @mysql
```

### 在键盘上敲一个：y
### 启动 MySQL

```sh
sudo systemctl start mysqld.service
```

### 登入 MySQL

```sh
mysql -u root -p
```

### 设密码、授权、开启远程访问

```sh
CREATE USER 'root'@'%' IDENTIFIED BY 'root';
GRANT ALL ON *.* TO 'root'@'%';
ALTER USER 'root'@'%' IDENTIFIED WITH mysql_native_password BY 'root';
```

### 更改端口

#### 编辑 my.cnf

```sh
sudo vim /etc/my.cnf
```

#### 增加配置

```sh
[mysqld]
port=6666
```

#### 重启 MySQL

```sh
sudo systemctl restart mysqld.service
```

## Centos7

> https://www.jb51.net/article/251117.htm

环境介绍 :
* 服务器： 阿里云轻量应用服务器
* 系统版本： CentOS 7.9
* MySQL版本： 8.0.23
![image-6.png](attachment:image-6.png)

### 卸载MariaDB

> 在CentOS中默认安装有MariaDB，是MySQL的一个分支，主要由开源社区维护。
CentOS 7及以上版本已经不再使用MySQL数据库，而是使用MariaDB数据库。
如果直接安装MySQL，会和MariaDB的文件冲突。
因此，需要先卸载自带的MariaDB，再安装MySQL。

#### 查看版本：

```sh
rpm -qa|grep mariadb
```

#### 卸载

```sh
rpm -e --nodeps 文件名
```

#### 检查是否卸载干净：

```sh
rpm -qa|grep mariadb
```

### 安装MySQL

#### 下载资源包

1. 官网下载

MySQL官网下载地址: https://dev.mysql.com/downloads/mysql/

2. wget下载

```sh
wget https://dev.mysql.com/get/Downloads/MySQL-8.0/mysql-8.0.20-linux-glibc2.12-x86_64.tar.xz
```

#### 解压

.tar.gz后缀：tar -zxvf 文件名

.tar.xz后缀：tar -Jxvf 文件名

```sh
tar -Jxvf mysql-8.0.20-linux-glibc2.12-x86_64.tar.xz
```

#### 重命名

将解压后的文件夹重命名（或者为文件夹创建软链接）

```sh
# 重命名
mv 原文件夹名 mysql8
# 软链接
ln -s 文件夹名 mysql8
```

#### 添加PATH变量

添加PATH变量后，可在全局使用MySQL。

有两种添加方式：export命令临时生效、修改配置文件用久生效；

```sh
# 临时环境变量，关闭shell后失效，通常用于测试环境
vim /etc/profile
追加下行内容到文件中
export PATH=$PATH:/data/software/mysql8/bin
source /etc/profile

```

#### 用户和用户组

1. 创建用户组和用户

```sh
# 创建一个用户组：mysql
groupadd mysql
# 创建一个系统用户：mysql，指定用户组为mysql
useradd -r -g mysql mysql
```

创建用户组：groupadd

创建用户：useradd

-r：创建系统用户
-g：指定用户组

#### 数据目录

1. 创建目录

```sh
mkdir -p /data/software/mysql8/datas
```

2. 赋予权限

```sh
# 更改属主和数组
chown -R mysql:mysql /data/software/mysql8/datas
# 更改模式
chmod -R 750 /data/software/mysql8/datas
```

#### 初始化MySQL

##### 配置参数

在/data/software/mysql8/下，创建my.cnf配置文件，用于初始化MySQL数据库

```sh
[mysql]
# 默认字符集
default-character-set=utf8mb4
[client]
port       = 3306
socket     = /tmp/mysql.sock

[mysqld]
port       = 3306
server-id  = 3306
user       = mysql
socket     = /tmp/mysql.sock
# 安装目录
basedir    = /data/software/mysql8
# 数据存放目录
datadir    = /data/software/mysql8/datas/mysql
log-bin    = /data/software/mysql8/datas/mysql/mysql-bin
innodb_data_home_dir      =/data/software/mysql8/datas/mysql
innodb_log_group_home_dir =/data/software/mysql8/datas/mysql
#日志及进程数据的存放目录
log-error =/data/software/mysql8/datas/mysql/mysql.log
pid-file  =/data/software/mysql8/datas/mysql/mysql.pid
# 服务端使用的字符集默认为8比特编码
character-set-server=utf8mb4
lower_case_table_names=1
autocommit =1
 
 ##################以上要修改的########################
skip-external-locking
key_buffer_size = 256M
max_allowed_packet = 1M
table_open_cache = 1024
sort_buffer_size = 4M
net_buffer_length = 8K
read_buffer_size = 4M
read_rnd_buffer_size = 512K
myisam_sort_buffer_size = 64M
thread_cache_size = 128
  
#query_cache_size = 128M
tmp_table_size = 128M
explicit_defaults_for_timestamp = true
max_connections = 500
max_connect_errors = 100
open_files_limit = 65535
   
binlog_format=mixed
    
binlog_expire_logs_seconds =864000
    
# 创建新表时将使用的默认存储引擎
default_storage_engine = InnoDB
innodb_data_file_path = ibdata1:10M:autoextend
innodb_buffer_pool_size = 1024M
innodb_log_file_size = 256M
innodb_log_buffer_size = 8M
innodb_flush_log_at_trx_commit = 1
innodb_lock_wait_timeout = 50
transaction-isolation=READ-COMMITTED
      
[mysqldump]
quick
max_allowed_packet = 16M
       
[myisamchk]
key_buffer_size = 256M
sort_buffer_size = 4M
read_buffer = 2M
write_buffer = 2M
        
[mysqlhotcopy]
interactive-timeout
```

##### 初始化

```sh
mysqld --defaults-file=/data/software/mysql8/my.cnf --basedir=/data/software/mysql8/ --datadir=/data/software/mysql8/datas/mysql --user=mysql --initialize-insecure
```

defaults-file：指定配置文件（要放在–initialize 前面）

user： 指定用户

basedir：指定安装目录

datadir：指定初始化数据目录

intialize-insecure：初始化无密码

### 启动MySQL

查看 MySQL的 bin路径下，是否包含mysqld_safe，用于后台安全启动MySQL。
![image-5.png](attachment:image-5.png)

#### 启动服务

```sh
# 完整命令
/data/software/mysql8/bin/mysqld_safe --defaults-file=/data/software/mysql8/my.cnf &
# 添加PATH变量后的命令（省略bin目录的路径）
mysqld_safe --defaults-file=/data/software/mysql/my.cnf &
# 查看是否启动
ps -ef|grep mysql
```
![image-4.png](attachment:image-4.png)

#### 登录

```sh
# 无密码登录方式
/data/software/mysql8/bin/mysql -u root --skip-password
# 有密码登录方式（初始的随机密码在/data/mysql8_data/mysql/mysql.log下）
mysql -u root -p
password:随机密码
```
![image-3.png](attachment:image-3.png)

#### 修改密码

```sh
# 修改密码
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '123456';
# 刷新权限
FLUSH PRIVILEGES;
```
![image-2.png](attachment:image-2.png)

#### 设置允许远程登录

登录到mysql里执行

```sh
mysql> use mysql
mysql> update user set user.Host='%'where user.User='root';
mysql> flush privileges;
mysql> quit
```

#### 在Navicat上测试连接

连接成功
![image.png](attachment:image.png)


## Centos7使用yum安装MySQL8

>https://blog.csdn.net/redrose2100/article/details/117938139

### 下载

```sh
[root@SqaServer Sysbench]# wget https://dev.mysql.com/get/mysql80-community-release-el7-7.noarch.rpm
--2022-11-06 13:17:56--  https://dev.mysql.com/get/mysql80-community-release-el7-7.noarch.rpm
正在解析主机 dev.mysql.com (dev.mysql.com)... 223.119.203.77, 2600:1417:e800:18a::2e31, 2600:1417:e800:189::2e31
正在连接 dev.mysql.com (dev.mysql.com)|223.119.203.77|:443... 已连接。
已发出 HTTP 请求，正在等待回应... 302 Moved Temporarily
位置：https://repo.mysql.com//mysql80-community-release-el7-7.noarch.rpm [跟随至新的 URL]
--2022-11-06 13:17:57--  https://repo.mysql.com//mysql80-community-release-el7-7.noarch.rpm
正在解析主机 repo.mysql.com (repo.mysql.com)... 23.36.48.238
正在连接 repo.mysql.com (repo.mysql.com)|23.36.48.238|:443... 已连接。
已发出 HTTP 请求，正在等待回应... 200 OK
长度：11196 (11K) [application/x-redhat-package-manager]
正在保存至: “mysql80-community-release-el7-7.noarch.rpm”

100%[====================================================================================>] 11,196      --.-K/s 用时 0s

2022-11-06 13:17:57 (106 MB/s) - 已保存 “mysql80-community-release-el7-7.noarch.rpm” [11196/11196])

[root@SqaServer Sysbench]# ll
总用量 592172
-rwxrwxrwx  1 root root 604856088 11月  5 10:27 mysql-8.0.31-linux-glibc2.12-x86_64.tar.xz
-rw-r--r--  1 root root     11196 8月  27 02:56 mysql80-community-release-el7-7.noarch.rpm
drwxrwxr-x 13 root root      4096 11月  5 17:33 sysbench-1.0.20
-rwxrwxrwx  1 root root   1509630 11月  5 10:27 sysbench-1.0.20.tar.gz
[root@SqaServer Sysbench]# mv mysql80-community-release-el7-7.noarch.rpm /opt/
[root@SqaServer Sysbench]# cd /opt/
[root@SqaServer opt]# ll
总用量 12
drwxr-xr-x  3 root root    17 11月  1 15:53 cni
drwx--x--x  4 root root    28 11月  1 15:46 containerd
-rw-r--r--  1 root root 11196 8月  27 02:56 mysql80-community-release-el7-7.noarch.rpm
drwxr-xr-x. 2 root root     6 10月 31 2018 rh
[root@SqaServer opt]# yum localinstall mysql80-community-release-el7-7.noarch.rpm
已加载插件：fastestmirror, langpacks
正在检查 mysql80-community-release-el7-7.noarch.rpm: mysql80-community-release-el7-7.noarch
mysql80-community-release-el7-7.noarch.rpm 将被安装
正在解决依赖关系
--> 正在检查事务
---> 软件包 mysql80-community-release.noarch.0.el7-7 将被 安装
--> 解决依赖关系完成
base/7/x86_64                                                                                          | 3.6 kB  00:00:00
docker-ce-stable/7/x86_64                                                                              | 3.5 kB  00:00:00
extras/7/x86_64                                                                                        | 2.9 kB  00:00:00
kubernetes                                                                                             | 1.4 kB  00:00:00
updates/7/x86_64                                                                                       | 2.9 kB  00:00:00

依赖关系解决

==============================================================================================================================
 Package                             架构             版本            源                                                 大小
==============================================================================================================================
正在安装:
 mysql80-community-release           noarch           el7-7           /mysql80-community-release-el7-7.noarch            10 k

事务概要
==============================================================================================================================
安装  1 软件包

总计：10 k
安装大小：10 k
Is this ok [y/d/N]: y
Downloading packages:
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  正在安装    : mysql80-community-release-el7-7.noarch                                                                    1/1
  验证中      : mysql80-community-release-el7-7.noarch                                                                    1/1

已安装:
  mysql80-community-release.noarch 0:el7-7

完毕！
[root@SqaServer opt]# yum -y install mysql-community-server
已加载插件：fastestmirror, langpacks
Loading mirror speeds from cached hostfile
 * base: mirrors.bupt.edu.cn
 * extras: mirrors.bupt.edu.cn
 * updates: mirrors.bupt.edu.cn
mysql-connectors-community                                                                             | 2.6 kB  00:00:00
mysql-tools-community                                                                                  | 2.6 kB  00:00:00
mysql80-community                                                                                      | 2.6 kB  00:00:00
(1/3): mysql80-community/x86_64/primary_db                                                             | 222 kB  00:00:00
(2/3): mysql-connectors-community/x86_64/primary_db                                                    |  93 kB  00:00:00
(3/3): mysql-tools-community/x86_64/primary_db                                                         |  89 kB  00:00:00
正在解决依赖关系
--> 正在检查事务
---> 软件包 mysql-community-server.x86_64.0.8.0.31-1.el7 将被 安装
--> 正在处理依赖关系 mysql-community-common(x86-64) = 8.0.31-1.el7，它被软件包 mysql-community-server-8.0.31-1.el7.x86_64 需要
--> 正在处理依赖关系 mysql-community-icu-data-files = 8.0.31-1.el7，它被软件包 mysql-community-server-8.0.31-1.el7.x86_64 需要
--> 正在处理依赖关系 mysql-community-client(x86-64) >= 8.0.11，它被软件包 mysql-community-server-8.0.31-1.el7.x86_64 需要
--> 正在检查事务
---> 软件包 mysql-community-client.x86_64.0.8.0.31-1.el7 将被 安装
--> 正在处理依赖关系 mysql-community-client-plugins = 8.0.31-1.el7，它被软件包 mysql-community-client-8.0.31-1.el7.x86_64 需要
--> 正在处理依赖关系 mysql-community-libs(x86-64) >= 8.0.11，它被软件包 mysql-community-client-8.0.31-1.el7.x86_64 需要
---> 软件包 mysql-community-common.x86_64.0.8.0.31-1.el7 将被 安装
---> 软件包 mysql-community-icu-data-files.x86_64.0.8.0.31-1.el7 将被 安装
--> 正在检查事务
---> 软件包 mariadb-libs.x86_64.1.5.5.68-1.el7 将被 取代
--> 正在处理依赖关系 libmysqlclient.so.18()(64bit)，它被软件包 1:mariadb-devel-5.5.68-1.el7.x86_64 需要
--> 正在处理依赖关系 libmysqlclient.so.18()(64bit)，它被软件包 2:postfix-2.10.1-9.el7.x86_64 需要
--> 正在处理依赖关系 libmysqlclient.so.18(libmysqlclient_18)(64bit)，它被软件包 2:postfix-2.10.1-9.el7.x86_64 需要
--> 正在处理依赖关系 mariadb-libs(x86-64) = 1:5.5.68-1.el7，它被软件包 1:mariadb-devel-5.5.68-1.el7.x86_64 需要
---> 软件包 mysql-community-client-plugins.x86_64.0.8.0.31-1.el7 将被 安装
---> 软件包 mysql-community-libs.x86_64.0.8.0.31-1.el7 将被 舍弃
--> 正在检查事务
---> 软件包 mariadb-devel.x86_64.1.5.5.68-1.el7 将被 取代
---> 软件包 mysql-community-devel.x86_64.0.8.0.31-1.el7 将被 舍弃
---> 软件包 mysql-community-libs-compat.x86_64.0.8.0.31-1.el7 将被 舍弃
--> 解决依赖关系完成

依赖关系解决

==============================================================================================================================
 Package                                    架构               版本                       源                             大小
==============================================================================================================================
正在安装:
 mysql-community-devel                      x86_64             8.0.31-1.el7               mysql80-community             1.9 M
      替换  mariadb-devel.x86_64 1:5.5.68-1.el7
 mysql-community-libs                       x86_64             8.0.31-1.el7               mysql80-community             1.5 M
      替换  mariadb-libs.x86_64 1:5.5.68-1.el7
 mysql-community-libs-compat                x86_64             8.0.31-1.el7               mysql80-community             670 k
      替换  mariadb-libs.x86_64 1:5.5.68-1.el7
 mysql-community-server                     x86_64             8.0.31-1.el7               mysql80-community              64 M
为依赖而安装:
 mysql-community-client                     x86_64             8.0.31-1.el7               mysql80-community              16 M
 mysql-community-client-plugins             x86_64             8.0.31-1.el7               mysql80-community             2.5 M
 mysql-community-common                     x86_64             8.0.31-1.el7               mysql80-community             647 k
 mysql-community-icu-data-files             x86_64             8.0.31-1.el7               mysql80-community             2.1 M

事务概要
==============================================================================================================================
安装  4 软件包 (+4 依赖软件包)

总下载量：89 M
Downloading packages:
警告：/var/cache/yum/x86_64/7/mysql80-community/packages/mysql-community-client-plugins-8.0.31-1.el7.x86_64.rpm: 头V4 RSA/SHA256 Signature, 密钥 ID 3a79bd29: NOKEY
mysql-community-client-plugins-8.0.31-1.el7.x86_64.rpm 的公钥尚未安装
(1/8): mysql-community-client-plugins-8.0.31-1.el7.x86_64.rpm                                          | 2.5 MB  00:00:01
(2/8): mysql-community-common-8.0.31-1.el7.x86_64.rpm                                                  | 647 kB  00:00:00
(3/8): mysql-community-devel-8.0.31-1.el7.x86_64.rpm                                                   | 1.9 MB  00:00:00
(4/8): mysql-community-icu-data-files-8.0.31-1.el7.x86_64.rpm                                          | 2.1 MB  00:00:01
(5/8): mysql-community-libs-8.0.31-1.el7.x86_64.rpm                                                    | 1.5 MB  00:00:00
(6/8): mysql-community-libs-compat-8.0.31-1.el7.x86_64.rpm                                             | 670 kB  00:00:00
(7/8): mysql-community-client-8.0.31-1.el7.x86_64.rpm                                                  |  16 MB  00:00:05
(8/8): mysql-community-server-8.0.31-1.el7.x86_64.rpm                                                  |  64 MB  00:00:12
------------------------------------------------------------------------------------------------------------------------------
总计                                                                                          4.9 MB/s |  89 MB  00:00:18
从 file:///etc/pki/rpm-gpg/RPM-GPG-KEY-mysql-2022 检索密钥
导入 GPG key 0x3A79BD29:
 用户ID     : "MySQL Release Engineering <mysql-build@oss.oracle.com>"
 指纹       : 859b e8d7 c586 f538 430b 19c2 467b 942d 3a79 bd29
 软件包     : mysql80-community-release-el7-7.noarch (@/mysql80-community-release-el7-7.noarch)
 来自       : /etc/pki/rpm-gpg/RPM-GPG-KEY-mysql-2022
从 file:///etc/pki/rpm-gpg/RPM-GPG-KEY-mysql 检索密钥
导入 GPG key 0x5072E1F5:
 用户ID     : "MySQL Release Engineering <mysql-build@oss.oracle.com>"
 指纹       : a4a9 4068 76fc bd3c 4567 70c8 8c71 8d3b 5072 e1f5
 软件包     : mysql80-community-release-el7-7.noarch (@/mysql80-community-release-el7-7.noarch)
 来自       : /etc/pki/rpm-gpg/RPM-GPG-KEY-mysql
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  正在安装    : mysql-community-client-plugins-8.0.31-1.el7.x86_64                                                       1/10
  正在安装    : mysql-community-common-8.0.31-1.el7.x86_64                                                               2/10
  正在安装    : mysql-community-libs-8.0.31-1.el7.x86_64                                                                 3/10
  正在安装    : mysql-community-client-8.0.31-1.el7.x86_64                                                               4/10
  正在安装    : mysql-community-icu-data-files-8.0.31-1.el7.x86_64                                                       5/10
  正在安装    : mysql-community-server-8.0.31-1.el7.x86_64                                                               6/10
  正在安装    : mysql-community-libs-compat-8.0.31-1.el7.x86_64                                                          7/10
  正在安装    : mysql-community-devel-8.0.31-1.el7.x86_64                                                                8/10
  正在删除    : 1:mariadb-devel-5.5.68-1.el7.x86_64                                                                      9/10
  正在删除    : 1:mariadb-libs-5.5.68-1.el7.x86_64                                                                      10/10
  验证中      : mysql-community-server-8.0.31-1.el7.x86_64                                                               1/10
  验证中      : mysql-community-common-8.0.31-1.el7.x86_64                                                               2/10
  验证中      : mysql-community-libs-compat-8.0.31-1.el7.x86_64                                                          3/10
  验证中      : mysql-community-client-plugins-8.0.31-1.el7.x86_64                                                       4/10
  验证中      : mysql-community-icu-data-files-8.0.31-1.el7.x86_64                                                       5/10
  验证中      : mysql-community-client-8.0.31-1.el7.x86_64                                                               6/10
  验证中      : mysql-community-libs-8.0.31-1.el7.x86_64                                                                 7/10
  验证中      : mysql-community-devel-8.0.31-1.el7.x86_64                                                                8/10
  验证中      : 1:mariadb-devel-5.5.68-1.el7.x86_64                                                                      9/10
  验证中      : 1:mariadb-libs-5.5.68-1.el7.x86_64                                                                      10/10

已安装:
  mysql-community-devel.x86_64 0:8.0.31-1.el7                      mysql-community-libs.x86_64 0:8.0.31-1.el7
  mysql-community-libs-compat.x86_64 0:8.0.31-1.el7                mysql-community-server.x86_64 0:8.0.31-1.el7

作为依赖被安装:
  mysql-community-client.x86_64 0:8.0.31-1.el7              mysql-community-client-plugins.x86_64 0:8.0.31-1.el7
  mysql-community-common.x86_64 0:8.0.31-1.el7              mysql-community-icu-data-files.x86_64 0:8.0.31-1.el7

替代:
  mariadb-devel.x86_64 1:5.5.68-1.el7                            mariadb-libs.x86_64 1:5.5.68-1.el7

完毕！
[root@SqaServer opt]# systemctl start mysqld
[root@SqaServer opt]# systemctl status  mysqld
● mysqld.service - MySQL Server
   Loaded: loaded (/usr/lib/systemd/system/mysqld.service; enabled; vendor preset: disabled)
   Active: active (running) since 日 2022-11-06 13:20:53 CST; 1s ago
     Docs: man:mysqld(8)
           http://dev.mysql.com/doc/refman/en/using-systemd.html
  Process: 4104 ExecStartPre=/usr/bin/mysqld_pre_systemd (code=exited, status=0/SUCCESS)
 Main PID: 4189 (mysqld)
   Status: "Server is operational"
    Tasks: 39
   CGroup: /system.slice/mysqld.service
           └─4189 /usr/sbin/mysqld

11月 06 13:20:48 SqaServer systemd[1]: Starting MySQL Server...
11月 06 13:20:53 SqaServer systemd[1]: Started MySQL Server.
[root@SqaServer opt]# systemctl enable mysqld
[root@SqaServer opt]# grep 'temporary password' /var/log/mysqld.log
2022-11-06T05:20:50.998266Z 6 [Note] [MY-010454] [Server] A temporary password is generated for root@localhost: qr.:wRI#_7Nu
[root@SqaServer opt]# mysql -uroot -p
Enter password:
ERROR 1045 (28000): Access denied for user 'root'@'localhost' (using password: YES)
[root@SqaServer opt]# mysql -uroot -p
Enter password:
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 9
Server version: 8.0.31

Copyright (c) 2000, 2022, Oracle and/or its affiliates.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY 'root';
ERROR 1819 (HY000): Your password does not satisfy the current policy requirements
mysql> exit
Bye
[root@SqaServer opt]# mysql -uroot -p
Enter password:
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 10
Server version: 8.0.31

Copyright (c) 2000, 2022, Oracle and/or its affiliates.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY '123ABCdef*';
Query OK, 0 rows affected (0.01 sec)

mysql> FLUSH PRIVILEGES;
Query OK, 0 rows affected (0.00 sec)

mysql> use mysql;
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed
mysql> update user set user.Host='%'where user.User='root';
Query OK, 1 row affected (0.00 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> flush privileges;
Query OK, 0 rows affected (0.01 sec)

mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
4 rows in set (0.00 sec)

mysql>
```

## docker compose部署mysql

1. 创建mysql文件夹，编写配置文件保存至mysql文件夹内

docker-compose.yml
```sh
version: '3'
services:
  db:
    image: mysql:latest
    environment:
      MYSQL_ROOT_PASSWORD: 123ABCdef*
      MYSQL_DATABASE: test
      MYSQL_USER: admin
      MYSQL_PASSWORD: 123ABCdef*
    ports:
      - "19994:3306"
      - "19993:8080"
    volumes:
      - ./mysql-data:/var/lib/mysql
  phpmyadmin:
    image: phpmyadmin/phpmyadmin
    environment:
      PMA_HOST: db
      PMA_USER: root
      PMA_PASSWORD: 123ABCdef*
    ports:
      - "19992:80"

```

2. 启动

```sh
root@VM-24-11-ubuntu:/data/docker/mysql# docker-compose up -d
Creating network "mysql_default" with the default driver
Creating mysql_phpmyadmin_1 ... done
Creating mysql_db_1         ... done
root@VM-24-11-ubuntu:/data/docker/mysql# 
```

3. 销毁

```sh
root@VM-24-11-ubuntu:/data/docker/mysql# docker-compose down
Stopping mysql_db_1         ... done
Stopping mysql_phpmyadmin_1 ... done
Removing mysql_db_1         ... done
Removing mysql_phpmyadmin_1 ... done
Removing network mysql_bridge
root@VM-24-11-ubuntu:/data/docker/mysql# 
```

## 参考链接

> https://www.jb51.net/article/251117.htm

> http://www.manongjc.com/detail/51-xnvorytnwrkdfgd.html
