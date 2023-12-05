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

## foreach

```makefile
$(foreach <var>,<list>,<test>)
```

+ 名称：循环函数
+ 功能：把字符串<list>中的元素逐一取出来，执行<text>包含的表达式
+ 返回：<test>返回每个字符串组成的整个字符串

> 示例

```makefile
include_paths := /usr/include \
				/root/code/vscode-server/Personal/CMake/include
include_paths_foreach:=$(foreach item,$(include_paths),-I $(item))
out_include:
	@echo $(include_paths)
	@echo ----------------------
	@echo $(include_paths_foreach)
```

foreach类比python

```python
for item in includes:
    item = "-I " + item
```

同等效果

```makefile
include_paths := /usr/include \
				/root/code/vscode-server/Personal/CMake/include
I_flag := $(include_paths:%=-I %)
out_include:
	@echo $(include_paths)
	@echo ----------------------
	@echo $(I_flag)
```

## dir

```makefile
$(dir <name...>)
```

+ 功能：取目录函数
+ 功能：从文件名序列中取出目录部分，目录部分是指最后一个反斜杠（‘/’）之前的那部分，如果没有反斜杠，那么返回“./”.
+ 返回：返回文件名序列的目录部分

> 示例

```sh
$(dir src/foo.c hacks)
# 返回值是“src/ ./”
```

```makefile
.PHONY: out_dir compile 
include_paths := /root/code/vscode-server/Projects/Make_CMake/include \
				/usr/include

include_path := $(foreach item,$(include_paths),-I $(item))
c_srcs := $(shell find src -name "*.c")
c_objs:= $(patsubst src/%.c,objs/%.o,$(c_srcs))
out_dirs:= $(dir $(c_srcs))

objs/%.o : src/%.c
	@mkdir -p $(dir $@)
	@gcc -c $^ -o $@ $(include_path)

compile: $(c_objs)

out_dir:
	@echo ===============
	@echo $(include_path) 
	@echo ===============
	@echo $(c_srcs) 
	@echo ===============
	@echo $(c_objs) 
	@echo ===============
	@echo $(out_dirs) 
```

```sh
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# make out_dir
===============
-I /root/code/vscode-server/Projects/Make_CMake/include -I /usr/include
===============
src/main.c src/pthread/pthread_demo_01.c src/proc/mem_segments.c src/temp/temp.c src/file/S0100201GN_02.c
===============
objs/main.o objs/pthread/pthread_demo_01.o objs/proc/mem_segments.o objs/temp/temp.o objs/file/S0100201GN_02.o
===============
src/ src/pthread/ src/proc/ src/temp/ src/file/
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# 
```

## notdir

```makefile
$(notdir <name...>)
```

> 示例

```sh
libs:= $(shell find /usr/lib -name lib*)
libs_notdir:= $(notdir $(shell find /usr/lib -name lib*))

out_notdir:
	@echo ============= libs =============
	@echo $(libs) 
	@echo ============= libs_notdir =============
	@echo $(libs_notdir) 
```

