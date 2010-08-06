#!/usr/bin/python

import psyco
psyco.full()

max_primes = 2000000
numbers = [0] * max_primes

def is_prime(n):
	if n <= 2:
		return True
	if numbers[n] == 1:
		return False
	c = 2
	m = 0
	while True:
		m = n * c
		if m < max_primes: 
			numbers[m] = 1
		else:
			break
		c+= 1

	#if any(n % x == 0 for x in xrange(2, int(n ** 0.5) + 1)):
	i = 2
	while i < int(n** 0.5 + 1):
		if n % i == 0:
			return False
		i += 1

	numbers[n] = 1	
	return True

def sum_primes():
	soma = 0
	for i in range (2, max_primes):
		if is_prime(i):
			soma += i
	return soma

print sum_primes()
