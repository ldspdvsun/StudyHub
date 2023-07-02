# Pytest_L1
## Pytest 安装

```sh
pip install pytest
```

## Pytest 命名规则

|类型|规则|
|-|-|
|文件|test_开头或者_test结尾|
|类|Test开头|
|方法/函数|test_开头|

+ 注意：测试类中不可以添加 __init__ 构造函数，添加之后，无法识别相关测试用例

## PyTest 测试用例结构

1. 用例名称
2. 用力步骤
3. 用例断言

+ 测试用例示例

```py
def test_XXX(self):
    # 测试步骤1
    # 测试步骤2
    # 断言 实际结果 对比 预期结果
    assert ActualResult == ExceptedResult
```

+ 类级别的测试用例

```py
class TestXXX:
    def setup(self):
        # 资源准备
        pass

    def teardown(self):
        # 资源销毁
        pass

    def test_XXX(self):
        # 测试步骤1
        # 测试步骤2
        # 断言 实际结果 对比 预期结果
        assert ActualResult == ExceptedResult
```

## PyTest测试用例断言

+ 什么是断言

断言(assert)是一种在程序中的一阶逻辑，目的为了表示与验证软件开发者预期的结果。当程序运行到断言的位置时，对应的断言应该为真。若断言不为真，程序会终止执行，并给出错误信息

+ 断言写法

    + assert <表达式>
        + assert True
        + assert False
    + assert <表达式>,<描述>
        + assert False,'Test false'

```py
import sys
def test_plat():
    assert ('linux' in sys.platform),'改代码只能在linux系统运行'
```

## Pytest 测试框架结构

|类型|规则|
|-|-|
|setup_moudle/teardown_module|全局模块级（.py文件）|
|setup_class/teardown_class|类级（class），只在类中前后运行一次|
|setup_function/teardown_function|函数级，在类外|
|setup_method/teardown_method|方法级，类中每个方法执行前后|
|setup/teardown|在类中，运行在调用方法的前后（重点，相当于setup_method/teardown_method缩写）|

```py
# coding=utf-8
"""
@File    : test_setup_teardown.py
@Time    : 2023/2/20 21:34
@Author  : Sun
@Description : 
"""


# 模块级别，整个py文件只调一次
def setup_module():
    print('资源准备：setup_module')


def teardown_module():
    print('资源销毁：teardown_module')


# 函数级、在类外
def setup_function():
    print('资源准备：setup_function')


def teardown_function():
    print('资源销毁：teardown_function')


def test_case1():
    print('test_case1')


def test_case2():
    print('test_case2')


class TestDemo:
    # 执行类级别，在类执行的前后分别执行setup_class teardown_class
    def setup_class(self):
        print('资源准备：setup_class')

    def teardown_class(self):
        print('资源销毁：teardown_class')

    # 在类的每个方法前后执行
    def setup(self):
        print('资源准备：setup')

    def teardown_method(self):
        print('资源销毁：teardown_method')
        print()

    def test_demo1(self):
        print('test_demo1')

    def test_demo2(self):
        print('test_demo2')
```

```py
# result
D:\Programs\anaconda3\envs\PyTest\python.exe "D:/Program Files/JetBrains/PyCharm 2022.2.3/plugins/python/helpers/pycharm/_jb_pytest_runner.py" --path E:\PycharmProjects\PyTest\test_setup_teardown.py 
Testing started at 21:50 ...
Launching pytest with arguments E:\PycharmProjects\PyTest\test_setup_teardown.py --no-header --no-summary -q in E:\PycharmProjects\PyTest

============================= test session starts =============================
collecting ... collected 4 items

test_setup_teardown.py::test_case1 资源准备：setup_module
资源准备：setup_function
PASSED                                [ 25%]test_case1
资源销毁：teardown_function

test_setup_teardown.py::test_case2 资源准备：setup_function
PASSED                                [ 50%]test_case2
资源销毁：teardown_function

test_setup_teardown.py::TestDemo::test_demo1 
test_setup_teardown.py::TestDemo::test_demo2 

============================== 4 passed in 0.02s ==============================

Process finished with exit code 0
资源准备：setup_class
资源准备：setup
PASSED                      [ 75%]test_demo1
资源销毁：teardown_method

资源准备：setup
PASSED                      [100%]test_demo2
资源销毁：teardown_method

资源销毁：teardown_class
资源销毁：teardown_module

```

## 计算器实战

计算器通过加法、减法、乘法、除法等功能的运算

# Pytest_L2
## Pytest参数化用例

### 参数化应用场景

+ 测试登录场景
    + 登录成功
    + 登录数百

+ 普通测试用例方法
    + copy多份代码 or 输入多个参数

### Pytest参数化实现方法

+ 装饰器：

**@pytest.mark.parametrize("参数名(与测试用例中需要替换的参数一致)",[参数值1,参数值2])**

```py
@pytest.mark.parametrize("useranme,password",[["right","right"],["wrong","wrong"]])
def test_param(useranme,password):
    login(useranme,password)
```

### Mark:参数化测试函数使用

#### 单参数，可以将数据放在列表中

```py
import pytest

seach_list = ['appium','sellent','pytest']
# 参数化实现测试用例的动态形成
@pytest.mark.parametrize("search_key",['appium','sellent','pytest','aba',''])
def test_search_param(search_key):
    # 1. 定义搜索词
    # search_key = "appium"
    # 2. 完成断言
    assert search_key in seach_list

# RESULT
test_param.py::test_search_param[sellent] 
test_param.py::test_search_param[pytest] 
test_param.py::test_search_param[aba] PASSED                          [ 20%]PASSED                         [ 40%]PASSED                          [ 60%]FAILED                             [ 80%]
test_param.py:14 (test_search_param[aba])
'aba' != ['appium', 'sellent', 'pytest']

Expected :['appium', 'sellent', 'pytest']
Actual   :'aba'
<Click to see difference>

search_key = 'aba'

    @pytest.mark.parametrize("search_key", ['appium', 'sellent', 'pytest', 'aba', ''])
    def test_search_param(search_key):
        # 1. 定义搜索词
        # search_key = "appium"
        # 2. 完成断言
>       assert search_key in seach_list
E       AssertionError: assert 'aba' in ['appium', 'sellent', 'pytest']

test_param.py:20: AssertionError



test_param.py::test_search_param[] FAILED                                [100%]
test_param.py:14 (test_search_param[])
'' != ['appium', 'sellent', 'pytest']

Expected :['appium', 'sellent', 'pytest']
Actual   :''
<Click to see difference>

search_key = ''

    @pytest.mark.parametrize("search_key", ['appium', 'sellent', 'pytest', 'aba', ''])
    def test_search_param(search_key):
        # 1. 定义搜索词
        # search_key = "appium"
        # 2. 完成断言
>       assert search_key in seach_list
E       AssertionError: assert '' in ['appium', 'sellent', 'pytest']

test_param.py:20: AssertionError


========================= 2 failed, 3 passed in 0.14s =========================

Process finished with exit code 1
```

#### 多参数，将数据放在列表嵌套元组中或列表嵌套列表中

```py
@pytest.mark.parametrize("username,password",
                         [('right_usename', 'right_password'), ('wrong_username', 'wrong_password'), (" ", 'password'),
                          ("username", ' ')])
def test_login1(username, password):
    print(f'登录的用户名:{username}, 密码:{password}')

# RESULT
PASSED          [ 25%]登录的用户名:right_usename, 密码:right_password
PASSED         [ 50%]登录的用户名:wrong_username, 密码:wrong_password
PASSED                            [ 75%]登录的用户名: , 密码:password
PASSED                            [100%]登录的用户名:username, 密码: 
```

#### 用例重命名

##### 用例重命名-添加ids参数

