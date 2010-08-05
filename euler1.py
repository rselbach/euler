def sum1toN(n):
   return n * (n + 1) / 2
 
def sumMultiples(limit, a):
   return sum1toN((limit - 1) // a) * a
 
print sumMultiples(10, 3) + sumMultiples(10, 5) - sumMultiples(10, 15)

