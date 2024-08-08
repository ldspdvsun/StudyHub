# Shell实战

## cron定时任务配置

```shell
# docker conainers stop and start
0 1 * * * /data/shell/docker_stop.sh vscode-server
0 7 * * * /data/shell/docker_start.sh vscode-server

# Periodic delete file
40 12,23 * * * /data/shell/tar_delete.sh /root/backup/File /data

# Periodic backup file
30 12,23 * * * /data/shell/tar_delete.sh /root/backup/File /data

# delete all file like *.out from /data/docker/vscode-server/C/Posix
30 6-23 * * * /data/shell/delete_suf.sh /data/docker/vscode-server

# chmod 777 for /data
0 */4 * * * /data/shell/chmod_permission.sh /data/docker

# update auth to ubuntu
0 3 * * * /data/shell/update_ubuntu_auth.sh

# sync file from source dir to target dir
25 6-23 * * * /data/shell/sync_files.sh /data/docker/vscode-server/Hexo/HexoGithub/source/_posts/ data/docker/vscode-server/Hexo/ldspdvsun.gitlab.io/source/_posts/

# sync local and remote repo
55 6-23 * * * /data/shell/sync_local_remote_repo.sh /data/docker/vscode-server/Hexo/HexoGithub/
55 6-23 * * * /data/shell/sync_local_remote_repo.sh /data/docker/vscode-server/Hexo/ldspdvsun.gitlab.io/
```

## 容器定时关闭与启动

```shell
root@10-7-153-197:/data/shell# cat docker_stop.sh
#!/bin/bash

docker stop $1
root@10-7-153-197:/data/shell# cat docker_start.sh
#!/bin/bash

docker start $1
root@10-7-153-197:/data/shell#

```

## 定时备份与删除文件

```shell
root@10-7-153-197:/data/shell# cat tar_delete.sh
#!/bin/bash

# 设置备份目录
backup_dir=$1

# 获取当前日期和时间
now=$(date +"%Y-%m-%d_%H-%M-%S")

# 备份文件
if [ $(date +%H) -eq 23 ] && [ $(date +%M) -eq 30 ]; then
    tar -czvf "${backup_dir}/backup_${now}.tar.gz" $2
elif [ $(date +%H) -eq 12 ] && [ $(date +%M) -eq 30 ]; then
    tar -czvf "${backup_dir}/backup_${now}.tar.gz" $2
fi

# 删除文件
if [ $(date +%H) -eq 12 ] && [ $(date +%M) -eq 40 ]; then
    # 删除前一天23点的备份
    last_day=$(date -d "yesterday" +"%Y-%m-%d")
    rm "${backup_dir}/backup_${last_day}_23"*".tar.gz"
elif [ $(date +%H) -eq 23 ] && [ $(date +%M) -eq 40 ]; then
    # 删除当天12点的备份
    rm "${backup_dir}/backup_${now:0:10}_12"*".tar.gz"
fi

root@10-7-153-197:/data/shell#
```

## 删除指定后缀文件

```shell
root@10-7-153-197:/data/shell# cat delete_suf.sh
#!/bin/bash
# delete all file like *.out
sudo find $1/ -name "*.out" -delete
sudo find $1/ -name "*.o" -delete
sudo find $1/ -name "*.log" -delete
sudo find "$1" -type d -name ".pytest_cache" -exec rm -rf {} +
sudo find "$1" -type d -name "__pycache__" -exec rm -rf {} +
sudo find "$1" -type d -name ".mypy_cache" -exec rm -rf {} +
root@10-7-153-197:/data/shell#
```

## 修改指定文件权限

```shell
root@10-7-153-197:/data/shell# cat chmod_permission.sh
#!/bin/bash
sudo chmod -R 777 $1/*
```

## 更改Ubuntu下Nginx认证权限

```shell
root@10-7-153-197:/data/shell# cat update_ubuntu_auth.sh
#!/bin/bash

# Step 1: Get current date with a prefix
current_date=$(date +'%m%d')
prefix="Author@"
prefixed_date="${prefix}${current_date}"

# Step 2: Write the prefixed date to password.txt
echo "$prefixed_date" > password.txt

# Step 3: Generate password and update .htpasswd file
if sudo htpasswd -b -c /etc/nginx/.htpasswd Author "$prefixed_date"; then
    echo "Password updated successfully."
else
    echo "Password update failed."
    exit 1
fi

# Step 4: Restart Nginx
if sudo systemctl restart nginx; then
    echo "Nginx restarted successfully."
else
    echo "Nginx restart failed."
    exit 1
fi

root@10-7-153-197:/data/shell#
```

## 同步本地文件夹与目标文件夹

```shell
root@10-7-153-197:/data/shell# cat sync_files.sh
#!/bin/bash

# 检查参数数量
if [ "$#" -ne 2 ]; then
  echo "Usage: ./sync_files.sh SOURCE_DIR TARGET_DIR"
  exit 1
fi

# 获取命令行参数
SOURCE_DIR="$1"
TARGET_DIR="$2"

# 确保目标目录存在
mkdir -p "$TARGET_DIR"

# 查找第一个目录下的所有文件
find "$SOURCE_DIR" -type f | while read -r file
do
  # 获取相对于 $SOURCE_DIR 的文件路径
  relative_path=${file#$SOURCE_DIR}

  # 去掉路径前的'/'符号
  relative_path=${relative_path#/}

  # 定义在第二个目录中的文件路径
  target_file="$TARGET_DIR/$relative_path"

  # 确保目标文件所在的目录存在
  mkdir -p "$(dirname "$target_file")"

  # 检查文件在第二个目录中是否存在
  if [ -f "$target_file" ]; then
    # 比较文件内容
    if ! diff -q "$file" "$target_file" > /dev/null 2>&1; then
      echo "文件不一致，复制: $file -> $target_file"
      cp "$file" "$target_file"
    else
      echo "文件一致: $file -> $target_file"
    fi
  else
    echo "目标不存在，复制新文件: $file -> $target_file"
    cp "$file" "$target_file"
  fi
done

root@10-7-153-197:/data/shell#
```

## 同步本地与远程仓库

```shell
root@10-7-153-197:/data/shell# cat sync_local_remote_repo.sh
#!/bin/bash

# 检查参数数量
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 REPO_DIR"
  exit 1
fi

# 获取命令行参数
REPO_DIR="$1"

# 检查指定目录是否是Git仓库
if [ ! -d "$REPO_DIR/.git" ]; then
  echo "The specified directory is not a Git repository."
  exit 1
fi

# 进入指定的Git仓库目录
cd "$REPO_DIR" || exit

# 检查工作目录中的变化
changes=$(git status --porcelain)

# 如果没有变化，退出
if [ -z "$changes" ]; then
  echo "No changes detected."
  exit 0
fi

# 获取变化的文件名
changed_files=$(echo "$changes" | awk '{print $2}')

# 输出变化的文件
echo "Changes detected in the following files:"
echo "$changed_files"

# 添加所有变化
git add .

# 提交变化，以变化的文件名作为提交信息
commit_message=$(echo "$changed_files" | tr '\n' ' ')
git commit -m "$commit_message"

# 推送到远程仓库
git push origin main

echo "Changes committed and pushed to the repository."

root@10-7-153-197:/data/shell#
```
