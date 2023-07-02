## 安装

```sh
admin@Centos8 lx]$ cat /etc/redhat-release
CentOS Linux release 8.5.2111
[admin@Centos8 lx]$ sudo yum install perf
akopytov_sysbench                                                                                                                                                                                        214  B/s | 833  B     00:03    
akopytov_sysbench-source                                                                                                                                                                                 229  B/s | 833  B     00:03    
软件包 perf-4.18.0-348.7.1.el8_5.x86_64 已安装。
依赖关系解决。
无需任何处理。
完毕！
```

## 查看参数信息

```sh
[admin@Centos8 lx]$ perf -h

 usage: perf [--version] [--help] [OPTIONS] COMMAND [ARGS]

 The most commonly used perf commands are:
   annotate        Read perf.data (created by perf record) and display annotated code
   archive         Create archive with object files with build-ids found in perf.data file
   bench           General framework for benchmark suites
   buildid-cache   Manage build-id cache.
   buildid-list    List the buildids in a perf.data file
   c2c             Shared Data C2C/HITM Analyzer.
   config          Get and set variables in a configuration file.
   daemon          Run record sessions on background
   data            Data file related processing
   diff            Read perf.data files and display the differential profile
   evlist          List the event names in a perf.data file
   ftrace          simple wrapper for kernel's ftrace functionality
   inject          Filter to augment the events stream with additional information
   kallsyms        Searches running kernel for symbols
   kmem            Tool to trace/measure kernel memory properties
   kvm             Tool to trace/measure kvm guest os
   list            List all symbolic event types
   lock            Analyze lock events
   mem             Profile memory accesses
   record          Run a command and record its profile into perf.data
   report          Read perf.data (created by perf record) and display the profile
   sched           Tool to trace/measure scheduler properties (latencies)
   script          Read perf.data (created by perf record) and display trace output
   stat            Run a command and gather performance counter statistics
   test            Runs sanity tests.
   timechart       Tool to visualize total system behavior during a workload
   top             System profiling tool.
   version         display the version of perf binary
   probe           Define new dynamic tracepoints
   trace           strace inspired tool

 See 'perf help COMMAND' for more information on a specific command.

[admin@Centos8 lx]$ perf top
[admin@Centos8 lx]$ 
```