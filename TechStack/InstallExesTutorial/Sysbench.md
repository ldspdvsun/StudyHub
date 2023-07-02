## 安装sysbench

1. 进入到sysbench源码目录/tmp/soft/sysbench-1.0.20

```sh
[root@centos7 sysbench-1.0.20]# 
```

2. 执行autogen.sh用它来生成configure这个文件

```sh
[root@centos7 sysbench-1.0.20]# ./autogen.sh
```

3. 执行configure && make && make install 来完成sysbench的安装

```sh
[root@centos7 sysbench-1.0.20]# ./configure --prefix=/usr/local/sysbench/ --with-mysql --with-mysql-includes=/data/software/mysql8/include --with-mysql-libs=/data/software/mysql8/lib
[root@centos7 sysbench-1.0.20]# make
[root@centos7 sysbench-1.0.20]# make install
我这里之所以要这样写是因为我的mysql安装在/data/software/mysql8/；而不是默认的rpm的安装位置
```

4. 测试是否安装成功：

```sh
[root@centos7 sysbench-1.0.20]# /usr/local/sysbench/bin/sysbench --version
sysbench 1.0.20
到目前为止sysbench的安装就算是完成了！
```
 
## MySQL测试

> 默认已经安装好MySQL

```sh
./autogen.sh
./configure
```

#ERROR: cannot find MySQL libraries. If you want to compile with MySQL support 没找到mysql库 需要用参数指定下 --with-mysql-includes和--with-mysql-libs

如何查找mysql的安装路径？

```sh
安装mysql-devel，使用mysql_config查看mysql的安装路径
yum install -y mysql-devel
mysql_config -help
```

再次执行./configure，成功。
```sh
./configure --with-mysql-includes=/usr/include/mysql --with-mysql-libs=/usr/lib64/mysql
make
make install
使用如下命令测试是否安装成功

sysbench --version
```

## 参考链接

> https://longsheng.org/post/14886.html

> https://blog.csdn.net/weixin_41561862/article/details/84651301
 
## 执行./autogen.sh过程可能会遇到如下错误

```sh
[root@SqaServer sysbench-1.0.20]# ./autogen.sh
automake 1.10.x (aclocal) wasn't found, exiting
[root@SqaServer sysbench-1.0.20]# ./autogen.sh
libtoolize 1.4+ wasn't found, exiting

# 解决方法
[root@SqaServer sysbench-1.0.20]# yum install -y automake
[root@SqaServer sysbench-1.0.20]# yum install -y libtool
```

执行./configure出现错误
```sh
# 问题
cannot find MySQL client libraries
# 解决方法，安装依赖
[root@SqaServer sysbench-1.0.20]# sudo yum install mysql-devel
# 执行./configure，如果还不行，执行
[root@centos7 sysbench-1.0.20]# ./configure --prefix=/usr/local/sysbench/ --with-mysql --with-mysql-includes=/data/software/mysql8/include 
```