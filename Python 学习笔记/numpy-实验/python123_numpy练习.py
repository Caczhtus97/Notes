import numpy as np

# [1 2 3]
# <class 'numpy.ndarray'>
#
# arr = np.array([1, 2, 3])
# print(arr)
# print(type(arr))

##
# 创建的数组为：
#  [[ 1  2  3  4]
#  [ 4  5  6  7]
#  [ 7  8  9 10]]
# 创建的数组维度为： (3, 4)
# 数组类型为： int64
# 数组元素个数为： 12
# 数组每个元素大小为： 8
# #

# arr = np.array([
#     [1, 2, 3, 4],
#     [4, 5, 6, 7],
#     [7, 8, 9, 10]
# ])
# print('创建的数组为：\n {}'.format(arr))
# print('创建的数组维度为： {}'.format(arr.shape))
# print('数组类型为： {}'.format(arr.dtype))
# print('数组元素个数为： {}'.format(arr.size))
# print('数组每个元素大小为： {}'.format(arr.itemsize))

# 使用arange函数创建的数组为：
#  [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9]

# arr = np.arange(0, 1.0, 0.1)
# print('使用arange函数创建的数组为：\n {}'.format(arr))

# 使用linspace函数创建的数组为： [0. 0.125 0.25 0.375 0.5 0.625 0.75 0.875 1. ]

# arr = np.linspace(0, 1, 9)
# print('使用linspace函数创建的数组为： {}'.format(arr))

# 使用logspace函数创建的数组为： [  1.           1.27427499   1.62377674   2.06913808   2.6366509
#    3.35981829   4.2813324    5.45559478   6.95192796   8.8586679
#   11.28837892  14.38449888  18.32980711  23.35721469  29.76351442
#   37.92690191  48.32930239  61.58482111  78.47599704 100.        ]

# np.set_printoptions(suppress=True)
# arr = np.logspace(0, 2, 20, base=10)
# print('使用logspace函数创建的数组为： {}'.format(arr))

# arr = np.zeros((2, 3), dtype='float')
# print('使用zeros函数创建的数组为： {}'.format(arr))

# arr = np.eye(3, 3, dtype='float')
# print('使用eye函数创建的数组为： {}'.format(arr))

# arr = np.diag([1, 2, 3, 4])
# print('使用diag函数创建的数组为： {}'.format(arr))

# arr = np.ones((5, 3), dtype='float')
# print('使用ones函数创建的数组为： {}'.format(arr))

# arr = np.mat(np.arange(1, 10).reshape((3, 3)))
# print('创建的矩阵为： {}'.format(arr))

# arr = np.matrix(np.arange(1, 10).reshape((3, 3)))
# print('创建的矩阵为： {}'.format(arr))

# arr1 = np.eye(3)
# arr2 = 3*arr1
# print('创建的矩阵为：',np.bmat([[arr1,arr2],[arr1,arr2]]))

# 花萼长度的最大值是：*
# 花萼长度的最小值是：*
# 花萼长度的均值是：*
# 花萼长度的方差是：*
# 花萼长度的标准差是：*

with open('iris_sepal_length.csv',encoding = 'utf-8') as f:
    data = np.loadtxt(f,delimiter = ",")
    dmax = np.around(np.max(data), 2)
    dmin = np.around(np.min(data), 2)
    dmean = np.around(np.mean(data), 2)
    dstd = np.around(np.std(data), 2)
    dvar = np.around(np.var(data), 2)
    res = "花萼长度的最大值是：{}\n花萼长度的最小值是：{}\n花萼长度的均值是：{}\n花萼长度的方差是：{}\n花萼长度的标准差是：{}".format(dmax, dmin, dmean, dvar, dstd)
    print(res)