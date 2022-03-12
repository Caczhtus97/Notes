# 类似于 pandas 二维表

table = data.frame(
  姓名 = c("张三", "李四"),
  工号 = c("001","002"),
  月薪 = c(1000, 2000)
  
)
print(table) # 查看 table 数据

table = data.frame(
  姓名 = c("张三", "李四"),
  工号 = c("001","002"),
  月薪 = c(1000, 2000)
  
)
# 显示概要
print(summary(table))  
print(summary(table))  

table = data.frame(
  姓名 = c("张三", "李四","王五"),
  工号 = c("001","002","003"),
  月薪 = c(1000, 2000,3000)
)
print(table)
# 提取前面两行
print("---输出前面两行----")
result <- table[1:2,]
print(result)