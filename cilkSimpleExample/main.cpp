#include <cilk/cilk.h>
#include <stdio.h>


long fibbonacci(long n)
{
	long x, y;

	if (n < 2) 
	{
		return n;
	}

	//find n - 1 number
	x = cilk_spawn fibbonacci(n - 1);

	y = cilk_spawn fibbonacci(n - 2);

	cilk_sync;

	return (x + y);
}

int main()
{
	long fib = fibbonacci(40);

	printf("Fibonacci 40th: %d", fib);

	getchar();
}