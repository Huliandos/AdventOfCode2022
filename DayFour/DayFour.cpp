#include "DayFour.h"

#include <iostream>
#include <fstream>	//std::ifstream

namespace dayFour {
	std::string inputDataPath = "./InputFiles/DayFour_pairedCleaningIDs.txt";

	void ConvertInputToInts(int* rangeExtrema, std::string* elfRanges, int posOfDelimiterRange1, int posOfDelimiterRange2) {
		rangeExtrema[0] = std::stoi(elfRanges[0].substr(0, posOfDelimiterRange1));
		rangeExtrema[1] = std::stoi(elfRanges[0].substr(posOfDelimiterRange1 + 1, elfRanges[0].length()));
		rangeExtrema[2] = std::stoi(elfRanges[1].substr(0, posOfDelimiterRange2));
		rangeExtrema[3] = std::stoi(elfRanges[1].substr(posOfDelimiterRange2 + 1, elfRanges[1].length()));
	}

	int GetNumberOfFullyContainedPairs() {
		std::ifstream cleaningPairIDsTxt(inputDataPath, std::ifstream::in);

		int totalContainedPairs = 0;
		//read out data
		if (cleaningPairIDsTxt.is_open())
		{
			std::string line{};

			while (std::getline(cleaningPairIDsTxt, line))
			{
				//position of delimter between both different ranges
				int posOfDelimiterBetweenRanges = line.find(",");

				std::string elfRanges[] { line.substr(0, posOfDelimiterBetweenRanges), line.substr(posOfDelimiterBetweenRanges + 1, line.length()) };

				//position of delimter in first range
				int posOfDelimiterInRange1 = elfRanges[0].find("-");

				//position of delimter in second range
				int posOfDelimiterInRange2 = elfRanges[1].find("-");

				//convert all numbers in the two ranges from string to int
				//ordered minElf1, maxElf1, minElf2, maxElf2
				int rangeExtrema[4];
				ConvertInputToInts(rangeExtrema, elfRanges, posOfDelimiterInRange1, posOfDelimiterInRange2);

				//if elf one's range is witin elf two's range
				if ((rangeExtrema[0] >= rangeExtrema[2] && rangeExtrema[1] <= rangeExtrema[3]) ||
					//if elf two's range is witin elf one's range
					(rangeExtrema[2] >= rangeExtrema[0] && rangeExtrema[3] <= rangeExtrema[1]))
					totalContainedPairs++;
			}

			//close file
			cleaningPairIDsTxt.close();
		}

		return totalContainedPairs;
	}

	int GetNumberOfOverlappingPairs() {
		std::ifstream cleaningPairIDsTxt(inputDataPath, std::ifstream::in);

		int totalOverlappingPairs = 0;
		//read out data
		if (cleaningPairIDsTxt.is_open())
		{
			std::string line{};

			while (std::getline(cleaningPairIDsTxt, line))
			{
				//position of delimter between both different ranges
				int posOfDelimiterBetweenRanges = line.find(",");

				std::string elfRanges[]{ line.substr(0, posOfDelimiterBetweenRanges), line.substr(posOfDelimiterBetweenRanges + 1, line.length()) };

				//position of delimter in first range
				int posOfDelimiterInRange1 = elfRanges[0].find("-");

				//position of delimter in second range
				int posOfDelimiterInRange2 = elfRanges[1].find("-");

				//convert all numbers in the two ranges from string to int
				//ordered minElf1, maxElf1, minElf2, maxElf2
				int rangeExtrema[4];
				ConvertInputToInts(rangeExtrema, elfRanges, posOfDelimiterInRange1, posOfDelimiterInRange2);

				//if elf one's min is within elf two's range
				if (((rangeExtrema[0] >= rangeExtrema[2] && rangeExtrema[0] <= rangeExtrema[3]) ||
					//or elf one's max is within elf two's range
					(rangeExtrema[1] >= rangeExtrema[2] && rangeExtrema[1] <= rangeExtrema[3])) ||
					//if elf two's min is within elf one's range
					((rangeExtrema[2] >= rangeExtrema[0] && rangeExtrema[3] <= rangeExtrema[1]) ||
					//or elf two's max is within elf one's range
					(rangeExtrema[3] >= rangeExtrema[0] && rangeExtrema[3] <= rangeExtrema[1])))
					totalOverlappingPairs++;
			}

			//close file
			cleaningPairIDsTxt.close();
		}

		return totalOverlappingPairs;
	}
}