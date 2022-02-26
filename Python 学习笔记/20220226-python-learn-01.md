# Python 学习笔记

## Python NumPy 基础

### 1. 数据类型

NumPy 有一些额外的数据类型，并通过一个字符引用数据类型，例如 i 代表整数，u 代表无符号整数等。

以下是 NumPy 中所有数据类型的列表以及用于表示它们的字符。

- i - 整数
- b - 布尔
- u - 无符号整数
- f - 浮点
- c - 复合浮点数
- m - timedelta
- M - datetime
- O - 对象
- S - 字符串
- U - unicode 字符串
- V - 固定的其他类型的内存块 ( void )

#### 检查数组的数据类型

NumPy 数组对象有一个名为 `dtype` 的属性，该属性返回数组的数据类型：

```python
import numpy as np

arr = np.array([1, 2, 3, 4])

print(arr.dtype)
```

#### 用已定义的数据类型创建数组

我们使用 array() 函数来创建数组，该函数可以使用可选参数：dtype，它允许我们定义数组元素的预期数据类型：

创建数据类型为 4 字节整数的数组：

```python
import numpy as np

arr = np.array([1, 2, 3, 4], dtype='i4')

print(arr)
print(arr.dtype)
```

**如果给出了不能强制转换元素的类型，则 NumPy 将引发 ValueError。**

ValueError：在 Python 中，如果传递给函数的参数的类型是非预期或错误的，则会引发 ValueError。

```python
import numpy as np

arr = np.array(['a', '2', '3'], dtype='i')
```

#### 转换已有数组的数据类型

更改现有数组的数据类型的最佳方法，是使用 astype() 方法复制该数组。

astype() 函数创建数组的副本，并允许您将数据类型指定为参数。

数据类型可以使用字符串指定，例如 'f' 表示浮点数，'i' 表示整数等。或者您也可以直接使用数据类型，例如 float 表示浮点数，int 表示整数。

```python
import numpy as np

arr = np.array([1.1, 2.1, 3.1])

newarr = arr.astype('i')

print(newarr)
print(newarr.dtype)
```

### 2. 副本和视图

#### 区别

副本和数组视图之间的主要区别在于副本是一个新数组，而这个视图只是原始数组的视图。

副本拥有数据，对副本所做的任何更改都不会影响原始数组，对原始数组所做的任何更改也不会影响副本。

视图不拥有数据，对视图所做的任何更改都会影响原始数组，而对原始数组所做的任何更改都会影响视图。

副本：

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5])
x = arr.copy()
arr[0] = 61

print(arr) 
print(x)
```

视图：

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5])
x = arr.view()
arr[0] = 61

print(arr) 
print(x)
```

#### 检查数组是否拥有数据

如上所述，副本拥有数据，而视图不拥有数据，但是我们如何检查呢？

每个 NumPy 数组都有一个属性 base，如果该数组拥有数据，则这个 base 属性返回 None。

否则，base 属性将引用原始对象。

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5])

x = arr.copy()
y = arr.view()

print(x.base)
print(y.base)
```

### 3. 数组的形状

NumPy 数组有一个名为 shape 的属性，该属性返回一个元组，每个索引具有相应元素的数量。

```python
import numpy as np

arr = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])

print(arr.shape)
```

**注意，数组不同于列表， 如果同维的对象是个四大集合之一，大小需要一样。举个例子，上述代码中，第二纬的元素必须都是 4 纬列表，不能一个是 4 纬另一个是 3 纬。**

### 4. 数组重塑

重塑意味着更改数组的形状。

数组的形状是每个维中元素的数量。

通过重塑，我们可以添加或删除维度或更改每个维度中的元素数量。

#### 从 1-D 重塑为 2-D

实例

将以下具有 12 个元素的 1-D 数组转换为 2-D 数组。

最外面的维度将有 4 个数组，每个数组包含 3 个元素：

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])

newarr = arr.reshape(4, 3)

print(newarr)
```

#### 从 1-D 重塑为 3-D

实例

将以下具有 12 个元素的 1-D 数组转换为 3-D 数组。

最外面的维度将具有 2 个数组，其中包含 3 个数组，每个数组包含 2 个元素：

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])

