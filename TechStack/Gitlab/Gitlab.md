
# Gitlab

## docker部署

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

查看root初始密码
```sh
docker exec -it gitlab grep "Password": /etc/gitlab/initial_root_password
```

## Gitlab CI/CD

### gitlab ci/cd
### gitlab runner

> gitlab runner 将会通过执行.gitlab-ci.yml 文件进行CI/CD操作

#### 安装

```sh
sudo docker run -d --name gitlab-runner --restart always -v /data/docker/gitlab-runner/config:/etc/gitlab-runner -v /var/run/docker.sock:/var/run/docker.sock gitlab/gitlab-runner:latest
```

#### 注册

```sh
sudo docker run --rm -v /data/docker/gitlab-runner/config:/etc/gitlab-runner gitlab/gitlab-runner \
--non-interactive \
--executor "docker"
--docker-image alpine:latest \
--url "Gitlab局域网IP" \
--registration-token "Gitlab管理员界面获取token" \
--tag-list "test-cicd,docker-cicd" \
--run-untagged="true" \
--locked="false" \
--access-level="not_protected"
```

### pipeline

> 一次pipeline相当于一次任务构建,里面可以包含多个流程,如安装依赖、运行测试、编译代码、部署服务器等。任何提交或者Merge Request的合并都可以触发 pipeline

[![image.png](https://i.postimg.cc/7YzNmbSG/image.png)](https://postimg.cc/Wh2r4NWT)

### stage

> stage 表示一个构建阶段,可以在一个 pipeline中定义多个stage,这些stage会有以下特点
1. 所有stage会按照stages参数里定义的顺序串行执行,及当一个stage完成后才会执行下一个stage
2. 默认情况下当所有的stage成功后,最后的pipeline构建任务才会成功
3. 默认情况下任何一个stage失败,那么后面的stage不会执行,该构建任务最终会失败

[![image.png](https://i.postimg.cc/bwtnTbh4/image.png)](https://postimg.cc/FYh1FY1x)

### job

> job 表示构建工作,即某个stage里面执行的工作内容,可以在同一个stage里定义多个job
1. 相同stage中的job会并行执行
2. 相同stage中的job都执行成功式,该stage才会成功
3. 如果任何一个job失败,那么该stage失败,即构建该任务失败

[![image.png](https://i.postimg.cc/yYHR6WCH/image.png)](https://postimg.cc/vD0T3Ymq)

[![image.png](https://i.postimg.cc/bJqMjkHB/image.png)](https://postimg.cc/1gYMGgdG)

### .gitlab-ci.yml

> pipeline 执行的内容使用ymal语言进行描述，默认文件名为 .gitlab-ci.yml，该文件存放在仓库的根目录下即可生效

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