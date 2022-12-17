#include "Day3.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>

namespace dayThree {
	std::string inputDataPath = "./InputFiles/Day3_itemsInRucksack.txt";

	int GetCombinedRucksackPriority()
	{
		std::ifstream itemsInRucksackTxt(inputDataPath, std::ifstream::in);

		int totalPriority = 0;
		//read out data
		if (itemsInRucksackTxt.is_open())
		{
			std::string line{};

			while (std::getline(itemsInRucksackTxt, line))
			{
				// Create a set of 1st compartment, to have linear access speed to each element of the set
				std::unordered_set<char> firstCompartmentSet;

				// traverse the first comparment and add its values to the set 
				for (int i = 0; i < line.size() / 2; i++)
					//elements are only inserted if they're not already in the set
					firstCompartmentSet.insert(line[i]);


				// traverse the second comparment and find the first repeating item 
				for (int i = line.size() / 2; i < line.size(); i++) {
					//repeating item found
					if (firstCompartmentSet.find(line[i]) != firstCompartmentSet.end()) {
						//convert letter to points
						//upper case letter
						if (line[i] <= 90)
							//priority is ranging from 27-52
							totalPriority += line[i] - 38;
						//lower case letter
						else
							//priority is ranging from 1-26
							totalPriority += line[i] - 96;

						//break out of the loop cause search is completed here
						break;
					}
				}
			}

			//close file
			itemsInRucksackTxt.close();
		}

		return totalPriority;
	}

	int GetCombinedGroupBadgePriority() {
		std::ifstream itemsInRucksackTxt(inputDataPath, std::ifstream::in);

		int totalPriority = 0;
		//read out data
		if (itemsInRucksackTxt.is_open())
		{
			std::string line1{}, line2{}, line3{};

			while (std::getline(itemsInRucksackTxt, line1))
			{
				// Create a set of first elves inventory
				std::unordered_set<char> firstElfInventorySet;

				// traverse the first comparment and add its values to the set 
				for (int i = 0; i < line1.size(); i++)
					//elements are only inserted if they're not already in the set
					firstElfInventorySet.insert(line1[i]);

				//get second and third elf inventory
				std::getline(itemsInRucksackTxt, line2);
				std::getline(itemsInRucksackTxt, line3);

				//find common items between first and second elf
				std::unordered_set<char> commonItems = GetCommonCharacters(firstElfInventorySet, line2);

				// traverse the third elves invetory, and look for first common character between it and the other two elves
				for (int i = 0; i < line3.size(); i++) {
					//repeating item found
					if (commonItems.find(line3[i]) != commonItems.end()) {
						//convert letter to points
						//upper case letter
						if (line3[i] <= 90)
							//priority is ranging from 27-52
							totalPriority += line3[i] - 38;
						//lower case letter
						else
							//priority is ranging from 1-26
							totalPriority += line3[i] - 96;

						//break out of the loop cause search is completed here
						break;
					}
				}
			}

			//close file
			itemsInRucksackTxt.close();
		}

		return totalPriority;
	}

	std::unordered_set<char> GetCommonCharacters(std::unordered_set<char>& charSet, std::string str) {
		std::unordered_set<char> commonCharacters;

		// traverse the string and look for common characters
		for (int i = 0; i < str.size(); i++) {
			//repeating item found
			if (charSet.find(str[i]) != charSet.end()) {
				commonCharacters.insert(str[i]);
			}
		}

		return commonCharacters;
	}
}