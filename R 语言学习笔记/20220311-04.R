# # 创建两个不同长度的向量
# vector1 <- c(5,9,3)
# vector2 <- c(10,11,12,13,14,15)
# column.names <- c("COL1","COL2","COL3")
# row.names <- c("ROW1","ROW2","ROW3")
# matrix.names <- c("Matrix1","Matrix2")
# 
# # 创建数组，并设置各个维度的名称
# result <- array(c(vector1,vector2),dim = c(3,3,2),dimnames = list(row.names,column.names,matrix.names))
# print(result)

# 创建两个不同长度的向量
vector1 <- c(5,9,3)
vector2 <- c(10,11,12,13,14,15)

# 创建数组
array1 <- array(c(vector1,vector2),dim = c(3,3,2))

# 创建两个不同长度的向量
vector3 <- c(9,1,0)
vector4 <- c(6,0,11,3,14,1,2,6,9)
array2 <- array(c(vector1,vector2),dim = c(3,3,2))

# 从数组中创建矩阵
matrix1 <- array1[,,2]
matrix2 <- array2[,,2]

# 矩阵相加
result <- matrix1+matrix2
print(result)