```sh
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# make out_notdir
============= libs =============
/usr/lib /usr/lib/usrmerge/lib /usr/lib/x86_64-linux-gnu/libgcc_s.so.1 /usr/lib/x86_64-linux-gnu/libe2p.so.2 /usr/lib/x86_64-linux-gnu/libBrokenLocale.so.1 /usr/lib/x86_64-linux-gnu/libcap-ng.so.0.0.0 /usr/lib/x86_64-linux-gnu/libformw.so.6 /usr/lib/x86_64-linux-gnu/libapt-private.so.0.0 /usr/lib/x86_64-linux-gnu/libtasn1.so.6 /usr/lib/x86_64-linux-gnu/libunistring.so.2 /usr/lib/x86_64-linux-gnu/libcom_err.so.2.1 /usr/lib/x86_64-linux-gnu/libpamc.so.0.82.1 /usr/lib/x86_64-linux-gnu/libgnutls.so.30 /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4 /usr/lib/x86_64-linux-gnu/libss.so.2.0 /usr/lib/x86_64-linux-gnu/libxxhash.so.0.8.1 /usr/lib/x86_64-linux-gnu/libmount.so.1 /usr/lib/x86_64-linux-gnu/libunistring.so.2.2.0 /usr/lib/x86_64-linux-gnu/libdrop_ambient.so.0.0.0 /usr/lib/x86_64-linux-gnu/libffi.so.8.1.2 /usr/lib/x86_64-linux-gnu/libncursesw.so.6.4 /usr/lib/x86_64-linux-gnu/libtasn1.so.6.6.3 /usr/lib/x86_64-linux-gnu/libpsx.so.2.66 /usr/lib/x86_64-linux-gnu/libsystemd.so.0.35.0 /usr/lib/x86_64-linux-gnu/libaudit.so.1 /usr/lib/x86_64-linux-gnu/libpam_misc.so.0 /usr/lib/x86_64-linux-gnu/libapt-private.so.0.0.0 /usr/lib/x86_64-linux-gnu/libgcrypt.so.20 /usr/lib/x86_64-linux-gnu/libp11-kit.so.0.3.0 /usr/lib/x86_64-linux-gnu/libe2p.so.2.3 /usr/lib/x86_64-linux-gnu/libext2fs.so.2.4 /usr/lib/x86_64-linux-gnu/libformw.so.6.4 /usr/lib/x86_64-linux-gnu/libsmartcols.so.1.1.0 /usr/lib/x86_64-linux-gnu/libmd.so.0 /usr/lib/x86_64-linux-gnu/librt.so.1 /usr/lib/x86_64-linux-gnu/libsmartcols.so.1 /usr/lib/x86_64-linux-gnu/libuuid.so.1 /usr/lib/x86_64-linux-gnu/libpcre2-8.so.0 /usr/lib/x86_64-linux-gnu/libdb-5.3.so /usr/lib/x86_64-linux-gnu/gconv/libJIS.so /usr/lib/x86_64-linux-gnu/gconv/libJISX0213.so /usr/lib/x86_64-linux-gnu/gconv/libCNS.so /usr/lib/x86_64-linux-gnu/gconv/libISOIR165.so /usr/lib/x86_64-linux-gnu/gconv/libKSC.so /usr/lib/x86_64-linux-gnu/gconv/libGB.so /usr/lib/x86_64-linux-gnu/libattr.so.1 /usr/lib/x86_64-linux-gnu/libmemusage.so /usr/lib/x86_64-linux-gnu/libmenuw.so.6.4 /usr/lib/x86_64-linux-gnu/libaudit.so.1.0.0 /usr/lib/x86_64-linux-gnu/libgpg-error.so.0.33.1 /usr/lib/x86_64-linux-gnu/libstdc++.so.6 /usr/lib/x86_64-linux-gnu/libz.so.1 /usr/lib/x86_64-linux-gnu/libpcprofile.so /usr/lib/x86_64-linux-gnu/libseccomp.so.2 /usr/lib/x86_64-linux-gnu/libidn2.so.0.3.8 /usr/lib/x86_64-linux-gnu/libgcrypt.so.20.4.1 /usr/lib/x86_64-linux-gnu/libz.so.1.2.13 /usr/lib/x86_64-linux-gnu/libcap.so.2 /usr/lib/x86_64-linux-gnu/libgnutls.so.30.34.2 /usr/lib/x86_64-linux-gnu/libdebconfclient.so.0 /usr/lib/x86_64-linux-gnu/libuuid.so.1.3.0 /usr/lib/x86_64-linux-gnu/libmvec.so.1 /usr/lib/x86_64-linux-gnu/libdrop_ambient.so.0 /usr/lib/x86_64-linux-gnu/libthread_db.so.1 /usr/lib/x86_64-linux-gnu/libffi.so.8 /usr/lib/x86_64-linux-gnu/libudev.so.1.7.5 /usr/lib/x86_64-linux-gnu/libsystemd.so.0 /usr/lib/x86_64-linux-gnu/libpanelw.so.6.4 /usr/lib/x86_64-linux-gnu/libnss_hesiod.so.2 /usr/lib/x86_64-linux-gnu/libc_malloc_debug.so.0 /usr/lib/x86_64-linux-gnu/libproc2.so.0 /usr/lib/x86_64-linux-gnu/libnsl.so.1 /usr/lib/x86_64-linux-gnu/liblzma.so.5.4.1 /usr/lib/x86_64-linux-gnu/libhogweed.so.6.6 /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libutil.so.1 /usr/lib/x86_64-linux-gnu/libcrypt.so.1.1.0 /usr/lib/x86_64-linux-gnu/libsepol.so.2 /usr/lib/x86_64-linux-gnu/libapt-pkg.so.6.0.0 /usr/lib/x86_64-linux-gnu/libgmp.so.10.4.1 /usr/lib/x86_64-linux-gnu/liblz4.so.1.9.4 /usr/lib/x86_64-linux-gnu/libgmp.so.10 /usr/lib/x86_64-linux-gnu/libproc2.so.0.0.1 /usr/lib/x86_64-linux-gnu/libdebconfclient.so.0.0.0 /usr/lib/x86_64-linux-gnu/libncursesw.so.6 /usr/lib/x86_64-linux-gnu/libcap-ng.so.0 /usr/lib/x86_64-linux-gnu/libpam.so.0 /usr/lib/x86_64-linux-gnu/libm.so.6 /usr/lib/x86_64-linux-gnu/libudev.so.1 /usr/lib/x86_64-linux-gnu/libtic.so.6 /usr/lib/x86_64-linux-gnu/libnss_files.so.2 /usr/lib/x86_64-linux-gnu/libcrypt.so.1 /usr/lib/x86_64-linux-gnu/libselinux.so.1 /usr/lib/x86_64-linux-gnu/libnettle.so.8 /usr/lib/x86_64-linux-gnu/libhogweed.so.6 /usr/lib/x86_64-linux-gnu/libresolv.so.2 /usr/lib/x86_64-linux-gnu/libbz2.so.1 /usr/lib/x86_64-linux-gnu/libext2fs.so.2 /usr/lib/x86_64-linux-gnu/libpam_misc.so.0.82.1 /usr/lib/x86_64-linux-gnu/libacl.so.1.1.2301 /usr/lib/x86_64-linux-gnu/libpsx.so.2 /usr/lib/x86_64-linux-gnu/libtic.so.6.4 /usr/lib/x86_64-linux-gnu/libxxhash.so.0 /usr/lib/x86_64-linux-gnu/libsemanage.so.2 /usr/lib/x86_64-linux-gnu/libmount.so.1.1.0 /usr/lib/x86_64-linux-gnu/libblkid.so.1.1.0 /usr/lib/x86_64-linux-gnu/libblkid.so.1 /usr/lib/x86_64-linux-gnu/libss.so.2 /usr/lib/x86_64-linux-gnu/libzstd.so.1 /usr/lib/x86_64-linux-gnu/libpcre2-8.so.0.11.2 /usr/lib/x86_64-linux-gnu/libnss_compat.so.2 /usr/lib/x86_64-linux-gnu/libidn2.so.0 /usr/lib/x86_64-linux-gnu/libmd.so.0.0.5 /usr/lib/x86_64-linux-gnu/liblzma.so.5 /usr/lib/x86_64-linux-gnu/libmenuw.so.6 /usr/lib/x86_64-linux-gnu/libbz2.so.1.0 /usr/lib/x86_64-linux-gnu/liblz4.so.1 /usr/lib/x86_64-linux-gnu/libzstd.so.1.5.4 /usr/lib/x86_64-linux-gnu/libp11-kit.so.0 /usr/lib/x86_64-linux-gnu/libdl.so.2 /usr/lib/x86_64-linux-gnu/libpamc.so.0 /usr/lib/x86_64-linux-gnu/libc.so.6 /usr/lib/x86_64-linux-gnu/libbz2.so.1.0.4 /usr/lib/x86_64-linux-gnu/libpanelw.so.6 /usr/lib/x86_64-linux-gnu/libgpg-error.so.0 /usr/lib/x86_64-linux-gnu/libcap.so.2.66 /usr/lib/x86_64-linux-gnu/libnettle.so.8.6 /usr/lib/x86_64-linux-gnu/libnss_dns.so.2 /usr/lib/x86_64-linux-gnu/perl-base/unicore/lib /usr/lib/x86_64-linux-gnu/perl-base/lib.pm /usr/lib/x86_64-linux-gnu/libapt-pkg.so.6.0 /usr/lib/x86_64-linux-gnu/libacl.so.1 /usr/lib/x86_64-linux-gnu/libpam.so.0.85.1 /usr/lib/x86_64-linux-gnu/libattr.so.1.1.2501 /usr/lib/x86_64-linux-gnu/libseccomp.so.2.5.4 /usr/lib/x86_64-linux-gnu/libcom_err.so.2 /usr/lib/x86_64-linux-gnu/libanl.so.1 /usr/lib/x86_64-linux-gnu/libpthread.so.0 /usr/lib/x86_64-linux-gnu/libxcb-sync.so.1.0.0 /usr/lib/x86_64-linux-gnu/libsqlite3.so.0 /usr/lib/x86_64-linux-gnu/libFLAC.so.12 /usr/lib/x86_64-linux-gnu/libdecor-0.so.0.100.1 /usr/lib/x86_64-linux-gnu/libipt.so.2.0.5 /usr/lib/x86_64-linux-gnu/liblsan.so.0 /usr/lib/x86_64-linux-gnu/libdecor /usr/lib/x86_64-linux-gnu/libdecor/plugins-1/libdecor-cairo.so /usr/lib/x86_64-linux-gnu/libcups.so.2 /usr/lib/x86_64-linux-gnu/libubsan.so.1.0.0 /usr/lib/x86_64-linux-gnu/libxcb-glx.so.0 /usr/lib/x86_64-linux-gnu/libvorbisenc.so.2 /usr/lib/x86_64-linux-gnu/libresolv.a /usr/lib/x86_64-linux-gnu/libbabeltrace-ctf-metadata.so.1.0.0 /usr/lib/x86_64-linux-gnu/libcbor.so.0.8.0 /usr/lib/x86_64-linux-gnu/libcrypto.so.3 /usr/lib/x86_64-linux-gnu/libgbm.so.1 /usr/lib/x86_64-linux-gnu/libuv.so.1.0.0 /usr/lib/x86_64-linux-gnu/libGLU.so.1 /usr/lib/x86_64-linux-gnu/libanl.so /usr/lib/x86_64-linux-gnu/libavahi-client.so.3.2.9 /usr/lib/x86_64-linux-gnu/libfido2.so.1.12.0 /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.3 /usr/lib/x86_64-linux-gnu/libdrm_intel.so.1.0.0 /usr/lib/x86_64-linux-gnu/libmpg123.so.0 /usr/lib/x86_64-linux-gnu/libcurl.so.4 /usr/lib/x86_64-linux-gnu/libbabeltrace-ctf-text.so.1 /usr/lib/x86_64-linux-gnu/libglapi.so.0.0.0 /usr/lib/x86_64-linux-gnu/libjsoncpp.so.25 /usr/lib/x86_64-linux-gnu/libm.so /usr/lib/x86_64-linux-gnu/libpython3.11.so.1.0 /usr/lib/x86_64-linux-gnu/libtcl8.6.so /usr/lib/x86_64-linux-gnu/libapparmor.so.1 /usr/lib/x86_64-linux-gnu/libxshmfence.so.1.0.0 /usr/lib/x86_64-linux-gnu/libanl.a /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.32 /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.74.0 /usr/lib/x86_64-linux-gnu/libLLVM-15.so.1 /usr/lib/x86_64-linux-gnu/libelf-0.188.so /usr/lib/x86_64-linux-gnu/libsource-highlight.so.4 /usr/lib/x86_64-linux-gnu/libbabeltrace-ctf-text.so.1.0.0 /usr/lib/x86_64-linux-gnu/libhistory.so.8.2 /usr/lib/x86_64-linux-gnu/libXss.so.1 /usr/lib/x86_64-linux-gnu/libxcb-xfixes.so.0 /usr/lib/x86_64-linux-gnu/libtsan.so.2 /usr/lib/x86_64-linux-gnu/libasyncns.so.0 /usr/lib/x86_64-linux-gnu/libksba.so.8 /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2 /usr/lib/x86_64-linux-gnu/libvorbis.so.0 /usr/lib/x86_64-linux-gnu/libbabeltrace-ctf.so.1.0.0 /usr/lib/x86_64-linux-gnu/libasyncns.so.0.3.1 /usr/lib/x86_64-linux-gnu/libGL.so.1 /usr/lib/x86_64-linux-gnu/libbabeltrace-lttng-live.so.1 /usr/lib/x86_64-linux-gnu/libhistory.so.8 /usr/lib/x86_64-linux-gnu/libreadline.so.8 /usr/lib/x86_64-linux-gnu/libjsoncpp.so.1.9.5 /usr/lib/x86_64-linux-gnu/libz.a /usr/lib/x86_64-linux-gnu/libcc1.so.0 /usr/lib/x86_64-linux-gnu/libg.a /usr/lib/x86_64-linux-gnu/libGLdispatch.so.0 /usr/lib/x86_64-linux-gnu/libopus.so.0.8.0 /usr/lib/x86_64-linux-gnu/libdw-0.188.so /usr/lib/x86_64-linux-gnu/libgssapi_krb5.so.2 /usr/lib/x86_64-linux-gnu/libXft.so.2.3.6 /usr/lib/x86_64-linux-gnu/libdw.so.1 /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0.600.3 /usr/lib/x86_64-linux-gnu/libdrm.so.2.4.0 /usr/lib/x86_64-linux-gnu/libX11.so.6 /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0 /usr/lib/x86_64-linux-gnu/libfido2.so.1 /usr/lib/x86_64-linux-gnu/libxcb-glx.so.0.0.0 /usr/lib/x86_64-linux-gnu/libxshmfence.so.1 /usr/lib/x86_64-linux-gnu/libxcb-dri2.so.0.0.0 /usr/lib/x86_64-linux-gnu/libGLX.so.0.0.0 /usr/lib/x86_64-linux-gnu/libgomp.so.1 /usr/lib/x86_64-linux-gnu/libnss_compat.so /usr/lib/x86_64-linux-gnu/libarchive.so.13 /usr/lib/x86_64-linux-gnu/libz.so /usr/lib/x86_64-linux-gnu/libavahi-client.so.3 /usr/lib/x86_64-linux-gnu/libkrb5.so.3.3 /usr/lib/x86_64-linux-gnu/libkrb5.so.3 /usr/lib/x86_64-linux-gnu/libnghttp2.so.14.24.1 /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0 /usr/lib/x86_64-linux-gnu/libpython3.11.so /usr/lib/x86_64-linux-gnu/libsamplerate.so.0.2.2 /usr/lib/x86_64-linux-gnu/libxcb-dri3.so.0.1.0 /usr/lib/x86_64-linux-gnu/libpython3.11.a /usr/lib/x86_64-linux-gnu/libxcb-randr.so.0 /usr/lib/x86_64-linux-gnu/libdrm_radeon.so.1.0.1 /usr/lib/x86_64-linux-gnu/libGLC.so.0 /usr/lib/x86_64-linux-gnu/libalut.so.0.1.0 /usr/lib/x86_64-linux-gnu/libBrokenLocale.so /usr/lib/x86_64-linux-gnu/perl/5.36.0/lib.pm /usr/lib/x86_64-linux-gnu/libbabeltrace.so.1 /usr/lib/x86_64-linux-gnu/libbabeltrace-ctf-metadata.so.1 /usr/lib/x86_64-linux-gnu/libresolv.so /usr/lib/x86_64-linux-gnu/libopenal.so.1.19.1 /usr/lib/x86_64-linux-gnu/libpulse.so.0.24.2 /usr/lib/x86_64-linux-gnu/libsndio.so.7.2 /usr/lib/x86_64-linux-gnu/libwayland-server.so.0.21.0 /usr/lib/x86_64-linux-gnu/libitm.so.1 /usr/lib/x86_64-linux-gnu/libbabeltrace-dummy.so.1.0.0 /usr/lib/x86_64-linux-gnu/libxcb-dri3.so.0 /usr/lib/x86_64-linux-gnu/libsndfile.so.1.0.35 /usr/lib/x86_64-linux-gnu/libatomic.so.1.2.0 /usr/lib/x86_64-linux-gnu/libGLX_indirect.so.0 /usr/lib/x86_64-linux-gnu/libpulse-simple.so.0 /usr/lib/x86_64-linux-gnu/libOpenGL.so.0 /usr/lib/x86_64-linux-gnu/libxcb-present.so.0 /usr/lib/x86_64-linux-gnu/libmp3lame.so.0.0.0 /usr/lib/x86_64-linux-gnu/libssl.so.3 /usr/lib/x86_64-linux-gnu/libapparmor.so.1.8.4 /usr/lib/x86_64-linux-gnu/libtk8.6.so /usr/lib/x86_64-linux-gnu/libquadmath.so.0.0.0 /usr/lib/x86_64-linux-gnu/libGLEWmx.so.1.13.0 /usr/lib/x86_64-linux-gnu/libutil.a /usr/lib/x86_64-linux-gnu/libasound.so.2.0.0 /usr/lib/x86_64-linux-gnu/libxcb-dri2.so.0 /usr/lib/x86_64-linux-gnu/libgbm.so.1.0.0 /usr/lib/x86_64-linux-gnu/libexpat.a /usr/lib/x86_64-linux-gnu/libdecor-0.so.0 /usr/lib/x86_64-linux-gnu/libdebuginfod-0.188.so /usr/lib/x86_64-linux-gnu/libc_nonshared.a /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1 /usr/lib/x86_64-linux-gnu/libpthread.a /usr/lib/x86_64-linux-gnu/liblsan.so.0.0.0 /usr/lib/x86_64-linux-gnu/libquadmath.so.0 /usr/lib/x86_64-linux-gnu/libxcb-present.so.0.0.0 /usr/lib/x86_64-linux-gnu/libperl.so.5.36 /usr/lib/x86_64-linux-gnu/libgomp.so.1.0.0 /usr/lib/x86_64-linux-gnu/libGLC.so.0.0.7 /usr/lib/x86_64-linux-gnu/libpulse-simple.so.0.1.1 /usr/lib/x86_64-linux-gnu/libdrm_radeon.so.1 /usr/lib/x86_64-linux-gnu/libgssapi_krb5.so.2.2 /usr/lib/x86_64-linux-gnu/libBrokenLocale.a /usr/lib/x86_64-linux-gnu/libsndio.so.7.0 /usr/lib/x86_64-linux-gnu/libdrm_intel.so.1 /usr/lib/x86_64-linux-gnu/libpython3.11.so.1 /usr/lib/x86_64-linux-gnu/libksba.so.8.14.3 /usr/lib/x86_64-linux-gnu/librt.a /usr/lib/x86_64-linux-gnu/libXss.so.1.0.0 /usr/lib/x86_64-linux-gnu/libasan.so.8 /usr/lib/x86_64-linux-gnu/libFLAC.so.12.0.0 /usr/lib/x86_64-linux-gnu/libasan.so.8.0.0 /usr/lib/x86_64-linux-gnu/libnpth.so.0 /usr/lib/x86_64-linux-gnu/libglapi.so.0 /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1.0.0 /usr/lib/x86_64-linux-gnu/libdebuginfod.so.1 /usr/lib/x86_64-linux-gnu/libc_malloc_debug.so /usr/lib/x86_64-linux-gnu/libcbor.so.0.8 /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.2600.3 /usr/lib/x86_64-linux-gnu/libmvec.so /usr/lib/x86_64-linux-gnu/libtiff.so.6.0.0 /usr/lib/x86_64-linux-gnu/libpciaccess.so.0.11.1 /usr/lib/x86_64-linux-gnu/libsource-highlight.so.4.0.1 /usr/lib/x86_64-linux-gnu/libGLX.so.0 /usr/lib/x86_64-linux-gnu/libmvec.a /usr/lib/x86_64-linux-gnu/libpulse.so.0 /usr/lib/x86_64-linux-gnu/libLLVM-15.so /usr/lib/x86_64-linux-gnu/libOpenGL.so.0.0.0 /usr/lib/x86_64-linux-gnu/libsensors.so.5 /usr/lib/x86_64-linux-gnu/libsndfile.so.1 /usr/lib/x86_64-linux-gnu/librhash.so.0 /usr/lib/x86_64-linux-gnu/libwebp.so.7.1.5 /usr/lib/x86_64-linux-gnu/libsensors.so.5.0.0 /usr/lib/x86_64-linux-gnu/libc.a /usr/lib/x86_64-linux-gnu/libXmuu.so.1.0.0 /usr/lib/x86_64-linux-gnu/libedit.so.2 /usr/lib/x86_64-linux-gnu/libm-2.37.a /usr/lib/x86_64-linux-gnu/libalut.so.0 /usr/lib/x86_64-linux-gnu/libsamplerate.so.0 /usr/lib/x86_64-linux-gnu/libasound.so.2 /usr/lib/x86_64-linux-gnu/libxcb-sync.so.1 /usr/lib/x86_64-linux-gnu/libbabeltrace-dummy.so.1 /usr/lib/x86_64-linux-gnu/pkgconfig/libtirpc.pc /usr/lib/x86_64-linux-gnu/pkgconfig/libcrypt.pc /usr/lib/x86_64-linux-gnu/pkgconfig/libxcrypt.pc /usr/lib/x86_64-linux-gnu/pkgconfig/libnsl.pc /usr/lib/x86_64-linux-gnu/libexpat.so /usr/lib/x86_64-linux-gnu/libogg.so.0.8.5 /usr/lib/x86_64-linux-gnu/systemd/libsystemd-shared-252.so /usr/lib/x86_64-linux-gnu/systemd/libsystemd-core-252.so /usr/lib/x86_64-linux-gnu/libXft.so.2 /usr/lib/x86_64-linux-gnu/libkrb5support.so.0 /usr/lib/x86_64-linux-gnu/libnpth.so.0.1.2 /usr/lib/x86_64-linux-gnu/libGL.so.1.7.0 /usr/lib/x86_64-linux-gnu/libpciaccess.so.0 /usr/lib/x86_64-linux-gnu/libbabeltrace-ctf.so.1 /usr/lib/x86_64-linux-gnu/libperl.so.5.36.0 /usr/lib/x86_64-linux-gnu/libsndio.so.7 /usr/lib/x86_64-linux-gnu/libopenal.so.1 /usr/lib/x86_64-linux-gnu/libnss_hesiod.so /usr/lib/x86_64-linux-gnu/libmcheck.a /usr/lib/x86_64-linux-gnu/libnghttp2.so.14 /usr/lib/x86_64-linux-gnu/libuv.so.1 /usr/lib/x86_64-linux-gnu/libc.so /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0 /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4.8.0 /usr/lib/x86_64-linux-gnu/libavahi-common.so.3 /usr/lib/x86_64-linux-gnu/cryptsetup/libcryptsetup-token-systemd-fido2.so /usr/lib/x86_64-linux-gnu/cryptsetup/libcryptsetup-token-systemd-tpm2.so /usr/lib/x86_64-linux-gnu/cryptsetup/libcryptsetup-token-systemd-pkcs11.so /usr/lib/x86_64-linux-gnu/libexpatw.so /usr/lib/x86_64-linux-gnu/libmp3lame.so.0 /usr/lib/x86_64-linux-gnu/libdrm_amdgpu.so.1.0.0 /usr/lib/x86_64-linux-gnu/libipt.so.2 /usr/lib/x86_64-linux-gnu/libX11-xcb.so.1.0.0 /usr/lib/x86_64-linux-gnu/ntp/libntpc.so.1.1.0 /usr/lib/x86_64-linux-gnu/ntp/libntpc.so.1 /usr/lib/x86_64-linux-gnu/ntp/libntpc.so /usr/lib/x86_64-linux-gnu/libbabeltrace-lttng-live.so.1.0.0 /usr/lib/x86_64-linux-gnu/libitm.so.1.0.0 /usr/lib/x86_64-linux-gnu/libthread_db.so /usr/lib/x86_64-linux-gnu/libGLEWmx.so.1.13 /usr/lib/x86_64-linux-gnu/libatomic.so.1 /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0 /usr/lib/x86_64-linux-gnu/libtiff.so.6 /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0 /usr/lib/x86_64-linux-gnu/libX11-xcb.so.1 /usr/lib/x86_64-linux-gnu/libedit.so.2.0.70 /usr/lib/x86_64-linux-gnu/libxcb-xfixes.so.0.0.0 /usr/lib/x86_64-linux-gnu/libcurl.so.4.8.0 /usr/lib/x86_64-linux-gnu/libtcl8.6.so.0 /usr/lib/x86_64-linux-gnu/libtsan.so.2.0.0 /usr/lib/x86_64-linux-gnu/libGLdispatch.so.0.0.0 /usr/lib/x86_64-linux-gnu/libbabeltrace.so.1.0.0 /usr/lib/x86_64-linux-gnu/libdl.a /usr/lib/x86_64-linux-gnu/libdrm_amdgpu.so.1 /usr/lib/x86_64-linux-gnu/libarchive.so.13.6.2 /usr/lib/x86_64-linux-gnu/libexpatw.a /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0 /usr/lib/x86_64-linux-gnu/libubsan.so.1 /usr/lib/x86_64-linux-gnu/libXmuu.so.1 /usr/lib/x86_64-linux-gnu/libwebp.so.7 /usr/lib/x86_64-linux-gnu/libk5crypto.so.3 /usr/lib/x86_64-linux-gnu/libelf.so.1 /usr/lib/x86_64-linux-gnu/krb5/plugins/libkrb5 /usr/lib/x86_64-linux-gnu/libk5crypto.so.3.1 /usr/lib/x86_64-linux-gnu/pulseaudio/libpulsecommon-16.1.so /usr/lib/x86_64-linux-gnu/libvorbis.so.0.4.9 /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so.4 /usr/lib/x86_64-linux-gnu/libvorbisenc.so.2.0.12 /usr/lib/x86_64-linux-gnu/libogg.so.0 /usr/lib/x86_64-linux-gnu/libsqlite3.so.0.8.6 /usr/lib/x86_64-linux-gnu/libtk8.6.so.0 /usr/lib/x86_64-linux-gnu/libwayland-server.so.0 /usr/lib/x86_64-linux-gnu/libreadline.so.8.2 /usr/lib/x86_64-linux-gnu/libmpg123.so.0.47.0 /usr/lib/x86_64-linux-gnu/libavahi-common.so.3.5.4 /usr/lib/x86_64-linux-gnu/libkrb5support.so.0.1 /usr/lib/x86_64-linux-gnu/libdrm.so.2 /usr/lib/x86_64-linux-gnu/libopus.so.0 /usr/lib/x86_64-linux-gnu/libxcb-randr.so.0.1.0 /usr/lib/x86_64-linux-gnu/libcc1.so.0.0.0 /usr/lib/x86_64-linux-gnu/libm.a /usr/lib/x86_64-linux-gnu/libGLU.so.1.3.1 /usr/lib/x86_64-linux-gnu/libip4tc.so.2 /usr/lib/x86_64-linux-gnu/libatk-1.0.so.0 /usr/lib/x86_64-linux-gnu/libldap.so.2.0.200 /usr/lib/x86_64-linux-gnu/libsecret-1.so.0 /usr/lib/x86_64-linux-gnu/libnsl.so /usr/lib/x86_64-linux-gnu/libcolord.so.2.0.5 /usr/lib/x86_64-linux-gnu/libgdk-3.so.0 /usr/lib/x86_64-linux-gnu/libpsl.so.5 /usr/lib/x86_64-linux-gnu/libepoxy.so.0.0.0 /usr/lib/x86_64-linux-gnu/libcolordprivate.so.2 /usr/lib/x86_64-linux-gnu/libpangoft2-1.0.so.0.5000.12 /usr/lib/x86_64-linux-gnu/libkmod.so.2.4.0 /usr/lib/x86_64-linux-gnu/libbrotlidec.so.1.0.9 /usr/lib/x86_64-linux-gnu/libpangoft2-1.0.so.0 /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0 /usr/lib/x86_64-linux-gnu/libicuuc.so.72 /usr/lib/x86_64-linux-gnu/libatspi.so.0 /usr/lib/x86_64-linux-gnu/libXfixes.so.3 /usr/lib/x86_64-linux-gnu/libbfd-2.40-system.so /usr/lib/x86_64-linux-gnu/libpng16.so.16 /usr/lib/x86_64-linux-gnu/libXau.so.6.0.0 /usr/lib/x86_64-linux-gnu/libXi.so.6 /usr/lib/x86_64-linux-gnu/libisl.so.23 /usr/lib/x86_64-linux-gnu/libatk-bridge-2.0.so.0 /usr/lib/x86_64-linux-gnu/libxcb.so.1 /usr/lib/x86_64-linux-gnu/libatspi.so.0.0.1 /usr/lib/x86_64-linux-gnu/libfreetype.so.6.18.3 /usr/lib/x86_64-linux-gnu/libctf.so.0 /usr/lib/x86_64-linux-gnu/libjson-c.so.5 /usr/lib/x86_64-linux-gnu/libicui18n.so.72 /usr/lib/x86_64-linux-gnu/libexpat.so.1.8.10 /usr/lib/x86_64-linux-gnu/libpng16.so.16.39.0 /usr/lib/x86_64-linux-gnu/libjansson.so.4 /usr/lib/x86_64-linux-gnu/libXau.so.6 /usr/lib/x86_64-linux-gnu/libtirpc.a /usr/lib/x86_64-linux-gnu/libXrender.so.1 /usr/lib/x86_64-linux-gnu/libicutest.so.72.1 /usr/lib/x86_64-linux-gnu/libgcr-ui-3.so.1 /usr/lib/x86_64-linux-gnu/libfontconfig.so.1.12.0 /usr/lib/x86_64-linux-gnu/libwayland-egl.so.1.21.0 /usr/lib/x86_64-linux-gnu/libnsl.so.2 /usr/lib/x86_64-linux-gnu/libcrypt.a /usr/lib/x86_64-linux-gnu/libicuuc.so.72.1 /usr/lib/x86_64-linux-gnu/libthai.so.0 /usr/lib/x86_64-linux-gnu/libxkbcommon.so.0 /usr/lib/x86_64-linux-gnu/libgraphite2.so.3.2.1 /usr/lib/x86_64-linux-gnu/libgmodule-2.0.so.0.7600.1 /usr/lib/x86_64-linux-gnu/libcairo-gobject.so.2.11600.0 /usr/lib/x86_64-linux-gnu/libXcursor.so.1.0.2 /usr/lib/x86_64-linux-gnu/libLerc.so.4 /usr/lib/x86_64-linux-gnu/libgcr-ui-3.so.1.0.0 /usr/lib/x86_64-linux-gnu/libgtk-3.so.0 /usr/lib/x86_64-linux-gnu/libgprofng.so.0 /usr/lib/x86_64-linux-gnu/libXrender.so.1.3.0 /usr/lib/x86_64-linux-gnu/libdbus-1.so.3.32.1 /usr/lib/x86_64-linux-gnu/libsasl2.so.2 /usr/lib/x86_64-linux-gnu/libbsd.so.0.11.7 /usr/lib/x86_64-linux-gnu/liblcms2.so.2.0.14 /usr/lib/x86_64-linux-gnu/libmpfr.so.6 /usr/lib/x86_64-linux-gnu/libkeyutils.so.1.10 /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7600.1 /usr/lib/x86_64-linux-gnu/libicudata.so.72 /usr/lib/x86_64-linux-gnu/libfribidi.so.0 /usr/lib/x86_64-linux-gnu/libfribidi.so.0.4.0 /usr/lib/x86_64-linux-gnu/libcairo-gobject.so.2 /usr/lib/x86_64-linux-gnu/libbsd.so.0 /usr/lib/x86_64-linux-gnu/libkmod.so.2 /usr/lib/x86_64-linux-gnu/gio/modules/libdconfsettings.so /usr/lib/x86_64-linux-gnu/libexpat.so.1 /usr/lib/x86_64-linux-gnu/libmpfr.so.6.2.0 /usr/lib/x86_64-linux-gnu/libgcr-base-3.so.1.0.0 /usr/lib/x86_64-linux-gnu/gprofng/libgp-collectorAPI.la /usr/lib/x86_64-linux-gnu/gprofng/libgp-collectorAPI.so /usr/lib/x86_64-linux-gnu/gprofng/libgp-sync.so /usr/lib/x86_64-linux-gnu/gprofng/libgp-iotrace.so /usr/lib/x86_64-linux-gnu/gprofng/libgp-collector.so /usr/lib/x86_64-linux-gnu/gprofng/libgp-heap.so /usr/lib/x86_64-linux-gnu/gprofng/libgp-collectorAPI.a /usr/lib/x86_64-linux-gnu/libjpeg.so.8.2.2 /usr/lib/x86_64-linux-gnu/libatk-bridge-2.0.so.0.0.0 /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-xbm.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-xpm.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-qtif.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-ani.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-pnm.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-tga.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-icns.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-bmp.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-ico.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-tiff.so /usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-gif.so /usr/lib/x86_64-linux-gnu/libXrandr.so.2.2.0 /usr/lib/x86_64-linux-gnu/libicudata.so.72.1 /usr/lib/x86_64-linux-gnu/libicutu.so.72 /usr/lib/x86_64-linux-gnu/libXcursor.so.1 /usr/lib/x86_64-linux-gnu/libldap.so.2 /usr/lib/x86_64-linux-gnu/libgck-1.so.0.0.0 /usr/lib/x86_64-linux-gnu/libxcb-render.so.0 /usr/lib/x86_64-linux-gnu/libicutu.so.72.1 /usr/lib/x86_64-linux-gnu/libgraphite2.so.3 /usr/lib/x86_64-linux-gnu/libdevmapper.so.1.02.1 /usr/lib/x86_64-linux-gnu/gtk-3.0/3.0.0/printbackends/libprintbackend-file.so /usr/lib/x86_64-linux-gnu/gtk-3.0/3.0.0/printbackends/libprintbackend-cups.so /usr/lib/x86_64-linux-gnu/libcrypt.so /usr/lib/x86_64-linux-gnu/libXinerama.so.1.0.0 /usr/lib/x86_64-linux-gnu/libgdbm.so.6 /usr/lib/x86_64-linux-gnu/libbrotlicommon.so.1.0.9 /usr/lib/x86_64-linux-gnu/libXrandr.so.2 /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0.7600.1 /usr/lib/x86_64-linux-gnu/librtmp.so.1 /usr/lib/x86_64-linux-gnu/libXext.so.6 /usr/lib/x86_64-linux-gnu/libsecret-1.so.0.0.0 /usr/lib/x86_64-linux-gnu/libgmodule-2.0.so.0 /usr/lib/x86_64-linux-gnu/libpangocairo-1.0.so.0 /usr/lib/x86_64-linux-gnu/libgdk_pixbuf-2.0.so.0.4200.10 /usr/lib/x86_64-linux-gnu/libxml2.so.2.9.14 /usr/lib/x86_64-linux-gnu/libctf-nobfd.so.0 /usr/lib/x86_64-linux-gnu/libexpatw.so.1.8.10 /usr/lib/x86_64-linux-gnu/libgprofng.so.0.0.0 /usr/lib/x86_64-linux-gnu/libargon2.so.1 /usr/lib/x86_64-linux-gnu/libthai.so.0.3.1 /usr/lib/x86_64-linux-gnu/libicutest.so.72 /usr/lib/x86_64-linux-gnu/libsframe.so.0 /usr/lib/x86_64-linux-gnu/libharfbuzz.so.0.60000.0 /usr/lib/x86_64-linux-gnu/libjpeg.so.8 /usr/lib/x86_64-linux-gnu/libip4tc.so.2.0.0 /usr/lib/x86_64-linux-gnu/libctf-nobfd.so.0.0.0 /usr/lib/x86_64-linux-gnu/libgck-1.so.0 /usr/lib/x86_64-linux-gnu/libgdbm.so.6.0.0 /usr/lib/x86_64-linux-gnu/sasl2/libsasldb.so /usr/lib/x86_64-linux-gnu/sasl2/libsasldb.so.2 /usr/lib/x86_64-linux-gnu/sasl2/libsasldb.so.2.0.25 /usr/lib/x86_64-linux-gnu/libharfbuzz.so.0 /usr/lib/x86_64-linux-gnu/libwayland-client.so.0 /usr/lib/x86_64-linux-gnu/libfdisk.so.1 /usr/lib/x86_64-linux-gnu/libassuan.so.0 /usr/lib/x86_64-linux-gnu/libsasl2.so.2.0.25 /usr/lib/x86_64-linux-gnu/libxml2.so.2 /usr/lib/x86_64-linux-gnu/libwayland-client.so.0.21.0 /usr/lib/x86_64-linux-gnu/libgio-2.0.so.0 /usr/lib/x86_64-linux-gnu/libgcr-base-3.so.1 /usr/lib/x86_64-linux-gnu/libmpc.so.3.3.1 /usr/lib/x86_64-linux-gnu/libopcodes-2.40-system.so /usr/lib/x86_64-linux-gnu/libXext.so.6.4.0 /usr/lib/x86_64-linux-gnu/liblcms2.so.2 /usr/lib/x86_64-linux-gnu/libgdbm_compat.so.4 /usr/lib/x86_64-linux-gnu/liblber.so.2 /usr/lib/x86_64-linux-gnu/libXinerama.so.1 /usr/lib/x86_64-linux-gnu/libsframe.so.0.0.0 /usr/lib/x86_64-linux-gnu/libdatrie.so.1.4.0 /usr/lib/x86_64-linux-gnu/libpangocairo-1.0.so.0.5000.12 /usr/lib/x86_64-linux-gnu/libcolordprivate.so.2.0.5 /usr/lib/x86_64-linux-gnu/libcryptsetup.so.12 /usr/lib/x86_64-linux-gnu/libtirpc.so /usr/lib/x86_64-linux-gnu/libdconf.so.1 /usr/lib/x86_64-linux-gnu/libicuio.so.72.1 /usr/lib/x86_64-linux-gnu/libpango-1.0.so.0.5000.12 /usr/lib/x86_64-linux-gnu/libXdamage.so.1.1.0 /usr/lib/x86_64-linux-gnu/bfd-plugins/libdep.so /usr/lib/x86_64-linux-gnu/libwayland-cursor.so.0 /usr/lib/x86_64-linux-gnu/libXcomposite.so.1.0.0 /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0 /usr/lib/x86_64-linux-gnu/libbrotlienc.so.1 /usr/lib/x86_64-linux-gnu/libctf.so.0.0.0 /usr/lib/x86_64-linux-gnu/libdbus-1.so.3 /usr/lib/x86_64-linux-gnu/libxcb-shm.so.0 /usr/lib/x86_64-linux-gnu/libatk-1.0.so.0.24809.1 /usr/lib/x86_64-linux-gnu/libssh.so.4.9.4 /usr/lib/x86_64-linux-gnu/libgtk-3-0 /usr/lib/x86_64-linux-gnu/libgtk-3.so.0.2405.32 /usr/lib/x86_64-linux-gnu/liblber.so.2.0.200 /usr/lib/x86_64-linux-gnu/libXdmcp.so.6.0.0 /usr/lib/x86_64-linux-gnu/libgio-2.0.so.0.7600.1 /usr/lib/x86_64-linux-gnu/libpango-1.0.so.0 /usr/lib/x86_64-linux-gnu/libassuan.so.0.8.5 /usr/lib/x86_64-linux-gnu/libpixman-1.so.0.42.2 /usr/lib/x86_64-linux-gnu/libxkbcommon.so.0.0.0 /usr/lib/x86_64-linux-gnu/libbrotlidec.so.1 /usr/lib/x86_64-linux-gnu/libmpc.so.3 /usr/lib/x86_64-linux-gnu/libpixman-1.so.0 /usr/lib/x86_64-linux-gnu/libgdk-3.so.0.2405.32 /usr/lib/x86_64-linux-gnu/libxcb-render.so.0.0.0 /usr/lib/x86_64-linux-gnu/libcairo.so.2.11600.0 /usr/lib/x86_64-linux-gnu/libxcb-shm.so.0.0.0 /usr/lib/x86_64-linux-gnu/libtirpc.so.3.0.0 /usr/lib/x86_64-linux-gnu/libexpatw.so.1 /usr/lib/x86_64-linux-gnu/libgthread-2.0.so.0.7600.1 /usr/lib/x86_64-linux-gnu/libXdmcp.so.6 /usr/lib/x86_64-linux-gnu/libnsl.so.2.0.1 /usr/lib/x86_64-linux-gnu/libgraphite2.so.2.0.0 /usr/lib/x86_64-linux-gnu/libjansson.so.4.14.0 /usr/lib/x86_64-linux-gnu/libicui18n.so.72.1 /usr/lib/x86_64-linux-gnu/libtirpc.so.3 /usr/lib/x86_64-linux-gnu/libisl.so.23.2.0 /usr/lib/x86_64-linux-gnu/libgdk_pixbuf-2.0.so.0 /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0 /usr/lib/x86_64-linux-gnu/libdatrie.so.1 /usr/lib/x86_64-linux-gnu/libkeyutils.so.1 /usr/lib/x86_64-linux-gnu/libicuio.so.72 /usr/lib/x86_64-linux-gnu/libjbig.so.0 /usr/lib/x86_64-linux-gnu/libbrotlienc.so.1.0.9 /usr/lib/x86_64-linux-gnu/libssh.so.4 /usr/lib/x86_64-linux-gnu/libcryptsetup.so.12.9.0 /usr/lib/x86_64-linux-gnu/libfdisk.so.1.1.0 /usr/lib/x86_64-linux-gnu/libbrotlicommon.so.1 /usr/lib/x86_64-linux-gnu/libgdbm_compat.so.4.0.0 /usr/lib/x86_64-linux-gnu/libjson-c.so.5.2.0 /usr/lib/x86_64-linux-gnu/libcolord.so.2 /usr/lib/x86_64-linux-gnu/libdconf.so.1.0.0 /usr/lib/x86_64-linux-gnu/libepoxy.so.0 /usr/lib/x86_64-linux-gnu/libXdamage.so.1 /usr/lib/x86_64-linux-gnu/libfontconfig.so.1 /usr/lib/x86_64-linux-gnu/libXcomposite.so.1 /usr/lib/x86_64-linux-gnu/libgthread-2.0.so.0 /usr/lib/x86_64-linux-gnu/libfreetype.so.6 /usr/lib/x86_64-linux-gnu/libwayland-cursor.so.0.21.0 /usr/lib/x86_64-linux-gnu/libXi.so.6.1.0 /usr/lib/x86_64-linux-gnu/libwayland-egl.so.1 /usr/lib/x86_64-linux-gnu/libcairo.so.2 /usr/lib/x86_64-linux-gnu/libdeflate.so.0 /usr/lib/x86_64-linux-gnu/libnsl.a /usr/lib/x86_64-linux-gnu/libXfixes.so.3.1.0 /usr/lib/x86_64-linux-gnu/libpsl.so.5.3.4 /usr/lib/libBLTlite.2.5.so.8.6 /usr/lib/python3.11/lib-dynload /usr/lib/python3.11/test/libregrtest /usr/lib/python3.11/config-3.11-x86_64-linux-gnu/libpython3.11.so /usr/lib/python3.11/config-3.11-x86_64-linux-gnu/libpython3.11.a /usr/lib/python3.11/config-3.11-x86_64-linux-gnu/libpython3.11-pic.a /usr/lib/python3.11/lib2to3 /usr/lib/libBLT.2.5.so.8.6 /usr/lib/gcc/x86_64-linux-gnu/12/libssp_nonshared.a /usr/lib/gcc/x86_64-linux-gnu/12/libgomp.so /usr/lib/gcc/x86_64-linux-gnu/12/libasan_preinit.o /usr/lib/gcc/x86_64-linux-gnu/12/libstdc++fs.a /usr/lib/gcc/x86_64-linux-gnu/12/libgomp.spec /usr/lib/gcc/x86_64-linux-gnu/12/libgcc_eh.a /usr/lib/gcc/x86_64-linux-gnu/12/libsanitizer.spec /usr/lib/gcc/x86_64-linux-gnu/12/libitm.a /usr/lib/gcc/x86_64-linux-gnu/12/libtsan.a /usr/lib/gcc/x86_64-linux-gnu/12/libbacktrace.a /usr/lib/gcc/x86_64-linux-gnu/12/libgomp.a /usr/lib/gcc/x86_64-linux-gnu/12/libstdc++.so /usr/lib/gcc/x86_64-linux-gnu/12/libgcov.a /usr/lib/gcc/x86_64-linux-gnu/12/libasan.so /usr/lib/gcc/x86_64-linux-gnu/12/libquadmath.so /usr/lib/gcc/x86_64-linux-gnu/12/libatomic.so /usr/lib/gcc/x86_64-linux-gnu/12/libtsan.so /usr/lib/gcc/x86_64-linux-gnu/12/libitm.so /usr/lib/gcc/x86_64-linux-gnu/12/libgcc.a /usr/lib/gcc/x86_64-linux-gnu/12/libgcc_s.so /usr/lib/gcc/x86_64-linux-gnu/12/liblto_plugin.so /usr/lib/gcc/x86_64-linux-gnu/12/libstdc++.a /usr/lib/gcc/x86_64-linux-gnu/12/libubsan.a /usr/lib/gcc/x86_64-linux-gnu/12/plugin/libcp1plugin.so.0 /usr/lib/gcc/x86_64-linux-gnu/12/plugin/libcp1plugin.so /usr/lib/gcc/x86_64-linux-gnu/12/plugin/libcc1plugin.so /usr/lib/gcc/x86_64-linux-gnu/12/plugin/libcc1plugin.so.0 /usr/lib/gcc/x86_64-linux-gnu/12/plugin/libcc1plugin.so.0.0.0 /usr/lib/gcc/x86_64-linux-gnu/12/plugin/libcp1plugin.so.0.0.0 /usr/lib/gcc/x86_64-linux-gnu/12/libitm.spec /usr/lib/gcc/x86_64-linux-gnu/12/libtsan_preinit.o /usr/lib/gcc/x86_64-linux-gnu/12/libcc1.so /usr/lib/gcc/x86_64-linux-gnu/12/libquadmath.a /usr/lib/gcc/x86_64-linux-gnu/12/liblsan.so /usr/lib/gcc/x86_64-linux-gnu/12/libsupc++.a /usr/lib/gcc/x86_64-linux-gnu/12/liblsan_preinit.o /usr/lib/gcc/x86_64-linux-gnu/12/libubsan.so /usr/lib/gcc/x86_64-linux-gnu/12/liblsan.a /usr/lib/gcc/x86_64-linux-gnu/12/libasan.a /usr/lib/gcc/x86_64-linux-gnu/12/libatomic.a /usr/lib/bfd-plugins/liblto_plugin.so
============= libs_notdir =============
lib lib libgcc_s.so.1 libe2p.so.2 libBrokenLocale.so.1 libcap-ng.so.0.0.0 libformw.so.6 libapt-private.so.0.0 libtasn1.so.6 libunistring.so.2 libcom_err.so.2.1 libpamc.so.0.82.1 libgnutls.so.30 libtinfo.so.6.4 libss.so.2.0 libxxhash.so.0.8.1 libmount.so.1 libunistring.so.2.2.0 libdrop_ambient.so.0.0.0 libffi.so.8.1.2 libncursesw.so.6.4 libtasn1.so.6.6.3 libpsx.so.2.66 libsystemd.so.0.35.0 libaudit.so.1 libpam_misc.so.0 libapt-private.so.0.0.0 libgcrypt.so.20 libp11-kit.so.0.3.0 libe2p.so.2.3 libext2fs.so.2.4 libformw.so.6.4 libsmartcols.so.1.1.0 libmd.so.0 librt.so.1 libsmartcols.so.1 libuuid.so.1 libpcre2-8.so.0 libdb-5.3.so libJIS.so libJISX0213.so libCNS.so libISOIR165.so libKSC.so libGB.so libattr.so.1 libmemusage.so libmenuw.so.6.4 libaudit.so.1.0.0 libgpg-error.so.0.33.1 libstdc++.so.6 libz.so.1 libpcprofile.so libseccomp.so.2 libidn2.so.0.3.8 libgcrypt.so.20.4.1 libz.so.1.2.13 libcap.so.2 libgnutls.so.30.34.2 libdebconfclient.so.0 libuuid.so.1.3.0 libmvec.so.1 libdrop_ambient.so.0 libthread_db.so.1 libffi.so.8 libudev.so.1.7.5 libsystemd.so.0 libpanelw.so.6.4 libnss_hesiod.so.2 libc_malloc_debug.so.0 libproc2.so.0 libnsl.so.1 liblzma.so.5.4.1 libhogweed.so.6.6 libtinfo.so.6 libutil.so.1 libcrypt.so.1.1.0 libsepol.so.2 libapt-pkg.so.6.0.0 libgmp.so.10.4.1 liblz4.so.1.9.4 libgmp.so.10 libproc2.so.0.0.1 libdebconfclient.so.0.0.0 libncursesw.so.6 libcap-ng.so.0 libpam.so.0 libm.so.6 libudev.so.1 libtic.so.6 libnss_files.so.2 libcrypt.so.1 libselinux.so.1 libnettle.so.8 libhogweed.so.6 libresolv.so.2 libbz2.so.1 libext2fs.so.2 libpam_misc.so.0.82.1 libacl.so.1.1.2301 libpsx.so.2 libtic.so.6.4 libxxhash.so.0 libsemanage.so.2 libmount.so.1.1.0 libblkid.so.1.1.0 libblkid.so.1 libss.so.2 libzstd.so.1 libpcre2-8.so.0.11.2 libnss_compat.so.2 libidn2.so.0 libmd.so.0.0.5 liblzma.so.5 libmenuw.so.6 libbz2.so.1.0 liblz4.so.1 libzstd.so.1.5.4 libp11-kit.so.0 libdl.so.2 libpamc.so.0 libc.so.6 libbz2.so.1.0.4 libpanelw.so.6 libgpg-error.so.0 libcap.so.2.66 libnettle.so.8.6 libnss_dns.so.2 lib lib.pm libapt-pkg.so.6.0 libacl.so.1 libpam.so.0.85.1 libattr.so.1.1.2501 libseccomp.so.2.5.4 libcom_err.so.2 libanl.so.1 libpthread.so.0 libxcb-sync.so.1.0.0 libsqlite3.so.0 libFLAC.so.12 libdecor-0.so.0.100.1 libipt.so.2.0.5 liblsan.so.0 libdecor libdecor-cairo.so libcups.so.2 libubsan.so.1.0.0 libxcb-glx.so.0 libvorbisenc.so.2 libresolv.a libbabeltrace-ctf-metadata.so.1.0.0 libcbor.so.0.8.0 libcrypto.so.3 libgbm.so.1 libuv.so.1.0.0 libGLU.so.1 libanl.so libavahi-client.so.3.2.9 libfido2.so.1.12.0 libcurl-gnutls.so.3 libdrm_intel.so.1.0.0 libmpg123.so.0 libcurl.so.4 libbabeltrace-ctf-text.so.1 libglapi.so.0.0.0 libjsoncpp.so.25 libm.so libpython3.11.so.1.0 libtcl8.6.so libapparmor.so.1 libxshmfence.so.1.0.0 libanl.a libstdc++.so.6.0.32 libboost_regex.so.1.74.0 libLLVM-15.so.1 libelf-0.188.so libsource-highlight.so.4 libbabeltrace-ctf-text.so.1.0.0 libhistory.so.8.2 libXss.so.1 libxcb-xfixes.so.0 libtsan.so.2 libasyncns.so.0 libksba.so.8 libdrm_nouveau.so.2 libvorbis.so.0 libbabeltrace-ctf.so.1.0.0 libasyncns.so.0.3.1 libGL.so.1 libbabeltrace-lttng-live.so.1 libhistory.so.8 libreadline.so.8 libjsoncpp.so.1.9.5 libz.a libcc1.so.0 libg.a libGLdispatch.so.0 libopus.so.0.8.0 libdw-0.188.so libgssapi_krb5.so.2 libXft.so.2.3.6 libdw.so.1 libSDL2_image-2.0.so.0.600.3 libdrm.so.2.4.0 libX11.so.6 libGLX_mesa.so.0.0.0 libfido2.so.1 libxcb-glx.so.0.0.0 libxshmfence.so.1 libxcb-dri2.so.0.0.0 libGLX.so.0.0.0 libgomp.so.1 libnss_compat.so libarchive.so.13 libz.so libavahi-client.so.3 libkrb5.so.3.3 libkrb5.so.3 libnghttp2.so.14.24.1 libGLX_mesa.so.0 libpython3.11.so libsamplerate.so.0.2.2 libxcb-dri3.so.0.1.0 libpython3.11.a libxcb-randr.so.0 libdrm_radeon.so.1.0.1 libGLC.so.0 libalut.so.0.1.0 libBrokenLocale.so lib.pm libbabeltrace.so.1 libbabeltrace-ctf-metadata.so.1 libresolv.so libopenal.so.1.19.1 libpulse.so.0.24.2 libsndio.so.7.2 libwayland-server.so.0.21.0 libitm.so.1 libbabeltrace-dummy.so.1.0.0 libxcb-dri3.so.0 libsndfile.so.1.0.35 libatomic.so.1.2.0 libGLX_indirect.so.0 libpulse-simple.so.0 libOpenGL.so.0 libxcb-present.so.0 libmp3lame.so.0.0.0 libssl.so.3 libapparmor.so.1.8.4 libtk8.6.so libquadmath.so.0.0.0 libGLEWmx.so.1.13.0 libutil.a libasound.so.2.0.0 libxcb-dri2.so.0 libgbm.so.1.0.0 libexpat.a libdecor-0.so.0 libdebuginfod-0.188.so libc_nonshared.a libXxf86vm.so.1 libpthread.a liblsan.so.0.0.0 libquadmath.so.0 libxcb-present.so.0.0.0 libperl.so.5.36 libgomp.so.1.0.0 libGLC.so.0.0.7 libpulse-simple.so.0.1.1 libdrm_radeon.so.1 libgssapi_krb5.so.2.2 libBrokenLocale.a libsndio.so.7.0 libdrm_intel.so.1 libpython3.11.so.1 libksba.so.8.14.3 librt.a libXss.so.1.0.0 libasan.so.8 libFLAC.so.12.0.0 libasan.so.8.0.0 libnpth.so.0 libglapi.so.0 libXxf86vm.so.1.0.0 libdebuginfod.so.1 libc_malloc_debug.so libcbor.so.0.8 libSDL2-2.0.so.0.2600.3 libmvec.so libtiff.so.6.0.0 libpciaccess.so.0.11.1 libsource-highlight.so.4.0.1 libGLX.so.0 libmvec.a libpulse.so.0 libLLVM-15.so libOpenGL.so.0.0.0 libsensors.so.5 libsndfile.so.1 librhash.so.0 libwebp.so.7.1.5 libsensors.so.5.0.0 libc.a libXmuu.so.1.0.0 libedit.so.2 libm-2.37.a libalut.so.0 libsamplerate.so.0 libasound.so.2 libxcb-sync.so.1 libbabeltrace-dummy.so.1 libtirpc.pc libcrypt.pc libxcrypt.pc libnsl.pc libexpat.so libogg.so.0.8.5 libsystemd-shared-252.so libsystemd-core-252.so libXft.so.2 libkrb5support.so.0 libnpth.so.0.1.2 libGL.so.1.7.0 libpciaccess.so.0 libbabeltrace-ctf.so.1 libperl.so.5.36.0 libsndio.so.7 libopenal.so.1 libnss_hesiod.so libmcheck.a libnghttp2.so.14 libuv.so.1 libc.so libdrm_nouveau.so.2.0.0 libcurl-gnutls.so.4.8.0 libavahi-common.so.3 libcryptsetup-token-systemd-fido2.so libcryptsetup-token-systemd-tpm2.so libcryptsetup-token-systemd-pkcs11.so libexpatw.so libmp3lame.so.0 libdrm_amdgpu.so.1.0.0 libipt.so.2 libX11-xcb.so.1.0.0 libntpc.so.1.1.0 libntpc.so.1 libntpc.so libbabeltrace-lttng-live.so.1.0.0 libitm.so.1.0.0 libthread_db.so libGLEWmx.so.1.13 libatomic.so.1 libX11.so.6.4.0 libtiff.so.6 libSDL2-2.0.so.0 libX11-xcb.so.1 libedit.so.2.0.70 libxcb-xfixes.so.0.0.0 libcurl.so.4.8.0 libtcl8.6.so.0 libtsan.so.2.0.0 libGLdispatch.so.0.0.0 libbabeltrace.so.1.0.0 libdl.a libdrm_amdgpu.so.1 libarchive.so.13.6.2 libexpatw.a libSDL2_image-2.0.so.0 libubsan.so.1 libXmuu.so.1 libwebp.so.7 libk5crypto.so.3 libelf.so.1 libkrb5 libk5crypto.so.3.1 libpulsecommon-16.1.so libvorbis.so.0.4.9 libcurl-gnutls.so.4 libvorbisenc.so.2.0.12 libogg.so.0 libsqlite3.so.0.8.6 libtk8.6.so.0 libwayland-server.so.0 libreadline.so.8.2 libmpg123.so.0.47.0 libavahi-common.so.3.5.4 libkrb5support.so.0.1 libdrm.so.2 libopus.so.0 libxcb-randr.so.0.1.0 libcc1.so.0.0.0 libm.a libGLU.so.1.3.1 libip4tc.so.2 libatk-1.0.so.0 libldap.so.2.0.200 libsecret-1.so.0 libnsl.so libcolord.so.2.0.5 libgdk-3.so.0 libpsl.so.5 libepoxy.so.0.0.0 libcolordprivate.so.2 libpangoft2-1.0.so.0.5000.12 libkmod.so.2.4.0 libbrotlidec.so.1.0.9 libpangoft2-1.0.so.0 libxcb.so.1.1.0 libicuuc.so.72 libatspi.so.0 libXfixes.so.3 libbfd-2.40-system.so libpng16.so.16 libXau.so.6.0.0 libXi.so.6 libisl.so.23 libatk-bridge-2.0.so.0 libxcb.so.1 libatspi.so.0.0.1 libfreetype.so.6.18.3 libctf.so.0 libjson-c.so.5 libicui18n.so.72 libexpat.so.1.8.10 libpng16.so.16.39.0 libjansson.so.4 libXau.so.6 libtirpc.a libXrender.so.1 libicutest.so.72.1 libgcr-ui-3.so.1 libfontconfig.so.1.12.0 libwayland-egl.so.1.21.0 libnsl.so.2 libcrypt.a libicuuc.so.72.1 libthai.so.0 libxkbcommon.so.0 libgraphite2.so.3.2.1 libgmodule-2.0.so.0.7600.1 libcairo-gobject.so.2.11600.0 libXcursor.so.1.0.2 libLerc.so.4 libgcr-ui-3.so.1.0.0 libgtk-3.so.0 libgprofng.so.0 libXrender.so.1.3.0 libdbus-1.so.3.32.1 libsasl2.so.2 libbsd.so.0.11.7 liblcms2.so.2.0.14 libmpfr.so.6 libkeyutils.so.1.10 libglib-2.0.so.0.7600.1 libicudata.so.72 libfribidi.so.0 libfribidi.so.0.4.0 libcairo-gobject.so.2 libbsd.so.0 libkmod.so.2 libdconfsettings.so libexpat.so.1 libmpfr.so.6.2.0 libgcr-base-3.so.1.0.0 libgp-collectorAPI.la libgp-collectorAPI.so libgp-sync.so libgp-iotrace.so libgp-collector.so libgp-heap.so libgp-collectorAPI.a libjpeg.so.8.2.2 libatk-bridge-2.0.so.0.0.0 libpixbufloader-xbm.so libpixbufloader-xpm.so libpixbufloader-qtif.so libpixbufloader-ani.so libpixbufloader-pnm.so libpixbufloader-tga.so libpixbufloader-icns.so libpixbufloader-bmp.so libpixbufloader-ico.so libpixbufloader-tiff.so libpixbufloader-gif.so libXrandr.so.2.2.0 libicudata.so.72.1 libicutu.so.72 libXcursor.so.1 libldap.so.2 libgck-1.so.0.0.0 libxcb-render.so.0 libicutu.so.72.1 libgraphite2.so.3 libdevmapper.so.1.02.1 libprintbackend-file.so libprintbackend-cups.so libcrypt.so libXinerama.so.1.0.0 libgdbm.so.6 libbrotlicommon.so.1.0.9 libXrandr.so.2 libgobject-2.0.so.0.7600.1 librtmp.so.1 libXext.so.6 libsecret-1.so.0.0.0 libgmodule-2.0.so.0 libpangocairo-1.0.so.0 libgdk_pixbuf-2.0.so.0.4200.10 libxml2.so.2.9.14 libctf-nobfd.so.0 libexpatw.so.1.8.10 libgprofng.so.0.0.0 libargon2.so.1 libthai.so.0.3.1 libicutest.so.72 libsframe.so.0 libharfbuzz.so.0.60000.0 libjpeg.so.8 libip4tc.so.2.0.0 libctf-nobfd.so.0.0.0 libgck-1.so.0 libgdbm.so.6.0.0 libsasldb.so libsasldb.so.2 libsasldb.so.2.0.25 libharfbuzz.so.0 libwayland-client.so.0 libfdisk.so.1 libassuan.so.0 libsasl2.so.2.0.25 libxml2.so.2 libwayland-client.so.0.21.0 libgio-2.0.so.0 libgcr-base-3.so.1 libmpc.so.3.3.1 libopcodes-2.40-system.so libXext.so.6.4.0 liblcms2.so.2 libgdbm_compat.so.4 liblber.so.2 libXinerama.so.1 libsframe.so.0.0.0 libdatrie.so.1.4.0 libpangocairo-1.0.so.0.5000.12 libcolordprivate.so.2.0.5 libcryptsetup.so.12 libtirpc.so libdconf.so.1 libicuio.so.72.1 libpango-1.0.so.0.5000.12 libXdamage.so.1.1.0 libdep.so libwayland-cursor.so.0 libXcomposite.so.1.0.0 libglib-2.0.so.0 libbrotlienc.so.1 libctf.so.0.0.0 libdbus-1.so.3 libxcb-shm.so.0 libatk-1.0.so.0.24809.1 libssh.so.4.9.4 libgtk-3-0 libgtk-3.so.0.2405.32 liblber.so.2.0.200 libXdmcp.so.6.0.0 libgio-2.0.so.0.7600.1 libpango-1.0.so.0 libassuan.so.0.8.5 libpixman-1.so.0.42.2 libxkbcommon.so.0.0.0 libbrotlidec.so.1 libmpc.so.3 libpixman-1.so.0 libgdk-3.so.0.2405.32 libxcb-render.so.0.0.0 libcairo.so.2.11600.0 libxcb-shm.so.0.0.0 libtirpc.so.3.0.0 libexpatw.so.1 libgthread-2.0.so.0.7600.1 libXdmcp.so.6 libnsl.so.2.0.1 libgraphite2.so.2.0.0 libjansson.so.4.14.0 libicui18n.so.72.1 libtirpc.so.3 libisl.so.23.2.0 libgdk_pixbuf-2.0.so.0 libgobject-2.0.so.0 libdatrie.so.1 libkeyutils.so.1 libicuio.so.72 libjbig.so.0 libbrotlienc.so.1.0.9 libssh.so.4 libcryptsetup.so.12.9.0 libfdisk.so.1.1.0 libbrotlicommon.so.1 libgdbm_compat.so.4.0.0 libjson-c.so.5.2.0 libcolord.so.2 libdconf.so.1.0.0 libepoxy.so.0 libXdamage.so.1 libfontconfig.so.1 libXcomposite.so.1 libgthread-2.0.so.0 libfreetype.so.6 libwayland-cursor.so.0.21.0 libXi.so.6.1.0 libwayland-egl.so.1 libcairo.so.2 libdeflate.so.0 libnsl.a libXfixes.so.3.1.0 libpsl.so.5.3.4 libBLTlite.2.5.so.8.6 lib-dynload libregrtest libpython3.11.so libpython3.11.a libpython3.11-pic.a lib2to3 libBLT.2.5.so.8.6 libssp_nonshared.a libgomp.so libasan_preinit.o libstdc++fs.a libgomp.spec libgcc_eh.a libsanitizer.spec libitm.a libtsan.a libbacktrace.a libgomp.a libstdc++.so libgcov.a libasan.so libquadmath.so libatomic.so libtsan.so libitm.so libgcc.a libgcc_s.so liblto_plugin.so libstdc++.a libubsan.a libcp1plugin.so.0 libcp1plugin.so libcc1plugin.so libcc1plugin.so.0 libcc1plugin.so.0.0.0 libcp1plugin.so.0.0.0 libitm.spec libtsan_preinit.o libcc1.so libquadmath.a liblsan.so libsupc++.a liblsan_preinit.o libubsan.so liblsan.a libasan.a libatomic.a liblto_plugin.so
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# 
```



