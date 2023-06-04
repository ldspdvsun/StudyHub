# Tmux是什么？

> Tmux是一个终端复用器（terminal multiplexer），属于常用的开发工具，学会了之后可以大大的提高工作效率。

## 基本概念

在使用tmux之前我们先了解关于tmux的几个名词：

* session，会话（任务）
* windows，窗口
* pane，窗格

1. 关于session，很多人把session成为会话，但我觉得叫任务更适合一些。

在普通的终端中，窗口和其中由于session（任务）而启动的进程是连在一起的，关闭窗口，session就结束了，session内部的进程也会终止，不管是否运行完。但是在具体使用中，我们希望当前的session隐藏起来，在终端中做其他事情，但是又不希望session及其进程被关闭。这样就需要用到tmux，对session进行解绑。之后再想继续出来这个session的时候，再次绑定就可以回到之前的工作状态。

2. 对于window可以理解为一个工作区，一个窗口。

对于一个session，可以创建好几个window，对于每一个窗口，都可以将其分解为几个pane小窗格。
所以，关于session、window、pane的关系是：

[pane∈window]∈session

## 安装

```sh
# Ubuntu or Debian
sudo apt-get install tmux

# CentOS or Fedora
sudo yum install tmux

# Mac
brew install tmux
```

# session操作

## 启动

```sh
# 新建session，可以在terminal上输入tmux命令，会自动生成一个id为0的session
tmux
# 也可以在建立时显式地说明session的名字，这个名字可以用于解绑后快速的重新进入该session：
tmux new -s your-session-name
```

## 分离

> 在tmux窗口中，按下ctrl+b d或者输入以下命令，就会将当前session与窗口分离，session转到后台执行：

```sh
tmux detach
```

## 退出

> 如果你想退出该session，可以杀死session：

```sh
tmux kill-session -t your-session-name
```

## 绑定、解绑、切换session

```sh
# 假设现在正处于session1，使用分离操作就是将session1进行解绑:
tmux detach

# 如果你想再次绑定session1，可以使用命令：
tmux attach -t your-session-name

# 切换到指定session：
tmux switch -t your-session-name
```

## 重命名session

```sh
tmux rename-session -t old-session new-session
```

# window操作

> 一个session可以有好几个window窗口。

## 新建窗口tmux new-window

```sh
# 新建一个指定名称的窗口
tmux new-window -n your-window-name
```

## 切换窗口

* ctrl+b c: 创建一个新窗口（状态栏会显示多个窗口的信息）
* ctrl+b p: 切换到上一个窗口（按照状态栏的顺序）
* ctrl+b n: 切换到下一个窗口
* ctrl+b w: 从列表中选择窗口（这个最好用）

## 重命名窗口

```sh
tmux rename-window -t old_name new_name
```

# pane操作

> tmux可以将一个窗口分为几个窗格（pane），每个窗格运行不同的命令。

## 划分窗格

* 命令

```sh
# 划分为上下两个窗格
tmux split-window

# 划分左右两个窗格
tmux split-window -h
```

* 快捷键

```sh
左右划分：ctrl+b %
上下划分：ctrl+b "
```

## 光标位置

* 快捷键

```sh
ctrl+b arrow-key（方向键）
```

* 命令

```sh
# 当前窗格往上移
tmux swap-pane -U

# 当前窗格往下移
tmux swap-pane -D
```

## 关闭窗格

* ctrl+d，记住如果只有一个窗格就是关闭window

# 其他操作

```sh
# 列出所有快捷键，及其对应的 Tmux 命令
$ tmux list-keys

# 列出所有 Tmux 命令及其参数
$ tmux list-commands

# 列出当前所有 Tmux 会话的信息
$ tmux info

# 重新加载当前的 Tmux 配置
$ tmux source-file ~/.tmux.conf
```

## tmux上下翻屏

> 使用快捷键ctrl+b [ ，就可以通过方向键上下移动使用PageUp和PageDown可以实现上下翻页

# 引用

* https://blog.csdn.net/CSSDCC/article/details/121231906
