#include <stdio.h>
#include <omp.h>

void main()
{
	int j = 0;

	#pragma omp parallel
	{
		//just one thread
		#pragma omp single nowait
		{
			for (int i = 0; i < 10; i++)
			{
				#pragma omp task firstprivate(i)
				{
					#pragma omp atomic
					j++;
					int threadNum = omp_get_thread_num();
					printf("i: %i, thread: %i\n", i, threadNum);
				}
			}
		}
	}

	getchar();
}