# linux常用命令行
https://static001.geekbang.org/resource/image/88/e5/8855bb645d8ecc35c80aa89cde5d16e5.jpg?wh=3431*2125


# 更改ip配置

```sh
# 打开配置文件
vi /etc/sysconfig/network-scripts/ifcfg-ens33
# 修改配置
BOOTPROTO="static"
ONBOOT="yes"
IPADDR=192.168.58.135
NETMASK=255.255.255.0
GATEWAY=192.168.58.2
DNS1=192.168.58.2
# 重启服务
systemctl restart network
```

# 创建用户
```sh
[root@VM-8-17-centos ~]# adduser admin
[root@VM-8-17-centos ~]# passwd admin
Changing password for user admin.
New password: 
BAD PASSWORD: The password is shorter than 8 characters
Retype new password: 
passwd: all authentication tokens updated successfully.
# 添加到wheel组，使其具备sudo权限
[root@VM-8-17-centos ~]# usermod -aG wheel admin
[root@VM-8-17-centos ~]# su admin
[admin@VM-8-17-centos root]$ cd ~
[admin@VM-8-17-centos ~]$ pwd
/home/admin
[admin@VM-8-17-centos ~]$ 

```

## 修改系统名称
```sh
[root@VM-8-17-centos ~]# hostnamectl set-hostname centos8
[root@VM-8-17-centos ~]# hostname
hostname
centos8
[root@VM-8-17-centos ~]# 
```

## 放开指定端口

```sh
[root@VM-24-11-centos ~]# firewall-cmd --zone=public --add-port=5212/tcp --permanent
success
[root@VM-24-11-centos ~]# firewall-cmd --reload
success
[root@VM-24-11-centos ~]# firewall-cmd --query-port=5212/tcp
yes
[root@VM-24-11-centos ~]# systemctl stop firewalld.service
[root@VM-24-11-centos ~]# systemctl start firewalld.service
[root@VM-24-11-centos ~]# systemctl status firewalld.service
● firewalld.service - firewalld - dynamic firewall daemon
   Loaded: loaded (/usr/lib/systemd/system/firewalld.service; enabled; vendor preset: enabled)
   Active: active (running) since Mon 2022-11-28 17:09:13 CST; 6h ago
     Docs: man:firewalld(1)
 Main PID: 242811 (firewalld)
    Tasks: 3 (limit: 23995)
   Memory: 40.4M
   CGroup: /system.slice/firewalld.service
           └─242811 /usr/libexec/platform-python -s /usr/sbin/firewalld --nofork --nopid

Nov 28 17:09:10 VM-24-11-centos systemd[1]: Starting firewalld - dynamic firewall daemon...
Nov 28 17:09:13 VM-24-11-centos systemd[1]: Started firewalld - dynamic firewall daemon.
Nov 28 17:09:13 VM-24-11-centos firewalld[242811]: WARNING: AllowZoneDrifting is enabled. This is considered an insecure configuration option. It wil>
Nov 28 17:09:14 VM-24-11-centos firewalld[242811]: WARNING: COMMAND_FAILED: '/usr/sbin/iptables -w10 -D FORWARD -i docker0 -o docker0 -j DROP' failed>
Nov 28 17:09:15 VM-24-11-centos firewalld[242811]: WARNING: COMMAND_FAILED: '/usr/sbin/iptables -w10 -D FORWARD -i docker0 -o docker0 -j DROP' failed>
Nov 28 23:05:37 VM-24-11-centos firewalld[242811]: WARNING: AllowZoneDrifting is enabled. This is considered an insecure configuration option. It wil>
Nov 28 23:05:38 VM-24-11-centos firewalld[242811]: WARNING: COMMAND_FAILED: '/usr/sbin/iptables -w10 -D FORWARD -i docker0 -o docker0 -j DROP' failed>
Nov 28 23:05:38 VM-24-11-centos firewalld[242811]: WARNING: COMMAND_FAILED: '/usr/sbin/iptables -w10 -D FORWARD -i docker0 -o docker0 -j DROP' failed>
lines 1-18/18 (END)

```

## 程序后台运行命令