+ 通过ids参数，将别名放在列表中，ids列表中参数的数量要与第二项参数值的个数一致

```py
@pytest.mark.parametrize("username,password",[['right_usename','right_password'],['wrong_username','wrong_password'],[" ",'password']],
                         ids=['RIGHT username and password','WRONG username and password','WRONG username and RIGHT password'])
def test_login(username,password):
    print(f'登录的用户名:{username}, 密码:{password}')

# RESULT
PASSED            [ 33%]登录的用户名:right_usename, 密码:right_password
PASSED            [ 66%]登录的用户名:wrong_username, 密码:wrong_password
PASSED      [100%]登录的用户名: , 密码:password
```

##### 用例重命名-添加ids参数（中文情况）

1. 在项目下新建conftest.py文件，添加以下内容

```py
def pytest_collection_modifyitems(items):
    # 测试用里收集完成是，将收集到的用例名name和用例表示nodeid的中文信息显示在控制台上
    for i in items:
        i.name = i.name.encode('utf-8').decode('unicode_escape')
        i._nodeid = i.nodeid.encode('utf-8').decode('unicode_escape')
```

2. 通过ids参数，将别名放在列表中，ids列表中参数的数量要与第二项参数值的个数一致

```py
# ids设置中文的情况
@pytest.mark.parametrize("username,password",[['right_usename','right_password'],['wrong_username','wrong_password'],[" ",'password']],
                         ids=['正确','错误','正确用户名，错误密码'])
def test_login2(username,password):
    print(f'登录的用户名:{username}, 密码:{password}')

# RESULT
PASSED                                  [ 33%]登录的用户名:right_usename, 密码:right_password
PASSED                                  [ 66%]登录的用户名:wrong_username, 密码:wrong_password
PASSED                  [100%]登录的用户名: , 密码:password
```

#### 笛卡儿积

+ 两组数据
    + a=[1,2,3]
    + b=[a,b,c]

+ 对应有几种形式
    + (1,a)(1,b)(1,c)
    + (2,a)(2,b)(2,c)
    + (3,a)(3,b)(3,c)

+ 装饰器其实就是一个方法，先执行离测试用例最近的装饰器，在执行远的，由近及远，所以测试结果是1-a,1-b,1-c,2-a,2-b,,,
```py
# 笛卡儿积
@pytest.mark.parametrize('b', ['a', 'b', 'c'])
@pytest.mark.parametrize('a', [1, 2, 3])
def test_dk(a, b):
    print(f'笛卡儿积形式的参数：a={a},b={b}')

# RESULT
PASSED                                       [ 11%]笛卡儿积形式的参数：a=1,b=a
PASSED                                       [ 22%]笛卡儿积形式的参数：a=1,b=b
PASSED                                       [ 33%]笛卡儿积形式的参数：a=1,b=c
PASSED                                       [ 44%]笛卡儿积形式的参数：a=2,b=a
PASSED                                       [ 55%]笛卡儿积形式的参数：a=2,b=b
PASSED                                       [ 66%]笛卡儿积形式的参数：a=2,b=c
PASSED                                       [ 77%]笛卡儿积形式的参数：a=3,b=a
PASSED                                       [ 88%]笛卡儿积形式的参数：a=3,b=b
PASSED                                       [100%]笛卡儿积形式的参数：a=3,b=c

```

## 标记测试用例

+ 场景：只执行符合要求的某一部分用例，可以把一个web项目划分多个模块，然后指定模块名称运行
+ 解决：在测试用例方法上加 **@pytest.mark.标签名**
+ 执行：-m执行自定义标记的相关用例
    + pytest -s test_mark_zi_09.py -m=webtest
    + pytest -s test_mark_zi_09.py -m "apptest"
    + pytest -s test_mark_zi_09.py -m "not ios"

1. 在文件夹下新建pytest.ini文件，注册标签，避免执行pytest -m 命令时出现warinning

```py
[pytest]
markers = str
    bignum
    int
    float
    zero
    minus
```

2. 新建测试用例

```py
import pytest


def double(a):
    return a * 2


# 测试数据：整形
@pytest.mark.int
def test_double_int():
    print('test double int')
    assert 1 == double(1)


# 测试数据：负数
@pytest.mark.minus
def test_double_minus():
    print('test double minus')
    assert -2 == double(-1)


# 测试数据：浮点数
@pytest.mark.float
def test_double_float():
    print('test double float')
    assert 0.2 == double(0.1)


@pytest.mark.float
def test_double_float2():
    print('test double float')
    assert -10.2 == double(-0.1)


@pytest.mark.zero
def test_double_zero():
    print('test double zero')
    assert 10 == double(0)


@pytest.mark.bignum
def test_double_bignum():
    print('test double bignum')
    assert 200 == double(100)


@pytest.mark.str
def test_double_str():
    print('test double str')
    assert 'aa' == double('a')


@pytest.mark.str
def test_double_str1():
    print('test double str')
    assert 'a$a$' == double('a$')


# RESULT
PS E:\PycharmProjects\PyTest\L2> pytest .\test_command_param.py -vs -m "str"
================================================================================= test session starts =================================================================================
platform win32 -- Python 3.9.12, pytest-7.1.2, pluggy-1.0.0 -- D:\Program Files\Python39\python.exe
cachedir: .pytest_cache
rootdir: E:\PycharmProjects\PyTest\L2, configfile: pytest.ini
collected 8 items / 6 deselected / 2 selected                                                                                                                                           

test_command_param.py::test_double_str test double str
PASSED
test_command_param.py::test_double_str1 test double str
PASSED

=========================================================================== 2 passed, 6 deselected in 0.01s =========================================================================== 
PS E:\PycharmProjects\PyTest\L2> 

```

## 设置跳过、预期失败用例

+ 调试时不像运行这个用例
+ 标记无法在某些平台上运行的测试功能

### 设置跳过

1. 添加装饰器

    + @pytest.mark.skip

    ```py
    @pytest.mark.skip(reason='未开发完成')
    def test_true():
        print('true')
        assert True

    # RESULT
    SKIPPED (未开发完成)                             [ 50%]
    Skipped: 未开发完成

    ```

    + @pytest.mark.skipif

    ```py
    @pytest.mark.skipif(sys.platform == 'win', reason='跳过此项测试的条件为，如果是win平台则跳过此项测试')
    def test_true1():
        print('Platform:{}'.format(sys.platform))
        assert True

    # RESULT
    PASSED                                          [ 66%]Platform:win32
    ```

2. 代码中添加跳过代码

    ```py
    pytest.skip(reason)

    def check_login():
        return True

    def test_login():
        print('start')
        if not check_login():
            pytest.skip('unsupported configuration')
        print('end')

    # RESULT
    PASSED                                          [100%]start
    end
    ```

### 预期失败用例

   + xfail使用场景
    
   + 与skip类似，预期结果为fail，标记用例为fail
   + 用法：添加装饰器@pytest.mark.xfail
   
   1. 
```py
@pytest.mark.xfail
def test_result():
    print('test_xfaile 方法执行')
    assert 2 == 2

# RESULT
XPASS                                          [100%]test_xfaile 方法执行
```

   2. 
```py
@xfail(reason='bug 110')
def test_result1():
    print('test_xfaile 方法执行')
    assert 1 == 2

# RESULT
XFAIL (bug 110)                               [100%]test_xfaile 方法执行

@xfail(reason='bug 110')
    def test_result1():
        print('test_xfaile 方法执行')
>       assert 1 == 2
E       assert 1 == 2
```

   3. 
