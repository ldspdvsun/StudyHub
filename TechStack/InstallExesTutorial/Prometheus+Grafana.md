## 安装前系统信息简述

|应用|主机名称|IP地址|端口|运行命令|
| ---| ---| ---| ---|---|
|node-exporter|SqaMaster1|192.168.171.128|9109|nohup /usr/local/node_exporter/node_exporter --web.listen-address="0.0.0.0:9109" &|
|alertmanager|SqaMaster1|192.168.171.128|9093|/usr/local/alertmanager/alertmanager --config.file=/usr/local/alertmanager/node-alert-rules.yml --web.listen-address=":9093"|
|mysql|SqaServer|192.168.171.128|9104|nohup /usr/local/mysqld_exporter/mysqld_exporter --config.my-cnf=/usr/local/mysqld_exporter/.my.cnf &|
|prometheus|SqaServer|192.168.171.200|9099|/usr/local/prometheus/prometheus --config.file="/usr/local/prometheus/prometheus.yml" --web.listen-address="0.0.0.0:9099"|
|grafana|SqaServer|192.168.171.200|3000|/usr/local/grafana-9.1.6/bin/grafana-server|

## 安装

### 被监控节点部署node_exporter V1.4.0

1. 登录到被监控服务器，预先将node_exporter V1.4.0上传到指定位置

```sh
[root@SqaMaster1 soft]# wget https://github.com/prometheus/node_exporter/releases/download/v1.4.0/node_exporter-1.4.0.linux-amd64.tar.gz
[root@SqaMaster1 soft]# pwd
/tmp/soft
-rw-rw-r-- 1 smy 10111972 Sep 26 20:39 node_exporter-1.4.0.linux-amd64.tar.gz
[root@SqaMaster1 soft]# 
```

2. 解压到/usr/local/，并重命名

```sh
[root@SqaMaster1 soft]# tar -zxvf node_exporter-1.4.0.linux-amd64.tar.gz -C /usr/local/
[root@SqaMaster1 soft]# cd /usr/local/
[root@SqaMaster1 local]# mv node_exporter-1.4.0.linux-amd64/ node_exporter/
[root@SqaMaster1 local]# ll
drwxr-xr-x  2 3434 3434 4096 Sep 26 20:39 node_exporter/
[root@SqaMaster1 local]# 
```

### 被监控节点部署Alertmanager V0.24.0

1. 下载解压

```sh
[root@SqaMaster1 soft]# pwd
/tmp/soft
[root@SqaMaster1 soft]# wget https://github.com/prometheus/alertmanager/releases/download/v0.24.0/alertmanager-0.24.0.linux-amd64.tar.gz
[root@SqaMaster1 soft]# tar -zxvf alertmanager-0.24.0.linux-amd64.tar.gz -C /usr/local/
[root@SqaMaster1 soft]# cd /usr/local
```

2. 重命名

```sh
[root@SqaMaster1 local]# mv alertmanager-0.24.0.linux-amd64 alertmanager
[root@SqaMaster1 local]# cd alertmanager/
[root@SqaMaster1 alertmanager]# ll
总用量 55748
-rwxr-xr-x 1 root root 31988661 11月  7 17:55 alertmanager
-rwxr-xr-x 1 root root     1646 11月  7 20:03 alertmanager.yml
-rwxr-xr-x 1 root root 25067944 11月  7 17:55 amtool
drwxr-xr-x 2 root root       35 11月  7 21:08 data
-rwxr-xr-x 1 root root    11357 11月  7 17:55 LICENSE
-rwxr-xr-x 1 root root     2218 11月  7 20:53 node-alert-rules.yml
-rwxr-xr-x 1 root root      457 11月  7 17:55 NOTICE
[root@SqaMaster1 alertmanager]# 
```

### 被监控节点部署mysql_exporter V0.14.0

1. 解压安装包