>使用nohup命令，意思是 no hang up（不挂起），也就是说，当前交互命令行退出的时候，程序还要在。当然这个时候，程序不能霸占交互命令行，而是应该在后台运行。最后加一个 &，就表示后台运行。另外一个要处理的就是输出，原来什么都打印在交互命令行里，现在在后台运行了，输出到文件。
### 后台方式
```sh
nohup command>out.file 2>&1 &

“1”表示文件描述符 1，表示标准输出，
“2”表示文件描述符 2，意思是标准错误输出，
“2>&1”表示标准输出和错误输出合并到 out.file 里。


# 那这个进程如何关闭呢？我们假设启动的程序包含某个关键字，那就可以使用下面的命令
ps -ef |grep 关键字  |awk '{print $2}'|xargs kill -9

ps -ef 可以单独执行，列出所有正在运行的程序，
grep 上面我们介绍过了，通过关键字找到咱们刚才启动的程序。
awk '{print $2}'是指第二列的内容，是运行的程序 ID。
通过 xargs 传递给 kill -9，也就是发给这个运行的程序一个信号，让它关闭。
如果你已经知道运行的程序 ID，可以直接使用 kill 关闭运行的程序。
```
### 服务方式

>Ubuntu 中，我们可以通过 
apt-get install mysql-server 的方式安装 MySQL，
然后通过命令systemctl start mysql启动 MySQL，
通过systemctl enable mysql设置开机启动。
之所以成为服务并且能够开机启动，是因为在 /lib/systemd/system 目录下会创建一个 XXX.service 的配置文件，里面定义了如何启动、如何关闭。

>在 CentOS 里有些特殊，MySQL 被 Oracle 收购后，因为担心授权问题，改为使用 MariaDB，它是 MySQL 的一个分支。通过命令
yum install mariadb-server mariadb进行安装，
命令systemctl start mariadb启动，
命令systemctl enable mariadb设置开机启动。
同理，会在 /usr/lib/systemd/system 目录下，创建一个 XXX.service 的配置文件，从而成为一个服务。




## 升级python3

>https://www.bilibili.com/read/cv15970563/

1. 查看已安装Python版本
```sh
python -V
```

2. 将python3上传到服务器并解压
```sh
wget https://www.python.org/ftp/python/3.10.8/Python-3.10.8.tgz
tar -zxvf Python-3.10.8.tgz
```

3. 进入Python3目录
```sh
cd Python-3.10.8
```

4. 安装依赖
```sh
yum groupinstall -y "Development tools"
yum install -y openssl-devel bzip2-devel expat-devel gdbm-devel readline-devel sqlite-devel psmisc libffi-devel
```

5. 预编译，设置安装目录
```sh
# 查看openssl版本，及位置，供下面命令使用
$ openssl version
OpenSSL 1.1.1k  FIPS 25 Mar 2021
$ which openssl
/usr/bin/openssl
$ whereis openssl
openssl: /usr/bin/openssl /usr/include/openssl /usr/share/man/man1/openssl.1ssl.gz

# 为/usr/local/python3。安装目录可以自定义
./configure --prefix=/usr/local/python3 --enable-optimizations --with-ssl
# 编译。因为CPU4核，所以设置-j4加快编译速度
make -j4
# 编译安装
make install -j4
```

6. 删除旧版本的python3链接
```sh
mv /usr/bin/python3 /tmp/
mv /usr/bin/pip3 /tmp/
```

7. 建立新的链接
```sh
ln -s /usr/local/python3/bin/python3.10 /usr/bin/python3
ln -s /usr/local/python3/bin/pip3 /usr/bin/pip3
```

8. 查看是否安装成功
```sh
python3 -V
pip3 -V
pip3 list
```

9. 加入系统环境
```sh
vi /etc/profile

export PATH=$PATH:/usr/local/python3/bin

source /etc/profile
```

10. pip install 出现错误的解决方法

```sh
[root@node1 Python-3.10.7]# pip3 install -i http://pypi.douban.com/simple/  pip -U --trusted-host pypi.douban.com
Looking in indexes: http://pypi.douban.com/simple/
Requirement already satisfied: pip in /usr/local/python3/lib/python3.10/site-packages (22.2.2)
Collecting pip
  Downloading http://pypi.doubanio.com/packages/07/51/2c0959c5adf988c44d9e1e0d940f5b074516ecc87e96b1af25f59de9ba38/pip-23.0.1-py3-none-any.whl (2.1 MB)
     ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 2.1/2.1 MB 4.7 MB/s eta 0:00:00
Installing collected packages: pip
  Attempting uninstall: pip
    Found existing installation: pip 22.2.2
    Uninstalling pip-22.2.2:
      Successfully uninstalled pip-22.2.2
Successfully installed pip-23.0.1
WARNING: Running pip as the 'root' user can result in broken permissions and conflicting behaviour with the system package manager. It is recommended to use a virtual environment instead: https://pip.pypa.io/warnings/venv
[root@node1 Python-3.10.7]# 
```

### openssl解决方法
>https://www.cnblogs.com/chengfo/p/16289666.html

1. 下载
```sh
wget https://www.openssl.org/source/openssl-1.1.1s.tar.gz
```