```py
def test_result2():
    print('test_xfaile 方法执行')
    pytest.xfail(reason='该功能尚未完成')
    assert 1 == 2

# RESULT
XFAIL (该功能尚未完成)                        [100%]test_xfaile 方法执行

def test_result2():
        print('test_xfaile 方法执行')
>       pytest.xfail(reason='该功能尚未完成')
E       _pytest.outcomes.XFailed: 该功能尚未完成
```

## 运行用例

1. 运行 某个/多个 用例包（文件夹）

    在某个文件夹下直接运行pytest，将会测试所有符合 test_xxx或 xxx_test 命名的用例
```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest
```

2. 运行 某个/多个 用力模块

    pytest 文件名.py

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest test_param.py -v
```

3. 运行 某个/多个 用例类

    pytest 文件名.py::测试类名
```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L1# pytest test_setup_teardown.py::TestDemo -v

```
4. 运行 某个/多个 用例方法

    pytest 文件名.py::测试类名::测试用例名
```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L1# pytest test_setup_teardown.py::TestDemo::test_demo1 -v
```

## 测试用例调度与执行

+ 命令行参数-使用缓存状态

    + --lf(--last-failed)只重新运行故障
    + --ff(--failed-first)先运行故障然后再运行其余的测试

```py
# 正常测试
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest -v
============================================================== test session starts ===============================================================
platform linux -- Python 3.10.6, pytest-7.2.1, pluggy-1.0.0 -- /usr/bin/python3
cachedir: .pytest_cache
rootdir: /root/code/vscode-server/PyTest/L2, configfile: pytest.ini
collected 56 items                                                                                                                               

test_command_param.py::test_double_int FAILED                                                                                              [  1%]
test_command_param.py::test_double_minus PASSED                                                                                            [  3%]
test_command_param.py::test_double_float PASSED                                                                                            [  5%]
test_command_param.py::test_double_float2 FAILED                                                                                           [  7%]
test_command_param.py::test_double_zero FAILED                                                                                             [  8%]
.....
test_skip.py::test_login PASSED                                                                                                            [ 94%]
test_skip.py::test_result XPASS                                                                                                            [ 96%]
test_skip.py::test_result1 XFAIL (该功能尚未完成)                                                                                          [ 98%]
test_skip.py::test_result2 XFAIL (该功能尚未完成)                                                                                          [100%]


# --lf
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest --lf -v
============================================================== test session starts ===============================================================
platform linux -- Python 3.10.6, pytest-7.2.1, pluggy-1.0.0 -- /usr/bin/python3
cachedir: .pytest_cache
rootdir: /root/code/vscode-server/PyTest/L2, configfile: pytest.ini
collected 5 items                                                                                                                                
run-last-failure: rerun previous 5 failures (skipped 1 file)

test_command_param.py::test_double_int FAILED                                                                                              [ 20%]
test_command_param.py::test_double_float2 FAILED                                                                                           [ 40%]
test_command_param.py::test_double_zero FAILED                                                                                             [ 60%]
test_param.py::test_search_param[aba] FAILED                                                                                               [ 80%]
test_param.py::test_search_param[] FAILED                                                                                                  [100%]


# --ff
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest --ff -v
============================================================== test session starts ===============================================================
platform linux -- Python 3.10.6, pytest-7.2.1, pluggy-1.0.0 -- /usr/bin/python3
cachedir: .pytest_cache
rootdir: /root/code/vscode-server/PyTest/L2, configfile: pytest.ini
collected 56 items                                                                                                                               
run-last-failure: rerun previous 5 failures first

test_command_param.py::test_double_int FAILED                                                                                              [  1%]
test_command_param.py::test_double_float2 FAILED                                                                                           [  3%]
test_command_param.py::test_double_zero FAILED                                                                                             [  5%]
test_param.py::test_search_param[aba] FAILED                                                                                               [  7%]
test_param.py::test_search_param[] FAILED                                                                                                  [  8%]
test_command_param.py::test_double_minus PASSED                                                                                            [ 10%]
test_command_param.py::test_double_float PASSED                                                                                            [ 12%]
test_command_param.py::test_double_bignum PASSED                                                                                           [ 14%]
.....
test_skip.py::test_login PASSED                                                                                                            [ 94%]
test_skip.py::test_result XPASS                                                                                                            [ 96%]
test_skip.py::test_result1 XFAIL (该功能尚未完成)                                                                                          [ 98%]
test_skip.py::test_result2 XFAIL (该功能尚未完成)                                                                                          [100%]
```

## pytest 命令行常用参数

+ --help 获取参数列表

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest --help
usage: pytest [options] [file_or_dir] [file_or_dir] [...]

positional arguments:
  file_or_dir

general:
  -k EXPRESSION         Only run tests which match the given substring expression. An expression is a Python evaluatable expression where all
                        names are substring-matched against test names and their parent classes. Example: -k 'test_method or test_other' matches
                        all test functions and classes whose name contains 'test_method' or 'test_other', while -k 'not test_method' matches those
                        that don't contain 'test_method' in their names. -k 'not test_method and not test_other' will eliminate the matches.
                        Additionally keywords are matched to classes and functions containing extra names in their 'extra_keyword_matches' set, as
                        well as functions which have names assigned directly to them. The matching is case-insensitive.
  -m MARKEXPR           Only run tests matching given mark expression. For example: -m 'mark1 and not mark2'.
  --markers             show markers (builtin, plugin and per-project ones).
  -x, --exitfirst       Exit instantly on first error or failed test
  --fixtures, --funcargs
...
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# 
```

+ -x 用例一旦失败（fail/error)立刻停止执行

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest -x
```

+ --maxfail=num 用例达到

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest --maxfail=3
```

+ -m 标记用例，执行@pytest.mark.xx 标记为xx的用例

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest -m 'bignum' -vs
============================================================== test session starts ===============================================================
platform linux -- Python 3.10.6, pytest-7.2.1, pluggy-1.0.0 -- /usr/bin/python3
cachedir: .pytest_cache
rootdir: /root/code/vscode-server/PyTest/L2, configfile: pytest.ini
collected 56 items / 55 deselected / 1 selected                                                                                                  

test_command_param.py::test_double_bignum test double bignum
PASSED

======================================================== 1 passed, 55 deselected in 0.01s ========================================================
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# 
```

+ -k 执行包含某个关键字的测试用例(针对测试用例名称)

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest -vs -k 'login1'
============================================================== test session starts ===============================================================
platform linux -- Python 3.10.6, pytest-7.2.1, pluggy-1.0.0 -- /usr/bin/python3
cachedir: .pytest_cache
rootdir: /root/code/vscode-server/PyTest/L2, configfile: pytest.ini
collected 56 items / 52 deselected / 4 selected                                                                                                  

test_param.py::test_login1[right_usename-right_password] 登录的用户名:right_usename, 密码:right_password
PASSED
test_param.py::test_login1[wrong_username-wrong_password] 登录的用户名:wrong_username, 密码:wrong_password
PASSED
test_param.py::test_login1[ -password] 登录的用户名: , 密码:password
PASSED
test_param.py::test_login1[username- ] 登录的用户名:username, 密码: 
PASSED

======================================================== 4 passed, 52 deselected in 0.02s ========================================================
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# 
```

+ -v打印详细日志

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest -v -k 'login1'
============================================================== test session starts ===============================================================
platform linux -- Python 3.10.6, pytest-7.2.1, pluggy-1.0.0 -- /usr/bin/python3
cachedir: .pytest_cache
rootdir: /root/code/vscode-server/PyTest/L2, configfile: pytest.ini
collected 56 items / 52 deselected / 4 selected                                                                                                  

test_param.py::test_login1[right_usename-right_password] PASSED                                                                            [ 25%]
test_param.py::test_login1[wrong_username-wrong_password] PASSED                                                                           [ 50%]
test_param.py::test_login1[ -password] PASSED                                                                                              [ 75%]
test_param.py::test_login1[username- ] PASSED                                                                                              [100%]

