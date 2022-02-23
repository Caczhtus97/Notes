# Python 学习笔记

## 基础语法

### 1. Python 变量

global 关键字

用于在局部作用域中使用或修改全局变量。

```python
x = "awesome"

def myfunc():
global x
x = "fantastic"

myfunc()

print("Python is " + x)
```

### 2. 内置数据类型

|含义|类型|
|:--:|:--:|
|文本类型：|str|
|数值类型：|int, float, complex|
|序列类型：|list, tuple, range|
|映射类型：|dict|
|集合类型：|set, frozenset|
|布尔类型：|bool|
|二进制类型：|bytes, bytearray, memoryview|

>**获取数据类型**
> 
> 可以使用 type() 函数获取任何对象的数据类型：

### 3. Python 数字

```python
x = 10    # int
y = 6.3  # float
z = 2j   # complex

print(type(x))
print(type(y))
print(type(z))
```

**类型转换**

```python
#convert from int to float:
x = float(10)

#convert from float to int:
y = int(6.3)

#convert from int to complex:
z = complex(x)

print(x)
print(y)
print(z)
```

### 4. Python 字符串

**字符串是数组**

像许多其他流行的编程语言一样，Python 中的字符串是表示 unicode 字符的字节数组。

但是，Python 没有字符数据类型，单个字符就是长度为 1 的字符串。

方括号可用于访问字符串的元素。

- 裁切

    注意：裁切的范围是左闭右开区间
    ```python
    b = "Hello, World!"
    print(b[2:5])
    ```
    python 中还可以使用负的索引，只不过默认的读取顺序是从左到右
    ```python
    b = "Hello, World!"
    print(b[-5:-2])
    ```
- 去除头尾空白

    strip() 方法删除开头和结尾的空白字符
    ```python
    a = " Hello, World! "
    print(a.strip()) # returns "Hello, World!"
    ```

- 返回大小写字母

    upper() 和 lower()

- 替换字符串

    replace() 用另一段字符串来替换字符串：
    ```python
    a = "Hello, World!"
    print(a.replace("World", "Kitty"))
    ```

- 正则分割字符串

    split() 方法在找到分隔符的实例时将字符串拆分为子字符串：
    ```python
    a = "Hello, World!"
    print(a.split(",")) # returns ['Hello', ' World!']
    ```

- 检查子字符串是否存在

    如需检查字符串中是否存在特定短语或字符，我们可以使用 in 或 not in 关键字。

- 拼接不同类型为一个字符串

    format() 方法接受传递的参数，格式化它们，并将它们放在占位符 {} 所在的字符串中：

    ```python
    age = 63
    txt = "My name is Bill, and I am {}"
    print(txt.format(age))
    ```

    format() 方法接受不限数量的参数，并放在各自的占位符中：

    ```python
    quantity = 3
    itemno = 567
    price = 49.95
    myorder = "I want {} pieces of item {} for {} dollars."
    print(myorder.format(quantity, itemno, price))
    ```

    您可以使用索引号 {0} 来确保参数被放在正确的占位符中：

    ```python
    quantity = 3
    itemno = 567
    price = 49.95
    myorder = "I want to pay {2} dollars for {0} pieces of item {1}."
    print(myorder.format(quantity, itemno, price))
    ```

|方法|含义|
|:--:|:--:|
|capitalize()|把首字符转换为大写。|
|casefold()|把字符串转换为小写。|
|center()|返回居中的字符串。|
|count()|返回指定值在字符串中出现的次数。|
|encode()|返回字符串的编码版本。|
|endswith()|如果字符串以指定值结尾，则返回 true。|
|expandtabs()|设置字符串的 tab 尺寸。|
|find()|在字符串中搜索指定的值并返回它被找到的位置。|
|format()|格式化字符串中的指定值。|
|format_map()|格式化字符串中的指定值。|
|index()|在字符串中搜索指定的值并返回它被找到的位置。|
|isalnum()|如果字符串中的所有字符都是字母数字，则返回 True。|
|isalpha()|如果字符串中的所有字符都在字母表中，则返回 True。|
|isdecimal()|如果字符串中的所有字符都是小数，则返回 True。|
|isdigit()|如果字符串中的所有字符都是数字，则返回 True。|
|isidentifier()|如果字符串是标识符，则返回 True。|
|islower()|如果字符串中的所有字符都是小写，则返回 True。|
|isnumeric()|如果字符串中的所有字符都是数，则返回 True。|
|isprintable()|如果字符串中的所有字符都是可打印的，则返回 True。|
|isspace()|如果字符串中的所有字符都是空白字符，则返回 True。|
|istitle()|如果字符串遵循标题规则，则返回 True。|
|isupper()|如果字符串中的所有字符都是大写，则返回 True。|
|join()|把可迭代对象的元素连接到字符串的末尾。|
|ljust()|返回字符串的左对齐版本。|
|lower()|把字符串转换为小写。|
|lstrip()|返回字符串的左修剪版本。|
|maketrans()|返回在转换中使用的转换表。|
|partition()|返回元组，其中的字符串被分为三部分。|
|replace()|返回字符串，其中指定的值被替换为指定的值。|
|rfind()|在字符串中搜索指定的值，并返回它被找到的最后位置。|
|rindex()|在字符串中搜索指定的值，并返回它被找到的最后位置。|
|rjust()|返回字符串的右对齐版本。|
|rpartition()|返回元组，其中字符串分为三部分。|
|rsplit()|在指定的分隔符处拆分字符串，并返回列表。|
|rstrip()|返回字符串的右边修剪版本。|
|split()|在指定的分隔符处拆分字符串，并返回列表。|
|splitlines()|在换行符处拆分字符串并返回列表。|
|startswith()|如果以指定值开头的字符串，则返回 true。|
|strip()|返回字符串的剪裁版本。|
|swapcase()|切换大小写，小写成为大写，反之亦然。|
|title()|把每个单词的首字符转换为大写。|
|translate()|返回被转换的字符串。|
|upper()|把字符串转换为大写。|
|zfill()|在字符串的开头填充指定数量的 0 值。|



