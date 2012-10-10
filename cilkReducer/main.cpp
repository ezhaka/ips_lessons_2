#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
#include <cilk/reducer_ostream.h>
#include <cilk/reducer_list.h>
#include <cilk/reducer_max.h>
#include <cilk/reducer_string.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <string>

#include "tbb/scalable_allocator.h"

using namespace cilk;

void main()
{
	reducer_basic_string<std::string> strReducer;

	//cilk_for(int i = 50; i < 70; i++)
	//{
	//	std::string* blah = scalable_malloc();

	//	strReducer.append(blah);
	//}

	printf("string reduce %s\n", strReducer.get_value());

	reducer_max_index<int,int> maxIndex = reducer_max_index<int,int>(1, 34);

	maxIndex.calc_max(2, 32);

	printf("key: %i value: %i\n", maxIndex.get_index(), maxIndex.get_value());


	reducer_max<int> unkonwnReducer = reducer_max<int>(34);

	unkonwnReducer.calc_max(32);

	printf("unknown reducer: %i\n", unkonwnReducer.get_value());





	std::list<int> list = std::list<int>();

	reducer_list_append<int> listAppend;


	//reducer_opadd<int> sum;
	//reducer_ostream* stream = new reducer_ostream(std::cout);
	//sum.set_value(0);

	//cilk_for (int i = 0; i < 100; i++)
	//{

	//	listAppend.push_back(i);

	//	//(*stream) << i << std::endl;
	//	std::cout << i << std::endl;
	//	sum += i;
	//}


	//list = listAppend.get_value();

	//for (std::list<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	//{
	//	printf("%i ", (*iter));
	//}


	getchar();
}