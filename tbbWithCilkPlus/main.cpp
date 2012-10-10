#include <time.h>
#include <stdio.h>

#include <cilk/cilk.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

#include "tbb/scalable_allocator.h"

char * arr[ARRAY_SIZE];

void main()
{
	clock_t start = clock();

	printf("scalable_malloc...\n");

	cilk_for (int i = 0; i < ARRAY_SIZE; i++)
	{
		arr[i] = (char *)scalable_malloc(1);
	}

	cilk_for (int i = 0; i < ARRAY_SIZE; i++)
	{
		scalable_free(arr[i]);
	}

	printf("Time taken: %fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
	printf("malloc...\n");

	start = clock();

	cilk_for (int i = 0; i < ARRAY_SIZE; i++)
	{
		arr[i] = (char *)malloc(1);
	}

	cilk_for (int i = 0; i < ARRAY_SIZE; i++)
	{
		free(arr[i]);
	}


	printf("Time taken: %fs", (double)(clock() - start)/CLOCKS_PER_SEC);

	getchar();
}