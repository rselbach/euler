#!/usr/bin/python

from sys import exit

def is_triplet(a, b, c):
	return (a ** 2 + b ** 2 == c ** 2)

for a in range(1, 1000):
	for b in range(a + 1, (1000 - a) / 2):
		c = 1000 - a - b
		if is_triplet(a, b, c):
			print "%d * %d * %d = %d" %(a, b, c, a * b * c)

