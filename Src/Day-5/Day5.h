#pragma once

#include <fstream>
#include <sstream>
#include <stack>

namespace Day5 {
		
#ifdef EXAMPLE
	#define NUM_OF_BINS 3
#else
	#define NUM_OF_BINS 9
#endif

	inline std::string star1(const char* path) noexcept
	{
		std::stack<char> bins[NUM_OF_BINS];

#ifdef EXAMPLE
		bins[0].push('Z'); bins[0].push('N');
		bins[1].push('M'); bins[1].push('C'); bins[1].push('D');
		bins[2].push('P');
#else
		bins[0].push('S'); bins[0].push('Z'); bins[0].push('P'); bins[0].push('D'); bins[0].push('L'); bins[0].push('B'); bins[0].push('F'); bins[0].push('C');
		bins[1].push('N'); bins[1].push('V'); bins[1].push('G'); bins[1].push('P'); bins[1].push('H'); bins[1].push('W'); bins[1].push('B');
		bins[2].push('F'); bins[2].push('W'); bins[2].push('B'); bins[2].push('J'); bins[2].push('G');
		bins[3].push('G'); bins[3].push('J'); bins[3].push('N'); bins[3].push('F'); bins[3].push('L'); bins[3].push('W'); bins[3].push('C'); bins[3].push('S');
		bins[4].push('W'); bins[4].push('J'); bins[4].push('L'); bins[4].push('T'); bins[4].push('P'); bins[4].push('M'); bins[4].push('S'); bins[4].push('H');
		bins[5].push('B'); bins[5].push('C'); bins[5].push('W'); bins[5].push('G'); bins[5].push('F'); bins[5].push('S');
		bins[6].push('H'); bins[6].push('T'); bins[6].push('P'); bins[6].push('M'); bins[6].push('Q'); bins[6].push('B'); bins[6].push('W');
		bins[7].push('F'); bins[7].push('S'); bins[7].push('W'); bins[7].push('T'); 
		bins[8].push('N'); bins[8].push('C'); bins[8].push('R');
#endif

		int from, too;
		int count;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			sscanf_s(buffer.c_str(), "move %d from %d to %d", &count, &from, &too);

			for (int i = 0; i < count; i++)
			{
				bins[too - 1].push(bins[from - 1].top());
				bins[from - 1].pop();
			}
		}

		std::string tops;
		for (int i = 0; i < NUM_OF_BINS; i++)
			tops += bins[i].top();

		return tops;
	}

	inline std::string star2(const char* path) noexcept
	{
		std::stack<char> bins[NUM_OF_BINS];

#ifdef EXAMPLE
		bins[0].push('Z'); bins[0].push('N');
		bins[1].push('M'); bins[1].push('C'); bins[1].push('D');
		bins[2].push('P');
#else
		bins[0].push('S'); bins[0].push('Z'); bins[0].push('P'); bins[0].push('D'); bins[0].push('L'); bins[0].push('B'); bins[0].push('F'); bins[0].push('C');
		bins[1].push('N'); bins[1].push('V'); bins[1].push('G'); bins[1].push('P'); bins[1].push('H'); bins[1].push('W'); bins[1].push('B');
		bins[2].push('F'); bins[2].push('W'); bins[2].push('B'); bins[2].push('J'); bins[2].push('G');
		bins[3].push('G'); bins[3].push('J'); bins[3].push('N'); bins[3].push('F'); bins[3].push('L'); bins[3].push('W'); bins[3].push('C'); bins[3].push('S');
		bins[4].push('W'); bins[4].push('J'); bins[4].push('L'); bins[4].push('T'); bins[4].push('P'); bins[4].push('M'); bins[4].push('S'); bins[4].push('H');
		bins[5].push('B'); bins[5].push('C'); bins[5].push('W'); bins[5].push('G'); bins[5].push('F'); bins[5].push('S');
		bins[6].push('H'); bins[6].push('T'); bins[6].push('P'); bins[6].push('M'); bins[6].push('Q'); bins[6].push('B'); bins[6].push('W');
		bins[7].push('F'); bins[7].push('S'); bins[7].push('W'); bins[7].push('T');
		bins[8].push('N'); bins[8].push('C'); bins[8].push('R');
#endif

		int from, too;
		int count;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			sscanf_s(buffer.c_str(), "move %d from %d to %d", &count, &from, &too);

			std::stack<char> slowReverse;
			for (int i = 0; i < count; i++)
			{
				slowReverse.push(bins[from - 1].top());
				bins[from - 1].pop();
			}
			for (int i = 0; i < count; i++)
			{
				bins[too - 1].push(slowReverse.top());
				slowReverse.pop();
			}
		}

		std::string tops;
		for (int i = 0; i < NUM_OF_BINS; i++)
			tops += bins[i].top();

		return tops;
	}

}