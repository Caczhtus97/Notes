qnorm(.5)
## [1] 0
qnorm(.96)
## [1] 1.750686
qnorm(.99)
## [1] 2.326348
pnorm(qnorm(0))
## [1] 0
qnorm(pnorm(0))
## [1] 0
# This is for getting two graphs next to each other
oldpar <- par()
par(mfrow=c(1,2))

# Let's make a vector of quantiles: from 0 to 1 by increments of .05
quantiles <- seq(0, 1, by = .05)
quantiles
##  [1] 0.00 0.05 0.10 0.15 0.20 0.25 0.30 0.35 0.40 0.45 0.50 0.55
## [13] 0.60 0.65 0.70 0.75 0.80 0.85 0.90 0.95 1.00
qvalues <- qnorm(quantiles)
qvalues
##  [1]       -Inf -1.6448536 -1.2815516 -1.0364334 -0.8416212
##  [6] -0.6744898 -0.5244005 -0.3853205 -0.2533471 -0.1256613
## [11]  0.0000000  0.1256613  0.2533471  0.3853205  0.5244005
## [16]  0.6744898  0.8416212  1.0364334  1.2815516  1.6448536
## [21]        Inf
plot(qvalues,
     type = "l", # We want a line graph
     xaxt = "n", # No x-axis
     xlab="Probability Density",
     ylab="Z-scores")

# Same pnorm plot from before
plot(pvalues, # Plot where y = values and x = index of the value in the vector
     xaxt = "n", # Don't label the x-axis
     type = "l", # Make it a line plot
     main = "cdf of the Standard Normal",
     xlab= "Quantiles",
     ylab="Probability Density") 

# These commands label the x-axis
axis(1, at=which(pvalues == pnorm(-2)), labels=round(pnorm(-2), 2))
axis(1, at=which(pvalues == pnorm(-1)), labels=round(pnorm(-1), 2))
axis(1, at=which(pvalues == pnorm(0)), labels=c(.5))
axis(1, at=which(pvalues == pnorm(1)), labels=round(pnorm(1), 2))
axis(1, at=which(pvalues == pnorm(2)), labels=round(pnorm(2), 2))