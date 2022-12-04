#pragma once

#include <fstream>
#include <sstream>

namespace Day4 {

	struct range
	{
		int from;
		int too;
	};

	inline long star1(const char* path) noexcept
	{
		long sum = 0;
		
		range elfOne, elfTwo;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			sscanf_s(buffer.c_str(), "%d-%d,%d-%d", &elfOne.from, &elfOne.too, &elfTwo.from, &elfTwo.too);

			sum += (elfOne.from <= elfTwo.from && elfOne.too >= elfTwo.too) || (elfTwo.from <= elfOne.from && elfTwo.too >= elfOne.too);
		}

		return sum;
	}

	inline long star2(const char* path) noexcept
	{
		long sum = 0;

		range elfOne, elfTwo;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			sscanf_s(buffer.c_str(), "%d-%d,%d-%d", &elfOne.from, &elfOne.too, &elfTwo.from, &elfTwo.too);

			sum += (elfOne.from <= elfTwo.from && elfOne.too >= elfTwo.from) || 
				(elfOne.from <= elfTwo.too && elfOne.too >= elfTwo.too) ||
				(elfTwo.from <= elfOne.from && elfTwo.too >= elfOne.from) ||
				(elfTwo.from <= elfOne.too && elfTwo.too >= elfOne.too);
		}

		return sum;
	}

}