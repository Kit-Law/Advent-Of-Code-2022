#include <iostream>

#include "Day-1/Day1.h"

int main()
{
	try
	{
		std::cout << "Day 1: Star 1 = " << Day1::star1("Input/Day1.txt") << ", Star 2 = " << Day1::star2("Input/Day1.txt") << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}