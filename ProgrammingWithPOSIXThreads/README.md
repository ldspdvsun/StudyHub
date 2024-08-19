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
# alarm.c
#include <stdio.h>
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

    有多种异步实现该程序的方法，例如可以实现多个程序拷贝。其中一种方式就是为每个命令使用fork调用生成一个子进程，就像alarm_fork.c中那样。新版本是异步方式的——可以随时输入命令行，他们彼此独立地执行。新版本并不比原版本复杂多少。

    alarm.c和alarm_fork.c的主要区别在于：新版本的main函数没有直接调用sleep函数，而是创建一个子进程，在子进程中异步地调用sleep函数（和printf），而父进程则继续运行。

    该版本的主要单点在于对所有已终止子进程的reap。如果程序不做这个工作，则要等待程序退出的时候系统回收，通常回收子进程的方法是调用某个wai系列函数。在本例中，我们调用waitpid函数，并设置WNOHANG(父进程不必挂起等待子进程的结束)。如果有子进程终止，该函数调用回收该子进程的资源；如果没有子进程终止，该函数调用回收该子进程的资源；如果没有子进程终止，该函数立即返回pid=0。父进程继续回收种植的子进程直到没有子进程终止。当循环终止的时候，main函数继续循环到while，读取下一个命令。

```c
# alarm_fork.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void errno_abort(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
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

        if (sscanf(line, "%d %63[^\n]", &seconds, message) < 2)
        {
            fprintf(stderr, "Bad input format\n");
        }
        else if (seconds <= 0)
        {
            fprintf(stderr, "Seconds must be a positive integer\n");
        }
        else
        {
            pid = fork();
            if (pid == (pid_t)-1)
            {
                errno_abort("Fork");
            }

            if (pid == (pid_t)0)
            {
                sleep(seconds);
                printf("Sleep %d seconds, Alarm: %s\n", seconds, message);
                exit(0);
            }
            else
            {
                do
                {
                    pid = waitpid((pid_t)-1, &status, WNOHANG);
                    if (pid == (pid_t)-1)
                    {
                        errno_abort("Wait for child pid");
                    }
                } while (pid > 0);
            }
        }
    }
}

```

### 多线程版本

    多线程版本和和多进程版本十分相似，只是使用线程而非子进程来实现异步闹钟。本例中使用到以下三个Pthreads函数：

* pthread_create函数建立一个线程，运行由第三个参数（alarm_thread）指定的例程，并返回线程标识符ID（保存在thread引用的变量中）。
* pthread_detach函数运行Pthreads当线程终止时立刻回收线程资源。
* pthread_exit函数终止调用线程
  数据结构alarm_t中定义了每个闹钟命令的信息，其中seconds中包含等待时间，message中包含显示文本。

    函数alarm_thread就是闹铃线程，即创建的每个闹铃线程执行该函数，当函数返回时，闹铃线程终止。该函数的参数（void *arg）就是传递pthread_create函数的第四个参数，即包含闹铃请求命令的alarm_t结构指针。线程首先将void *参数转换为alarm_t *类型，然后调用pthread_detach函数来分离自己，以通知Pthreads不必关心他的终止时间和退出状态。

    线程睡眠指定的时间由（alarm_t结构中的seconds决定），然后打印指定的消息字符串，最后，线程释放alarm_t结构空间并返回

```
# alarm_thread.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct alarm_tag
{
    int seconds;
    char message[100];
} alarm_t;

static void errno_abort(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void *alarm_thread(void *arg)
{
    alarm_t *alarm = (alarm_t *)arg;
    int status;

    status = pthread_detach(pthread_self());
    if (status != 0)
    {
        errno_abort("pthread_detach");
    }
    sleep(alarm->seconds);
    printf("Sleep %d seconds, Alarm: %s\n", alarm->seconds, alarm->message);
    free(alarm);
    return NULL;
}

int main()
{
    int status;
    char line[100];
    pthread_t thread;

    while (1)
    {
        printf("Alarm> \n");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        if (strlen(line) <= 1)
        {
            continue;
        }

        alarm_t *alarm = (alarm_t *)malloc(sizeof(alarm_t));
        if (alarm == NULL)
        {
            errno_abort("Allocate alarm");
        }

        if (sscanf(line, "%d %99[^\n]", &alarm->seconds, alarm->message) < 2)
        {
            fprintf(stderr, "Invalid input\n");
            free(alarm);
        }
        else
        {
            status = pthread_create(&thread, NULL, alarm_thread, alarm);
            if (status != 0)
            {
                errno_abort("pthread_create");
            }
        }
    }

    return 0;
}

```

