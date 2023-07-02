
## 安装helm

> https://helm.sh/zh/

### 脚本安装

```sh
$ curl -fsSL -o get_helm.sh https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3
$ chmod 700 get_helm.sh
$ ./get_helm.sh

如果想直接执行安装，运行curl https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash。
```

### 包管理器安装

```sh
sudo dnf install helm
```

### 二进制版本安装
```sh
下载 需要的版本
解压(tar -zxvf helm-v3.0.0-linux-amd64.tar.gz)
在解压目录中找到helm程序，移动到需要的目录中(mv linux-amd64/helm /usr/local/bin/helm)

初始化
当您已经安装好了Helm之后，您可以添加一个chart 仓库。从 Artifact Hub中查找有效的Helm chart仓库。

$ helm repo add bitnami https://charts.bitnami.com/bitnami
当添加完成，您将可以看到可以被您安装的charts列表：

$ helm search repo bitnami
NAME                             	CHART VERSION	APP VERSION  	DESCRIPTION
bitnami/bitnami-common           	0.0.9        	0.0.9        	DEPRECATED Chart with custom templates used in ...
bitnami/airflow                  	8.0.2        	2.0.0        	Apache Airflow is a platform to programmaticall...
bitnami/apache                   	8.2.3        	2.4.46       	Chart for Apache HTTP Server
bitnami/aspnet-core              	1.2.3        	3.1.9        	ASP.NET Core is an open-source framework create...
# ... and many more
```

## 参考链接

> https://helm.sh/zh/docs/intro/install/