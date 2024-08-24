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
8. Pthreads：在本文章中"Pthreads"代表"POSIX 1003.1c-1995"，用稍微正式的术语"POSIX1.b"来表示"POSIX 1003.1b-1993"；用“POSIX.14”表示“POSIX 1003.14多处理器系统主题”

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

    任意时刻，线程处于下表所示的四个基本状态之一。

|           状态           | 含义                                                                                                                                               |
| :----------------------: | -------------------------------------------------------------------------------------------------------------------------------------------------- |
|   就绪<br />（ready）   | 线程能够运行，但在等待可用的处理器。可能刚刚启动，或刚刚从阻塞中恢复，或者被其他线程抢占                                                           |
|  运行<br />（running）  | 线程正在运行。在多处理器系统中，可能有多个线程处于运行状态                                                                                         |
|  阻塞<br />（Blocked）  | 线程由于等待处理器外的其他条件无法运行，如条件变量的改变、加锁互斥量或I/O操作结束                                                                  |
| 终止<br />（Terminated） | 线程从起始函数中返回，或调用pthread_exit，或者被取消，终止自己并完成所有资源清理工作。不是被分离，也不是被等待结束，一旦线程被分离，他就可以被回收 |

    线程开始于就绪状态，当线程运行时，他调用特定的起始函数。他可能被其他线程抢占，或者因等待外来事件而阻塞自己。最终线程完成工作，或者从起始函数返回，或者调用pthread_exit函数，即进入终止态。如果线程已被分离，则它立刻被回收重用；否则线程停留在终止态直到被分离或者被等待结束。下图显示了线程状态间的转换关系及激发状态转换的事件。

