#!/usr/bin/python

import math

top_number = 600851475143

def is_divisor(divisor):
	return top_number % divisor == 0

def is_prime(divided):
	divisor = 3
	sqrt_divided = math.sqrt(divided)
	if divided == 1:
		return true
	while divisor <= sqrt_divided:
		if divided == divisor:
			return True
		elif divided % divisor == 0:
			return False
		else:
			divisor += 2
	return True

def main():
	count = 3
	go_to = top_number

	first_list =[]
	while count <= go_to:
		if is_divisor(count):
			first_list.append(count)
			go_to = top_number / count
			first_list.append(go_to)

		count += 2

	second_list = map(is_prime, first_list)
	print "%s" % max(zip(second_list, first_list))[-1]

if __name__ == "__main__":
	main()
