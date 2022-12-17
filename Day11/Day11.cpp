#include "Day11.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <regex>
#include <sstream>	//stringstream to read negative numbers from string

namespace dayEleven {
	Monkey::Monkey(std::vector<size_t> items, std::string operation, int divisibleBy, int throwToMonkeyTrue, int throwToMonkeyFalse) {
		numOfInspectedItems = 0;

		//all monkeys reference the same list of monkeys to pass items to
		this->items = items;
		this->operation = operation;
		this->divisibleBy = divisibleBy;

		throwToMonkey[0] = throwToMonkeyTrue;
		throwToMonkey[1] = throwToMonkeyFalse;
	}

	void Monkey::SetMonkeyVectorReferences(std::vector<Monkey*>& monkeys) {
		this->monkeys = monkeys;
	}

	void Monkey::SetCommonMultiple(int leastCommonMultiple) {
		this->leastCommonMultiple = leastCommonMultiple;
	}

	void Monkey::ThrowAllItems(bool decreaseWorryAfterInspection) {
		for (size_t item : items) {
			numOfInspectedItems++;

			item %= leastCommonMultiple;

			size_t secondPartOfEquation = 0;

			//apply operation. It looks like + 3 or * old etc. witin this class
			std::string secondPartOfEquationString = operation.substr(2, operation.size() - 2);
			if (secondPartOfEquationString == "old")
				secondPartOfEquation = item;
			else
				secondPartOfEquation = std::stoull(secondPartOfEquationString);

			switch (operation[0]) {
				case '+':
					item += secondPartOfEquation;
					break;
				case '-':
					item -= secondPartOfEquation;
					break;
				case '*':
					item *= secondPartOfEquation;
					break;
				case '/':
					item /= secondPartOfEquation;
					break;
			}

			//divide by 3 and round down, but int does that automatically
			if(decreaseWorryAfterInspection)
				item /= 3;

			//throw item to correct monkey depending on condition
			//Modulo == 0 means it's divisible without rest
			if (item % divisibleBy == 0)
				monkeys[throwToMonkey[0]]->AddItem(item);
			else
				monkeys[throwToMonkey[1]]->AddItem(item);
		}

		//all items are thrown to other monkeys
		items.clear();
	}

	void Monkey::AddItem(size_t item) {
		items.push_back(item);
	}

	int Monkey::GetNumOfInspectedItems() {
		return numOfInspectedItems;
	}


	unsigned long long GetMultipliedMonkeyBusiness(bool partOneOfTask) {
		std::ifstream movementInstructions("./InputFiles/Day11_Monkeys.txt", std::ifstream::in);

		std::vector<Monkey*> monkeys;
		//variable used to make sure no variable overflow is possible
		int leastCommonMultiple = 1;
		//read out data
		if (movementInstructions.is_open())
		{
			std::string line{};

			//Get input lines
			while (std::getline(movementInstructions, line)) {
				//first line is the monkey and its num
				
				std::getline(movementInstructions, line);
				//second line are starting items
				std::vector<size_t> startingItems{};
				//remove everything but , and
				line = std::regex_replace(line, std::regex("[^0-9,]"), "");
				//convert to int vec
				ConvertStringToIntVector(line, startingItems);

				std::getline(movementInstructions, line);
				//this line is operation
				//first 19 chars are always "  Operation: new = old "
				std::string operation = line.substr(23, line.size()-23);

				std::getline(movementInstructions, line);
				//fourth line is divisible by variable
				//regex to remove all but numbers
				line = std::regex_replace(line, std::regex("[^0-9]"), "");
				int divisibleBy = std::stoi(line);
				leastCommonMultiple *= divisibleBy;

				std::getline(movementInstructions, line);
				//fifth line is throw to monkey if true
				line = std::regex_replace(line, std::regex("[^0-9]"), "");
				int throwToMonkeyTrue = std::stoi(line);

				std::getline(movementInstructions, line);
				//sixth line is throw to monkey if false
				line = std::regex_replace(line, std::regex("[^0-9]"), "");
				int throwToMonkeyFalse = std::stoi(line);

				//skip empty lines
				std::getline(movementInstructions, line);

				//create new monkey and add it to the vector
				monkeys.push_back(new Monkey{ startingItems, operation, divisibleBy, throwToMonkeyTrue, throwToMonkeyFalse });
			}

			//close file
			movementInstructions.close();
		}

		for (Monkey* monkey : monkeys) {
			monkey->SetMonkeyVectorReferences(monkeys);
			monkey->SetCommonMultiple(leastCommonMultiple);
		}

		int twoHeighest[2]{ 0, 0 };
		if (partOneOfTask) {
			//iterate through all monkeys 20 times and let them execute their throwing actions
			for (int i = 0; i < 20; i++) {
				for (Monkey* monkey : monkeys)
					monkey->ThrowAllItems(true);
			}
		}
		//part two of task
		else {
			//iterate through all monkeys 10000 times and let them execute their throwing actions
			for (int i = 0; i < 10000; i++) {
				for (Monkey* monkey : monkeys) {
					monkey->ThrowAllItems(false);
				}
			}
		}

		//find two highest numbers of inspected items. 0 is heighest, 1 is second heighest
		for (Monkey* monkey : monkeys) {
			//if a new heighest number has been found
			if (monkey->GetNumOfInspectedItems() > twoHeighest[0]) {
				twoHeighest[1] = twoHeighest[0];
				twoHeighest[0] = monkey->GetNumOfInspectedItems();
			}
			//new second heighest number has been found
			else if (monkey->GetNumOfInspectedItems() > twoHeighest[1]) {
				twoHeighest[1] = monkey->GetNumOfInspectedItems();
			}
		}

		//free up memory
		for (Monkey* monkey : monkeys)
			delete(monkey);

		return static_cast<unsigned long long>(twoHeighest[0]) * twoHeighest[1];
	}

	void ConvertStringToIntVector(std::string& str, std::vector<size_t>& vec) {
		std::stringstream stringAsStream(str);
		std::string segment;

		while (std::getline(stringAsStream, segment, ','))
		{
			vec.push_back(std::stoull(segment));
		}
	}
}