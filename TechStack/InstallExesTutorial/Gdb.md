
## GDB安装

本节下载的 GDB 源码包为 gdb-9.2-tar.gz，接下来以 CentOS 系统为例（也同样适用于其它 Linux 发行版），给大家演示整个安装过程：
1) 找到 gdb-9.2-tar.gz 文件，笔者将下载好的 gdb-9.2-tat.gz 放置在 /usr/local/src 目录下：

```sh
[root@bogon ~]# cd /usr/local/src
[root@bogon src]# ls
gdb-9.2.tar.gz
```

2) 使用 tar 命令解压该文件，执行命令如下：

```sh
[root@bogon ~]# tar -zxvf gdb-9.2.tar.gz
--省略解压过程的输出结果


[root@bogon src]# ls
gdb-9.2  gdb-9.2.tar.gz
```

此步骤会得到 gdb-9.2.tar.gz 相应的解压文件 gdb-9.2 。

3) 进入 gdb-9.2 目录文件，创建一个 gdb_build_9.2 目录并进入，为后续下载并放置安装 GDB 所需的依赖项做准备：

```sh
[root@bogon src]# cd gdb-9.2
[root@bogon gdb-9.2]# mkdir gdb-build-9.2
[root@bogon src]# cd gdb-build-9.2
```

4) 在此基础上，继续执行如下指令：

```sh
[root@bogon gdb-build-9.2]# ../configure
......    <--省略众多输出
configure: creating ./config.status
config.status: creating Makefile
```

5) 执行 make 指令编译整个 GDB 源码文件，此过程可能会花费很长时间，读者耐心等待即可：

```sh
[root@bogon gdb-build-9.2]# make
...... <-- 省略编译过程产生的输出结果

# 注意，如果编译过程中出现错误，极有可能是所用的 GCC 编译器版本过低导致的，可尝试升级 GCC 版本后再重新执行 make 命令。

# 或者出现错误后

WARNING: `makeinfo' is missing on your system.  You should only need it if
         you modified a `.texi' or `.texinfo' file, or any other file     

# 尝试以下命令

[root@bogon gdb-build-9.2]# yum install texinfo
```

6) 确定整个编译过程没有出错之后，执行sudo make install指令（其中使用 sudo 指令是为了避免操作权限不够而导致安装失败），正式开始安装 GDB 调试器：

```sh
[root@bogon gdb-build-9.2]# sudo make install
...... <-- 省略输出结果

以上过程全部成功执行，则表示 GDB 安装成功。通过再次执行 gdb -v 指令，可验证其是否被成功安装。
[root@bogon gdb-build-9.2]# gdb -v
GNU gdb (GDB) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
......  <-- 省略部分输出
```

## 测试用例

```sh
[root@SqaServer gdb]# cat gdb-sample.c 
#include <stdio.h>
int nGlobalVar = 0;

int tempFunction(int a, int b)
{
    printf("tempFunction is called, a = %d, b = %d \n", a, b);
    return (a + b);
}

int main()
{
    int n;
        n = 1;
        n++;
        n--;

        nGlobalVar += 100;
        nGlobalVar -= 12;

    printf("n = %d, nGlobalVar = %d \n", n, nGlobalVar);

        n = tempFunction(1, 2);
    printf("n = %d", n);

    return 0;
}
[root@SqaServer gdb]# 
```

## gdb测试
```sh
#在下面的命令行中，使用 -o 参数指定了编译生成的可执行文件名为 gdb-sample，
#使用参数 -g 表示将源代码信息编译到可执行文件中。如果不使用参数 -g，会给后面的GDB调试造成不便
#当然，如果我们没有程序的源代码，自然也无从使用 -g 参数，调试/跟踪时也只能是汇编代码级别的调试/跟踪。

