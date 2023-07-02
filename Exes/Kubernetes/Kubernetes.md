# kubernetes简介

1. 基本介绍

    * kubernetes简称k8s，开源，目标是让部署容器化的应用简单高效
    * k8s是Google开源的容器编排引擎，支持自动化部署，大规模可伸缩，应用容器化管理
    * 可创建多个容器，每个容器里运行一个应用实例，通过内置的负载均衡策略，实现对这一组应用实例的管理、发现、访问
2. 功能和架构

    1. 概述
        Kubernetes 是一个轻便的和可扩展的开源平台，用于管理容器化应用和服务。通过Kubernetes 能够进行应用的自动化部署和扩缩容。在 Kubernetes 中，会将组成应用的容器组合成一个逻辑单元以更易管理和发现。Kubernetes 积累了作为 Google 生产环境运行工作负载 15 年的经验，并吸收了来自于社区的最佳想法和实践。
    2. K8s功能

        1. 自动装箱
        2. 自我修复
        3. 水平扩展
        4. 服务发现
        5. 滚动更新
        6. 版本回退
        7. 密钥和配置管理
        8. 存储编排
        9. 批处理
    3. 应用部署结构分类

        1. 无中心节点架构
            GluterFS
        2. 有中心节点架构
            HDFS
            K8S
    4. K8S集群架构
        ![image.png](attachment:image.png)
    5. K8S集群架构节点角色功能

        1. Master Node
            K8s集群控制节点，对集群进行调度管理，接受集群外用户集群操作请求：Master Node由API Server、Scheduler、ClusterState Store(ETCD数据库)和Controller-ManagerServer组成

            * apiserver 集群统一入口，以restful方式，交给etcd存储
            * scheduler 节点调度，选择节点应用部署
            * controller-manager 处理集群中常规后台任务，一个资源对应一个控制器
            * etcd 存储系统，永不保存集群相关的数据
        2. Worker Node
            集群工作节点，运行用户业务应用容器；
            Worker Node包含kubelet、kube proxy和ContainerRuntime

            * kubelet master派到节点的代表，管理本地容器
            * kube-proxy 提供网络代理，负载均衡操作

        ![image-2.png](attachment:image-2.png)
    6. K8S特性

        1. pod

            * 最小部署单元
            * 一组容器的集合
            * 共享网络
            * 生命周期是短暂的
        2. controller

            * 确保预期的pod副本数量
            * 无状态应用部署
            * 有状态应用部署
            * 确保所有的node运行同一个pod
            * 一次性任务和定时任务
        3. Service

            * 定义一组pod的访问规则

# kubernetes集群搭建

## kubeadm搭建

### 单master集群
![image-3.png](attachment:image-3.png)

#### 安装要求
1. | 服务器硬件配置要求 |     |     |
    | <br /> | master | node |
    | -------------------- | ----- | ----- |
    | CPU<br />              | 2核 | 4核 |
    | 内存               | 4G  | 8G  |
    | 硬盘               | 20G | 40G |
    
2. vmware虚拟出3台centos7配置如下
| <br />      |  | ip             | 默认路由     | 用户名 | 密码 | 用户名 | 密码  |
| --------- | -- | ---------------- | -------------- | -------- | ------ | -------- | ------- |
| master  |  | 192.168.58.135 | 192.168.58.2 | root   | root | admin  | admin |
| node1<br /> |  | 192.168.58.136 | 192.168.58.2 | root   | root | admin  | admin |
| node2   |  | 192.168.58.137 | 192.168.58.2 | root   | root | admin  | admin |

3. 更改ip配置

```sh
# 打开配置文件
vi /etc/sysconfig/network-scripts/ifcfg-ens33
# 修改配置
BOOTPROTO="static"
ONBOOT="yes"
IPADDR=192.168.58.135
NETMASK=255.255.255.0
GATEWAY=192.168.58.2
DNS1=192.168.58.2
# 重启服务
systemctl restart network
```

#### 配置环境

> 新增
```sh
bash <(curl -sSL https://gitee.com/SuperManito/LinuxMirrors/raw/main/ChangeMirrors.sh)
```
> 新增

1. 安装虚拟机，上述已安装，开始之前，添加如下依赖

```shell
# 以上centos7选择最小安装，安装完之后，下载依赖
yum install -y wget net-tools vim lsof
```

2. 在master,node1,node2中关闭防火墙

```shell
systemctl stop firewalld
systemctl disable firewalld
```

3. 在master,node1,node2中关闭selinux

```shell
# 永久
sed -i 's/enforcing/disabled/' /etc/selinux/config
# 临时
setenforce 0
```

4. 在master,node1,node2中关闭swap

