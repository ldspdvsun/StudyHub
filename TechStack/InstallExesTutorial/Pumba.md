## 下载
```sh
[admin@Centos8 lx]$ wget https://download.fastgit.org/alexei-led/pumba/releases/download/0.9.0/pumba_linux_amd64
[admin@Centos8 lx]$ ll
-rw-rw-r--  1 admin admin  14637627 12月  8 2021 pumba_linux_amd64
```sh

## 重命名

```sh
[admin@Centos8 lx]$ mv pumba_linux_amd64 pumba
```

## 复制到/usr/local/bin/目录下

```sh
[admin@Centos8 lx]$ sudo cp pumba /usr/local/bin/pumba
```

## 赋予执行权限

```sh
[admin@Centos8 lx]$ sudo chmod 777 /usr/local/bin/pumba 
```

## 测试是否安装成功

```sh
[admin@Centos8 lx]$ pumba -v
Pumba version 0.9.0 - 2e7ab7b (master) 2021-11-21T10:12:49+0200
[admin@Centos8 lx]$ 
```

## 参考教程

> https://github.com/alexei-led/pumba