## filter

```makefile
$(filter <names...>)
```

> 示例

```makefile
libs:= $(shell find /usr/lib -name lib*)
libs_notdir:= $(notdir $(shell find /usr/lib -name lib*))

libs_a:= $(filter %.a,$(libs_notdir))
libs_so:= $(filter %.so,$(libs_notdir))

out_filter:
	@echo ============= libs_a =============
	@echo $(libs_a) 
	@echo ============= libs_so =============
	@echo $(libs_so) 
```

```sh
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# make out_filter
============= libs_a =============
libresolv.a libanl.a libz.a libg.a libpython3.11.a libutil.a libexpat.a libc_nonshared.a libpthread.a libBrokenLocale.a librt.a libmvec.a libc.a libm-2.37.a libmcheck.a libdl.a libexpatw.a libm.a libtirpc.a libcrypt.a libgp-collectorAPI.a libnsl.a libpython3.11.a libpython3.11-pic.a libssp_nonshared.a libstdc++fs.a libgcc_eh.a libitm.a libtsan.a libbacktrace.a libgomp.a libgcov.a libgcc.a libstdc++.a libubsan.a libquadmath.a libsupc++.a liblsan.a libasan.a libatomic.a
============= libs_so =============
libdb-5.3.so libJIS.so libJISX0213.so libCNS.so libISOIR165.so libKSC.so libGB.so libmemusage.so libpcprofile.so libdecor-cairo.so libanl.so libm.so libtcl8.6.so libelf-0.188.so libdw-0.188.so libnss_compat.so libz.so libpython3.11.so libBrokenLocale.so libresolv.so libtk8.6.so libdebuginfod-0.188.so libc_malloc_debug.so libmvec.so libLLVM-15.so libexpat.so libsystemd-shared-252.so libsystemd-core-252.so libnss_hesiod.so libc.so libcryptsetup-token-systemd-fido2.so libcryptsetup-token-systemd-tpm2.so libcryptsetup-token-systemd-pkcs11.so libexpatw.so libntpc.so libthread_db.so libpulsecommon-16.1.so libnsl.so libbfd-2.40-system.so libdconfsettings.so libgp-collectorAPI.so libgp-sync.so libgp-iotrace.so libgp-collector.so libgp-heap.so libpixbufloader-xbm.so libpixbufloader-xpm.so libpixbufloader-qtif.so libpixbufloader-ani.so libpixbufloader-pnm.so libpixbufloader-tga.so libpixbufloader-icns.so libpixbufloader-bmp.so libpixbufloader-ico.so libpixbufloader-tiff.so libpixbufloader-gif.so libprintbackend-file.so libprintbackend-cups.so libcrypt.so libsasldb.so libopcodes-2.40-system.so libtirpc.so libdep.so libpython3.11.so libgomp.so libstdc++.so libasan.so libquadmath.so libatomic.so libtsan.so libitm.so libgcc_s.so liblto_plugin.so libcp1plugin.so libcc1plugin.so libcc1.so liblsan.so libubsan.so liblto_plugin.so
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# 
```