```sh
[root@SqaServer soft]# wget https://github.com/prometheus/mysqld_exporter/releases/download/v0.14.0/mysqld_exporter-0.14.0.linux-amd64.tar.gz
[root@SqaServer soft]# pwd
/tmp/soft
[root@SqaServer soft]# tar -zxvf mysqld_exporter-0.14.0.linux-amd64.tar.gz -C /usr/local/
```

2. 创建链接目录

```sh
[root@SqaServer soft]# cd /usr/local
[root@SqaServer local]# mv mysqld_exporter-0.14.0.linux-amd64 mysqld_exporter
```

3. 在MySQL服务器上创建监控用户

```sh
[root@SqaServer local]# mysql -u root -p
mysql> grant select,replication client, process on *.* to 'mysql_monitor'@'localhost' identified by '123';
Query OK, 0 rows affected, 1 warning (0.00 sec)

mysql> flush privileges;
Query OK, 0 rows affected (0.03 sec)

mysql> exit
Bye
```

4. 将上面创建的mysql用户信息写入mysqld_exporter配置文件（新创建一个）

```sh
[root@SqaServer local]# vim /usr/local/mysqld_exporter/.my.cnf
[client]
user=mysql_monitor
password=123
[root@SqaServer local]# 
```

### 服务器安装Prometheus V2.38.0

1. 预先将Prometheus工具安装包上传到指定位置

```sh
[root@SqaServer soft]# wget https://github.com/prometheus/prometheus/releases/download/v2.38.0/prometheus-2.38.0.linux-amd64.tar.gz
[root@SqaServer soft]# pwd
/tmp/soft
[root@SqaServer soft]# ll
总用量 89744
-rw-r--r--  1 root   84166501 8月  16 21:49 prometheus-2.38.0.linux-amd64.tar.gz
[root@SqaServer soft]# 
```

2. 解压下载下来的压缩包到/usr/local

```sh
[root@SqaServer soft]# tar -zxvf prometheus-2.38.0.linux-amd64.tar.gz -C /usr/local/
…
prometheus-2.38.0.linux-amd64/console_libraries/menu.lib
…
[root@SqaServer soft]# 
```

3. 更改名字

```sh
[root@SqaServer soft]# cd /usr/local/
[root@SqaServer local]# mv prometheus-2.38.0.linux-amd64/ prometheus/
[root@SqaServer local]# ls
prometheus
[root@SqaServer local]#
```

### 服务器安装Grafana V9.1.6

1. 预先将Grafana.rpmV9.1.6上传到指定位置并解压

```sh
[root@SqaServer soft]# pwd
/tmp/soft
[root@SqaServer soft]# wget https://github.com/grafana/grafana/archive/refs/tags/v9.1.6.tar.gz
[root@SqaServer soft]# tar -zxvf grafana-enterprise-9.1.6.linux-amd64.tar.gz -C /usr/local/
[root@SqaServer soft]# cd /usr/local
[root@SqaServer local]# ll | grep grafana
drwxrwxr-x  8 admin   admin         157 10月 13 18:38 grafana-9.1.6
[root@SqaServer local]# 
```

## 运行

为方便观察，运行顺序依此为
1. node_exproter 获取被监控节点日志信息
2. Alertmanager 启动被监控节点告警服务（发送告警email，展示告警信息
3. mysql_exporter 获取被监控mysql服务器数据
4. Prometheus 验证是否部署成功，是否可以接受到被监控节点的运行信息还有告警信息
5. Grafana 接入Prometheus还有MySQL数据源，图形化展示监控数据

### 被监控节点运行node_exporter

```sh
# 后台执行，并设置监听端口为9109
[root@SqaMaster1 local]# cd node_exporter/
[root@SqaMaster1 node_exporter]# pwd
/usr/local/node_exporter
[root@SqaMaster1 node_exporter]# nohup /usr/local/node_exporter/node_exporter --web.listen-address="0.0.0.0:9109" &
```
> 访问192.168.171.128:9109

### 被监控节点运行alertmanager，指定配置文件监听端口

