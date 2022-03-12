set.seed(10 - 1 - 2015)
rnorm(5)
## [1] -0.7197035 -1.4442137 -1.0120381  1.4577066 -0.1212466
set.seed(10 - 1 - 2015)
rnorm(5)
## [1] -0.7197035 -1.4442137 -1.0120381  1.4577066 -0.1212466
n10 <- rnorm(10, mean = 70, sd = 5)
n100 <- rnorm(100, mean = 70, sd = 5)
n10000 <- rnorm(10000, mean = 70, sd = 5)
n10
##  [1] 54.70832 72.89000 70.27049 69.16508 72.97937 67.91004
##  [7] 67.77183 72.29231 74.33411 63.57151
# This is for getting two graphs next to each other
oldpar <- par()
par(mfrow = c(1, 3))

# The breaks argument specifies how many bars are in the
# histogram
hist(n10, breaks = 5)
hist(n100, breaks = 20)
hist(n10000, breaks = 100)