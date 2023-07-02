## 安装

1. 下载安装文件
```sh
# anaconda
wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-2022.05-Linux-x86_64.sh
# miniconda
wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda3-py39_4.12.0-Linux-x86_64.sh
```

2. 执行下载命令
```sh
bash Anaconda3-2022.05-Linux-x86_64.sh
```

3. 安装过程中除了安装位置要修改为/usr/local/anaconda3(默认安装在root下，但是这样普通用户将无法使用anaconda，所以要修改安装位置)之外，其他的都是yes
4. 配置安装环境

```sh
vim /etc/profile
export ANACONDA_PATH=/usr/local/anaconda3
export PATH=$PATH:$ANACONDA_PATH/bin
source /etc/profile
```

5. 查看是否安装成功

```sh
conda -V
```
6. 配置下载镜像文件
```sh
先执行以下命令，在/home/admin目录下生成.bashrc文件
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
```

7. 编辑镜像文件

```sh
channels:
  - defaults
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

show_channel_urls: true
ssl_verify: false
```

8. 清理缓存

```sh
conda clean -i
```

9. 更新软件

```sh
conda update conda
conda update anaconda
```

## 创建、激活、退出环境

```sh
# 创建虚拟环境
conda create -n env_name（环境名称） python=3.7(对应的python版本号）
# 激活虚拟环境
conda activate env_name（环境名称）
# 退出虚拟环境
deactivate env_name（环境名称）
# 删除虚拟环境
conda remove -n env_name(环境名称) --all
```

## 查看已创建的虚拟环境

```sh
conda env list  或 conda info -e  或  conda info --env
```

## 修改某个虚拟环境的名字

* anaconda中没有重命名的命令，使用克隆删除的方法
```sh
# 进入旧环境
conda activate old_name
# 克隆旧环境
conda create -n new_name --clone old_name 
# 退出旧环境
conda deactivate
# 删除旧环境
conda remove -n old_name --all
```

## 查看conda的信息

```sh
conda info
```

## 查看当前python版本

```sh
python -V
```

## conda的环境管理

```sh
conda info -e  　　　　　　　　　　　　查看当前已安装的环境
conda create -n py27 python=2.7  　添加2.7版本的Python环境
activate py27  　　　　　　　　　　切换到Python2.7环境
conda deactivate  　　　　　　　　　　　 返回默认的Python环境
conda remove -n py27 --all   　　　　 删除已安装的Python环境
```

## anaconda的包管理，类似Python的pip

```sh
conda list　　　　　　　　　　　　　　查看当前环境下已安装的包
conda list -n py27　　　　　　　　　 查看指定环境的已安装的包
conda search selenium　　　　　　　 查找package信息
conda install -n py27 selenium  指定环境安装package，不加-n则安装在当前活跃环境
conda update -n py27 selenium   指定环境更新package，不加-n则更新在当前活跃环境
conda remove -n py27 selenium   删除package，不加-n则删除在当前活跃环境
conda clean --all               清理（应该是pkgs文件下的）安装包缓存
```
>conda将conda、python等都视为package，因此可以使用conda管理conda和python的版本
```sh
conda update conda  　 更新conda
conda update anaconda  更新anaconda
conda update python   更新python，假设当前环境是3.6，则更新3.6.x系列版本
```

## 安装包

```sh
conda install package_name 比较安全
也可以像python中使用的  pip  package_name
```

## conda clean的使用

```sh
# 删除从不使用的包
conda clean --packages
# 删除tar包
conda clean --tarballs
# 删除索引缓存、锁定文件、未使用过的包和tar包
conda clean -a
```

## 安装指定版本的包

```sh
# 若环境中有其他版本的，先卸载
conda uninstall h5py   （以h5py为例）
conda install h5py==2.10.0   再安装指定版本的

# 直接安装指定版本的
conda install h5py==2.10.0
```

## 修改conda的环境文件位置
>https://blog.csdn.net/weixin_39574140/article/details/110606076

```sh
# 查看存储位置
conda info
```

[![anaconda01.jpg](https://i.postimg.cc/vTkVNyR0/anaconda01.jpg)](https://postimg.cc/H80nrfkM)

* 修改/userdata/archiconda3/下面的.condarc文件,在.condarc文件后面添加两行代码。

```sh
envs_dirs:
  - /userdata/peter/envs
```

修改前内容
```sh
channels:
  - https://conda.anaconda.org/c4aarch64
  - https://conda.anaconda.org/conda-forge
```

修改后内容
```sh
channels:
  - https://conda.anaconda.org/c4aarch64
  - https://conda.anaconda.org/conda-forge
envs_dirs:  
  - /userdata/peter/envs
```

>表示以后创建的虚拟环境默认就存在/userdata/peter/envs目录下面。不要忘了/userdata/peter/envs前面的小的短横线 - 

