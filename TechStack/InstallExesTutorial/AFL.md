## 上传并解压工具

```sh
wget https://ghdl.feizhuqwq.cf/https://github.com/google/AFL/archive/refs/tags/v2.57b.tar.gz
[root@k8smaster soft]# tar -zxvf AFL-2.57b.tar.gz 
[root@k8smaster soft]# ls
AFL-2.57b  AFL-2.57b.tar.gz
[root@k8smaster soft]#
2.编译（默认已经具备gcc环境）
[root@k8smaster AFL-2.57b]# make
[root@k8smaster AFL-2.57b]# make install
当输入afl-后使用Tab补全出现如下内容证明安装成功
[root@k8smaster AFL-2.57b]# afl-
afl-analyze  afl-clang++  afl-fuzz     afl-gcc      afl-plot     afl-tmin     
afl-clang    afl-cmin     afl-g++      afl-gotcpu   afl-showmap  afl-whatsup  
[root@k8smaster AFL-2.57b]#
```

```txt
备注：针对以上内容的解释
• afl-gcc 和afl-g++ 分别对应的是gcc 和g++ 的封装
• afl-clang 和afl-clang++ 分别对应clang 的c 和c++ 编译器封装À。
• afl-fuzz 是AFL 的主体，用于对目标程序进行fuzz。
• afl-analyze 可以对用例进行分析，通过分析给定的用例，看能否发现用例中有意义的字段。
• afl-qemu-trace 用于qemu-mode，默认不安装，需要手工执行qemu-mode 的编译脚本进行编译，后面会介绍。
• afl-plot 生成测试任务的状态图
• afl-tmin 和afl-cmin 对用例进行简化
• afl-whatsup 用于查看fuzz 任务的状态
• afl-gotcpu 用于查看当前CPU 状态
• afl-showmap 用于对单个用例进行执行路径跟踪
```

## 创建相应文件夹并编制测试脚本

```sh
[root@k8smaster AFL-2.57b]# mkdir fuzz_in fuzz_out
[root@k8smaster AFL-2.57b]# echo "123AFc" >> fuzz_in/1
[root@k8smaster AFL-2.57b]# ls afl_test/afl_test*
afl_test/afl_test.c
[root@k8smaster AFL-2.57b]# cat ./afl_test/afl_test.c 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <signal.h> 
int vuln(char *str)
{
    int len = strlen(str);
    if(str[0] == 'A' && len == 66)
    {
        raise(SIGSEGV);
        //如果输入的字符串的首字符为A并且长度为66，则异常退出
    }
    else if(str[0] == 'F' && len == 6)
    {
        raise(SIGSEGV);
        //如果输入的字符串的首字符为F并且长度为6，则异常退出
    }
    else
    {
        printf("it is good!\n");
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char buf[100]={0};
    gets(buf);//存在栈溢出漏洞
    printf(buf);//存在格式化字符串漏洞
    vuln(buf);

    return 0;
}
```

## C文件编译

```sh
[root@k8smaster AFL-2.57b]# [root@k8smaster AFL-2.57b]# afl-gcc -g -o ./afl_test/afl_test  ./afl_test/afl_test.c
```

## 参考链接

>https://zhuanlan.zhihu.com/p/524552737

>https://www.jianshu.com/p/a77274dcebce