[![image.png](https://i.postimg.cc/vm5Dzgdb/image.png)](https://postimg.cc/t1CXRgTM)

### 创建线程

    Pthreads系统中建立线程的主要方式是调用pthread_create。如果进程的信号通知机制设为SIGEV_THREAD，则当进程收到一个POSIX信号时也会创建线程。

    在新线程建立后，他就处于就绪态。受调度机制的限制，新线程可能在**就绪态**停留一段时间后才被执行。回到示例程序lifecycle.c，运行thread_routin函数的线程在main函数调用pthread_create时处于就绪态。

    有关线程创建最重要的是，**在当前线程从函数pthread_create中返回以及新线程被调度执行之间不存在同步关系**。即，新线程可能在当前线程从pthread_create返回之前就运行了。甚至在当前线程从pthread_create返回之前，新线程就已经运行完毕了。

### 线程启动

    一旦线程被创建，最终它将开始执行机器指令。初始指令序列将导致在pthread_create调用中指定的线程启动函数的执行。线程启动函数的运行参数也是在创建线程时指定。例如，在lifecycle.c中，新线程使用参数args开始运行thread_routine函数中用户代码。

    在初始线程中，线程的启动函数（即main函数）是从程序外部调用的。例如，很多UNIX系统中将程序链接到一个crt0.o文件上，该文件负责初始化进程，然后调用main函数。这虽是一个较小的实现区别，但应该记住初始线程与普通线程之间存在的一些不同。如main函数的调用参数（argc和argv）与普通线程的启动函数不同（void *参数）。另一方面，如果普通线程从启动函数中返回时，则进程终止而其他线程依然可以运行；但初始进程从main函数中返回时，进程终止（进程内所有线程也被终止）。如果你希望在初始线程终止时，进程中的其他线程继续执行，则需要在初始线程中调用pthread_exit而不是从main函数中返回。

    另一个重要的区别时：在大多数性中，初始线程运行在默认进程堆栈上，该堆栈可以增长到足够的尺寸；而在某些视线中，普通线程的堆栈空间是受限的，如果线程堆栈溢出，则程序会因段错误或总线错误而失败。

### 运行和阻塞

    线程不可能一直保持清醒。大多数线程会不时地睡眠休息。线程之所以会睡眠是因为他需要的某个资源不可用（即被阻塞），或者因为系统将处理器分配给其他线程（即被抢占）。**线程大多数时间处于其生命周期中的三个状态：就绪、运行和阻塞。**

    当线程刚被创建时，或者当线程解除阻塞再次可以运行时，线程处于就绪态。就绪的线程在等待可用的处理器。同样，当一个运行线程被抢占时，如被时间片机制抢占（因为它已经运行足够长时间），线程立即进入就绪态。

    当处理器选中一个就绪线程执行它时，该线程进入运行态。通常这意味着某个其他线程被阻塞或者被时间片机制抢占，则处理器会保存被阻塞（或抢占）线程的环境并恢复下一个就绪线程的环境。不过在多处理器系统中，一个未用的处理器可以执行一个就绪线程而不必由于其他线程被阻塞。

    线程在以下情况时被阻塞：试图加锁一个已经被锁住的互斥量；等待某个条件变量；调用Singwait等待尚未发生的信号；执行无法立即完成的I/O操作。线程还会有与如内页错误之类的系统操作而被阻塞。

    在线程等到某个事件发生后，重新进入就绪态。如果处理器可用，它可以马上运行。在程序lifecycle.c中，主线程在调用pthread_join时进入阻塞态，等待它创建的线程运行结束。如果新线程此时没有运行，则他将在主线程被阻塞后从就绪态进入运行态。当新线程运行完毕并返回时，主线程才会被解除阻塞，返回就绪态。当处理器可用时，主线程或者立即执行或者等到创建的线程终止后重新运行直到结束。

### 终止

    线程通常从启动函数中返回来终止即。例如程序lifecycle.c中的线程返回NULL后，线程终止。当调用pthread_exit退出线程或者调用pthread_cancel取消线程时，线程在调用完每个清理过程后也将进入终止态。这些清理过程是由线程通过pthread_cleanup_push注册的，而且尚未通过调用pthread_cleanup_pop删除。

    线程还会有私有的“线程特定数据”（线程私有数据将在5.4节讲述）。如果线程有非空的私有数据值，则与这些数据相关的destructor函数将被调用。

    如果线程已经被分离，则它立刻进入下一节——回收；否则，线程处于终止态，它还可以被其他线程调用pthread_join等待结束。这就像UNX中的进程已经结束但还没有被一个wait调用回收一样。有时这种线程被称为“僵”线程，因为即使它们已经死了但还存在。僵线程可能会保留其运行时的大部分甚至所有资源，因此不应该让线程长时间处于这种状态。当创建不需等待结束的线程时，应该使用detachstate属性建立线程使其自动分离。

    终止后线程至少保留了线程ID(pthread_t类型数据)和void*返回值。该返回值从线程启动函数中返回或者在pthread_exit调用时设定。**通过函数返回或者pthread._exit调用正常终止的线程与通过取消调用终止的线程间的唯一外部区别是：被取消的线程其返回值总是PTHREAD_CANCELLED(这也是不把取消视为一种独立线程状态的原因)**。

    如果有其他线程在等待结束进入终止态的线程，则该其他线程将被唤醒。它将从其pthread_join调用中返回相应的值。一旦pthread join获得返回值，终止线程就被pthread_join函数分离，并且可能在pthread_join函数返回前被回收。这意味着，返回值一定不要是与终止线程堆栈相关的堆栈地址，因为该地址上的值可能在调用线程能够访问之前就被覆盖了。

    pthread_join是有用的，但不是规则。

    即使当你需要获得返回值时，建立分离的线程并定制自已的返回机制通常与使用pthread_join一样简单。例如，如果传给一个工作线程某种形式的数据结构，且该结构能够被其他线程访问，你可以让工作线程简单地将结果数据保存在该数据结构中，然后广播某个条件变量。做完这些之后，该线程的环境数据（包括线程ID就可以被立即回收，而你关心的返回值始终保存在你随时可以找到的地方。如果pthread_join恰恰实现了你想要的功能，则一定要使用它。不过要记住，这不过是最简单也是最受限的传递返回值的模型。如果pthread_join不能直接实现你想要的功能，则设计你自己的返回机制，而不要扭曲自己的设计来满足pthread_join的限制。

### 回收

    如果使用detachstate属性（设为PTHREAD_CREATE_DETACH）建立线程，或者调用pthread_detach分离线程，则当线程结束时被立刻回收。

    如果终止线程没有被分离，则他将一直处于终止态直到被分离（通过pthread_detach）或者被等待结束（pthread_join）。线程一旦被分离，就不能再访问他了。例如在程序lifecycle.c中，运行thread_routine的线程从pthread_join调用返回时将被回收。

    回收将释放所有在线程终止时未释放的系统和进程资源，包括保存线程返间值的内存空间、堆栈、保存寄存器状态的内存空间等。其中一些资源可能已在线程终止时被释放，但必须记住：在线程终止后上述资源就不该被访问了。例如，如果一个线程将其堆栈空间指针通过共享数据传给另一个线程，则当该线程终止后，此数据就是陈旧数据了。

    一旦线程被回收，线程ID就无效了，不能再等待它结束、取消它或者执行其他任何操作。终止线程ID(可能是系统数据结构地址)可能被分给新的线程。使用该ID调用pthread_cancel可能就会取消一个不同的线程，而不是返回ESRCH错误。

    终止线程将释放所有系统资源，但你必须释放由该线程占有的程序资源。调用ma11oc或mmap分配的内存可以在任何时候、由任何线程释放。互斥量、条件变量和信号灯可以由任何线程销毁，只要它们被解锁并没有线程等待。但是，只有互斥量的主人能够解锁它。如果线程终止时还有加锁的互斥量，则该互斥量就不能被再次使用（因为不会被解锁）。

# 同步

## 不变量、临界区和谓词

    不变量（invariant）是由程序作出的假设，特别是有关变量组间关系的假设。

    临界区（有时称为”串行区域“）是指影响共享数据的代码段。

    ”谓词“（Predicate）是描述代码所需不变量的状态的语句。

## 互斥量

    使线程同步最通用和最常用的方法就是确保对相同（或相关）数据的内存访问”互斥地“进行，即一次只能允许一个线程写数据，其他线程必须等待。Pthreads使用互斥量来实现。

### 创建和销毁互斥量

    程序中的互斥量使用pthread_mutex_t类型的变量来表示的。不能拷贝互斥量变量，因为使用拷贝的互斥量是不确定的。可以拷贝指向互斥量的指针，这样就可以使多个函数或线程共享互斥量来实现同步。

    大部分实践你可能在“文件范围”内，即函数体外，声明互斥量为外部或静态存储类型。如果有其他文件使用互斥量，则将其声明为外部类型；如果尽在本文件内使用，则将其声明为静态类型。

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