======================================================== 4 passed, 52 deselected in 0.02s ========================================================
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# 
```

+ -s打印输出日志（一般-vs一起使用）

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest -s -k 'login1'
============================================================== test session starts ===============================================================
platform linux -- Python 3.10.6, pytest-7.2.1, pluggy-1.0.0
rootdir: /root/code/vscode-server/PyTest/L2, configfile: pytest.ini
collected 56 items / 52 deselected / 4 selected                                                                                                  

test_param.py 登录的用户名:right_usename, 密码:right_password
.登录的用户名:wrong_username, 密码:wrong_password
.登录的用户名: , 密码:password
.登录的用户名:username, 密码: 
.

======================================================== 4 passed, 52 deselected in 0.02s ========================================================
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# 
```

+ --collect-only(测试平台，pytest自动导入)

```py
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# pytest --collect-only -k 'login1'
============================================================== test session starts ===============================================================
platform linux -- Python 3.10.6, pytest-7.2.1, pluggy-1.0.0
rootdir: /root/code/vscode-server/PyTest/L2, configfile: pytest.ini
collected 56 items / 52 deselected / 4 selected                                                                                                  

<Module test_param.py>
  <Function test_login1[right_usename-right_password]>
  <Function test_login1[wrong_username-wrong_password]>
  <Function test_login1[ -password]>
  <Function test_login1[username- ]>

================================================= 4/56 tests collected (52 deselected) in 0.01s ==================================================
root@99eb4bd37fb2:~/code/vscode-server/PyTest/L2# 
```

## 执行Pytest

+ 代码执行main函数

```py
if __name__ == '__main__':
    # 1、运行当前目录下所有符合规则的用例，包括子目录（test_*.py 和 *_test.py）
    # pytest.main()

    # 2、运行test_first.py::test_answer模块中的某一用例
    # pytest.main(['test_param.py::test_dk','-vs'])

    # 3、运行某个标签
    pytest.main(['test_command_param.py','-vs','-m','float'])
```

+ 使用python -m pytest调用pytest

```py
PS E:\PycharmProjects\PyTest\L2> python -m pytest -vs .\test_param.py^
```

## pytest异常处理

+ try...except

```py
try:
    a = int(input('Please input a number: '))
    b = int(input('Please input a number: '))
    c = a / b
    print(f'{a} / {b} = {c}')
except(ValueError, ArithmeticError):
    print('ValueError or ArithmeticError')
except:
    print("Unknown Error")
print("End")
```

+ pytest.raise()
    + 可以捕获特定的异常
    + 获取捕获的异常的细节（异常类型、异常信息）
    + 发生异常，后面的代码将不会被执行

```py
def test_raise1():
    with pytest.raises(ZeroDivisionError):
        raise ZeroDivisionError('除数为0')


def test_raise2():
    with pytest.raises((ValueError, ZeroDivisionError)):
        raise ZeroDivisionError('除数为0')


# 正则匹配里的内容必须和设置的内容一样，否则将会认为失败
def test_raise3():
    with pytest.raises((ValueError, ZeroDivisionError), match='value must be 0 or none'):
        raise ZeroDivisionError('value must be 0 or none')

def test_raise4():
    with pytest.raises((ValueError, ZeroDivisionError)) as exc_info:
        raise ValueError('value must be 0 or none')
    assert exc_info.type is ValueError
    assert exc_info.value.args[0] == 'value must be 0 or none'
```

# Pytest_L3
## Pytest结合数据驱动-yaml

+ 什么是数据驱动
    + 数据驱动就是数据的改变从而驱动自动化测试的执行，最终引起测试结果的改变。简单来说就是参数化的应用。

+ 应用
    + App、Web、接口自动化测试
    + 测试步骤数据驱动
    + 测试数据的驱动
    + 配置的数据驱动

### yaml文件介绍

+ 对象：键值对的集合，用冒号“:”表示
+ 数组：一组按次序排列的值，前加“-”
+ 纯量：单个的，不可再分的值
    + 字符串
    + 布尔值
    + 整数
    + 浮点数
    + Null
    + 时间
    + 日期

+ 读取yaml文件
    + 安装：pip install pyyaml
    + 方法：yaml.safe_load(f)
    + 方法：yaml.safe_dump(f)

1. datas/data.yaml

```yaml
#相当于[[1,2,3],[3,6,9],[100,200,300]]
-
  - 1
  - 2
  - 3
-
  - 3
  - 6
  - 9
-
  - 100
  - 200
  - 300
```

2. func/operation.py

```py
# coding=utf-8
"""
@File    : operation.py
@Time    : 2023/2/26 22:58
@Author  : Sun
@Description : 被测对象
"""

# 被测方法，相加功能
def my_add(x, y):
    result = x + y
    return result
```

3. testcase/test_add.py

```py
# coding=utf-8
"""
@File    : test_add.py
@Time    : 2023/2/26 22:58
@Author  : Sun
@Description : 测试用例
"""
import pytest
import yaml

from L3.func.operation import my_add

file_path = '../datas/data.yaml'


# 读取yaml文件
def get_data():
    with open(file_path, mode='r', encoding='utf-8') as f:
        data = yaml.safe_load(f)
    return data


def test_get_data():
    print(get_data())


class TestWithYAML:
    # 参数化适合少量数据测试，不适合批量数据
    @pytest.mark.parametrize('x,y,expected', [[1, 2, 3], [3, 6, 9], [100, 200, 300],
                                              [11, 22, 33], [32, 62, 94], [1001, 2001, 3002]])
    def test_add1(self, x, y, expected):
        assert my_add(int(x), int(y)) == int(expected)

    # 使用yaml文件测试
    @pytest.mark.parametrize('x,y,expected', get_data())
    def test_add2(self, x, y, expected):
        assert my_add(int(x), int(y)) == int(expected)


if __name__ == '__main__':
    pytest.main(['test_add.py','-vs'])

```

## Pytest 结合数据驱动-excel

+ openpyxl

```py
def get_excel():
    # 获取工作簿
    book = openpyxl.load_workbook('../datas/params.xlsx')

    # 获取工作表
    sheet = book.active

    # 获取单元格数据
    # a_1 = sheet['A1'].value
    # print(a_1)
    # 获取数据时column和row的索引都是从1开始
    # c_3 = sheet.cell(column=3, row=3).value
    # print(c_3)

    # 获取多个单元格
    cells = sheet['A1':'C7']
    values = []
    for row in cells:
        datas = []
        for cell in row:
            datas.append(cell.value)
        values.append(datas)
    # print(values)
    return values


    # 使用excel文件测试
    @pytest.mark.parametrize('x,y,expected', get_excel())
    def test_add_excel(self, x, y, expected):
        assert my_add(int(x), int(y)) == int(expected)
```

## Pytest 结合数据驱动-csv

```py
# 读取csv文件
def get_csv():
    with open('../datas/demo.csv', 'r') as f:
        datas = csv.reader(f)
        valuse = []
        for line in datas:
            valuse.append(line)
        return valuse

    # 使用csv文件测试
    @pytest.mark.parametrize('x,y,expected', get_csv())
    def test_add_csv(self, x, y, expected):
        assert my_add(int(x), int(y)) == int(expected)
```

## Pytest 结合数据驱动-json


```py
# 读取json文件
def get_json():
    with open('../datas/data.json','r') as f:
        datas = json.loads(f.read())
        return list(datas.values())

    # 使用json文件测试
    @pytest.mark.parametrize('x,y,expected', get_json())
    def test_add_json(self, x, y, expected):
        assert my_add(int(x), int(y)) == int(expected)
```

## Pytest 测试用例生命周期管理-Fixture用法