newarr = arr.reshape(2, 3, 2)

print(newarr)
```

#### 返回的是视图

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5, 6, 7, 8])

print(arr.reshape(2, 4).base)
```

#### 未知的维

您可以使用一个“未知”维度。

这意味着您不必在 reshape 方法中为维度之一指定确切的数字。

传递 -1 作为值，NumPy 将为您计算该数字。

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5, 6, 7, 8])

newarr = arr.reshape(2, 2, -1)

print(newarr)
```

**注意：不能将 `-1` 传递给一个以上的维度**

#### 展平数组

展平数组（Flattening the arrays）是指将多维数组转换为 1D 数组。

我们可以使用 `reshape(-1)` 来做到这一点。

#### 其他

有很多功能可以更改 numpy flatten、ravel 中数组形状，还可以重新排列元素 rot90、flip、fliplr、flipud 等。这些功能属于 numpy 的中级至高级部分。

### 5. 数组迭代

使用 `for` 迭代数组中的内容

```python
import numpy as np

arr = np.array([[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]])

for x in arr:
  for y in x:
    for z in y:
      print(z)
```

#### 使用 nditer() 迭代数组

函数 nditer() 是一个辅助函数，从非常基本的迭代到非常高级的迭代都可以使用。它解决了我们在迭代中面临的一些基本问题，让我们通过例子进行介绍。

1. 迭代每个标量元素

    ```python
    遍历以下 3-D 数组：

    import numpy as np

    arr = np.array([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])

    for x in np.nditer(arr):
    print(x)
    ```

2. 迭代不同数据类型的数组

    我们可以使用 `op_dtypes` 参数，并传递期望的数据类型，以在迭代时更改元素的数据类型。

    NumPy 不会就地更改元素的数据类型（元素位于数组中），**因此它需要一些其他空间来执行此操作，该额外空间称为 buffer**，为了在 nditer() 中启用它，我们传参 `flags=['buffered']`。

    以字符串形式遍历数组：
    ```python
    import numpy as np

    arr = np.array([1, 2, 3])

    for x in np.nditer(arr, flags=['buffered'], op_dtypes=['S']):
    print(x)
    ```

3. 迭代步长不一样

    ```python
    import numpy as np

    arr = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])

    for x in np.nditer(arr[:, ::2]):
    print(x)
    ```

4. 使用 ndenumerate() 进行枚举迭代

    枚举是指逐一提及事物的序号。

    有时，我们在迭代时需要元素的相应索引，对于这些用例，可以使用 ndenumerate() 方法。

    ```python
    import numpy as np

    arr = np.array([1, 2, 3])

    for idx, x in np.ndenumerate(arr):
    print(idx, x)
    ```
    ```python
    import numpy as np

    arr = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])

    for idx, x in np.ndenumerate(arr):
    print(idx, x)
    ```

### 6. 数组连接

更多例子见: [numpy中的拼接、堆叠、差分](https://www.cnblogs.com/yunshangyue71/p/13584316.html)

连接意味着将两个或多个数组的内容放在单个数组中。

在 SQL 中，我们基于键来连接表，而在 NumPy 中，我们按轴连接数组。

我们传递了一系列要与轴一起连接到 `concatenate()` 函数的数组。如果未显式传递轴，则将其视为 0。(**换句话说，就是默认按第一维元素合并**)

```python
import numpy as np

arr1 = np.array([1, 2, 3])

arr2 = np.array([4, 5, 6])

arr = np.concatenate((arr1, arr2))

print(arr)
```

沿着行 (axis=1) 连接两个 2-D 数组：

```python
import numpy as np

arr1 = np.array([[1, 2], [3, 4]])

arr2 = np.array([[5, 6], [7, 8]])

arr = np.concatenate((arr1, arr2), axis=1)

print(arr)
```

#### 使用堆栈函数连接数组

堆栈与级联相同，唯一的不同是堆栈是沿着新轴完成的。

我们可以沿着第二个轴连接两个一维数组，这将导致它们彼此重叠，即，堆叠（stacking）。

我们传递了一系列要与轴一起连接到 concatenate() 方法的数组。如果未显式传递轴，则将其视为 0。

```python
import numpy as np

