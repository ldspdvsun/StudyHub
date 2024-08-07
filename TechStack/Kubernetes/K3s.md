# K3s

# 安装

## Server节点安装

```sh

# 方法1
curl -sfL https://get.k3s.io | sh -

# 方法2
root@google:/home/ldspdvs# curl -sfL https://get.k3s.io | K3S_KUBECONFIG_MODE="744" sh -s - server --flannel-backend=vxlan --token 12345

# 中国
curl -sfL https://rancher-mirror.rancher.cn/k3s/k3s-install.sh | INSTALL_K3S_MIRROR=cn sh -
```

## 查看Server kubeconfig 文件

```sh
root@google:/home/ldspdvs# cat /etc/rancher/k3s/k3s.yaml
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: LS0tLS1CRUdJTiBDRVJUSUZJQ0FURS0tLS0tCk1JSUJkakNDQVIyZ0F3SUJBZ0lCQURBS0JnZ3Foa2pPUFFRREFqQWpNU0V3SHdZRFZRUUHYQmhyTTNNdGMyVnkKZG1WeUxXTmhRREUyT1RVeE16QTBNekF3SGhjTk1qTXdPVEU1TVRNek16VXdXaGNOTXpNd09URTJNVE16TXpVdwpXakFqTVNFd0h3WURWUVFEREJock0zTXRjMlZ5ZG1WeUxDFEThRREUyT1RVeE16QTBNekF3V1RBVEJnY3Foa2pPClBRSUJCZ2dxaGtqT1BRTUJCd05DQUFSWDRBbXd0SjNzYjd4L3VDSTFoamVxSkJEelpEZEdnWmtLejkxQ1NhSUMKRFM2bGtZKzR6VUswWHpEWjRSWG4wOEQ1TWJIbGlSTHA0akZ2UkRnQ2pod0tvMEl3UURBT0JnTlZIUThCQWY4RQpCQU1DQXFRd0R3WURWUjBUQVFIL0JBVXdBd0VCL3pBZEJnTlZIUTRFRmdRVUl4VTBoelRSRFM0YjFzRDMzN000CndHY1J4cW93Q2dZSUtvWkl6ajBFQXdJRFJ3QXdSQUlnV2wrTlpxYTFrV3hKSmFFdHBReVQrQnJsbUVVN1RVemoKTzEwZUlER2t4RnNDSUdsZW9VUlIrDFEh1L3FZa2xUcTVRQitvT2dVKzQ5bGNTMklUSGFxV01QL1MKLS0tLS1FTkQgQ0VSVElGSUNBVEUtLS0tLQo=
    server: https://127.0.0.1:6443
  name: default
contexts:
- context:
    cluster: default
    user: default
  name: default
current-context: default
kind: Config
preferences: {}
users:
- name: default
  user:
    client-certificate-data: LS0tLS1CRUdJTiBDRVJUSUZJQ0FURS0tLS0tCk1JSUJrVENDQVRlZ0F3SUJBZ0lJRTcyQVBBMStHVjR3Q2dZSUtvWkl6ajBFQXdJd0l6RWhNQjhHQTFVRUF3d1kKYXpOERTxXTnNhV1Z1ZEMxallVQXhOamsxTVRNd05ETXdNQjRYRFRJek1Ea3hPVEV6TXpNMU1Gb1hEVEkwTURreApPREV6TXpNMU1Gb3dNREVYTUJVR0ExVUVDaE1PYzNsemRHVnRPbTFoYzNSbGNuTXhGVEFUQmdOVkJBTVRESE41CmMzUmxiVHBoWkcxcGJqQlpNQk1HQnlxR1NNNDlBZ0VHQ0NxR1NNNDlBd0VIQTBJQUJOMDBMUXlDZ0pQbGsvSzDFDEJEdk5sMXF2N2xNcFFSZVE1TUU3V25BZFJIWm15dmtpMWxGVFF1U1pFYWJ3T0o5ZXRVUGVFLy9DVFdHNUlxZQorZGRNemM2alNEQkdNQTRHQTFVZER3RUIvd1FFQXdJRm9EQVRCZ05WSFNVRUREQUtCZ2dyQmdFRkJRY0RBakFmCkJnTlZIU01FR0RBV2dCUkY5cjZKRW4wcnJnY2NHWGlLL1R2YTRjMlJyREFLQmdncWhrak9QUVFEQWdOSUFEQkYKQWlBWk4wMTBTUFVNQTJBMUIrbEJxY1FHemN2R3JWSHhmdnpEbEZDeDE0c1RTUUloQUpMbTNzNXhmS1NOVVFPYwo4ODNtOTN3am5oSW55ZkJPY2pUOElkdEF6SjdmCi0tLS0tRU5EIENFUlRJRklDQVRFLS0tLS0KLS0tLS1CRUdJTiBDRVJUSUZJQ0FURS0tLS0tCk1JSUJkakNDQVIyZ0F3SUJBZ0lCQURBS0JnZ3Foa2pPUFFRREFqQWpNU0V3SHdZRFZRUUREQmhyTTNNdFkyeHAKWlc1MExXTmhRREUyT1RVeE16QTBNekF3SGhjTk1qTXdPVEU1TVRNek16VXdXaGNOTXpNd09URTJNVE16TXpVdwpXakFqTVNFd0h3WURWUVFEREJock0zTXRZMnhwWlc1MExXTmhRREUyT1RVeE16QTBNekF3V1RBVEJnY3Foa2pPClBRSUJCZ2dxaGtqTDFERTUJCd05DQUFSQjRyY3ZpNUUyUzAvUC83WGc4djhnWjBZUlRicFBUdGhiaG9MT3VwU0oKYVQ0dm5VZlp1ODdxT1hWc3hGd0FsQTFkVlp6akl0T25WQ2l3S1BIeWtnUUdvMEl3UURBT0JnTlZIUThCQWY4RQpCQU1DQXFRd0R3WURWUjBUQVFIL0JBVXdBd0VCL3pBZEJnTlZIUTRFRmdRVVJmYStpUko5SzY0SEhCbDRpdjA3CjJ1SE5rYXd3Q2dZSUtvWkl6ajBFQXdJRFJ3QXdSQUlnTGJQaE43dlUxVjBTKzhlZWhnemlPUWF0Q2dDcWp1c1UKbGtZdldqeHhuTGdDSUZ0KzVQYVVub0t6aTJBZzNab3h0L1RTN2VnU2ZSTlJhZXBCOElTSUsyL2kKLS0tLS1FTkQgQ0VSVElGSUNBVEUtLS0tLQo=
    client-key-data: LS0tLS1CRUdJTiBFQyBQUklWQVRFIEtFWS0tLS0tCk1IY0NBUUVFSUxYWVVNUXlqMDRobUJTRzlNSll1MHlqUVBtbXNXSTVIdVUrRlFFUkhvdVZvQW9HQ0NxR1NNNDkKQXdFSG9VUURRZ0FFM1RRdERJS0FrK1dUOHJUEGETPODJYV3EvdVV5bEJGNURrd1R0YWNCMUVkbWJLK1NMV1VWTgpDGETprUnB2QTRuMTYxUTk0VC84Sk5ZYmtpcDc1MTB6TnpnPT0KLS0tLS1FTkQgRUMgUFJJVkFURSBLRVktLS0tLQo=
root@google:/home/ldspdvs#
```

