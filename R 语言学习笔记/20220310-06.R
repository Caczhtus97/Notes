#R有5种基本类型：character numeric integer logical complex

# x <- "hello world" #赋值
# x <- 1.1
# x <- 1L
# x <- TRUE
# x <- 1+2i
# y = class(x) #类型值
# print(y)

# 按对象类型来分是以下 6 种（后面会详细介绍这几种类型）：
# 
# 向量（vector）
# 列表（list）
# 矩阵（matrix）
# 数组（array）
# 因子（factor)
# 数据框（data.frame)

# a = c(3, 4)
# b = c(5, 0)
# print(a + b)
# 
# x <- vector("character",length = 10)
# print(x)
# x <- 1:4
# x <- c(1,2,3,4)
# print(x)
#
# 注意：R 语言中的"下标"不代表偏移量，而代表第几个，也就是说是从 1 开始的！

# a = c(1, 2, 3, 4, 5)
# print(a[1:4]) # 取出第 1 到 4 项，包含第 1 和第 4 项
# print(a[c(1, 3, 5)]) # 取出第 1, 3, 5 项
# print(a[c(-1, -5)]) # 去掉第 1 和第 5 项

# a = c(1, 3, 5, 2, 4, 6)
# 
# b = sort(a)
# c = order(a)
# cat(b, c, sep = '  ')

# sum	求和
# mean	求平均值
# var	方差
# sd	标准差
# min	最小值
# max	最大值
# range	取值范围（二维向量，最大值和最小值）

# x = seq(1, 9, 5)
# print(x)
# print(sd(x)) # 注意标准差是有偏的标准差
# x1 = 6.25
# x2 = 6.25
# print(sqrt(x1+x2))

# x = seq(0, 1, length.out=7) # 等差数列, length.out --> 区间中的数列个数
# print(x)

# x = rep(0, 5) # 重复 5 次
# print(x)

# NA 代表的是"缺失"，NULL 代表的是"不存在"。
# NA 缺失就像占位符，代表这里没有一个值，但位置存在。
# NULL 代表的就是数据不存在。

# x = length(c(NA, NA, NULL))
# print(x)

# which 函数是十分常见的逻辑型向量处理函数，可以用于筛选我们需要的数据的下标

# a = c(1, 2, 3, 4)
# b = a >= 2
# c = which(b)
# cat(b, c, rep='  ')

# vector = c(10, 40, 78, 64, 53, 62, 69, 70)
# print(vector[which(vector >= 60 & vector < 70)])

