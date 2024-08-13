# 硬件结构

## CPU是如何执行程序的

### 图灵机的工作方式

1. 纸带 》 内存
2. 纸带中连续的格子 》内存中的数据或程序
3. 读写头 》 读取纸袋上任意格子的字符或把字符写入到纸带的格子
4. 读写头上的部件
   + 存储单元 》 存放数据
   + 控制单元 》 识别字符是数据还是指令，以及控制程序的流程
   + 运算单元 》 执行运算指令
5. 1+2的执行过程

[![image.png](https://i.postimg.cc/qRYhyg9P/image.png)](https://postimg.cc/8JRzVkk4)

+ 首先用**读写头**把**【1、2、+】**这3个字符分别写入到纸带的3个格子上

1. **读写头**读入**1**到**存储设备**，这个存储设备称为图灵机的**状态**
2. **读写头向右移动一格**，用同样的方式把**2**读入到图灵机的**状态**，于是现在图灵机的状态中存储着2个连续的数字1、2
3. **读写头再向右移动一格**，碰到+，将**\+**号传输给**控制单元**，控制单元发现是+号不是数字，所有没有存入到状态，因为+号是运算符指令，作用是加和目前的状态，于是通知**运算单元**工作。运算单元收到要加和状态中的值的通知后，就会**把状态中的1和2读入并计算，再将计算的结果3存放到状态中**；
4. 最后，**运算单元**将**结果**返回给**控制单元**，控制单元将结果传输给**读写头**，读写头向右移动，把结果**3**写入到纸带的**格子**中；
5. 通过图灵机计算1+2的过程，发现图灵机的主要功能是读取纸带（内存）格子的内容（数据） ，然后交给控制单元识别字符是数字还是运算符指令，如果是数字则存入到图灵机状态中（存储单元），如果是运算符，则通知运算单元读取状态中的数值进行计算，计算结果最终返回给读写头，读写头把结果写入到纸带的格子中。

### 冯诺依曼模型

[![Snipaste-2023-01-30-fnym.png](https://i.postimg.cc/65bZyTs6/Snipaste-2023-01-30-fnym.png)](https://postimg.cc/D8s0NvyR)

1. 中央处理器（CPU）

   > 中央处理器就是我们常说的CPU，32位和64位CPU最主要区别在于一次能计算多少字节数据：
   >

   + 32位CPU一次可以计算4个字节（1字节等于8位,4x8bit=32bit）；
   + 64位CPU一次可以计算8个字节（1字节等于8位,8x8bit=64bit）；
   + 这里的32位和64位，通常称为CPU的位宽。
   + 之所以CPU这样设计，是为了能计算更大的数值，如果是8位的CPU，那么一次只能计算1个字节（2^8）0-255范围内的数值，这样就无法一次完成计算10000*500，于是为了能一次计算大数的运算，CPU需要支持多个byte一起计算，所以CPU位宽越大，可以计算的数值就越大，比如说32位CPU能计算的最大整数为4294967295(2^32)
   + CPU内部还有一些组件，常见的有寄存器、控制单元和逻辑运算单元。
     + 控制单元，控制CPU工作
     + 逻辑运算单元，计算
     + 寄存器，根据种类不同划分不同的功能，主要作用是存储计算时的数据（因为内存离CPU太远，寄存器就在CPU里，紧挨控制单元和逻辑运算单元，计算时速度更快）
       + 通用寄存器，用来存放需要进行运算的**数据**，比如需要进行加和运算的两个数据。
       + 程序计数器，用来存储CPU要执行**下一条指令所在的内存地址**，注意不是存储了下一条要执行的指令，此时指令还在内存中，程序计数器只是存储了下一条指令的地址。
       + 指令寄存器，用来存放**程序计数器指向的指令**，也就是指令本身，指令被执行完之前，指令都存储在这里。
2. 内存

   > 程序和数据都是存储在内存，存储区域是线性的
   >

   + 数据存储单位是一个**二进制位（bit）**，即0或1，最小的存储单位是**字节（byte）**，**1字节等于8位**
   + **内存的地址是从0开始编号**的，然后**自增排列**，**最后一个地址为内存总字节数-1**，这种结构好似我们程序里的数组，所以内存的读写任何一个数据的速度都是一样的。
3. 输入设备

   > 输入设备向计算机输入数据，计算机经过计算后，把数据输出给输出设备。期间，如果输入设备是键盘，按下按键时是需要和CPU进行交互的，这时就需要用到控制总线了。
   >
4. 输出设备
5. 总线

   > 总线是用于CPU和内存以及其他设备之间的通信，总线可分为3中：
   >

   + 地址总线，用于指定CPU将要操作的内存地址；
   + 数据总线，用于读写内存的数据；
   + 控制总线，用于发送和接收信号，比如中断、设备复位等信号，CPU收到信号后自然进行响应，这时也需要控制总线。
   + 当CPU要读取内存数据的时候，一般需要通过两个总线：
     + 首先通过**地址总线**来指定内存的地址；
     + 再通过**数据总线**来传输数据；

### 线路位宽与CPU位宽

> 数据是如何通过线路传输的呢？其实是通过操作电压，低电压表示0，高电压表示1。

+ 如果构造了高低高这样的信号，其实就是101二进制数据，十进制表示则是5，如果只有一条线路，就意味着每次只能传递1bit的数据，即0或1，那么传输101这个数据，就需要3次，这样效率非常低，这样一位一位传输的方式，称为**串行**，下一个bit必须等待上一个bit传输完成才能进行传输。如果想一次多传一些数据，增加线路即可，这是数据就可以**并行**传输。
+ 为了避免低效率的串行传输方式，**线路的位宽**最好一次能访问所有的内存地址。CPU想要操作的内存地址就需要地址总线，如果地址总线只有1条，那每次只能表示**0或1**两种情况，所以CPU一次只能操作2个内存地址，如果想要CPU操作**4G**的内存，那么就需要**32条地址总线**，因为**2^32=4G**。
+ CPU位宽最好不要小于线路位宽，比如32位CPU控制40位宽的地址总线和数据总线的话，工作起来就会非常复杂其麻烦，所以32位的CPU最好和32位宽的线路搭配，因为32位CPU一次最多只能操作32位宽的地址总线和数据总线。
+ 64位CPU性能并不一定比32位CPU高很多，很少应用需要算超过32位的数字，所以**如果计算数额不超过32位数字的情况下，32位和64位CPU之间没什么区别，只有当计算超过32位数字的情况下，64为的优势才能体现出来。
+ 32位CPU最大智能操作4GB内存，就算装了8GB内存条也没用。而64位CPU寻址范围很大，理论最大的寻址空间为2^64。

### 程序执行的基本过程

[![Snipaste-2023-01-30-CPU.png](https://i.postimg.cc/MH6nwFFt/Snipaste-2023-01-30-CPU.png)](https://postimg.cc/1ndmcJPN)

> CPU执行程序的过程如下

1. CPU读取**程序计数器**的值，这个值是指令的内存地址，然后CPU的**控制单元**操作**地址总线**指定需要访问的内存地址，接着通知内存设备准备数据，数据准备好后通过**数据总线**将指令数据传给CPU，CPU收到内存传来的数据后，将这个指令数据存入到**指令寄存器**。
2. CPU分析**指令寄存器**中的指令，确定指令的类型和参数，如果是**计算类型**的指令，就把指令交给**逻辑运算单元**运算；如果是**存储类型**的指令，则交由**控制单元**执行。
3. CPU执行完指令后，**程序计数器**的值自增，表示指向下一条指令。这个自增的大小，由CPU的位宽决定，比如**32位的CPU，指令是4个字节**，需要**4个内存地址**存放，因此**程序计数器**的值会**自增4**；
4. 总结：一个程序执行的时候，CPU会根据**程序计数器**里的**内存地址**，从**内存**里面把需要执行的**指令**读取到**指令寄存器**里面**执行**，然后**根据指令长度自增**，开始顺序**读取下一条指令**。

### a=1+2执行具体过程

> CPU不认识**a=1+2**这个字符串，这些字符串只是方便我们程序员认识，要想这段程序能跑起来，还需要包整个程序翻译成**汇编语言**的程序，这个过程称为**编译成汇编代码**。
> 针对汇编代码，我们还需要用汇编器翻译成机器码，这些机器码由0和1组成的机器语言，这一条条机器码，就是一条条的**计算机指令**，这个才是CPU能够真正认识的东西。

1. a=1+2在32位CPU的执行过程。程序编译过程中，编译器通过分析代码，发现1和2是数据，于是程序运行时，内存会有个专门的区域来存放这些数据，这个区域就是**数据段**。

   + 数据1被存到0x104位置；
   + 数据2被存到0x100位置；
     [![Snipaste-2023-01-30-14-58-01.png](https://i.postimg.cc/zDt1jfr3/Snipaste-2023-01-30-14-58-01.png)](https://postimg.cc/vDVj8bDd)
2. 编译器把a=1+2翻译成4条指令，存放到正文段中。如图，这4条指令被存到了0x200~0x20c

   + 0x200 的内容是 load 指令将0x100地址中的数据2装入到寄存器R0；
   + 0x204 的内容是 load 指令将0x104地址中的数据1装入到寄存器R1；
   + 0x208 的内容是 add 指令将寄存器R0和R1的数据相加，并把结果存放到寄存器R2；
   + 0x20C 的内容是 store 指令将R2中的数据存回数据段中的0x108地址中，这个地址也就是变量a内存中的地址；
3. 编译完成后，具体执行程序的时候，程序计数器会被设置为0x200地址，然后依此执行这4条指令。
4. 上面的例子中，(0x100,0x104,0x200,0x204,0x208,0x20C按4位增长，是因为在32位CPU下，一条指令占32位大小，4个字节，需要4个内存地址存放，因此间隔4)
5. 而数据的大小是根据你再程序中指定的变量类型，比如int类型的数据占4个字节，char类型的数据则占1个字节。

#### 指令

> 上⾯的例⼦中，图中指令的内容我写的是简易的汇编代码，⽬的是为了⽅便理解指令的具体内容，事实上指令的内容是⼀串⼆进制数字的机器码，每条指令都有对应的机器码，CPU 通过解析机器码来知道指令的
> 内容；不同的 CPU 有不同的指令集，也就是对应着不同的汇编语⾔和不同的机器码，接下来选⽤最简单的 MIPS指集，来看看机器码是如何⽣成的，这样也能明⽩⼆进制的机器码的具体含义。

+ MIPS的指令是一个32位的整数，高6位代表着操作码，表示这条指令是一条什么样的指令，剩下的26位不同指令类型所表示的内容也就不相同，主要有三种类型R、I和J。

[![image.png](https://i.postimg.cc/X7XWHjTH/image.png)](https://postimg.cc/YhcTjH2Y)

+ R指令，用在算术和逻辑操作，里面有读取和写入数据的寄存器地址。如果是逻辑位移操作，后面还有位移操作的**位移量**，而最后的**功能码**则是在前面的操作码不够的时候，扩展操作码来表示对应的具体指令的。
+ I指令，用在数据传输、条件分支等。这个类型的指令，就没有了位移量和操作码，也没有了第三个寄存器，而是把这三部分直接合并成了一个地址值或一个常数；
+ J指令，用在跳转，高6位之外的26位都是一个跳转后的地址；
+ 把**add 指令将寄存器R0和R1的数据相加，并把结果放入到R2**，翻译成机器码。

[![image.png](https://i.postimg.cc/26Dm2gW0/image.png)](https://postimg.cc/f3B6b2Bd)

> 加和运算add指令是属于R指令类型：

+ add 对应的MIPS指令里面的操作码是 000000，以及最末尾的功能码是100000，这些值是固定的，可参考MIPS指令集手册
+ rs 代表第一个寄存器R0的编号，即00000；
+ rt 代表第二个寄存器R1的编号，即00001；
+ rd 代表目标的临时寄存器R2的编号，即00010；
+ 因为不是位移操作，所以位移量是00000
+ 把上面这些数字拼在一起就是一条32位的MIPS加法指令了，那么用16进制表示的机器码则是0x00011020

> 编译器在编译程序的时候，会构造指令，这个过程叫做指令的编码。CPU执行程序的时候就会解析指令，这个过程叫做指令的界面。
> 现代⼤多数 CPU 都使⽤来流⽔线的⽅式来执⾏指令，所谓的流⽔线就是把⼀个任务拆分成多个⼩任务，于是⼀条指令通常分为 4 个阶段，称为 4 级流⽔线，如下图：

[![image.png](https://i.postimg.cc/c4fs8QbR/image.png)](https://postimg.cc/CzLy3fY5)

> 四个阶段的具体含义：

1. CPU通过程序计数器读取对应内存地址的指令，这个部分称为 **Fetch(取得指令)** ；
2. CPU对指令进行解码，这个部分称为 **Decode(指令译码)** ；
3. CPU执行指令，这个部分称为 **Execution(执行指令)** ；
4. CPU将计算结果存回寄存器或者将寄存器的值存入内存，这个部分称为 **Store(数据回写)** ；
5. 上面这4个阶段，我们称为指令周期（Instrution Cycle），CPU的工作就是一个周期接着一个周期，周而复始。

[![image.png](https://i.postimg.cc/WzL3Jj08/image.png)](https://postimg.cc/1nBPLkCV)

+ 取指令的阶段，我们的指令是存放在**存储器**里的， 实际上，通过程序计数器和指令寄存器取出指令的过程，是由**控制器**操作的；
+ 指令的译码过程，也是由**控制器**进行的；
+ 指令执行的过程，无论是进行算术操作、逻辑操作，还是进行数据传输、条件分支操作，都是由**算术逻辑单元**操作的，也就是由运算器处理的。但是如果是一个简单地无条件地址跳转，则是直接在**控制器**里面完成的，不需要用到运算器。

#### 指令的类型

> 指令从功能的角度划分，可以分为5大类：

1. 数据传输类型的指令，比如store/load 是寄存器与内存见数据传输的指令，mov是将一个内存地址的数据移动到另一个内存地址的指令；
2. 运算类型的指令，比如加减乘除、位运算、比较大小等等，他们最多只能储量两个寄存器中的数据；
3. 跳转类型的指令，通过修改程序计数器的值来达到跳转执行指令的过程，比如编程中常见的if-else、switch-case、函数调用等。
4. 信号类型的指令，比如发生中断的指令 trap;
5. 闲置类型的指令，比如指令nop，执行后CPU悔空转一个周期；

#### 指令的速度

> CPU的硬件参数都会有**GHz**这个参数，比如一个1GHz的CPU，指的是时钟频率是1G，代表着1秒会产生1G次数的脉冲信号，每一次脉冲信号高低电平的转换就是一个周期，称为时钟周期。
> 对于CPU来说，在一个时钟周期内，CPU仅能完成一个最基本的动作，时钟频率越高，时钟周期越短，工作速度越快；但是一个时钟周期内，大多数不一定能执行完一条指令。

+ 程序执行的时候，耗费的CPU时间少就说明程序是快的，对于**CPU执行时间**，我们可以拆解成**CPU时钟周期数（CPU Cycles）**和**时钟周期时间（Cpu Cycle Time）**的**乘积**。
+ 要想CPU跑的更快，可以缩短时钟周期时间，提升CPU主频，但是现在很难提升CPU主频，可以减少CPU时钟周期数提升性能。CPU时钟周期数可以拆解成指令数x每条指令的平均周期数（Cycles Per Instruction，简称CPI），于是**程序的CPU执行时间=指令数xCPIx时钟周期时间**。
+ 因此，想要程序跑得快，优化这三者即可：
  + 指令数，表示执行程序需要多少条指令，以及哪些指令。这个层面基本靠编译器优化，同样代码，在不同编译器，编译出来的计算机指令会有各种不同的表示方式。
  + 每条指令的平均时钟周期数CPI，表示一条指令需要多少个时钟周期数，现代大多数COU通过流水线技术（Pipline），让一条指令需要的CPU时钟周期数尽可能的少。
  + 时钟周期时间，计算机主频，取决于计算机硬件。有的CPU支持超频技术，打开超频意味着把CPU内部的时钟给调快，CPU速度变快，但可能散热压力变大，CPU容易崩溃。

### 总结

1. 64 位相⽐ 32 位 CPU 的优势在哪吗？64 位 CPU 的计算性能⼀定⽐ 32 位 CPU ⾼很多吗？

+ 64位可以一次计算超过32位的数字，而32位要通过多步执行，这样效率就没那么高，所以**只有运算大数字的时候，64位CPU的优势才能体现出来，否则和32位CPU的计算性能相差不大**。
+ 64位CPU可以寻址更大的内存空间（2^64）,32位CPU最大可以寻址（2^32），可以寻到4G，即使有8G内存，还是只能寻到4G。

2. 你知道软件的 32 位和 64 位之间的区别吗？再来 32 位的操作系统可以运⾏在 64 位的电脑上吗？64 位的操作系统可以运⾏在 32 位的电脑上吗？如果不⾏，原因是什么？

+ 64位和32位软件，实际上代表指令是64位还是32位的：
+ 32位指令在64位机器上执行，需要一套兼容机制就可以运行了，但是**64位指令在32位指令机器上运行就比较困难，因为32位寄存器存不下64位的指令**；
+ 操作系统实际也是程序，其代表意义就是操作系统中程序的指令是多少位，64位操作系统不能装在32机器上。
+ 总之，**硬件的64位和32位指的是CPU的位宽，软件的64位和32位指的是指令的位宽**。

## 存储金字塔

> 内存和硬盘都属于计算机的存储设备，断电后内存的数据会丢失，硬盘则不会，因为硬盘是持久化存储设备，同时也是一个I/O设备。

> CPU内部也有存储数据的组件，比如寄存器、CPU L1/L2/L3 Cache也都是属于存储设备，只不过存储数据非常小，但是因为靠近CPU核心，所以访问速度非常快，快过硬盘几个数量级别

> 机械硬盘、固态硬盘、内存这3个存储器到底和CPU L1/L2/L3 Cache相比速度差多少呢？

### 存储器的层次结构

> CPU比喻成人体的大脑，大脑正在思考的东西好比 **寄存器** ，处理速度最快，但是能存储的数据也是最少的；大脑中的记忆好比 **CPU Cache** ，中文称为CPU高速缓存，处理速度相对寄存器慢一点，但是能存储的数据也相对多一些；CPU Cache通常分为**L1、L2、L3**三层，其中L1 Cache通常分成数据缓存和指令缓存，L1是距离CPU最近的，因此比L2、L3的读写速度都快、存储空间都小，我们脑中的短期记忆好比L1 Cache，长期记忆好比L2、L3Cache。

[![image.png](https://i.postimg.cc/ZKMGFf1X/image.png)](https://postimg.cc/1fD7yKRK)

+ 存储器通常可以分为这几个级别：
  + 寄存器
  + CPU Cache
    + L1-Cache
    + L2-Cache
    + L3-Cache
  + 内存
  + SSD/HDD 硬盘

   [![image.png](https://i.postimg.cc/bw1mD38x/image.png)](https://postimg.cc/yDYm2hDx)

#### 寄存器

> 最靠近CPU的控制单元和逻辑计算单元的存储器，使用的材料速度最快，价格最贵，数量不多。

> 存储器的数量通常在几十到几百之间，每个寄存器可以用来存储一定的字节（byte）的数据。

+ 32位CPU中大多数寄存器可以存储4个字节；
+ 64位CPU中大多数寄存器可以存储8个字节；

   寄存器的访问速度非常快，一般要求在**半个CPU时钟周期**内完成读写，CPU时钟周期跟CPU主频相关，比如2GHz主频的CPU，他的时钟周期就是1/2G，也就是0.5ns。

#### CPU Cache

> CPU Cache用的是一种叫SRAM(Static Random-Access Memory,静态随机存储器)的芯片，之所以叫静态存储器，是因为只要有电，数据就可以保持存在，一旦断电，数据就会丢失。

> **SRAM里面，一个bit的数据，通常需要6个晶体管**，所以SRAM的存储密度不高，同样的物理空间下，能存储数据有限，不过因为SRAM的电路简单，所以访问速度非常快。

> CPU的高速缓存，通常可以分为L1、L2、L3这样的三层高速缓存，也称为一级缓存、二级缓存、三级缓存。

[![image.png](https://i.postimg.cc/zXDLRkhs/image.png)](https://postimg.cc/6TS6knYc)

##### L1 Cache

> L1 高速缓存的访问速度和寄存器一样块，通常只需要**2-4个时钟周期**，而大小在**几十KB到几百KB**不等。

   每个CPU核心都有一块属于自己的L1高速缓存，指令和数据在L1是分开存放的，所以L1高速缓存通常分成**指令缓存**和**数据缓存**。

```sh
   # 查看CPU信息
   # less /proc/cpuinfo |grep model
    model           : 85
    model name      : Intel(R) Xeon(R) Platinum 8255C CPU @ 2.50GHz
    model           : 85
    model name      : Intel(R) Xeon(R) Platinum 8255C CPU @ 2.50GHz
    # 
    # cat  /proc/cpuinfo
    processor       : 0
    vendor_id       : GenuineIntel
    cpu family      : 6
    model           : 85
    model name      : Intel(R) Xeon(R) Platinum 8255C CPU @ 2.50GHz
    stepping        : 5
    microcode       : 0x1
    cpu MHz         : 2494.140
    cache size      : 36608 KB
    physical id     : 0
    siblings        : 2
    core id         : 0
    cpu cores       : 2
    apicid          : 0
    initial apicid  : 0
    fpu             : yes
    fpu_exception   : yes
    cpuid level     : 13
    wp              : yes
    flags           : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc rep_good nopl cpuid tsc_known_freq pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch invpcid_single pti fsgsbase bmi1 hle avx2 smep bmi2 erms invpcid rtm mpx avx512f avx512dq rdseed adx smap clflushopt clwb avx512cd avx512bw avx512vl xsaveopt xsavec xgetbv1 arat avx512_vnni
    bugs            : cpu_meltdown spectre_v1 spectre_v2 spec_store_bypass l1tf mds swapgs taa itlb_multihit
    bogomips        : 4988.28
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 46 bits physical, 48 bits virtual
    power management:

    processor       : 1
    vendor_id       : GenuineIntel
    cpu family      : 6
    model           : 85
    model name      : Intel(R) Xeon(R) Platinum 8255C CPU @ 2.50GHz
    stepping        : 5
    microcode       : 0x1
    cpu MHz         : 2494.140
    cache size      : 36608 KB
    physical id     : 0
    siblings        : 2
    core id         : 1
    cpu cores       : 2
    apicid          : 1
    initial apicid  : 1
    fpu             : yes
    fpu_exception   : yes
    cpuid level     : 13
    wp              : yes
    flags           : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc rep_good nopl cpuid tsc_known_freq pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch invpcid_single pti fsgsbase bmi1 hle avx2 smep bmi2 erms invpcid rtm mpx avx512f avx512dq rdseed adx smap clflushopt clwb avx512cd avx512bw avx512vl xsaveopt xsavec xgetbv1 arat avx512_vnni
    bugs            : cpu_meltdown spectre_v1 spectre_v2 spec_store_bypass l1tf mds swapgs taa itlb_multihit
    bogomips        : 4988.28
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 46 bits physical, 48 bits virtual
    power management:

    # 
```

   在Linux系统可以通过这条命令查看CPU里面的L1 Cache**数据缓存**的容量大小：

```sh
   # cat /sys/devices/system/cpu/cpu0/cache/index0/size
   32K
```

   查看L1 Cache**指令缓存**的容量大小

```sh
   # cat /sys/devices/system/cpu/cpu0/cache/index1/size
   32K
```

##### L2 Cache

> L2 高速缓存同样每个CPU核心都有，但是L2高速缓存位置比L1高速缓存距离CPU核心更远，它大小比L1高速缓存更大，CPU型号不同大小也就不同，通常大小在**几百KB到几MB**不等，访问速度更慢，速度在**10-20个时钟周期**。

   在Linux系统，我们可以通过这条命令，查看CPU⾥的L2 Cache的容量⼤⼩：

```sh
    # cat /sys/devices/system/cpu/cpu0/cache/index2/size
    4096K
```

##### L3 Cache

> L3高速缓存通常是**多个CPU核心共用**的，位置比L2高速缓存距离CPU核心更远，大小也会更大些，通常大小在**几MB到几十MB**不等，具体值根据CPU型号而定。访问速度在**20-60个时钟周期**。

   在Linux系统，我们可以通过这条命令，查看CPU⾥的L3 Cache的容量⼤⼩：

```sh
    # cat /sys/devices/system/cpu/cpu0/cache/index3/size
    36608K
```

#### 内存

> 内存使用的芯片和CPU Cache有所不同，它使用的是一种叫做DRAM(Dynamic Random Access Memory,动态随机存取存储器的芯片)

   相比SRAM，DRAM的密度更高，功耗更低，有更大的容量，而且造价比SRAM芯片便宜很多。

   **DRAM存储一个bit的数据，只需要一个晶体管和一个电容就能存储**，但是因为数据被存储在电容里，电容会不断漏电，所以需要**定时刷新电容**，才能保证数据不会被丢失，这就是DRAM之所以被称为动态存储器的原因，只有不断属性，数据才能被存储起来。

   DRAM的数据访问电路和数显电路比SRAM更复杂，所以访问速度会更慢，内存速度大概在**200-300个时钟周期**之间。

#### SSD/HDD硬盘

> SSD(Solid-state disk)固态硬盘，结构和内存类似，但是相比内存的优点是断电后数据还是存在的，而内存、寄存器、高速缓存断电后数据都会丢失。**内存的读写速度比SSD大概快10-1000**倍。

> HDD(Hard Disk Drive)机械硬盘，通过物理读写的方式来访问数据的，**访问速比内存慢10W倍左右**。

### 存储器的层次关系

> 每个存储器只和相邻的一层存储器设备打交道，并且存储设备为例追求更快的速度，所需材料成本必然是更高，正因为成本太高，所以CPU内部的寄存器、L1\L2\L3 Cache只好用较小的容量，相反内存、硬盘则可用更大的容量，这就是**存储器层次机构**。

[![image.png](https://i.postimg.cc/2js9x2mK/image.png)](https://postimg.cc/ThccdjKV)

+ CPU需要访问内存中某个数据的时候，如果寄存器中有这个数据，CPU就直接从寄存器中获取，如果寄存器没有这个数据，CPU就会查询L1高速缓存，如果L1高速缓存没有，则查询L2高速缓存，L2高速缓存没有，就查询L3高速缓存，L3依然没有才去内存中查找数据。

### 存储器之间的实际价格和性能差距

[![image.png](https://i.postimg.cc/hvb1ZjmP/image.png)](https://postimg.cc/5Qyz6fpZ)

### 总结

> 各种存储器之间的关系，可以用在图书馆学习场景举例

1. CPU相当于大脑，正在思考和处理知识的过程就好比寄存器处理数据的过程，速度极快，容量小；
2. CPU中的L1-L3 Cache好比大脑中的短期记忆和长期记忆；
3. 图书馆中的桌子好比内存，放下更多的数据，寻找和查看要花费时间，比CPU Cache慢。
4. 图书馆的书架相当于硬盘，能放下更多的数据，但是寻找更慢。

+ 那机械硬盘、固态硬盘、内存这三个存储器，到底和 CPU L1 Cache 相⽐速度差多少倍呢?
  + CPU L1 Cache随机访问延时是1纳秒，内存是100纳秒，SSD随机访问延时是150微秒；CPU L1 Cache比内存快100倍，比SSD快150000倍；

## 如何写出让CPU跑的更快的代码

> CPU内部嵌入了CPU Cache（高速缓存），存储量小，离CPU核心很近，缓存读写速度极快，如果运算时从CPU Cache读取数据而不是内存，运算速度就会很快。

### CPU Cache有多快

   CPU Cache 通常分为⼤⼩不等的三级缓存，分别是 L1 Cache、L2 Cache 和 L3 Cach，其中，**L1 Cache**通常会分为**数据缓存**和**指令缓存**，这意味着数据和指令在 L1 Cache 这⼀层是分开缓存的，上图中的 index0 也就是数据缓存，⽽ index1 则是指令缓存，它两的⼤⼩通常是⼀样的。另外，你也会注意到，L3 Cache ⽐ L1 Cache 和 L2 Cache ⼤很多，这是因为 **L1 Cache 和 L2 Cache 都是每个CPU 核⼼独有的**，⽽**L3 Cache 是多个 CPU 核⼼共享的**。程序执⾏时，会先将内存中的数据加载到共享的 L3 Cache 中，再加载到每个核⼼独有的 L2 Cache，最后进⼊到最快的 L1 Cache，之后才会被 CPU 读取。它们之间的层级关系，如下图

[![image.png](https://i.postimg.cc/zXDLRkhs/image.png)](https://postimg.cc/6TS6knYc)

[![image.png](https://i.postimg.cc/nc2cs48z/image.png)](https://postimg.cc/pp9t4nLb)

   越靠近CPU访问越快，根据上图可以看出CPU 从L1 Cache读取数据的速度，相比从内存读取的速度，会快100多倍。

```sh
# 查看L1 Cache数据缓存的大小
# cat /sys/devices/system/cpu/cpu0/cache/index0/size
32K
# 查看L1 Cache指令缓存的大小
# cat /sys/devices/system/cpu/cpu0/cache/index1/size
32K
# 查看L2 Cache的大小
# cat /sys/devices/system/cpu/cpu0/cache/index2/size
4096K
# 查看L3 Cache的大小
# cat /sys/devices/system/cpu/cpu0/cache/index3/size
36608K
```

### CPU Cache的数据结构和读取过程是什么样的

> CPU Cache的数据是从内存中读取过来的，他是以一小块一小块读取数据的，而不是按照单个数组元素读取的，在CPU Cache中的，这样一小块一小块的数据称为 **Cache Line(缓存块)** 。

```sh
   # 查看L1 Cache数据缓存一次载入数据的大小（字节）
   # cat /sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size 
64
```

+ 比如有一个int array[100]的数组，当载入array[0]时，由于这个数组元素的大小在内存只占4字节，不足64字节，CPU就会**顺序加载**数组元素到array[15]，意味着array[0]~array[15]数组元素都会被缓存在CPU Cache中，因此当下次访问这些数组元素，会直接从CPU Cache读取，而不用从内存读取，大大提高了CPU读取数据的性能。

   事实上，CPU读取数据的时候，无论是否放到Cache中，CPU都是先访问Cache，只有当Cache中找不到数据是，才会去访问内存，并把内存中的数据读入到Cache中，CPU再从CPU Cache读取数据。

   那么CPU是怎么知道要访问的内存数据，是否在Cache里？如果在的话，如何找到Cache的数据呢？从最简单的**直接映射 Cache（Direct Mapped Cache）**说起。

1. CPU访问内存数据时，是一小块一小块数据读取的，具体这一块数据的大小，取决于**coherench_line_size**的值，一般64字节。在内存中，这一块的数据称为**内存块（Block）**，读取的时候我们要拿到数据所在内存块的地址。
2. 对于直接映射Cache采用的策略，就是把**内存块的地址**始终**映射**在一个**CPU Line(缓存块)的地址**，映射关系的实现方式采用**取模运算**，取模运算的结果就是内存块地址对应的CPU Line(缓存块)的地址。

   举个例⼦，内存共被划分为32个内存块，CPU Cache共有8个CPU Line，假设 CPU 想要访问第15号内存块，如果 15 号内存块中的数据已经缓存在CPU Line中的话，则是⼀定映射在7号CPU Line中，因为15 % 8的值是7。使⽤取模⽅式映射的话，就会出现多个内存块对应同⼀个CPU Line，⽐如上⾯的例⼦，除了 15 号内存块是映射在7号CPU Line中，还有7号、23号、31号内存块都是映射到7号CPU Line中。

[![image.png](https://i.postimg.cc/Bv39fCBp/image.png)](https://postimg.cc/pms1Dz75)

   为了区别不同的内存块，在对应的**CPU Line**中我们还会存储⼀个**组标记（Tag）**。这个组标记会记录当前 CPU Line 中存储的数据对应的内存块，我们可以⽤这个组标记来区分不同的内存块。
   除了组标记信息外，CPU Line 还有两个信息：

+ 从内存加载过来的实际存放**数据（Data）**;
+ **有效位（Valid bie）**，标记对应CPU Line中的数据是否有效，如果是0，无论是否有数据，CPU都会直接访问内存，重新加载数据。

   CPU从CPU Line读取数据，不读取整个数据块，而是读取CPU需要的一个数据片段，这样的数据统称为一个**字（Word）**。可通过**偏移量（Offset）**在对应的CPU Line数据块中找到所需的字。

   因此，一个内存的访问地址包括**组标记、CPU Line索引、偏移量**这三种信息，于是CPU能通过这些信息，在CPU Cache中找到缓存的数据，对应CPU Cache里的数据结构，则是由**索引+有效位+组标记+数据块**组成。

[![image.png](https://i.postimg.cc/gjmPyHnr/image.png)](https://postimg.cc/k61Zq8Nd)

   如果内存中的数据已经在 CPU Cahe 中了，那 CPU 访问⼀个内存地址的时候，会经历这 4 个步骤：

1. 根据内存地址中索引信息，计算在 CPU Cahe 中的索引，也就是找出对应的 CPU Line 的地址；
2. 找到对应 CPU Line 后，判断 CPU Line 中的有效位，确认 CPU Line 中数据是否是有效的，如果是**⽆效的，CPU 就会越过CPU Cache直接访问内存，并重新加载数据，如果数据有效，则往下执⾏**；
3. 对⽐内存地址中组标记和 CPU Line 中的组标记，确认 CPU Line 中的数据是我们要访问的内存数据，如果不是的话，CPU 就会直接访问内存，并重新加载数据，如果是的话，则往下执⾏；
4. 根据内存地址中偏移量信息，从 CPU Line 的数据块中，读取对应的字

### 如何写出让CPU跑的更快的代码

> CPU访问内存的速度比访问CPU Cache的速度慢近100多倍，如果CPU操作的数据在CPU Cache中的话，将会带来很大的性能提升。访问数据在CPU Cache中的话意味着**缓存命中**，缓存命中率越高，代码性能越好，CPU跑的越快。因此如何写出让CPU跑的更快的代码可以看做是如何写出让CPU缓存命中率高的代码？

   L1 Cache通常分为数据缓存和指令缓存，如1+1=2这个运算，+就是指令，会被存在指令缓存里，而输入数字1会被存在数据缓存里。因此要分开看数据缓存和指令缓存的命中率

#### 如何提升数据缓存的命中率？

> 遍历二维数组有以下两种形式，代码执行结果一样，那种效率更高？

+ 通过下列代码可以发现arr[i][j]的执行时间要比arr[j][i]快好几倍，之所以有差距，是因为二维数组array所占用的内存是连续的，如果N=2，内存中数组元素的布局顺序是这样的arr[0][0],arr[0][1],arr[1][0],arr[1][1]
+ 形式1用arr[i][j]访问数组元素的顺序和上述一致。当 CPU 访问array[0][0] 时，由于该数据不在 Cache 中，于是会「顺序」把跟随其后的 3 个元素从内存中加载到 CPUCache，这样当 CPU 访问后⾯的 3 个数组元素时，就能在 CPU Cache 中成功地找到数据，这意味着缓存命中率很⾼，缓存命中的数据不需要访问内存，这便⼤⼤提⾼了代码的性能。
+ 形式2用arr[j][i]访问数组的顺序是arr[0][0],arr[1][0],arr[0][1],arr[1][1]，访问方式是跳跃式的而不是顺序的，那么如果 N 的数值很⼤，那么操作 array[j][i] 时，是没办法把 array[j+1][i] 也读⼊到 CPU Cache 中的，既然 array[j+1][i] 没有读取到 CPU Cache，那么就需要从内存读取该数据元素了。很明显，这种不连续性、跳跃式访问数据元素的⽅式，可能不能充分利⽤到了 CPU Cache 的特性，从⽽代码的性能不⾼。
+ 那访问 array[0][0] 元素时， CPU 具体会⼀次从内存中加载多少元素到 CPU Cache 呢？这个问题，在前⾯我们也提到过，这跟 CPU Cache Line 有关，它表示 CPU Cache ⼀次性能加载数据的⼤⼩，可以在Linux ⾥通过 coherency_line_size 配置查看 它的⼤⼩，通常是 64 个字节。也就是说，当 CPU 访问内存数据时，如果数据不在 CPU Cache 中，则会⼀次性会连续加载 64 字节⼤⼩的数据到 CPU Cache，那么当访问array[0][0] 时，由于该元素不⾜ 64 字节，于是就会往后顺序读取array[0][0]~array[0][15] 到 CPU Cache 中。顺序访问的 array[i][j] 因为利⽤了这⼀特点，所以就会⽐跳跃式访问的 array[j][i] 要快。
+ **提升数据的缓存命中率的方式，是暗中内存布局顺序访问**

```c
/**
 * 如何提升数据缓存的命中率
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

void test1(int N)
{
    int arr[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr[i][j] = i * 10 + j;
        }
    }
}

void test2(int N)
{
    int arr[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr[j][i] = j * 10 + i;
        }
    }
}

int main()
{
    clock_t start, end;
    double cost;
    int loop_size = 1000;
    start = clock();
    test1(loop_size);
    end = clock();
    cost = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
    printf("cost: %lf\n", cost);
    sleep(2);
    start = clock();
    test2(loop_size);
    end = clock();
    cost = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
    printf("cost: %lf\n", cost);

    return 0;
}
# result
CLOCKS_PER_SEC: 1000000
cost: 0.005171
CLOCKS_PER_SEC: 1000000
cost: 0.003415
```

### 如何提升指令缓存的命中率？

> 提升数据的缓存命中率的方式，是暗中内存布局顺序访问，那么针对指令缓存应该如何提升

```c
/**
 * 如何提升指令缓存的命中率
 */

#include <stdio.h>
// #include <algorithm>
#include <time.h>
#include <unistd.h>

void test3(int arr[], int N)
{
    for (int i = 0; i < N; i++)
    {
        if (arr[i] < 50)
        {
            arr[i] = 0;
        }
    }
}

// void test4(int arr[], int N)
// {
//     sort(arr, arr + N);
// }

int main()
{
    clock_t start, end;
    double cost;
    int loop_size = 100;

    // 指令缓存
    int arr[loop_size];
    for (int i = 0; i < loop_size; i++)
    {
        arr[i] = rand() % 100;
    }
    start = clock();
    test3(arr, loop_size);
    end = clock();
    cost = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
    printf("cost: %lf\n", cost);
    sleep(2);

    // start = clock();
    // test4(arr, loop_size);
    // end = clock();
    // cost = (double)(end - start) / CLOCKS_PER_SEC;
    // printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
    // printf("cost: %lf\n", cost);

    return 0;
}

# result
CLOCKS_PER_SEC: 1000000
cost: 0.000003
```

   先遍历再排序速度快，还是先排序再遍历速度快呢？

   在回答这个问题之前，我们先了解 CPU 的分⽀预测器。对于 if 条件语句，意味着此时⾄少可以选择跳转到两段不同的指令执⾏，也就是 if 还是 else 中的指令。那么， 如果分⽀预测可以预测到接下来要执⾏ if ⾥的指令，还是 else 指令的话，就可以「提前」把这些指令放在指令缓存中，这样 CPU 可以直接从 Cache读取到指令，于是执⾏速度就会很快。

   当数组中的元素是随机的，分⽀预测就⽆法有效⼯作，⽽当数组元素都是是顺序的，分⽀预测器会动态地根据历史命中数据对未来进⾏预测，这样命中率就会很⾼。因此，**先排序再遍历速度会更快**，这是因为排序之后，数字是从⼩到⼤的，那么前⼏次循环命中 if < 50的次数会⽐较多，于是分⽀预测就会缓存 if ⾥的 array[i] = 0 指令到 Cache 中，后续 CPU 执⾏该指令就只需要从 Cache 读取就好了。

### 如何提升多核CPU的缓存命中率

> 单核CPU，虽然只执行一个进程，但是操作系统给每个进程分配一个时间片，时间片用完调度下一个进程，各个进程按时间片交替占用CPU，宏观上看各个进程同时执行。

> 多核心CPU情况下，进程可能在不同CPU核心来回切换执行，虽然L3 Cache是多核之间共享的，但是L1、L2都是每个核心独有的，**如果一个进程在不同核心来回切换，各个核心的缓存命中率就会受到影响**，相反如果进程都在同一个核心上执行，那么L1、L2缓存命中率可以有效提高，减少访问内存的频率。

> 当有多个同时执行**计算密集型**的线程，为防止因切换到不同核心，导致缓存命中率下降的问题，我们可以把**线程绑定在某一个CPU核心上**，这样性能可以得到非常可观的提升。

+ Linux上提供了sched_setaffinity方法，来实现将线程绑定在某个CPU核心这一功能。

```c
# define _GNU_SOURCE
# include <sched.h>
int sched_setaffinity(pid_t pid,size_t cpusetsize,cpu_set_t * mask);
```

### 总结

   由于随着计算机技术的发展， CPU 与 内存的访问速度相差越来越多，如今差距已经⾼达好⼏百倍了，所以CPU 内部嵌⼊了 CPU Cache 组件，作为内存与 CPU 之间的缓存层， CPU Cache 由于离 CPU 核⼼很近，所以访问速度也是⾮常快的，但由于所需材料成本⽐较⾼，它不像内存动辄⼏个 GB ⼤⼩，⽽是仅有⼏⼗ KB 到 MB ⼤⼩。

   当 CPU 访问数据的时候，先是访问 CPU Cache，如果缓存命中的话，则直接返回数据，就不⽤每次都从内存读取速度了。因此，缓存命中率越⾼，代码的性能越好。但需要注意的是，当 CPU 访问数据时，如果 CPU Cache 没有缓存该数据，则会从内存读取数据，但是并不是只读⼀个数据，⽽是⼀次性读取⼀块⼀块的数据存放到 CPU Cache 中，之后才会被 CPU 读取。

   内存地址映射到 CPU Cache 地址⾥的策略有很多种，其中⽐较简单是直接映射 Cache，它巧妙的把内存地址拆分成**索引 + 组标记 + 偏移量**的⽅式，使得我们可以将很⼤的内存地址，映射到很⼩的 CPU
Cache 地址⾥。

   要想写出让 CPU 跑得更快的代码，就需要写出缓存命中率⾼的代码， CPU L1 Cache 分为**数据缓存和指令缓存**，因⽽需要分别提⾼它们的缓存命中率：

+ 对于数据缓存，我们在遍历数据的时候，应该按照内存布局的顺序操作，这是因为 CPU Cache 是根据 CPU Cache Line 批量操作数据的，所以顺序地操作连续内存数据时，性能能得到有效的提升；
+ 对于指令缓存，有规律的条件分⽀语句能够让 CPU 的分⽀预测器发挥作⽤，进⼀步提⾼执⾏的效率；

   另外，对于多核 CPU 系统，线程可能在不同 CPU 核⼼来回切换，这样各个核⼼的缓存命中率就会受到影响，于是要想提⾼进程的缓存命中率，可以考虑把线程绑定 CPU 到某⼀个 CPU 核⼼。

## CPU 缓存的一致性

### CPU Cache的数据写入

[![image.png](https://i.postimg.cc/zXDLRkhs/image.png)](https://postimg.cc/6TS6knYc)

> CPU Cache通常分为三级缓存：L1 Cache、L2 Cache、L3 Cache。L1离CPU核心最近，L3最远，每个核心有各自的L1/L2Cache、L3 Cache所有核心共享。

> CPU Cache是由多个Cache Line(缓存块)组成的，CPU Line是CPU从内存读取数据的基本单位，而CPU Line是由各种标志（Tag）+数据块（Data Block）组成

[![image.png](https://i.postimg.cc/k467L4B0/image.png)](https://postimg.cc/R6mrHv1d)

   数据除了读操作还要有写操作，如果数据写入Cache之后，内存与Cache相对应的数据将会不同，于是要讲Cache中的数据同步到内存里。以下是将Cache中的数据写入到内存中的方法。

#### 写直达（Write Through）

> 保持内存与Cache一致性的最简单方法是，**把数据同时写入内存和Cache中**，这种方法称为**写直达（Write Through）**。

[![image.png](https://i.postimg.cc/P5827n4C/image.png)](https://postimg.cc/5XbBHGDJ)

   在这个⽅法⾥，写⼊前会先判断数据是否已经在 CPU Cache ⾥⾯了：

+ 如果数据已经在 Cache ⾥⾯，先将数据更新到 Cache ⾥⾯，再写⼊到内存⾥⾯；
+ 如果数据没有在 Cache ⾥⾯，就直接把数据更新到内存⾥⾯。

   写直达法很直观，也很简单，但是问题明显，⽆论数据在不在 Cache ⾥⾯，每次写操作都会写回到内存，这样写操作将会花费⼤量的时间，⽆疑性能会受到很⼤的影响。

#### 写回（Write Back）

> 既然写直达由于每次写操作都会把数据写回到内存，而导致影响性能，为了减少数据写回内存的频率，出现了写回（Write Back）的方法。

   [![image.png](https://i.postimg.cc/hGHFwRNv/image.png)](https://postimg.cc/3yCb4V8Q)

   [![image.png](https://i.postimg.cc/vZkS8LhS/image.png)](https://postimg.cc/CRC4m8Wj)

+ 当发生写操作时，数据已经在CPU Cache里的话，就把数据更新到CPU Cache里，同时标记CPU Cache里的这个Cache Block为脏（Dirty）的，这个脏的标记代表这个时候CPU Cache里的Cache Block的数据和内存是不一致的，这种情况不用把数据写到内存里。
+ 当发生写操作时，数据对应的Cache Block里存放到是**别的内存地址的数据**的话，就要检测这个Cache Block里的数据有没有被标记为脏的，如果是脏的话，就要把这个Cache Block里的数据写回内存，然后把当前要写入的数据，写入到这个Cache Block里，同时把它也标记为脏的；如果Cache Block里面的数据，没有被标记为脏，则将数据直接写入到Cache Block里，然后再把这个CacheBlock标记为脏即可。
+ 写回：在把数据写入到Cache时，只有在缓存不命中，同时数据对应的Cache中的Cache Block标记为脏的情况下，才会将数据写到内存中；而缓存命中情况下，则在写入Cache后，只要把该数据对应的Cache Block标记为脏即可，而不用写到内存里。
+ 这样的好处是，如果大量的操作都能命中缓存，那么大部分时间里的CPU都不需要读写内存，自然性能要比写直达会高很多。

### 缓存一致性问题

> 多核CPU下，L1、L2 Cache是多个核心各自独有的，会带来多核心的**缓存一致性（Cache Coherence）**的问题，如果不能保证缓存一致性的问题，可能会造成结果错误。

+ 假设A核心和B核心同时运行2个线程，都操作共同变量i(初始值为0)
  这时如果 A 号核⼼**执⾏i++** 语句的时候，为了考虑性能，使⽤了我们前⾯所说的**写回策略**，先把值为**1** 的执⾏结果写⼊到**L1/L2 Cache**中，然后把 L1/L2 Cache 中对应的**Block 标记为脏**的，这个时候**数据其实没有被同步到内存**中的，因为写回策略，**只有在 A 号核⼼中的这个 Cache Block 要被替换的时候，数据才会写⼊到内存**⾥。

   如果这时旁边的**B 号核⼼尝试从内存读取 i 变量的值**，则读到的将会是错误的值，因为刚才 A 号核⼼更新i 值还没写⼊到内存中，**内存中的值还依然是 0**。 这个就是所谓的缓存⼀致性问题， A 号核⼼和 B 号核⼼的缓存，在这个时候是不⼀致，从⽽会导致执⾏结果的错误。

   [![image.png](https://i.postimg.cc/vBPtZ5wN/image.png)](https://postimg.cc/DJXXCJZr)

+ 解决方法：

1. 某个CPU核心里的Cache数据更新是，必须要传播到其他核心的Cache，这个称为**写传播（Write Propagation）**;
2. 某个CPU核心里对数据的操作顺序，必须在其他核心看起来顺序是一致的，这个称为**事务的串形化（Transaction Serialization）**

   假设有一个含有4核心的CPU，4个核心都操作共同的变量i(初始值为0)。A核心先把值变为100，B核心先把值变为200，这两个修改都会**传播**到C核心和D核心。

   [![image.png](https://i.postimg.cc/SKfMDTCH/image.png)](https://postimg.cc/jWC2jh8h)

   问题：

+ 如果C核心先收到A核心再收到B核心更新数据的事件，C核心看到的变量i先是变成100后变成200；
+ 如果D核心先收到B核心再收到C核心更新数据的事件，D核心看到的变量i先是变成200后变成100；
+ 虽然做到了写传播，但是各个Cache里的数据还是不一致的，所以要保证C核心和D核心看到**相同顺序的数据变化**，需要做到以下2点：
  + CPU核心对于Cache中数据的操作，需要同步给其他CPU核心；
  + 要引入**锁**的概念，如果两个CPU核心里有相同数据的Cache，那么对于这个Cache数据的更新，只有拿到了**锁**，才能进行相应的数据更新。

### 总线嗅探

> 写传播的原则就是当某个CPU核心更新了Cache中的数据，要将该事件广播通知单其他核心。最常见的实现方式就是**总线嗅探**。

   以前⾯的 i 变量例⼦来说明总线嗅探的⼯作机制，当 A 号 CPU 核⼼修改了 L1 Cache 中 i 变量的值，通过总线把这个事件⼴播通知给其他所有的核⼼，然后每个 CPU 核⼼都会监听总线上的⼴播事件，并检查是否有相同的数据在⾃⼰的 L1 Cache ⾥⾯，如果 B 号 CPU 核⼼的 L1 Cache 中有该数据，那么也需要把该数据更新到⾃⼰的 L1 Cache。

   可以发现，总线嗅探⽅法很简单， CPU 需要每时每刻监听总线上的⼀切活动，但是不管别的核⼼的Cache 是否缓存相同的数据，都需要发出⼀个⼴播事件，这⽆疑会加重总线的负载。

   另外，总线嗅探只是保证了某个 CPU 核⼼的 Cache 更新数据这个事件能被其他 CPU 核⼼知道，但是并不能保证事务串形化。
于是，有⼀个协议基于总线嗅探机制实现了事务串形化，也⽤状态机机制降低了总线带宽压⼒，这个协议就是 MESI 协议，这个协议就做到了 CPU 缓存⼀致性。

### MSSI协议

> MESI协议其实是4个状态单词的开头字母的缩写，分别是：

+ Modified，已修改
+ Exclusive，独占
+ Shared，共享
+ Invalidated，已失效

1. 「已修改」状态就是我们前⾯提到的脏标记，代表该 Cache Block 上的数据已经被更新过，但是还没有写到内存⾥。⽽「已失效」状态，表示的是这个 Cache Block ⾥的数据已经失效了，不可以读取该状态的数据。
2. 独占」和「共享」状态都代表 Cache Block ⾥的数据是⼲净的，也就是说，这个时候 Cache Block ⾥的数据和内存⾥⾯的数据是⼀致性的。
3. 「独占」和「共享」的差别在于，独占状态的时候，数据只存储在⼀个 CPU 核⼼的 Cache ⾥，⽽其他CPU 核⼼的 Cache 没有该数据。这个时候，如果要向独占的 Cache 写数据，就可以直接⾃由地写⼊，⽽不需要通知其他 CPU 核⼼，因为只有你这有这个数据，就不存在缓存⼀致性的问题了，于是就可以随便操作该数据。
4. 另外，在「独占」状态下的数据，如果有其他核⼼从内存读取了相同的数据到各⾃的 Cache ，那么这个时候，独占状态下的数据就会变成共享状态。
5. 那么，「共享」状态代表着相同的数据在多个 CPU 核⼼的 Cache ⾥都有，所以当我们要更新 Cache ⾥⾯的数据的时候，不能直接修改，⽽是要先向所有的其他 CPU 核⼼⼴播⼀个请求，要求先把其他核⼼的Cache 中对应的 Cache Line 标记为「⽆效」状态，然后再更新当前 Cache ⾥⾯的数据。

+ 举例：

1. 当 A 号 CPU 核⼼从内存读取变量 i 的值，数据被缓存在 A 号 CPU 核⼼⾃⼰的 Cache ⾥⾯，此时其他 CPU 核⼼的 Cache 没有缓存该数据，于是标记 Cache Line 状态为「独占」，此时其 Cache 中的数据与内存是⼀致的；
2. 然后 B 号 CPU 核⼼也从内存读取了变量 i 的值，此时会发送消息给其他 CPU 核⼼，由于 A 号 CPU核⼼已经缓存了该数据，所以会把数据返回给 B 号 CPU 核⼼。在这个时候， A 和 B 核⼼缓存了相同的数据， Cache Line 的状态就会变成「共享」，并且其 Cache 中的数据与内存也是⼀致的；
3. 当 A 号 CPU 核⼼要修改 Cache 中 i 变量的值，发现数据对应的 Cache Line 的状态是共享状态，则要向所有的其他 CPU 核⼼⼴播⼀个请求，要求先把其他核⼼的 Cache 中对应的 Cache Line 标记为「⽆效」状态，然后 A 号 CPU 核⼼才更新 Cache ⾥⾯的数据，同时标记 Cache Line 为「已修改」状态，此时 Cache 中的数据就与内存不⼀致了。
4. 如果 A 号 CPU 核⼼「继续」修改 Cache 中 i 变量的值，由于此时的 Cache Line 是「已修改」状态，因此不需要给其他 CPU 核⼼发送消息，直接更新数据即可。
5. 如果 A 号 CPU 核⼼的 Cache ⾥的 i 变量对应的 Cache Line 要被「替换」，发现 Cache Line 状态是「已修改」状态，就会在替换前先把数据同步到内存。

   所以，可以发现当 Cache Line 状态是「已修改」或者「独占」状态时，修改更新其数据不需要发送⼴播给
其他 CPU 核⼼，这在⼀定程度上减少了总线带宽压⼒。

[![image.png](https://i.postimg.cc/C1ZrzhJs/image.png)](https://postimg.cc/MMSmL8Cn)

### 总结

1. CPU 在读写数据的时候，都是在 CPU Cache 读写数据的，原因是 Cache 离 CPU 很近，读写性能相⽐内存⾼出很多。对于 Cache ⾥没有缓存 CPU 所需要读取的数据的这种情况， CPU 则会从内存读取数据，并将数据缓存到 Cache ⾥⾯，最后 CPU 再从 Cache 读取数据。
2. ⽽对于数据的写⼊， CPU 都会先写⼊到 Cache ⾥⾯，然后再在找个合适的时机写⼊到内存，那就有「写直达」和「写回」这两种策略来保证 Cache 与内存的数据⼀致性：

   + 写直达，只要有数据写⼊，都会直接把数据写⼊到内存⾥⾯，这种⽅式简单直观，但是性能就会受限于内存的访问速度；
   + 写回，对于已经缓存在 Cache 的数据的写⼊，只需要更新其数据就可以，不⽤写⼊到内存，只有在需要把缓存⾥⾯的脏数据交换出去的时候，才把数据同步到内存⾥，这种⽅式在缓存命中率⾼的情况，性能会更好；
3. 当今 CPU 都是多核的，每个核⼼都有各⾃独⽴的 L1/L2 Cache，只有 L3 Cache 是多个核⼼之间共享的。所以，我们要确保多核缓存是⼀致性的，否则会出现错误的结果。要想实现缓存⼀致性，关键是要满⾜ 2 点：

   + 第⼀点是写传播，也就是当某个 CPU 核⼼发⽣写⼊操作时，需要把该事件⼴播通知给其他核⼼；
   + 第⼆点是事物的串⾏化，这个很重要，只有保证了这个，才能保障我们的数据是真正⼀致的，我们的程序在各个不同的核⼼上运⾏的结果也是⼀致的；
4. 基于总线嗅探机制的 MESI 协议，就满⾜上⾯了这两点，因此它是保障缓存⼀致性的协议。
5. MESI 协议，是已修改、独占、共享、已实现这四个状态的英⽂缩写的组合。整个 MSI 状态的变更，则是根据来⾃本地 CPU 核⼼的请求，或者来⾃其他 CPU 核⼼通过总线传输过来的请求，从⽽构成⼀个流动的状态机。另外，对于在「已修改」或者「独占」状态的 Cache Line，修改更新其数据不需要发送⼴播给其他 CPU 核⼼。

## CPU是如何执行任务的

### CPU如何读写数据

#### CPU架构

> 只有先了解CPU架构，才能了解CPU如何读写数据，现代CPU架构如下

[![image.png](https://i.postimg.cc/LsHGPjhV/image.png)](https://postimg.cc/Js2TVDNy)

+ 一个CPU里包含多个核心，每个核心都有自己的L1/L2 Cache，L1 Cache又分为dCache(数据缓存)和iCache（指令缓存），L3 Cache则是多个核心共享的，这就是CPU典型的缓存层次。
+ 上面提到的都是CPU内部的Cache，外面还有内存和硬盘，这些存储设备共同构成了金字塔存储层次。如下图所示：

[![image.png](https://i.postimg.cc/2js9x2mK/image.png)](https://postimg.cc/ThccdjKV)

+ 从上图也可以看到，从上往下，存储设备容量越大，访问速度越慢。至于每个设备的存储延时，参考下图：

[![image.png](https://i.postimg.cc/hvb1ZjmP/image.png)](https://postimg.cc/5Qyz6fpZ)

#### CPU读写单位

[![image.png](https://i.postimg.cc/k467L4B0/image.png)](https://postimg.cc/R6mrHv1d)

+ CPU从内存读取数据到Cache的时候，并不是一个字节一个字节读取，而是一块一块的方式来读取数据的，这一块一块的数据称为CPU Line(缓存行)，所以**CPU Line是CPU总内存读取数据到Cache的单位**。
+ 至于CPU Line的大小，在Linux系统可以用以下命令查到，L1 Cache Line大小是64字节，也就意味着**L1 Cache一次载入数据的大小是64字节**。

```sh
# 查看L1 Cache数据缓存一次载入数据的大小
# cat /sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size
64
```

+ 对数组的加载，CPU会加载数组里面连续多个数据到Cache里，因此我们应该按照物理内存地址分布的顺序去访问元素，Cache命中率就会很高，于是能减少从内存读取数据的频率，从而提高内存的性能。
+ 不使用数组，使用单独的变量的时候，则会有Cache伪共享的问题，Cache伪共享问题是一个性能杀手，要尽量规避。

#### CPU伪共享问题

> 现在假设有⼀个双核⼼的 CPU，这两个 CPU 核⼼并⾏运⾏着两个不同的线程，它们同时从内存中读取两个不同的数据，分别是类型为 long 的变量 A 和 B，这个两个数据的地址在物理内存上是连续的，如果Cahce Line 的⼤⼩是 64 字节，并且变量 A 在 Cahce Line 的开头位置，那么这两个数据是位于同⼀个Cache Line 中，⼜因为 CPU Line 是 CPU 从内存读取数据到 Cache 的单位，所以这两个数据会被同时读⼊到了两个 CPU 核⼼中各⾃ Cache 中。

[![image.png](https://i.postimg.cc/yxV6x4Pn/image.png)](https://postimg.cc/ph6McS3n)

+ 如果这两个不同核⼼的线程分别修改不同的数据，⽐如 1 号 CPU 核⼼的线程只修改了 变量 A，或 2 号 CPU 核⼼的线程的线程只修改了变量 B，会发⽣什么呢？
+ 这种**因为多个线程同时读写同⼀个 Cache Line 的不同变量时，⽽导致 CPU Cache 失效的现象称为伪共享（False Sharing）**。

#### 避免伪共享方法

> 在Linux内核中存在_cacheline_aligned_in_smp宏定义，用于解决伪共享的问题

```sh
   #ifdef CONFIG_SMP
   #define __cacheline_aligned_in_smp __cacheline__aligned
   #else
   #define __cacheline_aligned_in_smp
   #endif
```

+ 从上面的宏定义可以看到：

  + 如果在多核（MP）系统里，该宏定义是__cacheline_aligned，也就是Cache Line的大小；
  + 如果在单核系统里，该宏定义是空的。
    因此，针对同一个CacheLine中的共享的数据，在多核之间竞争比较严重，为了防止伪共享现象的发生，可以采用上面的宏定义使得变量在CacheLine里是对齐的。
+ 举例：有如下结构体，结构体里面的2个成员变量a和b在物理内存地址上是连续的，可能会位于同一个Cache line中

```sh
   struct test{
       int a;
       int b;
   }
```

   [![image.png](https://i.postimg.cc/hvmVk8dW/image.png)](https://postimg.cc/dZq7dy64)

+ 为了防止前面提到的Cache伪共享问题，可以使用上面定义的宏定义，将b的地址设为对其地址：

```sh
   struct test{
       int a;
       int b __cacheline_aligned_in_smp;
   }
```

[![image.png](https://i.postimg.cc/HnLk5TTS/image.png)](https://postimg.cc/Fd2vX5dc)

+ 所以，避免Cache伪共享实际上是用空间换时间的思想，浪费一部分Cache空间，从而换来性能的提升。

### CPU如何选择线程

#### 进程与线程

> Linux内核中，进程和线程都是用**task_struct**结构体来表示，区别在于线程的tark_struct结构体里部分资源是共享了进程已创建的资源，比如内存地址空间、代码段、文件描述符等，所有Linux中的线程也被称为轻量级进程，因为线程的tark_struct相比进程的tark_struct承载的资源比较少，因此以**轻**得名。

   一般来说，没有创建线程的进程是只有单个执行流，被称是主线程。如果想让进程处理更多的事情，可以创建多个线程分别去处理，无论怎样，对应到内核里都是tark_struct。

[![image.png](https://i.postimg.cc/jqzbrtwV/image.png)](https://postimg.cc/c64jRqBT)

   所以，Linux内核里的调度器，调度的对象就是tark_struct，接下来把这个数据结构统称为**任务**。

#### 普通任务与实时任务

   Linux系统中，根据任务优先级和响应要求，主要分为两种，优先级数值越小，优先级越高：

+ 实时任务，对系统的响应要求很高，尽可能快的执行任务，优先级在**0-99**范围内的就算实时任务；
+ 普通任务，响应时间没有很高的要求，优先级在**100-139**范围内都是普通任务级别；

#### 调度类

> 由于任务有优先级之分，Linux系统为了保障高优先级的任务尽可能早的被执行，分了以下调度：

| 调度类   | 调度器         | 调度策略                 | 运行队列 |
| -------- | -------------- | ------------------------ | -------- |
| Deadline | Deadline调度器 | SCHED_DEANLINE           | dl_rq    |
| Realtime | RT调度器       | SCHED_FIFOS SCHED_RR     | rt_rq    |
| Fair     | CFS调度器      | SHCED_NORMAL SCHED_BATCH | cfs_rq   |

   Deadline和Realtime这两个调度类都是应用于实时任务的，这两个调度类的调度策略合起来有这3种

+ SCHED_DEADLINE：按照deadline进行调度，距离当前时间点最近的deadline的任务会被优先调度
+ SCHED_FIFO：对于相同优先级的任务，按照先来先服务的原则，但是优先级更高的任务可以抢占低优先级的任务，也就是高优先级的任务可以插队。
+ SCHED_RR：对于相同优先级的任务，轮流运行，每个任务都有一定的时间片，当用完时间片的任务通常会被放到队列尾部，以保证相同优先级任务的公平性，但是高优先级的任务依然可以抢占低优先级的任务；

#### 完全公平调度

> 平日遇到的基本都是普通任务，对于普通任务来说公平性最重要，在Linux里，实现了基于CFS的调度算法，也就是**完全公平调度（Completely Fair Scheduling）**。这个算法理念是想让分配给每个任务的CPU时间是一样，为每个任务安排一个虚拟运行时间vruntime，如果一个任务在运行，运行时间越久，该任务的runtime自然越大，没有被运行的任务，vruntime不会变化。所以在**CFS算法调度的时候会优先选择vruntime少的任务**，以保证每个任务的公平性。

   这就好⽐，让你把⼀桶的奶茶平均分到 10 杯奶茶杯⾥，你看着哪杯奶茶少，就多倒⼀些；哪个多了，就先不倒，这样经过多轮操作，虽然不能保证每杯奶茶完全⼀样多，但⾄少是公平的。当然，上⾯提到的例⼦没有考虑到优先级的问题，虽然是普通任务，但是普通任务之间还是有优先级区分的，所以在计算虚拟运⾏时间 vruntime 还要考虑普通任务的**权重值**，注意权重值并不是优先级的值，**内核中会有⼀个 nice 级别与权重值的转换表， nice 级别越低的权重值就越⼤**，⾄于 nice 值是什么，我们后⾯会提到。于是就有了以下这个公式：

   虚拟运行时间vruntime += 实际运行时间delta_exec * NICE_0_LOAD/权重

   NICE_0_LOAD 可以认为它是⼀个常量，那么在「同样的实际运⾏时间」⾥，⾼权重任务的 vruntime ⽐低权重任务的 vruntime 少，你可能会奇怪为什么是少的？你还记得 CFS 调度吗，它是会优先选择 vruntime 少的任务进⾏调度，所以⾼权重的任务就会被优先调度了，于是⾼权重的获得的实际运⾏时间⾃然就多了。

#### CPU运行队列

> 一个系统通常都会运行着很多任务，多任务的数量基本都是远超CPU核心数量，因此这时候就需要**排队**。

   事实上，每个CPU都有自己的**运行队列（Run Queue，rq）**，用于描述在此CPU上运行的所有进程，其队列包含三个运行队列，Deadline运行队列dl_rq、实时任务运行队列rt_rq和CFS（完全公平）运行队列cfs_rq，其中cfs_rq使用红黑树来描述的，按vruntime大小来排序的，最左侧叶子节点，就是下次会被调度的任务。

[![image.png](https://i.postimg.cc/Mpjv6cDx/image.png)](https://postimg.cc/rDM8gw3Y)

   这几种调度类是由优先级的，Deadline > Realtime > Fair，这意味着Linux选择下一个任务执行的时候，会按照优先级顺序进行选择，也就是从dl_rq里选择任务，然后从rt_rq里选择任务，最后从cfs_rq里选择任务，因此，**实施任务总是会比普通任务优先被执行**。

#### 调整优先级

   如果我们启动任务的时候，没有特意去只有优先级的话，默认情况下都是普通任务，普通任务的调度类Fair，由CFS调度器来进行管理。CFS调度器的目的是实现任务运行的公平性，也就是保障每个任务的运行时间是差不多的。

   如果想让某个普通任务有更多的执行时间，可以调整任务的**nice**值，从而让优先级高一些的任务执行更多时间。nice值能设置的范围是 **-20~19，值越低，表明优先级越高，默认优先级是0**。

   nice 值并不是表示优先级，⽽是表示优先级的修正数值，它与优先级（priority）的关系是这样的： priority(new) = priority(old) + nice。内核中， priority 的范围是0~139，值越低，优先级越⾼，其中前⾯的 0~99 范围是提供给实时任务使⽤的，⽽ nice 值是映射到100~139，这个范围是提供给普通任务⽤的，因此 nice 值调整的是普通任务的优先级。

```sh
# 启动任务指定nice的值，比如将msqld以-3优先级
$ nice -n 3 /usr/sbin/mysqld

# 修改已经运行中的任务的优先级，renice调整nice值
$ renice -10 -p <进程ID>

# nice 调整的是普通任务的优先级，所以不管怎么缩⼩ nice 值，任务永远都是普通任务，如果某些任务要求实时性⽐较⾼，那么你可以考虑改变任务的优先级以及调度策略，使得它变成实时任务，⽐如
# 修改调度策略为 SCHED_FIFO, 并且优先级为1
$ chrf -f 1 -p 1996
```

### 总结

   理解 CPU 是如何读写数据的前提，是要理解 CPU 的架构， CPU 内部的多个 Cache + 外部的内存和磁盘都就构成了⾦字塔的存储器结构，在这个⾦字塔中，越往下，存储器的容量就越⼤，但访问速度就会⼩。

   CPU 读写数据的时候，并不是按⼀个⼀个字节为单位来进⾏读写，⽽是以 CPU Line ⼤⼩为单位， CPULine ⼤⼩⼀般是 64 个字节，也就意味着 CPU 读写数据的时候，每⼀次都是以 64 字节⼤⼩为⼀块进⾏操作。

   因此，如果我们操作的数据是数组，那么访问数组元素的时候，按内存分布的地址顺序进⾏访问，这样能充分利⽤到 Cache，程序的性能得到提升。但如果操作的数据不是数组，⽽是普通的变量，并在多核 CPU的情况下，我们还需要避免 Cache Line 伪共享的问题。

   所谓的 Cache Line 伪共享问题就是，多个线程同时读写同⼀个 Cache Line 的不同变量时，⽽导致 CPU Cache 失效的现象。那么对于多个线程共享的热点数据，即经常会修改的数据，应该避免这些数据刚好在同⼀个 Cache Line 中，避免的⽅式⼀般有 Cache Line ⼤⼩字节对⻬，以及字节填充等⽅法。

   系统中需要运⾏的多线程数⼀般都会⼤于 CPU 核⼼，这样就会导致线程排队等待 CPU，这可能会产⽣⼀定的延时，如果我们的任务对延时容忍度很低，则可以通过⼀些⼈为⼿段⼲预 Linux 的默认调度策略和优先级。

## 软终断

### 中断是什么

> 在计算机中，中断是系统用来 **响应硬件设备请求** 的一种 **机制** ，操作系统**收到硬件的中断请求** ，会**打断正在执行的进程** ，然后 **调用内核中的中断处理程序** 来响应请求。

+ 中断是一种异步的时间处理机制，可以提高系统的并发处理能力。操作系统接收到中断请求，会打断其他进程的运行，所以 **中断请求的响应程序，也就是中断处理程序，要尽可能快的执行完，这样可以减少对正常进程运行调度地影响**。
+ 中断处理程序在响应中断时，还可能会 **临时关闭中断** ，意味着当前中断处理程序没有执行完之前，系统中其他的中断请求都无法被响应，也就是说中断可能会丢失，所以中断处理程序要快。

### 什么是软中断

> Linux系统 **为了解决中断处理程序执行过长和中断丢失的问题，将中断过程分成了两个阶段，分别是上半部和下半部分** 。

+ **上半部分用来快速处理中断** ，一般会暂时关闭中断请求，主要负责处理跟硬件紧密相关或者时间敏感的事情。
+ **下半部分用来延迟处理上半部未完成的工作** ，一般以 **内核线程** 的方式运行。

   举例：⽹卡收到⽹络包后，会通过 **硬件中断** 通知 **内核** 有新的数据到了，于是内核就会调⽤ **对应的中断处理程序** 来 **响应** 该事件，这个事件的处理也是会分成上半部和下半部。 **上部分要做到快速处理** ，所以只要把⽹卡的数据读到内存中，然后更新⼀下硬件寄存器的状态，⽐如把状态更新为表示数据已经读到内存中的状态值。接着， **内核会触发⼀个软中断** ，把⼀些处理 **⽐较耗时且复杂的事情** ，交给 **软中断处理程序** 去做，也就是中断的下半部，其主要是需要从内存中找到⽹络数据，再按照⽹络协议栈，对⽹络数据进⾏逐层解析和处理，最后把数据送给应⽤程序。

   也可以理解为：

+ 上半部直接处理硬件请求，也就是硬中断，主要是负责耗时短的工作，特点是快速执行；
+ 下半部是由内核触发，也就是软中断，主要是负责上半部未完成的工作，通常是耗时比较长的事情，特点是延迟执行。

   还有⼀个区别，硬中断（上半部）是会打断 CPU 正在执⾏的任务，然后⽴即执⾏中断处理程序，⽽软中断（下半部）是以内核线程的⽅式执⾏，并且 **每⼀个 CPU 都对应⼀个软中断内核线程，名字通常为「ksoftirqd/CPU 编号」**，⽐如 **0 号 CPU 对应的软中断内核线程的名字是 ksoftirqd/0** 。

### 系统里有哪些软中断

> 在linux系统里，可以通过/proc/softirqs的内容来知晓软中断的运行情况，以及/proc/interrupts的内容来知晓硬中断的运行情况

```sh
# 软中断
# cat /proc/softirqs
                CPU0       CPU1     
      HI:          0          1
   TIMER:    2941251    3669555
  NET_TX:         13         30
  NET_RX:     751341     633127
   BLOCK:      31171     319516
IRQ_POLL:          0          0
 TASKLET:       6189       4299
   SCHED:    2889645    3612050
 HRTIMER:        844        621
     RCU:    2475791    2558127
#  
```

+ 每一个CPU都有自己对应软中断的 **累计运行次数** ，有以下几点需要注意：

1. 第一列代表软中断的类型；
   + NET_TX 网络发送中断
   + NET_RX 网络接收中断
   + TIMEER 定时中断
   + RCU RCU锁中断
   + SCHED 内核调度中断
2. 通用类型的软中断在不同CPU的累计次数应该相差不多。
3. 上述数值是系统运行依赖累计中断次数，数值大小没什么参考意义，但是 **系统的中断次数的变化速率** 才是关注的，可以用 watch -d cat /proc/softirqs 来查看中断次数的变化速率。

[![image.png](https://i.postimg.cc/T3fNd9CV/image.png)](https://postimg.cc/D8pP5qV0)

   软中断是以内核线程的方式执行的，我们可以用ps命令查到，内核线程的名字外面都有中括号，这说明 ps 无法获取他们的命令行参数，所以一般来书，命令在中括号里的，都可以认为是内核线程。

```sh
# ps -aux | grep softirq
root           4  0.0  0.0   3532   712 ?        S    06:11   0:00 [ksoftirtqd/0]
root        3828  0.0  0.0   3532   712 pts/0    S+   06:11   0:00 grep softirq
```

```sh
# 硬中断
# cat /proc/interrupts
           CPU0       CPU1     
  1:          0          9   IO-APIC   1-edge      i8042
  4:          8          0   IO-APIC   4-edge      ttyS0
  6:          0          3   IO-APIC   6-edge      floppy
  8:          0          0   IO-APIC   8-edge      rtc0
  9:          0          0   IO-APIC   9-fasteoi   acpi
 11:          0          0   IO-APIC  11-fasteoi   virtio2, uhci_hcd:usb1
 12:         15          0   IO-APIC  12-edge      i8042
 14:      60895          0   IO-APIC  14-edge      ata_piix
 15:          0          0   IO-APIC  15-edge      ata_piix
 24:          0          0   PCI-MSI 98304-edge      virtio1-config
 25:          0     325982   PCI-MSI 98305-edge      virtio1-req.0
 26:          0          0   PCI-MSI 81920-edge      virtio0-config
 27:     271563          0   PCI-MSI 81921-edge      virtio0-input.0
 28:     319446          1   PCI-MSI 81922-edge      virtio0-output.0
 29:          1     222760   PCI-MSI 81923-edge      virtio0-input.1
 30:          0     252507   PCI-MSI 81924-edge      virtio0-output.1
NMI:          0          0   Non-maskable interrupts
LOC:   16335881   17020127   Local timer interrupts
SPU:          0          0   Spurious interrupts
PMI:          0          0   Performance monitoring interrupts
IWI:        822         44   IRQ work interrupts
RTR:          0          0   APIC ICR read retries
RES:    6347318    6209295   Rescheduling interrupts
CAL:     165150     168811   Function call interrupts
TLB:     381312     379175   TLB shootdowns
TRM:          0          0   Thermal event interrupts
THR:          0          0   Threshold APIC interrupts
DFR:          0          0   Deferred Error APIC interrupts
MCE:          0          0   Machine check exceptions
MCP:        196        196   Machine check polls
HYP:          0          0   Hypervisor callback interrupts
HRE:          0          0   Hyper-V reenlightenment interrupts
HVS:          0          0   Hyper-V stimer0 interrupts
ERR:          0
MIS:          0
PIN:          0          0   Posted-interrupt notification event
NPI:          0          0   Nested posted-interrupt event
PIW:          0          0   Posted-interrupt wakeup event
# 
```

### 如何定位软中断CPU使用率过高的问题

> 要想知道当前系统的软中断情况，可以使用top命令查看，

```sh
# top 运行后按数字1，即可显示所有CPU核心
$ top
top - 06:19:49 up 17:16,  0 users,  load average: 0.00, 0.01, 0.00
Tasks:   6 total,   1 running,   5 sleeping,   0 stopped,   0 zombie
%Cpu0  :  0.7 us,  0.7 sy,  0.0 ni, 98.7 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
%Cpu1  :  4.7 us,  0.7 sy,  0.0 ni, 94.6 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
MiB Mem :   3936.1 total,    140.9 free,   2247.1 used,   1548.2 buff/cache
MiB Swap:      0.0 total,      0.0 free,      0.0 used.   1422.4 avail Mem 

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                            
      1 root      20   0    2608    532    464 S   0.0   0.0   0:00.32 sh                                                 
      7 root      20   0  860320 108440  16812 S   0.0   2.7   0:47.39 jupyter-lab                                        
     67 root      20   0    2608   1680   1576 S   0.0   0.0   0:00.55 sh                                                 
     95 root      20   0  768984  59680  14136 S   0.0   1.5   0:02.84 python3                                            
     98 root      20   0  769116  59816  13968 S   0.0   1.5   0:02.98 python3                                            
   4005 root      20   0    6352   3408   2872 R   0.0   0.1   0:00.00 top 
```

+ 上述%Cpu0/%Cpu1两行中倒数第二列**0.0 si**，就是CPU在软中断上的使用率
+ 如果要知道那种软中断类型开销最大，可以使用 **watch -d cat /proc/softirqs** 命令来查看每个软中断类型的中断次数的变化速率。

```sh
Every 2.0s: cat /proc/softirqs            8cefcdab7b74: Thu Feb  2 06:26:04 2023

                    CPU0       CPU1
          HI:          0          1
       TIMER:    3054275    3769281
      NET_TX:         13         30
      NET_RX:     799145     645134
       BLOCK:      32037     326075
    IRQ_POLL:          0          0
     TASKLET:       6191       4341
       SCHED:    3002391    3711619
     HRTIMER:        844        621
         RCU:    2559520    2637886
```

   一般对于网络I/O较高的Web服务器，NET_RX网络接收中断的变化速率相比其他中断类型快很多。如果发现NET_RX网络接收中断次数的变化速率过快，可以使用 **sar -n DEV** 查看网卡的网络包接收速率情况，然后分析是那个网卡有大量的网络包进来。接着又 **tcpdump** 抓包分析包的来源。

### 总结

   为了避免由于中断处理程序执⾏时间过⻓，⽽影响正常进程的调度， Linux 将中断处理程序分为上半部和下半部：

+ 上半部，对应硬中断，由硬件触发中断，⽤来快速处理中断；
+ 下半部，对应软中断，由内核触发中断，⽤来异步处理上半部未完成的⼯作；

   Linux 中的软中断包括⽹络收发、定时、调度、 RCU 锁等各种类型，可以通过查看 **/proc/softirqs** 来观察软中断的累计中断次数情况，如果要实时查看中断次数的变化率，可以使⽤ **watch -d cat /proc/softirqs** 命令。

   每⼀个 CPU 都有各⾃的软中断内核线程，我们还可以⽤ ps 命令来查看内核线程，⼀般名字在中括号⾥⾯到，都认为是内核线程。

   如果在 top 命令发现， CPU 在软中断上的使⽤率 **(si)** ⽐较⾼，⽽且 CPU 使⽤率最⾼的进程也是软中断 **ksoftirqd** 的时候，这种⼀般可以认为系统的开销被软中断占据了。

   这时我们就可以分析是哪种软中断类型导致的，⼀般来说都是因为⽹络接收软中断导致的，如果是的话，可以⽤ sar 命令查看是哪个⽹卡的有⼤量的⽹络包接收，再⽤ tcpdump 抓⽹络包，做进⼀步分析该⽹络包的源头是不是⾮法地址，如果是就需要考虑防⽕墙增加规则，如果不是，则考虑硬件升级等。

## 为什么0.1+0.2不等于0.3

### 总结

1. 为什么负数要用补码来表示？
   负数之所以用补码表示，主要是为了统一和整数的加减法操作一样，毕竟数字的加减法是很常用的一个操作，尽量以统一方式运作。
2. 十进制怎么转换成二进制？
   十进制整数转换成二进制使用的是除2取余法，十进制小数使用的是乘2取整法。
3. 计算机怎么存小数？
   以浮点数的形式存储小数，大多数计算机都是IEEE754标准定义的浮点数格式，包含三个部分：

+ 符号位：表示数字是正数还是负数，0表示正数，1表示负数
+ 指数位：指定了⼩数点在数据中的位置，指数可以是负数，也可以是正数，指数位的⻓度越⻓则数值的表达范围就越⼤；
+ 尾数位：⼩数点右侧的数字，也就是⼩数部分，⽐如⼆进制 1.0011 x 2^(-2)，尾数部分就是 0011，⽽且尾数的⻓度决定了这个数的精度，因此如果要表示精度更⾼的⼩数，则就要提⾼尾数位的⻓度；

   ⽤ 32 位来表示的浮点数，则称为单精度浮点数，也就是我们编程语⾔中的 float 变量，⽽⽤ 64 位来表示的浮点数，称为双精度浮点数，也就是 double 变量。

4. 0.1+0.2==0.3吗？
   不是的， 0.1 和 0.2 这两个数字⽤⼆进制表达会是⼀个⼀直循环的⼆进制数，⽐如 0.1 的⼆进制表示为 0.00011 0011 0011… （0011 ⽆限循环)，对于计算机⽽⾔， 0.1 ⽆法精确表达，这是浮点数计算造成精度损失的根源。因此， IEEE 754 标准定义的浮点数只能根据精度舍⼊，然后⽤「近似值」来表示该⼆进制，那么意味着计算机存放的⼩数可能不是⼀个真实值。0.1 + 0.2 并不等于完整的 0.3，这主要是因为这两个⼩数⽆法⽤「完整」的⼆进制来表示，只能根据精度舍⼊，所以计算机⾥只能采⽤近似数的⽅式来保存，那两个近似数相加，得到的必然也是⼀个近似数。

# 操作系统结构

## Linux内核Windows内核

> 计算机是由各种外部硬件组成的，比如CPU、内存、硬盘等，如果每个应用都要和这些硬件设备对接通信协议，过于麻烦，所以需要内核作为中间人来负责，**内核作为应用连接硬件设备的桥梁**，应用程序只关心与内核的交互，不用关系硬件的细节。

   [![image.png](https://i.postimg.cc/9fwPJvJY/image.png)](https://postimg.cc/SXqzKt0n)

   内核有哪些能力呢？

1. 管理进程、线程，决定那个进程、线程使用CPU，也就是进程调度的能力；
2. 管理内存，决定内存的分配与回收，也就是内存管理的能力；
3. 管理硬件设备，为进程与硬件设备之间提供通信能力，也就是硬件通信能力；
4. 提供系统调用，如果应用程序要运行更高权限的服务，那么就需要有系统调用，他是用户程序与操作系统之间的接口。

   内核是怎么工作的？

> 内核具有很高的权限，可以控制CPU，内存，硬盘等硬件，而应用程序具有的权限很小，因此大多数系统把内存分成了两个区域：

+ 内核空间：这个内存空间只可以内核程序可以访问；
+ 用户空间：这个内存空间专门给应用程序使用；
+ 用户空间的代码智能访问一个局部的内存空间，而内核空间的代码可以访问所有内存空间。因此当程序使用用户空间时，我们常说程序在 **用户态** 执行，而程序使用内核空间时，程序则在 **内核态** 执行。

   [![image.png](https://i.postimg.cc/Nj8621CQ/image.png)](https://postimg.cc/K1zkdgyW)

   内核程序执⾏在内核态，⽤户程序执⾏在⽤户态。当应⽤程序使⽤系统调⽤时，会产⽣⼀个中断。发⽣中断后， CPU 会中断当前在执⾏的⽤户程序，转⽽跳转到中断处理程序，也就是开始执⾏内核程序。内核处理完后，主动触发中断，把 CPU 执⾏权限交回给⽤户程序，回到⽤户态继续⼯作。

### Linux的设计

> Linux内核设计的理念主要有以下几点

+ MultiTask，多任务
+ SMP，对称多处理
+ ELF，可执行文件链接格式
+ Monolithic Kernel，宏内核

1. MultiTask

   MultiTask的意思就是 **多任务**，代表Linux是一个多任务的系统，多任务意味着可以有多个任务同时执行，这里的 **同时** 可以是 **并发或并行**；

+ 对于单核CPU，可以让每个任务执行一小段时间，时间就切换到另外一个任务，宏观角度看，一段时间内执行多个任务，这被称为 **并发**。
+ 对于多核CPU，多个任务可以同时被不同核心的CPU同时执行，这被称为 **并行**。

2. SMP

   SMP的意思是 **对称多处理**，代表每个CPU的地位是相等的，对资源的使用权限也是相同的，多个CPU共享同一个内存，每个CPU都可以访问完整的内存和硬件资源。这个特点决定Linxu操作系统不会有某个CPU单独服务应用程序或内核程序，而是每个程序都可以被分配到任意一个CPU上被执行。

3. ELF

   ELF的意思是 **可执行文件链接格式**，他是Linux操作系统中可执行文件的存储格式，可以看到它的结构如下：

   [![image.png](https://i.postimg.cc/7ZcVSgSc/image.png)](https://postimg.cc/sMY7rG69)

   ELF文件有2种索引，Program header table中记录了 **运行时**所需的段，而Section header table记录了二进制文件中各个 **段的首地址**。

   ELF文件怎么生成的呢？

+ 编写的代码首先通过 **编译器** 编译成汇编代码，接着通过 **汇编器** 变成目标代码，也就是目标文件，最后通过 **链接器** 把多个目标文件及调用的各种函数库链接起来，形成一个可执行文件，也就是ELF文件。

   ELF文件怎么被执行？

+ 执行ELF文件的时候，通过 **装载器** 把ELF文件装载到内存里，CPU读取内存中的指令和数据，于是程序就被执行起来了。

4. Monolithic Kernel

   Monolithic Kernel的意思是 **宏内核** ，Linux内核架构就是宏内核，意味着Linux的内核是一个完整的可执行程序，且拥有最高的权限。

   宏内核的特征是系统内核的所有模块，比如进程调度、内存管理、文件系统、设备驱动等都运行在内核态。不过Linux也实现了动态加载内核模块的功能，例如大部分设备驱动是以可加载模块的形式存在的，与内核其他模块解耦。

   与宏内核相反的是 **微内核**，微内核架构的内核只保留最基本的能力，比如进程调度、虚拟机内存、中断等，把一些应用放在了用户空间，比如驱动程序、文件系统等。这样服务与服务之间是隔离的，单个服务出现问题不会影响其他，提高了操作系统的稳定性和可靠性。微内核内核功能少，可移植性⾼，相⽐宏内核有⼀点不好的地⽅在于，由于驱动程序不在内核中，⽽且驱动程序⼀般会频繁调⽤底层能⼒的，于是驱动和硬件设备交互就需要频繁切换到内核态，这样会带来性能损耗。华为的鸿蒙操作系统的内核架构就是微内核。

   还有⼀种内核叫混合类型内核，它的架构有点像微内核，内核⾥⾯会有⼀个最⼩版本的内核，然后其他模块会在这个基础上搭建，然后实现的时候会跟宏内核类似，也就是把整个内核做成⼀个完整的程序，⼤部分服务都在内核中，这就像是宏内核的⽅式包裹着⼀个微内核。

# 内存管理

## 虚拟内存

### 虚拟内存

> 单片机没有操作系统，每次写完代码，要借助工具将程序烧录进去， **单片机的CPU是直接操作内存的物理地址** 。在这种情况下，要想在内存中同时运⾏两个程序是不可能的。如果第⼀个程序在 2000 的位置写⼊⼀个新的值，将会擦掉第⼆个程序存放在相同位置上的所有内容，所以同时运⾏两个程序是根本⾏不通的，这两个程序会⽴刻崩溃。

> 操作系统如何解决这个问题？

   上述问题的关键是两个程序都引用了绝对物理地址，而这是需要避免的

   可以把进程所使用的的地址 **隔离** 开来，让操作系统为每个进程分配独立有的一套 **虚拟地址**，每隔进程都有，互不干涉。前提是每隔进程都不能访问物理地址。

[![image.png](https://i.postimg.cc/DwxqTvRd/image.png)](https://postimg.cc/DSbWQTv8)

   **操作系统会提供一种机制，将不同进程的虚拟地址和不同内存的物理地址映射起来**。

   如果程序要访问虚拟地址，由操作系统转换成不同的物理地址，这样不同进程运行的时候，写入不同的物理地址，不会冲突。

+ 程序使用的地址叫虚拟内存地址（Virtual Memory Address）；
+ 实际存在硬件里的空间地址叫物理内存地址（Physical Memory Address）

   操作系统引入虚拟内存，进程持有的虚拟地址会通过CPU芯片中的 **内存管理单元（MMU）** 的映射关系来转变成物理地址，然后在通过物理地址访问内存。

[![image.png](https://i.postimg.cc/V6CkLwLV/image.png)](https://postimg.cc/62BXYDZr)

> 操作系统是如何管理虚拟地址和物理地址之间的关系？

   主要有两种方式，分别是 **内存分段和内存页**

### 内存分段

> 程序有若干个逻辑分段组成，如可由代码分段、数据分段、栈段、堆段组成。 **不同的段是由不同的属性的，所以就用分段（Segementation）的形式把这些段分离出来**。

> 分段机制下，虚拟地址和物理地址是如何映射的？

   分段机制下的虚拟地址由两部分组成， **段选择子和段内偏移量** 。

[![image.png](https://i.postimg.cc/26WTzJTm/image.png)](https://postimg.cc/jwsycMGk)

+ **段选择子** 就保存在段寄存器里面。段选择子里面最重要的就是 **段号**，用作段表的 **索引** ，**段表** 里面保存的是这个 **段的基地址、段的界限和特权等级**等。
+ 虚拟地址中的 **段内偏移量** 应该位于0和段界限之间，如果 **段内偏移量** 是合法的，就将 **段基地址加上段内偏移量** 得到 **物理内存地址**。

   在上面知道 **虚拟地址** 是通过 **段表** 与 **物理地址** 进行映射的，分段机制把程序的虚拟地址分成4个段，每个段在段表中有一个项，在这一项找到段的基地址，再加上偏移量，于是就能找到物理内存中的地址。

[![image.png](https://i.postimg.cc/j58359JF/image.png)](https://postimg.cc/zbgF2x7C)

   如果访问段3中偏移量500的虚拟地址，我们可以计算出物理地址为，段3基地址7000+偏移量500=7500。

   分段的办法很好，解决程序本省不需要关系具体的物理内存地址的问题，但也有一些不足之处：

1. **内存碎片**的问题
2. **内存交换的效率低**的问题。

> 分段为什么会产生内存碎片的问题？

   假设有1G物理内存，用户执行多个程序，其中游戏占用512MB内存，浏览器占用128MB内存，音乐占用256MB内存。

   这个时候关闭浏览器，空闲内存还有1024-512-256=256MB，如果这个256MB不是连续的，被分成了2段128MB内存，这就会导致没有内存再打开一个200MB的程序。

[![image.png](https://i.postimg.cc/XvhqKNFK/image.png)](https://postimg.cc/5HBfbVsj)

   这里的内存碎片问题共有2处地方：

+ 外部内存碎片，也就是产生多个不连续的小物理内存，导致新的程序无法被加载；
+ 内部内存碎片，程序所有的内存都被装载到了物理内存，但是这个程序有部分的内存可能并不是很常使用，这也会导致内存的浪费。

   针对上面两种内存碎片的问题，解决外部内部碎片的问题就是 **内存交换**。

> 分段为什么会导致内存交换效率低的问题？

   对于多进程的系统来说，用分段的方式，内存碎片是很容易产生的，产生了内存碎片，不得不重新 **swap** 内存区域，这个过程会产生性能瓶颈。因为硬盘的访问速度要比内存慢太多，每一次内存交换都需要把一大段连续内存数据写到硬盘上，所以， **如果内存交换的时候，交换的是一个占内存空间很大的程序，这样整个机器都会显得卡顿**。为解决内存分段的内存碎片和内存交换效率低的问题，就出现了内存分页。

### 内存分页

> 分段的好处是能产生连续的内存空间，但是会出现内存碎片和内存交换空间太大的问题。要解决这些问题，就要想出能少出现内存碎片的办法，另外当需要进行内存交换的时候，让需要交换写入或从磁盘装载的数据更少一点，这样就可以解决问题了。这就是内存分页。 **内存分页是把整个虚拟和物理内存空间切成一段段固定尺寸的大小**。这样一个连续并且尺寸固定的内存空间叫做 **页（Page）**。在Linux下，每一页的大小为 **4KB** 。

   虚拟地址与物理地址之间通过 **页表** 来映射，如下图：

[![image.png](https://i.postimg.cc/tJZZ6ZYH/image.png)](https://postimg.cc/5QJ2dtBP)

   页表是存储在内存里面的，**内存管理单元（MMU）** 就做虚拟内存地址转换成物理地址的工作。当进程访问的虚拟地址页在页表中查不到是，系统就会产生一个 **缺页异常**，进入系统内核空间分配物理内存、更新进程页表、最后再返回用户空间，恢复进程的运行。

> 分页是怎么解决分段的内存碎片、内存交换效率低的问题？

1. 由于内存空间都是预先规划分好的不会想分段会产生间隙非常小的内存，这正是分队会产生内存碎片的原因， **采用分页，那么释放的内存都是以页为单位释放的，也就不会产生无法给进程使用的小内存**。
2. 如果内存空间不够，操作系统会把其他正运行的进程中的 **最近没被使用** 的内存页面给释放掉，也就是暂时写在硬盘上，称为 **换出（Swap Out）**，一旦需要的时候再加载进来，称为 **换入（Swap In）**。所以一次写入磁盘的也只有少数的一个或几个页，不会花太多时间， **内存交换效率就相对高**。

[![image.png](https://i.postimg.cc/bY7hxCJt/image.png)](https://postimg.cc/XXkm3g9j)

3. 另外，分页的方式使得我们在加载程序的时候，不再需要一次性的吧程序都加载到物理内存中， **只有在程序运行中，需要用到对应虚拟内存夜里面的指令和数据是，再加载到物理内存里面去。

> 分页机制下，虚拟地址和物理地址是如何映射的？

   在分页机制下，虚拟地址分为两部分，**页号和页内偏移**。 **页号作为页表的索引** ，**页表**包含物理页每页所在 **物理内存的基地址** ，这个基地址与页内偏移的组合就形成了物理内存地址，见下图

[![image.png](https://i.postimg.cc/cJcDHc92/image.png)](https://postimg.cc/xkcGpLS3)

+ 内存地址转换，其实就是以下步骤：

1. 把虚拟内存地址，切分成页号和偏移量；
2. 根据页号，从页表里面，查询到对应的物理页号；
3. 用物理页号加上从虚拟内存地址切分出的偏移量，就得到了物理内存地址。

+ 举例：虚拟内存中的页通过页表映射为了物理内存中的页，如下图：

[![image.png](https://i.postimg.cc/mDscg0pN/image.png)](https://postimg.cc/8FZkynSj)

> 上述分页看起来没问题，放到实际操作系统，这么简单的分页肯定会有问题的，存在什么缺陷呢？

+ 空间上存在缺陷。操作系统可以同时运行非常多的进程，意味着页表会非常庞大。在32位环境下，虚拟地址空间有4GB，假设一个页是4KB(2^12)，那么大概就需要100万（2^20）个页，每个 **页表项** 需要4个字节大小存储，那么整个4GB空间的映射就需要4MB内存来存储页表。但是每个进程都是有自己的虚拟地址空间的也就是页表，那么100个进程的话，就需要400MB的内存来存储页表，这占用过多内存
+ 多级页表

   解决上述问题可以采用 **多级页表（Multi-Level Page Table）** 的解决方案。

   对于单⻚表的实现⽅式，在 32 位和⻚⼤⼩ 4KB 的环境下，⼀个进程的⻚表需要装下 100 多万个「⻚表项」，并且每个⻚表项是占⽤ 4 字节⼤⼩的，于是相当于每个⻚表需占⽤ 4MB ⼤⼩的空间。我们把这个 100 多万个「⻚表项」的单级⻚表再分⻚，将⻚表（⼀级⻚表）分为 1024 个⻚表（⼆级⻚表），每个表（⼆级⻚表）中包含 1024 个「⻚表项」，形成⼆级分⻚。如下图所示：

[![image.png](https://i.postimg.cc/KzrPL4QR/image.png)](https://postimg.cc/xJ8NVfw2)

> 分了⼆级表，映射 4GB 地址空间就需要 4KB（⼀级⻚表） + 4MB（⼆级⻚表）的内存，这样占⽤空间不是更⼤了吗？

   如果使⽤了⼆级分⻚，⼀级⻚表就可以覆盖整个 4GB 虚拟地址空间，但 **如果某个⼀级⻚表的⻚表项没有被⽤到，也就不需要创建这个⻚表项对应的⼆级⻚表了，即可以在需要时才创建⼆级⻚表** 。做个简单的计算，假设只有 20% 的⼀级⻚表项被⽤到了，那么⻚表占⽤的内存空间就只有 4KB（⼀级⻚表） + 20% \*4MB（⼆级⻚表） = 0.804MB ，这对⽐单级⻚表的 4MB 是不是⼀个巨⼤的节约

> 对于64位的系统，两级分页肯定不够，就变成了四级目录，分别是：

+ 全局页目录项PGD(Page Global Directory)
+ 上层页目录项PUD(Page Upper Directory)
+ 中间页目录项PMD(Page Middle Directory)
+ 页表项PTD(Page Table Entry)

[![image.png](https://i.postimg.cc/ZRvmrY7z/image.png)](https://postimg.cc/7G4j44rK)

   多级⻚表虽然解决了空间上的问题，但是虚拟地址到物理地址的转换就多了⼏道转换的⼯序，这显然就降低了这俩地址转换的速度，也就是带来了时间上的开销。**程序是有局部性的，即在⼀段时间内，整个程序的执⾏仅限于程序中的某⼀部分。相应地，执⾏所访问的存储空间也局限于某个内存区域**。

[![image.png](https://i.postimg.cc/y8VCdy0R/image.png)](https://postimg.cc/RNbDpfsC)

   我们可以利用这一特性，把最常访问的几个页表项存储到访问速度更快的硬件，于是CPU芯片中加入了一个 **专门存放程序最常访问的页表项的Cache，这个Cache就是TLB（Transaction Lookaside Buffer），通常称为页表缓存、转址旁路缓存、快表等** 。

[![image.png](https://i.postimg.cc/PrqFRfsg/image.png)](https://postimg.cc/hhHrJBGs)

   在CPU芯片里面，封装了内存管理单元（Memory Management Unit）芯片，它用来完成地址转换和TLB的访问与交互，有了TLB后，CPU寻址时会先查TLB，如果没找到，才会继续查常规的页表。TLB因为经常访问的页不多，所以命中率很高。

### 段页式内存管理

> 内存分段和内存分页并不是对立的，他们是可以组合起来在同一个系统中使用的，组合起来后称为段页式管理。

[![image.png](https://i.postimg.cc/W30pJ61P/image.png)](https://postimg.cc/ZBKzGNNf)

   段页式管理的实现方式：

+ 先将程序划分多个有逻辑意义的段，也就是分段机制；
+ 接着把每个段划分成多个页，也就是对分段划分出来的连续空间，再划分固定大小的页

   这样，地址结构就由 **段号、段内页号和页内位移** 三部分组成。用于段页式地址变换的数据结构是一个程序一张段表，每个段又建立一张页表，段表中的地址是页表起始地址，而页表中的地址则为某页的物理页号，如图所示：

[![image.png](https://i.postimg.cc/WpXK2qsW/image.png)](https://postimg.cc/23LTG6bh)

+ 段页式地址变换中要得到物理地址必须经过三层内存访问：

1. 第一次访问段表，得到页表起始地址；
2. 第二次访问页表，得到物理页号；
3. 第三次将物理页号与页内位移组合，得到物理地址。

   可用软、硬件结合的方式实现段页式地址变换，这样虽然增加了硬件成本和系统开销，但提高了内存的利用率。

### Linux内存管理

   Linux内存主要采用的是页式内存管理，但同时也不可避免地涉及了段机制。

   Linux系统中的每个段地址都是从0地址开始的整个4GB虚拟空间（32位环境下），也就是所有的段的起始地址都是一样的。这意味着Linux系统中的代码，包括操作系统本身的代码和应用程序代码，所面对的地址空间都是线性地址空间（虚拟地址），这种做法相当于屏蔽了处理器中的逻辑地址概念，段只被用于访问控制和内存保护。

> Linux的虚拟地址空间是如何分布的？

   Linux操作系统中，虚拟地址空间内部又被分为 **内核空间和用户空间** 两部分，不同位数的系统，地址空间的额范围也不同。比如最常见的32位和64位系统，如下所示：

[![image.png](https://i.postimg.cc/Fs6gWJLw/image.png)](https://postimg.cc/ZCrd0njL)

   通过这⾥可以看出：32 位系统的内核空间占⽤ 1G ，位于最⾼处，剩下的 3G 是⽤户空间；64 位系统的内核空间和⽤户空间都是 128T ，分别占据整个内存空间的最⾼和最低处，剩下的中间部分是未定义的。再来说说，内核空间与⽤户空间的区别：   进程在⽤户态时，只能访问⽤户空间内存；只有进⼊内核态后，才可以访问内核空间的内存；虽然每个进程都各⾃有独⽴的虚拟内存，但是 **每个虚拟内存中的内核地址，其实关联的都是相同的物理内存** 。这样，进程切换到内核态后，就可以很⽅便地访问内核空间内存。

+ 32位内存空间解析：

[![image.png](https://i.postimg.cc/VvFR7Ytv/image.png)](https://postimg.cc/T5pg1vCv)

   通过上述图可以看到用户内存空间，从低到高分别是7中不同的内存段：

1. 程序文件段，包括二进制可执行代码；
2. 已初始化的数据段，包括静态常量；
3. 未初始化数据段，包括未初始化的静态变量；
4. 堆段，包括动态分配的内存，从低地址开始向上增长；
5. 文件映射段，包括动态库、共享内存库等，从低地址开始向上增长（跟硬件和内核版本有关）；
6. 栈段，包括局部变量和函数调用的上下文等。栈的大小是固定的，一般是 **8MB** ，也可以自定义大小。

   在这些内存段中，堆和文件映射段的内存是动态分配的。比如说，使用C标准库的malloc()或者mmap()，就可以分别在堆和文件映射段动态分配内存。

### 总结

   为了在多进程环境下，使得进程之间的内存地址不受影响，相互隔离，于是操作系统就为每个进程独⽴分配⼀套 **虚拟地址空间** ，每个程序只关⼼⾃⼰的虚拟地址就可以，实际上⼤家的虚拟地址都是⼀样的，但分布到物理地址内存是不⼀样的。作为程序，也不⽤关⼼物理地址的事情。

   每个进程都有⾃⼰的虚拟空间，⽽物理内存只有⼀个，所以当启⽤了⼤量的进程，物理内存必然会很紧张，于是操作系统会通过 **内存交换技术** ，把不常使⽤的内存暂时存放到硬盘（换出），在需要的时候再装载回物理内存（换⼊）。

   那既然有了虚拟地址空间，那必然要把虚拟地址「映射」到物理地址，这个事情通常由操作系统来维护。那么对于虚拟地址与物理地址的映射关系，可以有 **分段和分⻚** 的⽅式，同时两者结合都是可以的。内存分段是根据程序的逻辑⻆度，分成了栈段、堆段、数据段、代码段等，这样可以分离出不同属性的段，同时是⼀块连续的空间。但是每个段的⼤⼩都不是统⼀的，这就会导致内存碎⽚和内存交换效率低的问题。

   于是，就出现了内存分⻚，把虚拟空间和物理空间分成⼤⼩固定的⻚，如在 Linux 系统中，每⼀⻚的⼤⼩为 **4KB** 。由于分了⻚后，就不会产⽣细⼩的内存碎⽚。同时在内存交换的时候，写⼊硬盘也就⼀个⻚或⼏个⻚，这就⼤⼤提⾼了内存交换的效率。

   再来，为了解决简单分⻚产⽣的⻚表过⼤的问题，就有了 **多级⻚表** ，它解决了空间上的问题，但这就会导致 CPU 在寻址的过程中，需要有很多层表参与，加⼤了时间上的开销。于是根据程序的 **局部性原理** ，在CPU 芯⽚中加⼊了 **TLB** ，负责缓存最近常被访问的⻚表项，⼤⼤提⾼了地址的转换速度。

   **Linux 系统主要采⽤了分⻚管理，但是由于 Intel 处理器的发展史， Linux 系统⽆法避免分段管理** 。于是Linux 就把所有段的基地址设为 **0** ，也就意味着所有程序的地址空间都是线性地址空间（虚拟地址），相当于屏蔽了 CPU 逻辑地址的概念，所以段只被⽤于访问控制和内存保护。

   另外， Linxu 系统中虚拟空间分布可分为 **⽤户态和内核态** 两部分，其中⽤户态的分布：代码段、全局变量、BSS、函数栈、堆内存、映射区。

# 进程与线程

## 进程线程基础知识

### 进程

#### 进程的概念

> 我们编写的代码知识一个存储在硬盘的静态文件，变异后生成二进制可执行文件，当我们运行这个可执行文件后，他会被载到内存中，接着CP会执行程序中的每一条指令，那么这个 **运行中的程序就被称为进程（Process）**。

   假设有一个会读取硬盘文件的程序被执行，当进程要从硬盘读取数据时，CPU不需要阻塞等待数据的返回，而是去执行另外的进程。当硬盘数据返回是，CPU会收到个 **中断**，于是CPU再继续运行这个进程。

[![image.png](https://i.postimg.cc/Y9FWHqmL/image.png)](https://postimg.cc/hzSj8nsK)

   这种 **多个程序，交替执行** 的思想，就是CPU管理多个进程的初步想法。对于一个支持多进程的系统，CPU会从一个进程快速切换至另一个进程，其间每个进程各运行几十或几百个毫秒。虽然单核CPU在某一个瞬间，智能运行一个进程，但在1秒钟其间，他可能会运行多个进程，这样产生 **并行的错觉** ，实际上这是 **并发**。

> 并发和并行有什么区别？

[![image.png](https://i.postimg.cc/gkqs6d2P/image.png)](https://postimg.cc/Ln5LrcPy)

> 进程与程序关系的类比

   晚饭时间，男生尝试给女生做法，在网上找到菜谱后，按着菜谱买了原料，然后边学菜谱边做菜。

[![image.png](https://i.postimg.cc/MpZGz0L8/image.png)](https://postimg.cc/KRVbNTF9)

   突然女生想喝饮料了，那么男生只好把做菜的事情暂停一下，并在手机菜谱上标记做到哪一个步骤，把状态信息记录下来，然后听从女生的指令跑去楼下买一瓶冰可乐后，又回到厨房继续做菜。

+ 这体现了，CPU可以从一个进程（做菜）切换到另外一个进程（买可乐），在切换前必须要记录当前进程中运行的状态信息，以备下次切换回来的时候可以恢复执行。所以，可以发现进程有着 **运行-暂停-运行** 的活动规律。

#### 进程的状态

> 在知道运行-暂停-运行的互动规律后。一般来说，一个进程并不是自始至终连续不停的运行的。他与并发执行中的其他进程的执行是相互制约的。他有事处于运行状态，有时由于某种原因而暂停处于等待状态，当使他暂停的原因消失后它又进入准备运行的状态。

   所以 **一个进程的活动其间至少具备三种基本状态，即运行状态、就绪状态、阻塞状态** 。

[![image.png](https://i.postimg.cc/K8J8j9k5/image.png)](https://postimg.cc/LJgp03Vq)

   上图中各个状态的意义：

+ 运行状态（Running）：该时刻进程占用CPU;
+ 就绪状态（Ready）：可运行，因调度选择另一个进程进入到就绪状态，当调度选择运行此进程时，会从就绪状态进入到运行状态。
+ 阻塞状态（Blocked）：该进程正在等待某一事件发生（如等待输入/输出操作的完成）而暂时停止运行，这时即使给他CPU控制权，它也无法运行；某个进程因为等待事件而进入阻塞状态；导致某个进程进入阻塞状态的事件完成后，该进程会进入到就绪状态；
+ 创建状态（new）：进程正在被创建时的状态；
+ 结束状态（Exit）：进程正在从系统中消失时的状态；

   于是一个完整的进程状态的变迁如下图：

[![image.png](https://i.postimg.cc/rFjZzbcs/image.png)](https://postimg.cc/tY1NMBsG)

   再来详细的说明一下进程的状态变迁：

| 第一状态 | 第二状态 | 发生原因                                                                                                                                                             |
| -------- | -------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| NULL     | 创建状态 | 一个新进程被创建时的第一个状态                                                                                                                                       |
| 创建状态 | 就绪状态 | 进入就绪队列；当进程被创建完成并被初始化后，一切准备就绪并运行是，变为就绪状态，这个过程很快                                                                         |
| 就绪状态 | 运行状态 | 被调度；处于就绪状态的进程被操作系统的进程调度器选中后，就分配给CPU正式运行该进程；                                                                                  |
| 运行状态 | 就绪状态 | 时间片用完；处于运行状态的进程在运行过程中，由于分配给它的时间片用完，操作系统会把该进程变为就绪态，接着从就绪态选中另外一个进程运行（由于外部原因导致进程切换状态） |
| 运行状态 | 阻塞状态 | 等待事件；当进程请求某个事件且必须等待时，例如请求I/O事件（由于进程自身内部原因导致进程切换状态）                                                                    |
| 阻塞状态 | 就绪状态 | 事件完成；当进程要等待的时间完成是，它从阻塞状态变为就绪状态；                                                                                                       |
| 运行状态 | 结束状态 | 结束；当进程已经运行完成或出错时，会被操作系统结束状态处理                                                                                                           |

   如果有大量处于阻塞状态的进程，进程可能会占用着物理内存空间，所以在 **虚拟内存管理的操作系统中。通常会把阻塞状态的进程的物理内存空间换出到硬盘，等需要再次运行的时候，再从硬盘换入到物理内存** 。

[![image.png](https://i.postimg.cc/DZSMR0dk/image.png)](https://postimg.cc/HcCzyphB)

   那么就需要一个新的状态，来 **描述进程没有占用实际的物理内存空间的情况，这个状态就是挂起状态** 。这跟阻塞状态是不一样，阻塞状态是等待某个事件的返回。另外，挂起状态可以分为两种：

+ 阻塞挂起状态：进程在外存（硬盘）并等待某个事件的出现；
+ 就绪挂起状态：进程在外存（硬盘），但只要进入内存，即刻立刻执行；

   新的状态图如下所示：

[![image.png](https://i.postimg.cc/J4jb7X17/image.png)](https://postimg.cc/tYC12YZ8)

导致进程挂起的原因不只是因为 **进程所用的内存空间不在物理内存** ，还包括如下情况：

+ 通过sleep让进程间歇性挂起，其工作原理是设置一个定时器，到期后唤醒进程。
+ 用户希望挂起一个程序的执行，比如在Linux中用 Ctrl+Z 挂起进程。

#### 进程的控制结构

> 在操作系统中，用 **进程控制块（process control block,PCB）** 数据结构来描述进程的。**PCB是进程存在的唯一标识**，这意味着一个进程的存在，必然会有一个PCB。

> PCB具体包含什么信息呢？

1. 进程描述信息：
   + 进程标识符：标识各个进程，每个进程都有一个并且唯一的标识符；
   + 用户标识符：进程归属的用户，用户标识符主要为共享和保护服务；
2. 进程控制和管理信息：
   + 进程当前状态，如new、ready、running、waiting、block
   + 进车优先级：进程抢占CPU时的优先级；
3. 资源分配清单：
   + 有关内存地址克难攻坚或虚拟地址空间的信息，锁打开文件的雷暴和所使用的的I/O设备信息。
4. CPU相关信息：
   + CPU中各个寄存器的值，当进程被切换时，CPU的状态信息都会被保存在相应的PCB中，以便进程重新执行时，能从断点处继续执行。

> 每个PCB是如何组织的呢？

   通常是通过 **链表** 的方式，进行组织，把具有 **相同转态的进程链在一起，组成各种队列** 。比如：

[![image.png](https://i.postimg.cc/JzctvcRJ/image.png)](https://postimg.cc/FYz9JSds)

   除了链表的组织方式，还有索引方式，它的工作原理：将同一状态的进程组织在一个索引表中，索引表项指向相同的PCB，不同转态对应不同的索引表。一般会选择链表，因为可能会面临进程创建，销毁等调度导致进程状态发生变化，所以链表能更加灵活的插入和删除。

#### 进程的控制

> 知道了进程的状态变迁和进程的数据结构PCB后，再来看看进程的 **创建、终止、阻塞、唤醒** 的过程，这些过程也就是进程的控制。

1. 创建进程

   操作系统允许一个进程创建另一个进程，而且允许子进程继承父进程所拥有的资源，当子进程被终止时，其在父进程所继承的资源应还给父进程。同时，终止父进程时也会终止其所有的子进程。

+ 为新进程分配一个唯一的进程标识号，并申请一个空白的PCB，PCB是有限的，若申请失败则创建失败；
+ 为进程分配资源，如果此处资源不足，进程就会进入等待状态，以等待资源；
+ 初始化PCB
+ 如果进程的调度队列能够接纳新进程，那就将进程插入到就绪队列，等待调度运行；

2. 终止进程

   进程可以由3种终止方式：正常结束、异常结束以及外界干越（信号Kill掉）

+ 查找需要终止的进程的PCB
+ 如果处于执行状态，则立即终止该进程的执行，然后将CPU资源分配给其他进程
+ 如果其还有子进程，则应将其所有子进程终止；
+ 将该进程所有用的全部资源都归还给父进程或操作系统；
+ 将其从PCB所在的队列 中删除。

3. 阻塞进程

   当进程需要等待某一事件完成时，他可以调用阻塞语句把自己阻塞等待。而一旦被阻塞等待，他只能由另一个进程唤醒。

   阻塞进程的过程如下：

+ 找到要被阻塞进程标识号对应的PCB;
+ 如果该进程为运行状态，则保护其现场，将其状态转换为阻塞状态，停止运行；
+ 奖盖PCB插入到阻塞队列中去。

4. 唤醒进程

   进程由 **运行** 转变为 **阻塞** 状态是由于进程必须等待某一事件的完成，所以处于阻塞状态的进程是绝对不可能叫醒自己的。如果某进程正在等待I/O事件，需由别的进程发消息给他，则只有当该进程所期待的事件出现时，才由发现者进程用唤醒语句叫醒它。

   唤醒进程的过程如下：

+ 在该事件的阻塞队列中找到相应进程的PCB;
+ 将其从阻塞队列中移出，并致其状态Wie就绪状态；
+ 把该PCB插入到就绪队列中，等迪奥调度程序调度；

   进程的阻塞和唤醒是一对功能相反的语句，如果某个进程调用了阻塞语句，则必由一个与之对应的唤醒语句。

#### 进程的上下文切换

> 各个进程之间是共享CPU资源的，在不同的时候，进程之间需要切换，让不同进程可以在CPU执行，那么这样 **一个进程切换到另一个进程运行，称为进程的上下文切换**。

> 在详细说进程上下文切换前，先看下CPU上下文切换

   大多数操作系统都是多任务系统，通常支持大于CPU数量的任务同时运行。实际上这些任务并不是同时运行的，知识因为系统在很短时间内，让各个任务分别在CPU运行，于是就造成同时运行的错觉。

   任务交给CPU运行，在每个任务运行前，需要知道任务从哪里加载，又从哪里开始运行。

   所以，操作系统需要事先帮CPU设置好 **CPU寄存器和程序计数器** 。

   CPU寄存器是CPU内部一个容量小，但是速度极快的内存（缓存），程序计数器则是用来存储CPU正在执行的或者即将执行的下一条指令位置。所以说， **CPU寄存器和程序计数器是CPU在运行任何任务前所必须依赖的环境，这个环境就叫做 CPU上下文** 。

   CPU上下文切换就是先把前一个任务的CPU上下文（CPU寄存器和程序计数器）保存起来，然后加载新的任务的上下文到这些寄存器和程序计数器，最后再跳到程序计数器所指的新位置，运行新任务。

   系统内核会存储保持下来的上下文信息，当次任务再次被分配给CPU运行时，CPU会重新加载这些上下文，这样就能保证原来的状态不受影响，让任务看起来还是继续运行。

   上面所说的任务，主要包含进程，线程和中断，所以，可以根据任务的不同，把CPU上下文切换分成：**进程上下文切换，线程上下文切换和中断上下文切换**。通常会把交换的信息保存在进程的PCB，当要运行另外一个进程的时候，需要从这个进程的PCB取出上下文，然后恢复到CPU中，这使得这个进程可以继续执行，如下图所示：

[![image.png](https://i.postimg.cc/zvHh2NK0/image.png)](https://postimg.cc/wRH33SWm)

  进程上下文开销很关键，越小越好，避免耗费开销在上下文切换上。

> 发生进程的上下文切换场景有哪些？

1. 为保证所有进程可以得到公平调度，CPU时间被划为一段段时间片，轮流分配给每个进程，当某个进程时间片耗尽，进程就从运行态转变为就绪态，系统从就绪态队列选择另外一个进程执行；
2. 进程在系统资源不足（比如内存不足）时，要等到资源满足后才可以运行，这个时候进程也会被挂起，并由系统调度其他进程运行；
3. 当进程通过睡眠函数sleep这样的方法，将自己主动挂起时，自然也会重新调度；
4. 当有优先级更高的进程运行时，为了保证高优先级进程的运行，当前进程会被挂起，由高优先级进程来运行；
5. 当发生硬件中断时，CPU上的进程会被中断挂起，转而执行内核中的中断服务程序。

### 线程

   早期操作系统中都是以进程作为独立运行的基本单位，后来又提出了更小的能独立运行的基本单位，也就是线程。

#### 为什么使用线程

   如果编写一个视频播放器软件，该软件功能的核心模块有三个：

+ 从视频文件中读取数据；
+ 对读取的数据进行解压缩
+ 把解压缩后的数据播放出来；

   对于单进程的实现方式，会以以下方式运行：

[![image.png](https://i.postimg.cc/4N3y7d7t/image.png)](https://postimg.cc/PNBT0dMr)

   对于单进程的这种方式，存在以下问题：

+ 播放出来画面和声音不连贯，CPU能力不强是，Read的时候进程可能会卡住；
+ 各个函数之间不是并发执行，影响资源的使用效率；

   改成多进程的方式：

[![image.png](https://i.postimg.cc/XYvqTvcx/image.png)](https://postimg.cc/N5WQXBnr)

   依然会存在问题：

+ 进程之间如何通信，共享数据？
+ 维护进程的系统开销比较大，创建进程时，分配资源，建立PCB；终止进程时，回收资源、撤销PCB；进程切换时保护当前进程的状态信息；

   如何解决以上问题？需要一种新的实体，满足以下特性：

+ 实体之间可以并发运行；
+ 实体之间共享相同的地址空间；

   这个新的实体就是 **线程（Thread）** ，线程之间可以并发运行且共享相同的地址空间。

#### 什么是线程

> **线程是进程当中的一条执行流程**。

   同一个进程多个线程之间可以共享代码段、数据段、打开的文件等资源，但每个线程各自都有一套独立的寄存器和栈，这样可以确保线程的控制流都是相对独立的。

[![image.png](https://i.postimg.cc/bvmwLf2W/image.png)](https://postimg.cc/d7TFtX6j)

> 线程的优缺点？

   线程的优点

+ 一个进程中可以同时存在多个线程；
+ 各个线程之间可以并发执行；
+ 各个线程之间可以共享地址空间和文件等资源

   线程的缺点

+ 当进程中的一个线程崩溃时，会导致其所属进程的所有线程崩溃

#### 线程与进程的比较

   进程与线程的比较：

+ 进程时资源（包括内存、打开的文件等）分配的单位，线程是CPU调度的单位；
+ 进程拥有一个完整的资源平台，而现场制度相必不可少的资源，如寄存器和栈；
+ 线程同样具有就绪、阻塞、执行三种基本状态，同样具有状态之间的转换关系。
+ 线程能减少并发执行的时间和空间开销；

   对于线程能比进程减少开销，体现在：

+ 线程的创建时间比进程块，因为进程在创建的过程中，还需要资源管理信息，比如内存管理信息，文件管理嘻嘻，而线程在创建的过程中，不会涉及到这些资源管理信息，而是共享他们；
+ 线程的终止时间比进程快，因为线程释放的资源相比进程少很多；
+ 同一个进程内的线程切换比进程切换快，因为线程具有相同的地址空间（虚拟内存共享），这意味着同一进程的线程都具有同一个页表，那么在切换的时候不需要切换页表。而对于进程之间的切换，切换的时候要把页表切换掉，而页表的切换过程开销是比较大的。
+ 由于同一进程的各个线程共享内存和文件资源，那么在线程之间数据传递的时候，就不需要经过内核了，这就使得线程之间的数据交互效率更高了。

   所以不管是时间效率，还是空间效率，线程都比进程要高。

#### 线程的上下文切换

> 线程和进程的最大区别在于：**线程是调度的基本单位，而进程则是资源拥有的基本单位**。

   所以，所谓操作系统的任务调度，实际上调度对象是线程，而进程只是给线程提供了虚拟内存、全局变量等资源。

+ 当进程只有一个线程时，可以认为进程就等于线程
+ 当进程拥有多个线程时，这些线程就会共享相同的虚拟内存和全局变量等资源，这些资源在上下文切换时是不需要修改的；

   另外线程也有自己的私有数据，比如栈和寄存器等，这些在上下文切换时也是需要保存的。

> 线程上下文切换的是什么？

+ 当两个线程不是属于同一个进程，则切换的过程就跟进程上下文切换一样；
+ 当两线程属于同一个进程，因为虚拟内存是共享的，，所以在切换时，虚拟内存这些资源就保持不动，只需要切换线程的私有数据，寄存器等不共享的数据；

#### 线程的实现

1. 用户线程（User Thread）：在用户空间实现的线程，不是由内核管理的线程，是由用户态的线程库来完成线程的管理；
2. 内核线程（Kernel Thread）：在内核中实现的线程，是由内核管理的线程；
3. 轻量级线程（LightWeight Process）：在内核中来支持用户线程；

   用户线程和和内核线程的关系：

1. 多对一的关系，多个用户线程对应同一个内核线程：
2. 一对一的关系，一个用户线程对应一个内核线程；
3. 多对多的关系，多个用户线程对应到多个内核线程；

[![image.png](https://i.postimg.cc/XJQ4j3Zw/image.png)](https://postimg.cc/k66ks0v4)

> 用户线程如何理解？有什么优势和缺陷？

   用户线程是基于用户态的线程管理库来实现的，那么 **线程控制块（Thread Control Block,TCB）** 也是在库里面来实现的，对于操作系统而言是看不到这个TCB的，他只能看到整个进程的PCB。

   所以，**用户线程的整个线程管理和调度，操作系统是不直接参与的，而是由用户级线程库函数来完成线程的管理，包括线程的创建、终止、同步和调度等**。

   用户级线程的模型，也就类似前面提到的 **多对一** 关系，即多个用户线程对应同一个内核线程，如下图所示

[![image.png](https://i.postimg.cc/CMXZ8TLF/image.png)](https://postimg.cc/QVgxLzTP)

   用户线程的优点：

+ 每个进程都需要有它私有的线程控制块（TCB）列表，用来跟踪记录它各个线程的状态信息（PC、栈指针、寄存器），TCB由用户级线程函数来维护，可用于支持线程技术的操作系统；
+ 用户线程的切换也是由线程函数库来完成的，无需用户与内核态的切换，所以速度特别快；

   用户线程的缺点：

+ 由于操作系统不参与线程的调度，如果一个线程发起了系统调用而阻塞，那进程所包含的用户线程都不能执行了。
+ 当一个线程开始运行后，除非他主动交出CPU的使用权，否则他所在进程当中的其他线程无法运行，因为用户态的线程没法打断他、当前运行中的线程，他没有这个特权，只有操作系统才由，但是用户线程不是由操作系统管理的。
+ 由于时间片分配给进程，故与其他进程比，在多线程执行时，每个线程得到的时间片比较少，执行会比较慢；

> 内核线程如何理解？存在什么优势和缺陷？

   **内核线程都是由操作系统管理的，线程对应的TCB自然是放在操作系统里的，这样线程的创建、终止和管理都是由操作系统负责**。内核线程的模型，也就类似前面提到的 **一对一** 关系，即一个用户对应一个内核线程，如下图所示：

[![image.png](https://i.postimg.cc/284GyJVV/image.png)](https://postimg.cc/tY4WmBdj)

   内核线程的优点：

+ 在一个进程中，如果某个内核线程发起系统调用而被阻塞，并不会影响其他内核线程的运行；
+ 分配给线程，多线程的进程获得更多的CPU运行时间；

   内核线程的缺点：

+ 在支持内核线程的操作系统中，由内核来维护进程和线程的上下文信息，如PCB和TCB;
+ 线程的创建、终止和切换都是通过系统调用的方式来运行，因此对应系统来说，系统开销比较大；

> 轻量级进程如何理解？

   **轻量级进程（Light-weight process,LWP）是内核支持的用户线程，一个进程可以有一个或多个LWP，每个LWP是跟内核线程一对一映射的，也就是LWP都是有一个内核线程支持**。

   大多数系统中，**LWP与普通进程的区别在于它只有一个最小的执行上下文和调度程序所需的统计信息**。⼀般来说，⼀个进程代表程序的⼀个实例，⽽ LWP 代表程序的执⾏线程，因为⼀个执⾏线程不像进程那样需要那么多状态信息，所以 LWP 也不带有这样的信息。

   在LWP之上也是可以用户线程的，那么LWP与用户线程的对应关系就由三种：

+ 1:1，即一个LWP对应一个用户线程；
+ N:1，即N个LWP对应一个用户线程；
+ M:N，即M个LWP对应N个用户线程；

[![image.png](https://i.postimg.cc/hvYskz4w/image.png)](https://postimg.cc/1VpD6zqc)

+ 1:1模式

   ⼀个线程对应到⼀个 LWP 再对应到⼀个内核线程，如上图的进程 4，属于此模型。

+ 优点：实现并⾏，当⼀个 LWP 阻塞，不会影响其他 LWP；
+ 缺点：每⼀个⽤户线程，就产⽣⼀个内核线程，创建线程的开销较⼤
+ N:1模式

   多个⽤户线程对应⼀个 LWP 再对应⼀个内核线程，如上图的进程 2，线程管理是在⽤户空间完成的，此模式中⽤户的线程对操作系统不可⻅。.

+ 优点：⽤户线程要开⼏个都没问题，且上下⽂切换发⽣⽤户空间，切换的效率较⾼；
+ 缺点：⼀个⽤户线程如果阻塞了，则整个进程都将会阻塞，另外在多核 CPU 中，是没办法充分利⽤CPU 的。
+ M:N模式

   根据前⾯的两个模型混搭⼀起，就形成 M:N 模型，该模型提供了两级控制，⾸先多个⽤户线程对应到多个 LWP， LWP 再⼀⼀对应到内核线程，如上图的进程 3。

+ 优点：综合了前两种优点，⼤部分的线程上下⽂发⽣在⽤户空间，且多个线程⼜可以充分利⽤多核CPU 的资源。
+ 组合模式

   如上图的进程 5，此进程结合 1:1 模型和 M:N 模型。开发⼈员可以针对不同的应⽤特点调节内核线程的数⽬来达到物理并⾏性和逻辑并⾏性的最佳⽅案。

### 调度

> 进程希望自己能占用CPU进行工作，一旦操作系统把进程切换到运行状态，也就意味着该进程占用CPU在执行，但是当操作系统把进程切换到其他状态时，那就不在CPU中执行了，于是操作系统会选择下一个要运行的进程。选择一个进程运行这一功能是在操作系统中完成的，通常称为**调度程序（scheduler）**。

#### 调度时机

> 在进程的声明周期中，当进程从一个运行状态到另一状态变化的时候，其实会触发一次调度。

   比如，以下状态的变化都会触发操作系统的调度

+ 从就绪态 -> 运行态
+ 从运行态 -> 阻塞态
+ 从运行态 -> 结束态

   另外，如果硬件时钟提供某个频率的周期性中断，那么可以根据如何处理时钟中断，把调度算法分为两类：

+ **非抢占式调度算法** 挑选一个进程，然后让该进程运行直到被阻塞，或者直到该进程退出，才会调用另外一个进程，也就是说不会理时钟中断这个事情。
+ **抢占式调度算法** 挑选一个进程，然后让该进程只运行某段时间，如果在该时段结束时，该进程任然在运行，则会把它挂起，接着调度程序会从就绪队列挑选另外一个进程。这种抢占式调度处理，需要在时间间隔的末端发生 **时钟中断**，以便把CPU控制返回给调度程序进行调度，也就是常说的 **时间片机制**。

#### 调度原则

1. 如果运行的程序，发生了I/O时间的请求，那CPU使用率必然会很低，因为此时进程在阻塞等待硬盘的数据返回。这样的过程，势必会造成CPU突然的空闲。所以，**为了提高CPU利用率，在这种发送I/O事件致使CPU空闲的情况下，调度程序需要从就绪队列中选择一个进程来运行**。
2. 有的程序执行某个任务花费的时间会比较长，如果这个程序一直占着CPU，会造成系统吞吐量（CPU在单位时间内完成的进程数量）的降低。所以，**要提高系统的吞吐率，调度程序要权衡长任务和短任务进程的运行完成数量**。
3. 从进程开始到结束的过程中，实际上是包含两个时间，分别是进程运行时间和进程等待时间，这两个时间总和就称为周转时间。进程的周转时间越小越好，**如果进程的等待时间很长而运行时间很短，那周转时间就很长，这不是我们所期望的，调度程序应避免这种情况发生。
4. 处于就绪队列的进程，也不能等太久，当然希望这个等待的时间越短越好，这样可以使得进程更快的在CPU中执行。所以 **就绪队列中进程的等待时间也是调度程序所需要考虑的原则**。
5. 对于鼠标、键盘这种交互式比较强的应用，希望它的响应时间越快越好，否则影响用户体验。所以，**对于交互式比较强的应用，响应时间也是调度程序需要考虑的原则**。

   针对以上五种调度原则，总结如下：

+ CPU利用率：调度程序应确保CPU是始终匆忙的状态，这可提高CPU的利用率；
+ 系统吞吐率：吞吐量表示的是单位时间内CPU完成进程的数量，长作业的进程会占用较长的CPU资源，因此会降低吞吐量，相反，短作业的进程会提升系统吞吐量；
+ 周转时间：周转时间是进程运行和阻塞时间中能总和，一个进程的周转时间越小越好；
+ 等待时间：这个等待时间不是阻塞状态的时间，而是进程处于就绪队列的时间，等待时间越长，用户越不满意。
+ 响应时间：用户提交请求到系统第一次产生响应所花费时间，在交互式系统中，响应时间是衡量调度算法好坏的主要标准。

#### 调度算法

##### 单核CPU系统中常见的调度算法

> 1.先来先服务调度算法

   最简单的一个调度算法，就是非抢占式的 **先来先服务（First Come First Served,FCFS）** 算法；

[![image.png](https://i.postimg.cc/65TMLm49/image.png)](https://postimg.cc/0bRG9ZC3)

   先来后到， **每次从就绪队列宗选择最先进入队列的进程，然后一直运行，直到进程退出或被阻塞，才会继续从队列中选择第一个进程接着运行** 。

> 2.最短作业优先调度算法

   **最短作业优先（Shortest Job First,SJF）调度算法，优先选择运行时间最短的进程来运行**，有助于提高系统吞吐量。

[![image.png](https://i.postimg.cc/RZWsLb87/image.png)](https://postimg.cc/CRVsFJw5)

   这显然对长作业不利，很容易造成一种极端现象，如果一个长作业在就绪队列等待运行，而这个就绪队列有非常多的短作业，那么就会使得长作业不断的往后推，致使长作业长期不会被运行。

> 3.高响应比优先调度算法

   之前的先来先服务调度算法和最短作业优先调度算法，都没有很好的权衡短作业和长作业，那么**高响应比优先（Highest Response Ratio Next,HRRN）调度算法**，主要是权衡了短作业和长作业。**每次进行进程调度时，先计算 响应比优先级 ，然后把 响应比优先级 最高的进程投入运行**，响应比优先级的计算公式：***优先权=（等待时间+要求服务时间）/要求服务时间***。

   从上面公式可以发现：

+ 如果两个进程的 **等待时间相同** 时，要求的 **服务时间越短，响应比就越高** ，这样 **短作业的进程容易被选中运行** 。
+ 如果两个进程 **要求服务时间相同时** ，**等待时间越长，响应比越高** ，这就 **兼顾到了长作业进程** ，因为进程的响应比可以随着时间等待的增加而提高，当其等待时间足够长是，其响应时间便可以升到很高，从而获得运行的机会；

> 4.时间片轮转调度算法

   最简单、最公平且使用最广泛的算法就是 **时间片轮转（Round Robin,RR）调度算法。

[![image.png](https://i.postimg.cc/MTrzc8Xn/image.png)](https://postimg.cc/hzxkw6Ln)

   **每个进程被分配一个时间段，称为时间片（Quantun）即允许该进程在该时间段中运行**。

+ 如果时间片用完，进程还在运行，将把此进程从CPU释放出来，并把CPU分配给另外一个进程；
+ 如果该进程在时间片结束前阻塞或结束，则CPU立即进行切换；

   另外，时间片的长度就是一个很关键的点：

+ 如果时间片设的太短会导致过多的进程上下文切换，降低了CPU效率；
+ 如果时间片设的太长又可能引起对短作业进程的响应时间边长。
+ 一般来说，时间片设为 **20ms-50ms** 通常是一个比较合理的折中值。

> 5.最高优先级调度算法

   时间片轮转算法做了个假设，揖让所有进程同等重要，谁也不偏袒，大家的运行时间都一样。但是，对于多用户计算机系统就有不同的看法了，他们希望调度是有优先级的，即希望调度能 **从就绪队列中选择最高优先级的进程进行运行，这称为最高优先级（Highest Priority First,HPF）调度算法** 。进程的优先级可以分为，静态优先级和动态优先级：

+ 静态优先级：创建进程的时候，就已经确定了优先级，然后整个运行时间，优先级都不会变化。
+ 动态优先级：根据进程的动态变化调整优先级，比如如果进程时间增加，则将低优先级，如果进程等待时间（就绪队列的等待时间）增加，则升高其优先级，也就是 **随着时间的推移增加等待进程的优先级**。

   该算法也有两种处理优先级高的方法，非抢占式和抢占式：

+ 非抢占式：当就绪队列中出现优先级高的进程，运行完当前进程，在选择优先级高的进程。
+ 抢占式：当就绪队列中出现优先级高德进程，当前线程挂起，调度优先级高的进程运行。

   但是依然有缺点，可能会导致低优先级的进程永远不会运行。

> 多级反馈调度算法

   **多级反馈队列（Multilevel Feedback）调度算法** 是**时间片轮转算法** 和 **最高优先级算法** 的综合和发展。

+ **多级** 表示有多个队列，每个队列的优先级从高到低，同时优先级越高时间片越短。
+ **反馈** 表示如果有新的进程加入优先级高的队列是，立刻停止当前正在运行的进程，转而去运行优先级高的队列。

[![image.png](https://i.postimg.cc/tC3yGcFG/image.png)](https://postimg.cc/BXnRxMhm)

+ 设置多个队列，赋予每个队列不同的优先级，每个 **队列优先级从高到低，同时优先级越高，时间片越短**；
+ 新的进程会被放入到第一级队列的末尾，按照先来先服务的原则等待被调度，如果在第一级队列规定的时间片没运行完成，则停止当前运行的进程，并将其转入到第二队列的末尾，以此类推，直至完成；
+ 当较⾼优先级的队列为空，才调度较低优先级的队列中的进程运⾏。如果进程运⾏时，有新进程进⼊较⾼优先级的队列，则停⽌当前运⾏的进程并将其移⼊到原队列末尾，接着让较⾼优先级的进程运⾏；

   可以发现，对于短作业可能可以在第⼀级队列很快被处理完。对于⻓作业，如果在第⼀级队列处理不完，可以移⼊下次队列等待被执⾏，虽然等待的时间变⻓了，但是运⾏时间也变更⻓了，所以该算法很好的 **兼顾了⻓短作业，同时有较好的响应时间**。

## 进程间通信

   每个进程的用户地址空间都是独立的，一般而言是不能互相访问的，但内核空间每个进程都是共享的，所以进程之间要通信必须通过内核。

[![image.png](https://i.postimg.cc/7YDpvnD5/image.png)](https://postimg.cc/5j7PLvXJ)

### 管道

```sh
$ ps auxf | grep mysql
```

> Linux中的 ** | ** 管道，就是将前一个命令（ps auxf）的输出作为后一个命令（grep mysql）的输入，从这可以看出，**管道传输数据是单向的**，如果想互相通信需要建立两个管道。上面这种管道是没有名字的，所以 **|** 表示的管道称为 **匿名管道** ，用完就销毁。管道还有另外一个类型是 **命名管道** ，也被叫做 **FIFO** ，因为数据是先进先出的传输方式。在使用命名管道前，先需通过 **mkfifo** 命令来创建，并且指定管道名字：

```sh
$ mkfifo myPipe
```

   myPipe就是这个管道的名称，基于Linux一切皆文件的理念，所以管道也是以文件的方式存在，我们可以用ls来看一下这个文件的类型是p，也就是pipe（管道）的意思：

```sh
$ ls -l
$ prw-r--r--   1 root root    0 Feb  9 02:52 myPipe
```

   接下来，我们往myPipe这个管道写入数据，操作完后发现命令行停在这里，这是因为管道里的内容没有被读取，只有当管道里的数据被读完后，命令才可以正常退出。于是，可以执行另一个命令来读取管道里的数据。可以看到 **管道这样的通信方式效率低，不适合进程间频繁的交换数据**。

```sh
$ echo "hello" > myPipe
^C/usr/bin/sh: 43: cannot create myPipe: Interrupted system call

$ cat < myPipe // 读取管道⾥的数据
hello
```

### 消息队列

> 消息队列的通信模式可以解决管道效率低的问题。⽐如， A 进程要给 B 进程发送消息， A 进程把数据放在对应的消息队列后就可以正常返回了， B 进程需要的时候再去读取数据就可以了。同理， B 进程要给 A 进程发送消息也是如此。

   **消息队列是保存在内核中的消息链表**，在发送数据时，会分成一个一个独立的数据单元，也就是消息体（数据块），消息体是用户自定义的数据类型，消息的发送方和接收方要约定好消息体的数据类型，所以每个消息体都是固定⼤⼩的存储块，不像管道是⽆格式的字节流数据。如果进程从消息队列中读取了消息体，内核就会把这个消息体删除。

   消息队列⽣命周期随内核，如果没有释放消息队列或者没有关闭操作系统，消息队列会⼀直存在，⽽前⾯
提到的匿名管道的⽣命周期，是随进程的创建⽽建⽴，随进程的结束⽽销毁。

   消息这种模型，两个进程之间的通信就像平时发邮件⼀样，你来⼀封，我回⼀封，可以频繁沟通了。但邮件的通信⽅式存在不⾜的地⽅有两点， **⼀是通信不及时，⼆是附件也有⼤⼩限制** ，这同样也是消息队列通信不⾜的点。

   **消息队列不适合⽐较⼤数据的传输**，因为在内核中每个消息体都有⼀个最⼤⻓度的限制，同时所有队列所包含的全部消息体的总⻓度也是有上限。在 Linux 内核中，会有两个宏定义 **MSGMAX和MSGMNB**，它们 **以字节为单位**，分别定义了 **⼀条消息的最⼤⻓度和⼀个队列的最⼤⻓度**。

   **消息队列通信过程中，存在⽤户态与内核态之间的数据拷⻉开销**，因为进程写⼊数据到内核中的消息队列时，会发⽣从⽤户态拷⻉数据到内核态的过程，同理另⼀进程读取内核中的消息数据时，会发⽣从内核态拷⻉数据到⽤户态的过程。

### 共享内存

> 消息队列的读取和写入的过程，都会有用户态与内核态之间的消息拷贝过程。那 **共享内存** 的方式，就很好的解决了这一问题。

   **共享内存机制，就是拿出一块虚拟地址空间来，映射到相同的物理内存中**。这样这个进程写入的东西，另外一个进程马上就能看到，不需要拷贝，传输，大大提高了进程间通信的速度。

[![image.png](https://i.postimg.cc/1t3HSBMK/image.png)](https://postimg.cc/v1C9LWJ1)

### 信号量

   用了共享内存通信方式，带来新的问题，就是如果多个进程同时修改同一个贡献内存，很有可能就会冲突。例如两个进程都同时写一个地址，先写的那个进程发现内容被别人覆盖了。

   为了防止多进程竞争共享资源，而造成数据错了，所以需要保护机制，使得贡献的资源，在任意时刻只能被一个进程访问。正好，**信号量**就实现了这一保护机制。

   **信号量其实是一个整形的计数器，主要用于实现进程间的互斥与同步，而不是用户缓存进程间通信的数据**。

   信号量表示资源的数量，控制信号量的方式有两种原子操作：

+ 一个是 **P操作** ，这个操作会把 **信号量减去1** ，相减后如果信号量<0，则表明资源以备占用，进程需阻塞等待；相减后如果信号量>=0，则表明还有资源可使用，进程可正常继续执行。
+ 一个是 **V操作** ，这个操作会把 **信号量加上1** ，相加后如果信号量<=0，则表明当前有阻塞中的进程，于是会把该进程唤醒运行；相加后如果信号量>0，则表明当前没有阻塞中的进程；

   **P操做是用在进入共享资源之前，V操作是用在离开共享资源之后，这两个操作必须是成对出现的**。

   举例：如果使得两个进程互斥访问共享内存，我们可以初始化信号量为1。

[![image.png](https://i.postimg.cc/QCzG1Sf8/image.png)](https://postimg.cc/Fk0BQbt8)

   具体的过程如下：

+ 进程 A 在访问共享内存前，先执⾏了 P 操作，由于信号量的初始值为 1，故在进程 A 执⾏ P 操作后信号量变为 0，表示共享资源可⽤，于是进程 A 就可以访问共享内存。
+ 若此时，进程 B 也想访问共享内存，执⾏了 P 操作，结果信号量变为了 -1，这就意味着临界资源已被占⽤，因此进程 B 被阻塞。
+ 直到进程 A 访问完共享内存，才会执⾏ V 操作，使得信号量恢复为 0，接着就会唤醒阻塞中的线程B，使得进程 B 可以访问共享内存，最后完成共享内存的访问后，执⾏ V 操作，使信号量恢复到初始值 1。

   可以发现，**信号初始化为 1 ，就代表着是互斥信号量，它可以保证共享内存在任何时刻只有⼀个进程在访问，这就很好的保护了共享内存**。

   另外在多进程里，每个进程并不一定是顺序执行的，他们基本是是各自独立的、不可预知的速度向前推进，又希望多个进程能紧密合作，实现共同任务；

   例如，进程 A 是负责⽣产数据，⽽进程 B 是负责读取数据，这两个进程是相互合作、相互依赖的，进程 A必须先⽣产了数据，进程 B 才能读取到数据，所以执⾏是有前后顺序的。

[![image.png](https://i.postimg.cc/Xv39NhrS/image.png)](https://postimg.cc/87K7tZdt)

   具体过程：

+ 如果B比进程A先执行，那么执行到P操作是，由于信号量初始值为0，故信号量变为-1，表示进程A还没产生数据，于是B阻塞等待；
+ 接着，当进程A生产完数据后，执行V操作，就会使得信号变为0，于是就会唤醒阻塞在P操作的进程B;
+ 最后，进程B被唤醒后，意味着进程A已经生产了数据，于是进程B就可以正常读数据了。

   可以发现，**信号初始化为0，就代表着是同步信号量，可以保证进程A应在进程B之前运行**。

### 信号

> 上面说的进程间通信，都是常规状态下的工作模式。对于 **异常情况下的工作模式，就需要用信号的方式来通知进程**。信号跟信号量虽然名字相似，但是两者用途完全不一样，就像Java和JavaScript的区别。

   在linux操作系统中，为了相应各种各样的时间，提供了几十种信号，分别代表不同的意义，我们可以通过kill -l命令，查看所有信号：

```sh
$ kill -l
 1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
 6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
63) SIGRTMAX-1	64) SIGRTMAX
```

   运行在shell中断的进程，我们可以通过键盘输入某些组合键的时候，给进程发送信号。例如：

+ Ctrl + C 产生 **SIGINT** 信号，表示终止该进程；
+ Ctrl + Z 产生 **SIGSTP** 信号，表示停止该进程，但还未结束；

   如果进程在后台运行，可以通过kill命令的方式给进程发送信号，但前提需要知道运行中的进程PID号，例如：

```sh
# 给PID为1050的进程发送 SIGKILL信号，用来立即结束该进程
$ kill -9 1050
```

   所以，**信号事件的来源主要有硬件来源（如键盘Ctrl+C）和软件来源（如kill命令）**。

   信号是进程间通信机制中 **唯一的异步通信机制**，因为可以在任何时候发送信号给某一线程，一旦有信号产生，我们就有下面这几种，用户进程对信号的处理方式。

1. 执行默认操作。Linux对每种信号都规定了默认操作，例如上面列表中的SIGTERM信号，就是终止进程的意思。
2. 捕捉信号。我们可以为信号定义一个信号处理函数。当信号发生时，我们就执行相应的信号处理函数。
3. 忽略信号。当我们不希望处理某些信号的时候，就可以忽略该信号，不做任何处理。有两个信号是应用进程无法捕捉和忽略的，即 **SIGKILL(kill)和SIGSTOP** ，他们用于在任何时候中断或结束某一进程。

### Socket

   前面提到的管道、消息队列、共享内存、信号量和信号都是在同一台主机上进行进程间通信，那要想 **跨网络与不同主机上的进程之间通信，就需要socket通信了**。

   实际上，socket通信不仅可以跨网络与不同主机的进程间通信，还可以在同主机上进程间通信。我们来看socket的系统调用：

```c
int socket(int domain,int type,int protocal)
```

   三个参数分别代表：

+ domain参数用来指定协议族，比如AF_INET用于IPV4、AF_INET6用于IPV6、AF_LOCAL/AF_UNIX用于本机；
+ type参数用来指定通信特性，比如SOCK_STAERM表示的是字节流，对应TCP;SOCK_DREAM表示的是数据报，对应UDP；SOCK_RAW表示的是原始套接字；
+ protocol参数原本是用来指定通信协议的，但现在基本废弃。因为协议已经通过前面两个参数指定完成，protocol目前一般写成0即可；

   根据创建socket类型的不同，通信的方式也就不同：

+ 实现TCP字节流通信：socket类型是AF_INET和SOCK_STREAM;
+ 实现UDP数据报通信：socket类型是AF_INET和SOCK_DGRAM;
+ 实现本地进程间通信：socket类型是AF_LOCAL和SOCK_STREAM，AF_LOCAL和SOCKET_DGRAM。另外AF_UNIX和AF_LOCAL是等价的，所以AF_UNIX也属于本地SOCKT;

> 针对TCP协议通信的socket编程模型

[![image.png](https://i.postimg.cc/bwBM3gX4/image.png)](https://postimg.cc/G4vqpkmj)

+ 服务端和客户端初始化socket，得到文件描述符；
+ 服务端调用bind，将绑定在ip地址和端口；
+ 服务端调用listen，进行监听；
+ 服务端调用accept，等待客户端连接；
+ 客户端调用connect，向服务器端的地址和端口发起连接请求；
+ 服务端accept返回用于传输的socket的文件等描述符；
+ 客户端调用write写入数据；服务调用read读取数据；
+ 客户端断开连接时，调用close，那么服务端read读取数据的时候，就会读取到EOF，待处理完数据后，服务端调用close，表示连接关闭。
+ 这里需要注意的是，服务端调用accept时，连接成功了会返回一个已完成连接的socket，后续用来传输数据。

   所以监听的socket和真正用来传输数据的socket，是 2个socket，一个叫做 **监听socket** ，一个叫做 **已完成连接socket** 。

> 针对UDP协议通信的socket编程模型

[![image.png](https://i.postimg.cc/MHnQw1KM/image.png)](https://postimg.cc/jnr5Qwft)

   UDP是没有连接的，所以不需要三次握手，也就不需要像TCP调用listen和connect，但是UDP的交互任然需要IP地址和端口号，因此也需要bind。对于UDP来说不需要维护连接，也就没有所谓的发送方和接收方，甚至都不需要客户端和接收端的概念，只要有一个socket多台机器就可以任意通信，因此每一个UDP的socket都需要bind。另外每次通信时调用sendto和recvfrom，都要传入目标主机的IP和端口。

> 针对本地进程间通信的socket编程模型

   本地socket 被用于在 **同一台主机上进程间通信** 的场景

+ 本地socket的编程接口和IPV4、IPV6套接字编程接口是一致的，可以支持 **字节流** 和 **数据报** 两种协议；
+ 本地socket的实现效率高于IPV4、IPV6的字节流、数据报socket实现。

   对于本地字节流 socket，其 socket 类型是 AF_LOCAL 和 SOCK_STREAM。对于本地数据报 socket，其 socket 类型是 AF_LOCAL 和 SOCK_DGRAM。

   本地字节流socket和本地数据报socket在bind的时候，不像TCP和UDP要绑定IP地址和端口，而是 **绑定一个本地文件**，这也就是他们之间的最大区别。

### 总结

   由于每个进程的⽤户空间都是独⽴的，不能相互访问，这时就需要借助内核空间来实现进程间通信，原因很简单，每个进程都是共享⼀个内核空间。
   Linux 内核提供了不少进程间通信的⽅式，其中最简单的⽅式就是管道，管道分为「匿名管道」和「命名管道」。

   匿名管道顾名思义，它没有名字标识，匿名管道是特殊⽂件只存在于内存，没有存在于⽂件系统中， shell命令中的「 | 」竖线就是匿名管道，通信的数据是⽆格式的流并且⼤⼩受限，通信的⽅式是单向的，数据只能在⼀个⽅向上流动，如果要双向通信，需要创建两个管道，再来匿名管道是只能⽤于存在⽗⼦关系的进程间通信，匿名管道的⽣命周期随着进程创建⽽建⽴，随着进程终⽌⽽消失。

   命名管道突破了匿名管道只能在亲缘关系进程间的通信限制，因为使⽤命名管道的前提，需要在⽂件系统创建⼀个类型为 p 的设备⽂件，那么毫⽆关系的进程就可以通过这个设备⽂件进⾏通信。另外，不管是匿名管道还是命名管道，进程写⼊的数据都是缓存在内核中，另⼀个进程读取数据时候⾃然也是从内核中获取，同时通信数据都遵循先进先出原则，不⽀持 lseek 之类的⽂件定位操作。

   消息队列克服了管道通信的数据是⽆格式的字节流的问题，消息队列实际上是保存在内核的「消息链表」，消息队列的消息体是可以⽤户⾃定义的数据类型，发送数据时，会被分成⼀个⼀个独⽴的消息体，当然接收数据时，也要与发送⽅发送的消息体的数据类型保持⼀致，这样才能保证读取的数据是正确的。消息队列通信的速度不是最及时的，毕竟每次数据的写⼊和读取都需要经过⽤户态与内核态之间的拷⻉过程。

   共享内存可以解决消息队列通信中⽤户态与内核态之间数据拷⻉过程带来的开销， 它直接分配⼀个共享空间，每个进程都可以直接访问，就像访问进程⾃⼰的空间⼀样快捷⽅便，不需要陷⼊内核态或者系统调⽤，⼤⼤提⾼了通信的速度，享有最快的进程间通信⽅式之名。但是便捷⾼效的共享内存通信， 带来新的问题，多进程竞争同个共享资源会造成数据的错乱。

   那么，就需要信号量来保护共享资源，以确保任何时刻只能有⼀个进程访问共享资源，这种⽅式就是互斥访问。 信号量不仅可以实现访问的互斥性，还可以实现进程间的同步，信号量其实是⼀个计数器，表示的是资源个数，其值可以通过两个原⼦操作来控制，分别是 P 操作和 V 操作。

   与信号量名字很相似的叫信号，它俩名字虽然相似，但功能⼀点⼉都不⼀样。信号是进程间通信机制中唯⼀的异步通信机制，信号可以在应⽤进程和内核之间直接交互，内核也可以利⽤信号来通知⽤户空间的进程发⽣了哪些系统事件，信号事件的来源主要有硬件来源（如键盘 Cltr+C ）和软件来源（如 kill 命令），⼀旦有信号发⽣， 进程有三种⽅式响应信号 1. 执⾏默认操作、 2. 捕捉信号、 3. 忽略信号。有两个信号是应⽤进程⽆法捕捉和忽略的，即 SIGKILL 和 SEGSTOP ，这是为了⽅便我们能在任何时候结束或停⽌某个进程。

   前⾯说到的通信机制，都是⼯作于同⼀台主机，如果要与不同主机的进程间通信，那么就需要 Socket 通信了。 Socket 实际上不仅⽤于不同的主机进程间通信，还可以⽤于本地主机进程间通信，可根据创建Socket 的类型不同，分为三种常⻅的通信⽅式，⼀个是基于 TCP 协议的通信⽅式，⼀个是基于 UDP 协议的通信⽅式，⼀个是本地进程间通信⽅式。

   以上，就是进程间通信的主要机制了。你可能会问了，那线程通信间的⽅式呢？

   同个进程下的线程之间都是共享进程的资源，只要是共享变量都可以做到线程间通信，⽐如全局变量，所以对于线程间关注的不是通信⽅式，⽽是关注多线程竞争共享资源的问题，信号量也同样可以在线程间实现互斥与同步：

+ 互斥的⽅式，可保证任意时刻只有⼀个线程访问共享资源；
+ 同步的⽅式，可保证线程 A 应在线程 B 之前执⾏；

## 多线程同步

### 竞争与协作

> 在单核 CPU 系统⾥，为了实现多个程序同时运⾏的假象，操作系统通常以时间⽚调度的⽅式，让每个进程执⾏每次执⾏⼀个时间⽚，时间⽚⽤完了，就切换下⼀个进程运⾏，由于这个时间⽚的时间很短，于是就造成了「并发」的现象。

[![image.png](https://i.postimg.cc/prkKYD5V/image.png)](https://postimg.cc/jnwWRnhB)

   另外，操作系统也为每个进程创建巨⼤、私有的虚拟内存的假象，这种地址空间的抽象让每个程序好像拥有⾃⼰的内存，⽽实际上操作系统在背后秘密地让多个地址空间「复⽤」物理内存或者磁盘

[![image.png](https://i.postimg.cc/J7cwCGW1/image.png)](https://postimg.cc/z3B2nDBM)

   如果⼀个程序只有⼀个执⾏流程，也代表它是单线程的。当然⼀个程序可以有多个执⾏流程，也就是所谓的多线程程序，线程是调度的基本单位，进程则是资源分配的基本单位。所以，线程之间是可以共享进程的资源，⽐如代码段、堆空间、数据段、打开的⽂件等资源，但每个线程都有⾃⼰独⽴的栈空间。

[![image.png](https://i.postimg.cc/HLcx6bRW/image.png)](https://postimg.cc/KKbxz3mC)

#### 互斥的概念

[![image.png](https://i.postimg.cc/s2kRzg4s/image.png)](https://postimg.cc/xk3ZyYZ4)

> 上面的情况为**竞争条件（race condition）**，当多线程相互竞争操作共享变量时，由于运气不好，在执行过程中发生了上下文切换得到了错误结果，事实上，每次运行都可能得到不同的结果，因此输出的结果存在 **不确定性（indeterminate）**。由于多线程执行操作共享变量的这段代码可能会导致竞争状态，因此我们将这段代码称为 **临界区（critical section），他是访问共享资源的代码片段，一定不能给多线程同时运行**。我们希望这段代码是 **互斥（mutualexclusion）的，也就说保证一个线程在临界区执行是，其他线程应该被阻止进入临界区**，就是说这段代码执行过程中，最多只能出现一个线程。另外，互斥也不是只针对多线程。在多进程竞争共享资源的时候，也同样是可以使用互斥的方式来避免资源竞争造成的资源混乱。

[![image.png](https://i.postimg.cc/PxdHqzqK/image.png)](https://postimg.cc/t1vwS6WV)

#### 同步的概念

> 同步就是并发线程/进程在一些关键点上可能需要互相等待与互通消息，这种相互制约的等待与互通消息称为进程/线程同步。

   同步和互斥是两种不同的概念：

+ 同步：操作A应在操作B之前执行，操作C必须在操作A和操作B都完成之后才能执行等；
+ 互斥：操作A和操作B不能在同一时刻执行；

### 互斥与同步的实现

> 在进程/线程并发执行的过程中，进程/线程之间存在写作的关系，例如有互斥、同步的关系。为了实现进程/线程间的正确的写作，操作系统必须提供实现进程写作的措施和方法，主要的方法有两种，这两个都可以方便的实现进程/线程互斥，信号量比所得功能要更强一些，它还可以方便的实现进程/线程同步。

+ 锁：加锁，解锁操作；
+ 信号量：P、V操作；

#### 锁

> 使用加锁操作和解锁操作可以解决并发线程/进程的互斥问题。

   任何想进入临界区的线程，必须先加锁操作。若加锁顺利通过，则线程可进入临界区；在完成对临界资源的访问后再进行解锁操作，以释放该临界资源。根据锁的实现不同，可以分为 **忙等待锁** 和 **无忙等待锁**。

[![image.png](https://i.postimg.cc/g0HrzKpk/image.png)](https://postimg.cc/06r9ZDrL)

> 忙等待锁的实现

   在说明 **忙等待锁** 的实现之前，先介绍现代CPU体系结构提供的特殊 **源自操作指令--测试和置位（Test-and-Set）指令**。

   如果用C代码表示Test-and-Set指令，形式如下：

```c
int TestAndSet(int *old_ptr,int new){
    int old = *old_ptr;
    *old_ptr = new;
    return old;
}
```

+ 把old_ptr更新为new的值；
+ 返回old_ptr的旧值；

   这些代码是原子执行，因为既可以测试旧值又可以设置新值，所以把这条指令叫做 **测试并设置** 。**原子操作要么全部执行，要么都不执行，不能出现执行到一半的中间状态**。

   可以用Test-and-Set指令来实现 **忙等待锁**，代码如下：

```c
typedef struct lock_t
{
    int flag;
} lock_t;

void init(lock_t *lock)
{
    lock->flag = 0;
}

void lock(lock_t *lock)
{
    while (TestAndSet(&lock->flag, 1) == 1)
    {
        /* code */
    }
}

void unlock(lock_t *lock)
{
    lock->flag = 0;
}
```

   为什么这个锁能工作：

+ 第一个场景，假设一个线程正在运行，调用lock()，没有其他线程持有锁，所以flag是0，当调用TestAndSet(flag,1)方法，返回0，线程会跳出while循环，获取锁。同时也会原子的设置flag为1，标志锁已经被持有。当线程离开临界区，调用unlock()，家flag清理为0；
+ 第二个场景，当某一个线程已经持有锁（即flag为1）。本线程调用lock()，然后调用TestAndSet(flag,1)，这一次返回1。只要另一个线程一致持有锁，TestAndSet()会重复返回1，本线程会一直 **忙等**。当flag重要被改为0，本线程会调用TestAndSet()，返回0并且原子的设置为1，从而获得锁，进入临界区。

   当获取不到锁时，线程就会一直while选好，不做任何事情，所以被称为 **忙等待锁**，也被称为 **自旋锁（spin lock）**。

   这是最简单的⼀种锁，⼀直⾃旋，利⽤ CPU 周期，直到锁可⽤。在单处理器上，需要抢占式的调度器（即不断通过时钟中断⼀个线程，运⾏其他线程）。否则，⾃旋锁在单 CPU 上⽆法使⽤，因为⼀个⾃旋的线程永远不会放弃 CPU。

> 无等待锁的实现（获取不到锁的时候，不用自旋）

```c
typedef struct lock_t
{
    int flag;
    // 等待队列
    queue_t *q;
} lock_t;

void init(lock_t *lock)
{
    lock->flag = 0;
    queue_init(lock->q);
}

void lock(lock_t *lock)
{
    while (TestAndSet(&lock->flag, 1) == 1)
    {
        // 保存现在运行线程 TCB;
        // 将现在运行的线程 TCB 插入到等待队列；
        // 设置该线程为等待状态；
        // 调度程序；
    }
}

void unlock(lock_t *lock)
{
    if (lock->q != NULL)
    {
        // 移出等待队列的队头元素；
        // 将该线程的TCB插入到就绪队列；
        // 设置该线程为就绪状态；
    }
    lock->flag = 0;
}
```

#### 信号量

> 信号量是操作系统提供的一种协调共享资源访问的方法。通常 **信号量表示资源的数量** ，对应的变量是一个整形（sem）变量。另外还有 **两个原子操作的系统调用函数来控制信号量的**，分别是；

+ P操作：将sem减1，相减后，如果 sem<0，则进程/线程进入阻塞等待，否则继续，表明操作可能会阻塞；
+ V操作：将sem加1，相加后，如果 sem<0，唤醒一个等待中的进程/线程，表明V操作不会阻塞；
+ P操作是用在进入临界区之前，V操作是用在离开临界区之后，这两个操作是必须成对出现的。
+ PV操作的函数是由操作系统管理和实现的，所以操作系统已经使得执行PV函数是具有原子性的

```c
// 信号量数据结构
typedef struct sem_t
{
    // 资源个数
    int sem;
    // 等待队列
    queue_t *q;
} sem_t;

// 初始化信号量
void init(sem_t *s, int sem)
{
    s->sem = sem;
    queue_init(s->q);
}

// P操作
void P(sem_t *s){
    s->sem--;
    if (s->sem < 0)
    {
        // 1. 保留调用线程 CPU 现场；
        // 2. 将该线程的 TCB 插入到 s 的等待队列；
        // 3. 设置该线程为等待状态；
        // 4. 执行调度程序；
    }
  
}

// V操作
void V(sem_t *s){
    s->sem++;
    if (s->sem<=0)
    {
        // 1. 移出 s 等待队列首元素；
        // 2. 将该线程的 TCB 插入就绪队列；
        // 3. 设置该线程为 就绪状态；
    }
  
}
```

> PV操作如何使用的呢？

   信号量不仅可以实现临界区的互斥访问控制，还可以线程间的事件同步。

1. 使用**信号量实现临界区的互斥访问**。

   为每类共享资源设置⼀个信号量 s ，其初值为 **1** ，表示该临界资源未被占⽤。只要把进⼊临界区的操作置于 P(s) 和 V(s) 之间，即可实现进程/线程互斥：

[![image.png](https://i.postimg.cc/9MYhqKpr/image.png)](https://postimg.cc/7GhcFBjk)

   此时，任何想进⼊临界区的线程，必先在互斥信号量上执⾏ P 操作，在完成对临界资源的访问后再执⾏ V操作。由于互斥信号量的初始值为 1，故在第⼀个线程执⾏ P 操作后 s 值变为 0，表示临界资源为空闲，可分配给该线程，使之进⼊临界区。

   若此时⼜有第⼆个线程想进⼊临界区，也应先执⾏ P 操作，结果使 s 变为负值，这就意味着临界资源已被占⽤，因此，第⼆个线程被阻塞。

   并且，直到第⼀个线程执⾏ V 操作，释放临界资源⽽恢复 s 值为 0 后，才唤醒第⼆个线程，使之进⼊临界区，待它完成临界资源的访问后，⼜执⾏ V 操作，使 s 恢复到初始值 1。

   对于两个并发线程，互斥信号量的值仅取 1、 0 和 -1 三个值，分别表示：

+ 如果互斥信号量为 1，表示没有线程进⼊临界区；
+ 如果互斥信号量为 0，表示有⼀个线程进⼊临界区；
+ 如果互斥信号量为 -1，表示⼀个线程进⼊临界区，另⼀个线程等待进⼊。

   通过互斥信号量的⽅式，就能保证临界区任何时刻只有⼀个线程在执⾏，就达到了互斥的效果。

2. 使用 **信号量实现事件同步**。

   同步的⽅式是设置⼀个信号量，其初值为 **0** 。我们把前⾯的「吃饭-做饭」同步的例⼦，⽤代码的⽅式实现⼀下

```c
// 表示不需要吃饭
semaphoer s1 = 0;
// 表示饭还没做完
semaphore s2 = 0;

// 儿子线程函数
void son()
{
    while (TRUE)
    {
        肚子饿；
        // 叫妈妈做饭
        V(S1);
        // 等待妈妈做完饭
        P(S2);
        吃饭；
    }
}

// 妈妈线程函数
void mon(){
    while (TRUE)
    {
        // 询问需不需要做饭
        P(S1);
        做饭;
        // 做完饭，通知儿子吃饭
        V(S2);
    }
  
}
```

   妈妈⼀开始询问⼉⼦要不要做饭时，执⾏的是 P(s1) ，相当于询问⼉⼦需不需要吃饭，由于 s1 初始值为 0，此时 s1 变成 -1，表明⼉⼦不需要吃饭，所以妈妈线程就进⼊等待状态。

   当⼉⼦肚⼦饿时，执⾏了 V(s1) ，使得 s1 信号量从 -1 变成 0，表明此时⼉⼦需要吃饭了，于是就唤醒了阻塞中的妈妈线程，妈妈线程就开始做饭。接着，⼉⼦线程执⾏了 P(s2) ，相当于询问妈妈饭做完了吗，由于 s2 初始值是 0，则此时 s2 变成-1，说明妈妈还没做完饭，⼉⼦线程就等待状态。

   最后，妈妈终于做完饭了，于是执⾏ V(s2) ， s2 信号量从 -1 变回了 0，于是就唤醒等待中的⼉⼦线程，唤醒后，⼉⼦线程就可以进⾏吃饭了。

#### 生产者-消费者问题

[![image.png](https://i.postimg.cc/sgDqjMWt/image.png)](https://postimg.cc/HVRB3sB2)

   生产者消费者问题描述：

+ 生产者在生成数据后，放在一个缓冲区中；
+ 消费者从缓冲区去除数据处理；
+ 任何时刻，只能有个生产者或消费者可以访问缓冲区

   我们对问题的分析可以得出：

+ 任何时刻只能有一个线程操作缓冲区，说明操作缓冲区是临界代码，**需要互斥**；
+ 缓冲区空时，消费者必须等待生产者生成数据；缓冲区满是，生产者必须等待消费者取出数据。说明生产者和消费者**需要同步**；

   那么我们需要三个信号量，分别是：

+ 互斥信号量 mutex ：用于互斥访问缓冲区，初始值为1；
+ 资源信号量 fullBuffers ：用户消费者询问缓冲区是否有数据，有数据则读取数据，初始值为0（表明缓冲区一开始为空）；
+ 资源信号量 emptyBuffers ：用于生产者询问缓冲是否有空位，有空位则生成数据，初始化值为n（缓冲区大小）；

   具体的实现代码：

```c
#define N 100
// 互斥信号量，用于临界区的互斥访问
semaphore mutex = 1;
// 表示缓冲区空槽的个数
semaphore emptyBuffers = N;
// 表示缓冲区满槽的个数
semaphore fullBuffers = 0;

// 生产者线程函数
void producer(){
    while (TRUE)
    {
        // 将空槽的个数-1
        P(emptyBuffers);
        // 进入临界区
        P(mutex);
        将生成的数据放到缓冲区中；
        // 离开缓冲区
        V(mutex);
        // 将满槽的个数+1
        V(fullBuffers);

    }
  
}

// 消费者线程函数
void consumer(){
    while (TRUE)
    {
        // 将满槽的个数-1
        P(fullBuffers);
        // 进入临界区
        P(mutex);
        从缓冲里读取数据；
        // 离开临界区
        V(mutex);
        // 将空槽的个数+1
        V(emptyBuffers);
    }
  
}
```

   如果消费者线程⼀开始执⾏ P(fullBuffers) ，由于信号量 fullBuffers 初始值为 0，则此时 fullBuffers 的值从 0 变为 -1，说明缓冲区⾥没有数据，消费者只能等待。接着，轮到⽣产者执⾏ P(emptyBuffers) ，表示减少 1 个空槽，如果当前没有其他⽣产者线程在临界区执⾏代码，那么该⽣产者线程就可以把数据放到缓冲区，放完后，执⾏ V(fullBuffers) ，信号量 fullBuffers从 -1 变成 0，表明有「消费者」线程正在阻塞等待数据，于是阻塞等待的消费者线程会被唤醒。消费者线程被唤醒后，如果此时没有其他消费者线程在读数据，那么就可以直接进⼊临界区，从缓冲区读取数据。最后，离开临界区后，把空槽的个数 + 1。

### 经典同步问题

#### 哲学家就餐问题

> 5个哲学家围绕餐桌吃面，桌上只有5支叉子，每两个哲学家之间放一只叉子；哲学家要两只叉子才可以吃面，也就是需要拿到左右两边的叉子才进餐；那么如何保证哲学家的动作有序进行，而不会出现有人永远拿不到叉子呢？

[![image.png](https://i.postimg.cc/fymHfgq9/image.png)](https://postimg.cc/y36XVnH1)

1. 方案1 用信号量的方式，也就是PV操作来尝试解决，代码如下：

```c
// 哲学家个数
#define N 5

// 信号量初值为1，也就是叉子的个数
semaphore fork[5];

// i为哲学家编号0-4
void smart_person(int i)
{
    while (TRUE)
    {
        // 哲学家思考
        think();
        // 去拿左边的叉子
        P(fork[i]);
        // 去拿右边的叉子
        P(fork[(i + 1) % N]);
        // 进餐
        eat();
        // 放下左边的叉子
        V(fork[i]);
        // 放下右边的叉子
        V(fork[(i + 1) % N]);
    }
}
```

   不过这种方法存在一个极端的问题：假设5人同时拿起左边的叉子，桌面上就没叉子了，这样就没有人能够拿起他们右边的叉子，也就说每一个都会在P(fork[(i+1)%N])这条语句阻塞，发生死锁现象。

[![image.png](https://i.postimg.cc/jSPfcnbB/image.png)](https://postimg.cc/xXjqTCqP)

2. 既然方案1 会放生同时竞争左边叉子导致死锁现象，那我们在拿叉子前，加个互斥信号量，代码如下：

```c
// 哲学家个数
#define N 5

// 信号量初值为1，也就是叉子的个数
semaphore fork[5];

// 互斥信号量，初始值为1
semaphore mutex;

// i为哲学家编号0-4
void smart_person(int i)
{
    while (TRUE)
    {
        // 哲学家思考
        think();
        // 进入临界区
        P(mutex);
        // 去拿左边的叉子
        P(fork[i]);
        // 去拿右边的叉子
        P(fork[(i + 1) % N]);
        // 进餐
        eat();
        // 放下左边的叉子
        V(fork[i]);
        // 放下右边的叉子
        V(fork[(i + 1) % N]);
        // 退出临界区
        V(mutex);
    }
}
```

   上面程序的互斥信号量的作用在于，**只要有一个哲学家进入了 临界区 ，也就是准备拿起叉子时，其他哲学家都不能懂，只有这位哲学家用完叉子了，才能轮到下一个哲学家进餐**。

[![image.png](https://i.postimg.cc/4yCq74D6/image.png)](https://postimg.cc/ygPv2KYx)

   方案2虽然能让哲学家按顺序吃饭，但是每次只能一位，桌面上有5把叉子，最多可以有2位同时进餐。

3. 方案2使用互斥信号量会导致只能允许一个哲学家就餐，那么就不用它。另外，⽅案⼀的问题在于，会出现所有哲学家同时拿左边⼑叉的可能性，那我们就避免哲学家可以同时拿左边的⼑叉，采⽤分⽀结构，根据哲学家的编号的不同，⽽采取不同的动作。

   **即让偶数编号的哲学家「先拿左边的叉⼦后拿右边的叉⼦」，奇数编号的哲学家「先拿右边的叉⼦后拿左边的叉⼦」。

```c
// 哲学家个数
#define N 5

// 信号量初值为1，也就是叉子的个数
semaphore fork[5];

// 互斥信号量，初始值为1
semaphore mutex;

// i为哲学家编号0-4
void smart_person(int i)
{
    while (TRUE)
    {
        // 哲学家思考
        think();
        if (i % 2 == 0)
        {
            // 去拿左边的叉子
            P(fork[i]);
            // 去拿右边的叉子
            P(fork[(i + 1) % N]);
        }
        else
        {
            // 去拿右边的叉子
            P(fork[(i + 1) % N]);
            // 去拿左边的叉子
            P(fork[i]);
        }

        // 进餐
        eat();
        // 放下左边的叉子
        V(fork[i]);
        // 放下右边的叉子
        V(fork[(i + 1) % N]);
        // 退出临界区
        V(mutex);
    }
}
```

   上面的程序，在P操作时，根据哲学家的编号不同，拿起左右两边叉子的顺序不同。另外V操作是不需要分支的，因为V操作时不会阻塞的。

[![image.png](https://i.postimg.cc/L6zhx2ph/image.png)](https://postimg.cc/fJRwL4kh)

#### 读者-写者问题

> 读者只会读取数据，不会修改数据，而写者既可以读也可以修改数据。读者-写者的问题描述：

+ 读-读 允许：同一时刻，允许多个读者同时读
+ 读-写 互斥：没有写者时读者才能读，没有读者时，写者才能写；
+ 写-写 互斥：没有其他写者时，写者才能写。

## 死锁

### 死锁的概念

> 当两个线程为了保护两个不同的共享资源而使用两个互斥锁，那么这两个互斥锁应用不当的时候，可能会造成 **两个线程都在等待对方释放锁** ，在没有外力的作用下这些线程会一直相互等待，就没法继续运行，这种情况就是发生了 **死锁**。

   死锁只有同时满足以下四个条件才会发生：

+ 互斥条件
+ 持有并等待条件
+ 不可剥夺条件
+ 环路等条件

> 互斥条件是指 **多个线程不能同时使用同一个资源** 。

   如果线程 A 已经持有的资源，不能再同时被线程 B 持有，如果线程 B 请求获取线程 A 已经占⽤的资源，那线程 B 只能等待，直到线程 A 释放了资源。

[![image.png](https://i.postimg.cc/90FSXShx/image.png)](https://postimg.cc/Fd8GDT1c)

> 持有并等待条件

   持有并等待条件是指，当线程 A 已经持有了资源 1，⼜想申请资源 2，⽽资源 2 已经被线程 C 持有了，所以线程 A 就会处于等待状态，但是线程 A 在等待资源 2 的同时并不会释放⾃⼰已经持有的资源 1。

   [![image.png](https://i.postimg.cc/X7BLK3Qf/image.png)](https://postimg.cc/hfgVcFFv)

> 不可剥夺条件

   不可剥夺条件是指，当线程已经持有了资源 ，**在⾃⼰使⽤完之前不能被其他线程获取**，线程 B 如果也想使⽤此资源，则只能在线程 A 使⽤完并释放后才能获取。

[![image.png](https://i.postimg.cc/TPtrJtSb/image.png)](https://postimg.cc/GBs8cxb3)

> 环路等待条件

   环路等待条件指的是，在死锁发生的时候，**两个线程获取资源的数据构成了环形链**。⽐如，线程 A 已经持有资源 2，⽽想请求资源 1， 线程 B 已经获取了资源 1，⽽想请求资源 2，这就形成资源请求等待的环形图。

[![image.png](https://i.postimg.cc/RCHHWCMK/image.png)](https://postimg.cc/HjTxKg8k)

### 模拟死锁问题的产生

```C
/**
 * 死锁
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
pthread_mutex_t mutex_A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_B = PTHREAD_MUTEX_INITIALIZER;

/**
 * 线程函数A
 *
 * 先获取互斥锁A，休眠1秒
 * 再获取互斥锁B，
 * 释放互斥锁B
 * 最后释放互斥锁A
 */
void *threadA_func(void *data)
{
    printf("threadA waitting get ResourceA\n");
    pthread_mutex_lock(&mutex_A);
    printf("threadA got ResourceA\n");
    sleep(1);

    printf("threadA waitting get ResourceB\n");
    pthread_mutex_lock(&mutex_B);
    printf("threadA got ResourceB\n");

    pthread_mutex_unlock(&mutex_B);
    pthread_mutex_unlock(&mutex_A);

    return (void *)0;
}

/**
 * 线程函数B
 * 先获取互斥锁B，休眠1秒
 * 再获取互斥锁A，
 * 释放互斥锁A
 * 最后释放互斥锁B
 */
void *threadB_func(void *data)
{
    printf("threadB waitting get ResourceB\n");
    pthread_mutex_lock(&mutex_B);
    printf("threadB got ResourceB\n");
    sleep(1);

    printf("threadB waitting get ResourceA\n");
    pthread_mutex_lock(&mutex_A);
    printf("threadB got ResourceA\n");

    pthread_mutex_unlock(&mutex_A);
    pthread_mutex_unlock(&mutex_B);

    return (void *)0;
}

int main()
{

    pthread_t tidA, tidB;

    // 创建两个线程
    if (pthread_create(&tidA, NULL, threadA_func, NULL) != 0)
    {
        perror("ERROE CREATE TIDA\n");
    }
    else
    {
        printf("PASS CREATE TIDA\n");
    }
    if (pthread_create(&tidB, NULL, threadA_func, NULL) != 0)
    {
        perror("ERROE CREATE TIDB\n");
    }
    else
    {
        printf("PASS CREATE TIDB\n");
    }

    pthread_join(&tidA, NULL);
    pthread_join(&tidB, NULL);

    printf("TEST PASS\n");

    return 0;
}

# RESULT
PASS CREATE TIDA
thread A waitting get ResourceA
thread A got ResourceA
PASS CREATE TIDB
thread B waitting get ResourceB
thread B got ResourceB
thread A waitting get ResourceB
thread B waitting get ResourceA

```

   可以看到线程B在等待互斥锁A的释放，线程A在等待互斥锁B的释放，双方都在等待对方资源释放，很明显产生了死锁问题

### 避免死锁问题产生

> 产生死锁的四个必要条件是：互斥条件、只有并等待条件、不可剥夺条件、环路等待条件。避免死锁的问题只需要破坏其中一个条件就可以，最常见的并且可行的就是 **使用资源有序分配法，来破坏环路等待条件** 。

   如上述代码，线程A是先获取互斥锁A后获取互斥锁B。只需要将线程B改成以相同的顺序获取资源就可以打破死锁了。

```C
/**
 * 死锁
 *
 * 将线程改成以相同顺序获取资源，而取消死锁
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
pthread_mutex_t mutex_A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_B = PTHREAD_MUTEX_INITIALIZER;

/**
 * 线程函数A
 *
 * 先获取互斥锁A，休眠1秒
 * 再获取互斥锁B，
 * 释放互斥锁B
 * 最后释放互斥锁A
 */
void *threadA_func(void *data)
{
    printf("thread A waitting get ResourceA\n");
    pthread_mutex_lock(&mutex_A);
    printf("thread A got ResourceA\n");
    sleep(1);

    printf("thread A waitting get ResourceB\n");
    pthread_mutex_lock(&mutex_B);
    printf("thread A got ResourceB\n");

    pthread_mutex_unlock(&mutex_B);
    printf("thread A released Resource B\n");

    pthread_mutex_unlock(&mutex_A);
    printf("thread A released Resource A\n");

    return (void *)0;
}

/**
 * 线程函数B
 * 先获取互斥锁A，休眠1秒
 * 再获取互斥锁B，
 * 释放互斥锁B
 * 最后释放互斥锁A
 */
void *threadB_func(void *data)
{
    printf("thread B waitting get ResourceA\n");
    pthread_mutex_lock(&mutex_A);
    printf("thread B got ResourceA\n");
    sleep(1);

    printf("thread B waitting get ResourceB\n");
    pthread_mutex_lock(&mutex_B);
    printf("thread B got ResourceB\n");

    pthread_mutex_unlock(&mutex_B);
    printf("thread B released Resource B\n");
    pthread_mutex_unlock(&mutex_A);
    printf("thread B released Resource A\n");

    return (void *)0;
}

int main()
{

    pthread_t tidA, tidB;

    // 创建两个线程
    if (pthread_create(&tidA, NULL, threadA_func, NULL) != 0)
    {
        perror("ERROE CREATE TIDA\n");
    }
    else
    {
        printf("PASS CREATE TIDA\n");
    }
    if (pthread_create(&tidB, NULL, threadB_func, NULL) != 0)
    {
        perror("ERROE CREATE TIDB\n");
    }
    else
    {
        printf("PASS CREATE TIDB\n");
    }

    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);

    printf("TEST PASS\n");

    return 0;
}

# RESULT
PASS CREATE TIDA
thread A waitting get ResourceA
thread A got ResourceA
PASS CREATE TIDB
thread B waitting get ResourceA
thread A waitting get ResourceB
thread A got ResourceB
thread A released Resource B
thread A released Resource A
thread B got ResourceA
thread B waitting get ResourceB
thread B got ResourceB
thread B released Resource B
thread B released Resource A
TEST PASS
```

### 总结

   死锁问题的产⽣是由两个或者以上线程并⾏执⾏的时候，争夺资源⽽互相等待造成的。死锁只有同时满⾜互斥、持有并等待、不可剥夺、环路等待这四个条件的时候才会发⽣。所以要避免死锁问题，就是要破坏其中⼀个条件即可，最常⽤的⽅法就是使⽤资源有序分配法来破坏环路等待条件。

## 悲观锁与乐观锁

### 互斥锁与自旋锁：谁更轻松自如

> 最底层的两种就是 **互斥锁和自旋锁** ，很多高级锁都是基于他们实现的。加锁的目的就是保证贡献资源在任意时间里，只有一个线程访问，这样就可以避免多线程共享数据错乱的问题。

   当有一个线程加锁后，其他线程加锁就会失败，互斥锁和自旋锁对于加锁失败后的处理方式是不一样的：

+ 互斥锁 加锁失败后，线程会 释放CPU，给其他线程；
+ 自旋锁 加锁失败后，线程会 忙等待，直到它拿到锁；

   互斥锁是一种 **独占锁**，比如当线程A加锁成功后，此时互斥锁已经被线程A独占了，只要线程A没有释放手中的锁，线程B加锁就会失败，于是会释放CPU给其他线程， **既然线程B释放掉了CPU，自然线程B加锁的代码就会被阻塞**。

   **对于互斥锁加锁失败而阻塞的现象，是由操作系统内核实现的**。当加锁失败是，内核会将线程置为 **睡眠** 状态，等到锁被释放后，内核会在合适的时机唤醒线程，当这个线程获取到锁后，于是可以继续执行。如下图：

[![image.png](https://i.postimg.cc/RV7XSKCy/image.png)](https://postimg.cc/nCLvTsDG)

   所以，互斥锁加锁失败时，会从用户态陷入到内核态，让内核帮我们切换线程，虽然简化了使用锁的难度，但是存在一定的性能开销成本。那么这个开销成本是什么？ **两次线程上下文切换的成本**；

   线程上下文切换的是什么？当两个线程属于同一个进程时，**因为虚拟内存是共享的，所以在切换时，虚拟内存这些资源就保持不动，只需要切换线程的私有数据、寄存器等不共享的数据**。上下文切换的耗时大概在几十纳秒到几微秒之间，如果锁住的代码时间比较短，那么可能上下文切换的时间都比锁住代码的执行时间还要长。所以，**如果能确定被锁住的代码执行时间很短，就不应该用互斥锁，而应该选用自旋锁，否则使用互斥锁**。

   自旋锁是通过CPU提供的 **CAS**函数（Compare And Swap），在用户态完成加锁和解锁操作，不会主动产生线程上下文切换，所以相比互斥锁来说，会快一点，开销也小一点。

   一般加锁的过程，包含2个步骤：

1. 查看锁的状态，如果锁是空闲的，则执行第二步；
2. 将锁设置为当前线程持有；

   CAS函数就把这两个步骤合并成一条硬件级指令，形成 **原子指令**，这样就保证了这两个步骤是不可分割的，要么一次性执行完2个步骤，要门两个步骤都不执行。

   使用自旋锁的时候，当发生多线程竞争锁的情况，加锁失败的线程会 **忙等待** ，直到它拿到锁。这里的忙等待，可以用while循环等实现，不过最好使用CPU提供的 **PAUSE** 指令来实现 **忙等待**，因为可以减少循环等待时的耗电量。

   自旋锁是最比较简单的一种锁，一致自旋，利用CPU周期，直到锁可用。**需要注意，在单核CPU上，需要抢占式的调度器（即不断通过时钟中断一个线程，运行其他线程）。否则，自旋锁在单CPU上无法使用，因为一个自旋的线程永远不会放弃CPU**。

   自旋锁开销少，在多核系统下一般不会主动产生线程切换，适合异步、协程等在用户态切换请求的编程方式，但如果被锁住的代码执行时间过长，自旋锁的线程会长时间占用CPU资源，所以 **自旋的时间** 和 **被锁住的代码执行时间** 是成 **正比** 的关系。

   自旋锁与互斥锁使用层面比较相似，但实现层面上完全不同：**当加锁失败时，互斥锁用 线程切换 来赢多，自旋锁则用 忙等待 来应对。

   互斥锁和自旋锁是锁的最基本的处理凡是，更高级的锁都会选择其中一个来实现，比如读写锁既可以选择互斥锁来实现，也可以基于自旋锁来实现。

### 读写锁：读和写还有优先级区分吗？

> 读写锁由 读锁 和 写锁 两部分构成，如果只读取共享资源，用 读锁 加锁，如果要修改共享资源则用 写锁 加锁。所以，**读写锁适用于明确区分读操作和写操作的场景**。

   读写锁的工作原理是：

+ 当 写锁 没有被线程持有时，多个线程能并发的持有 读锁，这大大提供了共享资源的额访问效率，因为 读锁 是用于读取共享资源的场景，所以多个线程同时持有读锁也不会破坏共享资源的数据。
+ 但是，一旦 写锁 被线程持有后，读线程获取读锁的操作会被阻塞，而其他写线程的获取写锁的操作也会被阻塞。

   所以说 **写锁是独占锁** ，因为任何时刻只能有一个线程持有写锁，类似互斥锁和自旋锁，而 **读锁是共享锁** ，因为读锁可以被多个线程同时持有

   根据实现的不同，读写锁可以分为 读优先锁 和 写优先锁。读优先锁期望的是，读锁能被跟多的线程持有，以便提高读线程的并发性，它的工作方式是：当读线程A先持有了读锁，写线程B在获取写锁的时候会被阻塞，并且在阻塞过程中，后续来的读线程C任然可以成功获取读锁，最后直到读线程A和C释放读锁后，写线程B才可以成功获取写锁。如下图：

[![image.png](https://i.postimg.cc/d0xkYDBW/image.png)](https://postimg.cc/Mc1K06gR)

   写优先锁是优先服务写线程，其工作方式是：当读线程A先持有了读锁，写线程B在获取写锁的时候，会被阻塞，并且在阻塞过程中，后续来的读线程C获取读锁时会失败，于是读线程C将被阻塞在获取读锁的操作，这样只要读线程A释放读锁后，写线程B就可以成功获取读锁。如下图：

[![image.png](https://i.postimg.cc/PNs1kNtG/image.png)](https://postimg.cc/5QgXB4Yp)

   读优先锁对应读线程并发性更好，但也不是没有问题，如果一直有读线程获取读锁，那么写线程将永远获取不到写锁，这就造成了 **线程饥饿** 的现象。写优先锁可以保证写线程不会饿死，但是如果一直有写线程获取写锁，读线程也会被饿死。既然不管读优先锁还是写优先锁双方都可能出现饿死问题，所以希望出现 公平读写锁

   **公平读写锁**比较简单的一种方式是：用队列把获取所得线程排队，不管是写线程还是读线程，都按照先进先出的原则加锁即可，这样读线程仍然可以并发，也不会出现 **饥饿** 的现象。互斥锁和自旋锁都是最基本的锁，读写锁可以根据场景来选择这两种锁的其中一个来实现。

### 悲观锁与乐观锁：做事心态有何不同？

> 互斥锁、自旋锁、读写锁都属于悲观锁。悲观锁做事比较悲观，他认为 **多线程同时修改共享资源的概率比较高，于是很容易出现冲突，所以访问共享资源前，都要先上锁**。那相反，如果多线程同时修改共享资源概率比较低，就可以使用乐观锁。乐观锁做事比较乐观，它假定冲突的概率很低，它的工作方式是：**先修改完共享资源，再验证这段时间内有没有发生冲突，如果没有其他线程在修改资源，那么操作完成，如果发现其他线程已经修改过这个资源就放弃本次操作**。放弃后如何充实，这跟业务场景相关，虽然重试成本高，但是冲突概率足够低的话，还是可以接受的。可见 **乐观锁全程并没有加锁，所以也叫它无锁编程**。

   实际上，我们常见的SVN和Git也是用了乐观锁的思想，先让用户编辑代码，然后提交的时候通过版本号来判断是否发生了冲突，发生了冲突的地方，需要我们修改后，再重新提交。

   乐观锁，虽然去除了加锁解锁的操作，但是一旦发生冲突，重试的成本非常高，所以 **只有在冲突概率非常低，且加锁成本非常高的场景是，才考虑使用乐观锁**。

### 总结

   开发过程中，最常⻅的就是互斥锁的了，互斥锁加锁失败时，会⽤「线程切换」来应对，当加锁失败的线程再次加锁成功后的这⼀过程，会有两次线程上下⽂切换的成本，性能损耗⽐较⼤。

   如果我们明确知道被锁住的代码的执⾏时间很短，那我们应该选择开销⽐较⼩的⾃旋锁，因为⾃旋锁加锁失败时，并不会主动产⽣线程切换，⽽是⼀直忙等待，直到获取到锁，那么如果被锁住的代码执⾏时间很短，那这个忙等待的时间相对应也很短。

   如果能区分读操作和写操作的场景，那读写锁就更合适了，它允许多个读线程可以同时持有读锁，提⾼了读的并发性。根据偏袒读⽅还是写⽅，可以分为读优先锁和写优先锁，读优先锁并发性很强，但是写线程会被饿死，⽽写优先锁会优先服务写线程，读线程也可能会被饿死，那为了避免饥饿的问题，于是就有了公平读写锁，它是⽤队列把请求锁的线程排队，并保证先⼊先出的原则来对线程加锁，这样便保证了某种线程不会被饿死，通⽤性也更好点。

   互斥锁和⾃旋锁都是最基本的锁，读写锁可以根据场景来选择这两种锁其中的⼀个进⾏实现。

   另外，互斥锁、⾃旋锁、读写锁都属于悲观锁，悲观锁认为并发访问共享资源时，冲突概率可能⾮常⾼，所以在访问共享资源前，都需要先加锁。

   相反的，如果并发访问共享资源时，冲突概率⾮常低的话，就可以使⽤乐观锁，它的⼯作⽅式是，在访问共享资源时，不⽤先加锁，修改完共享资源后，再验证这段时间内有没有发⽣冲突，如果没有其他线程在修改资源，那么操作完成，如果发现有其他线程已经修改过这个资源，就放弃本次操作。

   但是，⼀旦冲突概率上升，就不适合使⽤乐观锁了，因为它解决冲突的重试成本⾮常⾼。不管使⽤的哪种锁，我们的加锁的代码范围应该尽可能的⼩，也就是加锁的粒度要⼩，这样执⾏速度会⽐
较快。再来，使⽤上了合适的锁，就会快上加快了。

# 调度算法

## 进程调度算法

## 内存页面置换算法

## 磁盘调度算法

## 扫描算法

# 文件系统

## 文件系统的组成

> 文件系统是操作系统中负责管理持久数据的子系统，就是把用户的文件存到磁盘硬件中，即使计算机断电了，磁盘里的数据并不会丢失，所以可以持久化的保存文件。文件的基本数据单位是文件，它的目的是对磁盘上的文件进行组织管理，组织的方式不同就会形成不同的文件系统。

   Linux最经典的一句话就是 **一切皆文件**，不仅普通的文件和目录，就连块设备、管道、socket等，也都是统一交给文件系统管理的。

   Linux文件系统会为没饿文件分配两个数据结构：**索引节点（index node）和目录项（directory entry）**，他们主要用来记录文件的元信息和目录层级结构。

+ 索引节点，也就是inode，用来记录文件的元信息，比如inode编号、文件大小、访问权限、创建时间、修改时间、 **数据在磁盘的位置** 等等。索引节点是文件的 **唯一** 标识，他们之间一一对应，也同样都会被存储在硬盘中，所以 **索引节点同样占用磁盘空间** 。
+ 目录项，也就是entry，用来记录文件的名字、 **索引节点指针** 以及与其他目录项的层级关联关系。多个目录项关联起来，就会形成目录结构，但他与索引节点不同的是， **目录项是由内核维护的一个数据结构，不存放于磁盘，而是缓存在内存**。

   由于索引节点唯一标识一个文件，而目录项记着文件的名，所以目录项和索引节点的关系是多对一，也就是说，一个文件可以有多个别字。比如，硬链接的实现就是，多个目录项中的索引节点指向同一个文件。

   注意：目录也是文件，也是索引节点唯一标识，和普通文件不同额是，普通文件在磁盘里面保存的是文件数据，而目录文件在磁盘里面保存子目录或文件。

> 目录项和目录是一个东西吗？

   虽然名字很相近，但是两者不是一个东西，目录是个文件，持久化存储在磁盘，而目录项是内核一个数据结构，缓存在内存。如果查询目录频繁从磁盘读，效率会很低，所以内核会把已经度过的目录用目录项这个数据结构缓存在内存，下次再读到相同目录时，只需从内存读就可以，大大提高了文件系统的效率。

> 那文件数据是如何存储在磁盘的呢？

   磁盘读写的最小单位是 **扇区**，扇区的大小只有 **512B**，很明显，如果每次读写都以这么小为单位，那这读写的效率会非常低。所以文件系统把多个扇区组成了一个 **逻辑块**，每次读写的最小单位就是逻辑块（数据块），Linux中的逻辑块大小是4GB，也就是一次读写8个扇区（512B X 8 = 4096B = 4KB(1KB = 1024B)）这将大大提高了磁盘的读写的效率。

   索引节点、目录项、以及文件数据的关系如下所示：

[![image.png](https://i.postimg.cc/cHhQ65zD/image.png)](https://postimg.cc/cgKKbT0Y)

   索引节点是村吃在硬盘上的数据，为了加速文件的访问，通常会把索引节点加载到内存中。另外，磁盘进行格式化的时候，会被分成三个存储区域，分别是 **超级块、索引节点和数据块区**。

+ 超级块，用来存储文件系统的详细信息，比如快个数、块大小、空闲块等等。
+ 索引节点区，用来存储索引节点；
+ 数据块区，用来存储文件或目录数据；

   不可能把超级块和索引节点区全部加载到内存，内存无法支撑，所以只有当需要使用的时候，才将其加载进内存，他们加载进内存的时候不同的：

+ 超级块：当文件系统挂载时进入内存；
+ 索引节点区：当文件被访问时进入内存；

## 虚拟文件系统

   文件系统种类太多，而操作系统希望 **对用户提供一个统一的接口**，于是在用户层与文件系统层引入了中间层，这个中间层就称为 **虚拟文件系统（Virtual File System,VFS）**，VFS定义了一组所有文件系统都要支持的数据结构和标准接口，只需要了解VFS提供的统一接口即可。在Linux文件系统中，用户空间、系统调用、虚拟机文件系统、缓存、文件系统以及存储之间的关系如下图：

[![image.png](https://i.postimg.cc/B6wyb1gk/image.png)](https://postimg.cc/ygcnrx2y)

   Linux支持的文件系统也不少，根据存储的位置不同，可以把文件系统分为三类：

+ 磁盘的文件系统，它是直接把数据存储在磁盘中，比如Ext2/3/4、XFS等都是这类文件系统
+ 内存的文件系统，这类文件系统的数据不是存储在硬盘的，而是占用内存空间，我们经常用到的/proc和/sys文件都属于这一类，读写这类文件，实际上是读写内核中相关的数据。
+ 网络的文件系统，用来访问其他的计算机主机数据的文件系统，比如NFS、SMB等等。

   文件系统首先要先挂载到某个目录才可以正常使用，比如Linux系统在启动是，会把文件系统挂载到根目录。

## 文件的使用

[![image.png](https://i.postimg.cc/65vvgF1n/image.png)](https://postimg.cc/RNvhnpmZ)

1. 首先用 **open** 系统调用打开文件，open的参数包括**文件的路径名和文件名** ；
2. 使用 **write** 写数据，其中write使用open所返回的 **文件描述符** ，并不使用文件名作为参数；
3. 使用完文件后，要用 **close** 系统调用关闭文件，避免资源的泄露。

   我们打开一个文件后，操作系统会跟踪进程打开的所有文件，所谓的跟踪就是操作系统为每个进程维护一个打开的文件表，文件表里的每一项代表 **文件描述符**，所以说文件描述符是打开文件的标识。

[![image.png](https://i.postimg.cc/SRyQGSx7/image.png)](https://postimg.cc/KkHyGyLR)

   操作系统在打开文件表中维护这打开文件的状态和信息：

+ 文件指针：系统跟踪上次读写位置作为当前文件位置指针，这种指针对打开文件的某个进程来说是唯一的；
+ 文件打开计数器：文件关闭时，操作系统必须重用其打开文件表条目，否则表内空间不够用。因为多个进程可能打开同一个文件，所以系统在删除打开文件条目之前，必须等待最后一个进程关闭文件，该计数器跟踪打开和关闭的数量，当该计数为0时，系统关闭文件，删除该条目；
+ 文件磁盘位置：绝大多数文件操作都要求修改文件数据，该信息保存在内存中，以免每个操作都从磁盘中读取；
+ 访问权限：每个进程打开文件都需要一个访问模式（创建、只读、读写、添加等），该信息保存在进程的打开文件列表中，以便操作系统能允许或拒绝之后的I/O请求。

   在用户视角里，文件就是一个持久化的数据结构，但操作系统不会关系你想存在磁盘上的任何数据结构，操作系统的视角是以数据块来读写文件，屏蔽掉这种差异的工作就是文件系统了。

   读文件和写文件的过程：

+ 当用户进程从文件读取1个字节大小的数据时，文件系统需要获取字节块所在的数据块，再返回数据块对应的用户进程需要的数据部分。
+ 当用户进程把1个字节大小的数据写进文件时，文件系统则找到需要写入数据块的位置，然后修改数据块中对应的部分。
+ 所以说，文件系统的基本操作单位是数据块

## 文件的存储

> 文件的数据时存储在硬盘上面的，数据在磁盘上的存放方式，就像程序在内存中存放的方式那样，有以下两种：

+ 连续空间存放方式
+ 非连续空间存放方式
  + 链表方式
  + 索引方式

### 连续空间存储

> 连续空间存放的方式顾名思义， **文件存放在磁盘 连续 的物理空间中**。这种模式下，文件的数据都是紧密相连，**读写效率很高**，因为一次磁盘寻道就可以独处整个文件。

   使用连续存放的方式有一个前提，必须先知道 一个文件的大小，这样文件系统才会根据文件的大小在磁盘上找到一块连续的空间分配给文件。

   所以，**文件头里需要指定 起始块的位置 和 长度** ，有了这两个信息就可以很好的表示文件的存放方式是一块连续的磁盘空间。（此处说的文件头就类似与Linux的inode）

[![image.png](https://i.postimg.cc/Mp7m4K4L/image.png)](https://postimg.cc/NK0X2YQ8)

   连续空间存放的方式虽然读写效率高，但是有 **磁盘空间碎片 和 文件长度不易扩展** 的缺陷。

### 非连续空间存储

#### 链表方式

> 链表的方式存放是 **离散的，不用连续的**，于是就可以 **消除磁盘碎片**，可以大大提高空间的利用率，同时 **文件的长度是可以动态扩展**。根据实现的方式不同，链表可以分为 **隐式链表** 和 **显示链接**两种形式。

   文件要以 **隐式链表** 的方式存放的话，**实现的方式是文件头要包含第一块和最后一块的位置，并且每个数据块里留出一个指针空间，用来存放下一个数据块的位置**，这样一个数据块连着一个数据块，从链头开始就可以顺着指针找到所有的数据块，所以存放的方式可以是不连续的。

[![image.png](https://i.postimg.cc/ryCkjSFX/image.png)](https://postimg.cc/z3B6XHg0)

   隐式链表的存放方式的 **缺点在于无法直接访问数据块，智能通过指针方式顺序访问文件，以及数据块指针消耗了一定的存储空间**。隐式链表分配的 **稳定性较差**，系统在运行过称中，由于软件或硬件错误 **导致链表中的指针丢失或损坏，会导致文件数据的丢失**。

   如果取出每个磁盘块的指针，把它放在内存的一个表中，就可以解决上述隐式链表中的两个不足。那么这种实现方式是 **显示链接**，他指 **把用于链接文件各数据块的指针，显示的存放在内存的一张链表中** ，该表在整个磁盘仅设置一张，**每个表项中存放的链接指针，指向下一个数据块号**。

   对于显式链接的⼯作⽅式，我们举个例⼦，⽂件 A 依次使⽤了磁盘块 4、 7、 2、 10 和 12 ，⽂件 B 依次使⽤了磁盘块 6、 3、 11 和 14 。利⽤下图中的表，可以从第 4 块开始，顺着链⾛到最后，找到⽂件 A 的全部磁盘块。同样，从第 6 块开始，顺着链⾛到最后，也能够找出⽂件 B 的全部磁盘块。最后，这两个链都以⼀个不属于有效磁盘编号的特殊标记（如 -1 ）结束。内存中的这样⼀个表格称为 **⽂件分配表（FileAllocation Table， FAT）**。

[![image.png](https://i.postimg.cc/ZqYqr4d3/image.png)](https://postimg.cc/18TPSxM5)

   由于查找记录的过程是在内存中进行的，因而不仅显著地 **提高了检索速度**，而且 **大大减少了访问磁盘的次数**。但也正是整个表都存放在内存中的关系， 它的主要缺点是 **不适用于大磁盘**。

#### 索引方式

> 链表的方式解决了连续分配的磁盘碎片和文件动态扩展的问题，但是不能有效支持直接访问（FAT除外），索引的方式可以解决这个问题。

   索引的实现是为每个文件创建一个 **索引数据块**，里面存放的是 **指向文件数据块的指针列表**，就像是书的目录一样，要找哪个章节的内容，看目录就可以。

   另外， **文件头需要包含指向 索引数据块 的指针** ，这样就可以通过文件头知道索引数据块的位置，再通过索引数据块里的索引信息找到对应的数据块。

   创建文件时，索引块的所有指针都设为空。当首次写入第i块是，先从空闲空间中取得一个块，再将其他地址写到索引块的第i个条目。

[![image.png](https://i.postimg.cc/SR2gKn7G/image.png)](https://postimg.cc/wRzXfTrt)

   索引的方式优点在于：

+ 文件的创建、增大、缩小很方便；
+ 不会有碎片的问题；
+ 支持顺序读写和随机读写；

   由于索引数据也是存放在磁盘块的，如果文件很小，明明只需一块就可存放的下，但还是需要额外分配一块来存放索引数据，所以缺陷之一就是存储索引带来的开销。如果文件很大，大到一个索引数据块放不下索引信息，可以通过组合的方式，来处理大文件的内存。

> 链表+索引 又被称为链式索引块，它的实现方式是 **在索引数据块留出一个存放下一个索引数据块的指针**，于是当一个索引数据块的索引信息用完，就可以通过指针的方式，找到下一个索引数据块的信息。这种方式也会出现前面提到的链表方式的问题，万一某个指针损坏，后面的数据就无法读取了。

[![image.png](https://i.postimg.cc/65sDr4TP/image.png)](https://postimg.cc/WtnWj3Gm)

> 还有另外一种组合的方式是 索引+索引的方式，这种组合称为 **多级索引块**，实现方式是 **通过一个索引块来存放多个索引数据块，一层套一层索引**。

[![image.png](https://i.postimg.cc/x8PhjtYb/image.png)](https://postimg.cc/30dnnjkK)

### Unix文件的实现方式

[![image.png](https://i.postimg.cc/cJpqKHz7/image.png)](https://postimg.cc/1gr729s4)

## 空闲空间管理

> 前面讲到的文件存储是针对已经被占用数据块组织和管理，那如果要保存一个数据块，应该放在硬盘哪个位置？

+ 空闲表法
+ 空闲链表法
+ 位图法

> 空闲表法

   空闲表法就是为所有空闲空间建立一张表，表内容包括空闲区的第一个块号和该空闲区的块个数，这个方式是连续分配的，如下图：

[![image.png](https://i.postimg.cc/m2SytgDv/image.png)](https://postimg.cc/3ddvq721)

   当请求分配磁盘空间时，系统依次扫描空闲表里的内容，直到找到一个合适的空闲区域位置，当用户撤销一个文件时，系统回收文件空间。这时，也需顺序扫描空闲表，寻找一个空闲表条目并将释放空间的第一个物理块号以及他占用的块数填到这个条目中。

   这种方法仅当有少量的空闲区时才有较好的效果。因为，如果存储空间存在大量的小的空闲区，则空闲区表变得很大，这样查询效率会很低。另外，这种分配技术适用于建立连续文件。

> 空闲链表法

   用链表的方式管理空想空间，每一个空闲块里有一个指针指向下一个空闲块

[![image.png](https://i.postimg.cc/76kRT1jx/image.png)](https://postimg.cc/f38CGdwF)

   当创建文件需要一块或几块是，就从链头上依次取下一块或几块。反之，当回收空间是，把这些空闲块依次接到链头上。这种技术只要在主存中保存一个指针，令他指向第一个空闲块。其特点是简单，但不能随机访问，工作效率低，因为每当在链表上增加或移动空闲块是需要做很多I/O操作，同时数据块的指针消耗了一定的存储空间。空闲表法和空闲链表法都不适用于大型文件系统，因为这回事空闲表或空闲链表太大。

> 位图法

   位图是利用二进制的一位来表示磁盘中的一个盘块的使用情况，磁盘上所有的盘块都有一个二进制位与之对应。当值为0时，表示对应的盘块空闲，值为1时，表示对应的盘块已分配。如：111111100001110010

   在Linux文件系统就采用了位图的方式来管理空闲空间，不仅用于数据空闲块的管理，还用于inode空闲块的管理，因为inode也是存储在磁盘的，自然也要有对其管理。

## 文件系统的结构

> Linux使用位图的方式管理空闲空间，用户在创建一个新文件时，Linux内核会通过inode的位图找到空闲可用的inode，并进行分配。存储数据时，会通过块的位图找到空闲的块，并分配，但仔细计算还是有问题的。

   数据块的位图是放在磁盘块里的，假设放在一个块里，一个块4k，每位表示一个数据块，共可以表示 4*1024*8=2^15 个空闲块，由于1个数据块是4k大小，那么最大可以表示的空间为 2^15*4*1024=2^27 个byte, 也就是128M。

   也就是说按照上⾯的结构，如果采⽤「⼀个块的位图 + ⼀系列的块」，外加「⼀个块的 inode 的位图 + ⼀系列的 inode 的结构」能表示的最⼤空间也就 128M，这太少了，现在很多⽂件都⽐这个⼤。在 Linux ⽂件系统，把这个结构称为⼀个块组，那么有 N 多的块组，就能够表示 N ⼤的⽂件。下图给出了 Linux Ext2 整个⽂件系统的结构和块组的内容，⽂件系统都由⼤量块组组成，在硬盘上相继排布：

[![image.png](https://i.postimg.cc/fRSwzf4B/image.png)](https://postimg.cc/87D8wWz6)

   最前面的第一个块是引导块，在系统启动时用于弃用引导，接着后面就是一个连续的块组了，块组的内容如下：

+ 超级块，包含的是文件系统的重要信息，比如inode总个数、块总个数、每个块组的inode个数、每个块组的块个数等待。
+ 块组描述符，包含文件系统中各个块组的状态，比如块组中空闲块和inode的数目等，每个块组都包含了文件系统中 **所有块组的组描述符信息**。
+ 数据位图和inode位图，用于表示对应的数据块或inode是空闲的还是被使用中
+ inode列表，包含了块组中所有的inode，inode用于保存文件系统中与各个文件和目录相关的所有元数据。
+ 数据块，包含文件的有用数据

   可以发现，每个块里有很多重复的信息，比如 **超级块和块组描述符表，这两个都是全局信息，而且非常重要**，原因如下：

+ 如果系统崩溃了破坏了超级块和块组描述符，有关文件系统结构和内容的所有信息都会丢失。如果有冗余的副本，该信息是可能恢复的。
+ 通过使文件和管理数据尽可能接近，减少了磁头寻道和旋转，这可以提高文件系统的性能。

   不过Ext2的后续版本采用了稀疏技术。该做法是，超级块和块组描述符表不再存储到文件系统的每个块组中，而是只写入到块组0、块组1和其他ID可以表示为3、5、7的幂的块组中。

## 目录的存储

> 和普通文件不同的是，**普通文件的块了保存的是文件数据，而目录文件的块里面保存的是目录里面一项一项的文件信息**。

### 列表

   在目录文件的块中，最简单的保存格式就是 **列表**，就是一项一项地将目录下的文件信息（如文件名、文件inode、文件类型等）列在表里。

   列表中每一项就代表该目录下的文件的文件名和对应的inode，通过这个inode，就可以找到真正的文件。

[![image.png](https://i.postimg.cc/5yBC18Vj/image.png)](https://postimg.cc/5Qt0SYjM)

   通常第一项是 **.** ，表示当前目录，第二项是 **..** ，表示上一级目录，接下来就是一项一项的文件名和inode。

### 哈希表

   如果一个目录有超级多的文件，我们想要在这个目录下找文件，按照列表一项一项的找，效率不高。

   于是，保存目录的格式改成 **哈希表** ，来宝座目录的内容，这种方法的优点是查找非常迅速，插入和删除也比较简单，不过需要一些预备措施来避免哈希冲突。

   目录查询是通过在磁盘上反复搜索完成，需要不断的镜像I/O操作，开销较大。所以，为了减少I/O操作，把当前使用的文件目录缓存在内存，以后要使用该文件时只要在内存中操作，从而降低了磁盘操作次数，提高了文件系统的访问速度。

## 软链接和硬链接

   有时希望给某个文件取个别名，那么在Linux中可以通过 **硬链接（Hard Link）和软链接（Symbolic Link）** 的方式来实现，他们都是比较特殊的文件，但实现方式也是不相同的。

   硬链接是 **多个目录项中的 索引节点 指向一个文件** ，也就是执行同一个inode，但是inode是不可能跨越文件系统的，每个文件系统都有格子的inode数据结构和列表，所以 **硬链接是不可用于跨文件系统的**。由于多个目录项都是执行一个inode，那么只有 **删除文件的所有硬链接以及源文件时，系统才会彻底删除该文件**。

[![image.png](https://i.postimg.cc/pTysRfP2/image.png)](https://postimg.cc/5YdBmFHG)

   软链接相当于重新创建一个文件，这个文件有 **独立的inode** ，但是这个 **文件的内容是另一个文件的路径**，所以访问软连接的时候，实际上相当于访问到了另外一个文件，所以 **软链接是可以跨文件系统的**，甚至 **目标文件被删除了，链接文件还是在的，只不过指向的文件找不到了而已** 。

[![image.png](https://i.postimg.cc/3RsSJkLz/image.png)](https://postimg.cc/5Ymqs2Wm)

## 文件I/O

> 文件的读写方式各有千秋，对文件的I/O分类也非常多，常见的有

+ 缓冲与非缓冲I/O
+ 直接与非直接I/O
+ 阻塞与非阻塞I/O VS 同步与异步I/O

### 缓冲与非缓冲I/O

   文件操作的标准库是可以实现数据的缓存，那么**根据 是否利用标准库缓冲，可以把文件I/O分为缓冲I/O和非缓冲I/O：

+ 缓冲I/O，利用的是标准库的缓存实现文件的加速访问，而标准库在通过系统调用访问文件。
+ 非缓冲I/O，直接通过系统调用访问文件，不经过标准库缓存。

   这里所说的 **缓冲** 特指标准库内部实现的缓冲。

   比如说，很多程序遇到换行时才真正输出，而换行前的内容，其实就是被标准库暂时缓存了起来，这样做的目的是，减少系统调用的次数，毕竟系统调用是由CPU上下文（CPU寄存器和程序计数器的切换）的开销的。

### 直接与非直接I/O

> 我们都知道磁盘I/O是非常慢的，所以Linux内核为了减少磁盘I/O次数，在系统调用后，会把用户数据拷贝到内核中缓存起来，这个内核缓存空间就是 **页缓存**，只有当缓存满足某些条件的时候，才发起磁盘I/O的请求。

   那么， **根据是否利用操作系统的缓存，可以把文件I/O分支直接I/O与非直接I/O：

+ 直接I/O，不会发生内核缓存何用程序之间数据复制，而是直接经过文件系统访问磁盘。
+ 非直接I/O，读操作时，数据从内核缓存中拷贝给用户程序，写操作时，数据从用户程序拷贝给内核缓存，再由内核决定什么时候写入数据到磁盘。

   如果在使用文件操作系统调用函数时，指定了 **O_DIRECT** 标志，则表示使用直接I/O，如果没有设置过，默认使用的是非直接I/O。

> 如果用了非直接I/O进行写数据操作，内核什么情况下才会把缓存数据写入到磁盘？

+ 在调用 write 的最后，当发现内核缓存的数据太多的时候，内核会把数据写到磁盘上；
+ 当用户主动调用 sync ，内核缓存会刷到磁盘上
+ 当内存十分紧张，无法再分配页面时，也会把内核数据写到磁盘上；
+ 内核缓存的数据的缓存时间超过某个时间时，也会把数据刷到磁盘上；

### 阻塞与非阻塞I/O VS 同步与异步I/O

   阻塞I/O，当用户程序执行read，线程会被阻塞，一直等到内核数据准备好，并把数据从内核缓冲区拷贝到应用程序的缓冲区中，当拷贝过程完成，read才会返回。

   注意：**阻塞等待的是 内核数据准备好 和 数据从内核态拷贝到用户态 这两个过程

[![image.png](https://i.postimg.cc/YqXb9FcP/image.png)](https://postimg.cc/7f2gtfZ1)

   非阻塞I/O，非阻塞的read请求数据未准备好的情况下⽴即返回，可以继续往
下执⾏，此时应⽤程序不断轮询内核，直到数据准备好，内核将数据拷⻉到应⽤程序缓冲区， read 调⽤才可以获取到结果。过程如下图：

[![image.png](https://i.postimg.cc/QNgjR8LC/image.png)](https://postimg.cc/LhXdPM8F)

   注意， **这⾥最后⼀次 read 调⽤，获取数据的过程，是⼀个同步的过程，是需要等待的过程。这⾥的同步指的是内核态的数据拷⻉到⽤户程序的缓存区这个过程** 。

   举个例⼦，访问管道或 socket 时，如果设置了 **O_NONBLOCK** 标志，那么就表示使⽤的是⾮阻塞 I/O 的⽅式访问，⽽不做任何设置的话，默认是阻塞 I/O。

   应⽤程序每次轮询内核的 I/O 是否准备好，感觉有点傻乎乎，因为轮询的过程中，应⽤程序啥也做不了，只是在循环。为了解决这种傻乎乎轮询⽅式，于是 **I/O 多路复⽤** 技术就出来了，如 select、 poll，它是通过 I/O 事件分发，当内核数据准备好时，再以事件通知应⽤程序进⾏操作。这个做法⼤⼤改善了应⽤进程对 CPU 的利⽤率，在没有被通知的情况下，应⽤进程可以使⽤ CPU 做其他的事情。下图是使⽤ select I/O 多路复⽤过程。注意， **read** 获取数据的过程（数据从内核态拷⻉到⽤户态的过程），也是⼀个 **同步的过程** ，需要等待：

[![image.png](https://i.postimg.cc/3RkQWhWM/image.png)](https://postimg.cc/JDC2d9bK)

   实际上，⽆论是阻塞 I/O、⾮阻塞 I/O，还是基于⾮阻塞 I/O 的多路复⽤ **都是同步调⽤。因为它们在 read调⽤时，内核将数据从内核空间拷⻉到应⽤程序空间，过程都是需要等待的，也就是说这个过程是同步的，如果内核实现的拷⻉效率不⾼， read 调⽤就会在这个同步过程中等待⽐较⻓的时间**。

   ⽽真正的 **异步 I/O** 是「内核数据准备好」和「数据从内核态拷⻉到⽤户态」这两个过程都不⽤等待。

   当我们发起 aio_read 之后，就⽴即返回，内核⾃动将数据从内核空间拷⻉到应⽤程序空间，这个拷⻉过程同样是异步的，内核⾃动完成的，和前⾯的同步操作不⼀样，应⽤程序并不需要主动发起拷⻉动作。过程如下图

[![image.png](https://i.postimg.cc/tTknRh1v/image.png)](https://postimg.cc/Q9Bd0KJc)

   以下是几种I/O模型

[![image.png](https://i.postimg.cc/MHvQHnJ7/image.png)](https://postimg.cc/m1WD62Dk)

   我们知道了I/O是分两个过程的：

1. 数据准备的过程
2. 数据从内核空间拷贝到用户进程缓冲区的过程

   阻塞I/O会阻塞在 过程1 和 过程2 ，而非阻塞I/O和基于非阻塞I/O的多路复用只会阻塞在 过程2，所以这三个都可以认为是同步I/O。

   异步I/O则不同，过程1 和 过程2 都不会阻塞。

> 用故事去理解这几种I/O模型

   举个你去饭堂吃饭的例⼦，你好⽐⽤户程序，饭堂好⽐操作系统。

   阻塞 I/O 好⽐，你去饭堂吃饭，但是饭堂的菜还没做好，然后你就⼀直在那⾥等啊等，等了好⻓⼀段时间终于等到饭堂阿姨把菜端了出来（数据准备的过程），但是你还得继续等阿姨把菜（内核空间）打到你的饭盒⾥（⽤户空间），经历完这两个过程，你才可以离开。

   ⾮阻塞 I/O 好⽐，你去了饭堂，问阿姨菜做好了没有，阿姨告诉你没，你就离开了，过⼏⼗分钟，你⼜来饭堂问阿姨，阿姨说做好了，于是阿姨帮你把菜打到你的饭盒⾥，这个过程你是得等待的。

   基于⾮阻塞的 I/O 多路复⽤好⽐，你去饭堂吃饭，发现有⼀排窗⼝，饭堂阿姨告诉你这些窗⼝都还没做好菜，等做好了再通知你，于是等啊等（ select 调⽤中），过了⼀会阿姨通知你菜做好了，但是不知道哪个窗⼝的菜做好了，你⾃⼰看吧。于是你只能⼀个⼀个窗⼝去确认，后⾯发现 5 号窗⼝菜做好了，于是你让 5 号窗⼝的阿姨帮你打菜到饭盒⾥，这个打菜的过程你是要等待的，虽然时间不⻓。打完菜后，你⾃然就可以离开了。

   异步 I/O 好⽐，你让饭堂阿姨将菜做好并把菜打到饭盒⾥后，把饭盒送到你⾯前，整个过程你都不需要任
何等待。

# 设备管理

## 设备控制器

> 电脑有非常的的输入输出设备，比如键盘、鼠标、显示器、网卡、硬盘、打印机、音响等，每个设备的用法和功能都不同，操作系统如何把这些输入输出设备统一管理的呢？为了屏保设备之间的差异，每个设备之间都有一个叫 **设备控制器** （Device Control）的组件，比如硬盘有硬盘控制器、显示器有视频控制器等。

[![image.png](https://i.postimg.cc/Znn60zpW/image.png)](https://postimg.cc/vxR4SjPy)

   因为这些控制器都很清楚知道对应设备的用法和功能，所以CPU是通过控制器和设备打交道的。设备控制器里有芯片，它可执行自己的逻辑，也有自己的寄存器，用来与CPU进行通信，比如：

+ 通过写入这些寄存器，操作系统可以命令设备发送数据、接收数据、开启或关闭、或者执行某些其他操作。
+ 通过读取这些寄存器，操作系统可以了解设备的状态，是否准备好接收一个新的命令等。

   实际上，控制器是由三类寄存器，他们分别是 **状态寄存器（Status Register）、命令寄存器（Command Register）以及数据寄存器（Data Reister）** ，如下图：

[![image.png](https://i.postimg.cc/bvjnjtvV/image.png)](https://postimg.cc/v43TrDf5)

+ 数据寄存器，CPU项I/O设备写入需要传输的数据，比如要打印的是内容是 “hello”，CPU就要先发送一个“h”字符给到对应的I/O设备
+ 命令寄存器，CPU发送一个命令，告诉I/O设备，要进行输入/输出操作，于是就会
+ 状态寄存器，目的是告诉CPU，现在已经再工作或工作已完成，如果在工作状态，CPU再发送数据或名命令过来，都是没用的，直到前面的工作完成，状态寄存标记已完成，CPU才能发送下一个字符和命令。

CPU通过读写设备控制器中的寄存器控制设备，比CPU直接控制输入输出设备，要方便和标准很多。
另外，输入输出设备可分为2大类：**块设备（Block Device）和字符设备（Character Device）**。

+ **块设备**，把数据存储再固定大小的块中，每个块有自己的地址，硬盘、USB是常见的块设备。
+ **字符设备**，已字符为单位发送或接收一个字符流，字符设备是不可寻址的，也没有任何寻道操作，鼠标是常见的字符设备。

块设备通常传输的数据量回非常大，于是控制器设立了一个可读写的**数据缓冲区**。

+ CPU写入数据控制器的缓冲区时，当缓冲区数据满时，才会发给设备。
+ CPU读取数据控制器的缓冲区时，也需要当缓冲区数据满时，才拷贝到内存。

这样是为了减少对设备的频繁操作。

那CPU是如何与设备的控制寄存器和数据缓冲区进行通信的？存在2个方法：

+ **端口I/O**，每个控制寄存器被分配一个I/O端口，可以通过特殊的汇编指令操作这些寄存器，比如 **in/ou**类似指令。
+ **内存映射I/O**，将所有控制寄存器映射到内存空间中，这样就可以项读写内存一样读写数据缓冲区。

## I/O控制方式

控制器的寄存器一般会有状态标记位，用来标识输入或输出操作是否完成。于是，有第一种 **轮询等待** 的方法，让CPU一直查寄存器的状态，直到状态标记位为完成，然后再进行下一步操作。很明显这种方式会占用CPU的全部时间。

第二种方法是 **中断** ，通知操作系统数据已经准备好。我们一般会以有一个硬件的 **中断控制器** ，当设备完成任务后触发中断到中断控制器，中断控制器就通知CPU，一个中断产生了，COU可以暂停当前进程来处理中断。

另外中断有两种，一种方式是 **软中断**，例如代码调用 **INT** 指令，一种是**硬件中断**，就是硬件通过中断控制器触发的。

但中断的方式对于频繁读写数据的磁盘并不友好，这样CPU容易经常被打断，会占用大量的时间。对于这一类设备的问题的解决方法是使用DMA(Direct Memory Access)功能，它可以使得设备再CPU不参与的情况下，能够自行完成把设备I/O数据放入到内存。那要实现DMA功能要有DMA控制器硬件的支持。

[![image.png](https://i.postimg.cc/1RnQTDRQ/image.png)](https://postimg.cc/hhB6Qz7y)

DMA的工作方式如下：
+ CPU需对DMA控制器下发指令，告诉它想读取多少数据，读完的数据放在内存的某个地方就可以了；
+ 接下来，DMA控制器回想磁盘控制器发出指令，通知他从磁盘读数据到其内部的缓冲区中，接着磁盘控制器将缓冲区的数据传输到内存；
+ 当磁盘控制器把数据传输到内存的操作完成后，磁盘控制器再总线上发出一个确认成功的信号的DMA控制器；
+ DMA控制器收到信号后，DMA控制器发中断通知CPU指令完成，CPU就可以直接用内存里线程的数据了。

可以看到，CPU当要读取磁盘数据的时候，只需给DMA控制器下发指令，告诉它想读取多少数据，然后就可以直接用内存里的数据了，仅仅在传送开始和结束时，需要CPU参与。这样可以大大提高CPU的效率。

## 设备驱动程序

虽然设备控制器屏蔽了设备的众多细节，但每种设备的控制器的寄存器、缓冲区等使用模式都是不同的，所以为了屏蔽这些差异，操作系统还提供了一系列的 **设备驱动程序** （Device Driver），它负责实现设备控制器的驱动，使得CPU可以像操作文件一样操作设备。

[![image.png](https://i.postimg.cc/xdswkPL6/image.png)](https://postimg.cc/FfLW83WS)

设备控制器不属于操作系统范畴，它属于硬件，而设备驱动程序属于操作系统的一部分，操作系统的内核代码可以想本地调用代码一样使用设备驱动程序的接口，而设备驱动程序时面向设备控制器的代码，他发出操控设备控制器的指令后，才可以操作设备控制器。

不同的设备控制器虽然功能不同，但是 **设备驱动程序会提供统一的接口给操作系统**，这样不同的设备驱动程序就可以共同使用，而不用关心设备控制器的具体实现。

[![image.png](https://i.postimg.cc/jSh5FGrC/image.png)](https://postimg.cc/PCPTLVJk)

前面所说的中断，当设备完成事情，则会发送中断来通知操作系统了。那操作系统就需要一个地方来处理这个中断，这个地方也就是再设备驱动程序里，他会及时想要控制器来发送中断请求，并根据这个中断的类型调用响应的**中断处理程序**进行处理。

通常，设备驱动程序初始化的时候，要注册一个该设备的中断处理函数。

[![image.png](https://i.postimg.cc/k4svMj85/image.png)](https://postimg.cc/CBZqmscy)

可以看下中断处理程序的处理流程：
1. 在I/O时，设备控制器如何已经准备好数据，则会通过中断控制器向CPU发送中断请求；
2. 保护被中断进程的CPU上下文；
3. 转入相应的设备中断处理函数；
4. 进行中断处理；
5. 恢复被中断进程的CPU上下文；
6. 继续执行被中断进程的后续代码。

## 通用块层

对于块设备，为了减少不同块设备的差异代理的影响，Linux通过一个统一的**通用块**层，来管理不同的块设备。

通用块层是处于文件系统和磁盘驱动中间的一个块设备抽象层，它主要有两个功能：
+ 第一个功能，向上位文件系统和应用程序，提供访问块设备的标准接口，向下把各种不同的磁盘设备抽象为统一的块设备，并在内核层面，提供一个框架来管理这些设备的驱动程序；
+ 第二个功能，通用层还会给文件系统和应用程序发来的I/O请求排队，接着会对队列重新排序、请求合并等方式，也就是I/O调度，主要目的是为了提高磁盘读写的效率。

Linux内存支持5中I/O调度算法，分别是：
+ 没有调度算法
+ 先入先出调度算法
+ 完全公平调度算法
+ 优先级调度算法
+ 最终期限调度算法

## 存储系统I/O软件分层

可以把Linux存储系统的I/O由上到下分为3个层次，分别是文件系统层、通用块层、设备层。他们整个层次关系如下图：

[![image.png](https://i.postimg.cc/C1cd6hcL/image.png)](https://postimg.cc/G8sc4C0Z)

这三个层次的作用是：
+ 文件系统层，包括虚拟文件系统和其他文件系统的具体实现，它向上为应用程序统一提供了标准的文件访问接口，向下会通过通用块层来存储和管理磁盘数据。
+ 通用块层，包括块设备的I/O队列和I/O调度器，他会对文件系统的I/O请求进行排队，并对请求进行合并，然后再向下传递给设备层。
+ 设备层，包括硬件设备、设备控制器和设备驱动程序，它负责最终物理设备的I/O操作。

有了文件系统接口之后，不但可以通过文件系统的命令行操作设备，也可以通过应用程序调用 **read、write** 函数，就像读写文件一样操作设备，所以说设备在Linux下，也只是一个特殊的文件。

但是，除了读写操作，还需要有检查特定于设备的功能和属性。于是需要**ioctl**接口，他表示输入输出控制接口，适用于配置和修改特定设备属性的通用接口。

另外，存储系统的I/O操作是整个系统最慢的一个环节，所以Linux提供了不少缓存机制来提高I/O的效率。

+ 为了提高文件的访问效率，会使用 **页缓存、索引节点缓存、目录项缓存** 等多种缓存机制，目的是为了减少对块设备的直接调用。
+ 为了提高块设备的访问效率，会使用 **缓冲区**，来缓存块设备的数据。

## 键盘敲入字母时，期间发生了什么

基于前面的内容，可以对输入输出设备的管理有了一定的认识，那 键盘敲入字母时，操作系统期间发生了什么呢？

可以先看看CPU的硬件架构图：

[![image.png](https://i.postimg.cc/brNSz66g/image.png)](https://postimg.cc/mzJgjSW1)

CPU里面的内存接口，直接和系统总线通信，然后系统总线再接入一个I/O桥接器，这个I/O桥接器另一边介入了内存总线，使得CPU和内存通信。再另一边，又介入了一个I/O总线，用来连接I/O设备，比如键盘，显示器等。

当用户输入了键盘字符，**键盘控制器** 就会产生扫描码数据，并将其换南充在键盘控制器的寄存器中，紧接着键盘控制器通过总线给CPU发送 **中断请求**。

CPU收到中断请求后，操作系统会暂停当前进程的执行，**保存被中断进程的CPU上下文** ，然后调用键盘的 **中断处理程序**。


键盘的中断处理程序是在 **键盘驱动程序** 初始化时注册的，那键盘 **中断处理函数** 的功能就是从键盘控制器的寄存器的缓冲区读取扫描码，再根据扫描码找到用户在键盘输入的字符，如果输入的字符时显示字符，那就会把扫描码翻译成对应显示的ASCII码，比如用户在键盘输入的是字母A，是显示字符，于是就会把扫描码翻译成A字符的ASCII码。

得到了显示字符的ASCII码后，就会把ASCII码发到 **读缓冲区队列**，接下来就是要把显示字符显示屏幕了，显示设备的驱动程序会定时从读缓冲区队列读取数据放到**写缓冲区队列**，最后把**写缓冲区队列的数据一个一个写入到显示设备的控制器的寄存器中的数据缓冲区，最后将这些数据显示在屏幕里。

显示出结果后，**恢复被中断进程的上下文**。

# 网络系统

## Linux系统是如何收发网络包的？

### 网络模型
### Linux网络协议栈
### Linux发送网络包的流程
### 总结

## 零拷贝
### 为什么要有DMA技术
### 传统的文件传输有多糟糕
### 如何优化文件传输的性能
### 如何实现零拷贝
#### mmap+write
#### sendfile
#### 使用零拷贝技术的项目
#### PageCache有什么作用
#### 大文件传输有什么作用
### 总结

## I/O多路复用
### select、poll、epoll
#### 最基本的socket模型
#### 如何服务更多的用户
#### 多进程模型
#### 多线程模型
#### I/O多路复用
#### select/poll
#### epoll
#### 总结

## 高性能网络模式：Reactor和Proactor
### Reactor模式
### Proactor模式
### 总结