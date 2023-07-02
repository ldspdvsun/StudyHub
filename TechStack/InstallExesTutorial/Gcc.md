## yum 安装

通过以下命令安装 gcc，该命令下安装的版本为 4.8.5，版本较低：

```sh
yum -y install gcc gcc-c++ kernel-devel
```

## 升级

### 安装 centos-release-scl

```sh
yum install -y centos-release-scl
```

### 安装 devtoolset

以下为 8 版本的安装，如果安装 7 版本将数字改为 7 即可：

```sh
yum install -y devtoolset-8-gcc*
```

### 激活 devtoolset

```sh
scl enable devtoolset-8 bash
```

### 查看版本

执行命令：

```sh
gcc -v
如果显示如下说明安装成功：
gcc version 8.3.1 20190311 (Red Hat 8.3.1-3) (GCC)
```

## 设置开机启动

可以通过两种方式设置开机启动。

### 配置自启动文件

1. 安装的 devtoolset 在 /opt/rh 目录下，编辑文件：

```sh
vi /etc/profile.d/gcc.sh
```

2. 填写以下内容后保存：

```sh
source /opt/rh/devtoolset-8/enable
```

3. 执行命令：

```sh
chmod +x /etc/profile.d/gcc.sh
source /etc/profile.d/gcc.sh
```

## 问题及解决方案
```sh
[root@SqaServer fio-fio-3.32]# fio fio-test.ini > fio-test.txt
fio: engine libaio not loadable
fio: failed to load engine
# 安装依赖
[root@SqaServer fio-fio-3.32]# yum install -y libaio-devel
```

## 环境插件安装

> https://blog.csdn.net/m0_47696151/article/details/123519481