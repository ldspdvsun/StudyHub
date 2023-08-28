
## 官方code-server

```sh
docker run -d \
 --restart=always \
 --name codercom-code-server \
 -p 18870:8080 \
 -e PASSWORD=code-server \
 -e SUDO_PASSWORD=root \
 --restart=always \
 -v /data/docker/codercom-code-server:/home/code/code-server \
 codercom/code-server:latest
```

## 第三方 vscode-server
```sh
docker run -d \
 --privileged \
 --restart=always \
 --name vscode-server \
 -p 18778:8000 \
 -e PASSWORD=code-server \
 -e SUDO_PASSWORD=root \
 -e VSCODE_KEYRING_PASS="vscode" \
 -e VSCODE_SERVE_MODE=serve-local \
 -v /data/docker/vscode-server:/root/code/vscode-server \
 ahmadnassri/vscode-server:latest
```

## 第三方 linuxserver

>https://hub.docker.com/r/linuxserver/code-server

```py
docker pull linuxserver/code-server

docker run -d \
  --name=code-server \
  -e PUID=1000 \
  -e PGID=1000 \
  -e TZ=Etc/UTC \
  -e PASSWORD=password `#optional` \
  -e HASHED_PASSWORD= `#optional` \
  -e SUDO_PASSWORD=password `#optional` \
  -e SUDO_PASSWORD_HASH= `#optional` \
  -e PROXY_DOMAIN=code-server.my.domain `#optional` \
  -e DEFAULT_WORKSPACE=/config/workspace `#optional` \
  -p 8443:8443 \
  -v /path/to/appdata/config:/config \
  --restart unless-stopped \
  lscr.io/linuxserver/code-server:latest

docker run -d \
  --privileged \
  --name=code-server \
  -e PUID=1000 \
  -e PGID=1000 \
  -e TZ=Etc/UTC \
  -e PASSWORD=code-server \
  -e SUDO_PASSWORD=code-server \
  -e DEFAULT_WORKSPACE=/config/workspace \
  -p 8443:8443 \
  -v /data/docker/linuxserver/config:/config \
  --restart unless-stopped \
  lscr.io/linuxserver/code-server:latest

```

## 配置

>https://code.visualstudio.com/docs/cpp/config-linux
 
## 修改登录密码

>https://blog.csdn.net/jmsLU/article/details/122488839

```SH
第一登录code-server编辑器时，需要输入密码，但是这个密码需要去配置文件中查看，配置文件地址如下：

/root/.config/code-server/config.yaml

当然，我们也可以直接修改config.yaml配置文件：

修改密码

# 首先需要进入code-server容器内部
 
$ docker container exec -it code-server /bin/bash
 
 
# 打开配置文件
 
$ vim /root/.config/code-server/config.yaml
 
 
# 修改密码 password 字段的值
 
# password 123456  设置密码为123456
 
 
# 如果 auth 字段 设置为 none  则没有密码
 
# auth none
 
# 退出容器
 
$ exit

注意： 修改完配置文件之后，需要重启docker容器

重启docker
```

## 官方镜像apt换源
```sh

切换为root
sudo su

1. 编辑源文件
cp /etc/apt/sources.list /etc/apt/sources.list.bak
nano /etc/apt/sources.list

2. 将以下内容替换原有内容
deb http://mirrors.163.com/debian/ bullseye main contrib non-free
deb http://mirrors.163.com/debian-security/ bullseye-security main contrib non-free

3. 保存退出
ctrl+o
enter
ctrl+x

4. 更新
apt-get update;apt-get upgrade
apt update;apt upgrade -y;apt dist-upgrade -y
```

## 必要插件安装

### vscode 初始化配置

```sh
gcc -v
sudo apt-get update
sudo apt-get install build-essential gdb
sudo apt-get install iputils-ping
sudo apt-get install net-tools
```

### gcc

```sh
root@6ec9ac246424:/home/coder# apt install -y build-essential
root@6ec9ac246424:/home/coder# gcc --version
gcc (Debian 10.2.1-6) 10.2.1 20210110
Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

root@6ec9ac246424:/home/coder#
```

### Python

>https://blog.csdn.net/bz0446/article/details/105500585

```sh
#检测可更新
sudo apt update
#用于添加ppa源的小工具，ubuntu server默认没装。
sudo apt install -y software-properties-common

#有确认提示按回车继续
sudo add-apt-repository ppa:deadsnakes/ppa

#搜索是否有需要的版本
sudo apt search python3.9
#安装
sudo apt install -y python3.9

python3 -V

#来查看python路径
$ whereis python 

#移除已有软连接
$ rm -rf /usr/bin/python 

# 增加新的软连接
$ ln -s /usr/bin/pip3 /usr/bin/pip
$ ln -s /usr/bin/python3 /usr/bin/python
```

### pip
```sh
sudo apt install curl
# 下载最新的官方 pip
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
# 安装 pip

python3 get-pip.py
```

### 更改pip源

1. 创建pip.conf配置文件

2. 在用户根目录(，而非系统根目录 / )下添加配置/.pip/pip.conf目录添加可信源，如果目录文件不存在，可直接创建。

```sh
mkdir ~/.pip   #创建文件夹

cd ~/.pip        #进入目录
vim pip.conf        #编辑配置文件
```

3. 替换阿里镜像源(或其他镜像源)

```sh
[global]
trusted-host = mirrors.aliyun.com
index-url = https://mirrors.aliyun.com/pypi/simple

[install]
trusted-host=mirrors.aliyun.com
```

### nano
```sh
apt-get install nano -y
```

## 代码提示

### C/C++

>https://blog.csdn.net/houxian1103/article/details/122165460


## 扩展安装

>https://marketplace.visualstudio.com/vscode

## VsCode新建自定义输入代码模板

1. 文件 -> 首选项 -> 配置用户代码片段-> 全局/C

2. 自定义输入

```json
{
	// Place your snippets for c here. Each snippet is defined under a snippet name and has a prefix, body and 
	// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the 
	// same ids are connected.
	// Example:
	// "Print to console": {
	// 	"prefix": "log",
	// 	"body": [
	// 		"console.log('$1');",
	// 		"$2"
	// 	],
	// 	"description": "Log output to console"
	// }
	"cmain": {
		"prefix": "cmain",
		"body": [
			"/**\n * $1\n */\n",
			"#include <stdio.h>\n#include <string.h>\n\n$2\n",
			"int main()",
			"{\n\t$0",
			"\treturn 0;",
			"}"
		],
		"description": "c stand main output"
	},
	"pf": {
		"prefix": "pf",
		"body": [
			"printf(\"$1\\n\");\n$0"
		],
		"description": "print with \\n"
	},
	"prf": {
		"prefix": "prf",
		"body": [
			"printf(\"$1 %$2\\n\", $3);\n$0"
		],
		"description": "print with %d \n"
	},
	"scf": {
		"prefix": "scf",
		"body": [
			"scanf(\"%$1\", &$2);\n$0"
		],
		"description": "scanf with %d \n"
	}
}
```

## 参考链接

>安装步骤https://blog.csdn.net/never_late/article/details/126964024

>apt换源https://blog.csdn.net/weixin_58191539/article/details/125298034

>教程https://www.cnblogs.com/anliven/p/13363811.html
