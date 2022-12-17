#include "Day10.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <sstream>	//stringstream to read negative numbers from string

namespace dayTen {
	std::string inputFile = "./InputFiles/Day10_CPUInstructions.txt";
	//std::string inputFile = "./InputFiles/_Test.txt";

	int GetTotalSignalStrength() {
		std::ifstream movementInstructions(inputFile, std::ifstream::in);

		int totalSignalStrength = 0;
		//read out data
		if (movementInstructions.is_open())
		{
			std::string line{};

			int xRegister = 1;
			int cycle = 0;
			int cycleToGetSignalStrengthFrom = 20;

			//Get input lines
			while (std::getline(movementInstructions, line)) {

				//first 4 chars are the command
				std::string command = line.substr(0, 4);

				if (command == "noop")
					RunCycle(cycle, totalSignalStrength, cycleToGetSignalStrengthFrom, xRegister);
				//command is addx
				else {
					RunCycle(cycle, totalSignalStrength, cycleToGetSignalStrengthFrom, xRegister);
					RunCycle(cycle, totalSignalStrength, cycleToGetSignalStrengthFrom, xRegister);
					int addToRegister = 0;
					//everything after 5th char is whatever is added by the addx command
					std::stringstream(line.substr(5, line.size() - 5)) >> addToRegister;
					xRegister += addToRegister;
				}
			}

			//close file
			movementInstructions.close();
		}

		return totalSignalStrength;
	}

	std::string GenerateSprite() {
		std::ifstream movementInstructions(inputFile, std::ifstream::in);

		std::string CRTScreen{};
		//read out data
		if (movementInstructions.is_open())
		{
			std::string line{};

			int xRegister = 1;
			int cycle = 0;

			//Get input lines
			while (std::getline(movementInstructions, line)) {

				//first 4 chars are the command
				std::string command = line.substr(0, 4);

				if (command == "noop")
					RunCycle(cycle, CRTScreen, xRegister);
				//command is addx
				else {
					RunCycle(cycle, CRTScreen, xRegister);
					RunCycle(cycle, CRTScreen, xRegister);

					int addToRegister = 0;
					//everything after 5th char is whatever is added by the addx command
					std::stringstream(line.substr(5, line.size() - 5)) >> addToRegister;
					xRegister += addToRegister;
				}
			}

			//close file
			movementInstructions.close();
		}

		return CRTScreen;
	}

	/// <summary>
	/// calculates the max signal strength and sets the next step to take signal strength from
	/// </summary>
	/// <param name="cycle"></param>
	/// <param name="totalSignalStrength"></param>
	/// <param name="cycleToGetSignalStrengthFrom"></param>
	/// <param name="xRegister"></param>
	void RunCycle(int& cycle, int& totalSignalStrength, int& cycleToGetSignalStrengthFrom, int xRegister) {
		cycle++;

		if (cycle % cycleToGetSignalStrengthFrom == 0) {
			totalSignalStrength += xRegister * cycleToGetSignalStrengthFrom;
			cycleToGetSignalStrengthFrom += 40;
		}
	}

	/// <summary>
	/// Generates the output screen as a string
	/// </summary>
	/// <param name="cycle">cycle of CPU</param>
	/// <param name="output">output screen</param>
	/// <param name="xRegister">Value of xRegister</param>
	void RunCycle(int& cycle, std::string& output, int xRegister) {
		int cycleMappedToScreensize = cycle % 40;

		//if the cyclse is in range to the register
		if (cycleMappedToScreensize >= xRegister - 1 && cycleMappedToScreensize <= xRegister + 1)
			output += "#";
		else
			output += ".";

		cycle++;

		//end of screen width
		if (cycle % 40 == 0)
			output += "\n";
	}
}