2. 解压并切换目录

```sh
tar -zxvf openssl-1.1.1.tar.gz
cd openssl-1.1.1
```

3. 设定Openssl 安装，( --prefix )参数为欲安装之目录，也就是安装后的档案会出现在该目录下

```sh
./config --prefix=/usr/local/bin/openssl
```

4. 执行命令

```sh
./config -t
```

5. 执行make、make install，编译Openssl

```sh
make & make install
```
P.S. 若CentOS7中没有GCC编译器，执行命令 yum -y install gcc 安装GCC。

 

6. 切换openssl版本

```sh
mv /usr/bin/openssl /usr/bin/openssl.bak
mv /usr/include/openssl /usr/include/openssl.bak


ln -s /usr/local/openssl/bin/openssl /usr/bin/openssl
ln -s /usr/local/openssl/include/openssl /usr/include/openssl

echo "/usr/local/openssl/lib" >> /etc/ld.so.conf

ldconfig -v

ln -s /usr/local/openssl/lib/libssl.so.1.1 /usr/lib64/libssl.so.1.1
ln -s /usr/local/openssl/lib/libcrypto.so.1.1 /usr/lib64/libcrypto.so.1.1
注意：不能直接删除软链接

如需使用新版本开发，则需替换原来的软链接指向，即替换原动态库，进行版本升级。

替换/lib(lib64)和/usr/lib(lib64)和/usr/local/lib(lib64)存在的相应动态库：

ln -sf /usr/local/openssl/lib/libssl.so.1.1 /usr/lib64/libssl.so
ln -sf /usr/local/openssl/lib/libcrypto.so.1.1 /usr/lib64/libcrypto.so

使配置生效
ldconfig
```

* https://blog.csdn.net/lim_5258/article/details/126508077

* https://blog.csdn.net/weixin_41227756/article/details/127003944

* https://www.cnblogs.com/XY-Heruo/p/15348521.html#:~:text=CentOS7%E5%8D%87%E7%BA%A7python3%E5%88%B0%E6%9C%80%E6%96%B0%E7%89%88%201%20%E9%A6%96%E5%85%88%EF%BC%8C%E4%BB%8Epython%E5%AE%98%E7%BD%91%E4%B8%8B%E8%BD%BD%E6%9C%80%E6%96%B0%E7%89%88%E7%9A%84python%E5%8E%8B%E7%BC%A9%E5%8C%85%E3%80%82%20%E6%9C%AC%E4%BA%BA%E4%B8%8B%E8%BD%BD%E7%9A%84%E6%98%AFPython-3.9.7.tar.xz%202,%E8%A7%A3%E5%8E%8B%E5%90%8E%E5%88%87%E6%8D%A2%E5%88%B0%E8%A7%A3%E5%8E%8B%E5%8C%85%E7%9B%AE%E5%BD%95%EF%BC%8C%E8%BF%9B%E8%A1%8C%E9%A2%84%E7%BC%96%E8%AF%91%20-%3E%20%E7%BC%96%E8%AF%91%20-%3E%20%E7%BC%96%E8%AF%91%E5%AE%89%E8%A3%85

## 如何让普通用户具有sudo权限

### 方法1 修改配置文件

```sh
# 1. 进入root用户
su root 
# 2. 进入etc目录
cd /etc/
# 3. vim sudoers找到 root ALL=(ALL) ALL
vim sudoers
# 4. 在 root ALL=(ALL) ALL 后面加上一行 user_name(要添加的普通用户名) ALL=(ALL) ALL
user_name ALL=(ALL) ALL
# 5. 保存退出
:wq
```

* 第一个 ALL 指示允许从任何终端、机器访问 sudo
* 第二个 (ALL) 指示 sudo 命令被允许以任何用户身份执行
* 第三个 ALL表示所有命令都可以作为 root 执行

### 方法2 修改用户组

* 在sudoers中看到 %wheel ALL=（ALL）ALL； 所以我们到  /etc/group中修改组成员。也可实现给用户 增加 sudo权限。

1. 使用命令加入组成员

```sh
usermod -aG wheel your_user_name
```

2. 修改配置文件

```sh
vim /etc/group
# 在wheel组的后面的成员列表里面添加进想要添加的用户名：wheel：x:10:root,yourusername
```

### 如何让普通用户输入sudo命令后避免输入密码验证

将组成员权限修改
```sh
## Same thing without a password
%wheel  ALL=(ALL)   NOPASSWD: ALL

```

## 更改pip源

创建pip.conf配置文件

