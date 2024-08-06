# C 语言基础

## C 指针

### 关于指针和指针变量

变量是用来存在数据的，指针是内存的地址，指针变量就是用来存放内存地址的变量

```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int age = 17;
    int *p = &age;

    printf("age的值:%d\n", age);
    printf("指针p的值:%d\n", *p);
  
    printf("age的地址:%p\n", &age);
    printf("指针p指向的地址:%p\n", p);
    printf("指针p自身的地址:%p\n", &p);
    return 0;
}
```

输出如下：

```shell
age的值:17
指针p的值:17
age的地址:0x7fff0f8cb0fc
指针p指向的地址:0x7fff0f8cb0fc
指针p自身的地址:0x7fff0f8cb100
```

### 指针图解

[![image.png](https://i.postimg.cc/2SQggSsB/image.png)](https://postimg.cc/68QHvt59)

### 关于内存

| 变量名 | 内存地址       | 值             |
| ------ | -------------- | -------------- |
| age    | 0x7fff0f8cb0fc | 17             |
| p      | 0x7fff0f8cb100 | 0x7fff0f8cb0fc |

整形指针变量p，存储的值是整型变量age的内存地址。

符号&是取地址符，那么&age = 0x7fff0f8cb0fc；

由于指针变量本身也是一个变量，所以p也有一个自己的地址，对其取地址的操作是&p=0x7fff0f8cb100；

而*p则是获取指针变量p存储的值对应内存地址中存储的值。

## 结构体

### 结构体的声明

结构体(struct)在C变成中经常用到，可以简单理解为面向对象编程语言中的只有属性没有方法的对象。结构体声明描述了一个对象的组成布局。

声明一个用于描述学生的struct

```c
struct Student
{
    char name[64];
    int age;
    int class;
};
```

其中student称为**结构体标记**。可以将struct student理解为一种类似int的变量类型。就可以使用这个结构体了。

### struct的初始化

#### 一次性初始化所有属性

```c
struct Student stu1 = {"admin", 23, 1};
```
**注意：**
大括号里值的顺序，要与声明结构体的属性保持一致。

#### 先声明再分别初始化
```c
struct Student stu2;
strcpy(stu2.name, "Alice");
stu2.age = 14;
stu2.class = 2;
```

#### 关于strcpy函数
strcpy函数来自C标准库<string.h>，使用时不要忘记include。由于C语言中没有类似String的变量类型，我们想要使用字符串一般使用字符数组来表示，但是字符数组不能被字符串直接赋值，而strcpy函数可以解决此类问题。

#### struct的属性声明和变量声明可以合并
```c
struct Student
{
    char name[64];
    int age;
    int class;
}stu3;
```

#### 初始化也能写在一起
```c
struct Student
{
    char name[64];
    int age;
    int class;
}stu3={"ausion",13,3};
```
也可以是多个变量一起
```c
struct Student
{
    char name[64];
    int age;
    int class;
}stu3={"ausion",13,3};
stu4={"Rose",14,4};
```

#### 结构的标记可以省略

加入只需要一个 struct student 的变量stu, 那么可以省略结构体标记student
```c
struct
{
    char name[64];
    int age;
    int class;
}stu3;
```

### struct的使用
定义结构体变量，访问成员时就用 **.**
定义结构体指针，访问成员时就用 **->**

```c
#include <stdio.h>
#include <string.h>

struct Student
{
    char name[64];
    int age;
    int class;
} stu3;

int main(int argc, char const *argv[])
{
    // 初始化成员变量
    strcpy(stu3.name, "Tom");
    stu3.age = 11;
    stu3.class = 3;

    // 初始化结构体指针
    struct Student *stu_ptr = &stu3;
    
    // 使用 . 访问结构体变量成员
    printf("stu3.name:%s\n", stu3.name);
    printf("stu3.age:%d\n", stu3.age);
    printf("stu3.class:%d\n", stu3.class);
    
    // 使用 -> 访问
    printf("stu3.age:%d\n", stu_ptr->age);

    printf("-----------------------------------------\n");
    return 0;
}
```

### 使用typedef
比如有这样一个结构体
```c
struct Student
{
    char name[64];
    int age;
    int class;
};
```
如上述，使用此结构体时，我们这样声明变量 *struct Student stu*。
可以用 **typedef** 关键字为 struct Student 指定一个别名：
```c
typedef sturuct Student s;
```
上面的代码，我们将 *struct Student* 指定为别名 *s*，那么 *s Stu;* 就等价于 *sturuct Student stu;*，显然更加简洁和方便。
我们可以在定义结构体时就加上 **typedef** 关键字，就可以将上面的代码合并为：
```c
typedef struct Student
{
    char name[64];
    int age;
    int class;
}s;
```

## 内存管理

### 为什么是malloc

学习c语言时，通常只是简单的使用int,float之类来声明变量。像这种变量，通常存放在栈区（stack），由编译器自动分配释放，存放函数的参数值，局部变量等值。而在实际编程中，需要足够的内存来保证程序的存储需求，由于stack区内存相对较小，所以我们需要使用malloc与free等函数从堆区（heap）动态申请与释放内存，堆区要比栈区大的多。


### malloc与内存

所有程序都需要预留足够的内存来存储程序使用的数据，malloc函数能够在程序运行时分配更多的内存。malloc函数会找到空概念的内存块并返回内存块的首地址，而char表示1字节，malloc()的返回类型被定为指向char类型的指针。
```c
void *malloc(unsigned num_bytes);
```
一个指向void的指针相当于是一个通用类型，所以通常我们需要什么类型的指针应进行强制转换即可，分配失败则返回空指针。

### 善用size_t类型

我们一般用 *size_t* 类型来定义变量进而存储 *sizeof* 函数返回的值。
```c
size_t size = sizeof(int);
```

### malloc的使用

malloc函数位与<stdlib.h>

#### 为简单变量申请内存

```c
int *p1 = (int *)malloc(sizeof(int));
*p1 = 100;
printf("*p1=%d\n", *p1);
printf("&p1=%p\n", &p1);
```

#### 为结构体申请内存

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student
{
    char name[64];
    int age;
    int class;
} stu3;

int main(int argc, char const *argv[])
{
    struct Student *stu_ptr1 = (struct Student *)malloc(sizeof(struct Student));
    char *name = (char *)malloc(sizeof(char) * 64);
    printf("*name=%d\n", *name);
    printf("&name=%p\n", &name);
    strcpy(stu_ptr1->name, "Admin");
    stu_ptr1->age = 13;
    stu_ptr1->class = 3;
    printf("name:%s\n", stu_ptr1->name);
    printf("age:%d\n", stu_ptr1->age);
    printf("class:%d\n", stu_ptr1->class);

    free(name);
    free(stu_ptr1);

    return 0;
}

```

#### free的使用

一般来说，内存错误是C编程中常见的问题，需要养成良好的习惯。通常malloc和free一起使用，这是因为malloc申请内存后无法主动释放，需要使用free函数手动释放。

```c
free(stu_ptr1);
```

#### AddressSanitizer的使用
C编程时，一些内存错误可能会在运行时出现错误而终止，也可能会有内存错误的情况，而表面却能正常使用。
AddressSanitizer是一款用于内存诊断的工具，可以配合gcc使用方便检测越界，非法访问等内存错误。
gcc编译加上这些参数即可：
```c
gcc -fsanitize=address -fno-omit-frame-pointer -g main.c
```

# 数据结构

## 单链表

### 单链表的节点

[![image.png](https://i.postimg.cc/gknCRpS6/image.png)](https://postimg.cc/6yxbJkN9)

如图所示，单链表的节点分为数据域和指针域，可以将他们视为一个整体，称之为 **节点**，稍后我们会用结构体来表示节点。

**数据域** 存放数据的地方
**指针域** 存放指针变量的地方，指针指向下一个节点的地址


### 单链表的表示

单链表时线性表的 **链式** 表示和实现。把节点连起来，就形成了单链表。

[![image.png](https://i.postimg.cc/wBmJs1Jb/image.png)](https://postimg.cc/cKd6p4FQ)

### 定义表示节点的结构体

```c
struct Node{
    // 后继节点
    struct Node *next;
    // 值
    int data;
};
```

首先我们定义了一个结构体，结构体的标记为 **Node** 。其次他有两个属性，一个是int类型的data，也就是上述提到的数据域。还有一个是指针域，也就是 **sruct Node \*next**, 指针域是存放指针变量的，这个变量名叫 **next**, 又因为这个指针是指向下一个节点的地址，换句话说，这个指针指向的是一个我们定义的用来表示节点的结构体。所以这个指针变量的类型为 **struct Node**，星号表示他是指针变量，所以合起来就是 **struct Node *next**。最后为了方便，我们可以使用 **typedef** 关键字为 **struct Node** 取一个别名。

```c
typdedef struct Node{
    // 后继节点
    struct Node;
    // 值
    int data;
}list;
```

这样，后面的代码书写中，**list** 就等价于 **struct Node**了。比如我们使用这个结构体创建一个新的节点，**list *new_node** 就等价于 **struct Node *new_node**。

### 单链表的创建

```c
list *create_list(){
    // 创建一个新的节点，由于使用typedef关键字，此处node *head与struct Node *head等价
    list *head = (list *)malloc(sizeof(list));
    if(head == NULL) return NULL;
    // 初始化节点
    head->data = 0;// 头节点数据域，我们用来表示链表长度
    head->next = NULL;
    return head;
}
```

[![image.png](https://i.postimg.cc/90X7HksG/image.png)](https://postimg.cc/0M3QpVkQ)

此函数会创建一个单链表，并返回头指针。
头指针是指向头节点地址的指针，和节点中指向下一个节点的指针是相同的类型。
首先，用 **malloc** 函数开辟了一块 **list** 大小的内存，并返回了指向该内存块首地址的指针，同时将此指针赋值给头指针变量。

### 为什么设置头节点

头节点的数据域一般无意义，这里为了方便后面的插入和删除操作而设置，头节点并非链表所必须。
头节点后面的第一个元素节点称为首节点。

### 单链表的插入

试想如下情况，一个新的节点 n，要插入到 x节点后。

[![image.png](https://i.postimg.cc/rpcyHrB4/image.png)](https://postimg.cc/NKJw95fG)

图中虚线表示断开连接，下同。
示意代码如下：
```c
n->next = x->next;
x->next = n;
```

完整版插入函数：
插入函数接受十三个参数，被插入节点的链表的指针head, 新节点的数据data,和要插入的位置pos;

```c
list * list_insert_node(list *head, int data, int pos)
{
    int i;
    list *curr = head;

    // 如果要插入的位置比链表长，则属于非法操作
    if (pos > curr->data) return NULL;

    // 创建一个节点，并初始化
    list *node = (list *)malloc(sizeof(list));
    if(node == NULL) return NULL;
    node->data = data;
    node->next = NULL;

    // 遍历链表，找到要插入的位置
    for(i = 0;i<pos;i++>)
    {
        curr = curr.next;
    }

    // 插入
    node->next = curr.next;
    curr.next = node;

    // 链表长度加1
    heat->data++;
    return head;
}

```

### 单链表的遍历

```c
// 打印链表数据，不包括头节点的数据
void print_list(list *head)
{
    list *curr = head->next;
    while(curr)
    {
        printf("%d\n",curr->data);
        curr = curr->next;
    }
    printf("\n");
}
```

### 完整代码

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    int data;
} list;

list *create_list() {
    // 创建一个新的节点，由于使用typedef关键字，此处node *head与struct Node *head等价
    list *head = (list *)malloc(sizeof(list));
    if (head == NULL) {
        return NULL;
    }
    // 初始化节点
    head->data = 0; // 头节点数据域，我们用来表示链表长度
    head->next = NULL;
    return head;
}

list *list_insert_node(list *head, int data, int pos) {
    int i;
    list *curr = head;

    // 如果要插入的位置比链表长，则属于非法操作
    if (pos > curr->data) {
        return NULL;
    }

    // 创建一个节点，并初始化
    list *node = (list *)malloc(sizeof(list));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;

    // 遍历链表，找到要插入的位置
    for (i = 0; i < pos; i++) {
        curr = curr->next;
    }

    // 插入
    node->next = curr->next;
    curr->next = node;

    // 链表长度加1
    head->data++;

    return head;
}

// 打印链表数据，不包括头节点的数据
void print_list(list *head) {
    list *curr = head->next;
    while (curr) {
        printf("%d \t", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// 单链表的删除
list *list_delete_data(list *head, int pos) {
    list *curr = head;
    // 如果要删除的位置比链表长，则属于非法操作
    if (pos >= curr->data) {
        return NULL;
    }

    // 遍历链表，找到要删除节点的前一个指针
    for (int i = 0; i < pos; i++) {
        curr = curr->next;
    }

    // 临时记录将被删除的节点
    list *temp = curr->next;
    // 删除节点
    curr->next = curr->next->next;

    // 释放掉被删除节点后的内容
    free(temp);
    head->data--;
    return head;
}

int main() {
    list *l = create_list();
    for (int i = 0; i < 5; i++) {
        list_insert_node(l, i * 10 + i, 0);
        print_list(l);
    }

    list_delete_data(l, 4);
    printf("+++++++++++++++\n");
    print_list(l);
    
    list_delete_data(l, 0);
    printf("+++++++++++++++\n");
    print_list(l);

    // 释放链表
    while (l != NULL) {
        list *temp = l;
        l = l->next;
        free(temp);
    }
    return 0;
}
```

## 链栈

### 什么是栈

栈(stack)是一种后进先出（Last In First Out,LIFO）的线性表，表尾有特殊含义，称为栈顶（top）。

### 栈的操作

栈最常用的操作有2中，一种是在表尾插入元素的操作，称为入栈（push）,也叫压栈；另一种是在表尾删除元素的操作称为出栈（pop）,也叫弹栈。

[![image.png](https://i.postimg.cc/d3PyxMVr/image.png)](https://postimg.cc/hzsvX5xt)

### 栈的表示

栈可以用数组表示即顺序栈，也可以用链表表示，叫做链式栈，简称链栈（本文主要讨论对象）。
单链表可以在表头、表尾或其他任意合法位置插入元素，如果只能在单链表的表尾插入和删除元素，那么就可以将其视为链栈。
因此，在单链表的基础上，我们再维护一个top指针即可。

[![image.png](https://i.postimg.cc/hvvtsp9T/image.png)](https://postimg.cc/Cny0LCrx)

**注意**
图中每个节点的指针域 **next** 指针指向下一个节点，而非下一个节点的指针域

### 栈的节点定义与top指针

定义表示链栈节点的结构体
```c
typedef struct stack_node
{
    struct stack_node *next;
    void *data;
}stack_node;
```

定义表示链栈的结构体
```c
typedef struct stack
{
    struct stack_node *top;
    int length; // 表示栈的高度
}stack;
```

注意，**top** 指针指向的是一个表示栈的节点的结构体。

### 函数清单

下面是用于操作栈的函数名及其作用域复杂度
| 函数 | 作用       | 算法复杂度             |
| ------ | -------------- | -------------- |
| stack_create    | 创建新的链式栈 | O(1)             |
| stack_release    | 释放栈，以及栈中的节点 | O(1)             |
| stack_push    | 入栈 | O(1)             |
| stack_pop    | 出栈 | O(1)             |
| stack_empty    | 释放栈中所有的节点，但不释放栈本身 | O(N)             |


### 创建栈
```c
/* 创建栈 */
stack *stack_create()
{
    stack *stack = (struct stack *)malloc(sizeof(struct stack));
    /* 等价写法
    stack *s = (stack*) malloc(sizeof(stack))*/

    if (stack == NULL)
    {
        return NULL;
    }
    /* 初始化 */
    stack->length = 0;
    stack->top = NULL;
    return stack;
}
```

### 入栈
```c
/* 入栈 */
stack *stack_push(stack *stack, void *data)
{
    /* 创建一个节点 */
    stack_node *node = (struct stack_node *)malloc(sizeof(struct stack_node));

    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;

    // 插入
    node->next = stack->top;
    stack->top = node;

    stack->length++;
    return stack;
}
```
### 出栈
```c
/* 出栈 */
void *stack_pop(stack *stack)
{
    /* 临时保存栈顶元素 */
    stack_node *curr = stack->top;
    if (curr == NULL)
    {
        return NULL;
    }

    void *data = curr->data;
    stack->top = stack->top->next;

    free(curr);
    stack->length--;
    return data;
}
```
### 清空栈
```c
/* 清空栈 清空栈中所有元素，但不释放栈本身 */
void stack_empty(stack *stack)
{
    int length = stack->length;
    stack_node *curr, *next;
    curr = stack->top;

    // 根据栈的高度决定删除节点的次数
    while (length--)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    stack->length = 0;
    stack->top = NULL;
}
```
### 清除栈
```c
/* 清除栈 清空栈中所有元素并删除栈 */
void stack_release(stack *stack)
{
    stack_empty(stack);
    free(stack);
}
```

### 完整代码
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_node
{
    struct stack_node *next;
    void *data;
} stack_node;

typedef struct stack
{
    struct stack_node *top;
    int length; // 表示栈的高度
} stack;

/* 创建栈 */
stack *stack_create()
{
    stack *stack = (struct stack *)malloc(sizeof(struct stack));
    /* 等价写法
    stack *s = (stack*) malloc(sizeof(stack))*/

    if (stack == NULL)
    {
        return NULL;
    }
    /* 初始化 */
    stack->length = 0;
    stack->top = NULL;
    return stack;
}

/* 入栈 */
stack *stack_push(stack *stack, void *data)
{
    /* 创建一个节点 */
    stack_node *node = (struct stack_node *)malloc(sizeof(struct stack_node));

    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;

    // 插入
    node->next = stack->top;
    stack->top = node;

    stack->length++;
    return stack;
}

/* 出栈 */
void *stack_pop(stack *stack)
{
    /* 临时保存栈顶元素 */
    stack_node *curr = stack->top;
    if (curr == NULL)
    {
        return NULL;
    }

    void *data = curr->data;
    stack->top = stack->top->next;

    free(curr);
    stack->length--;
    return data;
}

/* 清空栈 清空栈中所有元素，但不释放栈本身 */
void stack_empty(stack *stack)
{
    int length = stack->length;
    stack_node *curr, *next;
    curr = stack->top;

    // 根据栈的高度决定删除节点的次数
    while (length--)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    stack->length = 0;
    stack->top = NULL;
}

/* 清除栈 清空栈中所有元素并删除栈 */
void stack_release(stack *stack)
{
    stack_empty(stack);
    free(stack);
}

int main()
{
    char a = 'a';
    char b = 'b';
    char c = 'c';

    // 创建一个栈
    stack *stack = stack_create();

    printf("stack_pop: %p\n", stack_pop(stack));

    printf("====================\n");
    // 入栈
    stack_push(stack, &a);
    stack_push(stack, &b);
    stack_push(stack, &c);

    // 出栈
    while (stack->length > 0)
    {
        char *pop = (char *)stack_pop(stack);
        printf("stack_pop: %c %p\n", *pop, pop);
    }
    printf("====================\n");

    // 入栈
    stack_push(stack, &a);
    
    char *pop = (char *)stack_pop(stack);
    printf("pop: %c %p\n", *pop, pop);

    stack_empty(stack);

    // 释放栈
    stack_release(stack);

    return 0;
}

```

**实际结果**

```sh
stack_pop: (nil)
====================
stack_pop: c 0x7fff349b3c60
stack_pop: b 0x7fff349b3c50
stack_pop: a 0x7fff349b3c40
====================
pop: a 0x7fff349b3c40
```

## 队列

### 什么是队列

队列（queue）是一种先进先出（First In First Out，FIFO）的线性表

[![image.png](https://i.postimg.cc/MKh5SQc7/image.png)](https://postimg.cc/tYNWd7NJ)

### 队列的表示

队列也有顺序和链式两种表示方法。通用，我们可以将链式队列裂解为一种特殊的链表，只运行在表头删除，在表尾插入。
```c

// 队列节点
typedef struct queue_node
{
    // 后继节点
    struct queue_node *next;
    // 值
    void *data;
}queue_node;

// 队列本身
typedef struct queue
{
    // 队头
    struct queue_node *head;
    // 队尾
    struct queue_node *tail;
    // 队列长度
    int length;
}queue;
```

### 队列的操作
通常来说，队列常用的操作也是插入和删除两种。将执行删除的一端称为队头（head）,执行插入操作的一端称为队尾（tail）。

### 函数清单

|函数|作用|算法复杂度|
|-|-|-|
|queue_create|创建新队列|O(1)|
|queue_push|入队|O(1)|
|queue_pull|出队|O(1)|
|queue_empty|释放队列中的节点（头节点除外），但不释放队列本身|O(N)|
|queue_release|释放队列，以及队列中的节点|O(N)|

### 创建新队列

```c

// 创建队列
queue *queue_create()
{
    // 创建一个队列
    queue *queue = (struct queue *)malloc(sizeof(struct queue));

    // 为了方便操作，队列默认创建一个队列节点
    queue_node *node = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (queue == NULL || node == NULL)
    {
        return NULL;
    }
    node->data = NULL;
    node->next = NULL;

    // 初始化队列
    queue->head = queue->tail = node;
    queue->length = 0;
}
```
在创建新队列是，首先创建队列本身，接着，创建一个队列节点（头节点），并将队列的head 和 tail指针都指向这个节点。最后队列的长度设置尾0。

[![image.png](https://i.postimg.cc/85tk3CQ2/image.png)](https://postimg.cc/S2YpYkKd)

### 入队

```c

// 入队
queue *queue_push(queue *queue, void *data)
{
    // 创建一个节点
    queue_node *node = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;

    // 在队尾插入元素
    queue->tail->next = node;
    queue->tail = queue->tail->next;

    queue->length++;
    return queue;
}
```
在有元素需要入队的时候，执行在表尾的插入操作。
首先创建一个新的节点，接着让最后一个节点，即队尾指针tail指向的节点next指针指向新节点，然后，队尾指针tail也指向新的节点。最后，队列长度自增1。

[![image.png](https://i.postimg.cc/xjzvbkHx/image.png)](https://postimg.cc/xq9Jw16M)

### 出队
```c
// 出队
void *queue_pull(queue *queue)
{
    queue_node *curr = queue->head->next;

    // 判断队列中是否有数据
    if (curr == NULL)
    {
        return NULL;
    }

    void *data = curr->data;

    queue->head->next = curr->next;

    // 判断队列中除头节点外，是否只有一个节点，避免尾指针丢失
    if (queue->tail = curr)
    {
        queue->tail = queue->head;
    }
    free(curr);
    queue->length--;
    return data;
}
```
有元素出队时，首先判断队列是否有数据，如果没有则返回NULL，如果有则返回头节点下一个节点的数据。接着，判断队列中除头节点外，是否只有一个节点。如果只有一个节点，那么下一步是否节点的内存是，tail指针将会被一同释放，进而造成尾指针的丢失。
最后释放出队的节点内存，队列长度自减1。

[![image.png](https://i.postimg.cc/hvVM8sys/image.png)](https://postimg.cc/GThkdF1T)

### 清空队列
```c
// 清空队列
void queue_empty(queue *queue)
{
    int length = queue->length;
    queue_node *curr, *next;

    // 注意这里不释放节点
    curr = queue->head->next;
    while (length--)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }

    queue->head->next = NULL;
    queue->head->data = NULL;
    queue->tail = queue->head;
    queue->length = 0;
}
```
释放队列的所有数据系欸但，但不释放头节点，所有循环从head->next开始。因为head->next被free过，所以再次设置为NULL。
最后，设置队列长度为0，释放完毕。

### 清除队列

```c

// 清空队列
void queue_empty(queue *queue)
{
    int length = queue->length;
    queue_node *curr, *next;

    // 注意这里不释放节点
    curr = queue->head->next;
    while (length--)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }

    queue->head->next = NULL;
    queue->head->data = NULL;
    queue->tail = queue->head;
    queue->length = 0;
}
```

### 完整代码

```c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 队列节点
typedef struct queue_node
{
    /* 后继节点 */
    struct queue_node *next;
    /* 值 */
    void *data;
} queue_node;

// 队列本身
typedef struct queue
{
    // 队头
    struct queue_node *head;
    // 队尾
    struct queue_node *tail;
    // 队列长度
    int length;
} queue;

// 创建队列
queue *queue_create()
{
    // 创建一个队列
    queue *queue = (struct queue *)malloc(sizeof(struct queue));

    // 为了方便操作，队列默认创建一个队列节点
    queue_node *node = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (queue == NULL || node == NULL)
    {
        return NULL;
    }
    node->data = NULL;
    node->next = NULL;

    // 初始化队列
    queue->head = queue->tail = node;
    queue->length = 0;
    return queue;
}

// 入队
queue *queue_push(queue *queue, void *data)
{
    // 创建一个节点
    queue_node *node = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;

    // 在队尾插入元素
    queue->tail->next = node;
    queue->tail = queue->tail->next;

    queue->length++;
    return queue;
}

// 出队
void *queue_pull(queue *queue)
{
    queue_node *curr = queue->head->next;

    // 判断队列中是否有数据
    if (curr == NULL)
    {
        return NULL;
    }

    void *data = curr->data;

    queue->head->next = curr->next;

    // 判断队列中除头节点外，是否只有一个节点，避免尾指针丢失
    if (queue->tail == curr)
    {
        queue->tail = queue->head;
    }
    free(curr);
    queue->length--;
    return data;
}

// 清空队列
void queue_empty(queue *queue)
{
    int length = queue->length;
    queue_node *curr, *next;

    // 注意这里不释放节点
    curr = queue->head->next;
    while (length--)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }

    queue->head->next = NULL;
    queue->head->data = NULL;
    queue->tail = queue->head;
    queue->length = 0;
}

// 释放队列，包括队列中节点
void queue_release(queue *queue)
{
    queue_empty(queue);
    // 注意头节点也要释放
    free(queue->head);
    free(queue);
}
int main()
{
    char a = 'a';
    char b = 'b';
    char c = 'c';

    queue *queue = queue_create();
    printf("pull:%p\n", queue_pull(queue));

    printf("====================\n");

    queue_push(queue, &a);
    queue_push(queue, &b);
    queue_push(queue, &c);

    while (queue->length)
    {
        char *temp = (char *)queue_pull(queue);
        printf("queue_pull:%c %p\n", *temp, temp);
    }
    printf("====================\n");

    queue_push(queue, &c);
    queue_push(queue, &c);

    // 释放队列中节点
    queue_empty(queue);
    printf("pull:%p\n", queue_pull(queue));

    // 释放队列
    queue_release(queue);

    return 0;
}
```


## 双链表

## 哈希表

## 二叉树

## 二叉搜索树

## 平衡二叉树
