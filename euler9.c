#include <stdio.h>

int is_triplet(int a, int b, int c)
{
	return ((a * a + b * b) == (c * c));
}

int main(void)
{
	for (int a = 1; a < 1000; a++)
		for (int b = a + 1; b < (1000 - a) / 2; b++) {
			int c = 1000 - a - b;
			if (is_triplet(a, b, c)) {
				printf("%d %d %d = %d\n", a, b, c,
				       a * b * c);
				return 0;
			}
		}
}
