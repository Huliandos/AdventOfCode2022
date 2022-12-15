#include "DayFourteen.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <stack>
#include <vector>

namespace dayFourteen {
	bool endlessAbyss = true;
	int sandSpawnX = 500, sandSpawnY = 0;

	int GetUnitsOfSandBeforeOverflow(bool endlessAbyssInput) {
		std::ifstream distressSignal("./InputFiles/DayFourteen_Cavesystem.txt", std::ifstream::in);
		//std::ifstream distressSignal("./InputFiles/_Test.txt", std::ifstream::in);
		
		/* old way for part 1
		//set by debugging all possible input values and finding min and max height. +/- 1 to each side so sand can overflow in those directions
		//min y is always 0 cause that's where the sand is pouring from
		//proper input data
		int maxX = 552, minX = 491;
		int cols = maxX - minX;
		//==max Y+1
		int rows = 178;

		//test data
		//int maxX = 504, minX = 493;
		//int cols = maxX - minX;
		//int rows = 10;
		*/

		int maxX = 1000, minX = 0;
		int cols = maxX - minX;
		//==max Y+1
		int rows = 178;

		//test data
		/*
		int maxX = 520, minX = 480;
		int cols = maxX - minX;
		//==max Y+1
		int rows = 10;
		*/

		endlessAbyss = endlessAbyssInput;
		sandSpawnX = 500 - minX;
		sandSpawnY = 0;

		//if there's no endless abyss at the bottom, then there's two more columns
		if (!endlessAbyss)
			rows += 2;

		//bool spaceOccupied[maxX - minX][maxY - minY];
		bool* spaceOccupied = (bool*)malloc(cols * rows * sizeof(bool));
		for (int i = 0; i < cols * rows; i++)
			spaceOccupied[i] = false;

		//read out data
		if (distressSignal.is_open())
		{
			std::string line{};
			std::string coordinatesDelimiter = " -> ";
			std::string yxDelimiter = ",";

			int fromX = 0, toX = 0, fromY = 0, toY = 0;

			//generate cave
			while (std::getline(distressSignal, line)) {
				std::string token = line.substr(0, line.find(coordinatesDelimiter));

				int posOfComma = token.find(yxDelimiter);

				//-min x and min y to cast it to our array, as it starts from 0, but the data starts from much higher values (x: 492, y: 13)
				fromX = std::stoi(line.substr(0, posOfComma)) - minX;
				fromY = std::stoi(line.substr(posOfComma + 1, token.size() - (posOfComma + 1)));

				line.erase(0, token.size() + coordinatesDelimiter.size());

				//interpret current line and add all its walls to the maze
				while (line.size() != 0) {
					token = line.substr(0, line.find(coordinatesDelimiter));

					int posOfComma = token.find(yxDelimiter);

					toX = std::stoi(line.substr(0, posOfComma)) - minX;
					toY = std::stoi(line.substr(posOfComma + 1, token.size() - (posOfComma + 1)));

					line.erase(0, token.size() + coordinatesDelimiter.size());

					//set positions in the maze to true
					//horizontal line
					if (fromY == toY) {
						//check if the data goes left to right or right to left
						int smallerX = 0, largerX;
						if (fromX < toX) {
							smallerX = fromX;
							largerX = toX;
						}
						else {
							smallerX = toX;
							largerX = fromX;
						}

						for (int x = smallerX; x <= largerX; x++) {
							spaceOccupied[x * rows + fromY] = true;
						}
					}
					//vertical line
					else {
						//check if the data goes top to bottom or bottom to top
						int smallerY = 0, largerY;
						if (fromY < toY) {
							smallerY = fromY;
							largerY = toY;
						}
						else {
							smallerY = toY;
							largerY = fromY;
						}

						for (int y = smallerY; y <= largerY; y++) {
							spaceOccupied[fromX * rows + y] = true;
						}
					}

					fromX = toX;
					fromY = toY;
				}
			}

			//close file
			distressSignal.close();
		}

		//if there's no endless abyss at the bottom, then there's floor on the bottom
		if (!endlessAbyss) {
			for (int x = 0; x < cols; x++) {
				spaceOccupied[x * rows + (rows-1)] = true;
			}
		}

		//std::cout << "=== BEFORE SAND FALLING ===" << std::endl;
		//printCave(spaceOccupied, cols, rows);

		//means: if endless abyss then the start sand spawned is 0, else it's 1
		//1 because the last sand spawned isn't counted by the loop in case of no abyss
		int sandSpawned = int(!endlessAbyss);
		while (true) {
			//sand hit the abyss, leave the loop
			if (SimulateSandDrop(spaceOccupied, sandSpawnX, sandSpawnY, rows) == true) {
				break;
			}
			//sand came to rest, drop another piece of sand
			sandSpawned++;
		}

		//std::cout << "=== AFTER SAND FALLING ===" << std::endl;
		//printCave(spaceOccupied, cols, rows);

		free(spaceOccupied);

		return sandSpawned;
	}

	bool SimulateSandDrop(bool* spaceOccupied, int xSand, int ySand, int cols) {
		//sand is at the bottom and it's an endless abyss
		if (endlessAbyss && ySand == cols)
			return true;

		//space below isn't occupied (higher y value is lower in the cave)
		if (spaceOccupied[xSand * cols + (ySand + 1)] == false)
			//recursively call this
			return SimulateSandDrop(spaceOccupied, xSand, ySand + 1, cols);
		//space below and to the left isn't occupied
		if (spaceOccupied[(xSand - 1) * cols + (ySand + 1)] == false)
			//recursively call this
			return SimulateSandDrop(spaceOccupied, (xSand - 1), ySand + 1, cols);
		//space below and to the right isn't occupied
		if (spaceOccupied[(xSand + 1) * cols + (ySand + 1)] == false)
			//recursively call this
			return SimulateSandDrop(spaceOccupied, (xSand + 1), ySand + 1, cols);

		//sand came to rest
		spaceOccupied[xSand * cols + ySand] = true;

		//sand came to rest at the entrance of the hole
		if (!endlessAbyss && ySand == sandSpawnY && xSand == sandSpawnX) {
			return true;
		}

		return false;
	}

	void printCave(bool* spaceOccupied, int rows, int cols) {
		//print cave
		for (int y = 0; y < cols; y++) {
			for (int x = 0; x < rows; x++) {
				if (spaceOccupied[x * cols + y] == true)
					std::cout << "#";
				else
					std::cout << ".";
			}
			std::cout << std::endl;
		}
	}
}