# # 数据准备
# info = c(1, 2, 4, 8)
# 
# # 命名
# names = c("Google", "Runoob", "Taobao", "Weibo")
# 
# # 涂色（可选）
# cols = c("#ED1C24","#22B14C","#FFC90E","#3f48CC")
# 
# # 绘图
# pie(info, labels=names, col=cols)

# 载入 plotrix
library(plotrix)
# 数据准备
info = c(1, 2, 4, 8)

# 命名
names = c("Google", "Runoob", "Taobao", "Weibo")

# 涂色（可选）
cols = c("#ED1C24","#22B14C","#FFC90E","#3f48CC")

# 设置文件名，输出为 png
# png(file = "3d_pie_chart.png")

# 绘制 3D 图，family 要设置你系统支持的中文字体库
pie3D(info,labels = names,explode = 0.1, main = "3D 图",family = "STHeitiTC-Light")