```shell
# 临时
swapoff -a
# 永久
sed -ri 's/.*swap.*/#&/' /etc/fstab
```

5. 根据规划设置master,node1,node2主机名

```shell
hostnamectl set-hostname 主机名
hostname
```

6. 在所有节点中添加host

```shell
cat >> /etc/hosts << EOF
192.168.10.104 server
192.168.10.101 master
192.168.10.105 node1
192.168.10.103 node2
185.199.108.133 raw.githubusercontent.com
185.199.109.133 raw.githubusercontent.com
185.199.110.133 raw.githubusercontent.com
185.199.111.133 raw.githubusercontent.com
EOF
```

7. 在master,node1,node2中设置将桥接的IPV4流量传递到iptables的链：

```shell
cat > /etc/sysctl.d/k8s.conf << EOF
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
EOF
# 生效
sysctl --system
```

8. 在master,node1,node2中设置时间同步

```shell
yum install ntpdate -y
ntpdate time.windows.com
```

> Centos8新增替换上述内容

```sh
sudo dnf install chrony
sudo systemctl start chronyd
sudo systemctl enable chronyd
sudo timedatectl set-timezone Asia/Shanghai
sudo chronyc -a makestep
sudo systemctl status chronyd
timedatectl
```

```sh
如果在CentOS 8上执行sudo dnf install ntp命令时出现“未找到匹配的参数: ntp”错误，则可能是因为ntp包已被移除或替换为chrony服务。可以使用以下命令来安装并启用chrony服务：

安装chrony服务
sudo dnf install chrony
启动chrony服务
sudo systemctl start chronyd
设置chrony服务开机自启
sudo systemctl enable chronyd
将时区设置为上海
使用以下命令将时区设置为上海（Asia/Shanghai）：

sudo timedatectl set-timezone Asia/Shanghai
手动同步时间
使用以下命令手动同步时间：

sudo chronyc -a makestep
这会从指定的NTP服务器获取当前的时间并将其应用于系统时钟。

验证chrony服务是否正常运行
使用以下命令检查chrony服务是否已经开始运行：

sudo systemctl status chronyd
如果提示“Active: active (running)”则表示chrony服务已经在后台正常运行。

验证时区设置是否正确
使用以下命令验证时区设置是否正确：

timedatectl
输出结果应该包含类似于“Time zone: Asia/Shanghai”这样的行，表示时区已经成功设置为上海。
```

#### 所有节点安装Docker/kubeadm/kubelet

> 新增
```sh
bash <(curl -sSL https://gitee.com/SuperManito/LinuxMirrors/raw/main/DockerInstallation.sh)
```
> 新增

Kubernetes默认CRI(容器运行时为docker),因此先安装docker
> https://developer.aliyun.com/mirror/docker-ce?spm=a2c6h.13651102.0.0.57e31b112D5RuA

1. 安装Docker

```sh
# step 1: 安装必要的一些系统工具
sudo yum install -y yum-utils device-mapper-persistent-data lvm2
# Step 2: 添加软件源信息
sudo yum-config-manager --add-repo https://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo
# Step 3
sudo sed -i 's+download.docker.com+mirrors.aliyun.com/docker-ce+' /etc/yum.repos.d/docker-ce.repo
# Step 4: 更新并安装Docker-CE,注意安装版本，指定版本看下列
sudo yum makecache
sudo yum -y install docker-ce
# Step 5: 开启Docker服务
systemctl enable docker && systemctl start docker
docker --version
# 注意以下可选不需要一定执行：
# 官方软件源默认启用了最新的软件，您可以通过编辑软件源的方式获取各个版本的软件包。例如官方并没有将测试版本的软件源置为可用，您可以通过以下方式开启。同理可以开启各种测试版本等。
# vim /etc/yum.repos.d/docker-ce.repo
#   将[docker-ce-test]下方的enabled=0修改为enabled=1
#
# 安装指定版本的Docker-CE:
# Step 1: 查找Docker-CE的版本:
# yum list docker-ce.x86_64 --showduplicates | sort -r
#   Loading mirror speeds from cached hostfile
#   Loaded plugins: branch, fastestmirror, langpacks
#   docker-ce.x86_64            17.03.1.ce-1.el7.centos            docker-ce-stable
#   docker-ce.x86_64            17.03.1.ce-1.el7.centos            @docker-ce-stable
#   docker-ce.x86_64            17.03.0.ce-1.el7.centos            docker-ce-stable
#   Available Packages
# Step2: 安装指定版本的Docker-CE: (VERSION例如上面的17.03.0.ce.1-1.el7.centos)
# sudo yum -y install docker-ce-20.10.21-3.el7

或

[root@a ~]# sudo dnf install -y docker-ce-20.10.9 docker-ce-cli-20.10.9 containerd.io --allowerasing

```

