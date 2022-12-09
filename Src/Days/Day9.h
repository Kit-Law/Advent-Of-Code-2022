#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

namespace Day9 {

#define PREDICTED_WIDTH 100000

	struct pos
	{
		long x = 0, y = 0;
	};

	template<size_t n>
	class Rope
	{
	private:
		pos knots[n];

		std::unordered_set<long> trail;
	public:
		Rope() { updateTrail(); }

		inline void moveHead(short x, short y, short distance)
		{
			for (short i = 0; i < distance; i++)
			{
				knots[0].x += x;
				knots[0].y += y;

				for (size_t knot = 1; knot < n; knot++)
					moveTail(knot);
			}
		}

		inline auto getTotalTailMovement() { return trail.size(); }
	private:
		inline void moveTail(size_t knot)
		{
			short x = knots[knot - 1].x - knots[knot].x;
			short y = knots[knot - 1].y - knots[knot].y;

			if (abs(x) > 1 || abs(y) > 1)
			{
				knots[knot].x += x + (x > 1 ? -1 : x < -1 ? 1 : 0);
				knots[knot].y += y + (y > 1 ? -1 : y < -1 ? 1 : 0);

				if (knot == n - 1) 
					updateTrail();
			}
		}

		inline void updateTrail() { trail.insert(knots[n - 1].x + knots[n - 1].y * PREDICTED_WIDTH); }

		inline void printTrail()
		{
			std::cout << std::endl;
			std::cout << std::endl;

			for (int i = 0; i < PREDICTED_WIDTH; i++)
			{
				for (int j = 0; j < PREDICTED_WIDTH; j++)
				{
					if (knots[0].x + 20 == j && knots[0].y + 20 == PREDICTED_WIDTH - i - 1) { std::cout << "H "; continue; }
					
					bool hit = false;
					for (int k = 1; k < n; k++)
						if (knots[k].x + 20 == j && knots[k].y + 20 == PREDICTED_WIDTH - i - 1)
						{
							std::cout << "1 ";
							hit = true;
							break;
						}
					if (!hit) std::cout << ". ";
				}
				std::cout << std::endl;
			}
		}
	};

	inline long star1(const char* path) noexcept
	{
		Rope<2> rope;

		char dir;
		short dist;
		std::fstream input(path);
		while (input >> dir >> dist)
		{
			switch (dir)
			{
			case 'U':
				rope.moveHead(0, 1, dist);
				break;
			case 'R':
				rope.moveHead(1, 0, dist);
				break;
			case 'D':
				rope.moveHead(0, -1, dist);
				break;
			case 'L':
				rope.moveHead(-1, 0, dist);
			}
		}

		return rope.getTotalTailMovement();
	}

	inline long star2(const char* path) noexcept
	{
		Rope<10> rope;

		char dir;
		short dist;
		std::fstream input(path);
		while (input >> dir >> dist)
		{
			switch (dir)
			{
			case 'U':
				rope.moveHead(0, 1, dist);
				break;
			case 'R':
				rope.moveHead(1, 0, dist);
				break;
			case 'D':
				rope.moveHead(0, -1, dist);
				break;
			case 'L':
				rope.moveHead(-1, 0, dist);
			}
		}

		return rope.getTotalTailMovement();
	}

}