## basename

```makefile
$(basename <names...>)
```

> 示例1

```makefile

libs:= $(shell find /usr/lib -name lib*)
libs_notdir:= $(notdir $(shell find /usr/lib -name lib*))

libs_a:= $(filter %.a,$(libs_notdir))
libs_so:= $(filter %.so,$(libs_notdir))

libs_a_basename:= $(basename $(filter %.a,$(libs_notdir)))
libs_so_basename:= $(basename $(filter %.so,$(libs_notdir)))

out_basename:
	@echo ============= libs_a_basename =============
	@echo $(libs_a_basename) 
	@echo ============= libs_so_basename =============
	@echo $(libs_so_basename) 
```

```sh
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# make out_basename
============= libs_a_basename =============
libresolv libanl libz libg libpython3.11 libutil libexpat libc_nonshared libpthread libBrokenLocale librt libmvec libc libm-2.37 libmcheck libdl libexpatw libm libtirpc libcrypt libgp-collectorAPI libnsl libpython3.11 libpython3.11-pic libssp_nonshared libstdc++fs libgcc_eh libitm libtsan libbacktrace libgomp libgcov libgcc libstdc++ libubsan libquadmath libsupc++ liblsan libasan libatomic
============= libs_so_basename =============
libdb-5.3 libJIS libJISX0213 libCNS libISOIR165 libKSC libGB libmemusage libpcprofile libdecor-cairo libanl libm libtcl8.6 libelf-0.188 libdw-0.188 libnss_compat libz libpython3.11 libBrokenLocale libresolv libtk8.6 libdebuginfod-0.188 libc_malloc_debug libmvec libLLVM-15 libexpat libsystemd-shared-252 libsystemd-core-252 libnss_hesiod libc libcryptsetup-token-systemd-fido2 libcryptsetup-token-systemd-tpm2 libcryptsetup-token-systemd-pkcs11 libexpatw libntpc libthread_db libpulsecommon-16.1 libnsl libbfd-2.40-system libdconfsettings libgp-collectorAPI libgp-sync libgp-iotrace libgp-collector libgp-heap libpixbufloader-xbm libpixbufloader-xpm libpixbufloader-qtif libpixbufloader-ani libpixbufloader-pnm libpixbufloader-tga libpixbufloader-icns libpixbufloader-bmp libpixbufloader-ico libpixbufloader-tiff libpixbufloader-gif libprintbackend-file libprintbackend-cups libcrypt libsasldb libopcodes-2.40-system libtirpc libdep libpython3.11 libgomp libstdc++ libasan libquadmath libatomic libtsan libitm libgcc_s liblto_plugin libcp1plugin libcc1plugin libcc1 liblsan libubsan liblto_plugin
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# 
```

