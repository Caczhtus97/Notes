# 创建两个不同长度的向量
vector1 <- c(5,9,3)
vector2 <- c(10,11,12,13,14,15)

# 创建数组
new.array <- array(c(vector1,vector2),dim = c(3,3,2))
print(new.array)

# 计算数组中所有矩阵第一行的数字之和
result <- apply(new.array, c(2), sum) # 第n维求和
print(result)