[root@SqaServer gdb]# gcc gdb-sample.c -o gdb-sample -g
[root@SqaServer gdb]# ll
总用量 37716
-rwxrwxrwx 1 root root 38604458 5月   2 2022 gdb-12.1.tar.gz
-rwxr-xr-x 1 root root    11064 11月 17 10:42 gdb-sample
-rwxrwxrwx 1 root root      435 11月 17 10:43 gdb-sample.c
#下面“gdb”命令启动GDB，将首先显示GDB说明，：
[root@SqaServer gdb]# gdb
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-120.el7
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
#下面使用“file”命令载入被调试程序 gdb-sample（这里的 gdb-sample 即前面 GCC 编译输出的可执行文件）：
(gdb) file gdb-sample
Reading symbols from /tmp/soft/gdb/gdb-sample...done.
#上面最后一行提示已经加载成功。
#下面使用“r”命令执行（Run）被调试文件，因为尚未设置任何断点，将直接执行到程序结束：
(gdb) r
Starting program: /tmp/soft/gdb/gdb-sample 
n = 1, nGlobalVar = 88 
tempFunction is called, a = 1, b = 2 
n = 3[Inferior 1 (process 11509) exited normally]
Missing separate debuginfos, use: debuginfo-install glibc-2.17-326.el7_9.x86_64
#下面使用“b”命令在 main 函数开头设置一个断点（Breakpoint）：
(gdb) b main
Breakpoint 1 at 0x400549: file gdb-sample.c, line 13.
#上面最后一行提示已经成功设置断点，并给出了该断点信息：在源文件 gdb-sample.c 第19行处设置断点
#这是本程序的第一个断点（序号为1）；断点处的代码地址为 0x804835c（此值可能仅在本次调试过程中有效）。
#回过头去看源代码，第13行中的代码为“n = 1”，恰好是 main 函数中的第一个可执行语句（前面的“int n;”为变量定义语句，并非可执行语句）。

#再次使用“r”命令执行（Run）被调试程序：
(gdb) r
Starting program: /tmp/soft/gdb/gdb-sample 

Breakpoint 1, main () at gdb-sample.c:13
13	        n = 1;

#程序中断在gdb-sample.c第13行处，即main函数是第一个可执行语句处。
#上面最后一行信息为：下一条将要执行的源代码为“n = 1;”，它是源代码文件gdb-sample.c中的第19行。

#下面使用“s”命令（Step）执行下一行代码（即第13行“n = 1;”）：
(gdb) s
14	        n++;
#上面的信息表示已经执行完“n = 1;”，并显示下一条要执行的代码为第14行的“n++;”。
#既然已经执行了“n = 1;”，即给变量 n 赋值为 1，那我们用“p”命令（Print）看一下变量 n 的值是不是 1 ：
(gdb) p n
$1 = 1
#果然是 1。（$1大致是表示这是第一次使用“p”命令——再次执行“p n”将显示“$2 = 1”——此信息应该没有什么用处。）

#下面我们分别在第26行、tempFunction 函数开头各设置一个断点（分别使用命令“b 20”“b tempFunction”）：

(gdb) b 20
Breakpoint 2 at 0x400576: file gdb-sample.c, line 20.
(gdb) b tempFunction
Breakpoint 3 at 0x400520: file gdb-sample.c, line 6.
(gdb) 
Note: breakpoint 3 also set at pc 0x400520.
Breakpoint 4 at 0x400520: file gdb-sample.c, line 6.
#使用“c”命令继续（Continue）执行被调试程序，程序将中断在第二 个断点（20行），此时全局变量 nGlobalVar 的值应该是 88；
#再一次执行“c”命令，程序将中断于第三个断点（6行，tempFunction 函数开头处），此时tempFunction 函数的两个参数 a、b 的值应分别是 1 和 2：

(gdb) c
Continuing.

Breakpoint 2, main () at gdb-sample.c:20
20	    printf("n = %d, nGlobalVar = %d \n", n, nGlobalVar);
(gdb) c
Continuing.
n = 1, nGlobalVar = 88 

Breakpoint 3, tempFunction (a=1, b=2) at gdb-sample.c:6
6	    printf("tempFunction is called, a = %d, b = %d \n", a, b);
(gdb) p a
$2 = 1
(gdb) p b
$3 = 2
#上面反馈的信息一切都在我们预料之中~~

#再一次执行“c”命令（Continue），因为后面再也没有其它断点，程序将一直执行到结束：
(gdb) c
Continuing.
tempFunction is called, a = 1, b = 2 
n = 3[Inferior 1 (process 12101) exited normally]

#有时候需要看到编译器生成的汇编代码，以进行汇编级的调试或跟踪，又该如何操作呢？
#这就要用到display命令“display /i $pc”了（此命令前面已有详细解释）：
(gdb) display /i $pc
#此后程序再中断时，就可以显示出汇编代码了：
(gdb) r
Starting program: /tmp/soft/gdb/gdb-sample 

