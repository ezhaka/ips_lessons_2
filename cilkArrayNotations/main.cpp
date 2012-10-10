#include <cilk/cilk.h>
#include <time.h>
#include <stdio.h>

#define SIZE 10000000

double a[SIZE];
double b[SIZE];
double c[SIZE];

__declspec (vector) double ef_add(double x, double y)
{
	return x + y;
}

void main()
{
	clock_t start = clock();

	int i = 0;

	for (int j = 0; j < SIZE; j++)
	{
		b[j] = j;
	}

	for (int j = 0; j < SIZE; j++)
	{
		c[j] = j;
	}

	

	a[:] = ef_add(b[:], c[:]);

	printf("taken %fs\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	start = clock();

	a[:] = 0; 
	int length = SIZE / 2;
	int stride = 1;
	a[0:length:stride] = ef_add(b[0:length:stride], c[0:length:stride]);

	printf("taken %fs\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	start = clock();

	a[:] = 0;
	cilk_for (int i = 0; i < SIZE; i++)
	{
		a[i] = ef_add(b[i], c[i]);
	}

	printf("taken %fs\n", (double)(clock() - start) / CLOCKS_PER_SEC);

	//getchar();
}