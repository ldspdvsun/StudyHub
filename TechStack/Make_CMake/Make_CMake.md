# Makefile简介

* GNU Make 官方网站：https://www.gnu.org/software/make/

* GNU Make 官方文档下载地址：https://www.gnu.org/software/make/manual/
* Makefile Tutorial：https://makefiletutorial.com/

## 基本格式

```makefile
targets:prerequisties
[tab]键command
```

* target: 目标文件，可以是执行文件，也可以是一个标签
* prerequisite: 要生成那个target所需要的文件或目标
* command: make需要执行的命令，如果命令以@开始，将不会输出命令

```makefile
clean:
	@rm -rf ./*.o

root@3570ce881c55# make clean
root@3570ce881c55#

clean:
	rm -rf ./*.o
root@3570ce881c55# make clean
rm -rf ./*.o
root@3570ce881c55#
```



## Makefile规则

* make会在当前目录下找到一个名字叫Makefile或makefile的文件，如果找到，它会找文件中第一个目标文件（target），并把这个文件作为最终的目标文件
* 如果 target 文件不存在，或是 target 文件依赖的 .o 文件(prerequities)的文件修改时间要比 target 这个文件新，就会执行后面所定义的命令 command 来生成 target 这个文件
* 如果 target 依赖的 .o 文件（prerequisties）也存在，make 会在当前文件中找到 target 为 .o 文件的依赖性，如果找到，再根据那个规则生成 .o 文件

## 伪目标

为了避免target和Makefile同级目录下`文件/文件夹`重名的情况，可以使用一个特殊的标记`.PHONY`来显示地指明一个目标是`伪目标`，向make说明，不管是否有这个文件/文件夹，这个目标就是“伪目标”。

```makefile
.PHONY : clean
```

# Makefile的变量

变量在声明式需要给予初始值，当使用时，需要给变量名前加上“$”符号，并用小括号()把变量给包裹起来

## 变量的定义

```makefile
cpp := src/main.c
obj := objs/main.o
```

## 变量的引用

* 可以使用`()`或`{}`

```makefile
cpp := src/main.c
obj := objs/main.o

$(obj) : $(cpp)
	@gcc -c $(cpp) -o $(obj)
compile: $(obj)
```

## 预定义变量

* `$@`: 目标 (target)的完整名称
* `$<`: 第一个依赖文件（prerequisties）的名称
* `$^`: 所有的依赖文件（prerequisties），以空格分开，不包含重复的依赖文件

```makefile
cpp := src/main.cpp 
obj := objs/main.o

$(obj) : ${cpp}
	@g++ -c $< -o $@
	@echo $^

compile : $(obj)
.PHONY : compile
```

# Makefile常用符号

## =

* 简单的赋值运算符，用于将右边的值分配给左边的变量
* 重新定义将使用新的值

> 示例

```makefile
HOST_ARCH = amd64
HOST_ARCH = amd32
TARGET_ARCH = $(HOST_ARCH)

output:
	echo TARGET_ARCH
```

## :=

* 立即赋值运算符，用于在定义变量是立即求值
* 该值在定义后将不再修改

> 示例

```makefile
HOST_ARCH = amd64
HOST_ARCH = amd32
TARGET_ARCH = $(HOST_ARCH)
```

## ?=

* 默认赋值运算符，如果该变量已经定义不进行任何操作，如果该变量尚未定义则求值并分配

> 示例

```makefile
HOST_ARCH  = aarch64
HOST_ARCH ?= amd64

debug:
    @echo $(HOST_ARCH)
```

## +=

+ 累加

```makefile
CXXFLAGS := -m64 -fPIC -g -O0 -std=c++11 -w -fopenmp

CXXFLAGS += $(include_paths)
```

## \

+ 续行符

```makefile
LDLIBS := cudart opencv_core \
          gomp nvinfer protobuf cudnn pthread \
          cublas nvcaffe_parser nvinfer_plugin 
```

## * 与 %

* `*`: 通配符表示匹配任意字符串，可以用在目录名或文件名中
* `%`: 通配符表示匹配任意字符串，并将匹配到的字符串作为变量使用

# Makefile常用函数

函数调用，很想变量的使用，也是以“$”来标识

```makefile
$(fn,arguments) or ${fn,arguments}
```

+ fn: 函数名
+ arguments: 函数参数，参数间以逗号`,`分隔，而函数名和参数夹以“空格”分隔

## shell

```makefile
$(shell <comand> <arguments>)
```

+ 名称：shell命令函数——shell
+ 功能：调用shell命令command
+ 返回值：函数返回shell命令command的执行结果

> 示例

```makefile
# shell 指令，找到src下所有的.c文件
c_srcs := $(shell find src -name "*.c")

# shell 指令，获取计算机架构
HOST_ARCH := $(shell uname -m)

output_c_srcs:
	@echo $(c_srcs)
	@echo $(HOST_ARCH)
```

```sh
root@3570ce881c55:~/code/vscode-server/Personal/CMake# make output_c_srcs
src/main.c src/framework.c src/pthread/pthread_demo_01.c src/proc/mem_segments.c src/temp/temp.c src/file/S0100201GN_02.c
x86_64
root@3570ce881c55:~/code/vscode-server/Personal/CMake# 
```

## subst

```makefile
$(subst <from>,<to>,<text>)
```

+ 名称：字符串替换函数
+ 功能：把字符串<text>中的<from>字符串替换成<to>
+ 返回：函数返回被替换后的字符串

> 示例

```makefile
c_srcs := $(shell find src -name "*.c")
c_objs_1 := $(subst src/,objs/,$(c_srcs))
c_objs_2 := $(subst .c,.o,$(c_objs_1))

out_substs:
	@echo ${c_srcs}
	@echo ==========================
	@echo ${c_objs_1}
	@echo ==========================
	@echo ${c_objs_2}
```

```sh
root@3570ce881c55:~/code/vscode-server/Personal/CMake# make out_substs
src/main.c src/framework.c src/pthread/pthread_demo_01.c src/proc/mem_segments.c src/temp/temp.c src/file/S0100201GN_02.c
==========================
objs/main.c objs/framework.c objs/pthread/pthread_demo_01.c objs/proc/mem_segments.c objs/temp/temp.c objs/file/S0100201GN_02.c
==========================
objs/main.o objs/framework.o objs/pthread/pthread_demo_01.o objs/proc/mem_segments.o objs/temp/temp.o objs/file/S0100201GN_02.o
root@3570ce881c55:~/code/vscode-server/Personal/CMake# 
```

## patsubst

```makefile
$(patsubst <pattern>,<replacement>,<text)
```

+ 名称：模式字符串替换函数
+ 功能：通配符`%`，表示任意长度的字符串，从<text>中取出<pattern>，替换成<replacepattern>
+ 返回：函数返回被替换过后的字符串

> 示例

```makefile
c_srcs := $(shell find src -name "*.c")
c_patsubst:=${patsubst src/%.c,objs/%.o,$(c_srcs)}
out_patsubst:
	@echo ${c_srcs}
	@echo ==========================
	@echo $(c_patsubst)
```

```sh
root@3570ce881c55:~/code/vscode-server/Personal/CMake# make out_patsubst
src/main.c src/framework.c src/pthread/pthread_demo_01.c src/proc/mem_segments.c src/temp/temp.c src/file/S0100201GN_02.c
==========================
objs/main.o objs/framework.o objs/pthread/pthread_demo_01.o objs/proc/mem_segments.o objs/temp/temp.o objs/file/S0100201GN_02.o
root@3570ce881c55:~/code/vscode-server/Personal/CMake# 
```