2. 添加阿里云YUM软件源

设置仓库地址
```shell
cat > /etc/docker/daemon.json << EOF
{
"exec-opts": [
   "native.cgroupdriver=systemd"
],
"registry-mirrors": ["https://b9pmyelo.mirror.aliyuncs.com"]
}
EOF
# 重启docker
systemctl restart docker
```

3. 设置 kubernetes yum 源


```shell
cat > /etc/yum.repos.d/kubernetes.repo << EOF
[kubernetes]
name=Kubernetes
baseurl=https://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=0
repo_gpgcheck=0
gpgkey=https://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg
        https://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
EOF
```

centos8更新
>https://developer.aliyun.com/mirror/kubernetes
```
sudo bash -c 'cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64/
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg https://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
EOF'
```

4. 所有节点安装kubeadm,kubelet和kubectl


```shell
yum install -y kubelet-1.23.6 kubeadm-1.23.6 kubectl-1.23.6
systemctl enable kubelet
```


```shell
yum install -y kubelet-1.23.17 kubeadm-1.23.17 kubectl-1.23.17
systemctl enable kubelet
```
##### 安装错误之后如何卸载

```sh
sudo dnf remove -y kubelet kubeadm kubectl

sudo systemctl stop kubelet
sudo rm -rf /etc/kubernetes
sudo rm -rf /var/lib/kubelet
```

#### 在master上部署Kubernetes（初始化之后操作根据返回结果自行调整）

* 在master(192.168.58.135)上执行，注意--kubernetes-version v1.23.6的版本要与kubeadm,kubelet和kubectl的版本对应

>centos8
```sh
kubeadm init --apiserver-advertise-address=192.168.58.149 --image-repository registry.aliyuncs.com/google_containers --kubernetes-version v1.23.17 --service-cidr=10.96.0.0/12 --pod-network-cidr=10.244.0.0/16
```

```sh
kubeadm init --apiserver-advertise-address=192.168.58.138 --image-repository registry.aliyuncs.com/google_containers --kubernetes-version v1.23.6 --service-cidr=10.96.0.0/12 --pod-network-cidr=10.244.0.0/16

# --kubernetes-version v1.23.6的版本如果与kubeadm,kubelet和kubectl的版本不一致会导致初始化失败，解决方案如下
rm -rf /etc/kubernetes/manifests/kube-apiserver.yaml
rm -rf /etc/kubernetes/manifests/kube-controller-manager.yaml
rm -rf /etc/kubernetes/manifests/kube-scheduler.yaml
rm -rf /etc/kubernetes/manifests/etcd.yaml
kubeadm reset

# 初始化成功后将会看到如下信息
[addons] Applied essential addon: kube-proxy

Your Kubernetes control-plane has initialized successfully!

To start using your cluster, you need to run the following as a regular user:
# 初始化成功后操作1
  mkdir -p $HOME/.kube
  sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  sudo chown $(id -u):$(id -g) $HOME/.kube/config
Alternatively, if you are the root user, you can run:
  export KUBECONFIG=/etc/kubernetes/admin.conf
You should now deploy a pod network to the cluster.
# 初始化成功后操作2
Run "kubectl apply -f [podnetwork].yaml" with one of the options listed at:
  https://kubernetes.io/docs/concepts/cluster-administration/addons/

Then you can join any number of worker nodes by running the following on each as root:
# 初始化成功后操作3
kubeadm join 192.168.58.135:6443 --token lqsu8e.slm32auk92zge8uv \
	--discovery-token-ca-cert-hash sha256:fd9eb078dbe1e64d83463c78879496e993eb1c7b4b586ee17ec9e130bd158e01 
[root@k8smaster ~]#

kubeadm join 192.168.58.138:6443 --token xerq7h.qy6q9l0qqup2vxpf --discovery-token-ca-cert-hash sha256:cad363c2d71e7320d1b58dce408f08cba3bec41106296fb2a87c92c22a206c14

```

* master初始化成功后操作1

开始使用集群时，需要作为常规用户运行以下命令，(由上述kubeadm init成功后的结果作为输入)

```shell
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

#查看是否执行成功
[root@k8smaster ~]# kubectl get nodes
NAME        STATUS   ROLES                  AGE   VERSION
k8smaster   Ready    control-plane,master   42m   v1.23.6
k8snode1    Ready    <none>                 24m   v1.23.6
k8snode2    Ready    <none>                 24m   v1.23.6
[root@k8smaster ~]#
```

* master初始化成功后操作2

