# 安装

## WindowsTerminal

1. Microsoft Store下载
2. Github下载 https://github.com/microsoft/terminal/releases

## PowerShell

https://github.com/PowerShell/PowerShell/releases

## Oh My Posh

管理员模式打开终端运行

```shell
# 安装 oh-my-posh 包，让你的命令行更酷炫、优雅
Install-Module oh-my-posh -Scope CurrentUser   // 这里是旧版安装方式，最新的oh-my-posh已取消，如果已经这么安装的建议卸载

# 卸载 oh-my-posh 包
Uninstall-Module oh-my-posh

# 安装最新版  oh-my-posh
winget install JanDeDobbeleer.OhMyPosh -s winget  // 下载完成后一定要重启 item，将工具全都关闭然后从新打开。
```

# 配置

### 安装Powershell插件PSReadline、posh-git

管理员模式打开终端运行

```shell
# 1. 安装 PSReadline 包，该插件可以让命令行很好用，类似 zsh
Install-Module -Name PSReadLine  -Scope CurrentUser -Force

# 2. 安装 posh-git 包，让你的 git 更好用
Install-Module posh-git  -Scope CurrentUser
```

### 下载字体

下载oh-my-posh所需的字体库，这个需要再oh-my-posh下载完成之后运行

```shell
oh-my-posh font install
```

# 优化

## 浏览主题

1. 打开终端输入

   ```shell
   Get-PoshThemes
   ```
2. 查看官网

   https://ohmyposh.dev/docs/themes

## 更改主题

输入下列命令打开配置文件

```shell
notepad $PROFILE
```

修改配置文件，改为自己喜欢的主题后，保存退出，重启终端

```shell
oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH/主题名.omp.json" | Invoke-Expression
```

# 配置远程SSH连接

## 添加SSH配置

1.打开Windows Terminal设置，在左侧配置文件处，点击添加新配置文件，选择新建空配置文件

[![image.png](https://i.postimg.cc/GhCSkL8r/image.png)](https://postimg.cc/dD5BFKjS)

2. 名称自定义，命令行更改为

```sh
ssh root@服务器IP地址 -p 22 -o ServerAliveInterval=20
```

[![image.png](https://i.postimg.cc/qRc20TkX/image.png)](https://postimg.cc/tZTst8nY)

## 免密码登录

1. 查看本机是否有ssh公钥，如果没有使用命令生成

```sh
cat ~/.ssh/id_rsa.pub

# 没有公钥，使用下列命令生成
ssh-keygen -t rsa -C
```

2. 登录远程主机修改authorized_keys文件,将上述windows主机生成的id_rsa.pub添加进去，如果不存在使用上述ssh-keygen命令生成

```sh
vi ~/.ssh/authorized_keys
```

## 美化远程主机终端

### 安装Oh My Posh
```sh
sudo wget https://ghproxy.net/https://github.com/JanDeDobbeleer/oh-my-posh/releases/download/v23.2.0/posh-linux-amd64 -O /usr/local/bin/oh-my-posh
sudo chmod +x /usr/local/bin/oh-my-posh
```

### 安装主题
```sh
mkdir ~/.poshthemes
wget https://kkgithub.com/JanDeDobbeleer/oh-my-posh/releases/download/v23.2.0/themes.zip -O ~/.poshthemes/themes.zip
unzip ~/.poshthemes/themes.zip -d ~/.poshthemes
chmod u+rw ~/.poshthemes/*.omp.*
rm ~/.poshthemes/themes.zip
```

### 应用Oh My Posh

1. 在远程主机运行如下命令确定shell的类型
```sh
$ oh-my-posh get shell
bash
```

2. 参考官方文档 https://ohmyposh.dev/docs/installation/prompt ，针对不同shell类型有不同的应用方式。比如比较常见的bash，通常是在~/.bashrc文件的最下面添加一行
```sh
eval "$(oh-my-posh init bash --config ~/.poshthemes/jandedobbeleer.omp.json)"
```

3. 保存后重启ssh或者运行下列命令
```sh
exec bash
```
