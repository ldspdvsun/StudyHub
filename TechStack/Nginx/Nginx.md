# 需求分析

|序号|需求简述|完成情况|备注|
|---|---|---|---|
|1|Ubuntu系统安装docker|完成||
|2|docker部署容器（ahmadnassri/vscode-server:latest）|完成||
|3|为公网IP申请ssl证书| 完成| 目前支持公网IP的ssl证书只找到zerossl|
|4|部署nginx配置ssl|完成| zerossl申请时，需要先通过访问公网IP验证是否加载提供的txt文件，<br />暂时未完全掌握|
|5|为docker部署的容器成功运行后的端口开启反向代理|完成||
|6|为端口加入认证服务|完成||


# 基本需求软件及版本分析

|软件名称|版本|
|---|---|
|Ubuntu|20.04 LTS|
|Docker|20.10.5|
|nginx|1.18.0|
## Ubuntu版本信息

```sh
root@VM-24-11-ubuntu:~# lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 20.04 LTS
Release:	20.04
Codename:	focal
root@VM-24-11-ubuntu:~# 
root@VM-24-11-ubuntu:~# uname -a
Linux VM-24-11-ubuntu 5.4.0-42-generic #46-Ubuntu SMP Fri Jul 10 00:24:02 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
root@VM-24-11-ubuntu:~# uname -v
#46-Ubuntu SMP Fri Jul 10 00:24:02 UTC 2020
root@VM-24-11-ubuntu:~# cat /etc/os-release 
NAME="Ubuntu"
VERSION="20.04 LTS (Focal Fossa)"
ID=ubuntu
ID_LIKE=debian
PRETTY_NAME="Ubuntu 20.04 LTS"
VERSION_ID="20.04"
HOME_URL="https://www.ubuntu.com/"
SUPPORT_URL="https://help.ubuntu.com/"
BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
VERSION_CODENAME=focal
UBUNTU_CODENAME=focal
root@VM-24-11-ubuntu:~# 
```

## Docker版本信息

```sh
root@VM-24-11-ubuntu:~# docker version
Client: Docker Engine - Community
 Version:           20.10.5
 API version:       1.41
 Go version:        go1.13.15
 Git commit:        55c4c88
 Built:             Tue Mar  2 20:18:20 2021
 OS/Arch:           linux/amd64
 Context:           default
 Experimental:      true

Server: Docker Engine - Community
 Engine:
  Version:          20.10.5
  API version:      1.41 (minimum version 1.12)
  Go version:       go1.13.15
  Git commit:       363e9a8
  Built:            Tue Mar  2 20:16:15 2021
  OS/Arch:          linux/amd64
  Experimental:     false
 containerd:
  Version:          1.4.4
  GitCommit:        05f951a3781f4f2c1911b05e61c143e9c30eaa8e
 runc:
  Version:          1.0.0-rc93
  GitCommit:        12644e614e25b05da6fd34a38ffa0cfe1903fdec
 docker-init:
  Version:          0.19.0
  GitCommit:        de40ad0
root@VM-24-11-ubuntu:~# 
```

## Nginx版本信息

```sh
root@VM-24-11-ubuntu:~# nginx -v
nginx version: nginx/1.18.0 (Ubuntu)
```

# 实现步骤

## docker部署

> 默认已经部署完成

```sh
bash <(curl -sSL https://gitee.com/SuperManito/LinuxMirrors/raw/main/DockerInstallation.sh)
```

## 镜像部署

> 本次部署镜像为ahmadnassri/vscode-server:latest，如需其他镜像部署，方法一样

```sh
docker run -d \
 --privileged \
 --restart=always \
 --name vscode-server \
 -p Port2:8000 \
 -e PASSWORD=code-server \
 -e SUDO_PASSWORD=root \
 -e VSCODE_KEYRING_PASS="vscode" \
 -e VSCODE_SERVE_MODE=serve-local \
 -v /data/docker/vscode-server:/root/code/vscode-server \
 ahmadnassri/vscode-server:latest
```

## Nginx部署

1. 安装Nginx

```sh
# 中途如有选项，默认即可
root@VM-24-11-ubuntu:~# sudo apt install nginx
root@VM-24-11-ubuntu:~# systemctl status nginx
● nginx.service - A high performance web server and a reverse proxy server
     Loaded: loaded (/lib/systemd/system/nginx.service; enabled; vendor preset: enabled)
     Active: active (running) since Tue 2023-03-21 16:14:50 CST; 3h 47min ago
       Docs: man:nginx(8)
   Main PID: 189929 (nginx)
      Tasks: 3 (limit: 4612)
     Memory: 7.0M
     CGroup: /system.slice/nginx.service
             ├─189929 nginx: master process /usr/sbin/nginx -g daemon on; master_process on;
             ├─189930 nginx: worker process
             └─189931 nginx: worker process

Mar 21 16:14:50 VM-24-11-ubuntu systemd[1]: Starting A high performance web server and a reverse proxy server...
Mar 21 16:14:50 VM-24-11-ubuntu systemd[1]: Started A high performance web server and a reverse proxy server.
root@VM-24-11-ubuntu:~# 
```

