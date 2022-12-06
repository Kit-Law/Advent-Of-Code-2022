#pragma once

#include <fstream>
#include <sstream>

namespace Day3 {

	inline long star1(const char* path) noexcept
	{
		long sum = 0;

		std::string rucksack;

		std::fstream input(path);
		while (std::getline(input, rucksack))
		{
			char match = NULL;
			for (size_t firstComp = 0; firstComp < rucksack.size() / 2; firstComp++)
			{
				for (size_t secondComp = rucksack.size() / 2; secondComp < rucksack.size(); secondComp++)
					if (rucksack[firstComp] == rucksack[secondComp])
					{
						match = rucksack[firstComp];
						break;
					}
						
				if (match != NULL)
					break;
			}

			sum += match - (match < 'a' ? 'A' - 27 : 'a' - 1);
		}

		return sum;
	}

	inline long star2(const char* path) noexcept
	{
		long sum = 0;

		std::string rucksackOne;
		std::string rucksackTwo;
		std::string rucksackThree;

		std::fstream input(path);
		while (std::getline(input, rucksackOne))
		{
			std::getline(input, rucksackTwo);
			std::getline(input, rucksackThree);

			char badge = NULL;
			for (size_t i = 0; i < rucksackOne.size(); i++)
			{
				for (size_t j = 0; j < rucksackTwo.size(); j++)
					if (rucksackOne[i] == rucksackTwo[j])
					{
						for (size_t k = 0; k < rucksackThree.size(); k++)
							if (rucksackOne[i] == rucksackThree[k])
							{
								badge = rucksackOne[i];
								break;
							}
						if (badge != NULL) break;
					}
						
				if (badge != NULL) break;
			}

			sum += badge - (badge < 'a' ? 'A' - 27 : 'a' - 1);
		}

		return sum;
	}

}