>配置监控告警信息，包括邮件发送，告警级别，抑制规则

```sh
# 修改配置文件
[root@SqaMaster1 alertmanager]# pwd
/usr/local/alertmanager
[root@SqaMaster1 alertmanager]# vim node-alert-rules.yml 
# 具体内容在下方附录1
# 运行 指定配置文件和监听端口
[root@SqaMaster1 alertmanager]# /usr/local/alertmanager/alertmanager --config.file=/usr/local/alertmanager/node-alert-rules.yml --web.listen-address=":9093"
```
> 访问192.168.171.128:9093

### 被监控节点运行mysql_exporter

```sh
# 启动mysqld_exporter
[root@SqaServer local]# cd mysqld_exporter
[root@SqaServer mysqld_exporter]# pwd
/usr/local/mysqld_exporter
[root@SqaServer mysqld_exporter]# nohup /usr/local/mysqld_exporter/mysqld_exporter --config.my-cnf=/usr/local/mysqld_exporter/.my.cnf &

# 确认是否正常启动（默认端口9104）
[root@SqaServer mysqld_exporter]# netstat -lnptu | grep 9104
tcp6       0      0 :::9104                 :::*                    LISTEN      32688/mysqld_export 
```

>访问192.168.171.200:9104

### 服务器节点上配置被监控节点告警触发规则文件

```sh
[root@SqaServer local]# cd /usr/local/prometheus/rules/
[root@SqaServer rules]# pwd
/usr/local/prometheus/rules
[root@SqaServer rules]# ll
# 具体内容在附录3
-rw-r--r-- 1 root root 14058 11月  7 19:26 alert-rules.yml
-rw-r--r-- 1 root root   641 11月  7 18:58 node_down.yml
[root@SqaServer rules]# 

```

### 服务器运行Prometheus

1.	更改配置文件prometheus.yml，添加主服务器的配置还有被监控服务器的名称、IP、端口，配置文件修改内容如下：

```sh
[root@SqaServer local]# cd /usr/local/prometheus/
[root@SqaServer prometheus]# vim prometheus.yml
# 以下内容为示例，具体内容在附录2
- job_name: "prometheus"
  # metrics_path defaults to '/metrics'
  # scheme defaults to 'http'.
  static_configs:
    - targets: ["8.143.7.110:9099"]
- job_name: "ubuntu"
  static_configs:
- targets: ["101.43.224.143:9109"]
--config.file 指定配置文件
--web.listen-address="0.0.0.0:9099" 指定监控的端口
```

2. 启动Prometheus（若想首次启动便检测到被监控服务器，需要先在被监控服务器上执行node_exporter，然后再在主服务器上启动Prometheus）

```sh
[root@SqaServer prometheus]# /usr/local/prometheus/prometheus --config.file="/usr/local/prometheus/prometheus.yml" --web.listen-address="0.0.0.0:9099"
```

> 访问192.168.171.128:9099

### 服务器运行Grafana

```sh
# 启动服务，默认监听端口为3000，用户名密码为admin/admin
[root@SqaServer local]# cd ./grafana-9.1.6/bin
[root@SqaServer bin]# pwd
/usr/local/grafana-9.1.6/bin
[root@SqaServer bin]# /usr/local/grafana-9.1.6/bin/grafana-server
```
> 访问192.168.171.128:3000

## 附录1-被监控节点告警信息发送配置文件-node-alert-rules.yml

