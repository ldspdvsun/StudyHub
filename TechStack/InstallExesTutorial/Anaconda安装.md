
## 下载安装文件

```sh
wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-2022.05-Linux-x86_64.sh
```

## 执行下载命令

```sh
bash Anaconda3-2022.05-Linux-x86_64.sh
```

## 安装过程中除了安装位置要修改为/usr/local/anaconda3(默认安装在root下，但是这样普通用户将无法使用anaconda，所以要修改安装位置)之外，其他的都是yes
## 配置安装环境

```sh
vim /etc/profile
export ANACONDA_PATH=/usr/local/anaconda3
export PATH=$PATH:$ANACONDA_PATH/bin
source /etc/profile
```

## 查看是否安装成功

```sh
conda -V
```

## 配置下载镜像文件

```sh
先执行以下命令，在/home/admin目录下生成.bashrc文件
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
```

## 编辑镜像文件

```sh
vim /home/admin/.bashrc
channels:
  - defaults
show_channel_urls: true
default_channels:
  - http://mirrors.aliyun.com/anaconda/pkgs/main
  - http://mirrors.aliyun.com/anaconda/pkgs/r
  - http://mirrors.aliyun.com/anaconda/pkgs/msys2
custom_channels:
  conda-forge: http://mirrors.aliyun.com/anaconda/cloud
  msys2: http://mirrors.aliyun.com/anaconda/cloud
  bioconda: http://mirrors.aliyun.com/anaconda/cloud
  menpo: http://mirrors.aliyun.com/anaconda/cloud
  pytorch: http://mirrors.aliyun.com/anaconda/cloud
  simpleitk: http://mirrors.aliyun.com/anaconda/cloud
```

## 清理缓存

```sh
conda clean -i
```

## 更新软件

```sh
conda update conda
conda update anaconda
```