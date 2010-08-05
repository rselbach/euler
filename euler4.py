#!/usr/bin/python
 
def int_to_list(number):
  return map(int, str(number))
 
def is_palindrome(number):
  local_list = int_to_list(number)
  return local_list == list(reversed(local_list))

pal = 0 
if __name__ == "__main__":
  for i in range(100,1000):
	for j in range(100,1000):
		if is_palindrome(i * j):
			print "%d * %d = %d"%(i, j, i*j)
			if i * j > pal:
				pal = i * j

  print pal
