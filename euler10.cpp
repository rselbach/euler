#include <iostream>
#include <cmath>
#include <boost/dynamic_bitset.hpp>
using namespace std;

unsigned long long prime_sum(int limit)
{
	long sieve_size = ceil(limit / 2);
	boost::dynamic_bitset<> sieve(sieve_size);
	unsigned long long sum = 2;

	sieve.flip(); 

	for (unsigned int i = 1; i < sieve_size; i ++) {
		unsigned int n = (i * 2) + 1;
		if (!sieve[i]) 
			continue;
		else
			for (unsigned int j = 3 * n; j < limit; j += n) 
				if (j % 2) sieve[(j - 1) / 2] = 0;
	}

	for (unsigned int i = 1; i < sieve_size; i++)
		if (sieve[i])
			sum += (i * 2) + 1;

	return sum;
}


int main(void)
{
	cout << prime_sum(2000000) << endl;
	return 0;
}
