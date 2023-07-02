
## 创建文件夹，存放解压后的jdk文件

```sh
[root@Centos8 local]# pwd
/usr/local
[root@Centos8 local]# mkdir java
[root@Centos8 local]# cd java
[root@Centos8 java]# pwd
/usr/local/java
```

## 上传从JDK官网下载号的压缩包文件

```sh
[root@Centos8 java]# ll
-rw-r--r-- 1 root root 145424384 9月  20 08:56 jdk-8u341-linux-x64.tar.gz
```

## 解压jdk安装包

```sh
[root@Centos8 java]# tar -zxvf jdk-8u341-linux-x64.tar.gz(jdk安装包)
```

## 将解压后的jdk重命名

```sh
[root@Centos8 java]# mv jdk1.8.0_341 jdk8
```

## 给etc文件夹下的profile文件添加java运行环境

```sh
[root@Centos8 java]# vim /etc/profile
```

### 在文件末尾添加java运行环境

```sh
JAVA_HOME=/usr/local/java/jdk8
CALSS_PATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar:$JAR_HOME/lib
PATH=$JAVA_HOME/bin:$PATH
export JAVA_HOME CLASS_PATH PATH
```

### 将添加在文件中的配置信息马上生效

```sh
[root@Centos8 local]# source /etc/profile
```

## 检查是否安装成功

```sh
[root@Centos8 java]# java -version
java version "1.8.0_341"
Java(TM) SE Runtime Environment (build 1.8.0_341-b10)
Java HotSpot(TM) 64-Bit Server VM (build 25.341-b10, mixed mode)
[root@Centos8 java]#
```