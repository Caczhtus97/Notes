# 列表包含向量、矩阵、列表
list_data <- list(c("Google","Runoob","Taobao"), matrix(c(1,2,3,4,5,6), nrow = 2),
                  list("runoob",12.3))

# 给列表元素设置名字
names(list_data) <- c("Sites", "Numbers", "Lists")

# 添加元素
list_data[4] <- "新元素"
print(list_data[4])

# 删除元素
list_data[4] <- NULL

# 删除后输出为 NULL
print(list_data[4])

# 更新元素
list_data[3] <- "我替换来第三个元素"
print(list_data[3])

# 创建两个列表
list1 <- list(1,2,3)
list2 <- list("Google","Runoob","Taobao")

# 合并列表
merged.list <- c(list1,list2)

# 显示合并后的列表
print(merged.list)

# 创建列表
list1 <- list(1:5)
print(list1)

list2 <-list(10:14)
print(list2)

# 转换为向量
v1 <- unlist(list1)
v2 <- unlist(list2)

print(v1)
print(v2)

# 两个向量相加
result <- v1+v2
print(result)