部署CNI网络(由上述kubeadm init成功后的结果作为输入)

```shell
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
```

上述kubectl apply -f 命令执行时，有时会遇到如下错误

```shell
[root@k8smaster ~]# kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
The connection to the server raw.githubusercontent.com was refused - did you specify the right host or port?
```

解决方法为更改/etc/hosts，增加主机映射

去下面的网址，输入上述命令中的下载网址raw.githubusercontent.com，将查到的IP地址添加到/etc/hosts

> https://ip.tool.chinaz.com

```shell
[root@k8smaster ~]# cat /etc/hosts
127.0.0.1   localhost localhost.localdomain localhost4 localhost4.localdomain4
::1         localhost localhost.localdomain localhost6 localhost6.localdomain6
192.168.58.135 k8smaster
192.168.58.136 k8snode1
192.168.58.137 k8snode2

185.199.108.133 raw.githubusercontent.com
185.199.109.133 raw.githubusercontent.com
185.199.110.133 raw.githubusercontent.com
185.199.111.133 raw.githubusercontent.com
[root@k8smaster ~]# 
```

* master初始化成功后操作3

加入Kubernetes Node(由上述kubeadm init成功后的结果作为输入)

```shell
kubeadm join 192.168.58.135:6443 --token lqsu8e.slm32auk92zge8uv --discovery-token-ca-cert-hash sha256:fd9eb078dbe1e64d83463c78879496e993eb1c7b4b586ee17ec9e130bd158e01
#（备注） node部署完节点之后，去master再次查看节点
[root@k8smaster ~]# kubectl get nodes
NAME        STATUS     ROLES                  AGE   VERSION
k8smaster   NotReady   control-plane,master   18m   v1.23.6
k8snode1    NotReady   <none>                 18s   v1.23.6
k8snode2    NotReady   <none>                 6s    v1.23.6
```

##### 测试是否执行成功

```shell
[root@k8smaster ~]# kubectl get pods -n kube-system
NAME                                READY   STATUS    RESTARTS   AGE
coredns-6d8c4cb4d-2vdnc             1/1     Running   0          37m
coredns-6d8c4cb4d-s2hhx             1/1     Running   0          37m
etcd-k8smaster                      1/1     Running   0          37m
kube-apiserver-k8smaster            1/1     Running   0          37m
kube-controller-manager-k8smaster   1/1     Running   0          37m
kube-proxy-4wsv9                    1/1     Running   0          37m
kube-proxy-56zvx                    1/1     Running   0          19m
kube-proxy-89fcx                    1/1     Running   0          19m
kube-scheduler-k8smaster            1/1     Running   0          37m
[root@k8smaster ~]# 
```

网络部署好之后，可通过如下命令查看各个node状态，STATUS都为Ready证明已准备好

```shell
[root@k8smaster ~]# kubectl get nodes
NAME        STATUS   ROLES                  AGE   VERSION
k8smaster   Ready    control-plane,master   42m   v1.23.6
k8snode1    Ready    <none>                 24m   v1.23.6
k8snode2    Ready    <none>                 24m   v1.23.6
[root@k8smaster ~]#
```

##### 测试Kubernetes集群

```shell
kubectl create deployment nginx --image=nginx
kubectl expose deployment nginx --port=80 --type=NodePort
kubectl get pod,svc
访问地址：http://NodeIP:Port
# 创建一个pod
[root@k8smaster ~]# kubectl create deployment nginx --image=nginx
deployment.apps/nginx created
# 查看创建的pod，STATUS是否为Running
[root@k8smaster ~]# kubectl get pod
NAME                     READY   STATUS    RESTARTS   AGE
nginx-85b98978db-4b2xz   1/1     Running   0          45s
# 暴露端口
[root@k8smaster ~]# kubectl expose deployment nginx --port=80 --type=NodePort
service/nginx exposed
# 查看当前的pod状态还有对外暴露的端口是多少
[root@k8smaster ~]# kubectl get pod,svc
NAME                         READY   STATUS    RESTARTS   AGE
pod/nginx-85b98978db-4b2xz   1/1     Running   0          119s

NAME                 TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)        AGE
service/kubernetes   ClusterIP   10.96.0.1       <none>        443/TCP        48m
service/nginx        NodePort    10.99.127.192   <none>        80:32502/TCP   16s
```

访问地址：http://NodeIP:Port

![image-4.png](attachment:image-4.png)

![image-5.png](attachment:image-5.png)

![image-6.png](attachment:image-6.png)

#### 运行后一段时间的k8s如何再重新加入节点
**注意：新加入的节点必须完成上述2.1.1.2中的所有配置要求，保证和其他节点默认配置一致**

