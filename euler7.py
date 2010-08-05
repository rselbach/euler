#!/usr/bin/python

import math
	
def is_prime(n):
	return not (n < 2 or any(n % x == 0 for x in xrange(2, int(n ** 0.5) + 1)))
	
currentMax =0
primes = 1
counter = 3
	
while (primes<10001):
    if (is_prime(counter)):
        currentMax = counter
        primes+=1
    counter+=2
	
print currentMax
