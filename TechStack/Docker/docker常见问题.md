## docker 运行直接报错

> WARNING: IPv4 forwarding is disabled. Networking will not work.

### 第一步：在宿主机上执行

```sh
[root@localhost /]# echo "net.ipv4.ip_forward=1" >>/usr/lib/sysctl.d/00-system.conf
```

### 第二步：重启network和docker服务

```sh
[root@localhost /]# systemctl restart network && systemctl restart docker
```

### 第三步：验证是否成功

## Docker已存在的容器,怎么添加新端口号

### 查看容器端口映射情况

```sh
docker port 容器ID
```

[![image.png](https://i.postimg.cc/3J5GjLtm/image.png)](https://postimg.cc/QVmVhqGd)

### 查询容器在本机位置

```sh
docker inspect 容器ID | grep 容器ID
```

[![image.png](https://i.postimg.cc/25v0zH8w/image.png)](https://postimg.cc/JyrNx5XD)

+ 进入容器目录需修改2个文件
    + config.v2.json
    + hostconfig.json
    
### 备份原始配置

为了保证安全,我们修改配置后容器出问题,建议把之前的配置文件备份下:

[![image.png](https://i.postimg.cc/h45sFWKm/image.png)](https://postimg.cc/F103c6dF)

备份文件

[![image.png](https://i.postimg.cc/pLwKWzTY/image.png)](https://postimg.cc/nX1XTsqC)

如果容器运行出问题就把备份文件名称后面的.bak去掉

### 关闭docker进程

```sh
$ service docker stop
或
$ systemctl stop docker
```

运行完关闭命令后查看

[![image.png](https://i.postimg.cc/pXh1dQCp/image.png)](https://postimg.cc/bsPRCtKh)

再次查看docker进程是否还在运行

```sh
ps -aux | grep docker
```

[![image.png](https://i.postimg.cc/65x2gt8T/image.png)](https://postimg.cc/w3FjsKcd)

**注意：此时由上述命令运行结果可以看出没有在运行，就不要再运行Docker的命令，不然程序会自动启动**

### 修改配置文件

#### 修改config.v2.json

1. 修改config.v2.json 查看内部json数据

[![image.png](https://i.postimg.cc/3r9rL5DQ/image.png)](https://postimg.cc/w3ydvrVw)

2. 可以把json复制到在线网站去格式化，看起来美观些,格式化后我们找到Config->ExposedPorts里面添加想要的端口号格式为

```sh
$ "自己需要的端口/tcp"
```

[![image.png](https://i.postimg.cc/9Mm0MWq1/image.png)](https://postimg.cc/nsWpSf2Q)

3. 修改到配置文件中

[![image.png](https://i.postimg.cc/vm3g5gyC/image.png)](https://postimg.cc/WDq1v4h7)

#### 修改配置 hostconfig.json

1. 修改 vim hostconfig.json 查看内部json数据
2. 找到 PortBindings 参数内添加信息

[![image.png](https://i.postimg.cc/VsjRbgTh/image.png)](https://postimg.cc/Wt1rBGsm)

3. 修改自己需要绑定的端口信息，格式为

```sh
"容器内部的端口/tcp":[
    {
        "HostIp": "",
        "HostPort": "绑定宿主机的端口"
    }
]
```

[![image.png](https://i.postimg.cc/y6y1xJhH/image.png)](https://postimg.cc/MXX2rprP)

4. 配置信息后添加保存

[![image.png](https://i.postimg.cc/vmKzWHW8/image.png)](https://postimg.cc/3ygmhhSz)

### 启动Docker

```sh
service docker start
或
systemctl restart docker 
```

### 查看容器端口映射信息

```sh
docker port 容器ID
```

[![image.png](https://i.postimg.cc/13QC7tnv/image.png)](https://postimg.cc/4mWQmX1c)

## 一键安装

```sh
bash <(curl -sSL https://gitee.com/SuperManito/LinuxMirrors/raw/main/DockerInstallation.sh)
```

### 参考链接

>https://blog.csdn.net/qq_45502336/article/details/126135157

[![image.png](https://i.postimg.cc/76CcTbYt/image.png)](https://postimg.cc/zbrpszhT)

## docker cli部署的容器和docker compose部署的容器(自定义网络)，双方内部如何才能互相ping通

> Docker CLI 部署的容器和 Docker Compose 部署的容器，内部网络默认是使用 Docker 网桥，它们在同一个网络中，因此可以相互访问。假设有一个由 Docker Compose 部署的容器应用程序(自定义网络)，它的服务名为 web，暴露了一个 HTTP 服务。现在我们想从由 Docker CLI 部署的容器中访问该服务。

### 确定 Docker Compose 容器所在的网络

Docker Compose 会为应用程序创建一个默认网络。我们可以使用以下命令来查看该网络：

```sh
docker network ls
```
1. 找到应用程序的网络名称，例如 myapp_default。

```sh
root@VM-24-11-ubuntu:/data/docker/mysql# docker-compose up -d
Creating network "mysql_default" with the default driver
Creating mysql_phpmyadmin_1 ... done
Creating mysql_db_1         ... done
root@VM-24-11-ubuntu:/data/docker/mysql# docker network ls

NETWORK ID     NAME                DRIVER    SCOPE
20f53b127fad   bridge              bridge    local
667cea2f4d50   host                host      local
6051526b2b77   mysql_default       bridge    local
eb37be31f571   none                null      local
d5453e31729c   wordpress_default   bridge    local
```

### 连接到 Docker Compose 容器所在的网络

使用以下命令连接到 Docker Compose 容器所在的网络：

```sh
docker network connect myapp_default <docker_cli_container_name>
```

其中，myapp_default 是应用程序的网络名称，<docker_cli_container_name> 是 Docker CLI 部署的容器名称。

```sh
root@VM-24-11-ubuntu:/data/docker/mysql# docker network connect mysql_default vscode-server(docker cli部署容器)
```

### 测试容器之间的连通性

现在我们可以从 Docker CLI 部署的容器中使用 ping 命令测试与 Docker Compose 容器之间的连通性：

```sh
docker exec <docker_cli_container_name> ping <docker_compose_container_name> 
```

其中，<docker_cli_container_name> 是 Docker CLI 部署的容器名称，web 是应用程序中的服务名称。如果一切正常，你应该能够看到类似以下的输出：

```sh
root@VM-24-11-ubuntu:/data/docker/mysql# docker exec vscode-server ping mysql_db_1
PING mysql_db_1 (172.25.0.2) 56(84) bytes of data.
64 bytes from mysql_db_1.mysql_default (172.25.0.2): icmp_seq=1 ttl=64 time=0.098 ms
64 bytes from mysql_db_1.mysql_default (172.25.0.2): icmp_seq=2 ttl=64 time=0.063 ms
64 bytes from mysql_db_1.mysql_default (172.25.0.2): icmp_seq=3 ttl=64 time=0.061 ms
^C
root@VM-24-11-ubuntu:/data/docker/mysql# docker exec vscode-server ping mysql_phpmyadmin_1
PING mysql_phpmyadmin_1 (172.25.0.3) 56(84) bytes of data.
64 bytes from mysql_phpmyadmin_1.mysql_default (172.25.0.3): icmp_seq=1 ttl=64 time=0.087 ms
64 bytes from mysql_phpmyadmin_1.mysql_default (172.25.0.3): icmp_seq=2 ttl=64 time=0.067 ms
64 bytes from mysql_phpmyadmin_1.mysql_default (172.25.0.3): icmp_seq=3 ttl=64 time=0.095 ms
64 bytes from mysql_phpmyadmin_1.mysql_default (172.25.0.3): icmp_seq=4 ttl=64 time=0.063 ms
^C
root@VM-24-11-ubuntu:/data/docker/mysql# ^C

```

注意，如果你的应用程序使用了自定义网络，你需要使用自定义网络名称代替默认名称。同时，还需要确保 Docker Compose 和 Docker CLI 部署的容器都在同一个网络中

## 普通用户如何执行docker命令

```sh
1.创建docker用户组
[admin@Centos8 local]$ sudo groupadd docker
2.将admin用户填进docker组中
[admin@Centos8 local]$ sudo gpasswd -a ${USER} admin
3.重启docke服务
[admin@Centos8 local]$ sudo service docker restart
Redirecting to /bin/systemctl restart docker.service
[admin@Centos8 local]$ docker ps
4.如果普通用户执行docker命令，如果提示get …… dial unix /var/run/docker.sock权限不够，则修改/var/run/docker.sock权限
使用root用户执行如下命令，即可
Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Get "http://%2Fvar%2Frun%2Fdocker.sock/v1.24/containers/json": dial unix /var/run/docker.sock: connect: permission denied
[admin@Centos8 local]$ sudo chmod a+rw /var/run/docker.sock
[admin@Centos8 local]$ docker ps
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
[admin@Centos8 local]$ 