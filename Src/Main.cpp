#include <iostream>

#include "Day-1/Day1.h"
#include "Day-2/Day2.h"
#include "Day-3/Day3.h"
#include "Day-4/Day4.h"
#include "Day-5/Day5.h"

int main()
{
	try
	{
		//std::cout << "Day 1: Star 1 = " << Day1::star1("Input/Day1.txt") << ", Star 2 = " << Day1::star2("Input/Day1.txt") << std::endl;
		//std::cout << "Day 2: Star 1 = " << Day2::star1("Input/Day2.txt") << ", Star 2 = " << Day2::star2("Input/Day2.txt") << std::endl;
		//std::cout << "Day 3: Star 1 = " << Day3::star1("Input/Day3.txt") << ", Star 2 = " << Day3::star2("Input/Day3.txt") << std::endl;
		//std::cout << "Day 4: Star 1 = " << Day4::star1("Input/Day4.txt") << ", Star 2 = " << Day4::star2("Input/Day4.txt") << std::endl;
		std::cout << "Day 5: Star 1 = " << Day5::star1("Input/Day5.txt") << ", Star 2 = " << Day5::star2("Input/Day5.txt") << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}