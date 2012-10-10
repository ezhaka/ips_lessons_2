#include <cilk/cilk.h>
#include <cilk/reducer_ostream.h>
#include <cilk/reducer_list.h>
#include <cilk/reducer_max.h>
#include <stdio.h>
#include <iostream>
#include <list>

using namespace cilk;

void maxIndexReducerDemo()
{
	reducer_max_index<int,int> maxIndex = reducer_max_index<int,int>(1, 34);

	maxIndex.calc_max(2, 32);

	printf("maxIndexReducer, key: %i value: %i\n", maxIndex.get_index(), maxIndex.get_value());
}

void maxReducerDemo()
{
	reducer_max<int> reducerMax = reducer_max<int>(34);

	reducerMax.calc_max(32);

	printf("max reducer, max: %i\n", reducerMax.get_value());
}

void listAppendReducerDemo()
{
	std::list<int> list = std::list<int>();

	reducer_list_append<int> listAppendReducer;

	cilk_for (int i = 0; i < 100; i++)
	{
		listAppendReducer.push_back(i);
	}

	list = listAppendReducer.get_value();

	printf("list reducer result: \n");

	for (std::list<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		printf("%i ", (*iter));
	}
}

void oStreamReducerDemo()
{
	reducer_ostream* stream = new reducer_ostream(std::cout);

	printf("\nostream reducer result: \n");

	cilk_for (int i = 0; i < 100; i++)
	{
		(*stream) << i << " ";
	}
}

void main()
{
	maxIndexReducerDemo();
	maxReducerDemo();
	listAppendReducerDemo();
	oStreamReducerDemo();

	getchar();
}