1. 查看当前节点

```sh
[root@SqaMaster1 kubernetes]# kubectl get node
NAME         STATUS     ROLES                  AGE     VERSION
sqamaster1   Ready      control-plane,master   2d20h   v1.23.6
sqanode1     Ready      <none>                 2d20h   v1.23.6
sqanode2     Ready      <none>                 2d20h   v1.23.6
[root@SqaMaster1 kubernetes]# 
```

2. 查看token，一般有效期24小时，超过之后没有

```sh
[root@SqaMaster1 kubernetes]# kubeadm token list
```

3. 在k8s-master上使用以下命令重新生成令牌


```sh
[root@SqaMaster1 kubernetes]# kubeadm token create --print-join-command
kubeadm join 192.168.171.128:6443 --token x9bmkk.ktxnyt9flaws4970 --discovery-token-ca-cert-hash sha256:8f48b86ee5669521b2648931fd70f25484f04210afd378e3d5b15e8b3c1c878b
```

4. 新节点加入集群

将第三步生成的结果在要加入的节点中输入
```sh
[root@SqaNode3 ~]# kubeadm join 192.168.171.128:6443 --token x9bmkk.ktxnyt9flaws4970 --discovery-token-ca-cert-hash sha256:8f48b86ee5669521b2648931fd70f25484f04210afd378e3d5b15e8b3c1c878b
```

5. 查看当前节点

```sh
[root@SqaMaster1 kubernetes]# kubectl get node
NAME         STATUS     ROLES                  AGE     VERSION
sqamaster1   Ready      control-plane,master   2d20h   v1.23.6
sqanode1     Ready      <none>                 2d20h   v1.23.6
sqanode2     Ready      <none>                 2d20h   v1.23.6
sqanode3     NotReady   <none>                 26s     v1.23.6
[root@SqaMaster1 kubernetes]# 
```

6. 新节点加入集群时可能出现错误，可使用以下命令尝试之后再次加入

```sh
[root@SqaMaster1 kubernetes]# kubeadm reset
```

# Kubernetes DashBoard

```sh
kind: Service
apiVersion: v1
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard
  namespace: kubernetes-dashboard
spec:
  type: NodePort # new
  ports:
    - port: 443
      targetPort: 8443
      nodePort: 30009 # new
  selector:
    k8s-app: kubernetes-dashboard

---
```
## 下载yaml文件并运行,以上为具体修改内容，完整文件在下方
```sh
[root@k8smaster dashboard]# kubectl create -f dashboard-recommended.yaml 
namespace/kubernetes-dashboard created
serviceaccount/kubernetes-dashboard created
service/kubernetes-dashboard created
secret/kubernetes-dashboard-certs created
secret/kubernetes-dashboard-csrf created
secret/kubernetes-dashboard-key-holder created
configmap/kubernetes-dashboard-settings created
role.rbac.authorization.k8s.io/kubernetes-dashboard created
clusterrole.rbac.authorization.k8s.io/kubernetes-dashboard created
rolebinding.rbac.authorization.k8s.io/kubernetes-dashboard created
clusterrolebinding.rbac.authorization.k8s.io/kubernetes-dashboard created
deployment.apps/kubernetes-dashboard created
service/dashboard-metrics-scraper created
deployment.apps/dashboard-metrics-scraper created
[root@k8smaster dashboard]# 
```
## 查看namespace为kubernetes-dashboard下的资源
```sh
[root@k8smaster dashboard]# kubectl get pod,svc -n kubernetes-dashboard -o wide
NAME                                             READY   STATUS              RESTARTS   AGE   IP       NODE       NOMINATED NODE   READINESS GATES
pod/dashboard-metrics-scraper-6f669b9c9b-l8tkp   0/1     ContainerCreating   0          20s   <none>   k8snode1   <none>           <none>
pod/kubernetes-dashboard-758765f476-94cz2        0/1     ContainerCreating   0          21s   <none>   k8snode1   <none>           <none>

NAME                                TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)         AGE   SELECTOR
service/dashboard-metrics-scraper   ClusterIP   10.110.173.13   <none>        8000/TCP        21s   k8s-app=dashboard-metrics-scraper
service/kubernetes-dashboard        NodePort    10.104.63.91    <none>        443:30009/TCP   21s   k8s-app=kubernetes-dashboard
[root@k8smaster dashboard]# 
[root@k8smaster dashboard]# kubectl get pod,svc -n kubernetes-dashboard -o wide
NAME                                             READY   STATUS    RESTARTS   AGE    IP            NODE       NOMINATED NODE   READINESS GATES
pod/dashboard-metrics-scraper-6f669b9c9b-l8tkp   1/1     Running   0          99s    10.244.1.12   k8snode1   <none>           <none>
pod/kubernetes-dashboard-758765f476-94cz2        1/1     Running   0          100s   10.244.1.11   k8snode1   <none>           <none>

NAME                                TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)         AGE    SELECTOR
service/dashboard-metrics-scraper   ClusterIP   10.110.173.13   <none>        8000/TCP        100s   k8s-app=dashboard-metrics-scraper
service/kubernetes-dashboard        NodePort    10.104.63.91    <none>        443:30009/TCP   100s   k8s-app=kubernetes-dashboard
```

