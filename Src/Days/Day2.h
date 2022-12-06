#pragma once

#include <fstream>
#include <sstream>

namespace Day2 {

#define OPTIMAL_SOLUTION

#ifdef ORIGINAL_SOLUTION
	inline long star1(const char* path) noexcept
	{
		long sum = 0;

		char p1, p2;

		std::fstream input(path);
		while (input >> p2 >> p1)
		{
			p2 = p2 - 'A' + 1;
			p1 = p1 - 'X' + 1;

			sum += (p1 == p2) * 3 +
				((p1 == (p2 + 1)) || (p1 == (p2 - 2))) * 6 +
				p1;
		}

		return sum;
	}
#endif // ORIGINAL_SOLUTION

#ifdef OPTIMAL_SOLUTION
	inline long star1(const char* path) noexcept
	{
		long sum = 0;
		const short results[3][3] = { {3, 6, 0},
								      {0, 3, 6},
								      {6, 0, 3} };

		char p1, p2;
		std::fstream input(path);
		while (input >> p2 >> p1)
			sum += results[p2 - 'A'][p1 - 'X'] + p1 - 'X' + 1;

		return sum;
	}
#endif // OPTIMAL_SOLUTION

	inline long star2(const char* path) noexcept
	{
		long sum = 0;
		const short results[3][3] = { {3, 4, 8},
									  {1, 5, 9},
									  {2, 6, 7} };

		char outcome, p;
		std::fstream input(path);
		while (input >> p >> outcome)
			sum += results[p - 'A'][outcome - 'X'];

		return sum;
	}

}