Breakpoint 1, main () at gdb-sample.c:13
13	        n = 1;
1: x/i $pc
=> 0x400549 <main+8>:	movl   $0x1,-0x4(%rbp)
# 看到了汇编代码，“n = 1;”对应的汇编代码是“movl   $0x1,-0x4(%rbp)”。

# 并且以后程序每次中断都将显示下一条汇编指定（“si”命令用于执行一条汇编代码——区别于“s”执行一行C代码）：

(gdb) si
14	        n++;
1: x/i $pc
=> 0x400550 <main+15>:	addl   $0x1,-0x4(%rbp)
(gdb) si
15	        n--;
1: x/i $pc
=> 0x400554 <main+19>:	subl   $0x1,-0x4(%rbp)
(gdb) si
17	        nGlobalVar += 100;
1: x/i $pc
=> 0x400558 <main+23>:	mov    0x200ada(%rip),%eax        # 0x601038 <nGlobalVar>
# 接下来我们试一下命令“b *<函数名称>”。

#为了更简明，有必要先删除目前所有断点（使用“d”命令——Delete breakpoint）：
(gdb) d
Delete all breakpoints? (y or n) y
#当被询问是否删除所有断点时，输入“y”并按回车键即可。

#下面使用命令“b *main”在 main 函数的 prolog 代码处设置断点（prolog、epilog，分别表示编译器在每个函数的开头和结尾自行插入的代码）：

(gdb) b *main
Breakpoint 5 at 0x400541: file gdb-sample.c, line 11.
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /tmp/soft/gdb/gdb-sample 

Breakpoint 5, main () at gdb-sample.c:11
11	{
1: x/i $pc
=> 0x400541 <main>:	push   %rbp
(gdb) si
0x0000000000400542	11	{
1: x/i $pc
=> 0x400542 <main+1>:	mov    %rsp,%rbp
(gdb) si
0x0000000000400545	11	{
1: x/i $pc
=> 0x400545 <main+4>:	sub    $0x10,%rsp
(gdb) si
13	        n = 1;
1: x/i $pc
=> 0x400549 <main+8>:	movl   $0x1,-0x4(%rbp)
(gdb) si
14	        n++;
1: x/i $pc
=> 0x400550 <main+15>:	addl   $0x1,-0x4(%rbp)
(gdb) si
15	        n--;
1: x/i $pc
=> 0x400554 <main+19>:	subl   $0x1,-0x4(%rbp)
(gdb) si
17	        nGlobalVar += 100;
1: x/i $pc
=> 0x400558 <main+23>:	mov    0x200ada(%rip),%eax        # 0x601038 <nGlobalVar>
#此时可以使用“i r”命令显示寄存器中的当前值———“i r”即“Infomation Register”：
(gdb) i r
rax            0x400541	4195649
rbx            0x0	0
rcx            0x4005c0	4195776
rdx            0x7fffffffe228	140737488347688
rsi            0x7fffffffe218	140737488347672
rdi            0x1	1
rbp            0x7fffffffe130	0x7fffffffe130
rsp            0x7fffffffe120	0x7fffffffe120
r8             0x7ffff7dd5e80	140737351868032
r9             0x0	0
r10            0x7fffffffdc60	140737488346208
r11            0x7ffff7a2f460	140737348039776
r12            0x400440	4195392
r13            0x7fffffffe210	140737488347664
r14            0x0	0
r15            0x0	0
rip            0x400558	0x400558 <main+23>
eflags         0x202	[ IF ]
cs             0x33	51
ss             0x2b	43
ds             0x0	0
es             0x0	0
fs             0x0	0
gs             0x0	0
(gdb) i r eax
eax            0x400541	4195649
(gdb) q
A debugging session is active.

	Inferior 1 [process 12970] will be killed.

Quit anyway? (y or n) y
[root@SqaServer gdb]# 
```

## 使用手册

> https://zhuanlan.zhihu.com/p/297925056
> http://c.biancheng.net/gdb/

## 实战技巧

> https://wizardforcel.gitbooks.io/100-gdb-tips/content/set-var.html

## GDB调试代码

> https://www.jianshu.com/p/c9219fb0fd66
