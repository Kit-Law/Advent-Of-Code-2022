#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <sstream>

namespace Day10 {

	inline void updateCycle(long X, int* cycle, long* result) 
	{
		(*cycle)++;

		if ((*cycle - 20) % 40 == 0)
			*result += *cycle * X;
	}

	inline void updateCRT(long X, int* cycle, std::stringstream* output)
	{
		if (*cycle % 40 == 0)
			*output << std::endl;

		if (X == *cycle % 40 || X + 1 == *cycle % 40 || X - 1 == *cycle % 40)
			*output << "#";
		else
			*output << ".";

		(*cycle)++;
	}

	inline long star1(const char* path) noexcept
	{
		long result = 0;
	
		long X = 1;
		int cycle = 0;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			std::stringstream command(buffer);
			std::string opcode;

			command >> opcode;

			updateCycle(X, &cycle, &result);
			if (opcode == "addx")
			{
				updateCycle(X, &cycle, &result);

				command >> opcode; //oparand
				X += stoi(opcode);
			}
		}

		return result;
	}

	inline std::string star2(const char* path) noexcept
	{
		long X = 1;
		int cycle = 0;

		std::stringstream output;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			std::stringstream command(buffer);
			std::string opcode;

			command >> opcode;

			updateCRT(X, &cycle, &output);
			if (opcode == "addx")
			{
				updateCRT(X, &cycle, &output);

				command >> opcode; //oparand
				X += stoi(opcode);
			}
		}

		return output.str();
	}

}