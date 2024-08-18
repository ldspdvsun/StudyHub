# ProgrammingWithPOSIXThreads（多线程程序设计）

# 概述

## 基础概念

1. 异步（asynchronous）：表面事情相互独立地发生，除非有强加的依赖性。
2. 并发（concurrency）：指事情同时发生，在本书中，并发是指让实际上可能串行发生的事情好像同时发生一样。在POSIX中，并发的定义要求“延迟调用线程的函数不应该导致其他线程的无限期延迟”。
3. 单处理器(uniprocessor)和多处理器（multiprocessor）：单处理器指一台计算机只有一个编程人员可见的执行单元（处理器）。多处理器指一台计算机拥有多个处理器，他们共享同一个指令集和相同的物理内存。
4. 并行（parallelism）：指并发序列同时执行。真正的并行只能在多核处理器系统中存在，但是并发可以在单处理器和多处理器系统中都存在。并发能够在单处理器系统中存在是因为并发实际上是并行的假象。并行要求程序能够同时执行多个操作，而并发只要求程序能够假装同时执行多个操作。
5. 线程安全和可重入：线程安全是指代码能够被多个线程调用而不会产生灾难性结果。它不要求代码在多个线程中高效地运行，只要求能够安全地运行；可重入有是用来表示有效的线程安全，即通过采用比将函数或库转换成一系列区域更为复杂的方式使代码成为线程安全的。
6. 进程：UNIX进程包含了需要执行代码的所有欣欣，所以可以异步执行。UNIX进程包括与执行环境不直接相关的附加状态数据，如地址空间和文件描述符。
7. 线程：线程就是进程里足以执行代码的部分。在大多数计算机系统中，这意味着线程应该包括以下内容：当前指令位置指针（通常称为计数器或PC）、栈顶指针（SP）、通用寄存器、浮点或地址寄存器。线程可能还包括项处理器状态和协处理器寄存器等数据。线程不包括进程中其他数据，如地址空间和文件描述符。**一个进程中的所有线程共享文件和内存空间，包括程序文本段和数据段**。

## 异步编程举例

    本节将通过一个简单的闹钟实例程序来掩饰基本的异步编程方法。

    该程序循环接收用户输入信息，知道出错或输入完毕。用户输入的每行信息中，第一部分是闹钟等待的时间（以秒为单位），第二部分是闹钟时间到达时显示的文本信息。还提供另外两个版本，一个使用多进程，一个使用多线程。

### 基本的同步版本

    基本版本alarm.c是只有一个main函数的同步闹钟程序。Main函数的大部分是一个循环，在里面处理简单的命令直到fgets返回NULL(出错或者文件尾)。每行命令由scanf函数解析成等待时间（%d，数字序列）和打印的消息（%64[^\\n]，最多64字符）两部分。

```c
include <stdio.h>
#include <error.h>

int main(int argc, char *argv[])
{
    int seconds = 0;
    char line[128];
    char message[64];

    while (1)
    {
        printf("Alarm >\n");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        if (strlen(line) <= 1)
        {
            continue;
        }

        /**
         * Parse input line into seconds and message
         * (%63[^\n]), consisting of up to 63 characters
         * separated from the seconds by a space, and
         * terminated by a newline character.
         * 
         */
        if (sscanf(line, "%d %63[^\n]", &seconds, message) < 2)
        {
            fprintf(stderr, "Invalid input\n");
            continue;
        }
        else if (seconds < 0)
        {
            fprintf(stderr, "Invalid input\n");
            continue;
        }
        else
        {
            sleep(seconds);
            printf("Alarm (%d) seconds: %s\n", seconds, message);
        }
    }
}
```

### 多进程版本


### 多线程版本


# 线程

# 同步

# 使用线程的几种方式

# 线程高级编程

# POSIX针对线程的调整

# Real code

# 避免调试的提示

# POSIX多线程快速参考

# 标准化过程展望

---
