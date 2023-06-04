# PowerShell 常用命令

```bash
D:\Users\llddss\Desktop\tmp\test>help
有关某个命令的详细信息，请键入 HELP 命令名
ASSOC          显示或修改文件扩展名关联。
ATTRIB         显示或更改文件属性。
BREAK          设置或清除扩展式 CTRL+C 检查。
BCDEDIT        设置启动数据库中的属性以控制启动加载。
CACLS          显示或修改文件的访问控制列表(ACL)。
CALL           从另一个批处理程序调用这一个。
CD             显示当前目录的名称或将其更改。
CHCP           显示或设置活动代码页数。
CHDIR          显示当前目录的名称或将其更改。
CHKDSK         检查磁盘并显示状态报告。
CHKNTFS        显示或修改启动时间磁盘检查。
CLS            清除屏幕。
CMD            打开另一个 Windows 命令解释程序窗口。
COLOR          设置默认控制台前景和背景颜色。
COMP           比较两个或两套文件的内容。
COMPACT        显示或更改 NTFS 分区上文件的压缩。
CONVERT        将 FAT 卷转换成 NTFS。你不能转换
               当前驱动器。
COPY           将至少一个文件复制到另一个位置。
DATE           显示或设置日期。
DEL            删除至少一个文件。
DIR            显示一个目录中的文件和子目录。
DISKPART       显示或配置磁盘分区属性。
DOSKEY         编辑命令行、撤回 Windows 命令并
               创建宏。
DRIVERQUERY    显示当前设备驱动程序状态和属性。
ECHO           显示消息，或将命令回显打开或关闭。
ENDLOCAL       结束批文件中环境更改的本地化。
ERASE          删除一个或多个文件。
EXIT           退出 CMD.EXE 程序(命令解释程序)。
FC             比较两个文件或两个文件集并显示
               它们之间的不同。
FIND           在一个或多个文件中搜索一个文本字符串。
FINDSTR        在多个文件中搜索字符串。
FOR            为一组文件中的每个文件运行一个指定的命令。
FORMAT         格式化磁盘，以便用于 Windows。
FSUTIL         显示或配置文件系统属性。
FTYPE          显示或修改在文件扩展名关联中使用的文件
               类型。
GOTO           将 Windows 命令解释程序定向到批处理程序
               中某个带标签的行。
GPRESULT       显示计算机或用户的组策略信息。
GRAFTABL       使 Windows 在图形模式下显示扩展
               字符集。
HELP           提供 Windows 命令的帮助信息。
ICACLS         显示、修改、备份或还原文件和
               目录的 ACL。
IF             在批处理程序中执行有条件的处理操作。
LABEL          创建、更改或删除磁盘的卷标。
MD             创建一个目录。
MKDIR          创建一个目录。
MKLINK         创建符号链接和硬链接
MODE           配置系统设备。
MORE           逐屏显示输出。
MOVE           将一个或多个文件从一个目录移动到另一个
               目录。
OPENFILES      显示远程用户为了文件共享而打开的文件。
PATH           为可执行文件显示或设置搜索路径。
PAUSE          暂停批处理文件的处理并显示消息。
POPD           还原通过 PUSHD 保存的当前目录的上一个
               值。
PRINT          打印一个文本文件。
PROMPT         更改 Windows 命令提示。
PUSHD          保存当前目录，然后对其进行更改。
RD             删除目录。
RECOVER        从损坏的或有缺陷的磁盘中恢复可读信息。
REM            记录批处理文件或 CONFIG.SYS 中的注释(批注)。
REN            重命名文件。
RENAME         重命名文件。
REPLACE        替换文件。
RMDIR          删除目录。
ROBOCOPY       复制文件和目录树的高级实用工具
SET            显示、设置或删除 Windows 环境变量。
SETLOCAL       开始本地化批处理文件中的环境更改。
SC             显示或配置服务(后台进程)。
SCHTASKS       安排在一台计算机上运行命令和程序。
SHIFT          调整批处理文件中可替换参数的位置。
SHUTDOWN       允许通过本地或远程方式正确关闭计算机。
SORT           对输入排序。
START          启动单独的窗口以运行指定的程序或命令。
SUBST          将路径与驱动器号关联。
SYSTEMINFO     显示计算机的特定属性和配置。
TASKLIST       显示包括服务在内的所有当前运行的任务。
TASKKILL       中止或停止正在运行的进程或应用程序。
TIME           显示或设置系统时间。
TITLE          设置 CMD.EXE 会话的窗口标题。
TREE           以图形方式显示驱动程序或路径的目录
               结构。
TYPE           显示文本文件的内容。
VER            显示 Windows 的版本。
VERIFY         告诉 Windows 是否进行验证，以确保文件
               正确写入磁盘。
VOL            显示磁盘卷标和序列号。
XCOPY          复制文件和目录树。
WMIC           在交互式命令 shell 中显示 WMI 信息。

有关工具的详细信息，请参阅联机帮助中的命令行参考。

D:\Users\llddss\Desktop\tmp\test>
# 查询具体参数使用 命令 /?
D:\Users\llddss\Desktop\tmp\test>
D:\Users\llddss\Desktop\tmp\test>rd /?
删除一个目录。

RMDIR [/S] [/Q] [drive:]path
RD [/S] [/Q] [drive:]path

    /S      除目录本身外，还将删除指定目录下的所有子目录和
            文件。用于删除目录树。

    /Q      安静模式，带 /S 删除目录树时不要求确认

D:\Users\llddss\Desktop\tmp\test>
```

