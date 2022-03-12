# install.packages("reshape2", repos = "https://mirrors.ustc.edu.cn/CRAN/") 
# install.packages("reshape", repos = "https://mirrors.ustc.edu.cn/CRAN/") 

# # 载入库
# library(MASS)
# library(reshape2)
# library(reshape)
# 
# # 创建数据框
# id<- c(1, 1, 2, 2)
# time <- c(1, 2, 1, 2)
# x1 <- c(5, 3, 6, 2)
# x2 <- c(6, 5, 1, 4)
# mydata <- data.frame(id, time, x1, x2)
# 
# # 原始数据框
# cat("原始数据框:\n")
# print(mydata)
# # 整合
# md <- melt(mydata, id = c("id","time"))
# 
# cat("\n整合后:\n")
# print(md)

# 载入库
library(MASS)
library(reshape2)
library(reshape)

# 创建数据框
id<- c(1, 1, 2, 2)
time <- c(1, 2, 1, 2)
x1 <- c(5, 3, 6, 2)
x2 <- c(6, 5, 1, 4)
mydata <- data.frame(id, time, x1, x2)
# 整合
md <- melt(mydata, id = c("id","time"))
print(md)
# Print recasted dataset using cast() function
cast.data <- cast(md, id~variable, mean)

print(cast.data)

cat("\n")
time.cast <- cast(md, time~variable, mean)
print(time.cast)


cat("\n")
id.time <- cast(md, id~time, mean)
print(id.time)

cat("\n")
id.time.cast <- cast(md, id+time~variable)
print(id.time.cast)

cat("\n")
id.variable.time <- cast(md, id+variable~time)
print(id.variable.time)

cat("\n")
id.variable.time2 <- cast(md, id~variable+time)
print(id.variable.time2)


library(png)
imgpng <- readPNG("~/coding/R/语法学习/tmpfile/堆叠拆分.png")
r <- nrow(imgpng)/ncol(imgpng) 
plot(c(0,1),c(0,r),type = "n",xlab = "",ylab = "",asp=1)
rasterImage(imgpng,0,0,1,r)

