#include "Day16.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <sstream> 	//stringstream to read negative numbers from string
#include <regex>
#include <stdlib.h>     // abs
#include <unordered_set>
#include <set>
#include <vector>


/// <summary>
/// TODO
/// </summary>

namespace daySixteen{
	int ReadInputData() {
		std::ifstream distressSignal("./InputFiles/Day16_Valves.txt", std::ifstream::in);
		//std::ifstream distressSignal("./InputFiles/_Test.txt", std::ifstream::in);

		//read out data and figure out how big the array has to be to display all
		if (distressSignal.is_open())
		{
			std::string line{};

			//generate cave
			while (std::getline(distressSignal, line)) {

			}

			//close file
			distressSignal.close();
		}

		return 0;
	}
}