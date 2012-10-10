#include "tbb/tbb.h"
#include "tbb/atomic.h"
#include <stdio.h>


using namespace tbb;

void cycle(size_t n)
{
	printf("hello from parallel cycle not lambda\n");
}

void main()
{
	atomic<int> aCounter;

	aCounter = 0;

	int privet = 100500;

	parallel_for(0, 20, 1, 
		[=, &aCounter] (int i) {
			//printf("hello from parallel cycle %i\n", privet);
			aCounter.fetch_and_increment();
	});

	printf("aCounter is %i", (int) aCounter);

	//parallel_for(size_t(0), size_t(20), size_t(1), cycle);

	getchar();
}