1. 命令灵活：对应setup,teardown,可以不起这两个名字
2. 数据共享：在conftest.py配置里写方法，可以实现数据共享，不需要import导入
3. scope的层次及申请的yield组合相当于各种setup和teardown
4. 实现参数化

+ 场景：
    测试用例执行时，加入有10条用例，其中4条需要登录，setup和teardown无法满足
    
+ 步骤
    1. 导入pytest
    2. 在登录的函数(要实现自动化的函数)上面加上@pytest.fixture()
    3. 在要使用的测试方法中传入（登录函数名称），将会执行登录的方法
    4. 不传入登录函数的将会直接执行测试方法

```py
import pytest


# 定义了登录的fixture
@pytest.fixture
def login():
    print('完成登录操作')


# 未定义登录的fixture
def login1():
    print()
    print('完成登录操作')


def test_search():
    print('搜索')


# 使用fixture方法，需要调用函数就先传入函数名字，否则就不需要
def test_order(login):
    print('下单功能')


# 未使用fixture方法
def test_cart():
    login1()
    print('购物车')

```

## Fixture在自动化中的应用-作用域

|取值|范围|说明|
|-|-|-|
|function|函数级|每一个函数或方法都会调用|
|class|类级别|每个测试类只运行一次|
|module|模块级|每个.py文件调用一次|
|package|包级|每个python包只调用一次（暂不支持）|
|session|会话级|每个会话只运行一次，绘画内所有方法及类，模块都共享这个方法|


```py
import pytest


# 定义了登录的fixture，尽量避免以test_开头
# 设置作用域 scope="module"
# 设置作用域 scope="class"

# 定义了登录的fixture
# @pytest.fixture(scope="class")
@pytest.fixture(scope="module")
def login():
    print('完成登录操作')


def test_search():
    print('搜索')


# 使用fixture方法，需要调用函数就先传入函数名字，否则就不需要
def test_order(login):
    print('下单功能')


# 未使用fixture方法
def test_cart():
    print('购物车')


class TestDemo:
    def test_case1(self,login):
        print('case1')

    def test_case2(self,login):
        print('case2')

```

## Fixture在自动化中的应用-yield关键字

+ 场景：测试方法后销毁清除数据的如何进行

+ 解决：在fixture函数中加入yield关键字，yield是调用第一次返回的结果，第二次执行它下面的语句返回

+ 步骤：在@pytest.fixture(scope=module)，在登录的方法中加入yield，之后加销毁清除的步骤

```py
import pytest


# 定义了登录的fixture，尽量避免以test_开头
# 设置作用域 scope="module"
# 设置作用域 scope="class"

# 定义了登录的fixture
@pytest.fixture(scope="class")
# @pytest.fixture(scope="module")
# @pytest.fixture(scope="session")
def login():
    # setup 操作
    print('完成登录操作')
    token = 'abcagasss'
    username = 'user1'
    # 相当于return，但是如果改成return，将不会执行后续操作
    yield token,username
    # teardown 操作
    print('完成登出操作')


def test_search():
    print('搜索')


# 使用fixture方法，需要调用函数就先传入函数名字，否则就不需要
def test_order(login):
    token,username = login
    print(f'token:{token},username:{username}')
    print('下单功能')


# 未使用fixture方法
def test_cart():
    print('购物车')


class TestDemo:
    def test_case1(self,login):
        print('case1')

    def test_case2(self,login):
        print('case2')

```

## Pytest生命周期管理-自动注册

+ 场景
    与其他人一起开发，公共模块要在不同文件中，要在大家都能访问到的地方

+ 解决
    使用conftest.py这个文件进行数据共享，并且可以放在不同位置起到共享作用

+ 前提
    + conftest文件名不能换
    + 放在项目下是全局共享的地方
+ 执行
    + 系统执行到参数login时，先从本模块中查找是否有这个名字的变量什么的
    + 之后在conftest.py中找是否有

+ 步骤
    将登录模块@pytest.fixture写在conftest.py文件中
    
```py
# conftest.py
import pytest

# conftest.py 名字固定，不能改变
# 定义公用方法
# 定义了登录的fixture
@pytest.fixture(scope="class")
# @pytest.fixture(scope="module")
# @pytest.fixture(scope="session")
def login():
    # setup 操作
    print('完成登录操作')
    token = 'abcagasss'
    username = 'user1'
    # 相当于return，但是如果改成return，将不会执行后续操作
    yield token, username
    # teardown 操作
    print('完成登出操作')


@pytest.fixture(scope="session")
def connectDB():
    print('连接数据库')
    yield
    print('断开数据库')

# test_fixture_use_conftest.py
def test_get_order(connectDB, login):
    token, username = login
    print(f'token:{token},username:{username}')
    print('获取订单')
```

## Pytest生命周期管理-自动生效

+ 场景：
    不想测试方法有改动，或全部都自动实现，自动应用，没特例，也都不需要返回值时可以选择自动应用

+ 解决：
    使用fixture中参数 autouse=True 实现

+ 步骤：
    在方法上面加@pytest.fixture(autouse=True)
    
```py
# conftest.py
@pytest.fixture(scope="function",autouse=True)
def login1():
    # setup 操作
    print('完成登录操作—autouse=True')
    token = 'abcagasss'
    username = 'user1'
    # 相当于return，但是如果改成return，将不会执行后续操作
    yield token, username
    # teardown 操作
    print('完成登出操作-autouse=True')

# test_fixture_use_conftest1.py
class TestDemo:
    def test_case1(self):
        print('case1')

    def test_case2(self):
        print('case2')
```

## Pytest fixture 实现参数化

+ 场景：
    测试离不开数据，为了数据灵活，一般数据都是通过参数传递的

+ 解决：
    fixture 通过固定参数request传递

+ 步骤：
    在fixture中增加@pytest.fixture(params=[1,2,3,'linda'])
    在方法参数中写request，方法体里面使用request.param接收参数

```py
import pytest


@pytest.fixture(params=[['harry', '123'], ['lice', 999]])
def login_param(request):
    print(f'用户名：{request.param}')
    return request.param


def test_demo1(login_param):
    print(f'demo1 case:数据为：{login_param}')
```

# Pytest_L4

## Pytest 配置文件-pytest.ini

+ pytest.ini是pytest的配置文件
+ 可以修改pytest的默认行为
+ 不能使用任何中文符号，包括汉字、空格、引号、冒号等等

+ 作用

+ 修改用例的命名规则
+ 配置日志格式，比代码配置更方便
+ 添加标签，防止运行过程报警告错误
+ 指定执行目录
+ 排除搜索目录

执行check_开头和 test_开头的所有的文件，后面一定要加*
python_files = check_* test_*


## Pytest插件

+ pytest 插件分类
    + 外部插件 pip install 安装插件
    + 本地插件 pytest自动模块发现机制（conftest.py）存放的
    + 内置插件 代码内部的_pytest目录加载
+ pytest hook介绍
+ pytest hook执行顺序

## Pytest 常用插件

>https://pypi.org/search/?q=pytest

```py
pytest --collect-only 收集测试用例
pip install pytest-ordering 控制用例的执行顺序
pip install pytest-xdist 分布式并发执行测试用例
```

## Pytest并行与分布式执行

```py
pip install pytest-xdist 分布式并发执行测试用例

# auto 自行决定调用CPU核心，也可自己指定CPU核心数
pytest -n auto
```

## Pytest内置插件 hook 体系

+ 是个函数，在系统消息触时被系统调用
+ 自动触发机制
+ Hook函数的名称是确定的
+ pytest有非常多的勾子函数
+ 使用时直接编写函数体

