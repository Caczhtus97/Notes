# Python 学习笔记

## 基础语法

### 1. Python 循环

关键字 `for` 、 `while`

区别于 `CPP` ， `Python` 可以配合 `else` 使用循环，以达到判断循环跳出的追踪

通过使用 else 语句，当条件不再成立时，我们可以运行一次代码块：

```python
i = 1
while i < 6:
  print(i)
  i += 1
else:
  print("i is no longer less than 6")
```

**for 同理也能用 else**

### 2. Python 函数

#### 任意参数

如果您不知道将传递给您的函数多少个参数，请在函数定义的参数名称前添加 *。

这样，函数将接收一个参数元组，并可以相应地访问各项：

```python
def my_function(*kids):
  print("The youngest child is " + kids[2])

my_function("Phoebe", "Jennifer", "Rory")
```

### 3. Python Lambda

lambda 函数是一种小的匿名函数。

lambda 函数可接受任意数量的参数，但只能有一个表达式。

语法：

```python
lambda arguments : expression
```

```python
x = lambda a : a + 10
print(x(5))
```

#### lambda 函数

```python
def myfunc(n):
  return lambda a : a * n

mydoubler = myfunc(2)
mytripler = myfunc(3)

print(mydoubler(11)) 
print(mytripler(11))
```