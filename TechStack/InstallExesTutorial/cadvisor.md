## 下载镜像

```sh
[root@Centos8 ~]# docker pull google/cadvisor
```

## Docker上运行cAdvisor

```sh
[root@Centos8 ~]# docker images
REPOSITORY                 TAG       IMAGE ID       CREATED         SIZE
google/cadvisor            latest    eb1210707573   3 years ago     69.6MB
[root@Centos8 ~]#
[root@Centos8 ~]# docker run \
>   --volume=/:/rootfs:ro \
>   --volume=/var/run:/var/run:ro \
>   --volume=/sys:/sys:ro \
>   --volume=/var/lib/docker/:/var/lib/docker:ro \
>   --volume=/dev/disk/:/dev/disk:ro \
>   --publish=8089:8080 \
>   --detach=true \
>   --name=cadvisor_lx \
>   --privileged \
>   --device=/dev/kmsg \
>   google/cadvisor
```

```txt
--volume=/:/rootfs:ro: 将主机根目录（/）挂载到容器的/rootfs目录，并以只读模式（ro）挂载。这将允许cAdvisor容器查看主机文件系统的信息。

--volume=/var/run:/var/run:ro: 将主机的/var/run目录挂载到容器中的相应目录，以只读模式（ro）。这将允许cAdvisor容器查看主机上的运行时信息。

--volume=/sys:/sys:ro: 将主机的/sys目录挂载到容器的相应目录，并以只读模式（ro）挂载。这将允许cAdvisor容器监视主机上的系统信息。

--volume=/var/lib/docker/:/var/lib/docker:ro: 将主机的Docker数据目录挂载到cAdvisor容器中的相应目录，并以只读模式（ro）挂载。这将允许cAdvisor容器监视和分析Docker容器的资源使用情况。

--volume=/dev/disk/:/dev/disk:ro: 将主机的磁盘设备文件目录挂载到cAdvisor容器的相应目录，并以只读模式（ro）挂载。这将允许cAdvisor容器识别和监视主机上的磁盘信息。

--publish=8089:8080: 将cAdvisor容器的8080端口映射到主机上的8089端口。这将允许您从主机上的Web浏览器访问cAdvisor Web UI。

--detach=true: 在后台运行cAdvisor容器，使其在退出终端时继续运行。

--name=cadvisor_lx: 为cAdvisor容器指定名称（cadvisor_lx）。

--privileged: 启用特权模式，以便cAdvisor容器可以执行一些系统级操作。
```
## 创建成功返回容器ID值

```sh
e96c09e2e0db7c65164029c0913679641529a93cbdec8284566f31dc3b0d9541
[root@Centos8 ~]#
```