在用户根目录(，而非系统根目录 / )下添加配置/.pip/pip.conf目录添加可信源，如果目录文件不存在，可直接创建。
```sh
mkdir ~/.pip   #创建文件夹

cd ~/.pip        #进入目录
vim pip.conf        #编辑配置文件
```
替换阿里镜像源(或其他镜像源)
```sh
[global]
trusted-host = mirrors.aliyun.com
index-url = https://mirrors.aliyun.com/pypi/simple

[install]
trusted-host=mirrors.aliyun.com
```

```sh
[root@centos7 .pip]# cat ~/.pip/pip.conf.bak 
[global]
index-url = http://mirrors.tencentyun.com/pypi/simple
trusted-host = mirrors.tencentyun.com
[root@centos7 .pip]#
```

## vim 默认配置


```sh
# centos
[root@centos7 c]# vim /etc/vimrc
# ubuntu
[root@ubunut c]# vim /etc/vim/vimrc
# 将以下内容追加到配置文件中
set nocompatible
set nu
set ic
set hlsearch
set encoding=utf-8
set fileencodings=utf-8,ucs-bom,GB2312,big5
set autoindent
set smartindent
set scrolloff=2
set showmatch
set shiftwidth=4
set tabstop=4
set showmatch
set cursorline
set autoread
syntax on
```

## 更改ip配置
```sh
# 打开配置文件
vi /etc/sysconfig/network-scripts/ifcfg-ens33

# 修改配置
BOOTPROTO="static"
ONBOOT="yes"
IPADDR=192.168.58.135
NETMASK=255.255.255.0
GATEWAY=192.168.58.2
DNS1=192.168.58.2

# 重启服务
systemctl restart network
```

## yum镜像修改

```sh

1. 首先备份/etc/yum.repos.d/CentOS-Base.repo
mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo.backup

2. 从下方镜像源列表选择要使用的镜像源
vim /etc/yum.repos.d/CentOS-Base.repo

3. 运行以下命令生成缓存
yum clean all
yum makecache
yum update
```



### 网易源


>http://mirrors.163.com/.help/centos.html

