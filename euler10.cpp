#include <iostream>
#include <boost/dynamic_bitset.hpp>
using namespace std;

#define LIMIT 2000000

int main()
{
	boost::dynamic_bitset<> sieve(LIMIT);
	unsigned long long sum = 0;

	sieve.flip();		// Set all bits to 1 
	sieve[0].flip();	// Set 0 and 1 to not prime 
	sieve[1].flip();

	// Check all nos from 2 to 1 million 
	for (unsigned long i = 2; i < LIMIT; ++i) {
		if (!sieve[i])	// If marked not prime 
			continue;	// return to head of loop 
		else
			// Set all multiples as not prime 
			for (unsigned long j = 2 * i; j < LIMIT; j += i)
				sieve[j] = 0;
	}

	for (unsigned long i = 0; i < LIMIT; ++i)
		if (sieve[i]){	// Add all nos with bit set
			sum += i;
		}

	cout << "\nThe sum is : " << sum << endl;

	return 0;
}