```yml
global:
  # 当alertmanager持续多长时间未接收到告警后标记告警状态为 resolved
  resolve_timeout: 5m
  # 配置邮件发送信息
  smtp_smarthost: 'smtp.qq.com:465'
  smtp_from: 'skywalker0@qq.com'
  smtp_auth_username: 'skywalker0@qq.com'
  smtp_auth_password: 'aaftwxutipqiecbh'
  smtp_require_tls: false
  ######################告警抑制内容#############################
inhibit_rules:
- source_match:
    alertname: NodeMemoryUsage
    severity: critical
  target_match:
    severity: normal
  equal:
    - instance
# 所有报警信息进入后的根路由，用来设置报警的分发策略
route:
  # 接收到的报警信息里面有许多alertname=NodeLoadHigh 这样的标签的报警信息将会批量被聚合到一个分组里面
  group_by: ['alertname']
  # 当一个新的报警分组被创建后，需要等待至少 group_wait 时间来初始化通知，如果在等待时间内当前group接收到了新的告警，这些告警将会合并为一个通知向receiver发送
  group_wait: 30s

  # 相同的group发送告警通知的时间间隔
  group_interval: 30s
  # 如果一个报警信息已经发送成功了，等待 repeat_interval 时间来重新发送
  repeat_interval: 1m

  # 默认的receiver：如果一个报警没有被一个route匹配，则发送给默认的接收器
  receiver: default

  # 上面所有的属性都由所有子路由继承，并且可以在每个子路由上进行覆盖。
  routes:
  - receiver: critical_alerts
    group_wait: 10s
    match:
      severity: critical
  - receiver: normal_alerts
    group_wait: 10s
    match_re:
      severity: normal|middle
# 配置告警接收者的信息
receivers:
- name: 'default'
  email_configs:
  - to: 'EMAIL@126.com'
    send_resolved: true
- name: 'critical_alerts'    #严重告警级别发送给skywalker0@qq.com
  email_configs:
  - to: 'skywalker0@qq.com'
    send_resolved: true
- name: 'normal_alerts'    #普通告警级别发送给EMAIL@126.com
  email_configs:
  - to: 'EMAIL@126.com'
    send_resolved: true  #接受告警恢复的通知
#kind: ConfigMap
#metadata:
#  name: alertmanager
#  namespace: monitor
```

## 附录2-Prometheus系统配置文件-prometheus.yml

```yml
# my global config
global:
  scrape_interval: 15s # Set the scrape interval to every 15 seconds. Default is every 1 minute.
  evaluation_interval: 15s # Evaluate rules every 15 seconds. The default is every 1 minute.
  # scrape_timeout is set to the global default (10s).

# Alertmanager configuration
# 接受被监控节点告警配置
alerting:
  alertmanagers:
    - static_configs:
        - targets:
          - 192.168.171.128:9093

# Load rules once and periodically evaluate them according to the global 'evaluation_interval'.
# 被监控节点告警触发规则文件
rule_files:
  # - "first_rules.yml"
  # - "second_rules.yml"
  - 'rules/*.yml'
# A scrape configuration containing exactly one endpoint to scrape:
# Here it's Prometheus itself.
scrape_configs:
  # The job name is added as a label `job=<job_name>` to any timeseries scraped from this config.
  - job_name: "sqaserver"

    # metrics_path defaults to '/metrics'
    # scheme defaults to 'http'.

    static_configs:
      - targets: ["192.168.171.200:9099"]
  # 被监控mysql节点
  - job_name: "sqamaster1"
    static_configs:
      - targets: ["192.168.171.128:9109"]

  # 被监控mysql服务器
  - job_name: "mysql-sqaserver"
    static_configs:
      - targets: ["192.168.171.200:9104"]
```

## 附录3-Prometheus上监控各节点触发告警规则配置文件

### alert-rules.yml

