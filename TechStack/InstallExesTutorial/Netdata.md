|IP|备注|
|-|-|
|8.143.7.110|主服务器|
|43.143.132.104|被监控服务器1|
|101.43.224.143|被监控服务器2|


## 主服务器部署

### 下载NetData
```sh
[root@Centos8 lx]# wget -O /tmp/netdata-kickstart.sh https://my-netdata.io/kickstart.sh && sh /tmp/netdata-kickstart.sh
```
To view the Netdata dashboard, navigate to http://localhost:19999, or http://NODE:19999

### docker部署

```sh
docker run -d --name=netdata \
  -p 19999:19999 \
  -v netdataconfig:/etc/netdata \
  -v netdatalib:/var/lib/netdata \
  -v netdatacache:/var/cache/netdata \
  -v /etc/passwd:/host/etc/passwd:ro \
  -v /etc/group:/host/etc/group:ro \
  -v /proc:/host/proc:ro \
  -v /sys:/host/sys:ro \
  -v /etc/os-release:/host/etc/os-release:ro \
  --restart unless-stopped \
  --cap-add SYS_PTRACE \
  --security-opt apparmor=unconfined \
  netdata/netdata
```

## 被监控服务器1、被监控服务器2配置Netdata，配置完成后可在主服务器上自动更新

### 下载Netdata

```sh
wget -O /tmp/netdata-kickstart.sh https://my-netdata.io/kickstart.sh && sh /tmp/netdata-kickstart.sh --claim-token qCiOQN8bfBIEiOvbjpBXuhP2i0Pg1E0p4ZZHtgeXhbt4lZrl7Jkpy7VOUHbzWHR6u7nvuH8ND47kbErRLa0kRBxg4GGulAiHigPCvpGps-farTDa5r6425bp-YMBKwwEKpEAqyo --claim-url https://app.netdata.cloud
```

### docker部署

```sh
docker run -d --name=netdata \
  -p 19999:19999 \
  -v netdataconfig:/etc/netdata \
  -v netdatalib:/var/lib/netdata \
  -v netdatacache:/var/cache/netdata \
  -v /etc/passwd:/host/etc/passwd:ro \
  -v /etc/group:/host/etc/group:ro \
  -v /proc:/host/proc:ro \
  -v /sys:/host/sys:ro \
  -v /etc/os-release:/host/etc/os-release:ro \
  --restart unless-stopped \
  --cap-add SYS_PTRACE \
  --security-opt apparmor=unconfined \
  -e NETDATA_CLAIM_TOKEN=qCiOQN8bfBIEiOvbjpBXuhP2i0Pg1E0p4ZZHtgeXhbt4lZrl7Jkpy7VOUHbzWHR6u7nvuH8ND47kbErRLa0kRBxg4GGulAiHigPCvpGps-farTDa5r6425bp-YMBKwwEKpEAqyo \
  -e NETDATA_CLAIM_URL=https://app.netdata.cloud \
  netdata/netdata
```

## 卸载

```sh
[root@Centos8 lx]# sh netdata-kickstart-20221012.sh --uninstall
```

## 个人服务器监控部署

```sh
docker run -d --name=netdata \
  -p 19990:19999 \
  -v /proc:/host/proc:ro \
  -v /sys:/host/sys:ro \
  -v /var/run/docker.sock:/var/run/docker.sock:ro \
  --cap-add SYS_PTRACE \
  --security-opt apparmor=unconfined \
  netdata/netdata

```

## 参考链接

> https://github.com/netdata/netdata
