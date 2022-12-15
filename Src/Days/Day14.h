#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <math.h>

namespace Day14 {

	struct point
	{
		int x, y;
	};

	template<int n>
	class Cave
	{
	private:
		bool atRest[n][n] = { false };
		int largestY = 0;
	public:
		inline void genRocks(const char* path)
		{
			std::string buffer;
			std::fstream input(path);
			while (std::getline(input, buffer))
			{
				point start = {-1, -1};
				point end = { 0, 0 };

				std::stringstream rocks(buffer);
				while (rocks.good())
				{
					rocks >> buffer;
					if (buffer == "->")
						continue;

					sscanf_s(buffer.c_str(), "%d,%d", &end.x, &end.y);

					if (end.y > largestY)
						largestY = end.y;

					if (start.x != -1)
						createRocks(start, end);

					start = end;
				}
			}
		}

		inline void addFloor()
		{
			for (int x = 0; x < n; x++)
				atRest[largestY + 2][x] = true;
		}

		inline bool addSandGain()
		{
			if (atRest[0][500]) return false;

			int x = 500;
			for (int y = 0; y < largestY + 2; y++)
				if (!atRest[y + 1][x])
					continue;
				else if (!atRest[y + 1][x - 1])
				{
					x--;
					continue;
				}
				else if (!atRest[y + 1][x + 1])
				{
					x++;
					continue;
				}
				else
				{
					atRest[y][x] = true;
					return true;
				}

			return false;
		}
	private:
		inline void createRocks(const point& start, const point& end)
		{
			for (int x = std::min(start.x, end.x); x <= std::max(start.x, end.x); x++)
				for (int y = std::min(start.y, end.y); y <= std::max(start.y, end.y); y++)
					atRest[y][x] = true;
		}
	};

	inline long star1(const char* path) noexcept
	{
		Cave<1000> cave;
		cave.genRocks(path);
		for (int result = 0; true; result++)
			if (!cave.addSandGain()) return result;

		return -1;
	}

	inline long star2(const char* path) noexcept
	{
		Cave<1000> cave;
		cave.genRocks(path);
		cave.addFloor();
		for (int result = 0; true; result++)
			if (!cave.addSandGain()) return result;

		return -1;
	}

}