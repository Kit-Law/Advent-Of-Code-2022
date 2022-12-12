#include <iostream>

#include "Days/Day1.h"
#include "Days/Day2.h"
#include "Days/Day3.h"
#include "Days/Day4.h"
#include "Days/Day5.h"
#include "Days/Day6.h"
#include "Days/Day7.h"
#include "Days/Day8.h"
#include "Days/Day9.h"
#include "Days/Day10.h"
#include "Days/Day11.h"
#include "Days/Day12.h"
#include "Days/Day13.h"
#include "Days/Day14.h"
#include "Days/Day15.h"
#include "Days/Day16.h"
#include "Days/Day17.h"
#include "Days/Day18.h"
#include "Days/Day19.h"
#include "Days/Day20.h"
#include "Days/Day21.h"
#include "Days/Day22.h"
#include "Days/Day23.h"
#include "Days/Day24.h"
#include "Days/Day25.h"

#define SOLUTION(day) std::cout << #day << ": Star 1 = " << day::star1("Input/" #day ".txt") << ", Star 2 = " << day::star2("Input/" #day ".txt") << std::endl;

int main()
{
	try
	{
		SOLUTION(Day12)
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}