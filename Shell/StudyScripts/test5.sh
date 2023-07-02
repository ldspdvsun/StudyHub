# Specify the shell                                                                             
#!/bin/bash

# Specify the Author
# Author:Sun

# Specify the create date
# Created:2022/11/13 10:37

# Specify the script`s version
# Release:1.0

# Add Description
# Scription Description:Command replacement

now_date=`date`
echo "The date and time are: "$now_date

# 获得当前日期来并用其生成唯一文件名
today=$(date +%y%m%d)
ls -al $(pwd) > test5_$today.log
