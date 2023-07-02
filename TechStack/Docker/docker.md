## Docker安装

### 环境准备

1、linux基础

2、Cetnos7

3、MobaXterm连接

### 安装Docker

#### 环境查看

```shell
# 系统内核
[ldspdvs@cetnos7 ~]$ uname -r
3.10.0-1160.31.1.el7.x86_64
[ldspdvs@cetnos7 ~]$ uname -r
3.10.0-1160.31.1.el7.x86_64
```

```shell
# 系统版本
[root@cetnos7 ldspdvs]# cat /etc/os-release
NAME="CentOS Linux"
VERSION="7 (Core)"
ID="centos"
ID_LIKE="rhel fedora"
VERSION_ID="7"
PRETTY_NAME="CentOS Linux 7 (Core)"
ANSI_COLOR="0;31"
CPE_NAME="cpe:/o:centos:centos:7"
HOME_URL="https://www.centos.org/"
BUG_REPORT_URL="https://bugs.centos.org/"

CENTOS_MANTISBT_PROJECT="CentOS-7"
CENTOS_MANTISBT_PROJECT_VERSION="7"
REDHAT_SUPPORT_PRODUCT="centos"
REDHAT_SUPPORT_PRODUCT_VERSION="7"

```

#### 安装

官方文档https://docs.docker.com/engine/install/centos/

```shell
# 1、卸载旧的版本
yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-engine
                
# 2、需要的安装包
yum install -y yum-utils

# 3、设置镜像仓库
yum-config-manager \
    --add-repo \
    https://download.docker.com/linux/centos/docker-ce.repo
  
yum-config-manager \
    --add-repo \
    http://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo
  
# 更新软件包
yum makecache fast

# 4、安装docker相关内容
yum install docker-ce docker-ce-cli containerd.io

# 5、启动docker
systemctl start docker

# 6、使用docker version验证是否成功
```