# PowerShell常见问题

## 创建文件

```bash
@echo off
for /l %%i in (1,1,10) do type nul > SSS_CCCC_GGGG_%%i.c
pause
```

## 批量导出文件名到指定文件

```bash
dir /b D:\test > D:\test\filelist.txt
```

## win10上如何使用cmd批量重命名文件

1. 如果文件所在目录为 D:\test，则输入以下命令：

```bash
cd D:\test
```

2. 使用“ren”命令来重命名文件。ren命令的语法如下：

```bash
ren <原文件名> <新文件名>
```

3. 如果要将所有以“.txt”结尾的文件名中的“old”替换为“new”，则输入以下命令：

```bash
@echo off
ren SSS_AAA_GGGG_*.c SSS_SSS_CCCC_GGGG_*.c
pause
```

上述命令将批量重命名所有以“.txt”结尾的文件名中的“old”为“new”。

按下“Enter”键执行命令，等待命令提示符窗口显示操作完成即可。

请注意，执行重命名操作时请谨慎，因为重命名后无法恢复文件名。

4. 当前文件夹中有多个子文件夹文件名为
   子文件夹1中的文件有
   SSS_CCCC_GGGG_5.txt
   SSS_CCCC_GGGG_6.txt
   SSS_CCCC_GGGG_7.txt
   SSS_CCCC_GGGG_8.txt
   SSS_CCCC_GGGG_9.txt
   子文件夹2中的文件有
   SSS_AAA_GGGG_1.txt
   SSS_AAA_GGGG_10.txt
   如何才能重命名为SSS_CCC_GGGG_*.txt的格式

 可以使用命令提示符 (cmd) 中的“for”命令和“ren”命令来批量重命名多个子文件夹中的文件。

假设当前文件夹下有两个子文件夹，分别为“子文件夹1”和“子文件夹2”，它们中间包含了多个文件名为“SSS_CCCC_GGGG_.txt”和“SSS_AAA_GGGG_.txt”的文件。现在需要将它们的文件名都重命名为“SSS_CCC_GGGG_*.txt”的格式。

以下是可以使用的命令：

```bash
for /r .\ %%a in (SSS_CCCC_GGGG_*.txt) do ren "%%a" "%%~na_tmp%%~xa"
for /r .\ %%a in (SSS_AAA_GGGG_*.txt) do ren "%%a" "%%~na_tmp%%~xa"
for /r .\ %%a in (*_tmp*.txt) do ren "%%a" "SSS_CCC_GGGG_%%~xa"
```

上述命令首先将所有符合“SSS_CCCC_GGGG_.txt”模式的文件名都重命名为“tmp.txt”的格式，然后将所有符合“SSS_AAA_GGGG.txt”模式的文件名都重命名为“_tmp.txt”的格式。最后，将所有包含“tmp”字符的文件名都重命名为“SSS_CCC_GGGG*.txt”的格式。

请注意，在命令中“for /r”语句中，“.\”表示当前目录，而“%%a”是循环变量，可以根据需要进行修改。另外，上述命令需要在当前文件夹下运行，如果需要在其他文件夹下运行，请将“.\”替换为对应的文件夹路径。

## 如何给多级文件夹内的文件重命名

1. 示例目录结构

```sh
├─a
│  ├─b
│  │  │  SSS_CCCC_AAAA_GGGG_1.c
│  │  │  SSS_CCCC_AAAA_GGGG_2.c
│  │  │  SSS_CCCC_AAAA_GGGG_3.c
│  │  │
│  │  └─b1
│  ├─c
│  │  │  SSS_CCCC_AAAA_GGGG_4.c
│  │  │  SSS_CCCC_AAAA_GGGG_5.c
│  │  │  SSS_CCCC_AAAA_GGGG_6.c
│  │  │
│  │  ├─c1
│  │  └─c1 - 副本
│  └─d
│      │  SSS_CCCC_AAAA_GGGG_10.c
│      │  SSS_CCCC_AAAA_GGGG_7.c
│      │  SSS_CCCC_AAAA_GGGG_8.c
│      │  SSS_CCCC_AAAA_GGGG_9.c
│      │
│      └─d1
│          │  SSS_CCCC_AAAA_GGGG_11.c
│          │  SSS_CCCC_AAAA_GGGG_12.c
│          │  SSS_CCCC_AAAA_GGGG_13.c
│          │
│          └─b1
└─help
```