## 创建账户
```sh
[root@k8smaster dashboard]# kubectl create serviceaccount dashboard-admin -n kubernetes-dashboard
serviceaccount/dashboard-admin created
[root@k8smaster dashboard]# 
```

## 授权
```sh
[root@k8smaster dashboard]# kubectl create clusterrolebinding dashboard-admin-rb --clusterrole=cluster-admin --serviceaccount=kubernetes-dashboard:dashboard-admin
clusterrolebinding.rbac.authorization.k8s.io/dashboard-admin-rb created
[root@k8smaster dashboard]# 
```

## 获取账号token
```sh
[root@k8smaster dashboard]# kubectl get secrets -n kubernetes-dashboard | grep dashboard-admin
dashboard-admin-token-6gxrq        kubernetes.io/service-account-token   3      30s
# dashboard-admin-token-6gxrq 为下方命令中用到的token
[root@k8smaster dashboard]# 
[root@k8smaster dashboard]# kubectl describe secrets dashboard-admin-token-6gxrq  -n kubernetes-dashboard
Name:         dashboard-admin-token-6gxrq
Namespace:    kubernetes-dashboard
Labels:       <none>
Annotations:  kubernetes.io/service-account.name: dashboard-admin
              kubernetes.io/service-account.uid: 9f1f6487-20c0-4dc5-94b5-5bf688095f79

Type:  kubernetes.io/service-account-token

Data
====
namespace:  20 bytes
token:      eyJhbGciOiJSUzI1NiIsImtpZCI6Il91blJ1cUpPcm03N2UtZFBETjdlMFktWXdienBSQ0VHX0dwemlXYzdtVU0ifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJrdWJlcm5ldGVzLWRhc2hib2FyZCIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VjcmV0Lm5hbWUiOiJkYXNoYm9hcmQtYWRtaW4tdG9rZW4tNmd4cnEiLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlcnZpY2UtYWNjb3VudC5uYW1lIjoiZGFzaGJvYXJkLWFkbWluIiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZXJ2aWNlLWFjY291bnQudWlkIjoiOWYxZjY0ODctMjBjMC00ZGM1LTk0YjUtNWJmNjg4MDk1Zjc5Iiwic3ViIjoic3lzdGVtOnNlcnZpY2VhY2NvdW50Omt1YmVybmV0ZXMtZGFzaGJvYXJkOmRhc2hib2FyZC1hZG1pbiJ9.EbNnsYdao-qYPxnuNJ4aqBwVHSN1-pUgV-0N2C5_Qz6YuCufA_21MzJPJBlcXwMiZuTb4x7nI_IOtFRiXUHYDlEWgVCrjjuEfIZM6yEMQzz0tKmS7wqpX_NDkIRhZ7WtTWb3cxu_6sje5GOc6ZxwuONPSqwbndMEzMVXhUyoXRHIgeESYWcaz-o4EuS6vUAYSvqHpcYZsG1f-qqdxl7xzkjO-JbTeQVOQ4cmqEZri3QuRkzZr4illTjSw0c0T33WxyVDLOOGpsd_o4Tb5REaXM1nvintKoiX3WleSjKzje-toLVEOeRxvN9m04xetKJPn8xAM3pZFk5NHGUHBXM5cA
ca.crt:     1099 bytes
[root@k8smaster dashboard]# 
[root@k8smaster dashboard]# 

```

访问地址：https://192.168.171.128:30999/#/login
* 打开浏览器会提示是否选择token验证登录，将上方的token输入即可

# 命令行工具 kubectl

```sh
kubectl --help

kubectl get node
```

# NFS搭建

>https://kuboard.cn/learning/k8s-intermediate/persistent/nfs.html#%E9%85%8D%E7%BD%AEnfs%E6%9C%8D%E5%8A%A1%E5%99%A8

## 配置NFS服务器
* 本章节中所有命令都以 root 身份执行

1. 执行以下命令安装 nfs 服务器所需的软件包

```sh
yum install -y rpcbind nfs-utils
```

