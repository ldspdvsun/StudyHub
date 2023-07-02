# Specify the shell
#!/bin/bash

# Specify the Author
# Author:Sun

# Specify the create date
# Created:2022/11/13 10:37

# Specify the script`s version
# Release:1.0

# Add Description
# Scription Description:Change the permissions of current directory and subdirectories


# -c或——changes    # 效果类似“-v”参数，但仅回报更改的部分，如果文件权限已经改变，显示其操作信息；
# -f或--quiet或——silent # 操作过程中不显示任何错误信息；
# -R或——recursive  # 递归处理，将指令目录下的所有文件及子目录一并处理；
# -v或——verbose    # 显示命令运行时的详细执行过程；

sudo chmod -Rc 777 ./*
