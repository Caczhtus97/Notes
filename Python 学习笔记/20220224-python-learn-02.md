# Python 学习笔记

## 基础语法

### 1.Python 迭代器

#### 1. 概念

迭代器是一种对象，该对象包含值的可计数数字。

迭代器是可迭代的对象，这意味着您可以遍历所有值。

从技术上讲，在 Python 中，迭代器是实现迭代器协议的对象，它包含方法 `__iter__()` 和 `__next__()`。

#### 2. 迭代器 VS 可迭代对象（Iterable）
列表、元组、字典和集合都是可迭代的对象。它们是可迭代的容器，您可以从中获取迭代器（Iterator）。

所有这些对象都有用于获取迭代器的 iter() 方法：

```python
mytuple = ("apple", "banana", "cherry")
myit = iter(mytuple)

print(next(myit))
print(next(myit))
print(next(myit))
```

```python
mystr = "banana"
myit = iter(mystr)

print(next(myit))
print(next(myit))
print(next(myit))
print(next(myit))
print(next(myit))
print(next(myit))
```

**提示：for 循环实际上创建了一个迭代器对象，并为每个循环执行 next() 方法。**

#### 创建迭代器

要把对象/类创建为迭代器，必须为对象实现 `__iter__()` 和 `__next__()` 方法。

`__iter__()` 方法的作用相似，您可以执行操作（初始化等），但必须始终返回迭代器对象本身。

`__next__()` 方法也允许您执行操作，并且必须返回序列中的下一个项目。

例子 

创建一个返回数字的迭代器，从 1 开始，每个序列将增加 1（返回 1、2、3、4、5 等）：

```python
class MyNumbers:
  def __iter__(self):
    self.a = 1
    return self

  def __next__(self):
    x = self.a
    self.a += 1
    return x

myclass = MyNumbers()
myiter = iter(myclass)

print(next(myiter))
print(next(myiter))
print(next(myiter))
print(next(myiter))
print(next(myiter))
```

#### 遍历器终止

如果你有足够的 next() 语句，或者在 for 循环中使用，则上面的例子将永远进行下去。

为了防止迭代永远进行，我们可以使用 StopIteration 语句。

在 `__next__()` 方法中，如果迭代完成指定的次数，我们可以添加一个终止条件来引发错误：

```python
class MyNumbers:
  def __iter__(self):
    self.a = 1
    return self

  def __next__(self):
    if self.a <= 20:
      x = self.a
      self.a += 1
      return x
    else:
      raise StopIteration

myclass = MyNumbers()
myiter = iter(myclass)

for x in myiter:
  print(x)
```

### 2. Python 模块

1. [链接一](https://www.w3school.com.cn/python/python_modules.asp)
2. [链接二](https://www.runoob.com/python/python-modules.html)

### 3. Python 文件

在 Python 中使用文件的关键函数是 open() 函数。

open() 函数有两个参数：文件名和模式。

有四种打开文件的不同方法（模式）：

- "r" - 读取 - 默认值。打开文件进行读取，如果文件不存在则报错。
- "a" - 追加 - 打开供追加的文件，如果不存在则创建该文件。
- "w" - 写入 - 打开文件进行写入，如果文件不存在则创建该文件。
- "x" - 创建 - 创建指定的文件，如果文件存在则返回错误。

此外，您可以指定文件是应该作为`二进制`还是`文本模式`进行处理。

- "t" - 文本 - 默认值。文本模式。
- "b" - 二进制 - 二进制模式（例如图像）。

#### 文件删除

如需删除文件，必须导入 OS 模块，并运行其 `os.remove()` 函数：

```python
import os
os.remove("demofile.txt")
```

#### 检查文件是否存在

```python
import os
if os.path.exists("demofile.txt"):
  os.remove("demofile.txt")
else:
  print("The file does not exist")
```

#### 删除文件夹

```python
import os
os.rmdir("myfolder")
```

**注意：只能删除空文件夹**



