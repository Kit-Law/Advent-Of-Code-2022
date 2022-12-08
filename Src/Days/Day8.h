#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

namespace Day8 {

	inline bool isVisable(std::vector<std::vector<int>>& trees, int row, int col)
	{
		int height = trees[row][col];

		for (int i = row - 1; ; i--)
			if (i < 0) return true;
			else if (trees[i][col] >= height) break;

		for (int i = row + 1; ; i++)
			if (i >= trees.size()) return true;
			else if (trees[i][col] >= height) break;

		for (int i = col - 1; ; i--)
			if (i < 0) return true;
			else if (trees[row][i] >= height) break;

		for (int i = col + 1; ; i++)
			if (i >= trees.at(row).size()) return true;
			else if (trees[row][i] >= height) break;

		return false;
	}

	inline int getScenicScore(std::vector<std::vector<int>>& trees, int row, int col)
	{
		int scores[4] = { 0, 0, 0, 0 };
		int height = trees[row][col];

		for (int i = row - 1; i >= 0; i--)
		{
			scores[0]++;
			if (trees[i][col] >= height) break;
		}
		for (int i = row + 1; i < trees.size(); i++)
		{
			scores[1]++;
			if (trees[i][col] >= height) break;
		}
		for (int i = col - 1; i >= 0; i--)
		{
			scores[2]++;
			if (trees[row][i] >= height) break;
		}
		for (int i = col + 1; i < trees.at(row).size(); i++)
		{
			scores[3]++;
			if (trees[row][i] >= height) break;
		}

		return scores[0] * scores[1] * scores[2] * scores[3];
	}

	inline long star1(const char* path) noexcept
	{
		long result = 0;

		std::vector<std::vector<int>> trees;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			std::vector<int> line;
			for (int i = 0; i < buffer.size(); i++)
				line.push_back(buffer[i]);

			trees.push_back(line);
		}

		for (int row = 0; row < trees.size(); row++)
			for (int col = 0; col < trees.size(); col++)
				result += isVisable(trees, row, col);

		return result;
	}

	inline long star2(const char* path) noexcept
	{
		long bestScenicScore = 0;

		std::vector<std::vector<int>> trees;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			std::vector<int> line;
			for (int i = 0; i < buffer.size(); i++)
				line.push_back(buffer[i]);

			trees.push_back(line);
		}

		for (int row = 0; row < trees.size(); row++)
			for (int col = 0; col < trees.size(); col++)
			{
				int scenicScore = getScenicScore(trees, row, col);
				if (scenicScore > bestScenicScore)
					bestScenicScore = scenicScore;
			}

		return bestScenicScore;
	}

}