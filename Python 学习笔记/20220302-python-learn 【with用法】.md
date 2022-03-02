# Python 学习笔记

## With 关键字用法

### 背景

有一些任务，可能事先需要设置，事后做清理工作。对于这种场景，Python的with语句提供了一种非常方便的处理方式。一个很好的例子是文件处理，你需要获取一个文件句柄，从文件中读取数据，然后关闭文件句柄。

如果不用 with 则就要使用 try catch 语句，在代码中，这样的语句经常被复用，所以 with 应运而生。

**with还可以优雅地处理上下文环境产生的异常。**

### 用法

原理：

>with 语句实质是上下文管理。
>
>1、上下文管理协议。包含方法`__enter__()` 和 `__exit__()`，支持该协议对象要实现这两个方法。
>
>2、上下文管理器，定义执行with语句时要建立的运行时上下文，负责执行with语句块上下文中的进入与退出操作。
>
>3、进入上下文的时候执行`__enter__`方法，如果设置as var语句，var变量接受`__enter__()`方法返回值。
>
>4、如果运行时发生了异常，就退出上下文管理器。调用管理器`__exit__`方法。

```python
with EXPR as VAR:
  BLOCK
```

其中： EXPR 可以是任意表达式； as VAR 是可选的。其一般的执行过程是这样的：

>计算 EXPR ，并获取一个上下文管理器。
>
>上下文管理器的 `__exit()__` 方法被保存起来用于之后的调用。
>
>调用上下文管理器的 `__enter()__` 方法。
>
>如果 with 表达式包含 as VAR ，那么 EXPR 的返回值被赋值给 VAR 。
>
>执行 BLOCK 中的表达式。
>调用上下文管理器的 `__exit()__` 方法。如果 BLOCK 的执行过程中发生了一个异常导致程序退出，那么异常的 type 、 value 和 traceback (即 sys.exc_info()的返回值 )将作为参数传递给 `__exit()__` 方法。否则，将传递三个 None 。

```python
mgr = (EXPR)
exit = type(mgr).__exit__ # 这里没有执行
value = type(mgr).__enter__(mgr)
exc = True
 
try:
  try:
    VAR = value # 如果有 as VAR
    BLOCK
  except:
    exc = False
    if not exit(mgr, *sys.exc_info()):
      raise
finally:
  if exc:
    exit(mgr, None, None, None)
```
这个过程有几个细节：

如果上下文管理器中没有 `__enter()__` 或者 `__exit()__` 中的任意一个方法，那么解释器会抛出一个 AttributeError。

在 BLOCK 中发生异常后，如果 `__exit()__` 方法返回一个可被看成是 True 的值，那么这个异常就不会被抛出，后面的代码会继续执行。

```python
class Mycontex(object):
    def __init__(self,name):
        self.name=name
    def __enter__(self):
        print("进入enter")
        return self
    def do_self(self):
        print(self.name)
        a
    def __exit__(self,exc_type,exc_value,traceback):
        print("退出exit")
        print(exc_type,exc_value)
if __name__ == '__main__':
    with Mycontex('test') as mc:
        mc.do_self()
```
即使程序发生了错误，python解释器终止了我们的程序，但是我们的类 还是顺利关闭了。

### 应用场景

1、文件操作。2、进程线程之间互斥对象。3、支持上下文其他对象

### 补充

多个项：

```python
with open("x.txt") as f1, open('xxx.txt') as f2:
    do something with f1,f2
```


### 参考

1. [Python 中的with关键字使用详解](http://www.zzvips.com/article/101419.html)

2. [python的with关键字](https://www.jianshu.com/p/5b01fb36fd4c)

3. [python的with用法（参考）](https://www.cnblogs.com/wanglei-xiaoshitou1/p/9238275.html)


