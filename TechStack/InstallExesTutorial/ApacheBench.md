```sh
[admin@Centos8 lx]$ pwd
/opt/lx
# 输入下面两个命令，检测依赖包apr-util-1.5.2-6.el7.x86_64；yum-utils-1.1.31-40.el7.noarch是否安装
[admin@Centos8 lx]$ rpm -qa|grep apr-util
apr-util-1.6.1-6.el8.x86_64
apr-util-openssl-1.6.1-6.el8.x86_64
apr-util-bdb-1.6.1-6.el8.x86_64
[admin@Centos8 lx]$ rpm -qa|grep yum-utils
yum-utils-4.0.21-3.el8.noarch
[admin@Centos8 lx]$ mkdir abtmp
[admin@Centos8 lx]$ cd abtmp/

# 如果没有安装，请使用以下命令安装
[admin@Centos8 abtmp]# yum -y install apr-util
[admin@Centos8 abtmp]# yum -y install yum-utils
# 如果没有安装，请使用以上命令安装

[admin@Centos8 abtmp]$ 
[admin@Centos8 abtmp]$ pwd
/opt/lx/abtmp
# 安装ab工具
[admin@Centos8 abtmp]$ sudo yum install yum-utils.noarch
akopytov_sysbench                                                                                                                                                                                        227  B/s | 833  B     00:03    
akopytov_sysbench-source                                                                                                                                                                                 301  B/s | 833  B     00:02    
软件包 yum-utils-4.0.21-3.el8.noarch 已安装。
依赖关系解决。
无需任何处理。
完毕！
[admin@Centos8 abtmp]$ yumdownloader httpd-tools*
CentOS-8.5.2111 - Base - mirrors.aliyun.com                                                                                                                                                               21 kB/s | 3.9 kB     00:00    
CentOS-8.5.2111 - Extras - mirrors.aliyun.com                                                                                                                                                             15 kB/s | 1.5 kB     00:00    
CentOS-8.5.2111 - AppStream - mirrors.aliyun.com                                                                                                                                                          33 kB/s | 4.3 kB     00:00    
akopytov_sysbench                                                                                                                                                                                        2.1 kB/s | 3.9 kB     00:01    
导入 GPG 公钥 0x04DCFD39:
 Userid: "https://packagecloud.io/akopytov/sysbench-prerelease (https://packagecloud.io/docs#gpg_signing) <support@packagecloud.io>"
 指纹: 9789 8D69 F99E E5CA C462 A0F8 CF10 4890 04DC FD39
 来自: https://packagecloud.io/akopytov/sysbench/gpgkey
确定吗？[y/N]： y
akopytov_sysbench                                                                                                                                                                                        1.6 kB/s | 6.5 kB     00:03    
akopytov_sysbench-source                                                                                                                                                                                 3.1 kB/s | 3.9 kB     00:01    
导入 GPG 公钥 0x04DCFD39:
 Userid: "https://packagecloud.io/akopytov/sysbench-prerelease (https://packagecloud.io/docs#gpg_signing) <support@packagecloud.io>"
 指纹: 9789 8D69 F99E E5CA C462 A0F8 CF10 4890 04DC FD39
 来自: https://packagecloud.io/akopytov/sysbench/gpgkey
确定吗？[y/N]： y
akopytov_sysbench-source                                                                                                                                                                                 290  B/s | 1.3 kB     00:04    
Docker CE Stable - x86_64                                                                                                                                                                                7.0 kB/s | 3.5 kB     00:00    
httpd-tools-2.4.37-43.module_el8.5.0+1022+b541f3b1.x86_64.rpm                                                                                                                                            150 kB/s | 107 kB     00:00    
[admin@Centos8 abtmp]$ rpm2cpio httpd-tools*.rpm | cpio -idmv
./usr/bin/ab
./usr/bin/htdbm
./usr/bin/htdigest
./usr/bin/htpasswd
./usr/bin/httxt2dbm
./usr/bin/logresolve
./usr/lib/.build-id
./usr/lib/.build-id/33
./usr/lib/.build-id/33/6c269480766febcb49d92ac989c447c6ccf020
./usr/lib/.build-id/43/ddb0757ee63df612386e5f9e979ddb13fd2a67
./usr/lib/.build-id/4c
./usr/lib/.build-id/4c/83c9ff7f3582c02c3ed20f1b0782e9ea057cc1
./usr/lib/.build-id/71
./usr/lib/.build-id/71/0b9fa43212365ecd69cda8475f99226c10292b
./usr/lib/.build-id/8c
./usr/lib/.build-id/8c/465d35e5425ee725c67d7f91d8daefd4117856
./usr/lib/.build-id/95/b29a4b8eae007fa43f315144d11e76d69147ae
./usr/share/doc/httpd-tools
./usr/share/doc/httpd-tools/LICENSE
./usr/share/doc/httpd-tools/NOTICE
./usr/share/man/man1/ab.1.gz
./usr/share/man/man1/htdbm.1.gz
./usr/share/man/man1/htdigest.1.gz
./usr/share/man/man1/htpasswd.1.gz
./usr/share/man/man1/httxt2dbm.1.gz
./usr/share/man/man1/logresolve.1.gz
396 块
# 将./user/bin/ab复制到系统bin下即可：
[admin@Centos8 abtmp]$ sudo cp /opt/lx/abtmp/usr/bin/ab /usr/bin
[admin@Centos8 abtmp]$ ab -V
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

[admin@Centos8 abtmp]$ 

```

>https://blog.csdn.net/luckymama/article/details/74231680