> 示例2

```makefile

libs:= $(shell find /usr/lib -name lib*)
libs_notdir:= $(notdir $(shell find /usr/lib -name lib*))

libs_a_basename_subst:= $(subst lib,,$(basename $(filter %.a,$(libs_notdir))))
libs_so_basename_subst:= $(subst lib,,$(basename $(filter %.so,$(libs_notdir))))

out_basename_subst:
	@echo ============= libs_a_basename_subst =============
	@echo $(libs_a_basename_subst) 
	@echo ============= libs_so_basename_subst =============
	@echo $(libs_so_basename_subst) 
```

```sh
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# make out_basename_subst
============= libs_a_basename_subst =============
resolv anl z g python3.11 util expat c_nonshared pthread BrokenLocale rt mvec c m-2.37 mcheck dl expatw m tirpc crypt gp-collectorAPI nsl python3.11 python3.11-pic ssp_nonshared stdc++fs gcc_eh itm tsan backtrace gomp gcov gcc stdc++ ubsan quadmath supc++ lsan asan atomic
============= libs_so_basename_subst =============
db-5.3 JIS JISX0213 CNS ISOIR165 KSC GB memusage pcprofile decor-cairo anl m tcl8.6 elf-0.188 dw-0.188 nss_compat z python3.11 BrokenLocale resolv tk8.6 debuginfod-0.188 c_malloc_debug mvec LLVM-15 expat systemd-shared-252 systemd-core-252 nss_hesiod c cryptsetup-token-systemd-fido2 cryptsetup-token-systemd-tpm2 cryptsetup-token-systemd-pkcs11 expatw ntpc thread_db pulsecommon-16.1 nsl bfd-2.40-system dconfsettings gp-collectorAPI gp-sync gp-iotrace gp-collector gp-heap pixbufloader-xbm pixbufloader-xpm pixbufloader-qtif pixbufloader-ani pixbufloader-pnm pixbufloader-tga pixbufloader-icns pixbufloader-bmp pixbufloader-ico pixbufloader-tiff pixbufloader-gif printbackend-file printbackend-cups crypt sasldb opcodes-2.40-system tirpc dep python3.11 gomp stdc++ asan quadmath atomic tsan itm gcc_s lto_plugin cp1plugin cc1plugin cc1 lsan ubsan lto_plugin
root@3570ce881c55:~/code/vscode-server/Projects/Make_CMake# 
```

