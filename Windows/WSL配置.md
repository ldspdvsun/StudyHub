# 先决条件

    必须运行 Windows 10 版本 2004 及更高版本（内部版本 19041 及更高版本）或 Windows 11 才能使用以下命令。如果使用的是更早的版本，请参阅[手动安装页](https://learn.microsoft.com/zh-cn/windows/wsl/install-manual)。

## 更新WSL

```shell
$ wsl.exe --update
```

## 修改配置文件

装完WSL后，查看任务管理器时发现vmmem进程占用内存过高。WSL内存默认值是电脑内存的一半，CPU默认值是电脑处理器个数，swap空间默认值是电脑内存的四分之一。

```sh
# 查看wsl版本
wsl -l -v
# 查看正在wsl中运行的linux发行版
wsl --list --running
# 关闭所有正在wsl中运行的linux发行版
wsl --shutdown
```

.wslconfig文件路径：

.wslconfig文件存放于当前用户的目录，即绝对路径为C:\Users\你的用户名.wslconfig，没有的话就新建一个。
也可以打开文件管理器后，在地址栏输入%UserProfile%跳转至用户目录，再新建或编辑.wslconfig文件。
修改.wslconfig配置文件（根据自己电脑配置修改）

```sh
# Settings apply across all Linux distros running on WSL 2
[wsl2]

# Limits VM memory to use no more than 2 GB, this can be set as whole numbers using GB or MB
memory=4GB 

# Sets the VM to use two virtual processors
processors=4

# Sets amount of swap storage space to 2GB, default is 25% of available RAM
swap=4GB

# Sets swapfile path location, default is %USERPROFILE%\AppData\Local\Temp\swap.vhdx
# swapfile=C:\\temp\\wsl-swap.vhdx
```

以上文件改好后，在powershell中执行以下代码，以重启wsl2，使得配置生效。

```sh
wsl --shutdown
```

# 查看可支持版本

```shell
$ wsl --list --online
以下是可安装的有效分发的列表。
使用 'wsl.exe --install <Distro>' 安装。

NAME                                   FRIENDLY NAME
Ubuntu                                 Ubuntu
Debian                                 Debian GNU/Linux
kali-linux                             Kali Linux Rolling
Ubuntu-18.04                           Ubuntu 18.04 LTS
Ubuntu-20.04                           Ubuntu 20.04 LTS
Ubuntu-22.04                           Ubuntu 22.04 LTS
Ubuntu-24.04                           Ubuntu 24.04 LTS
OracleLinux_7_9                        Oracle Linux 7.9
OracleLinux_8_7                        Oracle Linux 8.7
OracleLinux_9_1                        Oracle Linux 9.1
openSUSE-Leap-15.5                     openSUSE Leap 15.5
SUSE-Linux-Enterprise-Server-15-SP4    SUSE Linux Enterprise Server 15 SP4
SUSE-Linux-Enterprise-15-SP5           SUSE Linux Enterprise 15 SP5
openSUSE-Tumbleweed                    openSUSE Tumbleweed
```

# 安装WSL

## 管理员模式进入Power Shell，默认安装的为Ubuntu

```shell
# 默认安装
$ wsl --install

# 指定版本
$ wsl --install -d <Distrubution Name>
```

> 安装过程要求输入用户名，用户名不能大写；
>
> 如果安装失败，无法解析服务器的名称或地址。可以考虑 更改DNS为114.114.114.114,8.8.8.8
> 这里建议更改DNS。

## 查看当前状态

```shell
$ wsl -l -v
  NAME      STATE           VERSION
* Ubuntu    Running         2
```

# 更改安装位置

## 查看要迁移的系统名称

```sh
$ wsl -l
适用于 Linux 的 Windows 子系统分发:
Ubuntu (默认)
```

## 创建目标目录并导出

```sh
$ mkdir D:\WSL\backup
$ cd D:\WSL\backup
$ wsl --export Ubuntu ./Ubuntu.tar
正在导出，这可能需要几分钟时间。
操作成功完成
```

## 注销正在运行的系统

```sh
$ wsl --unregister Ubuntu-20.04
正在注销。
操作成功完成。
```

## 导入系统

```sh
# wsl --import (发行版) (安装位置) (文件路径以及文件名称)
$ wsl --import Ubuntu-20.04 D:\WSL\Ubuntu D:\WSL\backup\Ubuntu.tar
正在导入，这可能需要几分钟时间。
操作成功完成。
```

# 更改默认登录用户名

## 管理员权限打开powershell，关掉子系统

```sh
wsl --shutdown
```

## 设置默认用户

```sh
<wsl> config --default-user <username>

Ubuntu config --default-user username
```
