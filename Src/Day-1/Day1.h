#pragma once

#include <fstream>
#include <sstream>

namespace Day1 {

	inline long star1(const char* path) noexcept
	{
		long fattestElf = 0;
		long currentElf = 0;

		std::fstream input(path);
		std::string calories;
		while (std::getline(input, calories))
		{
			if (!calories.empty()) [[likely]]
			{
				currentElf += stoi(calories);
				continue;
			}	
			
			if (currentElf > fattestElf)
				fattestElf = currentElf;

			currentElf = 0;
		}

		return fattestElf > currentElf ? fattestElf : currentElf;
	}

	template<typename t, int k>
	class KMax
	{
	private:
		t elements[k];
	
	public:
		KMax()
		{
			for (int i = 0; i < k; i++)
				elements[i] = 0;
		}

		inline void insert(const t element)
		{
			for (size_t i = 0; i < k; i++)
				if (elements[i] < element)
				{
					pushStack(i);
					elements[i] = element;
					break;
				}
		}

		inline t getElementSum() 
		{ 
			t sum = 0;
			for (int i = 0; i < k; i++)
				sum += elements[i];

			return sum;
		}
	private:
		inline void pushStack(size_t i)
		{
			t buffer;
			for (int j = k - 1; j > i; j--)
			{
				buffer = elements[j];
				elements[j] = elements[j - 1];
				elements[j - 1] = buffer;
			}
		}
	};

	inline long star2(const char* path) noexcept
	{
		KMax<long, 3> fattestElfs;
		long currentElf = 0;

		std::fstream input(path);
		std::string calories;
		while (std::getline(input, calories))
		{
			if (!calories.empty()) [[likely]]
			{
				currentElf += stoi(calories);
				continue;
			}

			fattestElfs.insert(currentElf);
			currentElf = 0;
		}
		fattestElfs.insert(currentElf);

		return fattestElfs.getElementSum();
	}
}