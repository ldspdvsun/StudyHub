## 安装

```sh
[root@Centos8 lx]# pip3 install cloudperf
[root@Centos8 lx]# cloudperf prices --filter region=us-west-2 | head -10
     instanceType    region    spot-az  vcpu    memory     price
         t3a.nano us-west-2 us-west-2c     2     0.500   0.00140
         t3a.nano us-west-2 us-west-2b     2     0.500   0.00140
         t3a.nano us-west-2 us-west-2a     2     0.500   0.00140
         t3a.nano us-west-2 us-west-2d     2     0.500   0.00140
          t3.nano us-west-2 us-west-2a     2     0.500   0.00160
          t3.nano us-west-2 us-west-2b     2     0.500   0.00160
          t3.nano us-west-2 us-west-2c     2     0.500   0.00160
          t3.nano us-west-2 us-west-2d     2     0.500   0.00160
         t4g.nano us-west-2 us-west-2d     2     0.500   0.00180
[root@Centos8 lx]# 
```

## 参考链接

>https://github.com/bra-fsn/cloudperf