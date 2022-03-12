# # 创建函数
# myfunc = function(n) {
#   if( n==0 || n==1)
#     return(n)
#   return(myfunc(n-1)+myfunc(n-2))
# }
# 
# for( i in 1:15)
#   print(myfunc(i))

# 注意使用递归函数时要用 return 

# x <- c(1,2,3,4)
# names(x) <- c("a","b","c","d")

# 列表包含向量、矩阵、列表
list_data <- list(c("Google","Runoob","Taobao"), matrix(c(1,2,3,4,5,6), nrow = 2),
                  list("runoob",12.3))

print(list_data)

# 给列表元素设置名字
names(list_data) <- c("Sites", "Numbers", "Lists")

# 显示列表
print(list_data)

