# Python 学习笔记

## 基础语法

### 1. Python 布尔

用 bool 类进行封装操作，可以把非空或者非零的封装成布尔类型

**函数也可以返回布尔类型**：

```python
# 检查变量是否为整数类型
x = 200
print(isinstance(x, int))
```

### 2. Python 运算符

运算符用于对变量和值执行操作。

Python 在以下组中划分运算符：

- 算术运算符
- 赋值运算符
- 比较运算符
- 逻辑运算符
- 身份运算符
- 成员运算符
- 位运算符

#### 1. 整除和非整除

整除： `//`

除法： `/`

#### 2. 幂运算

`x ** y` 等价于 $x^y$

#### 3. 身份运算符

用于判断内存对象是否为同一个，关键字 `is` 或 `is not`

```python
x is y # 如果两个变量是同一个对象，则返回 true
```

#### 4. 成员运算符

用于测试**序列**是否在对象中出现，关键字 `in` 或 `not in`

```python
x in y
```

### 3. Python 集合框架

Python 编程语言中有四种集合数据类型：

- 列表（List）是一种有序和可更改的集合。允许重复的成员。
- 元组（Tuple）是一种有序且不可更改的集合。允许重复的成员。
- 集合（Set）是一个无序和无索引的集合。没有重复的成员。
- 词典（Dictionary）是一个无序，可变和有索引的集合。没有重复的成员。

#### 1. Python 列表（数组）

列表是一个有序且可更改的集合。在 Python 中，列表用**方括号**编写。

```python
thislist = ["apple", "banana", "cherry"]
print(thislist)
```
**注意点：**

1. 数组中的元素类型不必相同，这点应该是和编程语言协变、逆变、不变特性有关
2. 列表支持随机访问，如果要使用物理结构不连续的集合改用 linked list

|方法|含义|
|:--:|:--:|
|append()|在列表的末尾添加一个元素|
|clear()|删除列表中的所有元素|
|copy()|返回列表的副本|
|count()|返回具有指定值的元素数量。|
|extend()|将列表元素（或任何可迭代的元素）添加到当前列表的末尾|
|index()|返回具有指定值的第一个元素的索引|
|insert()|在指定位置添加元素|
|pop()|删除指定位置的元素|
|remove()|删除具有指定值的项目|
|reverse()|颠倒列表的顺序|
|sort()|对列表进行排序|

**排序**

|选项|含义|
|:--:|:--:|
|reverse|可选。reverse=True 将对列表进行降序排序。默认是 reverse=False。|
|key|可选。指定排序标准的函数。|

```python
# 返回值的长度的函数：
def myFunc(e):
  return len(e)

cars = ['Porsche', 'Audi', 'BMW', 'Volvo']

cars.sort(reverse=True, key=myFunc)

print(cars)
```

#### 2. Python 元组

元组是**有序且不可更改**的集合。在 Python 中，元组是用**圆括号**编写的。

```python
thistuple = ("apple", "banana", "cherry")
print(thistuple)
```

在使用元组时，假设需要修改某一项的值内容，可以先把元组利用列表的构造方法转列表，改完后再转元组

**注意：元组不但元素不可改，本真大小也不可改，是一个只读的数据结构**

如需创建仅包含一个项目的元组，您必须在该项目后添加一个逗号，否则 Python 无法将变量识别为元组。

```python
#是元组
thistuple = ("apple",)
print(type(thistuple))

#不是元组
thistuple = ("apple")
print(type(thistuple))

#是元组
thistuple = tuple("apple")
print(type(thistuple))
```

**注意：**
1. 元组可以合并！利用 `+` 运算符即可
2. 元组也可以利用 `tuple` 类进行构造，注意是两个括号
    ```python
    thistuple = tuple(("apple", "banana", "cherry")) # 请注意双括号
    print(thistuple)
    ```
|方法|含义|
|:--:|:--:|
|count()|返回元组中指定值出现的次数。|
|index()|在元组中搜索指定的值并返回它被找到的位置。|

#### 3. Python 集合（Set）

集合是**无序和无索引**的集合。在 Python 中，集合用**花括号**编写。

```python
thisset = {"apple", "banana", "cherry"}
print(thisset)
```

**注意：区别于 CPP 中的 set 集合，这里的集合是无序的，但他们都拥有元素唯一的性质**

|方法|含义|
|:--:|:--:|
|add()|向集合添加元素。|
|clear()|删除集合中的所有元素。|
|copy()|返回集合的副本。|
|difference()|返回包含两个或更多集合之间差异的集合。|
|difference_update()|删除此集合中也包含在另一个指定集合中的项目。|
|discard()|删除指定项目。|
|intersection()|返回为两个其他集合的交集的集合。|
|intersection_update()|删除此集合中不存在于其他指定集合中的项目。|
|isdisjoint()|返回两个集合是否有交集。|
|issubset()|返回另一个集合是否包含此集合。|
|issuperset()|返回此集合是否包含另一个集合。|
|pop()|从集合中删除一个元素。|
|remove()|删除指定元素。|
|symmetric_difference()|返回具有两组集合的对称差集的集合。|
|symmetric_difference_update()|插入此集合和另一个集合的对称差集。|
|union()|返回包含集合并集的集合。|
|update()|用此集合和其他集合的并集来更新集合。|

#### 4. Python 字典（Dictionary）

字典是一个**无序、可变和有索引**的集合。在 Python 中，字典用**花括号**编写，拥有键和值。

```python
thisdict =	{
  "brand": "Porsche",
  "model": "911",
  "year": 1963
}
print(thisdict)
```

**注意：类似于 CPP 中的 map ， 区别在于 map 中是有序的，而 dict 是无序的，其他均类似**

使用 `item()` 遍历 dict 中的键值对：

```python
for x, y in thisdict.items():
    print(x, y)
```

|方法|含义|
|:--:|:--:|
|clear()|删除字典中的所有元素|
|copy()|返回字典的副本|
|fromkeys()|返回拥有指定键和值的字典|
|get()|返回指定键的值|
|items()|返回包含每个键值对的元组的列表|
|keys()|返回包含字典键的列表|
|pop()|删除拥有指定键的元素|
|popitem()|删除最后插入的键值对|
|setdefault()|返回指定键的值。如果该键不存在，则插入具有指定值的键。|
|update()|使用指定的键值对字典进行更新|
|values()|返回字典中所有值的列表|


