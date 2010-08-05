#!/usr/bin/python

sqr_sum = 0
num_sum = 0
for i in range(1,100 + 1):
	num_sum += i
	sqr_sum += i**2

num_sum = num_sum**2
print sqr_sum - num_sum

