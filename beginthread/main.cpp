#include <process.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <windows.h>
#include <iostream>

using namespace std;

#define ITER 1000000000

int activeThreads = 0;
CRITICAL_SECTION cs;

void iAlu()
{
	_asm
	{
		mov eax, 0x16
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		add eax, eax
		/*add ebx, ebx
		add edx, edx
		add esi, esi
		add edi, edi*/
	}
}

void iFpu()
{
	_asm
	{
		fadd st(0), st(2)
		fxch st(1)
		fadd st(0), st(3)
		fxch st(1)
	}
}
  
void Thread1( void* pParams )
{ 
	int x = 1;

	for (int i = 0; i < ITER; i++)
	{
		x+=100500;
		x-=100500;
		//iAlu();
	}

	EnterCriticalSection( &cs );
	activeThreads--;
	LeaveCriticalSection(&cs);
}

void Thread3 (void* pParams)
{
	int x = 1;
	int y = 2;

	for (int i = 0; i < ITER; i++)
	{
		x+=100500;
		x-=100500;
		y+=100500;
		y-=100500;
		//iAlu();
	}

	EnterCriticalSection( &cs );
	activeThreads--;
	LeaveCriticalSection(&cs);
}

void Thread2( void* pParams )
{ 
	float x = 1.21;

	for (int i = 0; i < ITER; i++)
	{
		x+=100500.666;
		x-=100500.666;
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

		if (arg == 3)
		{
			_beginthread(Thread3, 0, NULL);
		}
	}

	printf("...\n");
	va_end(args);
  
	while(activeThreads != 0) {}

	printf("%i threads time taken: %.2fs\n", num, (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
  
int main()
{ 
	InitializeCriticalSection( &cs );

	//createThreads(1, 1);

	createThreads(1, 1);
	createThreads(1, 3);
	//createThreads(1, 2);
	//createThreads(4, 2, 1, 2, 1);
	//createThreads(4, 1, 1, 1, 1);
	//createThreads(4, 2, 2, 2, 2);
	//createThreads(8);

	getchar();

	return 0;
}