```yml
groups:
- name: AlertRules
  rules:
  - alert: HostOutOfMemory
    expr: node_memory_MemAvailable_bytes / node_memory_MemTotal_bytes * 100 < 80
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host out of memory (instance {{ $labels.instance }})
      description: "Node memory is filling up (< 80% left)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostMemoryUnderMemoryPressure
    expr: rate(node_vmstat_pgmajfault[1m]) > 1000
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host memory under memory pressure (instance {{ $labels.instance }})
      description: "The node is under heavy memory pressure. High rate of major page faults\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostUnusualNetworkThroughputIn
    expr: sum by (instance) (rate(node_network_receive_bytes_total[2m])) / 1024 / 1024 > 100
    for: 5m
    labels:
      severity: warning
    annotations:
      summary: Host unusual network throughput in (instance {{ $labels.instance }})
      description: "Host network interfaces are probably receiving too much data (> 100 MB/s)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostUnusualNetworkThroughputOut
    expr: sum by (instance) (rate(node_network_transmit_bytes_total[2m])) / 1024 / 1024 > 100
    for: 5m
    labels:
      severity: warning
    annotations:
      summary: Host unusual network throughput out (instance {{ $labels.instance }})
      description: "Host network interfaces are probably sending too much data (> 100 MB/s)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostUnusualDiskWriteRate
    expr: sum by (instance) (rate(node_disk_written_bytes_total[2m])) / 1024 / 1024 > 50
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host unusual disk write rate (instance {{ $labels.instance }})
      description: "Disk is probably writing too much data (> 50 MB/s)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  # Please add ignored mountpoints in node_exporter parameters like
  # "--collector.filesystem.ignored-mount-points=^/(sys|proc|dev|run)($|/)".
  # Same rule using "node_filesystem_free_bytes" will fire when disk fills for non-root users.
  - alert: HostOutOfDiskSpace
    expr: (node_filesystem_avail_bytes * 100) / node_filesystem_size_bytes < 10 and ON (instance, device, mountpoint) node_filesystem_readonly == 0
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host out of disk space (instance {{ $labels.instance }})
      description: "Disk is almost full (< 10% left)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  # Please add ignored mountpoints in node_exporter parameters like
  # "--collector.filesystem.ignored-mount-points=^/(sys|proc|dev|run)($|/)".
  # Same rule using "node_filesystem_free_bytes" will fire when disk fills for non-root users.
  - alert: HostDiskWillFillIn24Hours
    expr: (node_filesystem_avail_bytes * 100) / node_filesystem_size_bytes < 10 and ON (instance, device, mountpoint) predict_linear(node_filesystem_avail_bytes{fstype!~"tmpfs"}[1h], 24 * 3600) < 0 and ON (instance, device, mountpoint) node_filesystem_readonly == 0
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host disk will fill in 24 hours (instance {{ $labels.instance }})
      description: "Filesystem is predicted to run out of space within the next 24 hours at current write rate\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostOutOfInodes
    expr: node_filesystem_files_free / node_filesystem_files * 100 < 10 and ON (instance, device, mountpoint) node_filesystem_readonly == 0
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host out of inodes (instance {{ $labels.instance }})
      description: "Disk is almost running out of available inodes (< 10% left)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostInodesWillFillIn24Hours
    expr: node_filesystem_files_free / node_filesystem_files * 100 < 10 and predict_linear(node_filesystem_files_free[1h], 24 * 3600) < 0 and ON (instance, device, mountpoint) node_filesystem_readonly == 0
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host inodes will fill in 24 hours (instance {{ $labels.instance }})
      description: "Filesystem is predicted to run out of inodes within the next 24 hours at current write rate\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostUnusualDiskReadLatency
    expr: rate(node_disk_read_time_seconds_total[1m]) / rate(node_disk_reads_completed_total[1m]) > 0.1 and rate(node_disk_reads_completed_total[1m]) > 0
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host unusual disk read latency (instance {{ $labels.instance }})
      description: "Disk latency is growing (read operations > 100ms)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostUnusualDiskWriteLatency
    expr: rate(node_disk_write_time_seconds_total[1m]) / rate(node_disk_writes_completed_total[1m]) > 0.1 and rate(node_disk_writes_completed_total[1m]) > 0
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host unusual disk write latency (instance {{ $labels.instance }})
      description: "Disk latency is growing (write operations > 100ms)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostHighCpuLoad
    expr: 100 - (avg by(instance) (rate(node_cpu_seconds_total{mode="idle"}[2m])) * 100) > 80
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Host high CPU load (instance {{ $labels.instance }})
      description: "CPU load is > 80%\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostCpuStealNoisyNeighbor
    expr: avg by(instance) (rate(node_cpu_seconds_total{mode="steal"}[5m])) * 100 > 10
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Host CPU steal noisy neighbor (instance {{ $labels.instance }})
      description: "CPU steal is > 10%. A noisy neighbor is killing VM performances or a spot instance may be out of credit.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostCpuHighIowait
    expr: avg by (instance) (rate(node_cpu_seconds_total{mode="iowait"}[5m])) * 100 > 5
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Host CPU high iowait (instance {{ $labels.instance }})
      description: "CPU iowait > 5%. A high iowait means that you are disk or network bound.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"


  # 1000 context switches is an arbitrary number.
  # Alert threshold depends on nature of application.
  # Please read: https://github.com/samber/awesome-prometheus-alerts/issues/58
  - alert: HostContextSwitching
    expr: (rate(node_context_switches_total[5m])) / (count without(cpu, mode) (node_cpu_seconds_total{mode="idle"})) > 1000
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Host context switching (instance {{ $labels.instance }})
      description: "Context switching is growing on node (> 1000 / s)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostSwapIsFillingUp
    expr: (1 - (node_memory_SwapFree_bytes / node_memory_SwapTotal_bytes)) * 100 > 80
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host swap is filling up (instance {{ $labels.instance }})
      description: "Swap is filling up (>80%)\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostSystemdServiceCrashed
    expr: node_systemd_unit_state{state="failed"} == 1
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Host systemd service crashed (instance {{ $labels.instance }})
      description: "systemd service crashed\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostPhysicalComponentTooHot
    expr: node_hwmon_temp_celsius > 75
    for: 5m
    labels:
      severity: warning
    annotations:
      summary: Host physical component too hot (instance {{ $labels.instance }})
      description: "Physical hardware component too hot\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostNodeOvertemperatureAlarm
    expr: node_hwmon_temp_crit_alarm_celsius == 1
    for: 0m
    labels:
      severity: critical
    annotations:
      summary: Host node overtemperature alarm (instance {{ $labels.instance }})
      description: "Physical node temperature alarm triggered\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostRaidArrayGotInactive
    expr: node_md_state{state="inactive"} > 0
    for: 0m
    labels:
      severity: critical
    annotations:
      summary: Host RAID array got inactive (instance {{ $labels.instance }})
      description: "RAID array {{ $labels.device }} is in degraded state due to one or more disks failures. Number of spare drives is insufficient to fix issue automatically.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostRaidDiskFailure
    expr: node_md_disks{state="failed"} > 0
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host RAID disk failure (instance {{ $labels.instance }})
      description: "At least one device in RAID array on {{ $labels.instance }} failed. Array {{ $labels.md_device }} needs attention and possibly a disk swap\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostKernelVersionDeviations
    expr: count(sum(label_replace(node_uname_info, "kernel", "$1", "release", "([0-9]+.[0-9]+.[0-9]+).*")) by (kernel)) > 1
    for: 6h
    labels:
      severity: warning
    annotations:
      summary: Host kernel version deviations (instance {{ $labels.instance }})
      description: "Different kernel versions are running\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostOomKillDetected
    expr: increase(node_vmstat_oom_kill[1m]) > 0
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Host OOM kill detected (instance {{ $labels.instance }})
      description: "OOM kill detected\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostEdacCorrectableErrorsDetected
    expr: increase(node_edac_correctable_errors_total[1m]) > 0
    for: 0m
    labels:
      severity: info
    annotations:
      summary: Host EDAC Correctable Errors detected (instance {{ $labels.instance }})
      description: "Host {{ $labels.instance }} has had {{ printf \"%.0f\" $value }} correctable memory errors reported by EDAC in the last 5 minutes.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostNetworkTransmitErrors
    expr: rate(node_network_transmit_errs_total[2m]) / rate(node_network_transmit_packets_total[2m]) > 0.01
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: Host Network Transmit Errors (instance {{ $labels.instance }})
      description: "Host {{ $labels.instance }} interface {{ $labels.device }} has encountered {{ printf \"%.0f\" $value }} transmit errors in the last two minutes.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: HostRequiresReboot
    expr: node_reboot_required > 0
    for: 4h
    labels:
      severity: info
    annotations:
      summary: Host requires reboot (instance {{ $labels.instance }})
      description: "{{ $labels.instance }} requires a reboot.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: PrometheusJobMissing
    expr: absent(up{job="prometheus"})
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Prometheus job missing (instance {{ $labels.instance }})
      description: "A Prometheus job has disappeared\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: PrometheusTargetMissing
    expr: up == 0
    for: 0m
    labels:
      severity: critical
    annotations:
      summary: Prometheus target missing (instance {{ $labels.instance }})
      description: "A Prometheus target has disappeared. An exporter might be crashed.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: PrometheusAllTargetsMissing
    expr: sum by (job) (up) == 0
    for: 0m
    labels:
      severity: critical
    annotations:
      summary: Prometheus all targets missing (instance {{ $labels.instance }})
      description: "A Prometheus job does not have living target anymore.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: PrometheusTargetMissingWithWarmupTime
    expr: sum by (instance, job) ((up == 0) * on (instance) group_right(job) (node_time_seconds - node_boot_time_seconds > 600))
    for: 0m
    labels:
      severity: critical
    annotations:
      summary: Prometheus target missing with warmup time (instance {{ $labels.instance }})
      description: "Allow a job time to start up (10 minutes) before alerting that it's down.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: PrometheusConfigurationReloadFailure
    expr: prometheus_config_last_reload_successful != 1
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Prometheus configuration reload failure (instance {{ $labels.instance }})
      description: "Prometheus configuration reload error\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

  - alert: PrometheusTooManyRestarts
    expr: changes(process_start_time_seconds{job=~"prometheus|pushgateway|alertmanager"}[15m]) > 2
    for: 0m
    labels:
      severity: warning
    annotations:
      summary: Prometheus too many restarts (instance {{ $labels.instance }})
      description: "Prometheus has restarted more than twice in the last 15 minutes. It might be crashlooping.\n  VALUE = {{ $value }}\n  LABELS = {{ $labels }}"

```

