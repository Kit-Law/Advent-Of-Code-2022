#pragma once

#pragma warning(disable:4996)

#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <cstdint>

namespace Day11 {

	class Monkey
	{
	private:
		std::queue<uint64_t> items;

		char opcode;
		int oparand;
		
		int test;
		int trueMonkey;
		int falseMonkey;

		int inspectedCount = 0;

		long* lcm;
	public:
		inline void inspectNextItem(float worryRelif = 3.0f) 
		{ 
			switch (opcode)
			{
			case '+':
				items.front() += oparand;
				break;
			case '*':
				items.front() *= oparand != 0 ? oparand : items.front();
				break;
			}
			inspectedCount++;

			if (worryRelif != 1.0f)
				items.front() /= worryRelif;
			else
				items.front() = items.front() % *lcm;
		}

		inline int passToMonkey()
		{
			return items.front() % test == 0 ? trueMonkey : falseMonkey;
		}

		inline void reciveItem(uint64_t worryLevel)
		{ 
			items.push(worryLevel); 
		}

		inline uint64_t thorwItem()
		{ 
			uint64_t buffer = items.front();
			items.pop();
			return buffer;
		}

		inline size_t getStockpileCount() { return items.size(); }

		inline char* getOpcode() { return &opcode; };
		inline int* getOparand() { return &oparand; };

		inline int* getTest() { return &test; };
		inline int* getTrueMonkey() { return &trueMonkey; };
		inline int* getFalseMonkey() { return &falseMonkey; };

		inline std::queue<uint64_t> getItems() { return items; };

		inline int getInspectedCount() { return inspectedCount; };

		inline void setLCM(long* lcm) { this->lcm = lcm; }
	};

	class MonkeyMastermind
	{
	private:
		std::vector<Monkey*> monkeys;
		long lcm = 1;
	public:
		MonkeyMastermind(const char* path)
		{
			std::string buffer;
			std::fstream input(path);
			
			while (std::getline(input, buffer))
			{
				monkeys.push_back(new Monkey());

				std::getline(input, buffer);
				std::stringstream ss(buffer);
				ss >> buffer; ss >> buffer;
				while (ss.good())
				{
					std::getline(ss, buffer, ',');
					monkeys.back()->reciveItem(stoi(buffer));
				}
				std::getline(input, buffer);
				int opcode; int oparand;
				sscanf(buffer.c_str(), "  Operation: new = old %c %d", monkeys.back()->getOpcode(), monkeys.back()->getOparand());
				std::getline(input, buffer);
				sscanf_s(buffer.c_str(), "  Test: divisible by %d", monkeys.back()->getTest());
				std::getline(input, buffer);
				sscanf_s(buffer.c_str(), "    If true: throw to monkey %d", monkeys.back()->getTrueMonkey());
				std::getline(input, buffer);
				sscanf_s(buffer.c_str(), "    If false: throw to monkey %d", monkeys.back()->getFalseMonkey());
				std::getline(input, buffer);

				lcm *= *monkeys.back()->getTest();
				monkeys.back()->setLCM(&lcm);
			}
		}

		inline void preformRound(float worryRelif = 3.0f)
		{
			for (Monkey* monkey : monkeys)
			{
				size_t stockpile = monkey->getStockpileCount();
				for (int item = 0; item < stockpile; item++)
				{
					monkey->inspectNextItem(worryRelif);
					int throwTo = monkey->passToMonkey();
					uint64_t worryLevel = monkey->thorwItem();
					monkeys[throwTo]->reciveItem(worryLevel);
				}
			}
		}

		inline void outputRound()
		{
			std::cout << std::endl;
			for (int i = 0; i < monkeys.size(); i++)
			{
				std::cout << "Monkey " << i << ": ";
				std::queue<uint64_t> items = monkeys.at(i)->getItems();
				while (items.size() > 0)
				{
					std::cout << items.front() << ", ";
					items.pop();
				}
				std::cout << std::endl;
			}
		}

		inline unsigned long long getMonkeyBusiness()
		{
			std::vector<int> businessLevels;
			for (Monkey* monkey : monkeys)
				businessLevels.push_back(monkey->getInspectedCount());
			std::sort(businessLevels.begin(), businessLevels.end(), [](int& a, int& b) { return a > b; });
			return (unsigned long long)businessLevels[0] * (unsigned long long)businessLevels[1];
		}
	};

	inline unsigned long long star1(const char* path) noexcept
	{
		MonkeyMastermind mm(path);

		for (int i = 0; i < 20; i++)
		{
			mm.preformRound();
			//mm.outputRound();
		}

		return mm.getMonkeyBusiness();
	}

	inline unsigned long long star2(const char* path) noexcept
	{
		MonkeyMastermind mm(path);

		for (int i = 0; i < 10000; i++)
			mm.preformRound(1.0f);

		return mm.getMonkeyBusiness();
	}

}