#include "Day1.h"

#include <fstream>	//std::ifstream
#include <string>
#include <algorithm> //std::sort

namespace dayOne {
	/// <summary>
	/// returns the n highest calorie numbers the elfs are carrying
	/// </summary>
	/// <param name="n">Number of highest calorie numbers to return. 
	/// If n is bigger than the number of elfes, then the whole list gets returned</param>
	/// <returns>n highest calorie numbers</returns>
	std::vector<int> GetNMostCalories(int n) {

		//open file
		std::ifstream elfCaloriesTxt("./InputFiles/Day1_elfCalories.txt", std::ifstream::in);

		std::vector<int> elfCalories;
		//read out data
		if (elfCaloriesTxt.is_open())
		{
			int currentElfCalories = 0;
			std::string line{};

			while (std::getline(elfCaloriesTxt, line))
			{
				//line is empty once an elf is done being processed
				if (line.empty()) {
					elfCalories.push_back(currentElfCalories);

					currentElfCalories = 0;
				}
				else {
					//add this line's calories to the current elf calories
					currentElfCalories += std::stoi(line);
				}
			}

			//close file
			elfCaloriesTxt.close();
		}

		//sort the vector values
		std::sort(elfCalories.begin(), elfCalories.end(), elfCaloriesComparator);

		//only resize if n is smaller than total size to not add empty elemets
		if(n < elfCalories.size())
			elfCalories.resize(n);

		return elfCalories;
	}

	/// <summary>
	/// used to sort the vector of elf colories in descending order
	/// </summary>
	/// <param name="i">num 1</param>
	/// <param name="j">num 2</param>
	/// <returns>is num 1 bigger than num 2</returns>
	bool elfCaloriesComparator(int i, int j) { 
		return (i > j); 
	}
}