2. V1 脚本

```sh
@echo off
setlocal enabledelayedexpansion

REM 设置要搜索的字符串
set "search=SSS_AAA_GGGG_"
REM 设置要替换的字符串
set "replace=SSS_CCCC_AAAA_GGGG_"

REM 设置目标文件夹的路径
set "targetFolder=D:\Users\llddss\Desktop\tmp\test"

REM 遍历目标文件夹及其子文件夹中的所有.c文件，并将每个文件的路径赋值给%%F变量
for /r "%targetFolder%" %%F in (*.c) do (
    REM 获取文件名（不包含扩展名）
    set "filename=%%~nF"
    REM 获取文件扩展名
    set "extension=%%~xF"
    REM 使用字符串替换操作将搜索字符串替换为替换字符串
    set "newfilename=!filename:%search%=%replace%!"
    REM 使用ren命令重命名文件
    ren "%%F" "!newfilename!!extension!"
)

REM 显示完成消息
echo Renaming complete.
pause
```

3. V2 脚本

```bash
@echo off
setlocal enabledelayedexpansion

REM 输入验证和错误处理
set "targetFolder=%~1"
if "%targetFolder%"=="" (
    set "targetFolder=D:\Users\llddss\Desktop\tmp\test"
)
if not exist "%targetFolder%" (
    echo Target folder does not exist.
    exit /b
)

REM 设置要搜索的字符串和替换的字符串
set "search=%~2"
if "%search%"=="" (
    set "search=SSS_AAA_GGGG_"
)

set "replace=%~3"
if "%replace%"=="" (
    set "replace=SSS_CCCC_AAAA_GGGG_"
)

REM 文件扩展名数组
set "extensions=.c"

REM 日志文件路径
set "logFile=renaming_log.txt"

REM 遍历目标文件夹及其子文件夹中的所有指定扩展名的文件，并将每个文件重命名
for /r "%targetFolder%" %%F in (*%extensions%) do (
    REM 获取文件名（不包含扩展名）
    set "filename=%%~nF"
    REM 获取文件扩展名
    set "extension=%%~xF"
    REM 使用字符串替换操作将搜索字符串替换为替换字符串
    set "newfilename=!filename:%search%=%replace%!"
    REM 使用ren命令重命名文件
    ren "%%F" "!newfilename!!extension!"

    REM 记录重命名操作到日志文件
    echo [!DATE! !TIME!] Renamed: %%F -> !newfilename!!extension! >> "%logFile%"
)

REM 显示完成消息
echo Renaming complete.

REM 帮助文档
echo.
echo Usage: script.bat [targetFolder] [search] [replace]
echo.
echo Parameters:
echo   targetFolder  : The target folder where files will be renamed.
echo                    Default: D:\tmp\test
echo   search        : The string to search for in file names.
echo                    Default: QQQ_AAA_BBB_CCC_
echo   replace       : The string to replace the search string with in file names.
echo                    Default: QQQ_DDD_CCC_
echo.
echo Example: script.bat "D:\Path\To\Folder" "searchString" "replaceString"

pause

```

## 如何给多级文件夹重命名

```sh
@echo off
setlocal enabledelayedexpansion

REM 获取命令行参数或设置默认值
set "targetFolder=%~1"
if "%targetFolder%"=="" set "targetFolder=D:\Users\llddss\Desktop\tmp\test"
set "search=%~2"
if "%search%"=="" set "search=SSS_CCCC_AAAA_GGGG"
set "replace=%~3"
if "%replace%"=="" set "replace=SSS_AAA_GGGG_"

REM 输入验证和错误处理
if not exist "%targetFolder%" (
    echo Target folder does not exist.
    exit /b
)

REM 文件夹重命名
for /d /r "%targetFolder%" %%F in (*%search%*) do (
    set "folder=%%~nxF"
    set "newfolder=!folder:%search%=%replace%!"
    ren "%%F" "!newfolder!"
)

echo Renaming complete.
pause
```

## 如何将指定文件夹下的指定后缀名的文件名保存到指定文件中

```
for /r "文件夹路径" %i in (*.后缀名) do @echo %~nxi >> 输出文件路径\输出文件名.txt
```

# 参考链接

> https://learn.microsoft.com/zh-cn/windows-server/administration/windows-commands/windows-commands
>