2. 执行命令 vim /etc/exports，创建 exports 文件，文件内容如下：

```sh
/root/nfs_root/ *(insecure,rw,sync,no_root_squash)
```

3. 执行以下命令，启动 nfs 服务

```sh
# 创建共享目录，如果要使用自己的目录，请替换本文档中所有的 /root/nfs_root/
mkdir /root/nfs_root

systemctl enable rpcbind
systemctl enable nfs-server

systemctl start rpcbind
systemctl start nfs-server
exportfs -r
```

4. 检查配置是否生效
```sh
exportfs
# 输出结果如下所示
/root/nfs_root /root/nfs_root
```
        已复制到剪贴板！
    
## 在客户端测试nfs

* 本章节中所有命令都以 root 身份执行
* 服务器端防火墙开放111、662、875、892、2049的 tcp / udp 允许，否则远端客户无法连接。

1. 执行以下命令安装 nfs 客户端所需的软件包

```sh
yum install -y nfs-utils
```

2. 执行以下命令检查 nfs 服务器端是否有设置共享目录

```sh
# showmount -e $(nfs服务器的IP)
showmount -e 172.17.216.82
# 输出结果如下所示
Export list for 172.17.216.82:
/root/nfs_root *
```

3. 执行以下命令挂载 nfs 服务器上的共享目录到本机路径 /root/nfsmount

```sh
mkdir /root/nfsmount
# mount -t nfs $(nfs服务器的IP):/root/nfs_root /root/nfsmount
mount -t nfs 172.17.216.82:/root/nfs_root /root/nfsmount
# 写入一个测试文件
echo "hello nfs server" > /root/nfsmount/test.txt
``` 

4. 在 nfs 服务器上执行以下命令，验证文件写入成功

```sh
cat /root/nfs_root/test.txt
```

# 参考链接

> https://blog.csdn.net/u010349629/article/details/123796789?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168243184516782427417377%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=168243184516782427417377&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-123796789-null-null.142^v86^insert_down28v1,239^v2^insert_chatgpt&utm_term=centos8%E4%B8%8B%E6%90%AD%E5%BB%BAk8s&spm=1018.2226.3001.4187

