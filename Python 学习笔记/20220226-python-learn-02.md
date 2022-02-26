# Python 学习笔记

## Python NumPy 基础

### 1. 数组搜索

您可以在数组中搜索（检索）某个值，然后返回获得匹配的索引。

要搜索数组，请使用 where() 方法。

```python
import numpy as np

arr = np.array([1, 2, 3, 4, 5, 4, 4])

x = np.where(arr == 4)

print(x)
```

上例会返回一个元组：(array([3, 5, 6],)

意思就是值 4 出现在索引 3、5 和 6。

#### 搜索排序

有一个名为 `searchsorted()` 的方法，该方法在数组中执行二进制搜索，并返回将在其中插入指定值以维持搜索顺序的索引。

ps: 有点像二分搜索，就是做找最长上升子序列中，二分中的那个操作。

```python
import numpy as np

arr = np.array([6, 7, 8, 9])

x = np.searchsorted(arr, 7, side='right')

print(x)
```

```python
import numpy as np

arr = np.array([1, 3, 5, 7])

x = np.searchsorted(arr, [2, 4, 6])

print(x)
```

### 2. 数组排序

排序是指将元素按有序顺序排列。

有序序列是拥有与元素相对应的顺序的任何序列，例如数字或字母、升序或降序。

NumPy ndarray 对象有一个名为 sort() 的函数，该函数将对指定的数组进行排序。

```python
import numpy as np

arr = np.array([3, 2, 0, 1])

print(np.sort(arr))
```

**此方法返回数组的副本，而原始数组保持不变。**



