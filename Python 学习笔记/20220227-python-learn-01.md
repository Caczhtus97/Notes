# Python 学习笔记

## Python NumPy 基础

### 1. 数组排序

numpy.sort(a, axis, kind, order)

参数说明：

- a: 要排序的数组

- axis: 沿着它排序数组的轴，如果没有数组会被展开，沿着最后的轴排序， axis=0 按列排序，axis=1 按行排序

- kind: 默认为'quicksort'（快速排序）

- order: 如果数组包含字段，则是要排序的字段

### 2. 数组过滤

从现有数组中取出一些元素并从中创建新数组称为过滤（filtering）。

在 `NumPy` 中，我们使用布尔索引列表来过滤数组。

布尔索引列表是与数组中的索引相对应的布尔值列表。

如果索引处的值为 True，则该元素包含在过滤后的数组中；如果索引处的值为 False，则该元素将从过滤后的数组中排除。

```python
import numpy as np

arr = np.array([61, 62, 63, 64, 65])

x = [True, False, True, False, True]

newarr = arr[x]

print(newarr)
```

创建过滤器：

```python
import numpy as np

arr = np.array([61, 62, 63, 64, 65])

filter_arr = arr > 62

newarr = arr[filter_arr]

print(filter_arr)
print(newarr)
```