> https://blog.csdn.net/realize_dream/article/details/127284864
# dashboard-recommended.yaml
```yaml
# Copyright 2017 The Kubernetes Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

apiVersion: v1
kind: Namespace
metadata:
  name: kubernetes-dashboard

---

apiVersion: v1
kind: ServiceAccount
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard
  namespace: kubernetes-dashboard

---

kind: Service
apiVersion: v1
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard
  namespace: kubernetes-dashboard
spec:
  type: NodePort # new
  ports:
    - port: 443
      targetPort: 8443
      nodePort: 30009 # new
  selector:
    k8s-app: kubernetes-dashboard

---

apiVersion: v1
kind: Secret
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard-certs
  namespace: kubernetes-dashboard
type: Opaque

---

apiVersion: v1
kind: Secret
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard-csrf
  namespace: kubernetes-dashboard
type: Opaque
data:
  csrf: ""

---

apiVersion: v1
kind: Secret
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard-key-holder
  namespace: kubernetes-dashboard
type: Opaque

---

kind: ConfigMap
apiVersion: v1
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard-settings
  namespace: kubernetes-dashboard

---

kind: Role
apiVersion: rbac.authorization.k8s.io/v1
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard
  namespace: kubernetes-dashboard
rules:
  # Allow Dashboard to get, update and delete Dashboard exclusive secrets.
  - apiGroups: [""]
    resources: ["secrets"]
    resourceNames: ["kubernetes-dashboard-key-holder", "kubernetes-dashboard-certs", "kubernetes-dashboard-csrf"]
    verbs: ["get", "update", "delete"]
    # Allow Dashboard to get and update 'kubernetes-dashboard-settings' config map.
  - apiGroups: [""]
    resources: ["configmaps"]
    resourceNames: ["kubernetes-dashboard-settings"]
    verbs: ["get", "update"]
    # Allow Dashboard to get metrics.
  - apiGroups: [""]
    resources: ["services"]
    resourceNames: ["heapster", "dashboard-metrics-scraper"]
    verbs: ["proxy"]
  - apiGroups: [""]
    resources: ["services/proxy"]
    resourceNames: ["heapster", "http:heapster:", "https:heapster:", "dashboard-metrics-scraper", "http:dashboard-metrics-scraper"]
    verbs: ["get"]

---

kind: ClusterRole
apiVersion: rbac.authorization.k8s.io/v1
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard
rules:
  # Allow Metrics Scraper to get metrics from the Metrics server
  - apiGroups: ["metrics.k8s.io"]
    resources: ["pods", "nodes"]
    verbs: ["get", "list", "watch"]

---

apiVersion: rbac.authorization.k8s.io/v1
kind: RoleBinding
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard
  namespace: kubernetes-dashboard
roleRef:
  apiGroup: rbac.authorization.k8s.io
  kind: Role
  name: kubernetes-dashboard
subjects:
  - kind: ServiceAccount
    name: kubernetes-dashboard
    namespace: kubernetes-dashboard

---

apiVersion: rbac.authorization.k8s.io/v1
kind: ClusterRoleBinding
metadata:
  name: kubernetes-dashboard
roleRef:
  apiGroup: rbac.authorization.k8s.io
  kind: ClusterRole
  name: kubernetes-dashboard
subjects:
  - kind: ServiceAccount
    name: kubernetes-dashboard
    namespace: kubernetes-dashboard

---

kind: Deployment
apiVersion: apps/v1
metadata:
  labels:
    k8s-app: kubernetes-dashboard
  name: kubernetes-dashboard
  namespace: kubernetes-dashboard
spec:
  replicas: 1
  revisionHistoryLimit: 10
  selector:
    matchLabels:
      k8s-app: kubernetes-dashboard
  template:
    metadata:
      labels:
        k8s-app: kubernetes-dashboard
    spec:
      securityContext:
        seccompProfile:
          type: RuntimeDefault
      containers:
        - name: kubernetes-dashboard
          image: kubernetesui/dashboard:v2.7.0
          imagePullPolicy: Always
          ports:
            - containerPort: 8443
              protocol: TCP
          args:
            - --auto-generate-certificates
            - --namespace=kubernetes-dashboard
            # Uncomment the following line to manually specify Kubernetes API server Host
            # If not specified, Dashboard will attempt to auto discover the API server and connect
            # to it. Uncomment only if the default does not work.
            # - --apiserver-host=http://my-address:port
          volumeMounts:
            - name: kubernetes-dashboard-certs
              mountPath: /certs
              # Create on-disk volume to store exec logs
            - mountPath: /tmp
              name: tmp-volume
          livenessProbe:
            httpGet:
              scheme: HTTPS
              path: /
              port: 8443
            initialDelaySeconds: 30
            timeoutSeconds: 30
          securityContext:
            allowPrivilegeEscalation: false
            readOnlyRootFilesystem: true
            runAsUser: 1001
            runAsGroup: 2001
      volumes:
        - name: kubernetes-dashboard-certs
          secret:
            secretName: kubernetes-dashboard-certs
        - name: tmp-volume
          emptyDir: {}
      serviceAccountName: kubernetes-dashboard
      nodeSelector:
        "kubernetes.io/os": linux
      # Comment the following tolerations if Dashboard must not be deployed on master
      tolerations:
        - key: node-role.kubernetes.io/master
          effect: NoSchedule

---

kind: Service
apiVersion: v1
metadata:
  labels:
    k8s-app: dashboard-metrics-scraper
  name: dashboard-metrics-scraper
  namespace: kubernetes-dashboard
spec:
  ports:
    - port: 8000
      targetPort: 8000
  selector:
    k8s-app: dashboard-metrics-scraper

---

kind: Deployment
apiVersion: apps/v1
metadata:
  labels:
    k8s-app: dashboard-metrics-scraper
  name: dashboard-metrics-scraper
  namespace: kubernetes-dashboard
spec:
  replicas: 1
  revisionHistoryLimit: 10
  selector:
    matchLabels:
      k8s-app: dashboard-metrics-scraper
  template:
    metadata:
      labels:
        k8s-app: dashboard-metrics-scraper
    spec:
      securityContext:
        seccompProfile:
          type: RuntimeDefault
      containers:
        - name: dashboard-metrics-scraper
          image: kubernetesui/metrics-scraper:v1.0.8
          ports:
            - containerPort: 8000
              protocol: TCP
          livenessProbe:
            httpGet:
              scheme: HTTP
              path: /
              port: 8000
            initialDelaySeconds: 30
            timeoutSeconds: 30
          volumeMounts:
          - mountPath: /tmp
            name: tmp-volume
          securityContext:
            allowPrivilegeEscalation: false
            readOnlyRootFilesystem: true
            runAsUser: 1001
            runAsGroup: 2001
      serviceAccountName: kubernetes-dashboard
      nodeSelector:
        "kubernetes.io/os": linux
      # Comment the following tolerations if Dashboard must not be deployed on master
      tolerations:
        - key: node-role.kubernetes.io/master
          effect: NoSchedule
      volumes:
        - name: tmp-volume
          emptyDir: {}

```