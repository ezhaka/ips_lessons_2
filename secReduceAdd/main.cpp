#include <cilk/cilk.h>
#include <stdio.h>

void main()
{
	int a[] = {1, 2, 3, 4};
	int b[] = {5, 6, 7, 8};
	int c[4];

	c[:] = a[:] + b[:];

	for (int i = 0; i < 4; i++)
	{
		printf("%i ", c[i]);
	}

	printf("\n");

	int sum = __sec_reduce_add(c[:]);

	printf("sum is %i", sum);

	getchar();
}