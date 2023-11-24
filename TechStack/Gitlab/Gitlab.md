# Gitlab

## Docker 部署

部署 

```sh
docker run -itd \
-p 19980:80 \
-p 19922:22 \
-u root \
-v /data/docker/gitlab/data/log:/var/log/gitlab \
-v /data/docker/gitlab/data/opt:/var/opt/gitlab \
-v /data/docker/gitlab/data/etc:/etc/gitlab \
--restart=unless-stopped \
--name=gitlab \
gitlab/gitlab-ce
```

创建网络

```sh
docker network create custom_network --subnet=172.20.0.0/16
```

指定网络部署

```sh
docker run -itd \
-p 19980:80 \
-p 19922:22 \
--network custom_network --ip 172.20.0.100 \  # 请确保这个 IP 地址在你的网络中没有冲突
-u root \
-v /data/docker/gitlab/data/log:/var/log/gitlab \
-v /data/docker/gitlab/data/opt:/var/opt/gitlab \
-v /data/docker/gitlab/data/etc:/etc/gitlab \
--restart=unless-stopped \  # 推荐使用 unless-stopped 替代 always
--name=gitlab \
gitlab/gitlab-ce
```

查看 root 初始密码

```sh
docker exec -it gitlab grep "Password": /etc/gitlab/initial_root_password
```

## Gitlab CI/CD

### Gitlab Runner

> gitlab runner 将会通过执行.gitlab-ci.yml 文件进行 CI/CD 操作

[![image.png](https://i.postimg.cc/dtX1qMHc/image.png)](https://postimg.cc/LntRTWFx)

[![image.png](https://i.postimg.cc/yNCrCd0g/image.png)](https://postimg.cc/rDg9SqnM)

[![image.png](https://i.postimg.cc/TYW92xdr/image.png)](https://postimg.cc/8jNWwqr5)

[![image.png](https://i.postimg.cc/XYvGQcrQ/image.png)](https://postimg.cc/zV9GfhSg)

#### 安装

##### Linux AMD64

```shell
# Download the binary for your system
sudo curl -L --output /usr/local/bin/gitlab-runner https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64

# Give it permission to execute
sudo chmod +x /usr/local/bin/gitlab-runner

# Create a GitLab Runner user
sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash

# Install and run as a service
sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner
sudo gitlab-runner start
```

##### Docker

```sh
sudo docker run -d --name gitlab-runner --restart always -v /data/docker/gitlab-runner/config:/etc/gitlab-runner -v /var/run/docker.sock:/var/run/docker.sock gitlab/gitlab-runner:latest
```

#### 注册

##### Linux AMD64

[![image.png](https://i.postimg.cc/mZ6SYDpx/image.png)](https://postimg.cc/G9GYrc1z)

##### Docker

```sh
docker run --rm -itd -v /data/docker/gitlab-runner/config:/etc/gitlab-runner gitlab/gitlab-runner register --executor "docker" --docker-image alpine:latest --url "http://192.168.2.136:19980/" --registration-token "npVkW9uCZiLbjXzzNJVN" --description "first-register-runner" --tag-list "test-cicd,docker-cicd" --run-untagged="true" --locked="false" --access-level="not_protected"
```

#### 成功注册

[![image.png](https://i.postimg.cc/VspnY99J/image.png)](https://postimg.cc/140fBqjS)

[![image.png](https://i.postimg.cc/C1tBxYq3/image.png)](https://postimg.cc/Hcws6q3z)

## 常用概念

### pipeline

> 一次 pipeline 相当于一次任务构建,里面可以包含多个流程,如安装依赖、运行测试、编译代码、部署服务器等。任何提交或者 Merge Request 的合并都可以触发 pipeline

[![image.png](https://i.postimg.cc/7YzNmbSG/image.png)](https://postimg.cc/Wh2r4NWT)

### stage

> stage 表示一个构建阶段,可以在一个 pipeline 中定义多个 stage,这些 stage 会有以下特点

1. 所有 stage 会按照 stages 参数里定义的顺序串行执行,及当一个 stage 完成后才会执行下一个 stage
2. 默认情况下当所有的 stage 成功后,最后的 pipeline 构建任务才会成功
3. 默认情况下任何一个 stage 失败,那么后面的 stage 不会执行,该构建任务最终会失败

[![image.png](https://i.postimg.cc/bwtnTbh4/image.png)](https://postimg.cc/FYh1FY1x)

### job

> job 表示构建工作,即某个 stage 里面执行的工作内容,可以在同一个 stage 里定义多个 job

1. 相同 stage 中的 job 会并行执行
2. 相同 stage 中的 job 都执行成功式,该 stage 才会成功
3. 如果任何一个 job 失败,那么该 stage 失败,即构建该任务失败

[![image.png](https://i.postimg.cc/yYHR6WCH/image.png)](https://postimg.cc/vD0T3Ymq)

[![image.png](https://i.postimg.cc/bJqMjkHB/image.png)](https://postimg.cc/1gYMGgdG)

### .gitlab-ci.yml

> pipeline 执行的内容使用 ymal 语言进行描述，默认文件名为 .gitlab-ci.yml，该文件存放在仓库的根目录下即可生效

[![image.png](https://i.postimg.cc/v8pxmzkk/image.png)](https://postimg.cc/PNQ53mtQ)

[![image.png](https://i.postimg.cc/NMqZMZ8L/image.png)](https://postimg.cc/67cMbjmN)

[![image.png](https://i.postimg.cc/qqns7ZLB/image.png)](https://postimg.cc/bSyDCgW4)

## gitlab-ci.yml

```json
stages:
 - linecode
 - install
 - build
 - deploy
 - clean
 - stage1
 - stage2

job1:
 stage: stage1
 script:
  - echo "Running in stage1 of job1..."

job2:
 stage: stage2
 script:
  - echo "Running in stage2 of job2..."
```