### node_down.yml

```yml
groups:
- name: node_down
  rules:
  # 告警名称
  - alert: 节点离线告警
    # 告警的判定条件，参考Prometheus高级查询来设定
    expr: probe_success == 0
    # for表示告警持续时间，超过这个时间才会发送给alertmanager
    for: 10s
    # 标签项
    labels:
      severity: warning
    annotations:
      # 尽可能把详细告警信息写入summary标签值，因为告警短信/邮件/钉钉发送的内容使用了summary标签中的值
      summary: "Instance {{ $labels.instance }} 离线"
      # 这是一条告警描述
      description: "这是一条告警描述信息"
```


## 参考教程

### 监控插件安装

> https://blog.csdn.net/qq_29860591/article/details/108754090

```sh
[admin@Centos8 lx]$ wget https://github.com/prometheus/alertmanager/releases/download/v0.24.0/alertmanager-0.24.0.linux-amd64.tar.gz
[admin@Centos8 lx]$ ll | grep aler
-rw-rw-r--  1 admin   admin    25880024 10月 14 17:46 alertmanager-0.24.0.linux-amd64.tar.gz
[admin@Centos8 lx]$ tar -zxvf alertmanager-0.24.0.linux-amd64.tar.gz 
alertmanager-0.24.0.linux-amd64/
alertmanager-0.24.0.linux-amd64/alertmanager.yml
alertmanager-0.24.0.linux-amd64/LICENSE
alertmanager-0.24.0.linux-amd64/NOTICE
alertmanager-0.24.0.linux-amd64/alertmanager
alertmanager-0.24.0.linux-amd64/amtool
[admin@Centos8 lx]$ ll | grep aler
drwxr-xr-x  2 admin   admin          93 3月  25 2022 alertmanager-0.24.0.linux-amd64
-rw-rw-r--  1 admin   admin    25880024 10月 14 17:46 alertmanager-0.24.0.linux-amd64.tar.gz
[admin@Centos8 lx]$ mv alertmanager-0.24.0.linux-amd64/ alertmanager
[admin@Centos8 lx]$ ll | grep aler
drwxr-xr-x  2 admin   admin          93 3月  25 2022 alertmanager
-rw-rw-r--  1 admin   admin    25880024 10月 14 17:46 alertmanager-0.24.0.linux-amd64.tar.gz
[admin@Centos8 lx]$ cd alertmanager/
[admin@Centos8 alertmanager]$ ls
alertmanager  alertmanager.yml  amtool  LICENSE  NOTICE
[admin@Centos8 alertmanager]$ pwd
/opt/lx/alertmanager
[admin@Centos8 alertmanager]$ 
[admin@Centos8 alertmanager]$ 
[admin@Centos8 alertmanager]$ 
[admin@Centos8 alertmanager]$ sudo cp alertmanager /usr/local/bin/
[admin@Centos8 alertmanager]$ sudo cp amtool /usr/local/bin/
[admin@Centos8 alertmanager]$ alertmanager --version
alertmanager, version 0.24.0 (branch: HEAD, revision: f484b17fa3c583ed1b2c8bbcec20ba1db2aa5f11)
  build user:       root@265f14f5c6fc
  build date:       20220325-09:31:33
  go version:       go1.17.8
  platform:         linux/amd64
[admin@Centos8 alertmanager]$ sudo mkdir -pv /etc/alertmanager
mkdir: 已创建目录 '/etc/alertmanager'
[admin@Centos8 alertmanager]$ sudo touch /etc/alertmanager/alertmanager.yml
[admin@Centos8 alertmanager]$ sudo chmod 777 /etc/alertmanager/alertmanager.yml
[admin@Centos8 alertmanager]$ vim /etc/alertmanager/alertmanager.yml
[admin@Centos8 alertmanager]$ cat /etc/alertmanager/alertmanager.yml
global:
  resolve_timeout: 5m
  smtp_smarthost: 'smtp.qq.com:465'
  smtp_from: 'skywalker0@qq.com'
  smtp_auth_username: 'skywalker0@qq.com'
  smtp_auth_password: 'xikolfiokklfebaa'
  smtp_require_tls: false
route:
  receiver: mail
receivers:
  - name: 'mail'
    email_configs:
      - to: 'EMAIL@126.com'
[admin@Centos8 alertmanager]$ 
[admin@Centos8 alertmanager]$ alertmanager --config.file alertmanager.yml^C
[admin@Centos8 alertmanager]$ alertmanager --config.file /etc/alertmanager/alertmanager.yml
ts=2022-10-14T10:01:15.102Z caller=main.go:231 level=info msg="Starting Alertmanager" version="(version=0.24.0, branch=HEAD, revision=f484b17fa3c583ed1b2c8bbcec20ba1db2aa5f11)"
ts=2022-10-14T10:01:15.102Z caller=main.go:232 level=info build_context="(go=go1.17.8, user=root@265f14f5c6fc, date=20220325-09:31:33)"
ts=2022-10-14T10:01:15.104Z caller=cluster.go:185 level=info component=cluster msg="setting advertise address explicitly" addr=172.17.9.131 port=9094
ts=2022-10-14T10:01:15.121Z caller=cluster.go:680 level=info component=cluster msg="Waiting for gossip to settle..." interval=2s




http://8.143.7.110:9093/#/alerts

```

### mysql监控

> https://www.cnblogs.com/easydb/p/14151866.html

### Prometheus监控

>https://awesome-prometheus-alerts.grep.to/rules#prometheus-self-monitoring

>https://www.cnblogs.com/zhaojiedi1992/p/zhaojiedi_liunx_65_prometheus_alertmanager_rule.html