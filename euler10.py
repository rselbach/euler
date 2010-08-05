#!/usr/bin/python

import psyco
psyco.full()

import math

primes = []

def is_prime(n):
	if not (n < 2 or any(n % x == 0 for x in filter(lambda x: x < math.ceil(n ** 2), primes))):
		primes.append(n)
		return True
	return False
	
def doit():
	sum_primes = 0
	n = 1
	while n < 2000000:
	    if (is_prime(n)):
	        sum_primes += n
	    n += 1
	return sum_primes

print doit()

for i in range(2, 30):
	if is_prime(i):
		print i
