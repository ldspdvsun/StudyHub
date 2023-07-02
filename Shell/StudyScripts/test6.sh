# Specify the shell
#!/bin/bash

# Specify the Author
# Author:Sun

# Specify the create date
# Created:2022/11/13 10:37

# Specify the script`s version
# Release:1.0

# Add Description
# Scription Description:Output redirection

# 将date的输出重定向到test6_redirection.sh中，没有文件时将会新建，存在时将会覆盖原有的内容
date > test6_redirection.log
# 将who的输出追加到test6_redirection.log中，并不会覆盖原有的内容
who >> test6_redirection.log
