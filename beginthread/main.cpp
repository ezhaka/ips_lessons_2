#include <process.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <windows.h>
#include <iostream>

using namespace std;

#define ITER 3000

int activeThreads = 0;
CRITICAL_SECTION cs;

void iAlu()
{
	for (int i = 0; i < ITER; i++)
	{
		_asm
		{
			add eax, eax
			add ebx, ebx
			add ecx, ecx
			add edx, edx
		}
	}
}

void iFpu()
{
	for (int i = 0; i < ITER; i++)
	{
		_asm
		{
			fadd st(0), st(2)
			fxch st(1)
			fadd st(0), st(3)
			fxch st(1)
		}
	}
}
  
void Thread1( void* pParams )
{ 
	for (int i = 0; i < ITER; i++)
	{
		iAlu();
	}

	EnterCriticalSection( &cs );
	activeThreads--;
	LeaveCriticalSection(&cs);
}

void Thread2( void* pParams )
{ 
	for (int i = 0; i < ITER; i++)
	{
		iFpu();
	}

	EnterCriticalSection( &cs );
	activeThreads--;
	LeaveCriticalSection(&cs);
}

void createThreads(int num, ...)
{
	activeThreads = num;

	va_list args;
	va_start(args, num);

	clock_t tStart = clock();

	for (int i = 0; i < num; i++)
	{
		int arg = va_arg(args, int);
		
		printf("%i ", arg);

		if (arg == 1)
		{
			_beginthread(Thread1, 0, NULL);
		}
		
		if (arg == 2)
		{
			_beginthread(Thread2, 0, NULL);
		}
	}

	printf("...\n");
	va_end(args);
  
	while(activeThreads != 0) {}

	printf("%i threads time taken: %fs\n", num, (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

//hyper-threading test
//taken from http://evatutin.narod.ru/evatutin_opt_05_httdepindep.pdf
int main()
{ 
	InitializeCriticalSection( &cs );

	int experimentsCount = 5;

	for (int i = 0; i < experimentsCount; i++)
	{
		createThreads(1, 2); //iFpu threads
	}

	for (int i = 0; i < experimentsCount; i++)
	{
		createThreads(2, 2, 2); //iFpu threads
	}

	for (int i = 0; i < experimentsCount; i++)
	{
		createThreads(4, 2, 2, 2, 2); //iFpu threads
	}

	getchar();

	return 0;
}