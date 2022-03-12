pnorm(0)
## [1] 0.5
pnorm(2)
## [1] 0.9772499
pnorm(2, mean = 5, sd = 3)
## [1] 0.1586553
pnorm(2, mean = 5, sd = 3, lower.tail = FALSE)
## [1] 0.8413447
1 - pnorm(2, mean = 5, sd = 3, lower.tail = FALSE)
## [1] 0.1586553
pvalues <- pnorm(z_scores)

# Now we'll plot these values
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