[![image-20210616182704213-20220801230503-iv3inme.png](https://i.postimg.cc/DyJRYqpr/image-20210616182704213-20220801230503-iv3inme.png)](https://postimg.cc/1fSW8NQX)

```shell
# 7、hello-world
docker run hello-world
```
[![image-docker-2.png](https://i.postimg.cc/RCbjRPdC/image-docker-2.png)](https://postimg.cc/Thg72JBB)

```shell
# 8、查看镜像
[root@cetnos7 ldspdvs]# docker images
REPOSITORY    TAG       IMAGE ID       CREATED        SIZE
hello-world   latest    d1165f221234   3 months ago   13.3kB
```

#### 卸载docker

```shell
# 9、卸载依赖
yum remove docker-ce docker-ce-cli containerd.io
# 10、删除资源
rm -rf /var/lib/docker
rm -rf /var/lib/containerd
```

#### 阿里云镜像加速

```shell
sudo mkdir -p /etc/docker

sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://rojd6brn.mirror.aliyuncs.com"]
}
EOF

sudo systemctl daemon-reload

sudo systemctl restart docker
```

## Docker常用命令

### 帮助命令

```shell
docker version			# 显示docker的版本信息
docker info 			# 显示docker的系统信息，包括镜像和容器的数量
docke 命令 --help			# 帮助命令
```

帮助文档地址 https://docs.docker.com/reference/

### 镜像命令

#### docker images

**查看所有本地主机上的镜像**

```shell
[root@cetnos7 docker]# docker images
REPOSITORY    TAG       IMAGE ID       CREATED        SIZE
hello-world   latest    d1165f221234   3 months ago   13.3kB

# 解释
REPOSITORY	镜像的仓库源
TAG			镜像的标签
IMAGE ID	镜像的id
CREATED		镜像的创建时间
SIZE		镜像的大小

# 可选项

  -a, --all             Show all images (default hides intermediate images)
      --digests         Show digests
  -f, --filter filter   Filter output based on conditions provided
      --format string   Pretty-print images using a Go template
      --no-trunc        Don't truncate output
  -q, --quiet           Only show image IDs

```

#### docker search

**搜索镜像**

```sh
[root@cetnos7 docker]# docker search mysql
NAME                              DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
mysql                             MySQL is a widely used, open-source relation…   10999     [OK]
mariadb                           MariaDB Server is a high performing open sou…   4165      [OK]
mysql/mysql-server                Optimized MySQL Server Docker images. Create…   815                  [OK]
percona                           Percona Server is a fork of the MySQL relati…   544       [OK]
phpmyadmin                        phpMyAdmin - A web interface for MySQL and M…   240       [OK]
centos/mysql-57-centos7           MySQL 5.7 SQL database server                   88
mysql/mysql-cluster               Experimental MySQL Cluster Docker images. Cr…   86
centurylink/mysql                 Image containing mysql. Optimized to be link…   59                   [OK]
bitnami/mysql                     Bitnami MySQL Docker Image                      52                   [OK]
databack/mysql-backup             Back up mysql databases to... anywhere!         44
deitch/mysql-backup               REPLACED! Please use http://hub.docker.com/r…   41                   [OK]
prom/mysqld-exporter                                                              39                   [OK]
tutum/mysql                       Base docker image to run a MySQL database se…   35
linuxserver/mysql                 A Mysql container, brought to you by LinuxSe…   30
schickling/mysql-backup-s3        Backup MySQL to S3 (supports periodic backup…   29                   [OK]
centos/mysql-56-centos7           MySQL 5.6 SQL database server                   20
circleci/mysql                    MySQL is a widely used, open-source relation…   20
mysql/mysql-router                MySQL Router provides transparent routing be…   19
arey/mysql-client                 Run a MySQL client from a docker container      17                   [OK]
fradelg/mysql-cron-backup         MySQL/MariaDB database backup using cron tas…   13                   [OK]
openshift/mysql-55-centos7        DEPRECATED: A Centos7 based MySQL v5.5 image…   6
devilbox/mysql                    Retagged MySQL, MariaDB and PerconaDB offici…   3
ansibleplaybookbundle/mysql-apb   An APB which deploys RHSCL MySQL                2                    [OK]
jelastic/mysql                    An image of the MySQL database server mainta…   1
widdpim/mysql-client              Dockerized MySQL Client (5.7) including Curl…   1                    [OK]

# 可选项

  -f, --filter filter   Filter output based on conditions provided
      --format string   Pretty-print search using a Go template
      --limit int       Max number of search results (default 25)
      --no-trunc        Don't truncate output

[root@cetnos7 docker]# docker search mysql --filter=STARS=3000
NAME      DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
mysql     MySQL is a widely used, open-source relation…   10999     [OK]
mariadb   MariaDB Server is a high performing open sou…   4165      [OK]

```

#### docker pull

**下载镜像**

```sh
# 下载镜像 docker pull 镜像名[:tag]
[root@cetnos7 docker]# docker pull mysql
Using default tag: latest	# 如果不写tag，默认就是latest最新版
latest: Pulling from library/mysql
69692152171a: Pull complete		# 分层下载，docker image的核心，联合文件系统
1651b0be3df3: Pull complete
951da7386bc8: Pull complete
0f86c95aa242: Pull complete
37ba2d8bd4fe: Pull complete
6d278bb05e94: Pull complete
497efbd93a3e: Pull complete
f7fddf10c2c2: Pull complete
16415d159dfb: Pull complete
0e530ffc6b73: Pull complete
b0a4a1a77178: Pull complete
cd90f92aa9ef: Pull complete
Digest: sha256:d50098d7fcb25b1fcb24e2d3247cae3fc55815d64fec640dc395840f8fa80969		# 签名
Status: Downloaded newer image for mysql:latest
docker.io/library/mysql:latest		# 真实地址
# 等价于它
docker pull mysql
docker pull docker.io/library/mysql:latest

# 指定版本下载
[root@cetnos7 ~]# docker pull mysql:5.7
5.7: Pulling from library/mysql
69692152171a: Already exists
1651b0be3df3: Already exists
951da7386bc8: Already exists
0f86c95aa242: Already exists
37ba2d8bd4fe: Already exists
6d278bb05e94: Already exists
497efbd93a3e: Already exists
a023ae82eef5: Pull complete
e76c35f20ee7: Pull complete
e887524d2ef9: Pull complete
ccb65627e1c3: Pull complete
Digest: sha256:a682e3c78fc5bd941e9db080b4796c75f69a28a8cad65677c23f7a9f18ba21fa
Status: Downloaded newer image for mysql:5.7
docker.io/library/mysql:5.7

```

#### docker rmi

**删除镜像**

```sh
[root@cetnos7 docker]# docker images
REPOSITORY    TAG       IMAGE ID       CREATED        SIZE
tomcat        latest    c43a65faae57   4 weeks ago    667MB
mysql         5.7       2c9028880e58   5 weeks ago    447MB
mysql         latest    c0cdc95609f1   5 weeks ago    556MB
hello-world   latest    d1165f221234   3 months ago   13.3kB
# [root@cetnos7 docker]# docker rmi -f 容器ID		# 删除指定容器
# [root@cetnos7 docker]# docker rmi -f 容器ID 容器ID 容器ID		# 删除多个容器
# [root@cetnos7 docker]# docker rmi -f $(docker images -aq)		# 删除全部容器
[root@cetnos7 docker]# docker rmi -f 2c9028880e58		# 删除指定容器
Untagged: mysql:5.7
Untagged: mysql@sha256:a682e3c78fc5bd941e9db080b4796c75f69a28a8cad65677c23f7a9f18ba21fa
Deleted: sha256:2c9028880e5814e8923c278d7e2059f9066d56608a21cd3f83a01e3337bacd68
Deleted: sha256:c49c5c776f1bc87cdfff451ef39ce16a1ef45829e10203f4d9a153a6889ec15e
Deleted: sha256:8345316eca77700e62470611446529113579712a787d356e5c8656a41c244aee
Deleted: sha256:8ae51b87111404bd3e3bde4115ea2fe3fd2bb2cf67158460423c361a24df156b
Deleted: sha256:9d5afda6f6dcf8dd59aef5c02099f1d3b3b0c9ae4f2bb7a61627613e8cdfe562

```

### 容器命令

==说明==：我们有了镜像才可以创建容器，linux，下载一个cetnos镜像来测试学习

```sh
docker pull cetnos
```

#### 新建容器并启动

```shell
docker run [可选参数] image

# 参数说明
--name="Name"	容器名字 tomcat01 tomcat02 用来区分容器
-d				后台方式运行
-it				使用交互方式运行，进入容器查看内容
-p				指定容器端口 -p 8080:8080
	-p	ip:主机端口
	-p	主机端口:容器端口（常用）
	-p	容器端口
	容器端口
-P				随机指定端口
# 测试，启动并进入容器
[root@cetnos7 docker]# docker run -it centos /bin/bash
[root@88d08d3e888b /]# ls		# 查看容器的centos，基础版本，很多命令都是不完善的
bin  dev  etc  home  lib  lib64  lost+found  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
# 从容器中退回主机
[root@88d08d3e888b /]# exit
exit
[root@cetnos7 docker]# ls
daemon.json  key.json
[root@cetnos7 docker]# cd ../
[root@cetnos7 etc]# cd ../
[root@cetnos7 /]# ls
bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
```

#### 列出所有运行的容器

```sh
# docker ps		# 列出当前正在运行的容器
	-a			# 列出当前正在运行的容器+历史运行过的容器
	-q			# 只显示容器的编号
	-n=?		# 显示最近创建的容器
[root@cetnos7 /]# docker ps
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
[root@cetnos7 /]# docker ps -a
CONTAINER ID   IMAGE          COMMAND                  CREATED         STATUS                       PORTS     NAMES
88d08d3e888b   centos         "/bin/bash"              5 minutes ago   Exited (130) 3 minutes ago             thirsty_galileo
a11f1465cda9   centos         "/bin/bash --name=ce…"   6 minutes ago   Exited (2) 6 minutes ago               mystifying_poincare
89e468b92efe   d1165f221234   "/hello"                 15 hours ago    Exited (0) 15 hours ago                hungry_euclid
ea0927bcd5bd   d1165f221234   "/hello"                 15 hours ago    Exited (0) 15 hours ago                heuristic_bhaskara
24251067d1b7   d1165f221234   "/hello"                 22 hours ago    Exited (0) 22 hours ago                laughing_wescoff
e49b069aabc4   d1165f221234   "/hello"                 35 hours ago    Exited (0) 35 hours ago                keen_wiles

[root@cetnos7 /]# docker ps -qa
88d08d3e888b
a11f1465cda9
89e468b92efe
ea0927bcd5bd
24251067d1b7
e49b069aabc4
[root@cetnos7 /]# docker ps -a -n=1
CONTAINER ID   IMAGE     COMMAND       CREATED          STATUS                       PORTS     NAMES
88d08d3e888b   centos    "/bin/bash"   10 minutes ago   Exited (130) 8 minutes ago             thirsty_galileo
[root@cetnos7 /]# docker ps -a -n=2
CONTAINER ID   IMAGE     COMMAND                  CREATED          STATUS                       PORTS     NAMES
88d08d3e888b   centos    "/bin/bash"              10 minutes ago   Exited (130) 8 minutes ago             thirsty_galileo
a11f1465cda9   centos    "/bin/bash --name=ce…"   11 minutes ago   Exited (2) 11 minutes ago              mystifying_poincare

```

#### 退出容器

```sh
exit			# 容器停止并退出
Ctrl + P + Q	# 容器不停止退出
```

#### 删除容器

```sh
docker rm 容器id 					# 删除指定的容器，不能删除正在运行的，强制删除需要rm -f
docker rm -f $(docker ps -aq)	 # 删除所有的容器
docker ps -a -q | xargs docker rm # 删除所有容器
[root@cetnos7 /]# docker ps -aq
88d08d3e888b
a11f1465cda9
89e468b92efe
ea0927bcd5bd
24251067d1b7
e49b069aabc4
[root@cetnos7 /]# docker rm 88d08d3e888b
88d08d3e888b
[root@cetnos7 /]# docker ps -aq
a11f1465cda9
89e468b92efe
ea0927bcd5bd
24251067d1b7
e49b069aabc4
[root@cetnos7 /]# docker rm -f $(docker ps -aq)
a11f1465cda9
89e468b92efe
ea0927bcd5bd
24251067d1b7
e49b069aabc4
[root@cetnos7 /]# docker ps -aq
[root@cetnos7 /]#
```

#### 启动和停止容器的操作

```shell
docker start 容器id		# 启动容器
docker restart 容器id		# 重启容器
docker stop 容器id		# 停止当前正在运行容器
docker kill 容器id		# 强制停止当前容器
```

#### 常用其他命令

##### 后台启动容器

```shell
# 命令 docker run -d 镜像名
[root@cetnos7 /]# docker run -d centos
1c58ce5ef8c38480f280be84a071083c8515d2aab90d5796078160fe22434e52
[root@cetnos7 /]# docker ps
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
[root@cetnos7 /]#
# 问题 docker ps 发现centos停止了
# 常见的坑：docker 容器使用后台运行就必须要有一个前台进程，docker发现没有应用，就会自动停止
# nginx，容器启动后，发现自己没有提供服务，就会立刻停止，就是没有程序了
```

#### 查看日志

```shell
[root@cetnos7 /]# docker logs --help
Usage:  docker logs [OPTIONS] CONTAINER
Fetch the logs of a container
Options:
      --details        Show extra details provided to logs
  -f, --follow         Follow log output
      --since string   Show logs since timestamp (e.g. 2013-01-02T13:23:37Z) or relative (e.g. 42m for 42 minutes)
  -n, --tail string    Number of lines to show from the end of the logs (default "all")
  -t, --timestamps     Show timestamps	# 时间戳
      --until string   Show logs before a timestamp (e.g. 2013-01-02T13:23:37Z) or relative (e.g. 42m for 42 minutes)

# 编写脚本
[root@cetnos7 /]# docker run -d centos /bin/sh -c "while true;do echo sun1;sleep 1;done"
a01aa4045648b5d9c22e88038eea9117e718fde7281ed48af5ce81e23e7c528e

# 查看容器
[root@cetnos7 /]# docker ps
CONTAINER ID   IMAGE     COMMAND                  CREATED         STATUS         PORTS     NAMES
a01aa4045648   centos    "/bin/sh -c 'while t…"   5 seconds ago   Up 4 seconds             festive_montalcini

# 显示日志
# -tf 				# 显示日志
# --tail number 	# 显示日志条数
[root@cetnos7 /]# docker logs -tf --tail 10 a01aa4045648
2021-06-17T02:17:13.845995409Z sun1
2021-06-17T02:17:14.849198894Z sun1
2021-06-17T02:17:15.850829523Z sun1
2021-06-17T02:17:16.853976336Z sun1
2021-06-17T02:17:17.857956862Z sun1
2021-06-17T02:17:18.860741444Z sun1
2021-06-17T02:17:19.864721492Z sun1
2021-06-17T02:17:20.869478161Z sun1
2021-06-17T02:17:21.871854909Z sun1
2021-06-17T02:17:22.885784515Z sun1
2021-06-17T02:17:23.889363112Z sun1
2021-06-17T02:17:24.891500188Z sun1
2021-06-17T02:17:25.893458493Z sun1
2021-06-17T02:17:26.895170299Z sun1
^C
[root@cetnos7 /]#

docker logs -f -t --tail 容器
```

#### 查看容器中的进程信息

```shell
# 命令 docker inspect 容器ID
# docker top 容器id
[root@cetnos7 /]# docker top a01aa4045648
UID                 PID                 PPID                C                   STIME               TTY                 TIME                CMD
root                34921               34901               0                   10:16               ?                   00:00:00            /bin/sh -c while true;do echo sun1;sleep 1;done
# UID 用户ID 
# PID 父ID 
# PPID 进程ID
```

#### 查看镜像的元数据

```shell
[root@cetnos7 ~]# docker inspect --help

Usage:  docker inspect [OPTIONS] NAME|ID [NAME|ID...]

Return low-level information on Docker objects

Options:
  -f, --format string   Format the output using the given Go template
  -s, --size            Display total file sizes if the type is container
      --type string     Return JSON for specified type
[root@cetnos7 ~]# docker ps
CONTAINER ID   IMAGE     COMMAND                  CREATED        STATUS        PORTS     NAMES
a01aa4045648   centos    "/bin/sh -c 'while t…"   22 hours ago   Up 22 hours             festive_montalcini
[root@cetnos7 ~]# docker inspect a01aa4045648
[
    {
        "Id": "a01aa4045648b5d9c22e88038eea9117e718fde7281ed48af5ce81e23e7c528e",
        "Created": "2021-06-17T02:16:20.011138636Z",
        "Path": "/bin/sh",
        "Args": [
            "-c",
            "while true;do echo sun1;sleep 1;done"
        ],
        "State": {
            "Status": "running",
            "Running": true,
            "Paused": false,
            "Restarting": false,
            "OOMKilled": false,
            "Dead": false,
            "Pid": 34921,
            "ExitCode": 0,
            "Error": "",
            "StartedAt": "2021-06-17T02:16:20.531700464Z",
            "FinishedAt": "0001-01-01T00:00:00Z"
        },
        "Image": "sha256:300e315adb2f96afe5f0b2780b87f28ae95231fe3bdd1e16b9ba606307728f55",
        "ResolvConfPath": "/var/lib/docker/containers/a01aa4045648b5d9c22e88038eea9117e718fde7281ed48af5ce81e23e7c528e/resolv.conf",
        "HostnamePath": "/var/lib/docker/containers/a01aa4045648b5d9c22e88038eea9117e718fde7281ed48af5ce81e23e7c528e/hostname",
        "HostsPath": "/var/lib/docker/containers/a01aa4045648b5d9c22e88038eea9117e718fde7281ed48af5ce81e23e7c528e/hosts",
        "LogPath": "/var/lib/docker/containers/a01aa4045648b5d9c22e88038eea9117e718fde7281ed48af5ce81e23e7c528e/a01aa4045648b5d9c22e88038eea9117e718fde7281ed48af5ce81e23e7c528e-json.log",
        "Name": "/festive_montalcini",
        "RestartCount": 0,
        "Driver": "overlay2",
        "Platform": "linux",
        "MountLabel": "",
        "ProcessLabel": "",
        "AppArmorProfile": "",
        "ExecIDs": null,
        "HostConfig": {
            "Binds": null,
            "ContainerIDFile": "",
            "LogConfig": {
                "Type": "json-file",
                "Config": {}
            },
            "NetworkMode": "default",
            "PortBindings": {},
            "RestartPolicy": {
                "Name": "no",
                "MaximumRetryCount": 0
            },
            "AutoRemove": false,
            "VolumeDriver": "",
            "VolumesFrom": null,
            "CapAdd": null,
            "CapDrop": null,
            "CgroupnsMode": "host",
            "Dns": [],
            "DnsOptions": [],
            "DnsSearch": [],
            "ExtraHosts": null,
            "GroupAdd": null,
            "IpcMode": "private",
            "Cgroup": "",
            "Links": null,
            "OomScoreAdj": 0,
            "PidMode": "",
            "Privileged": false,
            "PublishAllPorts": false,
            "ReadonlyRootfs": false,
            "SecurityOpt": null,
            "UTSMode": "",
            "UsernsMode": "",
            "ShmSize": 67108864,
            "Runtime": "runc",
            "ConsoleSize": [
                0,
                0
            ],
            "Isolation": "",
            "CpuShares": 0,
            "Memory": 0,
            "NanoCpus": 0,
            "CgroupParent": "",
            "BlkioWeight": 0,
            "BlkioWeightDevice": [],
            "BlkioDeviceReadBps": null,
            "BlkioDeviceWriteBps": null,
            "BlkioDeviceReadIOps": null,
            "BlkioDeviceWriteIOps": null,
            "CpuPeriod": 0,
            "CpuQuota": 0,
            "CpuRealtimePeriod": 0,
            "CpuRealtimeRuntime": 0,
            "CpusetCpus": "",
            "CpusetMems": "",
            "Devices": [],
            "DeviceCgroupRules": null,
            "DeviceRequests": null,
            "KernelMemory": 0,
            "KernelMemoryTCP": 0,
            "MemoryReservation": 0,
            "MemorySwap": 0,
            "MemorySwappiness": null,
            "OomKillDisable": false,
            "PidsLimit": null,
            "Ulimits": null,
            "CpuCount": 0,
            "CpuPercent": 0,
            "IOMaximumIOps": 0,
            "IOMaximumBandwidth": 0,
            "MaskedPaths": [
                "/proc/asound",
                "/proc/acpi",
                "/proc/kcore",
                "/proc/keys",
                "/proc/latency_stats",
                "/proc/timer_list",
                "/proc/timer_stats",
                "/proc/sched_debug",
                "/proc/scsi",
                "/sys/firmware"
            ],
            "ReadonlyPaths": [
                "/proc/bus",
                "/proc/fs",
                "/proc/irq",
                "/proc/sys",
                "/proc/sysrq-trigger"
            ]
        },
        "GraphDriver": {
            "Data": {
                "LowerDir": "/var/lib/docker/overlay2/595aafe31004009a057801602665f36723c7621a6d03c0226e24bcb32daf3f74-init/diff:/var/lib/docker/overlay2/dbe0863967eda16db79356c5aa892895ef73d0afee2ecec4b52c209393f16103/diff",
                "MergedDir": "/var/lib/docker/overlay2/595aafe31004009a057801602665f36723c7621a6d03c0226e24bcb32daf3f74/merged",
                "UpperDir": "/var/lib/docker/overlay2/595aafe31004009a057801602665f36723c7621a6d03c0226e24bcb32daf3f74/diff",
                "WorkDir": "/var/lib/docker/overlay2/595aafe31004009a057801602665f36723c7621a6d03c0226e24bcb32daf3f74/work"
            },
            "Name": "overlay2"
        },
        "Mounts": [],
        "Config": {
            "Hostname": "a01aa4045648",
            "Domainname": "",
            "User": "",
            "AttachStdin": false,
            "AttachStdout": false,
            "AttachStderr": false,
            "Tty": false,
            "OpenStdin": false,
            "StdinOnce": false,
            "Env": [
                "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
            ],
            "Cmd": [
                "/bin/sh",
                "-c",
                "while true;do echo sun1;sleep 1;done"
            ],
            "Image": "centos",
            "Volumes": null,
            "WorkingDir": "",
            "Entrypoint": null,
            "OnBuild": null,
            "Labels": {
                "org.label-schema.build-date": "20201204",
                "org.label-schema.license": "GPLv2",
                "org.label-schema.name": "CentOS Base Image",
                "org.label-schema.schema-version": "1.0",
                "org.label-schema.vendor": "CentOS"
            }
        },
        "NetworkSettings": {
            "Bridge": "",
            "SandboxID": "0ac4d097a0a96512343c9f0ab1d35891554162b4f52c3aa738b331bdad059560",
            "HairpinMode": false,
            "LinkLocalIPv6Address": "",
            "LinkLocalIPv6PrefixLen": 0,
            "Ports": {},
            "SandboxKey": "/var/run/docker/netns/0ac4d097a0a9",
            "SecondaryIPAddresses": null,
            "SecondaryIPv6Addresses": null,
            "EndpointID": "6381bb14df541826bde3d8464cb5c3ee733788a41e1e03cca6625435ab3aa2d3",
            "Gateway": "172.17.0.1",
            "GlobalIPv6Address": "",
            "GlobalIPv6PrefixLen": 0,
            "IPAddress": "172.17.0.2",
            "IPPrefixLen": 16,
            "IPv6Gateway": "",
            "MacAddress": "02:42:ac:11:00:02",
            "Networks": {
                "bridge": {
                    "IPAMConfig": null,
                    "Links": null,
                    "Aliases": null,
                    "NetworkID": "eea50bf7ae4003415c3271a588d18d786750f08cefd87476f11d22e06d38c433",
                    "EndpointID": "6381bb14df541826bde3d8464cb5c3ee733788a41e1e03cca6625435ab3aa2d3",
                    "Gateway": "172.17.0.1",
                    "IPAddress": "172.17.0.2",
                    "IPPrefixLen": 16,
                    "IPv6Gateway": "",
                    "GlobalIPv6Address": "",
                    "GlobalIPv6PrefixLen": 0,
                    "MacAddress": "02:42:ac:11:00:02",
                    "DriverOpts": null
                }
            }
        }
    }
]
[root@cetnos7 ~]#
```

#### 进入当前正在运行的容器

```shell
# 我们通常容器都是使用后台方式运行的，需要进入容器，修改一些配置
# 方式一 以交互方式进入后台
docker exec -it 容器ID /bin/bash

# 测试
[root@cetnos7 ~]# docker ps
CONTAINER ID   IMAGE     COMMAND                  CREATED        STATUS        PORTS     NAMES
a01aa4045648   centos    "/bin/sh -c 'while t…"   22 hours ago   Up 22 hours             festive_montalcini
[root@cetnos7 ~]# docker exec -it a01aa4045648 /bin/bash
[root@a01aa4045648 /]# ls
bin  dev  etc  home  lib  lib64  lost+found  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
[root@a01aa4045648 /]#

# 方式二
docker attach 容器ID
[root@cetnos7 ~]# docker attach --help

Usage:  docker attach [OPTIONS] CONTAINER

Attach local standard input, output, and error streams to a running container

Options:
      --detach-keys string   Override the key sequence for detaching a container
      --no-stdin             Do not attach STDIN
      --sig-proxy            Proxy all received signals to the process (default true)

# 测试
[root@cetnos7 ~]# docker attach a01aa4045648
sun1
sun1
# 进入正在执行的当前代码

# docker exec		# 进入容器后打开一个新的终端，可以在里面操作
# docker attach 	# 进入容器正在执行的终端，不会启动新的进程
```

#### 从容器内拷贝文件到主机上

```shell
docker cp 容器ID:容器内路径 目的地路径
# 查看主机现有文件
[root@centos7 home]# ll
总用量 4
drwx------. 17 ldspdvs ldspdvs 4096 6月  18 09:30 ldspdvs
-rw-r--r--.  1 root    root       0 6月  18 10:51 sun.java

# 进入容器
[root@centos7 home]# docker attach 6d8882478a04
[root@6d8882478a04 /]# ls
bin  dev  etc  home  lib  lib64  lost+found  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
[root@6d8882478a04 /]# cd home
[root@6d8882478a04 home]# ls

# 容器内创建文件
[root@6d8882478a04 home]# touch test.java
[root@6d8882478a04 home]# ls
test.java
[root@6d8882478a04 home]# exit
exit
[root@centos7 home]# docker ps
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
[root@centos7 home]# docker ps -a
CONTAINER ID   IMAGE     COMMAND                  CREATED         STATUS                       PORTS     NAMES
6d8882478a04   centos    "/bin/bash"              4 minutes ago   Exited (0) 6 seconds ago               inspiring_taussig
a01aa4045648   centos    "/bin/sh -c 'while t…"   25 hours ago    Exited (255) 4 minutes ago             festive_montalcini
1c58ce5ef8c3   centos    "/bin/bash"              25 hours ago    Exited (0) 25 hours ago                mystifying_cannon

# 从容器内复制文件到主机上
[root@centos7 home]# docker cp 6d8882478a04:/home/test.java /home
[root@centos7 home]# ls
ldspdvs  sun.java  test.java
[root@centos7 home]#
```

#### 小结

[![image-docker-3.png](https://i.postimg.cc/GtBgVCKL/image-docker-3.png)](https://postimg.cc/RJBTJ22y)

```shell
attach			# 当前shell下attach连接到指定镜像环境中
build			# 通过Dockerfile定制镜像
commit			# 提交当前容器为新的镜像
cp				# 从容器中拷贝文件到宿主机中
create			# 创建一个新的容器，同run但不启动容器
diff			# 查看docker容器话
events			# 从docker服务获取容器实时事件
export			# 到处容器的内容作为一个tar归档文件对应import
history			# 站是一个镜像形成历史
images			# 列出系统当前镜像
info			# 显示系统相关信息
inspect			# 查看容器详细信息
kill			# kill指定docker容器
load			# 从一个tar包中加载一个镜像对应save
login			# 注册或登录一个dockers源服务器
logout			# 从当前Dockers registry退出
logs			# 输出当前容器日志信息
port			# 查看映射端口对应容器内部源端口
pause			# 暂停容器
ps				# 列出容器列表
pull			# 从docker镜像服务器拉取指定镜像
push			# 推送指定镜像或者库镜像至docker源服务器
restart			# 重启运行的容器
rm				# 移除一个或多个容器
rmi				# 移除一个或多个镜像[无容器使用该镜像才可以删除，否则需删除相关内容]
run				# 创建一个新的荣光其并运行一个命令
save			# 保存一个镜像为一个tar包[对应load]
search			# 在docker hub中搜索镜像
start			# 启动容器
stop			# 停止容器
tag				# 给源中镜像打标签
top				# 查看容器中运行的进程信息
unpause			# 取消暂停容器
version			# 查看docker版本号
wait			# 截取容器停止时的退出状态值
```

## 练习

### Nginx

```shell
# 1、搜索镜像
[root@centos7 ~]# docker search nginx
NAME                               DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
nginx                              Official build of Nginx.                        15026     [OK]
jwilder/nginx-proxy                Automated Nginx reverse proxy for docker con…   2038                 [OK]
richarvey/nginx-php-fpm            Container running Nginx + PHP-FPM capable of…   814                  [OK]
jc21/nginx-proxy-manager           Docker container for managing Nginx proxy ho…   200
linuxserver/nginx                  An Nginx container, brought to you by LinuxS…   147
tiangolo/nginx-rtmp                Docker image with Nginx using the nginx-rtmp…   130                  [OK]
jlesage/nginx-proxy-manager        Docker container for Nginx Proxy Manager        119                  [OK]
alfg/nginx-rtmp                    NGINX, nginx-rtmp-module and FFmpeg from sou…   99                   [OK]
bitnami/nginx                      Bitnami nginx Docker Image                      98                   [OK]
jasonrivers/nginx-rtmp             Docker images to host RTMP streams using NGI…   90                   [OK]
nginxdemos/hello                   NGINX webserver that serves a simple page co…   70                   [OK]
privatebin/nginx-fpm-alpine        PrivateBin running on an Nginx, php-fpm & Al…   55                   [OK]
nginx/nginx-ingress                NGINX and  NGINX Plus Ingress Controllers fo…   55
nginxinc/nginx-unprivileged        Unprivileged NGINX Dockerfiles                  38
staticfloat/nginx-certbot          Opinionated setup for automatic TLS certs lo…   23                   [OK]
schmunk42/nginx-redirect           A very simple container to redirect HTTP tra…   19                   [OK]
nginx/nginx-prometheus-exporter    NGINX Prometheus Exporter for NGINX and NGIN…   18
centos/nginx-112-centos7           Platform for running nginx 1.12 or building …   15
centos/nginx-18-centos7            Platform for running nginx 1.8 or building n…   13
raulr/nginx-wordpress              Nginx front-end for the official wordpress:f…   13                   [OK]
bitwarden/nginx                    The Bitwarden nginx web server acting as a r…   11
bitnami/nginx-ingress-controller   Bitnami Docker Image for NGINX Ingress Contr…   9                    [OK]
mailu/nginx                        Mailu nginx frontend                            8                    [OK]
ansibleplaybookbundle/nginx-apb    An APB to deploy NGINX                          2                    [OK]
wodby/nginx                        Generic nginx                                   1                    [OK]

# 2、拉取镜像
[root@centos7 ~]# docker pull nginx
Using default tag: latest
latest: Pulling from library/nginx
69692152171a: Pull complete
30afc0b18f67: Pull complete
596b1d696923: Pull complete
febe5bd23e98: Pull complete
8283eee92e2f: Pull complete
351ad75a6cfa: Pull complete
Digest: sha256:6d75c99af15565a301e48297fa2d121e15d80ad526f8369c526324f0f7ccb750
Status: Downloaded newer image for nginx:latest
docker.io/library/nginx:latest

# 3、查看镜像
[root@centos7 ~]# docker images
REPOSITORY   TAG       IMAGE ID       CREATED        SIZE
nginx        latest    d1a364dc548d   3 weeks ago    133MB
centos       latest    300e315adb2f   6 months ago   209MB

# 4、启动镜像
# -d 后台运行
# --name 运行镜像别名
# -p 宿主机端口：容器端口 联通宿主机还有容器对应的端口
[root@centos7 ~]# docker run -d --name nginx01 -p 8080:80 nginx
bc781c453438558d384b5b8977862dc75c53889addbe69f0080345cf7220e3b4
[root@centos7 ~]# docker ps
CONTAINER ID   IMAGE     COMMAND                  CREATED         STATUS         PORTS                                   NAMES
bc781c453438   nginx     "/docker-entrypoint.…"   6 seconds ago   Up 4 seconds   0.0.0.0:8080->80/tcp, :::8080->80/tcp   nginx01
# 5、测试
[root@centos7 ~]# curl localhost:8080
<!DOCTYPE html>
<html>
<head>
<title>Welcome to nginx!</title>
<style>
    body {
        width: 35em;
        margin: 0 auto;
        font-family: Tahoma, Verdana, Arial, sans-serif;
    }
</style>
</head>
<body>
<h1>Welcome to nginx!</h1>
<p>If you see this page, the nginx web server is successfully installed and
working. Further configuration is required.</p>

<p>For online documentation and support please refer to
<a href="http://nginx.org/">nginx.org</a>.<br/>
Commercial support is available at
<a href="http://nginx.com/">nginx.com</a>.</p>

<p><em>Thank you for using nginx.</em></p>
</body>
</html>

# 6、进入容器
[root@centos7 ~]# docker ps
CONTAINER ID   IMAGE     COMMAND                  CREATED          STATUS          PORTS                                   NAMES
bc781c453438   nginx     "/docker-entrypoint.…"   11 minutes ago   Up 11 minutes   0.0.0.0:8080->80/tcp, :::8080->80/tcp   nginx01
[root@centos7 ~]# docker exec -it nginx01 /bin/bash
root@bc781c453438:/# whereis nginx
nginx: /usr/sbin/nginx /usr/lib/nginx /etc/nginx /usr/share/nginx
root@bc781c453438:/# cd /etc/nginx
root@bc781c453438:/etc/nginx# ls
conf.d  fastcgi_params  mime.types  modules  nginx.conf  scgi_params  uwsgi_params
root@bc781c453438:/etc/nginx#

# 7、从容器中退出
root@bc781c453438:/etc/nginx# exit
exit
[root@centos7 ~]# docker ps
CONTAINER ID   IMAGE     COMMAND                  CREATED          STATUS          PORTS                                   NAMES
bc781c453438   nginx     "/docker-entrypoint.…"   15 minutes ago   Up 15 minutes   0.0.0.0:8080->80/tcp, :::8080->80/tcp   nginx01

# 8、停止容器
[root@centos7 ~]# docker stop bc781c453438
bc781c453438
[root@centos7 ~]#

```

[![image-docker-4.png](https://i.postimg.cc/yNB5d21j/image-docker-4.png)](https://postimg.cc/yDQnpQS3)

端口暴露的概念

[![image-dcoker-5.png](https://i.postimg.cc/50Kks0wK/image-dcoker-5.png)](https://postimg.cc/WFrn3sY0)

### Tomcat

```shell
# 官方使用
# --rm 用完即删除 适合测试环境
[root@centos7 ~]# docker run -it --rm tomcat:9.0
Unable to find image 'tomcat:9.0' locally
9.0: Pulling from library/tomcat
d960726af2be: Pull complete
e8d62473a22d: Pull complete
8962bc0fad55: Pull complete
65d943ee54c1: Pull complete
da20b77f10ac: Pull complete
8669a096f083: Pull complete
e0c0a5e9ce88: Pull complete
f7f46169d747: Pull complete
215575e3a745: Pull complete
6b282851d654: Pull complete
Digest: sha256:9f502a5c7bafd4e1953dba4e77f9347c9211f987902ab8668a34997178f9bcd0
Status: Downloaded newer image for tomcat:9.0
Using CATALINA_BASE:   /usr/local/tomcat
Using CATALINA_HOME:   /usr/local/tomcat
Using CATALINA_TMPDIR: /usr/local/tomcat/temp
Using JRE_HOME:        /usr/local/openjdk-11
Using CLASSPATH:       /usr/local/tomcat/bin/bootstrap.jar:/usr/local/tomcat/bin/tomcat-juli.jar
Using CATALINA_OPTS:
NOTE: Picked up JDK_JAVA_OPTIONS:  --add-opens=java.base/java.lang=ALL-UNNAMED --add-opens=java.base/java.io=ALL-UNNAMED --add-opens=java.base/java.util=ALL-UNNAMED --add-opens=java.base/java.util.concurrent=ALL-UNNAMED --add-opens=java.rmi/sun.rmi.transport=ALL-UNNAMED
19-Jun-2021 02:06:50.472 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Server version name:   Apache Tomcat/9.0.48
19-Jun-2021 02:06:50.483 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Server built:          Jun 10 2021 09:22:01 UTC
19-Jun-2021 02:06:50.483 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Server version number: 9.0.48.0
19-Jun-2021 02:06:50.483 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log OS Name:               Linux
19-Jun-2021 02:06:50.484 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log OS Version:            3.10.0-1160.31.1.el7.x86_64
19-Jun-2021 02:06:50.484 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Architecture:          amd64
19-Jun-2021 02:06:50.484 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Java Home:             /usr/local/openjdk-11
19-Jun-2021 02:06:50.484 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log JVM Version:           11.0.11+9
19-Jun-2021 02:06:50.484 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log JVM Vendor:            Oracle Corporation
19-Jun-2021 02:06:50.484 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log CATALINA_BASE:         /usr/local/tomcat
19-Jun-2021 02:06:50.484 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log CATALINA_HOME:         /usr/local/tomcat
19-Jun-2021 02:06:50.494 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: --add-opens=java.base/java.lang=ALL-UNNAMED
19-Jun-2021 02:06:50.494 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: --add-opens=java.base/java.io=ALL-UNNAMED
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: --add-opens=java.base/java.util=ALL-UNNAMED
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: --add-opens=java.base/java.util.concurrent=ALL-UNNAMED
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: --add-opens=java.rmi/sun.rmi.transport=ALL-UNNAMED
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Djava.util.logging.config.file=/usr/local/tomcat/conf/logging.properties
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Djava.util.logging.manager=org.apache.juli.ClassLoaderLogManager
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Djdk.tls.ephemeralDHKeySize=2048
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Djava.protocol.handler.pkgs=org.apache.catalina.webresources
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Dorg.apache.catalina.security.SecurityListener.UMASK=0027
19-Jun-2021 02:06:50.495 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Dignore.endorsed.dirs=
19-Jun-2021 02:06:50.496 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Dcatalina.base=/usr/local/tomcat
19-Jun-2021 02:06:50.496 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Dcatalina.home=/usr/local/tomcat
19-Jun-2021 02:06:50.498 INFO [main] org.apache.catalina.startup.VersionLoggerListener.log Command line argument: -Djava.io.tmpdir=/usr/local/tomcat/temp
19-Jun-2021 02:06:50.508 INFO [main] org.apache.catalina.core.AprLifecycleListener.lifecycleEvent Loaded Apache Tomcat Native library [1.2.30] using APR version [1.6.5].
19-Jun-2021 02:06:50.508 INFO [main] org.apache.catalina.core.AprLifecycleListener.lifecycleEvent APR capabilities: IPv6 [true], sendfile [true], accept filters [false], random [true], UDS [true].
19-Jun-2021 02:06:50.508 INFO [main] org.apache.catalina.core.AprLifecycleListener.lifecycleEvent APR/OpenSSL configuration: useAprConnector [false], useOpenSSL [true]
19-Jun-2021 02:06:50.521 INFO [main] org.apache.catalina.core.AprLifecycleListener.initializeSSL OpenSSL successfully initialized [OpenSSL 1.1.1d  10 Sep 2019]
19-Jun-2021 02:06:51.333 INFO [main] org.apache.coyote.AbstractProtocol.init Initializing ProtocolHandler ["http-nio-8080"]
19-Jun-2021 02:06:51.400 INFO [main] org.apache.catalina.startup.Catalina.load Server initialization in [1396] milliseconds
19-Jun-2021 02:06:51.534 INFO [main] org.apache.catalina.core.StandardService.startInternal Starting service [Catalina]
19-Jun-2021 02:06:51.534 INFO [main] org.apache.catalina.core.StandardEngine.startInternal Starting Servlet engine: [Apache Tomcat/9.0.48]
19-Jun-2021 02:06:51.560 INFO [main] org.apache.coyote.AbstractProtocol.start Starting ProtocolHandler ["http-nio-8080"]
19-Jun-2021 02:06:51.606 INFO [main] org.apache.catalina.startup.Catalina.start Server startup in [206] milliseconds
^C19-Jun-2021 02:07:34.809 INFO [Thread-2] org.apache.coyote.AbstractProtocol.pause Pausing ProtocolHandler ["http-nio-8080"]
19-Jun-2021 02:07:34.828 INFO [Thread-2] org.apache.catalina.core.StandardService.stopInternal Stopping service [Catalina]
19-Jun-2021 02:07:34.838 INFO [Thread-2] org.apache.coyote.AbstractProtocol.stop Stopping ProtocolHandler ["http-nio-8080"]
19-Jun-2021 02:07:34.877 INFO [Thread-2] org.apache.coyote.AbstractProtocol.destroy Destroying ProtocolHandler ["http-nio-8080"]
[root@centos7 ~]# ^C

# 查找运行中容器
[root@centos7 ~]# docker ps
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
[root@centos7 ~]# docker ps -a
CONTAINER ID   IMAGE     COMMAND                  CREATED          STATUS                        PORTS     NAMES
bc781c453438   nginx     "/docker-entrypoint.…"   29 minutes ago   Exited (137) 13 minutes ago             nginx01
6d8882478a04   centos    "/bin/bash"              23 hours ago     Exited (0) 23 hours ago                 inspiring_taussig
a01aa4045648   centos    "/bin/sh -c 'while t…"   2 days ago       Exited (255) 23 hours ago               festive_montalcini
1c58ce5ef8c3   centos    "/bin/bash"              2 days ago       Exited (0) 2 days ago                   mystifying_cannon
[root@centos7 ~]#

# 1、下载镜像
[root@centos7 ~]# docker pull tomcat
Using default tag: latest
latest: Pulling from library/tomcat
Digest: sha256:9f502a5c7bafd4e1953dba4e77f9347c9211f987902ab8668a34997178f9bcd0
Status: Downloaded newer image for tomcat:latest
docker.io/library/tomcat:latest
[root@centos7 ~]# docker images
REPOSITORY   TAG       IMAGE ID       CREATED        SIZE
tomcat       9.0       5505f7218e4d   2 days ago     667MB
tomcat       latest    5505f7218e4d   2 days ago     667MB
nginx        latest    d1a364dc548d   3 weeks ago    133MB
centos       latest    300e315adb2f   6 months ago   209MB

# 2、启动容器
[root@centos7 ~]# docker run -d -p 3355:8080 --name tomcat01 tomcat
bb20b849a7ce6719ae9f6e6278d97fc2eeb43c3fceb1a22f8fabe649f3b20efa
[root@centos7 ~]#

# 3、测试访问没有问题

# 4、进入容器
[root@centos7 ~]# docker exec -it tomcat01 /bin/bas
root@bb20b849a7ce:/usr/local/tomcat# ll
bash: ll: command not found
root@bb20b849a7ce:/usr/local/tomcat# ls
BUILDING.txt  CONTRIBUTING.md  LICENSE  NOTICE  README.md  RELEASE-NOTES  RUNNING.txt  bin  conf  lib  logs  native-jni-lib  temp  webapps  webapps.dist  work
root@bb20b849a7ce:/usr/local/tomcat#

# 5、发现问题，Tomcat被阉割，没有linux命令，webapps
# 原因是阿里云镜像最小安装删除不必要东西

root@bb20b849a7ce:/usr/local/tomcat# ls
BUILDING.txt  CONTRIBUTING.md  LICENSE  NOTICE  README.md  RELEASE-NOTES  RUNNING.txt  bin  conf  lib  logs  native-jni-lib  temp  webapps  webapps.dist  work
root@bb20b849a7ce:/usr/local/tomcat# cd webapps
root@bb20b849a7ce:/usr/local/tomcat/webapps# ls
root@bb20b849a7ce:/usr/local/tomcat/webapps# cd ..
root@bb20b849a7ce:/usr/local/tomcat# cp -r webapps.dist/* webapps
root@bb20b849a7ce:/usr/local/tomcat# cd webapps
root@bb20b849a7ce:/usr/local/tomcat/webapps# ls
ROOT  docs  examples  host-manager  manager
root@bb20b849a7ce:/usr/local/tomcat/webapps#
```

[![image-20210619102330523-20220801230504-9ury3c1.png](https://i.postimg.cc/y65b9D6k/image-20210619102330523-20220801230504-9ury3c1.png)](https://postimg.cc/JtNxC4kL)

### Es+Kibana

```shell
# ElasticSearch 暴露端口太多
# ElasticSearch 十分耗内存
# ElasticSearch 的数据一般需要放置到安全目录？挂载
# --net somenetwork 网络配置
docker run -d --name elasticsearch -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" elasticsearch:7.6.2

# 启动了，Linux变卡，docker stats 查看内存CPU状态
[root@centos7 ~]#docker stats
CONTAINER ID   NAME            CPU %     MEM USAGE / LIMIT    MEM %     NET I/O     BLOCK I/O        PIDS
575e2e354c4a   elasticsearch   0.34%     1005MiB / 1.777GiB   55.23%    656B / 0B   1.53GB / 131MB   41


# 测试是否成功
[root@centos7 ~]# curl localhost:9200
{
  "name" : "575e2e354c4a",
  "cluster_name" : "docker-cluster",
  "cluster_uuid" : "rsauTenDTca7UhjJZPABig",
  "version" : {
    "number" : "7.6.2",
    "build_flavor" : "default",
    "build_type" : "docker",
    "build_hash" : "ef48eb35cf30adf4db14086e8aabd07ef6fb113f",
    "build_date" : "2020-03-26T06:34:37.794943Z",
    "build_snapshot" : false,
    "lucene_version" : "8.4.0",
    "minimum_wire_compatibility_version" : "6.8.0",
    "minimum_index_compatibility_version" : "6.0.0-beta1"
  },
  "tagline" : "You Know, for Search"
}
[root@centos7 ~]#
# 关闭、增加内存限制，修改配置文件 -e
docker run -d --name elasticsearch01 -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" -e ES_JAVA_OPTS="-Xms64m -Xmx512m" elasticsearch:7.6.2
# 测试
[root@centos7 ~]# docker run -d --name elasticsearch03 -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" -e ES_JAVA_OPTS="-Xms64m -Xmx512m" elasticsearch:7.6.2
15b88d7c7446553c132efda007c36ef94da06e6f4b5ed2ba0a17f9af30d5f4c6
[root@centos7 ~]# docker ps
CONTAINER ID   IMAGE                 COMMAND                  CREATED         STATUS         PORTS                                                                                  NAMES
15b88d7c7446   elasticsearch:7.6.2   "/usr/local/bin/dock…"   4 seconds ago   Up 4 seconds   0.0.0.0:9200->9200/tcp, :::9200->9200/tcp, 0.0.0.0:9300->9300/tcp, :::9300->9300/tcp   elasticsearch03
[root@centos7 ~]# docker stats
CONTAINER ID   NAME              CPU %     MEM USAGE / LIMIT     MEM %     NET I/O     BLOCK I/O    PIDS
15b88d7c7446   elasticsearch03   0.05%     251.3MiB / 1.777GiB   13.82%    656B / 0B   136MB / 0B   19
CONTAINER ID   NAME              CPU %     MEM USAGE / LIMIT     MEM %     NET I/O     BLOCK I/O    PIDS
15b88d7c7446   elasticsearch03   0.05%     251.3MiB / 1.777GiB   13.82%    656B / 0B   136MB / 0B   19
CONTAINER ID   NAME              CPU %     MEM USAGE / LIMIT     MEM %     NET I/O     BLOCK I/O    PIDS
15b88d7c7446   elasticsearch03   99.81%    272.8MiB / 1.777GiB   14.99%    656B / 0B   140MB / 0B   19
^C
[root@centos7 ~]#
```

ES 和 Kibana怎么互联

[![image-docker-5.png](https://i.postimg.cc/R0RYnGqB/image-docker-5.png)](https://postimg.cc/R3Wdk7cs)

### 可视化

==Portainer==

Docker图形化界面管理工具

```shell
[root@centos7 ~]# docker run -d -p 19000:9000 --name=portainer --restart=always -v /var/run/docker.sock:/var/run/docker.sock --privileged=true portainer/portainer-ce:latest

Unable to find image 'portainer/portainer:latest' locally
latest: Pulling from portainer/portainer
94cfa856b2b1: Pull complete
49d59ee0881a: Pull complete
a2300fd28637: Pull complete
Digest: sha256:fb45b43738646048a0a0cc74fcee2865b69efde857e710126084ee5de9be0f3f
Status: Downloaded newer image for portainer/portainer:latest
17ed1c084c4aa422c97d307f9489bc45d64ade996dceaf307a43f21e41f10a09
[root@centos7 ~]# docker ps
CONTAINER ID   IMAGE                 COMMAND                  CREATED          STATUS          PORTS                                                                                  NAMES
17ed1c084c4a   portainer/portainer   "/portainer"             2 minutes ago    Up 2 minutes    0.0.0.0:8088->9000/tcp, :::8088->9000/tcp                                              naughty_lehmann
15b88d7c7446   elasticsearch:7.6.2   "/usr/local/bin/dock…"   56 minutes ago   Up 56 minutes   0.0.0.0:9200->9200/tcp, :::9200->9200/tcp, 0.0.0.0:9300->9300/tcp, :::9300->9300/tcp   elasticsearch03
```

访问，**密码：portainer**

```shell
http://192.168.52.180:8088/#/init/admin
S05141123l@211
```

[![image-docker-8.png](https://i.postimg.cc/gJ2TyR66/image-docker-8.png)](https://postimg.cc/cKPh0vhs)

[![image-docker-9.png](https://i.postimg.cc/wjY4fnmz/image-docker-9.png)](https://postimg.cc/8jwbsK4X)

[![image-docker-10.png](https://i.postimg.cc/wj5fSFXm/image-docker-10.png)](https://postimg.cc/bZJ9nxFy)

==Rancher==

## portainer忘记密码如何重置

>https://www.cnblogs.com/A1999/p/15993682.html
1. 查看所有容器,包括未运行的
```shell
docker ps -a
```
2. 找到Portainer对应信息

3. 停止Portainer容器

```shell
docker stop portainerid
```
我这里就应该是
```shell
docker stop 507566f7086e
```

4. 找到Portainer容器挂载信息
```shell
docker inspect  portainerid
```
我这里就应该是
```sh
docker inspect 507566f7086e
```
找到这个信息"Source":"xxx"

5. 执行命令重置密码

```sh
docker run --rm -v /dockerpath:/data portainer/helper-reset-password
我这里应该是
docker run --rm -v /mnt/docker/portainer:/data portainer/helper-reset-password
```

现在admin登录的密码就为：4~!15SlshwmY#89FpcRE06u\{HL2(_Z:

6.启动容器,输入用户名密码就可以登录

```sh
docker start  portainerid
我这里就应该是
docker start 507566f7086e
```

7.修改Portainer登录密码





## Docker镜像

### 镜像是什么

### 加载原理

UnionFS(联合文件系统)

分层下载

### 分层理解

### commit 镜像

```shell
## 提交镜像为一个新的副本
docker commit

## 命令
docker commit -m="提交的描述信息" -a="作者" 容器ID 目标镜像名:[TAG]
```

实战测试

```shell
## 启动默认tomcat
docker run -it -p 8080:8080 tocat
ctrl + p + q
docker exec -it 容器ID

# 发现webapps下没有文件
# 拷贝文件到webapps
cp -r webapps.dist/* webapps

# 提交
[root@centos7 ~]# docker ps
CONTAINER ID   IMAGE     COMMAND             CREATED          STATUS          PORTS                                       NAMES
6868cb5454ee   tomcat    "catalina.sh run"   12 minutes ago   Up 12 minutes   0.0.0.0:8080->8080/tcp, :::8080->8080/tcp   hardcore_ardinghelli
# 打包提交镜像
[root@centos7 ~]# docker commit -a="sun" -m="add webapps app" 6868cb5454ee tomcat02:1.0
sha256:61485aa8d509c59e71125e3d29fb65f11e20cb661edfd0939470eadffd288cde
[root@centos7 ~]# docker images
REPOSITORY            TAG       IMAGE ID       CREATED         SIZE
tomcat02              1.0       61485aa8d509   5 seconds ago   672MB
tomcat                9.0       5505f7218e4d   3 days ago      667MB
tomcat                latest    5505f7218e4d   3 days ago      667MB
redis                 latest    fad0ee7e917a   2 weeks ago     105MB
nginx                 latest    d1a364dc548d   3 weeks ago     133MB
portainer/portainer   latest    580c0e4e98b0   3 months ago    79.1MB
centos                latest    300e315adb2f   6 months ago    209MB
elasticsearch         7.6.2     f29a1ee41030   15 months ago   791MB
[root@centos7 ~]#

```

## 容器数据卷

### 什么是容器数据卷

**总结：容器的持久化和同步！容器间也是可以数据共享的**

### 使用数据卷

#### 方法一：直接使用命令来挂载 -v

```shell
docker run -it -v 主机目录:容器内目录

[root@centos7 ~]# cd /home
[root@centos7 home]# ls
ldspdvs  sun.java  test.java

# 使用命令挂载
[root@centos7 home]# docker run -it -v /home/ceshi:/home centos /bin/bash
[root@d7bd1e6e693f /]# cd /home
[root@d7bd1e6e693f home]# ls
[root@d7bd1e6e693f home]# [root@centos7 home]#
[root@centos7 home]# ls
ceshi  ldspdvs  sun.java  test.java
[root@centos7 home]# docker ps
CONTAINER ID   IMAGE     COMMAND             CREATED         STATUS         PORTS                                       NAMES
d7bd1e6e693f   centos    "/bin/bash"         3 minutes ago   Up 3 minutes                                               flamboyant_gates
6868cb5454ee   tomcat    "catalina.sh run"   17 hours ago    Up 17 hours    0.0.0.0:8080->8080/tcp, :::8080->8080/tcp   hardcore_ardinghelli

# 查看相关信息
[root@centos7 home]# docker inspect d7bd1e6e693f
[
    {
        "Id": "d7bd1e6e693fc22f3db7734798b63c2eade1a7154a84b354661d3c546bc7718a",
        "Created": "2021-06-21T01:08:46.218734547Z",
        "Path": "/bin/bash",
        "Args": [],
        "State": {
            "Status": "running",
            "Running": true,
            "Paused": false,
            "Restarting": false,
            "OOMKilled": false,
            "Dead": false,
            "Pid": 4149,
            "ExitCode": 0,
            "Error": "",
            "StartedAt": "2021-06-21T01:08:48.057350529Z",
            "FinishedAt": "0001-01-01T00:00:00Z"
        },
        "Image": "sha256:300e315adb2f96afe5f0b2780b87f28ae95231fe3bdd1e16b9ba606307728f55",
        "ResolvConfPath": "/var/lib/docker/containers/d7bd1e6e693fc22f3db7734798b63c2eade1a7154a84b354661d3c546bc7718a/resolv.conf",
        "HostnamePath": "/var/lib/docker/containers/d7bd1e6e693fc22f3db7734798b63c2eade1a7154a84b354661d3c546bc7718a/hostname",
        "HostsPath": "/var/lib/docker/containers/d7bd1e6e693fc22f3db7734798b63c2eade1a7154a84b354661d3c546bc7718a/hosts",
        "LogPath": "/var/lib/docker/containers/d7bd1e6e693fc22f3db7734798b63c2eade1a7154a84b354661d3c546bc7718a/d7bd1e6e693fc22f3db7734798b63c2eade1a7154a84b354661d3c546bc7718a-json.log",
        "Name": "/flamboyant_gates",
        "RestartCount": 0,
        "Driver": "overlay2",
        "Platform": "linux",
        "MountLabel": "",
        "ProcessLabel": "",
        "AppArmorProfile": "",
        "ExecIDs": null,
        "HostConfig": {
            "Binds": [
                "/home/ceshi:/home"
            ],
            "ContainerIDFile": "",
            "LogConfig": {
                "Type": "json-file",
                "Config": {}
            },
            "NetworkMode": "default",
            "PortBindings": {},
            "RestartPolicy": {
                "Name": "no",
                "MaximumRetryCount": 0
            },
            "AutoRemove": false,
            "VolumeDriver": "",
            "VolumesFrom": null,
            "CapAdd": null,
            "CapDrop": null,
            "CgroupnsMode": "host",
            "Dns": [],
            "DnsOptions": [],
            "DnsSearch": [],
            "ExtraHosts": null,
            "GroupAdd": null,
            "IpcMode": "private",
            "Cgroup": "",
            "Links": null,
            "OomScoreAdj": 0,
            "PidMode": "",
            "Privileged": false,
            "PublishAllPorts": false,
            "ReadonlyRootfs": false,
            "SecurityOpt": null,
            "UTSMode": "",
            "UsernsMode": "",
            "ShmSize": 67108864,
            "Runtime": "runc",
            "ConsoleSize": [
                0,
                0
            ],
            "Isolation": "",
            "CpuShares": 0,
            "Memory": 0,
            "NanoCpus": 0,
            "CgroupParent": "",
            "BlkioWeight": 0,
            "BlkioWeightDevice": [],
            "BlkioDeviceReadBps": null,
            "BlkioDeviceWriteBps": null,
            "BlkioDeviceReadIOps": null,
            "BlkioDeviceWriteIOps": null,
            "CpuPeriod": 0,
            "CpuQuota": 0,
            "CpuRealtimePeriod": 0,
            "CpuRealtimeRuntime": 0,
            "CpusetCpus": "",
            "CpusetMems": "",
            "Devices": [],
            "DeviceCgroupRules": null,
            "DeviceRequests": null,
            "KernelMemory": 0,
            "KernelMemoryTCP": 0,
            "MemoryReservation": 0,
            "MemorySwap": 0,
            "MemorySwappiness": null,
            "OomKillDisable": false,
            "PidsLimit": null,
            "Ulimits": null,
            "CpuCount": 0,
            "CpuPercent": 0,
            "IOMaximumIOps": 0,
            "IOMaximumBandwidth": 0,
            "MaskedPaths": [
                "/proc/asound",
                "/proc/acpi",
                "/proc/kcore",
                "/proc/keys",
                "/proc/latency_stats",
                "/proc/timer_list",
                "/proc/timer_stats",
                "/proc/sched_debug",
                "/proc/scsi",
                "/sys/firmware"
            ],
            "ReadonlyPaths": [
                "/proc/bus",
                "/proc/fs",
                "/proc/irq",
                "/proc/sys",
                "/proc/sysrq-trigger"
            ]
        },
        "GraphDriver": {
            "Data": {
                "LowerDir": "/var/lib/docker/overlay2/711e9edb5aeec3c26ec8889f1c0879e6454012a527c73ec12d3a27a6f28298e0-init/diff:/var/lib/docker/overlay2/dbe0863967eda16db79356c5aa892895ef73d0afee2ecec4b52c209393f16103/diff",
                "MergedDir": "/var/lib/docker/overlay2/711e9edb5aeec3c26ec8889f1c0879e6454012a527c73ec12d3a27a6f28298e0/merged",
                "UpperDir": "/var/lib/docker/overlay2/711e9edb5aeec3c26ec8889f1c0879e6454012a527c73ec12d3a27a6f28298e0/diff",
                "WorkDir": "/var/lib/docker/overlay2/711e9edb5aeec3c26ec8889f1c0879e6454012a527c73ec12d3a27a6f28298e0/work"
            },
            "Name": "overlay2"
        },
        # 挂载
        "Mounts": [
            {
                "Type": "bind",
                "Source": "/home/ceshi",
                "Destination": "/home",
                "Mode": "",
                "RW": true,
                "Propagation": "rprivate"
            }
        ],
        "Config": {
            "Hostname": "d7bd1e6e693f",
            "Domainname": "",
            "User": "",
            "AttachStdin": true,
            "AttachStdout": true,
            "AttachStderr": true,
            "Tty": true,
            "OpenStdin": true,
            "StdinOnce": true,
            "Env": [
                "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
            ],
            "Cmd": [
                "/bin/bash"
            ],
            "Image": "centos",
            "Volumes": null,
            "WorkingDir": "",
            "Entrypoint": null,
            "OnBuild": null,
            "Labels": {
                "org.label-schema.build-date": "20201204",
                "org.label-schema.license": "GPLv2",
                "org.label-schema.name": "CentOS Base Image",
                "org.label-schema.schema-version": "1.0",
                "org.label-schema.vendor": "CentOS"
            }
        },
        "NetworkSettings": {
            "Bridge": "",
            "SandboxID": "5dde2a555d6ebe590a4cab2cc07ccac80e49289b0565d8c15a04b99ef5853765",
            "HairpinMode": false,
            "LinkLocalIPv6Address": "",
            "LinkLocalIPv6PrefixLen": 0,
            "Ports": {},
            "SandboxKey": "/var/run/docker/netns/5dde2a555d6e",
            "SecondaryIPAddresses": null,
            "SecondaryIPv6Addresses": null,
            "EndpointID": "608816e6eca9c267896e7254e97246a02ecbcb955148eddfe96e2dc6fb53856f",
            "Gateway": "172.17.0.1",
            "GlobalIPv6Address": "",
            "GlobalIPv6PrefixLen": 0,
            "IPAddress": "172.17.0.3",
            "IPPrefixLen": 16,
            "IPv6Gateway": "",
            "MacAddress": "02:42:ac:11:00:03",
            "Networks": {
                "bridge": {
                    "IPAMConfig": null,
                    "Links": null,
                    "Aliases": null,
                    "NetworkID": "2dc7231034028aab340034b6ff968fc0b71a79f04e5db48c916ac2b79d48476e",
                    "EndpointID": "608816e6eca9c267896e7254e97246a02ecbcb955148eddfe96e2dc6fb53856f",
                    "Gateway": "172.17.0.1",
                    "IPAddress": "172.17.0.3",
                    "IPPrefixLen": 16,
                    "IPv6Gateway": "",
                    "GlobalIPv6Address": "",
                    "GlobalIPv6PrefixLen": 0,
                    "MacAddress": "02:42:ac:11:00:03",
                    "DriverOpts": null
                }
            }
        }
    }
]
[root@centos7 home]#

```

[![image-docker-11.png](https://i.postimg.cc/SsRgYhw6/image-docker-11.png)](https://postimg.cc/DJVrRtf0)

![image-20210621104854490](assets/image-20210621104854490-20220801230504-bdr5h5j.png)

##### 实战：安装MySQL

```shell
# 获取镜像
[root@centos7 ~]# docker pull mysql:5.7
5.7: Pulling from library/mysql
69692152171a: Already exists 
1651b0be3df3: Pull complete 
951da7386bc8: Pull complete 
0f86c95aa242: Pull complete 
37ba2d8bd4fe: Pull complete 
6d278bb05e94: Pull complete 
497efbd93a3e: Pull complete 
a023ae82eef5: Pull complete 
e76c35f20ee7: Pull complete 
e887524d2ef9: Pull complete 
ccb65627e1c3: Pull complete 
Digest: sha256:a682e3c78fc5bd941e9db080b4796c75f69a28a8cad65677c23f7a9f18ba21fa
Status: Downloaded newer image for mysql:5.7
docker.io/library/mysql:5.7
[root@centos7 ~]# 

# 官方测试
docker run --name some-mysql -e MYSQL_ROOT_PASSWORD=my-secret-pw -d mysql:tag

# 运行容器需要做数据挂载， 安装MySQL配置密码为：123456
# -d 后台运行
# -p 开放端口
# -v 数据挂载
# -e 环境配置，配置密码
# --name 重命名
[root@centos7 ~]# docker run -d -p 3310:3306 -v /home/mysql/conf:/etc/mysql/conf.d -v /home/mysql/data:/var/lib/mysql -e MYSQL_ROOT_PASSWORD=123456 --name mysql01 mysql:5.7
db66837b45da8131de849b47d9bd0e90c52f4e1a8b11494ad0e31bb1e408516b
[root@centos7 ~]# 
```

**连接测试**

[![image-20210621162103825-20220801230504-imvacll.png](https://i.postimg.cc/9fW8VTbN/image-20210621162103825-20220801230504-imvacll.png)](https://postimg.cc/bZBH9ZKQ)

**本地创建数据库测试**

[![image-20210621162623201-20220801230504-k3qe6zz.png](https://i.postimg.cc/FzJGGxF1/image-20210621162623201-20220801230504-k3qe6zz.png)](https://postimg.cc/y3sF8cZz)

##### 具名挂载匿名挂载

```shell
# 匿名挂载
# -v 容器内路径
[root@centos7 mysql]# docker run -d -P --name nginx01 -v /etc/nginx nginx
f04206577f07e886fbffaaa65add7af434fecfacd82c56b9d22b1e252983f59b
[root@centos7 mysql]# docker volume

Usage:  docker volume COMMAND

Manage volumes

Commands:
  create      Create a volume
  inspect     Display detailed information on one or more volumes
  ls          List volumes
  prune       Remove all unused local volumes
  rm          Remove one or more volumes

Run 'docker volume COMMAND --help' for more information on a command.
# 查看所有volume 情况，匿名挂载（只写了容器内部路径，没有外部路径）
[root@centos7 mysql]# docker volume ls
DRIVER    VOLUME NAME
local     aa55538068166b2b900c9447c7a26d8f89866213e35b0b65eced751bab761cb5
local     c49dfa6ae87d3401c54e7f7b3d9aee03ada33dac5bf28fe19847defb2a2b2e19
[root@centos7 mysql]# 

# 具名挂载 
# -v 卷名:容器内路径
[root@centos7 home]# docker run -d -P --name nginx01 -v juming-nginx:/etc/nginx nginx
305679aa5ab8a41a506bc06d1065dd639d1687d20f292e7db786efc60c0fe257
[root@centos7 home]# docker volume ls
DRIVER    VOLUME NAME
local     juming-nginx
[root@centos7 home]# 

# 查看卷的位置
[root@centos7 home]# docker volume inspect juming-nginx
[
    {
        "CreatedAt": "2021-06-21T16:46:08+08:00",
        "Driver": "local",
        "Labels": null,
        "Mountpoint": "/var/lib/docker/volumes/juming-nginx/_data",
        "Name": "juming-nginx",
        "Options": null,
        "Scope": "local"
    }
]
[root@centos7 home]# 
# 所有挂载的卷都存在/var/lib/docker/volumes/xxx/_data
```

##### 如何确定具名挂载、匿名挂载、指定路径挂载

```shell
# 如何确定具名挂载、匿名挂载、指定路径挂载
-v 容器内路径				# 匿名挂载
-v 卷名:容器内路径			   # 具名挂载
-v /宿主机路径:容器内路径		 # 指定路径挂载
```

拓展

```shell
# 通过-v 容器内路径:ro / rw 改变读写情况
:ro	readonly	# 只读
:rw	readwrite	# 可读可写
[root@centos7 _data]# docker run -d -P --name nginx01 -v juming-nginx:/etc/nginx:ro nginx
[root@centos7 _data]# docker run -d -P --name nginx01 -v juming-nginx:/etc/nginx:rw nginx

# ro 只要看到ro就说明这个路径只能通过宿主机来操作，容器内部是无法操作的
```

#### 方法二：Dockerfile

dockerfile就是

```shell
# 编写dockerfile文件，名字随机，建议dockerfile
# 文件中内容 指令（大写） 参数
FROM centos

VOLUME ["/volume01"]

CMD echo "----end----"
CMD /bin/bash
# 这里的每个命令都是镜像的一层
[root@centos7 docker-test-volume]# docker build -f /home/docker-test-volume/dockerfile1 -t sun-centos:1.0 .
Sending build context to Docker daemon  2.048kB
Step 1/4 : FROM centos
 ---> 300e315adb2f
Step 2/4 : VOLUME ["volume01","volume02"]
 ---> Running in b36b79463beb
Removing intermediate container b36b79463beb
 ---> e71eafd862d1
Step 3/4 : CMD echo "----end----"
 ---> Running in 02491f2242ee
Removing intermediate container 02491f2242ee
 ---> dc91e948c128
Step 4/4 : CMD /bin/bash
 ---> Running in bc87399b42b0
Removing intermediate container bc87399b42b0
 ---> a6f24aa84bbd
Successfully built a6f24aa84bbd
Successfully tagged sun-centos:1.0
[root@centos7 docker-test-volume]# docker images
REPOSITORY            TAG       IMAGE ID       CREATED         SIZE
sun-centos            1.0       a6f24aa84bbd   8 seconds ago   209MB
tomcat02              1.0       61485aa8d509   25 hours ago    672MB
tomcat                9.0       5505f7218e4d   4 days ago      667MB
tomcat                latest    5505f7218e4d   4 days ago      667MB
redis                 latest    fad0ee7e917a   2 weeks ago     105MB
nginx                 latest    d1a364dc548d   3 weeks ago     133MB
mysql                 5.7       2c9028880e58   5 weeks ago     447MB
portainer/portainer   latest    580c0e4e98b0   3 months ago    79.1MB
centos                latest    300e315adb2f   6 months ago    209MB
elasticsearch         7.6.2     f29a1ee41030   15 months ago   791MB
[root@centos7 docker-test-volume]# 
# 运行容器
[root@centos7 docker-test-volume]# docker run -it 7d80e12c9a4b /bin/bash
[root@010849c53365 /]# ls -l
total 0
lrwxrwxrwx.   1 root root   7 Nov  3  2020 bin -> usr/bin
drwxr-xr-x.   5 root root 360 Jun 22 03:39 dev
drwxr-xr-x.   1 root root  66 Jun 22 03:39 etc
drwxr-xr-x.   2 root root   6 Nov  3  2020 home
lrwxrwxrwx.   1 root root   7 Nov  3  2020 lib -> usr/lib
lrwxrwxrwx.   1 root root   9 Nov  3  2020 lib64 -> usr/lib64
drwx------.   2 root root   6 Dec  4  2020 lost+found
drwxr-xr-x.   2 root root   6 Nov  3  2020 media
drwxr-xr-x.   2 root root   6 Nov  3  2020 mnt
drwxr-xr-x.   2 root root   6 Nov  3  2020 opt
dr-xr-xr-x. 189 root root   0 Jun 22 03:39 proc
dr-xr-x---.   2 root root 162 Dec  4  2020 root
drwxr-xr-x.  11 root root 163 Dec  4  2020 run
lrwxrwxrwx.   1 root root   8 Nov  3  2020 sbin -> usr/sbin
drwxr-xr-x.   2 root root   6 Nov  3  2020 srv
dr-xr-xr-x.  13 root root   0 Jun 20 08:21 sys
drwxrwxrwt.   7 root root 145 Dec  4  2020 tmp
drwxr-xr-x.  12 root root 144 Dec  4  2020 usr
drwxr-xr-x.  20 root root 262 Dec  4  2020 var
drwxr-xr-x.   2 root root   6 Jun 22 03:39 volume1
[root@010849c53365 /]# cd volume1/
[root@010849c53365 volume1]# ls
[root@010849c53365 volume1]# touch container.txt
[root@010849c53365 volume1]# ls
container.txt
[root@010849c53365 volume1]# 

# 查看挂载位置
[root@centos7 ~]# docker ps
CONTAINER ID   IMAGE          COMMAND       CREATED          STATUS              POR
010849c53365   fd96f4121255   "/bin/bash"   2 minutes ago    Up About a minute    
6f6ed0914c11   fd96f4121255   "/bin/bash"   49 minutes ago   Up 49 minutes        
[root@centos7 ~]# docker inspect 010849c53365
[
    {
        "Id": "010849c533651fbcf17685e23cd9a0334cb5a3de227d73780d0e0d0cfff73586",
        "Created": "2021-06-22T03:39:31.568552243Z",
        "Path": "/bin/bash",
        "Args": [],
        "State": {
            "Status": "running",
            "Running": true,
            "Paused": false,
            "Restarting": false,
            "OOMKilled": false,
            "Dead": false,
            "Pid": 12832,
            "ExitCode": 0,
            "Error": "",
            "StartedAt": "2021-06-22T03:39:32.96622469Z",
            "FinishedAt": "0001-01-01T00:00:00Z"
        },
        "Image": "sha256:fd96f41212555eefb88d461ee204bb87f0549c3b3c707bb4d8fa71c2e51
        "ResolvConfPath": "/var/lib/docker/containers/010849c533651fbcf17685e23cd9a0
        "HostnamePath": "/var/lib/docker/containers/010849c533651fbcf17685e23cd9a033
        "HostsPath": "/var/lib/docker/containers/010849c533651fbcf17685e23cd9a0334cb
        "LogPath": "/var/lib/docker/containers/010849c533651fbcf17685e23cd9a0334cb5a73586-json.log",
        "Name": "/eager_mirzakhani",
        "RestartCount": 0,
        "Driver": "overlay2",
        "Platform": "linux",
        "MountLabel": "",
        "ProcessLabel": "",
        "AppArmorProfile": "",
        "ExecIDs": null,
        "HostConfig": {
            "Binds": null,
            "ContainerIDFile": "",
            "LogConfig": {
                "Type": "json-file",
                "Config": {}
            },
            "NetworkMode": "default",
            "PortBindings": {},
            "RestartPolicy": {
                "Name": "no",
                "MaximumRetryCount": 0
            },
            "AutoRemove": false,
            "VolumeDriver": "",
            "VolumesFrom": null,
            "CapAdd": null,
            "CapDrop": null,
            "CgroupnsMode": "host",
            "Dns": [],
            "DnsOptions": [],
            "DnsSearch": [],
            "ExtraHosts": null,
            "GroupAdd": null,
            "IpcMode": "private",
            "Cgroup": "",
            "Links": null,
            "OomScoreAdj": 0,
            "PidMode": "",
            "Privileged": false,
            "PublishAllPorts": false,
            "ReadonlyRootfs": false,
            "SecurityOpt": null,
            "UTSMode": "",
            "UsernsMode": "",
            "ShmSize": 67108864,
            "Runtime": "runc",
            "ConsoleSize": [
                0,
                0
            ],
            "Isolation": "",
            "CpuShares": 0,
            "Memory": 0,
            "NanoCpus": 0,
            "CgroupParent": "",
            "BlkioWeight": 0,
            "BlkioWeightDevice": [],
            "BlkioDeviceReadBps": null,
            "BlkioDeviceWriteBps": null,
            "BlkioDeviceReadIOps": null,
            "BlkioDeviceWriteIOps": null,
            "CpuPeriod": 0,
            "CpuQuota": 0,
            "CpuRealtimePeriod": 0,
            "CpuRealtimeRuntime": 0,
            "CpusetCpus": "",
            "CpusetMems": "",
            "Devices": [],
            "DeviceCgroupRules": null,
            "DeviceRequests": null,
            "KernelMemory": 0,
            "KernelMemoryTCP": 0,
            "MemoryReservation": 0,
            "MemorySwap": 0,
            "MemorySwappiness": null,
            "OomKillDisable": false,
            "PidsLimit": null,
            "Ulimits": null,
            "CpuCount": 0,
            "CpuPercent": 0,
            "IOMaximumIOps": 0,
            "IOMaximumBandwidth": 0,
            "MaskedPaths": [
                "/proc/asound",
                "/proc/acpi",
                "/proc/kcore",
                "/proc/keys",
                "/proc/latency_stats",
                "/proc/timer_list",
                "/proc/timer_stats",
                "/proc/sched_debug",
                "/proc/scsi",
                "/sys/firmware"
            ],
            "ReadonlyPaths": [
                "/proc/bus",
                "/proc/fs",
                "/proc/irq",
                "/proc/sys",
                "/proc/sysrq-trigger"
            ]
        },
        "GraphDriver": {
            "Data": {
                "LowerDir": "/var/lib/docker/overlay2/f50fba6d9d1be7b03cd4e0f5a7f5d179356c5aa892895ef73d0afee2ecec4b52c209393f16103/diff",
                "MergedDir": "/var/lib/docker/overlay2/f50fba6d9d1be7b03cd4e0f5a7f5d
                "UpperDir": "/var/lib/docker/overlay2/f50fba6d9d1be7b03cd4e0f5a7f5d1
                "WorkDir": "/var/lib/docker/overlay2/f50fba6d9d1be7b03cd4e0f5a7f5d1b
            },
            "Name": "overlay2"
        },
        "Mounts": [
            {
                "Type": "volume",
                "Name": "9e3b0fdaaa5d64a9911c2600aee6b0ecda1f26efc8598056a361ea860cf
                "Source": "/var/lib/docker/volumes/9e3b0fdaaa5d64a9911c2600aee6b0ecd
                "Destination": "/volume1",
                "Driver": "local",
                "Mode": "",
                "RW": true,
                "Propagation": ""
            }
        ],
        "Config": {
            "Hostname": "010849c53365",
            "Domainname": "",
            "User": "",
            "AttachStdin": true,
            "AttachStdout": true,
            "AttachStderr": true,
            "Tty": true,
            "OpenStdin": true,
            "StdinOnce": true,
            "Env": [
                "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
            ],
            "Cmd": [
                "/bin/bash"
            ],
            "Image": "fd96f4121255",
            "Volumes": {
                "/volume1": {}
            },
            "WorkingDir": "",
            "Entrypoint": null,
            "OnBuild": null,
            "Labels": {
                "org.label-schema.build-date": "20201204",
                "org.label-schema.license": "GPLv2",
                "org.label-schema.name": "CentOS Base Image",
                "org.label-schema.schema-version": "1.0",
                "org.label-schema.vendor": "CentOS"
            }
        },
        "NetworkSettings": {
            "Bridge": "",
            "SandboxID": "ba03c4ece79e4dc6486fdbefd41b1027d4ed45fbfb52f96dd625b94e7e
            "HairpinMode": false,
            "LinkLocalIPv6Address": "",
            "LinkLocalIPv6PrefixLen": 0,
            "Ports": {},
            "SandboxKey": "/var/run/docker/netns/ba03c4ece79e",
            "SecondaryIPAddresses": null,
            "SecondaryIPv6Addresses": null,
            "EndpointID": "68b6affc5b24788b8b0cd59956fcdbf74d15333153a93beb5d87758a4
            "Gateway": "172.17.0.1",
            "GlobalIPv6Address": "",
            "GlobalIPv6PrefixLen": 0,
            "IPAddress": "172.17.0.3",
            "IPPrefixLen": 16,
            "IPv6Gateway": "",
            "MacAddress": "02:42:ac:11:00:03",
            "Networks": {
                "bridge": {
                    "IPAMConfig": null,
                    "Links": null,
                    "Aliases": null,
                    "NetworkID": "2dc7231034028aab340034b6ff968fc0b71a79f04e5db48c91
                    "EndpointID": "68b6affc5b24788b8b0cd59956fcdbf74d15333153a93beb5
                    "Gateway": "172.17.0.1",
                    "IPAddress": "172.17.0.3",
                    "IPPrefixLen": 16,
                    "IPv6Gateway": "",
                    "GlobalIPv6Address": "",
                    "GlobalIPv6PrefixLen": 0,
                    "MacAddress": "02:42:ac:11:00:03",
                    "DriverOpts": null
                }
            }
        }
    }
]
[root@centos7 ~]# cd /var/lib/docker/volumes/9e3b0fdaaa5d64a9911c2600aee6b0ecda1f26e
[root@centos7 _data]# ls
container.txt
[root@centos7 _data]# 
```

### 数据卷容器

多个MySQL同步数据

[![image-20210622154718480-20220801230504-91pyrj8.png](https://i.postimg.cc/vDFhK6Dh/image-20210622154718480-20220801230504-91pyrj8.png)](https://postimg.cc/xN5LJ8vN)

==测试==，3个同步

```shell
# 启动第一个容器
[root@centos7 ~]# docker images
REPOSITORY            TAG       IMAGE ID       CREATED         SIZE
sun/centos            1.0       fd96f4121255   5 hours ago     209MB
tomcat02              1.0       61485aa8d509   47 hours ago    672MB
tomcat                9.0       5505f7218e4d   5 days ago      667MB
tomcat                latest    5505f7218e4d   5 days ago      667MB
redis                 latest    fad0ee7e917a   2 weeks ago     105MB
nginx                 latest    d1a364dc548d   3 weeks ago     133MB
mysql                 5.7       2c9028880e58   5 weeks ago     447MB
portainer/portainer   latest    580c0e4e98b0   3 months ago    79.1MB
centos                latest    300e315adb2f   6 months ago    209MB
elasticsearch         7.6.2     f29a1ee41030   15 months ago   791MB
[root@centos7 ~]# docker run -it --name docker01 fd96f4121255
[root@21e6fb0d15cd /]# ls -l
total 0
lrwxrwxrwx.   1 root root   7 Nov  3  2020 bin -> usr/bin
drwxr-xr-x.   5 root root 360 Jun 22 07:22 dev
drwxr-xr-x.   1 root root  66 Jun 22 07:22 etc
drwxr-xr-x.   2 root root   6 Nov  3  2020 home
lrwxrwxrwx.   1 root root   7 Nov  3  2020 lib -> usr/lib
lrwxrwxrwx.   1 root root   9 Nov  3  2020 lib64 -> usr/lib64
drwx------.   2 root root   6 Dec  4  2020 lost+found
drwxr-xr-x.   2 root root   6 Nov  3  2020 media
drwxr-xr-x.   2 root root   6 Nov  3  2020 mnt
drwxr-xr-x.   2 root root   6 Nov  3  2020 opt
dr-xr-xr-x. 185 root root   0 Jun 22 07:22 proc
dr-xr-x---.   2 root root 162 Dec  4  2020 root
drwxr-xr-x.  11 root root 163 Dec  4  2020 run
lrwxrwxrwx.   1 root root   8 Nov  3  2020 sbin -> usr/sbin
drwxr-xr-x.   2 root root   6 Nov  3  2020 srv
dr-xr-xr-x.  13 root root   0 Jun 20 08:21 sys
drwxrwxrwt.   7 root root 145 Dec  4  2020 tmp
drwxr-xr-x.  12 root root 144 Dec  4  2020 usr
drwxr-xr-x.  20 root root 262 Dec  4  2020 var
drwxr-xr-x.   2 root root   6 Jun 22 07:22 volume1
[root@21e6fb0d15cd /]# 
# 启动第二个容器
[root@centos7 ~]# docker run -it --name docker02 --volumes-from docker01 sun/centos:1.0
[root@9c8e6cb85c3f /]# ls -l
total 0
lrwxrwxrwx.   1 root root   7 Nov  3  2020 bin -> usr/bin
drwxr-xr-x.   5 root root 360 Jun 22 07:25 dev
drwxr-xr-x.   1 root root  66 Jun 22 07:25 etc
drwxr-xr-x.   2 root root   6 Nov  3  2020 home
lrwxrwxrwx.   1 root root   7 Nov  3  2020 lib -> usr/lib
lrwxrwxrwx.   1 root root   9 Nov  3  2020 lib64 -> usr/lib64
drwx------.   2 root root   6 Dec  4  2020 lost+found
drwxr-xr-x.   2 root root   6 Nov  3  2020 media
drwxr-xr-x.   2 root root   6 Nov  3  2020 mnt
drwxr-xr-x.   2 root root   6 Nov  3  2020 opt
dr-xr-xr-x. 186 root root   0 Jun 22 07:25 proc
dr-xr-x---.   2 root root 162 Dec  4  2020 root
drwxr-xr-x.  11 root root 163 Dec  4  2020 run
lrwxrwxrwx.   1 root root   8 Nov  3  2020 sbin -> usr/sbin
drwxr-xr-x.   2 root root   6 Nov  3  2020 srv
dr-xr-xr-x.  13 root root   0 Jun 20 08:21 sys
drwxrwxrwt.   7 root root 145 Dec  4  2020 tmp
drwxr-xr-x.  12 root root 144 Dec  4  2020 usr
drwxr-xr-x.  20 root root 262 Dec  4  2020 var
drwxr-xr-x.   2 root root   6 Jun 22 07:22 volume1
[root@9c8e6cb85c3f /]# 
```

容器同步数据，删除docker01之后，数据依然存在

[![image-20210622153303293-20220801230504-4mcr7pn.png](https://i.postimg.cc/Y25w7nWn/image-20210622153303293-20220801230504-4mcr7pn.png)](https://postimg.cc/ThJsqcQg)

#### 多个MySQL实现数据共享

```shell
[root@centos7 ~]# docker run -d -p 3310:3306 -v /etc/mysql/conf.d -v /var/lib/mysql -e MYSQL_ROOT_PASSWORD=123456 --name mysql01 mysql:5.7

[root@centos7 ~]# docker run -d -p 3310:3306 -e MYSQL_ROOT_PASSWORD=123456 --name mysql02 --volumes-from mysql01 mysql:5.7
```

## DockerFile

DockerFile介绍

dockerfile是用来构建docker镜像的主要工具

1. 编写docker file文件
2. docker build 构建镜像
3. docker run运行镜像
4. docker push发布镜像

[![image-20210622164648546-20220801230504-7ittz0h.png](https://i.postimg.cc/zGjmnqP6/image-20210622164648546-20220801230504-7ittz0h.png)](https://postimg.cc/87jnGgGm)

[![image-20210622164718336-20220801230504-73eqjwm.png](https://i.postimg.cc/NjYq9KbR/image-20210622164718336-20220801230504-73eqjwm.png)](https://postimg.cc/0btHh2TN)

### DockerFile构建过程

### DockerFile指令

```shell
FROM			# 基础镜像，一切从这里开始构建
MAINTAINER		# 镜像是谁写的，姓名+邮箱
RUN 			# 镜像构建的时候运行的命令
ADD				# 步骤；Tomcat镜像，这个Tomcat压缩包！添加内容
WORKDIR			# 镜像的工作目录
VOLUME			# 挂载的目录
EXPOST			# 暴露端口配置
CMD				# 指定这个容器启动的时候要运行的命令，只有最后一个会生效，可被替代
ENTRYPOINT		# 制定这个容器启动时候运行的命令，可以追加命
ONBUILD			# 当构建一个被继承dockerfile这时候运行ONBUILD的指令，触发指令
COPY			# 类似ADD，将我们文件拷贝到镜像中
ENV				# 构建的时候设置环境变量
```

[![image-20210622170415805-20220801230504-ju8j9yp.png](https://i.postimg.cc/zXTYGCwJ/image-20210622170415805-20220801230504-ju8j9yp.png)](https://postimg.cc/cr1bD85j)

### 实战cebtos测试

Dockerhub上多数镜像都是从这个基础镜像过来的FROM scratch

[![image-20210622170956986-20220801230504-mp0tr7p.png](https://i.postimg.cc/NMZZgF59/image-20210622170956986-20220801230504-mp0tr7p.png)](https://postimg.cc/BLcmpq54)

==创建自己的centos==

```shell
# 编写dockerfile文件
[root@centos7 ~]# cd /home
[root@centos7 home]# ls
ceshi  docker-test-volume  ldspdvs  mysql  sun.java  test.java
[root@centos7 home]# mkdir dockerfile
[root@centos7 home]# cd dockerfile/
[root@centos7 dockerfile]# ls
[root@centos7 dockerfile]# vim mydockerfile
[root@centos7 dockerfile]# cat mydockerfile 
FROM centos
MAINTAINER sun<skywalker0@qq.com>
ENV MYPATH /usr/local

WORKDIR $MYPATH

RUN yum install vim
RUN yum install net-tools

EXPOSE 80
CMD echo $MYPATH
CMD "====END===="
CMD /bin/bash
# 开始构建
[root@centos7 dockerfile]# docker build -f mydockerfile -t mycentos:0.1 .
Sending build context to Docker daemon  2.048kB
Step 1/10 : FROM centos
 ---> 300e315adb2f
Step 2/10 : MAINTAINER sun<skywalker0@qq.com>
 ---> Running in 739b57131710
Removing intermediate container 739b57131710
 ---> 29ad5f97ca5b
Step 3/10 : ENV MYPATH /usr/local
 ---> Running in 1d7ee28b2250
Removing intermediate container 1d7ee28b2250
 ---> ddf6af18fc09
Step 4/10 : WORKDIR $MYPATH
 ---> Running in 40a1b3882030
Removing intermediate container 40a1b3882030
 ---> a546b4765636
Step 5/10 : RUN yum -y install vim
 ---> Running in 75a3034c74ba
CentOS Linux 8 - AppStream                      4.5 MB/s | 7.5 MB     00:01  
CentOS Linux 8 - BaseOS                         895 kB/s | 2.6 MB     00:02  
CentOS Linux 8 - Extras                          12 kB/s | 9.6 kB     00:00  
Last metadata expiration check: 0:00:01 ago on Tue Jun 22 09:29:31 2021.
Dependencies resolved.
================================================================================
 Package             Arch        Version                   Repository      Size
================================================================================
Installing:
 vim-enhanced        x86_64      2:8.0.1763-15.el8         appstream      1.4 M
Installing dependencies:
 gpm-libs            x86_64      1.20.7-17.el8             appstream       39 k
 vim-common          x86_64      2:8.0.1763-15.el8         appstream      6.3 M
 vim-filesystem      noarch      2:8.0.1763-15.el8         appstream       48 k
 which               x86_64      2.21-12.el8               baseos          49 k

Transaction Summary
================================================================================
Install  5 Packages

Total download size: 7.8 M
Installed size: 30 M
Downloading Packages:
(1/5): gpm-libs-1.20.7-17.el8.x86_64.rpm        137 kB/s |  39 kB     00:00  
(2/5): vim-filesystem-8.0.1763-15.el8.noarch.rp 486 kB/s |  48 kB     00:00  
(3/5): which-2.21-12.el8.x86_64.rpm              72 kB/s |  49 kB     00:00  
(4/5): vim-enhanced-8.0.1763-15.el8.x86_64.rpm  1.3 MB/s | 1.4 MB     00:01  
(5/5): vim-common-8.0.1763-15.el8.x86_64.rpm    5.9 MB/s | 6.3 MB     00:01  
--------------------------------------------------------------------------------
Total                                           3.4 MB/s | 7.8 MB     00:02   
warning: /var/cache/dnf/appstream-02e86d1c976ab532/packages/gpm-libs-1.20.7-17.el8.x86_64.rpm: Header V3 RSA/SHA256 Signature, key ID 8483c65d: NOKEY
CentOS Linux 8 - AppStream                      166 kB/s | 1.6 kB     00:00  
Importing GPG key 0x8483C65D:
 Userid     : "CentOS (CentOS Official Signing Key) <security@centos.org>"
 Fingerprint: 99DB 70FA E1D7 CE22 7FB6 4882 05B5 55B3 8483 C65D
 From       : /etc/pki/rpm-gpg/RPM-GPG-KEY-centosofficial
Key imported successfully
Running transaction check
Transaction check succeeded.
Running transaction test
Transaction test succeeded.
Running transaction
  Preparing        :                                                        1/1 
  Installing       : which-2.21-12.el8.x86_64                               1/5 
  Installing       : vim-filesystem-2:8.0.1763-15.el8.noarch                2/5 
  Installing       : vim-common-2:8.0.1763-15.el8.x86_64                    3/5 
  Installing       : gpm-libs-1.20.7-17.el8.x86_64                          4/5 
  Running scriptlet: gpm-libs-1.20.7-17.el8.x86_64                          4/5 
  Installing       : vim-enhanced-2:8.0.1763-15.el8.x86_64                  5/5 
  Running scriptlet: vim-enhanced-2:8.0.1763-15.el8.x86_64                  5/5 
  Running scriptlet: vim-common-2:8.0.1763-15.el8.x86_64                    5/5 
  Verifying        : gpm-libs-1.20.7-17.el8.x86_64                          1/5 
  Verifying        : vim-common-2:8.0.1763-15.el8.x86_64                    2/5 
  Verifying        : vim-enhanced-2:8.0.1763-15.el8.x86_64                  3/5 
  Verifying        : vim-filesystem-2:8.0.1763-15.el8.noarch                4/5 
  Verifying        : which-2.21-12.el8.x86_64                               5/5 

Installed:
  gpm-libs-1.20.7-17.el8.x86_64         vim-common-2:8.0.1763-15.el8.x86_64  
  vim-enhanced-2:8.0.1763-15.el8.x86_64 vim-filesystem-2:8.0.1763-15.el8.noarch
  which-2.21-12.el8.x86_64           

Complete!
Removing intermediate container 75a3034c74ba
 ---> 1255cabbbf83
Step 6/10 : RUN yum -y install net-tools
 ---> Running in fa9d065790b6
Last metadata expiration check: 0:00:28 ago on Tue Jun 22 09:29:31 2021.
Dependencies resolved.
================================================================================
 Package         Architecture Version                        Repository    Size
================================================================================
Installing:
 net-tools       x86_64       2.0-0.52.20160912git.el8       baseos       322 k

Transaction Summary
================================================================================
Install  1 Package

Total download size: 322 k
Installed size: 942 k
Downloading Packages:
net-tools-2.0-0.52.20160912git.el8.x86_64.rpm   395 kB/s | 322 kB     00:00  
--------------------------------------------------------------------------------
Total                                           258 kB/s | 322 kB     00:01   
Running transaction check
Transaction check succeeded.
Running transaction test
Transaction test succeeded.
Running transaction
  Preparing        :                                                        1/1 
  Installing       : net-tools-2.0-0.52.20160912git.el8.x86_64              1/1 
  Running scriptlet: net-tools-2.0-0.52.20160912git.el8.x86_64              1/1 
  Verifying        : net-tools-2.0-0.52.20160912git.el8.x86_64              1/1 

Installed:
  net-tools-2.0-0.52.20160912git.el8.x86_64                                   

Complete!
Removing intermediate container fa9d065790b6
 ---> 322759aa809c
Step 7/10 : EXPOSE 80
 ---> Running in e970b836aa84
Removing intermediate container e970b836aa84
 ---> 509ce133ae12
Step 8/10 : CMD echo $MYPATH
 ---> Running in 41bd2f1f7a2f
Removing intermediate container 41bd2f1f7a2f
 ---> 3cbf69399d4b
Step 9/10 : CMD echo "====END===="
 ---> Running in 62af383c922e
Removing intermediate container 62af383c922e
 ---> cef3ff258ffa
Step 10/10 : CMD /bin/bash
 ---> Running in d719cbfbb9f5
Removing intermediate container d719cbfbb9f5
 ---> ef11becad48a
Successfully built ef11becad48a
Successfully tagged mycentos:0.1
[root@centos7 dockerfile]# 

# 验证测试
[root@centos7 dockerfile]# docker images
REPOSITORY            TAG       IMAGE ID       CREATED              SIZE
mycentos              0.1       ef11becad48a   About a minute ago   295MB
sun/centos            1.0       fd96f4121255   7 hours ago          209MB
tomcat02              1.0       61485aa8d509   2 days ago           672MB
tomcat                9.0       5505f7218e4d   5 days ago           667MB
tomcat                latest    5505f7218e4d   5 days ago           667MB
redis                 latest    fad0ee7e917a   2 weeks ago          105MB
nginx                 latest    d1a364dc548d   3 weeks ago          133MB
mysql                 5.7       2c9028880e58   5 weeks ago          447MB
portainer/portainer   latest    580c0e4e98b0   3 months ago         79.1MB
centos                latest    300e315adb2f   6 months ago         209MB
elasticsearch         7.6.2     f29a1ee41030   15 months ago        791MB
[root@centos7 dockerfile]# docker run -it mycentos:0.1
# 默认工作目录
[root@e09c800665d1 local]# pwd
/usr/local
# 测试ifconfig
[root@e09c800665d1 local]# ifconfig
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.17.0.4  netmask 255.255.0.0  broadcast 172.17.255.255
        ether 02:42:ac:11:00:04  txqueuelen 0  (Ethernet)
        RX packets 8  bytes 656 (656.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
# 测试vim
[root@e09c800665d1 local]# vim test

# 查看构建过程
[root@centos7 ~]# docker images
REPOSITORY            TAG       IMAGE ID       CREATED          SIZE
mycentos              0.1       ef11becad48a   18 minutes ago   295MB
sun/centos            1.0       fd96f4121255   7 hours ago      209MB
tomcat02              1.0       61485aa8d509   2 days ago       672MB
tomcat                9.0       5505f7218e4d   5 days ago       667MB
tomcat                latest    5505f7218e4d   5 days ago       667MB
redis                 latest    fad0ee7e917a   2 weeks ago      105MB
nginx                 latest    d1a364dc548d   3 weeks ago      133MB
mysql                 5.7       2c9028880e58   5 weeks ago      447MB
portainer/portainer   latest    580c0e4e98b0   3 months ago     79.1MB
centos                latest    300e315adb2f   6 months ago     209MB
elasticsearch         7.6.2     f29a1ee41030   15 months ago    791MB
[root@centos7 ~]# docker history ef11becad48a
IMAGE          CREATED          CREATED BY                                      SIZE      COMMENT
ef11becad48a   19 minutes ago   /bin/sh -c #(nop)  CMD ["/bin/sh" "-c" "/bin…   0B      
cef3ff258ffa   19 minutes ago   /bin/sh -c #(nop)  CMD ["/bin/sh" "-c" "echo…   0B      
3cbf69399d4b   19 minutes ago   /bin/sh -c #(nop)  CMD ["/bin/sh" "-c" "echo…   0B      
509ce133ae12   19 minutes ago   /bin/sh -c #(nop)  EXPOSE 80                    0B      
322759aa809c   19 minutes ago   /bin/sh -c yum -y install net-tools             24.9MB  
1255cabbbf83   19 minutes ago   /bin/sh -c yum -y install vim                   60.7MB  
a546b4765636   19 minutes ago   /bin/sh -c #(nop) WORKDIR /usr/local            0B      
ddf6af18fc09   19 minutes ago   /bin/sh -c #(nop)  ENV MYPATH=/usr/local        0B      
29ad5f97ca5b   19 minutes ago   /bin/sh -c #(nop)  MAINTAINER sun<skywalker0…   0B      
300e315adb2f   6 months ago     /bin/sh -c #(nop)  CMD ["/bin/bash"]            0B      
<missing>      6 months ago     /bin/sh -c #(nop)  LABEL org.label-schema.sc…   0B      
<missing>      6 months ago     /bin/sh -c #(nop) ADD file:bd7a2aed6ede423b7…   209MB   
[root@centos7 ~]# 

```

==CMD和ENTRYPOINT的区别==

```shell
CMD				# 指定这个容器启动的时候运行的命令，只有最后一个会生效，可被替代
ENTRYPOINT		# 指定这个容器启动的时候要运行的命令，可以追加命令
```

测试CMD

```shell
[root@centos7 dockerfile]# touch cmdfile
[root@centos7 dockerfile]# vim cmdfile 
[root@centos7 dockerfile]# ls
cmdfile  mydockerfile
[root@centos7 dockerfile]# cat cmdfile 
FROM centos

CMD ["ls","-a"]
[root@centos7 dockerfile]# docker build -f cmdfile -t cmdtest .
Sending build context to Docker daemon  3.072kB
Step 1/2 : FROM centos
 ---> 300e315adb2f
Step 2/2 : CMD ["ls","-a"]
 ---> Running in c26847036d1d
Removing intermediate container c26847036d1d
 ---> da2d7b4985a1
Successfully built da2d7b4985a1
Successfully tagged cmdtest:latest
[root@centos7 dockerfile]# docker run -it da2d7b4985a1
.   .dockerenv	dev  home  lib64       media  opt   root  sbin	sys  usr
..  bin		etc  lib   lost+found  mnt    proc  run   srv	tmp  var

# 想追加一个命令-l ls -al
[root@centos7 dockerfile]# docker run da2d7b4985a1 -l
docker: Error response from daemon: OCI runtime create failed: container_linux.go:380: starting container process caused: exec: "-l": executable file not found in $PATH: unknown.

# CMD的清理下，-l替换了CMD["ls","-a"]命令，-l不是命令所以报错
[root@centos7 dockerfile]# docker run da2d7b4985a1 ls -al
total 0
drwxr-xr-x.   1 root root   6 Jun 23 02:52 .
drwxr-xr-x.   1 root root   6 Jun 23 02:52 ..
-rwxr-xr-x.   1 root root   0 Jun 23 02:52 .dockerenv
lrwxrwxrwx.   1 root root   7 Nov  3  2020 bin -> usr/bin
drwxr-xr-x.   5 root root 340 Jun 23 02:52 dev
drwxr-xr-x.   1 root root  66 Jun 23 02:52 etc
drwxr-xr-x.   2 root root   6 Nov  3  2020 home
lrwxrwxrwx.   1 root root   7 Nov  3  2020 lib -> usr/lib
lrwxrwxrwx.   1 root root   9 Nov  3  2020 lib64 -> usr/lib64
drwx------.   2 root root   6 Dec  4  2020 lost+found
drwxr-xr-x.   2 root root   6 Nov  3  2020 media
drwxr-xr-x.   2 root root   6 Nov  3  2020 mnt
drwxr-xr-x.   2 root root   6 Nov  3  2020 opt
dr-xr-xr-x. 188 root root   0 Jun 23 02:52 proc
dr-xr-x---.   2 root root 162 Dec  4  2020 root
drwxr-xr-x.  11 root root 163 Dec  4  2020 run
lrwxrwxrwx.   1 root root   8 Nov  3  2020 sbin -> usr/sbin
drwxr-xr-x.   2 root root   6 Nov  3  2020 srv
dr-xr-xr-x.  13 root root   0 Jun 20 08:21 sys
drwxrwxrwt.   7 root root 145 Dec  4  2020 tmp
drwxr-xr-x.  12 root root 144 Dec  4  2020 usr
drwxr-xr-x.  20 root root 262 Dec  4  2020 var
[root@centos7 dockerfile]# 


# 测试 ENTRYPOINT
[root@centos7 dockerfile]# vim dockerfile-entrypoint
[root@centos7 dockerfile]# cat dockerfile-entrypoint 
FROM centos

ENTRYPOINT ["ls","-a"]
[root@centos7 dockerfile]# docker build -f dockerfile-entrypoint -t docker-entrypoint-test .
Sending build context to Docker daemon  4.096kB
Step 1/2 : FROM centos
 ---> 300e315adb2f
Step 2/2 : ENTRYPOINT ["ls","-a"]
 ---> Running in 8dcb269c923b
Removing intermediate container 8dcb269c923b
 ---> 8524617105fd
Successfully built 8524617105fd
Successfully tagged docker-entrypoint-test:latest
[root@centos7 dockerfile]# docker run 8524617105fd
.
..
.dockerenv
bin
dev
etc
home
lib
lib64
lost+found
media
mnt
opt
proc
root
run
sbin
srv
sys
tmp
usr
var
[root@centos7 dockerfile]# docker run 8524617105fd -l
total 0
drwxr-xr-x.   1 root root   6 Jun 23 02:59 .
drwxr-xr-x.   1 root root   6 Jun 23 02:59 ..
-rwxr-xr-x.   1 root root   0 Jun 23 02:59 .dockerenv
lrwxrwxrwx.   1 root root   7 Nov  3  2020 bin -> usr/bin
drwxr-xr-x.   5 root root 340 Jun 23 02:59 dev
drwxr-xr-x.   1 root root  66 Jun 23 02:59 etc
drwxr-xr-x.   2 root root   6 Nov  3  2020 home
lrwxrwxrwx.   1 root root   7 Nov  3  2020 lib -> usr/lib
lrwxrwxrwx.   1 root root   9 Nov  3  2020 lib64 -> usr/lib64
drwx------.   2 root root   6 Dec  4  2020 lost+found
drwxr-xr-x.   2 root root   6 Nov  3  2020 media
drwxr-xr-x.   2 root root   6 Nov  3  2020 mnt
drwxr-xr-x.   2 root root   6 Nov  3  2020 opt
dr-xr-xr-x. 188 root root   0 Jun 23 02:59 proc
dr-xr-x---.   2 root root 162 Dec  4  2020 root
drwxr-xr-x.  11 root root 163 Dec  4  2020 run
lrwxrwxrwx.   1 root root   8 Nov  3  2020 sbin -> usr/sbin
drwxr-xr-x.   2 root root   6 Nov  3  2020 srv
dr-xr-xr-x.  13 root root   0 Jun 20 08:21 sys
drwxrwxrwt.   7 root root 145 Dec  4  2020 tmp
drwxr-xr-x.  12 root root 144 Dec  4  2020 usr
drwxr-xr-x.  20 root root 262 Dec  4  2020 var
[root@centos7 dockerfile]# 

```

### 实战Tomcat测试

1. 准备tomcat，jdk压缩包

[![image-20210623172859393-20220801230504-25dcjwo.png](https://i.postimg.cc/8CP24x25/image-20210623172859393-20220801230504-25dcjwo.png)](https://postimg.cc/zy62X2XZ)

1. 编写dockerfile文件，Dockerfile官方命名，

```shell
[root@centos7 tomcat]# touch readme.txt
[root@centos7 tomcat]# vim Dockerfile
[root@centos7 tomcat]# cat Dockerfile 
FROM centos

MAINTAINER sun<skywalker0@qq.com>

COPY readme.txt /usr/local/readme.txt

ADD jdk-8u291-linux-x64.tar.gz /usr/local/
ADD apache-tomcat-9.0.48.tar.gz /usr/local/

RUN yum -y install vim

ENV MYPATH /usr/local
WORKDIR $MYPATH

ENV JAVA_HOME /usr/local/jdk1.8.0_291
ENV CLASSPATH $JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
ENV CATALINA_HOME /usr/local/apache-tomcat-9.0.48
ENV CATALINA_BASH /usr/local/apache-tomcat-9.0.48

ENV PATH $PATH:$JAVA_HOME/bin:$CATALINA_HOME/lib:$CATALINA_HOME/bin

EXPOSE 8080

CMD /usr/local/apache-tomcat-9.0.48/bin/startup.sh && tail -F /usr/local/apache-tomcat-9.0.48/bin/logs/catalina.out
[root@centos7 tomcat]# 
```

3. 构建镜像

```shell
[root@centos7 tomcat]# docker build -t diytomcat .
Sending build context to Docker daemon  156.4MB
Step 1/15 : FROM centos
 ---> 300e315adb2f
Step 2/15 : MAINTAINER sun<skywalker0@qq.com>
 ---> Using cache
 ---> 29ad5f97ca5b
Step 3/15 : COPY readme.txt /usr/local/readme.txt
 ---> 35c9e0c265bd
Step 4/15 : ADD jdk-8u291-linux-x64.tar.gz /usr/local/
 ---> 7f5622c3b39f
Step 5/15 : ADD apache-tomcat-9.0.48.tar.gz /usr/local/
 ---> ccb0ac77da86
Step 6/15 : RUN yum -y install vim
 ---> Running in 421a061a716d
CentOS Linux 8 - AppStream                      2.1 MB/s | 7.5 MB     00:03  
CentOS Linux 8 - BaseOS                         1.7 MB/s | 2.6 MB     00:01  
CentOS Linux 8 - Extras                          11 kB/s | 9.6 kB     00:00  
Dependencies resolved.
================================================================================
 Package             Arch        Version                   Repository      Size
================================================================================
Installing:
 vim-enhanced        x86_64      2:8.0.1763-15.el8         appstream      1.4 M
Installing dependencies:
 gpm-libs            x86_64      1.20.7-17.el8             appstream       39 k
 vim-common          x86_64      2:8.0.1763-15.el8         appstream      6.3 M
 vim-filesystem      noarch      2:8.0.1763-15.el8         appstream       48 k
 which               x86_64      2.21-12.el8               baseos          49 k

Transaction Summary
================================================================================
Install  5 Packages

Total download size: 7.8 M
Installed size: 30 M
Downloading Packages:
(1/5): gpm-libs-1.20.7-17.el8.x86_64.rpm        217 kB/s |  39 kB     00:00  
(2/5): vim-filesystem-8.0.1763-15.el8.noarch.rp 771 kB/s |  48 kB     00:00  
(3/5): which-2.21-12.el8.x86_64.rpm             197 kB/s |  49 kB     00:00  
(4/5): vim-enhanced-8.0.1763-15.el8.x86_64.rpm  1.6 MB/s | 1.4 MB     00:00  
(5/5): vim-common-8.0.1763-15.el8.x86_64.rpm    2.1 MB/s | 6.3 MB     00:03  
--------------------------------------------------------------------------------
Total                                           1.8 MB/s | 7.8 MB     00:04   
warning: /var/cache/dnf/appstream-02e86d1c976ab532/packages/gpm-libs-1.20.7-17.el8.x86_64.rpm: Header V3 RSA/SHA256 Signature, key ID 8483c65d: NOKEY
CentOS Linux 8 - AppStream                      1.6 MB/s | 1.6 kB     00:00  
Importing GPG key 0x8483C65D:
 Userid     : "CentOS (CentOS Official Signing Key) <security@centos.org>"
 Fingerprint: 99DB 70FA E1D7 CE22 7FB6 4882 05B5 55B3 8483 C65D
 From       : /etc/pki/rpm-gpg/RPM-GPG-KEY-centosofficial
Key imported successfully
Running transaction check
Transaction check succeeded.
Running transaction test
Transaction test succeeded.
Running transaction
  Preparing        :                                                        1/1 
  Installing       : which-2.21-12.el8.x86_64                               1/5 
  Installing       : vim-filesystem-2:8.0.1763-15.el8.noarch                2/5 
  Installing       : vim-common-2:8.0.1763-15.el8.x86_64                    3/5 
  Installing       : gpm-libs-1.20.7-17.el8.x86_64                          4/5 
  Running scriptlet: gpm-libs-1.20.7-17.el8.x86_64                          4/5 
  Installing       : vim-enhanced-2:8.0.1763-15.el8.x86_64                  5/5 
  Running scriptlet: vim-enhanced-2:8.0.1763-15.el8.x86_64                  5/5 
  Running scriptlet: vim-common-2:8.0.1763-15.el8.x86_64                    5/5 
  Verifying        : gpm-libs-1.20.7-17.el8.x86_64                          1/5 
  Verifying        : vim-common-2:8.0.1763-15.el8.x86_64                    2/5 
  Verifying        : vim-enhanced-2:8.0.1763-15.el8.x86_64                  3/5 
  Verifying        : vim-filesystem-2:8.0.1763-15.el8.noarch                4/5 
  Verifying        : which-2.21-12.el8.x86_64                               5/5 

Installed:
  gpm-libs-1.20.7-17.el8.x86_64         vim-common-2:8.0.1763-15.el8.x86_64  
  vim-enhanced-2:8.0.1763-15.el8.x86_64 vim-filesystem-2:8.0.1763-15.el8.noarch
  which-2.21-12.el8.x86_64           

Complete!
Removing intermediate container 421a061a716d
 ---> f88663230bd4
Step 7/15 : ENV MYPATH /usr/local
 ---> Running in b29e7feb8197
Removing intermediate container b29e7feb8197
 ---> f88b3b6b9fc4
Step 8/15 : WORKDIR $MYPATH
 ---> Running in e322ebc34b34
Removing intermediate container e322ebc34b34
 ---> d4ccfa95cba3
Step 9/15 : ENV JAVA_HOME /usr/local/jdk1.8.0_291
 ---> Running in 7f7849cc8d4f
Removing intermediate container 7f7849cc8d4f
 ---> ddd14b26fae7
Step 10/15 : ENV CLASSPATH $JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
 ---> Running in 87d807a16cae
Removing intermediate container 87d807a16cae
 ---> 15f6402f5a54
Step 11/15 : ENV CATALINA_HOME /usr/local/apache-tomcat-9.0.48
 ---> Running in cee8a00cd2db
Removing intermediate container cee8a00cd2db
 ---> 1c582cbd31c7
Step 12/15 : ENV CATALINA_BASH /usr/local/apache-tomcat-9.0.48
 ---> Running in 290c5f06ce92
Removing intermediate container 290c5f06ce92
 ---> 3caea79d33e8
Step 13/15 : ENV PATH $PATH:$JAVA_HOME/bin:$CATALINA_HOME/lib:$CATALINA_HOME/bin
 ---> Running in 79f38c96cd90
Removing intermediate container 79f38c96cd90
 ---> caf7b868665f
Step 14/15 : EXPOSE 8080
 ---> Running in 499d5b411319
Removing intermediate container 499d5b411319
 ---> 1ed395c4db26
Step 15/15 : CMD /usr/local/apache-tomcat-9.0.48/bin/startup.sh && tail -F /usr/local/apache-tomcat-9.0.48/bin/logs/catalina.out
 ---> Running in 08a268721b7c
Removing intermediate container 08a268721b7c
 ---> 82452044925f
Successfully built 82452044925f
Successfully tagged diytomcat:latest
[root@centos7 tomcat]# docker images
REPOSITORY               TAG       IMAGE ID       CREATED              SIZE
diytomcat                latest    82452044925f   About a minute ago   646MB
docker-entrypoint-test   latest    8524617105fd   7 hours ago          209MB
cmdtest                  latest    da2d7b4985a1   7 hours ago          209MB
mycentos                 0.1       ef11becad48a   25 hours ago         295MB
sun/centos               1.0       fd96f4121255   31 hours ago         209MB
tomcat02                 1.0       61485aa8d509   3 days ago           672MB
tomcat                   9.0       5505f7218e4d   6 days ago           667MB
tomcat                   latest    5505f7218e4d   6 days ago           667MB
redis                    latest    fad0ee7e917a   3 weeks ago          105MB
nginx                    latest    d1a364dc548d   4 weeks ago          133MB
mysql                    5.7       2c9028880e58   6 weeks ago          447MB
portainer/portainer      latest    580c0e4e98b0   3 months ago         79.1MB
centos                   latest    300e315adb2f   6 months ago         209MB
elasticsearch            7.6.2     f29a1ee41030   15 months ago        791MB
[root@centos7 tomcat]# 
```

3. 启动镜像

```shell
[root@centos7 tomcat]# docker run -d -p 9090:8080 --name suntomcat1 -v /home/ldspdvs/build/tomcat/testwebapps:/usr/local/apache-tomcat-9.0.48/webapps/test -v /home/ldspdvs/build/tomcat/tomcatlogs:/usr/local/apache-tomcat-9.0.48/logs diytomcat
1172d133897813cbf1731037a3b0b52353e7f83b0d6a2adac7ad265c0b1d87fa
[root@centos7 tomcat]# docker exec -it 1172d133897813cbf17 /bin/bash
[root@1172d1338978 local]# ll
bash: ll: command not found
[root@1172d1338978 local]# ls
apache-tomcat-9.0.48  bin  etc	games  include	jdk1.8.0_291  lib  lib64  libexec  readme.txt  sbin  share  src
[root@1172d1338978 local]# 

```

4. 访问测试

[![image-20210624084416988-20220801230504-pheekcl.png](https://i.postimg.cc/K8QV1J1y/image-20210624084416988-20220801230504-pheekcl.png)](https://postimg.cc/VJr4T997)

1. 发布项目

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns="http://java.sun.com/xml/ns/javaee" xmlns:web="http://java.sun.com/xml/ns/javaee/web-app_2_5.xsd" xsi:schemaLocation="http://java.sun.com/xml/ns/javaee http://java.sun.com/xml/ns/javaee/web-app_2_5.xsd" id="WebApp_ID" version="2.5">

</web-app>
```

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Hello</title>
</head>
<body>
Hello World!<br/>
<%
System.out.println("----my test web log----");
%>
</body>
</html>
```

[![image-20210624084334177-20220801230504-2jvsd67.png](https://i.postimg.cc/5yvTjJCP/image-20210624084334177-20220801230504-2jvsd67.png)](https://postimg.cc/PvX2FBKZ)

6. 项目测试

[![image-20210624084135720-20220801230504-wtjdqu5.png](https://i.postimg.cc/3wSPcnhZ/image-20210624084135720-20220801230504-wtjdqu5.png)](https://postimg.cc/94984Pr4)

[![image-20210624084204822-20220801230504-g9szldr.png](https://i.postimg.cc/zGq6D9Xj/image-20210624084204822-20220801230504-g9szldr.png)](https://postimg.cc/8jnttXvJ)

### 发布自己的镜像

```shell
[root@centos7 /]# docker login --help

Usage:  docker login [OPTIONS] [SERVER]

Log in to a Docker registry.
If no server is specified, the default is defined by the daemon.

Options:
  -p, --password string   Password
      --password-stdin    Take the password from stdin
  -u, --username string   Username
 # 登录账号 密码 S05141123l
 [root@centos7 home]# docker login -u ldspdvs
Password: 
WARNING! Your password will be stored unencrypted in /root/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded
[root@centos7 home]# 
# 错误
The push refers to repository [docker.io/sun/diytomcat]
An image does not exist locally with the tag: sun/diytomcat

# 解决
[root@centos7 home]# docker tag 82452044925f sun/tomcat:1.0
[root@centos7 home]# docker images
REPOSITORY               TAG       IMAGE ID       CREATED         SIZE
diytomcat                latest    82452044925f   16 hours ago    646MB
sun/tomcat               1.0       82452044925f   16 hours ago    646MB
docker-entrypoint-test   latest    8524617105fd   23 hours ago    209MB
cmdtest                  latest    da2d7b4985a1   23 hours ago    209MB
mycentos                 0.1       ef11becad48a   40 hours ago    295MB
sun/centos               1.0       fd96f4121255   47 hours ago    209MB
tomcat02                 1.0       61485aa8d509   3 days ago      672MB
tomcat                   9.0       5505f7218e4d   7 days ago      667MB
tomcat                   latest    5505f7218e4d   7 days ago      667MB
redis                    latest    fad0ee7e917a   3 weeks ago     105MB
nginx                    latest    d1a364dc548d   4 weeks ago     133MB
mysql                    5.7       2c9028880e58   6 weeks ago     447MB
portainer/portainer      latest    580c0e4e98b0   3 months ago    79.1MB
centos                   latest    300e315adb2f   6 months ago    209MB
elasticsearch            7.6.2     f29a1ee41030   15 months ago   791MB
[root@centos7 home]# 

# push到dockerhub
[root@centos7 home]# docker tag diytomcat ldspdvs/tomcat-diy
[root@centos7 home]# docker push ldspdvs/tomcat-diy:latest
The push refers to repository [docker.io/ldspdvs/tomcat-diy]
f3da40fad94f: Pushed 
002600359583: Pushed 
792c4cae176c: Pushed 
9b177b322da8: Pushed 
2653d992f4ef: Pushed 
latest: digest: sha256:f0c2dd722b385a82e211e519b4ec328d8b862fa85bd5ff5419c1aceecb44700b size: 1373
```

### 小结

[![image-20210624205850191-20220801230504-u1umuin.png](https://i.postimg.cc/BQ9RkjrR/image-20210624205850191-20220801230504-u1umuin.png)](https://postimg.cc/c6hD8L4c)

## Docker网络

[![image-20210624210846843-20220801230504-5enzvio.png](https://i.postimg.cc/fTc1NwZy/image-20210624210846843-20220801230504-5enzvio.png)](https://postimg.cc/vcm07w4w)

三个网络

1. 运行容器

```sh
[root@centos7 ~]# docker run -d -P --name tomcat01 tomcat
27479ed0d31c714c0a76bf554b4c0b1c8d9f54778833b7ed951828c2c95869e4
```

2. 查看ip

```sh
[root@centos7 ~]# docker exec -it tomcat01 ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
88: eth0@if89: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default 
    link/ether 02:42:ac:11:00:02 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 172.17.0.2/16 brd 172.17.255.255 scope global eth0
       valid_lft forever preferred_lft forever
```

3. 查看是否ping通

```sh
[root@centos7 ~]# ping 172.17.0.2
PING 172.17.0.2 (172.17.0.2) 56(84) bytes of data.
64 bytes from 172.17.0.2: icmp_seq=1 ttl=64 time=0.197 ms
64 bytes from 172.17.0.2: icmp_seq=2 ttl=64 time=0.132 ms
64 bytes from 172.17.0.2: icmp_seq=3 ttl=64 time=0.079 ms
64 bytes from 172.17.0.2: icmp_seq=4 ttl=64 time=0.067 ms
64 bytes from 172.17.0.2: icmp_seq=5 ttl=64 time=0.056 ms
^C
--- 172.17.0.2 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4021ms
rtt min/avg/max/mdev = 0.056/0.106/0.197/0.052 ms
[root@centos7 ~]# 
# linux可以ping通容器内部
```

4. 启动容器2测试

```sh
[root@centos7 ~]# docker run -d -P --name tomcat02 tomcat
9d9c3ec767ddc56f30daa0d00eb525661baee2cb3c79426d233d0bfcb7f919eb
[root@centos7 ~]# docker exec -it tomcat02 ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
90: eth0@if91: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default 
    link/ether 02:42:ac:11:00:03 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 172.17.0.3/16 brd 172.17.255.255 scope global eth0
       valid_lft forever preferred_lft forever
[root@centos7 ~]# 
```

4. 分析

[![image-20210624215427521-20220801230504-hdk0lrf.png](https://i.postimg.cc/tgMM5JdS/image-20210624215427521-20220801230504-hdk0lrf.png)](https://postimg.cc/5H8g9xRL)

```sh
# 我们发现容器带来网卡都是一对的
veth-pair 就是一对虚拟设备接口，成对出现，一段连着协议，一段彼此相连
正因为这个技术，veth-pair充当一个桥梁，连接各种虚拟网络设备
```

==测试tomcat01和tomcat02是否可以ping通==

```sh
[root@centos7 ~]# docker exec -it tomcat02 ping 172.17.0.2
PING 172.17.0.2 (172.17.0.2) 56(84) bytes of data.
64 bytes from 172.17.0.2: icmp_seq=1 ttl=64 time=0.239 ms
64 bytes from 172.17.0.2: icmp_seq=2 ttl=64 time=0.078 ms
64 bytes from 172.17.0.2: icmp_seq=3 ttl=64 time=0.161 ms
^C
--- 172.17.0.2 ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2ms
rtt min/avg/max/mdev = 0.078/0.159/0.239/0.066 ms
[root@centos7 ~]# 
```

5. 网络模型

[![image-20210624220545879-20220801230504-0dc945a.png](https://i.postimg.cc/qBC91s58/image-20210624220545879-20220801230504-0dc945a.png)](https://postimg.cc/8sNK56D5)

## 小结

[![image-20210624220622191-20220801230504-nd3efgl.png](https://i.postimg.cc/g0J788hL/image-20210624220622191-20220801230504-nd3efgl.png)](https://postimg.cc/LJcvMqNm)

docker中网络都是虚拟的，虚拟转发效率高（内网传递文件）只要删除容器，对应网桥一对就没了