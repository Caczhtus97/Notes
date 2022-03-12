table = data.frame(
  姓名 = c("张三", "李四","王五"),
  工号 = c("001","002","003"),
  月薪 = c(1000, 2000,3000)
)
newtable = data.frame(
  姓名 = c("小明", "小白"),
  工号 = c("101","102"),
  月薪 = c(5000, 7000)
)
# 合并两个数据框
result <- rbind(table,newtable)
print(result)