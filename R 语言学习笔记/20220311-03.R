# byrow 为 TRUE 元素按行排列
M <- matrix(c(3:14), nrow = 4, byrow = TRUE)
print(M)

# Ebyrow 为 FALSE 元素按列排列
N <- matrix(c(3:14), nrow = 4, byrow = FALSE)
print(N)

# 定义行和列的名称
rownames = c("row1", "row2", "row3", "row4")
colnames = c("col1", "col2", "col3")

P <- matrix(c(3:14), nrow = 4, byrow = TRUE, dimnames = list(rownames, colnames))
print(P)

# 矩阵
x <- matrix(1:6 , nrow = 3,ncol = 2 ) #创建3x2矩阵
dim(x) #查看维度
attributes(x) #查看当前属性

y <- 1:6 #创建2x3矩阵
dim(y) <- c(2,3)

# 矩阵拼接
y1 <- matrix(1:6 , nrow = 3,ncol = 2 )
y2 <- matrix(1:6 , nrow = 3,ncol = 2 )
rbind(y1,y2) # 6x2矩阵
cbind(y1,y2) # 3x4矩阵