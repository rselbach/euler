#include <iostream>
#include <cmath>

#ifdef USE_BOOST
#include <boost/dynamic_bitset.hpp>
#else
#include <bitset>
#endif

using namespace std;

unsigned long long prime_sum(int limit)
{
	if (limit < 2) return 0;

	long sieve_size = ceil(limit / 2);
#ifdef USE_BOOST
	boost::dynamic_bitset<> sieve(sieve_size);
#else
	bitset<1000000> sieve;
#endif
	unsigned long long sum = 2;

	sieve.flip(); 

	for (unsigned int i = 0; i < floor(sqrt(limit) / 2); i++) {
		if (!sieve[i]) 
			continue;
		for (int j = (i * (i + 3) * 2) + 3; j < sieve_size; j += (i * 2) + 3)
			sieve[j] = 0;
	}

	for (unsigned int i = 0; i < sieve_size; i++)
		if (sieve[i])
			sum += (i * 2) + 3;

	return sum;
}


int main(void)
{
	cout << prime_sum(2000000) << endl;
	return 0;
}
