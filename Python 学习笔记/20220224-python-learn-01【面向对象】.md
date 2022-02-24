# Python 学习笔记

## 基础语法

### 1. Python 类、对象

#### 创建类

如需创建类，请使用 class 关键字：

```python
class MyClass:
  x = 5
```

#### 构造函数

**关键字**: `__init__`

**注释**：每次使用类创建新对象时，都会自动调用 `__init__()` 函数。

注意：使用这个方法时要加上一个 self，self 参数是对类的当前实例的引用，用于访问属于该类的变量。它不必被命名为 self，您可以随意调用它，但它必须是类中任意函数的首个参数。

```python
class Person:
  def __init__(mysillyobject, name, age):
    mysillyobject.name = name
    mysillyobject.age = age

  def myfunc(abc):
    print("Hello my name is " + abc.name)

p1 = Person("Bill", 63)
p1.myfunc()
```

#### 删除对象属性

可以使用 del 关键字删除对象的属性而不删除对象

#### 内置类属性

- `__dict__` : 类的属性（包含一个字典，由类的数据属性组成）
- `__doc__` :类的文档字符串
- `__name__`: 类名
- `__module__`: 类定义所在的模块（类的全名是'__main__.className'，如果类位于一个导入模块mymod中，那么className.__module__ 等于 mymod）
- `__bases__` : 类的所有父类构成元素（包含了一个由所有父类组成的元组）

```python
class Employee:
   '所有员工的基类'
   empCount = 0
 
   def __init__(self, name, salary):
      self.name = name
      self.salary = salary
      Employee.empCount += 1
   
   def displayCount(self):
     print "Total Employee %d" % Employee.empCount
 
   def displayEmployee(self):
      print "Name : ", self.name,  ", Salary: ", self.salary
 
print "Employee.__doc__:", Employee.__doc__
print "Employee.__name__:", Employee.__name__
print "Employee.__module__:", Employee.__module__
print "Employee.__bases__:", Employee.__bases__
print "Employee.__dict__:", Employee.__dict__
```

### 2. Python 继承

语法：

```python
class 派生类名(基类名)
    ...
```

多继承:

```python
class SubClassName (ParentClass1[, ParentClass2, ...]):
    ...
```

```python
class A:        # 定义类 A
.....

class B:         # 定义类 B
.....

class C(A, B):   # 继承类 A 和 B
.....
```

>在python中继承中的一些特点：
>
>1、如果在子类中需要父类的构造方法就需要显式的调用父类的构造方法，或者不重写父类的构造方法。详细说明可查看： python 子类继承父类构造函数说明。
>
>2、在调用基类的方法时，需要加上基类的类名前缀，且需要带上 self 参数变量。区别在于类中调用普通函数时并不需要带上 self 参数
>
>3、Python 总是首先查找对应类型的方法，如果它不能在派生类中找到对应的方法，它才开始到基类中逐个查找。（先在本类中查找调用的方法，找不到才去基类中找）。
>
>如果在继承元组中列了一个以上的类，那么它就被称作"多重继承" 。

例子：

```python
class Person:
  def __init__(self, fname, lname):
    self.firstname = fname
    self.lastname = lname

  def printname(self):
    print(self.firstname, self.lastname)

# 使用 Person 来创建对象，然后执行 printname 方法：

x = Person("Bill", "Gates")
x.printname()

class Student(Person):
  pass

x = Student("Elon", "Musk")
x.printname()
```

>你可以使用issubclass()或者isinstance()方法来检测。
>
>- issubclass() - 布尔函数判断一个类是另一个类的子类或者子孙类，语法：issubclass(son, father)
>- isinstance(obj, Class) 布尔函数如果obj是Class类的实例对象或者是一个Class子类的实例对象则返回true。

如果子类添加了 `__init__` 方法后，会覆盖父类的构造方法，经测试，即使参数列表不一样，也不会发生重载，而是直接覆盖。

子类如果需要调用父类的构造可以参考以下例子：

```python
class Student(Person):
  def __init__(self, fname, lname):
    Person.__init__(self, fname, lname)
```

#### 使用 `super()` 函数

Python 还有一个 super() 函数，它会使子类从其父继承所有方法和属性：

```python
class Student(Person):
  def __init__(self, fname, lname):
    super().__init__(fname, lname)
```

通过使用 `super()` 函数，您不必使用父元素的名称，它将自动从其父元素继承方法和属性。

#### 添加属性

```python
class Student(Person):
  def __init__(self, fname, lname):
    super().__init__(fname, lname)
    self.graduationyear = 2019
```

#### 添加方法

```python
class Student(Person):
  def __init__(self, fname, lname, year):
    super().__init__(fname, lname)
    self.graduationyear = year

  def welcome(self):
    print("Welcome", self.firstname, self.lastname, "to the class of", self.graduationyear)
```

**如果您在子类中添加一个与父类中的函数同名的方法，则将覆盖父方法的继承。**

#### 基础重载方法

1. `__init__ ( self [,args...] )`
  构造函数
  简单的调用方法: obj = className(args)
2. `__del__( self )`
  析构方法, 删除一个对象
  简单的调用方法 : del obj
3. `__repr__( self )`
  转化为供解释器读取的形式
  简单的调用方法 : repr(obj)
4. `__str__( self )`
  用于将值转化为适于人阅读的形式
  简单的调用方法 : str(obj)
5. `__cmp__ ( self, x )`
  对象比较
  简单的调用方法 : cmp(obj, x)

#### 运算符重载

1. [链接一](https://www.cnblogs.com/hotbaby/p/4913363.html)
2. [链接二](https://blog.csdn.net/zhangshuaijun123/article/details/82149056)

#### 单下划线、双下划线、头尾双下划线说明：
1. `__foo__`: 定义的是特殊方法，一般是系统定义名字 ，类似 __init__() 之类的。

2. `_foo`: 以单下划线开头的表示的是 protected 类型的变量，即保护类型只能允许其本身与子类进行访问，不能用于 from module import *

3. `__foo`: 双下划线的表示的是私有类型(private)的变量, 只能是允许这个类本身进行访问了。

