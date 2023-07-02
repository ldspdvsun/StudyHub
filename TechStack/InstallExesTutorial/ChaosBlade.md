## 下载chaosblade

```sh
[admin@Centos8 lx]$ wget https://download.fastgit.org/chaosblade-io/chaosblade/releases/download/v1.7.0/chaosblade-1.7.0-linux-amd64.tar.gz
[admin@Centos8 lx]$ ll
-rw-rw-r--  1 admin admin  53765642 9月   6 15:54 chaosblade-1.7.0-linux-amd64.tar.gz
[admin@Centos8 lx]$ ll
总用量 301884
drwxr-xr-x  5 admin admin        68 9月   6 15:15 chaosblade-1.7.0
-rw-rw-r--  1 admin admin  53765642 9月   6 15:54 chaosblade-1.7.0-linux-amd64.tar.gz
[admin@Centos8 lx]$ cd chaosblade-1.7.0/
[admin@Centos8 chaosblade-1.7.0]$ ll
总用量 11772
drwxr-xr-x 2 admin admin      138 9月  29 14:46 bin
-rwxr-xr-x 1 admin admin 12050700 9月   6 15:08 blade
drwxr-xr-x 4 admin admin       34 9月  29 14:46 lib
drwxr-xr-x 2 admin admin      272 9月   6 15:12 yaml
[admin@Centos8 chaosblade-1.7.0]$ tree
.
├── bin
│   ├── chaos_fuse
│   ├── chaos_os
│   ├── nsexec
│   └── strace
├── blade
├── lib
│   ├── cplus
│   │   ├── chaosblade-exec-cplus
│   │   └── script
│   │       ├── shell_break_and_return_attach_parent.sh
│   │       ├── shell_break_and_return_attach.sh
│   │       ├── shell_break_and_return.sh
│   │       ├── shell_check_process_duplicate.sh
│   │       ├── shell_check_process_id.sh
│   │       ├── shell_initialization.sh
│   │       ├── shell_modify_variable_attach_parent.sh
│   │       ├── shell_modify_variable_attach.sh
│   │       ├── shell_modify_variable.sh
│   │       ├── shell_remove_process.sh
│   │       ├── shell_response_delay_attach_parent.sh
│   │       ├── shell_response_delay_attach.sh
│   │       └── shell_response_delay.sh
│   └── sandbox
│       ├── bin
│       │   └── sandbox.sh
│       ├── cfg
│       │   ├── sandbox-logback.xml
│       │   ├── sandbox.properties
│       │   └── version
│       ├── example
│       │   └── sandbox-debug-module.jar
│       ├── install-local.sh
│       ├── lib
│       │   ├── sandbox-agent.jar
│       │   ├── sandbox-core.jar
│       │   └── sandbox-spy.jar
│       ├── module
│       │   ├── chaosblade-java-agent-1.7.0.jar
│       │   └── sandbox-mgr-module.jar
│       ├── provider
│       │   └── sandbox-mgr-provider.jar
│       ├── sandbox-module
│       └── tools.jar
└── yaml
    ├── chaosblade-check-spec-1.7.0.yaml
    ├── chaosblade-cplus-spec.yaml
    ├── chaosblade-cri-spec-1.7.0.yaml
    ├── chaosblade-docker-spec-1.7.0.yaml
    ├── chaosblade-jvm-spec-1.7.0.yaml
    ├── chaosblade-k8s-spec-1.7.0.yaml
    └── chaosblade-os-spec-1.7.0.yaml

13 directories, 39 files
[admin@Centos8 chaosblade-1.7.0]$ ./blade version
version: 1.7.0
env: #1 SMP Thu Mar 17 17:08:06 UTC 2022 x86_64
build-time: Tue Sep  6 07:06:55 UTC 2022
[admin@Centos8 chaosblade-1.7.0]$ 

```


ChaosBlade V1.7.0可针对Docker 容器进行包括但不限于删除容器、容器内 CPU负载、内存、网络、磁盘、进程等实验场景测试，以下将选取典型场景进行验证。在执行本测试前默认系统已经配置好docker环境，这里使用的版本为V20.10.18，且已经成功运行一个容器，这里以Nginx为例，容器ID为f74cabd852d2

## 容器内CPU负载

### 对容器做CPU负载80%测试

```sh
[root@centos7 chaosblade-1.7.0]# ./blade create docker cpu fullload --cpu-percent 80 /tmp/soft/chaosblade-1.7.0-linux-amd64.tar.gz --container-id f74cabd852d2
执行上述命令后，返回如下结果，说明执行成功：
{"code":200,"success":true,"result":"30276abc2fa0290c"}
通过top命令验证，可以看到测试达到预期
```

### 销毁命令（参数为创建测试成功的返回值）

```sh
[root@centos7 chaosblade-1.7.0]# ./blade destroy 30276abc2fa0290c
执行上述命令后，返回如下结果，说明执行成功：
{"code":200,"success":true,"result":{"target":"cpu","action":"fullload","flags":{"container-id":"f74cabd852d2","cpu-percent":"80"},"ActionProcessHang":false}}通过top命令验证，可以看到测试达到预期
``` 

## 容器内网络场景

### 对Nginx容器 80 端口做访问延迟 3 秒测试

```sh
[root@centos7 chaosblade-1.7.0]# ./blade create docker network delay --time 3000 --interface eth0 --local-port 80 --container-id f74cabd852d2
执行上述命令后，返回如下结果，说明执行成功。
{"code":200,"success":true,"result":"fa177eca0d5952a9"}
[root@centos7 chaosblade-1.7.0]# time curl localhost:80
执行上述测试命令后，返回如下结果，说明执行成功。
 
此处延迟 9 秒的原因是涉及到多次 80 端口访问。
```

### 销毁命令

```sh
[root@centos7 chaosblade-1.7.0]# ./blade destroy fa177eca0d5952a9
执行上述命令后，返回如下结果，说明执行成功。
{"code":200,"success":true,"result":{"target":"network","action":"delay","flags":{"container-id":"f74cabd852d2","interface":"eth0","local-port":"80","time":"3000"},"ActionProcessHang":false}}
```

## 验证是否恢复正常

```sh
[admin@Centos8 chaosblade]$ time curl localhost:32768
```

## 容器内进程场景

### 进入容器，使用top命令查看nginx的pid号

### 杀掉容器内 nginx 进程

```sh
[root@centos7 chaosblade-1.7.0]# ./blade create docker process kill --pid 1 --signal 9 /tmp/soft/chaosblade-1.7.0-linux-amd64.tar.gz --container-id f74cabd852d2
执行上述命令后，返回如下结果，说明执行成功。
{"code":200,"success":true,"result":"41ec24664e8aed56"}
```

## 容器自身管理

### 删除容器测试
--force 强制删除

```sh
[root@centos7 chaosblade-1.7.0]# ./blade create docker container remove --force --container-id f74cabd852d2
执行上述命令后，返回如下结果，说明执行成功。
{"code":200,"success":true,"result":"93066cb30f8f63ba"}
```

## 参考链接

>https://github.com/chaosblade-io/chaosblade/blob/master/README_CN.md