## Agent节点安装

### Server 查看Token

```sh
root@google:/home/ldspdvs# cat /var/lib/rancher/k3s/server/node-token
K100f8b7f090838618d5458e454db076f13dac95d6999594ddbceb723ec7a005e4d::server:471fa1591fbac45218573dab2fabe3cb
root@google:/home/ldspdvs# 
```

### Agent 加入

```sh
# Agent 节点在加入server节点的时候，会因网络问题导致加入失败，可通过以下方法解决，具体见参考
root@aws:/home/ubuntu# iptables -t nat -A OUTPUT -d Server内网IP -j DNAT --to-destination Server外网IP

# 方法1
root@aws:/home/ubuntu# curl -sfL https://get.k3s.io | K3S_URL=https://myserver:6443 K3S_TOKEN=mynodetoken sh -

# 方法2
root@aws:/home/ubuntu# curl -sfL https://get.k3s.io | K3S_URL=https://myserver:6443 K3S_TOKEN=12345 sh -

# 中国
root@aws:/home/ubuntu# curl -sfL https://rancher-mirror.rancher.cn/k3s/k3s-install.sh | INSTALL_K3S_MIRROR=cn K3S_URL=https://myserver:6443 K3S_TOKEN=mynodetoken sh -
```

# 卸载

## Server 卸载

```sh
root@google:/home/ldspdvs# /usr/local/bin/k3s-uninstall.sh
```

## Agent 卸载

```sh
root@google:/home/ldspdvs# /usr/local/bin/k3s-agent-uninstall.sh
```

# Kuboard部署

```sh
sudo docker run -d \
  --restart=unless-stopped \
  --name=kuboard \
  -p 80:80/tcp \
  -p 10081:10081/tcp \
  -e KUBOARD_ENDPOINT="http://YOUR_IP:80" \
  -e KUBOARD_AGENT_SERVER_TCP_PORT="10081" \
  -v /root/kuboard-data:/data \
  eipwork/kuboard:v3
```

# 参考链接

https://docs.k3s.io/zh/

https://www.maosi.vip/2022/01/08/%E8%BF%90%E7%BB%B4%E7%9B%B8%E5%85%B3%EF%BC%9A%E6%AD%BB%E7%A3%95k3s%E5%92%8Crancher/