## 选择线程还是不用线程

    线程无需给所有编程问题提供最好的解决方案。线程并非总是容易使用，而且并非总是可达到更好的性能，一些问题本身就是非并发的，添加线程只能降低程序的性能并使程序更复杂。如果程序中的每一步都需要上一步的结果，则使用线程不会有任何帮助。

    最适合使用线程的是实现以下功能的应用：

1. 计算密集型应用，为了能在多处理器系统上运行，将这些计算分解到多个线程中实现。
2. I/O密集型应用，为提高性能，将I/O操作重叠。很多线程可以同时等他待不同的I/O操作。

# 线程

## 建立和使用线程

    程序中使用线程标识符ID来表示线程。线程ID属于封装的pthread_t类型。为建立线程，需要在程序中声明一个pthread_t类型变量。

    Pthreads线程通过调用提供的某些函数开始。这个“线程函数”应该只有一个void *类型参数，并返回相同的类型值。通过向pthread_create函数传送线程函数地址和线程函数调用参数来创建线程。

    当创建线程时，pthread_create函数返回一个phtread_t类型的线程ID，并保存在thread参数中。通过这个线程ID，程序可以引用该线程。线程可以通过调用pthread_self来获得自身的ID。除非线程的创建者或线程本身将线程ID保存于某处，否则不可能获得一个线程的ID。要对线程进行任何操作时都必须通过线程ID。例如，如果要知道线程何时结束就需要保存线程ID。

```c
/**
 * @file lifecycle.c
 * @author sunmy
 * @date 2024-08-19
 * @brief This is the implementation of pthread lifecycle example.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <error.h>

typedef struct thread_args
{
    int value;
    char name[100];
} thread_args;

static void *thread_routine(void *arg)
{
    thread_args *args = (thread_args *)arg;
    printf("value: %d, name: %s\n", args->value, args->name);

    printf("Thread id: %lu\n", pthread_self());
    return arg;
}

int main()
{
    pthread_t thread_id;
    void *thread_result;
    int status;

    thread_args *args = (thread_args *)malloc(sizeof(thread_args));
    args->value = 100;
    strcpy(args->name, "Thread Child");

    status = pthread_create(&thread_id, NULL, thread_routine, args);
    if (status != 0)
    {
        error(1, status, "pthread_create failed");
    }
    else
    {
        printf("Thread created successfully\n");
    }

    printf("Main thread id: %lu\n", pthread_self());

    status = pthread_join(thread_id, &thread_result);
    if (status != 0)
    {
        error(1, status, "pthread_join failed");
    }
    else
    {
        printf("Thread joined successfully\n");
    }

    if (thread_result == NULL)
    {
        printf("Thread returned NULL, Test failed\n");
        return 0;
    }
    else
    {
        printf("Thread returned %p Test passed\n", thread_result);
        return 1;
    }

    return 0;
}
```

## 线程的声明周期

# 同步

## 不变量、临界区和谓词

## 互斥量

## 条件变量

## 线程间的内存可视性

# 使用线程的几种方式

## 流水线

## 工作组

## 客户/服务器

# 线程高级编程

## 一次性初始化

## 属性

## 取消

## 线程私有数据

## 实时调度

## 线程和核实体

# POSIX针对线程的调整

## fork

## exec

## 进程结束

## stdio

## 线程安全的函数

## 信号

# Real code

## 扩展同步

## 工作队列管理器

## 对现存库的处理

# 避免调试的提示

# POSIX多线程快速参考

# 标准化过程展望

---
