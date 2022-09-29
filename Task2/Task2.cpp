
#include <iostream>
#include "PriorityStack.cpp"
#include "windows.h"

#include <random>

int main()
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 1000);
    
    PriorityStack<int> pStack;

	
	for (int i = 0; i < 20; i++)
	{
		pStack.Push(distribution(generator), distribution(generator));
	}

	pStack.printStack();

	while(!pStack.IsEmpty())
	{
		std::cout<<pStack.Pop() <<std::endl;
	}
}
