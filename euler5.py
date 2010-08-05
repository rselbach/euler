#/usr/bin/python



def gcd(a, b):
	if b== 0: return a
	return gcd(b, a % b)

def lcm(a, b):
	return a * b / gcd(a, b)

if __name__ == "__main__":
	b = 2
	for i in range(3,20):
		b = lcm(b, i)
	print b	
