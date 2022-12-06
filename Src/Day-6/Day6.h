#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

namespace Day6 {

	inline long star1(const char* path) noexcept
	{
		long at = 0;
		std::vector<char> queue;

		char letter;
		std::fstream input(path);
		while (input >> letter)
		{
			at++;

			std::vector<char> testQueue;
			testQueue.push_back(letter);

			for (int i = queue.size() - 1; i >= 0; i--)
				if (letter != queue[i])
					testQueue.push_back(queue[i]);
				else
					break;
			
			if (testQueue.size() == 4)
				break;

			queue.clear();
			for (int i = testQueue.size() - 1; i >= 0; i--)
				queue.push_back(testQueue[i]);
		}

		return at;
	}

	inline long star2(const char* path) noexcept
	{
		long at = 0;
		std::vector<char> queue;

		char letter;
		std::fstream input(path);
		while (input >> letter)
		{
			at++;

			std::vector<char> testQueue;
			testQueue.push_back(letter);

			for (int i = queue.size() - 1; i >= 0; i--)
				if (letter != queue[i])
					testQueue.push_back(queue[i]);
				else
					break;

			if (testQueue.size() == 14)
				break;

			queue.clear();
			for (int i = testQueue.size() - 1; i >= 0; i--)
				queue.push_back(testQueue[i]);
		}

		return at;
	}

}