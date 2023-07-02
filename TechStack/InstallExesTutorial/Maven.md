
## 创建文件夹，存放下载的maven压缩包

```sh
[root@Centos8 ~]# cd /usr/local/
[root@Centos8 local]# mkdir maven
[root@Centos8 local]# cd maven/
[root@Centos8 maven]# ll
总用量 0
[root@Centos8 maven]# pwd
/usr/local/maven
```

## 从官网下载maven压缩包

```sh
[root@Centos8 maven]# wget https://dlcdn.apache.org/maven/maven-3/3.8.6/binaries/apache-maven-3.8.6-bin.tar.gz
[root@Centos8 maven]# ll
总用量 8476
-rw-r--r-- 1 root root 8676320 6月   7 00:45 apache-maven-3.8.6-bin.tar.gz
```

## 解压

```sh
[root@Centos8 maven]# tar -zxvf apache-maven-3.8.6-bin.tar.gz
[root@Centos8 maven]# ll
总用量 8476
drwxr-xr-x 6 root root      99 9月  20 11:41 apache-maven-3.8.6
-rw-r--r-- 1 root root 8676320 6月   7 00:45 apache-maven-3.8.6-bin.tar.gz
```

## 编辑配置文件，添加下面变量，配置maven环境

```sh
#MAVEN_ENV
MAVEN_HOME=/usr/local/maven/apache-maven-3.8.6
export PATH=${MAVEN_HOME}/bin:${PATH}
[root@Centos8 maven]# vim /etc/profile
[root@Centos8 maven]# pwd
/usr/local/maven
[root@Centos8 maven]# vim /etc/profile
```

## 重新加载配置文件

```sh
[root@Centos8 maven]# source /etc/profile
```

## 测试maven是否配置成功

```sh
[root@Centos8 maven]# mvn -v
Apache Maven 3.8.6 (84538c9988a25aec085021c365c560670ad80f63)
Maven home: /usr/local/maven/apache-maven-3.8.6
Java version: 1.8.0_341, vendor: Oracle Corporation, runtime: /usr/local/java/jdk8/jre
Default locale: zh_CN, platform encoding: UTF-8
OS name: "linux", version: "4.18.0-193.14.2.el8_2.x86_64", arch: "amd64", family: "unix"
```

## 编辑配置文件，修改镜像位置和仓库位置

```yml
    <mirror>
          <id>nexus-aliyun</id>
          <mirrorOf>*,!jeecg,!jeecg-snapshots</mirrorOf>
          <name>Nexus aliyun</name>
          <url>http://maven.aliyun.com/nexus/content/groups/public</url>
    </mirror>
    
    <localRepository>/usr/local/maven/repository</localRepository>
```

```sh
[root@Centos8 maven]# vim /usr/local/maven/apache-maven-3.8.6/conf/settings.xml
[root@Centos8 maven]# mkdir repository
[root@Centos8 maven]# ll
总用量 8476
drwxr-xr-x 6 root root      99 9月  20 11:41 apache-maven-3.8.6
-rw-r--r-- 1 root root 8676320 6月   7 00:45 apache-maven-3.8.6-bin.tar.gz
drwxr-xr-x 2 root root       6 9月  20 11:51 repository
[root@Centos8 maven]# pwd
/usr/local/maven
[root@Centos8 maven]# mvn -v
Apache Maven 3.8.6 (84538c9988a25aec085021c365c560670ad80f63)
Maven home: /usr/local/maven/apache-maven-3.8.6
Java version: 1.8.0_341, vendor: Oracle Corporation, runtime: /usr/local/java/jdk8/jre
Default locale: zh_CN, platform encoding: UTF-8
OS name: "linux", version: "4.18.0-193.14.2.el8_2.x86_64", arch: "amd64", family: "unix"
[root@Centos8 maven]#
```