[![image.png](https://i.postimg.cc/0NVpNMkh/image.png)](https://postimg.cc/zLRLtfRk)


```py
conftest.py(存放在根目录下)
# hook 体系

from typing import Optional

def pytest_collection_modifyitems(session, config, items:list):
    for item in items:
        item.name = item.name.encode('utf-8').decode('unicode-escape')
        item._nodeid = item.nodeid.encode('utf-8').decode('unicode-escape')
    """Called after collection has been performed. May filter or re-order
    the items in-place.

    :param pytest.Session session: The pytest session object.
    :param pytest.Config config: The pytest config object.
    :param List[pytest.Item] items: List of item objects.
    """


def pytest_runtest_setup(item: "Item") -> None:
    print("hook : setup")
    """Called to perform the setup phase for a test item.

    The default implementation runs ``setup()`` on ``item`` and all of its
    parents (which haven't been setup yet). This includes obtaining the
    values of fixtures required by the item (which haven't been obtained
    yet).
    """

def pytest_runtest_teardown(item: "Item", nextitem: Optional["Item"]) -> None:
    print('hook : teardown')
    """Called to perform the teardown phase for a test item.

    The default implementation runs the finalizers and calls ``teardown()``
    on ``item`` and all of its parents (which need to be torn down). This
    includes running the teardown phase of fixtures required by the item (if
    they go out of scope).

    :param nextitem:
        The scheduled-to-be-next test item (None if no further test item is
        scheduled). This argument is used to perform exact teardowns, i.e.
        calling just enough finalizers so that nextitem only needs to call
        setup functions.
    """

```

```py
test_hook.py

# hook 体系

def test_demo1():
    print('test_demo1')
```

> 总结

1. hook函数名字固定
2. hook函数会被自动执行
3. 执行是有先后顺序的
4. pytest定义了很多hook函数，可以在不同阶段实现不同功能

## Pytest插件开发

pytest_collection_modifyitems 收集上来的测试用例


# Allure2_L1

## Allure2安装

+ Java开发、轻量级、灵活的测试报告工具
+ 多平台的Report框架
+ 支持多语言，Python、JavaScript、PHP、Ruby
+ 可以为开发/测试/管理等人员提供详尽的测试报告，包括测试类别、测试步骤、日志、图片、视频等
+ 可为管理层提供高水准的统计报告
+ 可以集成到Jenkins生成在线的趋势汇总报告

```sh
# Ubuntu 2204
# 1. 配置Java环境
sudo apt-get update
sudo apt-get install default-jre
sudo apt-get install default-jdk

# 2. 配置allure
sudo apt-add-repository ppa:qameta/allure
sudo apt-get update 
sudo apt-get install allure

sudo nano /etc/environment
ALLURE_HOME="/usr/lib/allure/"
source /etc/environment


# 3. 验证版本 
allure --version

```

## 运行方式

1. 运行用例，添加 --alluredir

```sh
pytest [测试用例/模块/包] --alluredir=存放结果路径
pytest [测试用例/模块/包] --alluredir=./results
```

2. 生成报告
    + allure server 生成在线报告
    + allure generate 生成静态资源报告

```sh
# 指定端口、IP
allure serve ./results/ -h 172.17.0.5 -p 20000
```

# Allure2_L2

## allure2 报告生成

>常用参数
+ allure generate可以输出路径，也可以清理上次的报告记录
    + -o / --output 输出报告的路径
    + -c / --clean 如果报告路径重复
+ allure open打开报告
    + -h / --host 主机IP地址，此主机将用于启动报表的web服务
    + -p / --port 主机端口，此端口将用于启动报表的web服务器，默认值0


### 清理上次结果 --clean-alluredir

```sh
root@3832dba7df75:~/code/vscode-server/PyTest/Allure2_L1/allure2_2# pytest test_allure_demo.py --alluredir=./results --clean-alluredir
```

### allure generate 生成静态资源报告

```sh
root@3832dba7df75:~/code/vscode-server/PyTest/Allure2_L1/allure2_2# allure generate ./results
Report successfully generated to allure-report
```

### allure generate 生成静态资源报告,指定输出报告路径

```sh
root@3832dba7df75:~/code/vscode-server/PyTest/Allure2_L1/allure2_2# allure generate ./results -o ./myreports 
```

### allure open打开报告，指定IP，port

```sh
root@3832dba7df75:~/code/vscode-server/PyTest/Allure2_L1/allure2_2# allure open -h 172.17.0.3 -p 20000 ./allure-report/
```

## allure2 报告中添加常用用例

>allure用法

|方法名|方法参数|参数说明|
|-|-|-|
|@allure.epic()|epic描述|敏捷里面的概念，定义史诗，往下是feature|
|@allure.feature()|模块名称|功能点的描述，往下是story|
|@allure.story|用户故事|用户故事，往下是title|
|@allure.title(用例的标题)|用例的标题|重命名html报告名称|
|@allure.step()|操作步骤|测试用例的步骤|
|@allure.testcase()|测试用例的连接地址|对应功能测试用例系统里面的case|
|@allure.issue()|缺陷|对应缺陷管理系统里面的链接|
|@allure.description|用例描述|测试用例的描述|
|@allure.severity()|用例等级|blocker,citical,normal,minor,trival|
|@allure.link()|链接|定义一个链接，在测试报告展现|
|@allure.attachment()|附件|报告添加附件|

+ 通过使用装饰器@allure.title可以为测试用例自定义一个可阅读性的标题
+ allure.title的三种使用方法
1. 直接使用@allure.title为测试用例自定义标题

```py
@allure.title('自定义测试用例标题')
def test_with_title1():
    assert True
```

2. @allure.title 支持通过占位符的方式传递参数，可以实现测试用例标题参数化，动态生成测试用例标题

```py
@allure.title('参数化用例标题:参数1：{param1}，参数2，{parame2}')
@pytest.mark.parametrize('param1,parame2,expected',[[1,2,3],[0.2,0.31,0.5],(12,32,44),(90,22,112)])
def test_with_title2(param1,parame2,expected):
    assert param1 + parame2 == expected
```

3. allure.dynamic.title 动态更新测试用例标题

```py
@allure.title("动态更新前的标题")
def test_with_title3():
    assert True
    allure.dynamic.title("动态更新后的标题")
```

## allure2 报告中添加用例步骤

>Allure支持两种方法：

1. 使用装饰器定义一个测试步骤，在测试用例中使用

```py
@allure.step
def simple_step1(step_param1,step_param2 = None):
    # 定义一个测试步骤1
    print('首先：链接数据库，准备测试数据')
    print(f'步骤1：打开页面，参数1：{step_param1}, 参数2：{step_param2}')

@allure.step
def simple_step2(step_param):
    # 定义一个测试步骤2
    assert False
    print(f'步骤2：完成搜索：{step_param} 功能')


#@pytest.mark.parametrize('param1',['pytest','allure'])
@pytest.mark.parametrize('param1',['pytest','allure'],ids=['search pytest','search allure'])
def test_parameterize_with_id(param1):
    simple_step2(param1)

@pytest.mark.parametrize('param1',[True,False])
@pytest.mark.parametrize('param2',['Value 1','Value 2'])
def test_parameterize_with_two_params(param1,param2):
    simple_step1(param1,param2)

@pytest.mark.parametrize('param2',["Pytest","unittest"])
@pytest.mark.parametrize('param1,param3',[[1,2]])
def test_parameterize_with_uneven_value_sets(param1,param2,param3):
    simple_step1(param1,param3)
    simple_step2(param2)
```

2. 使用with allure.step() 添加测试步骤

```py
@allure.title('搜索用例:{searchkey}')
@pytest.mark.parametrize('searchkey',['pytest','allure','unittest'])
def test_step_in_method(searchkey):
    with allure.step('测试步骤1：打开页面'):
        print('操作 a')
        print('操作 b')

    with allure.step(f'测试步骤2：搜索 {searchkey}'):
        print(f'搜索操作: {searchkey}')

    with allure.step('测试步骤3：断言'):
        assert False
```

## allure2 报告中添加用例链接

1. @allure.link(url,name)添加一个普通的link链接

```py
# 1. 添加一个普通的 link 链接
@allure.link('https://ceshiren.com/t/topic/15860')
def test_with_link():
    pass

# 2. 添加一个普通的 link 链接, 添加name别名
@allure.link('https://ceshiren.com/t/topic/15860',name="这是一个链接")
def test_with_link_name():
    pass
```

2. @allure.testcase（url,name) 添加一个用例管理系统连接

```py
# 3. 添加用例管理系统链接
TEST_CASE_LING = "www.baidu.com"
@allure.testcase(TEST_CASE_LING,"用例管理系统")
def test_with_testcase_link():
    pass
```

3. @allure.issue(url,name) 添加bug管理系统连接

```py
# 4. 添加 bug管理系统链接
# pytest test_allure_link.py --alluredir=./results --allure-link-pattern=issue:https://ceshiren.com/t/topic/{}
@allure.issue("15860",'bug管理系统')
def test_with_issue():
    pass
```

## allure2 报告中添加用例分类

1. @allure.epic:敏捷里面的概念，定义史诗(相当于需求)，往下是feature

```py
pytest test_allure_feature.py --alluredir=./results --allure-epics=demand1
```

2. @allure.feature:功能点的描述，理解成模块，往下是story

```py
pytest test_allure_feature.py --alluredir=./results --allure-features=demand1_function2
```

3. @allure.story:故事story是feature的子集

```py
pytest test_allure_feature.py --alluredir=./results --allure-stories=demand1_function2_sub_function3
pytest test_allure_feature.py --alluredir=./results --allure-stories=demand1_function2_sub_function3,demand2_function1_sub_function3
```

4. 需求1+需求2-功能模块1-子功能模块3

```py
pytest test_allure_feature.py --alluredir=./results --allure-epics=demand1 --allure-stories=demand2_function1_sub_function3
```

## 报告中添加用例描述

1. 使用装饰器 @allure.description()传递一个字符

```py
@allure.description('''
通过@allure.description()传递
多行描述
第一行
第二行
''')
def test_description_provide_string():
    assert True
```

2. 使用装饰器 @allure.description_html传递一段HTML文本来描述测试用例

```py
@allure.description_html('''
<div id="lg" class="s-p-top"><img id="s_lg_img" class="s_lg_img_gold_show" src="//www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png" width="270" height="129" onerror="this.src='https://dss0.bdstatic.com/5aV1bjqh_Q23odCf/static/superman/img/logo/bd_logo1-66368c33f8.png';this.onerror=null;" usemap="#mp" title="" cursor="default"><img id="s_lg_img_new" class="s_lg_img_gold_showre" src="//www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png" width="270" height="129" onerror="this.src='https://dss0.bdstatic.com/5aV1bjqh_Q23odCf/static/superman/img/logo/bd_logo1-66368c33f8.png';this.onerror=null;" usemap="#mp" title="" cursor="default"><img hidefocus="true" id="s_lg_img_aging" class="index-logo-aging-tools" src="//www.baidu.com/img/PCfb_5bf082d29588c07f842ccde3f97243ea.png" width="270" height="129" onerror="this.src='https://dss0.bdstatic.com/5aV1bjqh_Q23odCf/static/superman/img/logo/bd_logo1-66368c33f8.png';this.onerror=null;" usemap="#mp" title="" cursor="default"><map name="mp" id="s_mp"><area style="cursor:pointer;outline:none;" shape="rect" coords="0,0,270,129" href="//www.baidu.com/s?wd=%E7%99%BE%E5%BA%A6%E7%83%AD%E6%90%9C&amp;sa=ire_dl_gh_logo_texing&amp;rsv_dl=igh_logo_pc" target="_blank" title="点击一下，了解更多" onmousedown="&quot;return" ns_c({&#39;fm&#39;:&#39;behs&#39;,&#39;tab&#39;:&#39;bdlogo&#39;})&quot;=""></map></div>
''')
def test_description_html():
    assert True
```

3. 直接在测试用例方法中通过编写文档注释的方法来添加描述

```py
def test_description_dostring():
    """
    直接写在测试用例方法中
    通过编写文档注释的方法
    来添加描述
    """
    assert 1+1 == 2
```

4. 用例代码内部动态添加描述信息

```py
@allure.description('这个描述将被替换')
def test_dynamic_description():
    assert 1+1 == 2
    allure.dynamic.description('替换后的文本信息')

@allure.description('这个描述将被替换')
def test_dynamic_description_html():
    assert 1+1 == 2
    allure.dynamic.description_html('''
    替换后的html信息
    <div id="lg" class="s-p-top"><img id="s_lg_img" class="s_lg_img_gold_show" src="//www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png" width="270" height="129" onerror="this.src='https://dss0.bdstatic.com/5aV1bjqh_Q23odCf/static/superman/img/logo/bd_logo1-66368c33f8.png';this.onerror=null;" usemap="#mp" title="" cursor="default"><img id="s_lg_img_new" class="s_lg_img_gold_showre" src="//www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png" width="270" height="129" onerror="this.src='https://dss0.bdstatic.com/5aV1bjqh_Q23odCf/static/superman/img/logo/bd_logo1-66368c33f8.png';this.onerror=null;" usemap="#mp" title="" cursor="default"><img hidefocus="true" id="s_lg_img_aging" class="index-logo-aging-tools" src="//www.baidu.com/img/PCfb_5bf082d29588c07f842ccde3f97243ea.png" width="270" height="129" onerror="this.src='https://dss0.bdstatic.com/5aV1bjqh_Q23odCf/static/superman/img/logo/bd_logo1-66368c33f8.png';this.onerror=null;" usemap="#mp" title="" cursor="default"><map name="mp" id="s_mp"><area style="cursor:pointer;outline:none;" shape="rect" coords="0,0,270,129" href="//www.baidu.com/s?wd=%E7%99%BE%E5%BA%A6%E7%83%AD%E6%90%9C&amp;sa=ire_dl_gh_logo_texing&amp;rsv_dl=igh_logo_pc" target="_blank" title="点击一下，了解更多" onmousedown="&quot;return" ns_c({&#39;fm&#39;:&#39;behs&#39;,&#39;tab&#39;:&#39;bdlogo&#39;})&quot;=""></map></div>
    ''')
```

## allure2报告中添加用例优先级

+ 应用场景，用例执行时，希望按照严重级别执行测试用例
+ 解决：为每个用例添加一个等级的装饰器 @allure.severity
+ 类上添加的级别，对类中没有添加级别的方法生效

+ allure对严重级别定义分为5个
1. Blocker级别：中断缺陷（客户端程序无响应，无法执行下一步操作）
2. Critical级别：临界缺陷（功能点缺失）
3. Normal级别：普通缺陷（数值计算错误）
4. Minor级别：次要缺陷（界面错误与UI需求不符）
5. Trivial级别：轻微缺陷（必输项无提示，或提示不规范）

+ 运行时添加命令行参数 --allure-serverities

```py
import allure

def test_with_no_severity_label():
    assert True

@allure.severity(allure.severity_level.TRIVIAL)
def test_with_trival_severity():
    assert True

@allure.severity(allure.severity_level.NORMAL)
def test_with_normal_severity():
    assert True


@allure.severity(allure.severity_level.NORMAL)
class TestClassWithNormalSeverity:
    def test_inside_class_with_no_severity(self):
        assert True

    @allure.severity(allure.severity_level.CRITICAL)
    def test_inside_class_with_critical_severity(self):
        assert True

    @allure.severity(allure.severity_level.MINOR)
    def test_inside_class_with_minor_severity(self):
        assert True

    @allure.severity(allure.severity_level.BLOCKER)
    def test_inside_class_with_blocker_severity(self):
        assert True

$: pytest test_allure_serverity.py --alluredir=./results --allure-severities=rmal
$: allure serve ./results/ -h 172.17.0.5 -p 20000

```

## allure2报告中添加用例支持tag标签

```py
import pytest
import allure

# 当用例通过时标记 xfail
@pytest.mark.xfail(condition=lambda :True,reason='这是一个预期失败的用例')
def test_xfail_expected_failure():
    assert False

# 当用例通过时标记 xpass
@pytest.mark.xfail
def test_xfail_unexpected_pass():
    assert True

# 跳过用例
@pytest.mark.skipif('2+2!=5',reason='当条件触发时，这个用例被跳过 @pytest.mark.skipif')
def test_skip_by_triggered_condition():
    assert True


@pytest.fixture()
def fun1():
    print('这是fixture fun1 的前置动作')
    yield
    print('这是fixture fun1 的后置动作')

@pytest.fixture()
def func(request):
    # 前置动作 -- 相当于setup
    print("这是一个fixture 前置方法")

    # 后置动作 -- 相当于teardown
    # 定义一个终结器，teardown动作放在终结器中
    def over():
        print("session 级别终结器")
    
    # 添加终结器，在执行完测试用例之后会执行终结器中的内容
    request.addfinalizer(over)

class TestClass(object):
    def test_with_scopped_finalizers(self,func,fun1):
        print('测试用例')
```


## allure2 报告中支持记录失败重试功能

+ 重试功能可以使用pytest相关插件 pytest-rerunfailures

```py
# pip install pytest-rerunfailures
# reruns = 2 失败重试次数
# reruns_delay=2 失败重试间隔
@pytest.mark.flaky(reruns=3,reruns_delay=1.5)
def test_rerun2():
    assert False
```

# Allure2_L3

## Allure2 报告中添加附件-图片

1. allure.attach.file(source,name,attachment_type,extension)
    + source：文件路径
    + name：附件名字
    + attachment_type：附件类型，是allure.attachment_type其中的一种
    + extension：附件的扩展名

```py
import allure
import logging

class TestWithAttach:
    def test_pic(self):
        logging.info('添加一个图片')

        allure.attach.file('./img/pic1.png',
                           name='这是一个测试图片',
                           attachment_type=allure.attachment_type.PNG,
                           extension='png')
```

2. allure.attach(body,name=None,attachment_type=None,extension=None)
    + body：要写入附件的内容
    + name：附件名字
    + attachment_type：附件类型，是allure.attachment_type其中的一种
    + extension：附件的扩展名

```py
def test_pic1(self):
    logging.info('这是通过 allure.attach 添加的一个测试图片')
    with open('./img/pic1.png',mode='rb') as f:
        # 文本的内容
        file = f.read()
        # 将文件内容添加到allure.attach()方法中
        allure.attach(file,name='页面截图',attachment_type=allure.attachment_type.PNG)
```

## Allure2 报告中添加附件-日志

+ 配置工具类

```py
# 创建一个日志模块 log_util.py

import sys
sys.path.append('./')

import logging
import os

from logging.handlers import RotatingFileHandler

# 绑定句柄到logger对象
logger = logging.getLogger(__name__)

# 获取当前工具文件所在的路径
root_path = os.path.dirname(os.path.abspath(__file__))

# 拼接当前要输出的日志的路径
log_dir_path = os.sep.join([root_path,f'/logs'])
if not os.path.isdir(log_dir_path):
    os.mkdir(log_dir_path)

# 创建日志记录器，指明日志保存路径，每个日志的大小，保存的上限
file_log_handler = RotatingFileHandler(os.sep.join([log_dir_path,'log.log']),maxBytes=1024*1024,backupCount=10,encoding='utf-8')

# 设置日志的格式
data_string = '%Y-%m-%d %H:%M:%S'
formatter = logging.Formatter(
    '[%(asctime)s] [%(levelname)s] [%(filename)s]/[line: %(lineno)d]/[%(funcName)s] [%(message)s]',data_string
)

# 日志输出到控制台的句柄
stream_handler = logging.StreamHandler()
# 将日志记录器指定日志的格式
file_log_handler.setFormatter(formatter)
stream_handler.setFormatter(formatter)

# 为全局的日志工具对象添加日志记录器
# 绑定句柄到logger对象
logger.addHandler(stream_handler)
logger.addHandler(file_log_handler)

# 设置日志输出级别
logger.setLevel(level=logging.INFO)
```


```py
import sys
sys.path.append('../../tools')
from logTools.log_util import logger

import allure

@allure.epic('需求1')
@allure.feature('功能模块1')
class TestEpic:
    @allure.story('子功能模块1')
    @allure.title('用例1')
    def test_case1(self):
        logger.info('这是TestEpic 第1条用例')
        print('用例1')
```

+ 禁用日志
--allure-no-capture

## Allure2 报告中添加附件-html

+ 语法：allure.attach(body,name=None,attachment_type=None,extension=None)
    + body：要写入附件的内容
    + name：附件名字
    + attachment_type：附件类型，是allure.attachment_type其中的一种
    + extension：附件的扩展名
    
```py
import allure
import sys
sys.path.append('../../tools')
from logTools.log_util import logger

class TestAllureHtml:

    def test_html_part(self):
        logger.info('这是添加一个html 部分代码的测试用例')
        allure.attach('''
        <div class="boiling-title_ZrdUH"><img src="https://ss1.baidu.com/6ONXsjip0QIZ8tyhnq/it/u=423474926,1801248814&amp;fm=179&amp;app=35&amp;f=PNG?w=518&amp;h=136&amp;s=ADFEEB16D210A1925C7BF2EA0300E03E"></div>
        ''',name='allure.attach(name=html片段)',attachment_type=allure.attachment_type.HTML,extension='extension:html')
```

# Allure2_L4

## allure2报告定制

+ 定制页面logo

1. 获取安装路径
```sh
root@3832dba7df75:~/code/vscode-server# ll /root/downloads/allure
total 24
drwxr-xr-x  6 root root 4096 Feb  7 11:41 ./
drwxr-xr-x  3 root root 4096 Mar 11 10:55 ../
drwxr-xr-x  2 root root 4096 Feb  7 11:41 bin/
drwxr-xr-x  2 root root 4096 Feb  7 11:41 config/
drwxr-xr-x  3 root root 4096 Mar 11 09:25 lib/
drwxr-xr-x 12 root root 4096 Mar 11 09:25 plugins/
root@3832dba7df75:~/code/vscode-server# 
```

2. 修改config下的allure.yml文件

```py
plugins:
  - junit-xml-plugin
  - xunit-xml-plugin
  - trx-plugin
  - behaviors-plugin
  - packages-plugin
  - screen-diff-plugin
  - xctest-plugin
  - jira-plugin
  - xray-plugin
  - custom-logo-plugin
```

3. allure.yml修改后，在plugins下custom-logo-plugin内的static文件夹下修改style.css文件中的url，替换需要的文件

```yml
.side-nav__brand {
  background: url('custom-logo.svg') no-repeat left center !important;
  margin-left: 10px;
}
```

+ 修改标题内容

1. 修改style.css文件

```css
/* 去掉logo后面的Allure文本 */
.side-nav__brand-text{
  display: none;
}

/* 设置logo后面的字体大小与样式 */
.side-nav__brand::after{
  content: "测试俱乐部";
  margin-left: 18px;
  height: 20px;
  font-family: Arial, Helvetica, sans-serif;
  font-size: 13px;
}
```