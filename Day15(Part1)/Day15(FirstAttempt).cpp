#include "Day15(FirstAttempt).h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <sstream> 	//stringstream to read negative numbers from string
#include <regex>
#include <stdlib.h>     // abs
#include <unordered_set>

/// <summary>
/// This ended up not working because the array size got too large with my input data. Thus I had to create another solution for this task
/// </summary>

namespace dayFifteenOLD {
	int rowToCheck = 10;

	struct hashFunctionPairs
	{
		size_t operator()(const std::pair<int,int>& pair) const
		{
			return pair.first ^ pair.second;
		}
	};

	int GetPositionsWhereBeaconsCanNotBePresenetedInRow() {
		//std::ifstream distressSignal("./InputFiles/Day15_CaveBeacons.txt", std::ifstream::in);
		std::ifstream distressSignal("./InputFiles/_Test.txt", std::ifstream::in);
		//rowToCheck = 10;

		int maxX = INT_MIN, minX = INT_MAX;
		int maxY = INT_MIN, minY = INT_MAX;

		//a vector of pairs of coordinates, each paired x y -> {{{0, 1}, {1, 0}}, {{0, 2}, {2, 0}}}
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> inputData;
		//read out data and figure out how big the array has to be to display all
		if (distressSignal.is_open())
		{
			std::string line{};
			std::string delimiter = "=";

			//generate cave
			while (std::getline(distressSignal, line)) {
				//remove all from the input line but numbers, - signs and = signs
				line = std::regex_replace(line, std::regex("[^0-9-=]"), "");
				//remove first '='
				line.erase(0, 1);

				std::stringstream lineAsStream(line);
				std::string segment;

				int sensorX = 0, sensorY = 0, beaconX = 0, beaconY = 0;
				//read line while taking segments each =
				std::getline(lineAsStream, segment, '=');
				std::stringstream(segment) >> sensorX;

				//read line while taking segments each =
				std::getline(lineAsStream, segment, '=');
				std::stringstream(segment) >> sensorY;

				//read line while taking segments each =
				std::getline(lineAsStream, segment, '=');
				std::stringstream(segment) >> beaconX;

				//read line while taking segments each =
				std::getline(lineAsStream, segment, '=');
				std::stringstream(segment) >> beaconY;

				//set up max and min values to be able to initialize the array size need later
				int distance = abs(sensorY - beaconY) + abs(sensorX - beaconX);

				//is value bigger than current max?
				if (sensorX + distance > maxX)
					maxX = sensorX + distance;
				if (sensorY + distance > maxY)
					maxY = sensorY + distance;
				//smaller than current min?
				if (sensorX - distance < minX)
					minX = sensorX - distance;
				if (sensorY - distance < minY)
					minY = sensorY - distance;

				//add to input data vector
				inputData.push_back(std::pair<std::pair<int, int>, std::pair<int, int>> { {sensorX, sensorY}, {beaconX, beaconY} });
			}

			//close file
			distressSignal.close();
		}

		//maxX - minX + 1 is the exact num of calls needed to have enough space for all sensor ranges
		int cols = maxX - minX + 1;
		//maxY - minY + 1 is the exact num of calls needed to have enough space for all sensor ranges
		int rows = maxY - minY + 1;

		//bool spaceOccupied[maxX - minX][maxY - minY];
		bool* spaceOccupied = (bool*)malloc(cols * rows * sizeof(bool));
		for (int i = 0; i < cols * rows; i++)
			spaceOccupied[i] = false;
		//spaceOccupied[x + fromY * cols]

		//iterate every sensor/beacon pair, and enter the spaces that this sensor covers
		for (std::pair<std::pair<int, int>, std::pair<int, int>> data : inputData) {
			//minX/Y to cast to array space
			int sensorX = data.first.first - minX;
			int sensorY = data.first.second - minY;
			int beaconX = data.second.first - minX;
			int beaconY = data.second.second - minY;

			int distance = abs(sensorY - beaconY) + abs(sensorX - beaconX);

			for (int y = sensorY - distance; y <= sensorY + distance; y++) {
				for (int x = sensorX - distance + abs(sensorY - y); x <= sensorX + distance - abs(sensorY - y); x++) {
					spaceOccupied[x + y * cols] = true;
				}
			}
		}

		printSensorRanges(inputData, spaceOccupied, cols, rows, minX, maxX, minY, maxY);

		//count together all spaces without a beacon
		int numOfSpacesWithoutBeacon = 0;
		for (int x = 0; x < cols; x++) {
			//cast to array space
			if (spaceOccupied[x + (rowToCheck - minY) * cols] == true)
				numOfSpacesWithoutBeacon++;
		}

		std::unordered_set<std::pair<int, int>, hashFunctionPairs> foundBeacons;
		//and substract all spaces that actually do include a beacon
		for (std::pair<std::pair<int, int>, std::pair<int, int>> data : inputData) {
			//minY to cast to array space
			int beaconY = data.second.second - minY;

			//but not the ones that were already substracted
			if (foundBeacons.find(data.second) == foundBeacons.end() && beaconY == (rowToCheck - minY)) {
				foundBeacons.insert(data.second);
				numOfSpacesWithoutBeacon--;
			}
		}

		free(spaceOccupied);

		return numOfSpacesWithoutBeacon;
	}

	//only works for test data, the actual data gets way too big
	void printSensorRanges(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& inputData, bool* spaceOccupied, int cols, int rows, int minX, int maxX, int minY, int maxY) {
		std::string debug{};
		
		//print cave
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {

				if (spaceOccupied[x + y * cols] == true)
					debug += "#";
				else
					debug += ".";
			}
			debug += "\n";
		}
		
		//change chars at beacon and sensor points to B and S
		for (std::pair<std::pair<int, int>, std::pair<int, int>> data : inputData) {
			//minX/Y to cast to array space
			int sensorX = data.first.first - minX;
			int sensorY = data.first.second - minY;
			int beaconX = data.second.first - minX;
			int beaconY = data.second.second - minY;

			//+y because we have +1 char per row cause of \n
			debug[sensorX + sensorY * cols + sensorY] = 'S';
			debug[beaconX + beaconY * cols + beaconY] = 'B';
		}

		std::cout << debug << std::endl;
	}
}