arr1 = np.array([1, 2, 3])

arr2 = np.array([4, 5, 6])

arr = np.stack((arr1, arr2), axis=1)

print(arr)
```

参考博客：

[1. numpy堆叠问题](https://blog.csdn.net/qq_39048976/article/details/101313893)

[2. 强推这个博客，深入浅出！](https://blog.csdn.net/Riverhope/article/details/78922006)


```python
import numpy as np
a=[[1,2,3],
   [4,5,6]]
b=[[1,2,3],
   [4,5,6]]
c=[[1,2,3],
   [4,5,6]]
print("a=",a)
print("b=",b)
print("c=",c)

print("增加一维，新维度的下标为0")
d=np.stack((a,b,c),axis=0)
print(d)

print("增加一维，新维度的下标为1")
d=np.stack((a,b,c),axis=1)
print(d)
print("增加一维，新维度的下标为2")
d=np.stack((a,b,c),axis=2)
print(d)

输出：
('a=', [[1, 2, 3], [4, 5, 6]])
('b=', [[1, 2, 3], [4, 5, 6]])
('c=', [[1, 2, 3], [4, 5, 6]])
增加一维，新维度的下标为0
[[[1 2 3]
  [4 5 6]]

 [[1 2 3]
  [4 5 6]]

 [[1 2 3]
  [4 5 6]]]
增加一维，新维度的下标为1
[[[1 2 3]
  [1 2 3]
  [1 2 3]]

 [[4 5 6]
  [4 5 6]
  [4 5 6]]]
增加一维，新维度的下标为2
[[[1 1 1]
  [2 2 2]
  [3 3 3]]

 [[4 4 4]
  [5 5 5]
  [6 6 6]]]
```

#### 沿行堆叠

NumPy 提供了一个辅助函数：hstack() 沿行堆叠。

hstack， horizontal 水平堆叠

hstack水平堆叠要求行必须初始化（行数对齐）

```python
import numpy as np

arr1 = np.array([1, 2, 3])

arr2 = np.array([4, 5, 6])

arr = np.hstack((arr1, arr2))

print(arr)
```

```python
import numpy as np
a=[[1],[2],[3]]
b=[[1],[2],[3]]
c=[[1],[2],[3]]
d=[[1],[2],[3]]
print(np.hstack((a,b,c,d)))

输出：
[[1 1 1 1]
 [2 2 2 2]
 [3 3 3 3]]
```

#### 沿列堆叠

NumPy 提供了一个辅助函数：vstack() 沿列堆叠。

vstack，vertical 垂直堆叠

vstack垂直堆叠要求列必须初始化（列数对齐）

```python
import numpy as np

arr1 = np.array([1, 2, 3])

arr2 = np.array([4, 5, 6])

arr = np.vstack((arr1, arr2))

print(arr)
```

#### 沿高度堆叠（深度）

NumPy 提供了一个辅助函数：dstack() 沿高度堆叠，该高度与深度相同。

```python
import numpy as np

arr1 = np.array([1, 2, 3])

arr2 = np.array([4, 5, 6])

arr = np.dstack((arr1, arr2))

print(arr)
```

### 7. 数组拆分

拆分是连接的反向操作。

连接（Joining）是将多个数组合并为一个，拆分（Spliting）将一个数组拆分为多个。

我们使用 `array_split()` 分割数组，将要分割的数组和分割数传递给它。

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5, 6])

newarr = np.array_split(arr, 4)

print(newarr)
```

**如果数组中的元素少于要求的数量，它将从末尾进行相应调整。**

*我们也有 split() 方法可用，但是当源数组中的元素较少用于拆分时，它将不会调整元素，如上例那样，array_split() 正常工作，但 split() 会失败。*

高维：(沿行把这个 2-D 拆分为三个 2-D 数组。)

```python
import numpy as np

arr = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12], [13, 14, 15], [16, 17, 18]])

newarr = np.array_split(arr, 3, axis=1)

print(newarr)
```

按列拆分：

```python
import numpy as np

arr = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12], [13, 14, 15], [16, 17, 18]])

newarr = np.hsplit(arr, 3)

print(newarr)
```




