## Centos8安装

### 确定python环境是否符合

```sh
[root@Centos8 locust]# python3 -V
Python 3.10.6
[root@Centos8 locust]# 
```

### 安装locust

```sh
[root@Centos8 lx]# cd locust
[root@Centos8 locust]# pwd
/opt/lx/locust
[root@Centos8 locust]# python3 install locust==2.15.0
```

### 确认是否安装成功

```sh
[root@Centos8 locust]# locust -V
locust 2.15.0
[root@Centos8 locust]#
```

## Windows10安装

### 确定python环境是否符合

```sh
PS D:\PycharmProjects\pythonProject> python -V 
Python 3.10.5
PS D:\PycharmProjects\pythonProject> pip install locust
```

### 安装locust

```sh
PS D:\PycharmProjects\pythonProject> pip install locust
```

### 确认是否安装成功

```sh
PS D:\PycharmProjects\pythonProject> locust -V
locust 2.12.1
PS D:\PycharmProjects\pythonProject> 
```

## 服务端运行

```sh
[root@Centos8 locust]# java -jar pinter.jar
<2022-09-22 19:17:18,165>[ INFO] HV000001: Hibernate Validator 6.0.14.Final - org.hibernate.validator.internal.util.Version
```

## 客户端运行
```sh
PS D:\PycharmProjects\pythonProject\locust> java -jar pinter.jar
```


