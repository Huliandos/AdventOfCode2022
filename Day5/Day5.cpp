#include "Day5.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <stack>

namespace dayFive {
	std::string inputDataPath = "./InputFiles/Day5_SupplyStacks.txt";

	/// <summary>
	/// reads the input file, creates stacks of items out of it, and shuffles them according to the commands of the input file. Then it returns the tops of each stack
	/// </summary>
	/// <param name="craneIsCrateMover9000">a create mover 9000 can only move a single crate at the time, a crate mover 9001 can move multiple crates at a time</param>
	/// <returns></returns>
	std::vector<char> GetTopsOfStacksAfterMoving(bool craneIsCrateMover9000) {
		std::ifstream cargoStacksTxt(inputDataPath, std::ifstream::in);
		std::vector<char> cargoOnTopOfEachStack;

		//read out data
		if (cargoStacksTxt.is_open())
		{
			std::string line{};

			std::vector<std::string> cargoAsString;

			//get first line of the cargo
			std::getline(cargoStacksTxt, line);

			//while we're still parsing the cargo part of the input
			while (!line.empty())
			{
				cargoAsString.push_back(line);
				std::getline(cargoStacksTxt, line);
			}
 
			//remove the last string, as it just contains the number of each row
			cargoAsString.pop_back();

			std::stack<char> cargoStacks[9];

			//iterate through the cargo from back to front
			for (int i = cargoAsString.size() - 1; i >= 0; i--) {
				//the input is set up so that each cargo of every stack can be found after 4 characters, starting from the character on position 1
				for (int j = 1; j < cargoAsString[i].size(); j+=4) {
					//Empty char means that no cargo should be added to this stack anymore
					if (cargoAsString[i][j] != ' ') {
						//(j-1)/4 is used so we remove the offset created in the loop, and asign the data to cargo stacks 0-8
						cargoStacks[(j-1)/ 4].push(cargoAsString[i][j]);
					}
				}
			}

			//iterate through the rest of the commands to process all the cargo moving
			while (std::getline(cargoStacksTxt, line))
			{
				//can always remove first 5 chars "move "
				line.erase(0, 5);
				//find delimiter pos
				int delimiterPos = line.find(" ");

				//convert first number to amount to be moved
				int amount = std::stoi(line.substr(0, delimiterPos));

				//can always remove 6 chars " from " + the letters up to the and including the delimiter
				line.erase(0, 6+delimiterPos);
				//find next delimiter pos
				delimiterPos = line.find(" ");

				//convert second number to stack to be moved from
				//-1 because the txt assumes stacks are indexed from 1-9, but we index arrays 0-8
				int stackToRemoveFrom = std::stoi(line.substr(0, delimiterPos))-1;

				//can always remove 4 chars " to " + the letters up to the and including the delimiter
				line.erase(0, 4 + delimiterPos);
				//find next delimiter pos
				delimiterPos = line.find(" ");

				//convert second number to stack to be moved from
				//-1 because the txt assumes stacks are indexed from 1-9, but we index arrays 0-8
				int stackToAddTo = std::stoi(line.substr(0, delimiterPos))-1;

				if (craneIsCrateMover9000) {
					for (int i = 0; i < amount; i++) {
						//get character
						char c = cargoStacks[stackToRemoveFrom].top();
						//remove from stack
						cargoStacks[stackToRemoveFrom].pop();
						//move to other stack
						cargoStacks[stackToAddTo].push(c);
					}
				}
				else {
					std::vector<char> cratesToMove;
					for (int i = 0; i < amount; i++) {
						//get character and push into vector
						cratesToMove.push_back(cargoStacks[stackToRemoveFrom].top());
						//remove from stack
						cargoStacks[stackToRemoveFrom].pop();
					}
					
					//this retains the ordering of the crate, and thus emulates moving mutliple crates at a time
					for(int i = cratesToMove.size()-1; i>=0; i--)
						cargoStacks[stackToAddTo].push(cratesToMove[i]);
				}
			}

			//Add the top of each stack to output
			for (std::stack<char> cargoStack : cargoStacks) {
				cargoOnTopOfEachStack.push_back(cargoStack.top());
			}

			//close file
			cargoStacksTxt.close();
		}

		return cargoOnTopOfEachStack;
	}
}