CentOS7-Base-163.repo
```repo
# CentOS-Base.repo
#
# The mirror system uses the connecting IP address of the client and the
# update status of each mirror to pick mirrors that are updated to and
# geographically close to the client.  You should use this for CentOS updates
# unless you are manually picking other mirrors.
#
# If the mirrorlist= does not work for you, as a fall back you can try the 
# remarked out baseurl= line instead.
#
#
[base]
name=CentOS-$releasever - Base - 163.com
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=os
baseurl=http://mirrors.163.com/centos/$releasever/os/$basearch/
gpgcheck=1
gpgkey=http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-7

#released updates
[updates]
name=CentOS-$releasever - Updates - 163.com
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=updates
baseurl=http://mirrors.163.com/centos/$releasever/updates/$basearch/
gpgcheck=1
gpgkey=http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-7

#additional packages that may be useful
[extras]
name=CentOS-$releasever - Extras - 163.com
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=extras
baseurl=http://mirrors.163.com/centos/$releasever/extras/$basearch/
gpgcheck=1
gpgkey=http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-7

#additional packages that extend functionality of existing packages
[centosplus]
name=CentOS-$releasever - Plus - 163.com
baseurl=http://mirrors.163.com/centos/$releasever/centosplus/$basearch/
gpgcheck=1
enabled=0
gpgkey=http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-7

```
### 清华源
```repo
#CentOS-Base.repo
#
# The mirror system uses the connecting IP address of the client and the
# update status of each mirror to pick mirrors that are updated to and
# geographically close to the client.  You should use this for CentOS updates
# unless you are manually picking other mirrors.
#
# If the mirrorlist= does not work for you, as a fall back you can try the
# remarked out baseurl= line instead.
#
#

[base]
name=CentOS-$releasever - Base
baseurl=https://mirrors.tuna.tsinghua.edu.cn/centos/$releasever/os/$basearch/
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=os
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7

#released updates
[updates]
name=CentOS-$releasever - Updates
baseurl=https://mirrors.tuna.tsinghua.edu.cn/centos/$releasever/updates/$basearch/
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=updates
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7

#additional packages that may be useful
[extras]
name=CentOS-$releasever - Extras
baseurl=https://mirrors.tuna.tsinghua.edu.cn/centos/$releasever/extras/$basearch/
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=extras
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7

#additional packages that extend functionality of existing packages
[centosplus]
name=CentOS-$releasever - Plus
baseurl=https://mirrors.tuna.tsinghua.edu.cn/centos/$releasever/centosplus/$basearch/
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=centosplus
gpgcheck=1
enabled=0
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7

```
### 阿里源
```repo
# CentOS-Base.repo
#
# The mirror system uses the connecting IP address of the client and the
# update status of each mirror to pick mirrors that are updated to and
# geographically close to the client.  You should use this for CentOS updates
# unless you are manually picking other mirrors.
#
# If the mirrorlist= does not work for you, as a fall back you can try the 
# remarked out baseurl= line instead.
#
#
 
[base]
name=CentOS-$releasever - Base - mirrors.aliyun.com
failovermethod=priority
baseurl=http://mirrors.aliyun.com/centos/$releasever/os/$basearch/
        http://mirrors.aliyuncs.com/centos/$releasever/os/$basearch/
        http://mirrors.cloud.aliyuncs.com/centos/$releasever/os/$basearch/
gpgcheck=1
gpgkey=http://mirrors.aliyun.com/centos/RPM-GPG-KEY-CentOS-7
 
#released updates 
[updates]
name=CentOS-$releasever - Updates - mirrors.aliyun.com
failovermethod=priority
baseurl=http://mirrors.aliyun.com/centos/$releasever/updates/$basearch/
        http://mirrors.aliyuncs.com/centos/$releasever/updates/$basearch/
        http://mirrors.cloud.aliyuncs.com/centos/$releasever/updates/$basearch/
gpgcheck=1
gpgkey=http://mirrors.aliyun.com/centos/RPM-GPG-KEY-CentOS-7
 
#additional packages that may be useful
[extras]
name=CentOS-$releasever - Extras - mirrors.aliyun.com
failovermethod=priority
baseurl=http://mirrors.aliyun.com/centos/$releasever/extras/$basearch/
        http://mirrors.aliyuncs.com/centos/$releasever/extras/$basearch/
        http://mirrors.cloud.aliyuncs.com/centos/$releasever/extras/$basearch/
gpgcheck=1
gpgkey=http://mirrors.aliyun.com/centos/RPM-GPG-KEY-CentOS-7
 
#additional packages that extend functionality of existing packages
[centosplus]
name=CentOS-$releasever - Plus - mirrors.aliyun.com
failovermethod=priority
baseurl=http://mirrors.aliyun.com/centos/$releasever/centosplus/$basearch/
        http://mirrors.aliyuncs.com/centos/$releasever/centosplus/$basearch/
        http://mirrors.cloud.aliyuncs.com/centos/$releasever/centosplus/$basearch/
gpgcheck=1
enabled=0
gpgkey=http://mirrors.aliyun.com/centos/RPM-GPG-KEY-CentOS-7
 
#contrib - packages by Centos Users
[contrib]
name=CentOS-$releasever - Contrib - mirrors.aliyun.com
failovermethod=priority
baseurl=http://mirrors.aliyun.com/centos/$releasever/contrib/$basearch/
        http://mirrors.aliyuncs.com/centos/$releasever/contrib/$basearch/
        http://mirrors.cloud.aliyuncs.com/centos/$releasever/contrib/$basearch/
gpgcheck=1
enabled=0
gpgkey=http://mirrors.aliyun.com/centos/RPM-GPG-KEY-CentOS-7
```

## 一键更换国内源

> https://github.com/SuperManito/LinuxMirrors

### 下载安装

```sh
bash <(curl -sSL https://gitee.com/SuperManito/LinuxMirrors/raw/main/ChangeMirrors.sh)
```

### 使用方法

1. 完整复制上面的命令到终端按回车键即可执行，若无法安装 curl 软件包可复制源码到本地后手动执行

2. 为了适配所有环境，建议使用 Root 用户执行脚本，切换命令为 sudo -i ，如遇报错请查看常见问题与帮助

3. 如果您使用的环境没有安装或不支持简体中文环境，请通过 SSH客户端工具 使用，否则将无法正确选择交互内容

4. 执行脚本过程中会自动备份原有源无需手动备份，期间会在终端输出多个主观选择交互内容，可按回车键快速确定

5. 脚本支持在原有源配置错误或者不存在的情况下使用，并且可以重复使用；脚本变更的软件源默认使用 HTTP 协议

### 脚本执行流程

1. 选择国内源 交互
    + 检测如果是 RHEL或CentOS 系统选择是否安装/覆盖 EPEL 扩展国内源 交互

2. 选择软件源使用的 WEB 协议 交互

3. 检测 防火墙 和 SELINUX 如果开启并且系统是 RHEL或CentOS 选择是否关闭 交互

4. 备份原有源
    + 检测如果存在重复的备份文件选择是否覆盖 交互

5. 更换国内源

6. 选择是否更新软件包 交互

    + 选择是否清理已下载的软件包缓存 交互
```sh

```