2. 修改Nginx配置文件

> 本配置文件将会监听80端口使得http的请求转发到https，另外监听443端口，并配置反向代理到自定义端口（18778）

    1. 配置文件位于：/etc/nginx/sites-available下的default

```yaml
server {
    listen 80;
    server_name IP;
    location / {
        proxy_pass http://127.0.0.1:Port1;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}

server {
    listen 443 ssl;
    server_name IP;

    ssl_certificate /etc/ssl/certs/certificate_ca_bundle.crt;
    ssl_certificate_key /etc/ssl/private/private.key;

    location / {
        proxy_pass http://127.0.0.1:Port2;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
	proxy_set_header Upgrade $http_upgrade;
	proxy_set_header Connection "upgrade";
	proxy_set_header Accept-Encoding gzip;
	proxy_http_version 1.1;
    }
}
```

    2. 重启nginx，并查看nginx状态
 
```sh
# 查看语法是否有误，无误后重启
root@VM-24-11-ubuntu:~# nginx -t
root@VM-24-11-ubuntu:~# sudo systemctl restart nginx
root@VM-24-11-ubuntu:~# systemctl status nginx
# 查看nginx状态无误后，可以设置nginx开机自启
root@VM-24-11-ubuntu:~# systemctl enable nginx
```

    3. Nginx安装注意事项

> 安装过程中可能出现端口占用的问题，可以通过如下命令查询到占用端口的进程，杀死进程后再重新尝试

```sh
root@VM-24-11-ubuntu:~# lsof -i:80
COMMAND    PID     USER   FD   TYPE  DEVICE SIZE/OFF NODE NAME
nginx   189929     root    6u  IPv4 1457821      0t0  TCP *:http (LISTEN)
nginx   189930 www-data    6u  IPv4 1457821      0t0  TCP *:http (LISTEN)
nginx   189931 www-data    6u  IPv4 1457821      0t0  TCP *:http (LISTEN)
root@VM-24-11-ubuntu:~# lsof -i:80 -P -t -sTCP:LISTEN
189929
189930
189931
root@VM-24-11-ubuntu:~# kill -9 18929

```

3. 卸载Nginx

```sh
sudo apt-get remove nginx
```

4. 删除Nginx以及配置文件

```sh
sudo apt-get purge nginx
sudo apt-get purge nginx nginx-common nginx-full

```

## SSL证书验证

1. ZeroSSL 证书申请

> https://zerossl.com

2. 验证域名

    选择网站 Web 访问的话，直接下载验证文件，然后上传到 IP 地址默认的 Web 目录(/var/www/html/)下，要求是路径保持如下：

```sh
ubuntu@ip-172-31-38-101:~$ cd /var/www/html/
ubuntu@ip-172-31-38-101:/var/www/html$ ls -a
.  ..  .well-known  index.nginx-debian.html
ubuntu@ip-172-31-38-101: cd .well-known/pki-validation
ubuntu@ip-172-31-38-101: pwd
/var/www/html/.well-known/pki-validation
ubuntu@ip-172-31-38-101: ls -a
.  ..  2F451152F65DFD149BDF7F23F4AJOL33.txt

```

3. 用你的浏览器打开 IP，保证可以访问到验证文件。

> https://www.51cto.com/article/708255.html

## 为端口加入认证服务

> 服务器对外提供的端口服务中如果没有权限验证机制可通过nginx的用户名密码认证来替代

1. 安装工具 apache2-utils

```sh
root@VM-24-11-ubuntu:~# sudo apt update
root@VM-24-11-ubuntu:~# sudo apt install apache2-utils
```

2. 生成配置文件

```sh
# 1.交互方式输入密码
root@VM-24-11-ubuntu:~# sudo htpasswd -c /etc/nginx/.htpasswd username
# 输入要设置的密码

# 2.直接设置密码
root@VM-24-11-ubuntu:~# sudo htpasswd -c /etc/nginx/.htpasswd username password
```

3. 修改nginx配置文件
```sh
server {
     listen 80;
     server_name IP;
     location / {
         auth_basic "Restricted Access";
         auth_basic_user_file /etc/nginx/.htpasswd;
         add_header Cache-Control "no-cache, private";
         proxy_pass http://127.0.0.1:PORT; # 转发请求到容器的端口
         proxy_set_header Host $host;
         proxy_set_header X-Real-IP $remote_addr;
     }
 }
```

4. 重启nginx
```sh
root@VM-24-11-ubuntu:~# sudo systemctl restart nginx
```
