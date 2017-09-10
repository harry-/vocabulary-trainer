#include <stdio.h>

int power(int m, int n);

int main()
{
   printf("%d\n", power(5,2));
}

int power(int base, int exp)
{
	int p = 1;
	for (int i = 0; i < exp; ++i)
	{
		p = p * base;
	}
	return p;
}