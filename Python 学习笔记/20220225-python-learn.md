# Python 学习笔记

## Python NumPy 基础

### 1. 数组创建

NumPy 用于处理数组。 NumPy 中的数组对象称为 ndarray。

我们可以使用 array() 函数创建一个 NumPy ndarray 对象。

```python
import numpy as np 

arr = np.array([1, 2, 3, 4, 5])

print(arr)

print(type(arr))
```


要创建 ndarray，我们可以将列表、元组或任何类似数组的对象传递给 array() 方法，然后它将被转换为 ndarray：

```python
import numpy as np 

arr = np.array((1, 2, 3, 4, 5))

print(arr)
```

#### 2-D 数组

其元素为 1-D 数组的数组，称为 2-D 数组。

它们通常用于表示矩阵或二阶张量。

NumPy 有一个专门用于矩阵运算的完整子模块 `numpy.mat`。

```python
import numpy as np

arr = np.array([[1, 2, 3], [4, 5, 6]])

print(arr)
```

#### 高维数组

NumPy 数组提供了 `ndim` 属性，该属性返回一个整数，该整数会告诉我们数组有多少维。

数组可以拥有任意数量的维。

在创建数组时，可以使用 `ndmin` 参数定义维数。

```python
import numpy as np

arr = np.array([1, 2, 3, 4], ndmin=5)

print(arr)
print('number of dimensions :', arr.ndim)
```
>在此数组中，最里面的维度（第 5 个 dim）有 4 个元素，第 4 个 dim 有 1 个元素作为向量，第 3 个 dim 具有 1 个元素是与向量的矩阵，第 2 个 dim 有 1 个元素是 3D 数组，而第 1 个 dim 有 1 个元素，该元素是 4D 数组。

### 2. 数组索引

和列表中访问数组类似，只不过在访问多维数组时按逗号间隔区分

- 列表访问： `arr[i][j]...`
- numPy访问： `arr[i, j, ...]`

```python
import numpy as np

arr = np.array([[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]])

print(arr[0, 1, 2])
```

### 3. 数组裁剪

python 中裁切的意思是将元素从一个给定的索引带到另一个给定的索引。

我们像这样传递切片而不是索引：[start：end]。

我们还可以定义步长，如下所示：[start：end：step]。

如果我们不传递 start，则将其视为 0。

如果我们不传递 end，则视为该维度内数组的长度。

如果我们不传递 step，则视为 1。

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5, 6, 7])

print(arr[1:5])
```

裁切数组中索引 4 到结尾的元素：

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5, 6, 7])

print(arr[4:])
```
多维数组
```python
import numpy as np

arr = np.array([[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]])

print(arr[0:2, 1:4])
```