#include "Day15.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <sstream> 	//stringstream to read negative numbers from string
#include <regex>
#include <stdlib.h>     // abs
#include <unordered_set>
#include <set>


/// <summary>
/// This ended up not working because the array size got too large with my input data. Thus I had to create another solution for this task
/// </summary>

namespace dayFifteen {
	int rowToCheckForBeaconCoveredSpaces = 2000000;
	int maxRowsAndCollsOfCave = 4000000;
	//test data
	//int rowToCheckForBeaconCoveredSpaces = 10;
	//int maxRowsAndCollsOfCave = 20;

	struct hashFunctionPairs
	{
		size_t operator()(const std::pair<int, int>& pair) const
		{
			//return pair.first ^ pair.second;

			std::hash<int> hasher;
			std::size_t seed = 0;
			//basically does what boost::hash_combine does
			seed ^= hasher(pair.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hasher(pair.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};

	void ReadInputData(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& sensorBeacons) {
		std::ifstream distressSignal("./InputFiles/Day15_CaveBeacons.txt", std::ifstream::in);
		//std::ifstream distressSignal("./InputFiles/_Test.txt", std::ifstream::in);

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

				//add to input data vector
				sensorBeacons.push_back(std::pair<std::pair<int, int>, std::pair<int, int>> { {sensorX, sensorY}, { beaconX, beaconY } });
			}

			//close file
			distressSignal.close();
		}

	}

	int GetNumPositionsWithoutBeacon() {
		//a vector of pairs of coordinates, each paired x y -> {{{0, 1}, {1, 0}}, {{0, 2}, {2, 0}}}
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> sensorBeacons;
		ReadInputData(sensorBeacons);

		std::unordered_set<std::pair<int, int>, hashFunctionPairs> spacesCoveredBySensorsInRow;
		//iterate every sensor/beacon pair, and enter the spaces that this sensor covers
		for (std::pair<std::pair<int, int>, std::pair<int, int>> data : sensorBeacons) {
			//minX/Y to cast to array space
			int sensorX = data.first.first;
			int sensorY = data.first.second;
			int beaconX = data.second.first;
			int beaconY = data.second.second;

			int distance = abs(sensorY - beaconY) + abs(sensorX - beaconX);

			//if row to check is within the row of this sensor's coverage
			if (rowToCheckForBeaconCoveredSpaces >= sensorY - distance && rowToCheckForBeaconCoveredSpaces <= sensorY + distance) {
				for (int x = sensorX - distance + abs(sensorY - rowToCheckForBeaconCoveredSpaces); x <= sensorX + distance - abs(sensorY - rowToCheckForBeaconCoveredSpaces); x++) {
					spacesCoveredBySensorsInRow.insert(std::pair<int, int>{x, rowToCheckForBeaconCoveredSpaces});
				}
			}
		}

		//remove all spaces that are already covered by a beacon
		for (std::pair<std::pair<int, int>, std::pair<int, int>> data : sensorBeacons) {
			if (spacesCoveredBySensorsInRow.find(data.second) != spacesCoveredBySensorsInRow.end()) {
				spacesCoveredBySensorsInRow.erase(data.second);
			}
		}
		
		return spacesCoveredBySensorsInRow.size();
	}

	//didn't figure part 2 out on my own and essentially translated this solution https://www.reddit.com/r/adventofcode/comments/zmcn64/comment/j0b90nr/?utm_source=share&utm_medium=web2x&context=3 to C++
	//ToDo: works for test input, but doesn't work for actual input 
	unsigned long long GetInputFrequencyOfFreeSpace() {
		//a vector of pairs of coordinates, each paired x y -> {{{0, 1}, {1, 0}}, {{0, 2}, {2, 0}}}
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> sensorBeacons;
		ReadInputData(sensorBeacons);

		//std::unordered_set<int> acoeffs{}, bcoeffs{};
		std::vector<int> acoeffs{}, bcoeffs{};
		//iterate every sensor/beacon pair, and save the spaces that this sensor covers
		for (std::pair<std::pair<int, int>, std::pair<int, int>> data : sensorBeacons) {
			int sensorX = data.first.first;
			int sensorY = data.first.second;
			int beaconX = data.second.first;
			int beaconY = data.second.second;

			int radius = abs(sensorY - beaconY) + abs(sensorX - beaconX);

			/*
			acoeffs.insert(sensorY - sensorX + radius + 1);
			acoeffs.insert(sensorY - sensorX - radius - 1);
			bcoeffs.insert(sensorX + sensorY + radius + 1);
			bcoeffs.insert(sensorX + sensorY - radius - 1);
			*/

			acoeffs.push_back(sensorY - sensorX + radius + 1);
			acoeffs.push_back(sensorY - sensorX - radius - 1);
			bcoeffs.push_back(sensorX + sensorY + radius + 1);
			bcoeffs.push_back(sensorX + sensorY - radius - 1);
		}

		std::cout << acoeffs.size() << " " << bcoeffs.size() << std::endl;

		//acoeffs = { a for a in acoeffs if acoeffs.count(a) >= 2 }
		//	bcoeffs = { b for b in bcoeffs if bcoeffs.count(b) >= 2 }

		for (int a : acoeffs) {
			for (int b : bcoeffs)
			{
				//std::pair<int, int> p{(b-a)/2, (a+b)/2};
				std::pair<int, int> p{ (a + b) / 2, (b - a) / 2 };

				//std::cout << p.first << "|" << p.second << std::endl;
				if (0 <= p.first && p.first <= maxRowsAndCollsOfCave && 0 <= p.second && p.second <= maxRowsAndCollsOfCave) {
					bool distanceLargerThanAllRadii = true;
					for (std::pair<std::pair<int, int>, std::pair<int, int>> data : sensorBeacons) {
						int sensorX = data.first.first;
						int sensorY = data.first.second;
						int beaconX = data.second.first;
						int beaconY = data.second.second;

						int radius = abs(sensorY - beaconY) + abs(sensorX - beaconX);
						int distance =  abs(p.first - sensorX) + abs(p.second - sensorY);
						//int distance = abs(p.second - sensorX) + abs(p.first - sensorY);

						if (distance <= radius) {
							distanceLargerThanAllRadii = false;
							break;
						}
					}

					if (distanceLargerThanAllRadii) {
						std::cout << "Possible output found " << p.first << "|" << p.second << std::endl;
						//return maxRowsAndCollsOfCave * p.first + p.second;
						return 4000000 * p.first + p.second;
					}
				}
			}
		}

		std::cout << "not found" << std::endl;
		//not found
		return -1;
	}

	/*
	unsigned long long GetInputFrequencyOfFreeSpace() {
		//a vector of pairs of coordinates, each paired x y -> {{{0, 1}, {1, 0}}, {{0, 2}, {2, 0}}}
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> sensorBeacons;
		ReadInputData(sensorBeacons);

		int x = 0, y = 0;
		//scan cave from top to bottom
		for (y = 0; y < maxRowsAndCollsOfCave; y++) {
			std::unordered_set<int> xSpacesCoveredInRow;
			//optimization for counting intervals
			int minX = INT_MAX, maxX = 0;

			//iterate every sensor/beacon pair, and save the spaces that this sensor covers
			for (std::pair<std::pair<int, int>, std::pair<int, int>> data : sensorBeacons) {
				//minX/Y to cast to array space
				int sensorX = data.first.first;
				int sensorY = data.first.second;
				int beaconX = data.second.first;
				int beaconY = data.second.second;

				int distance = abs(sensorY - beaconY) + abs(sensorX - beaconX);

				//if row to check is within the row of this sensor's coverage
				if (y >= sensorY - distance && y <= sensorY + distance) {
					for (int x = sensorX - distance + abs(sensorY - y); x <= sensorX + distance - abs(sensorY - y); x++) {
						xSpacesCoveredInRow.insert(x);

						if (x < minX)
							minX = x;
						if (x > maxX)
							maxX = x;
					}
				}
			}

			int numOfIntervals = 0;
			bool ongoingIntervall = false;
			int xOfEmptyTile = 0;
			//count how many intervals of consecutively covered spaces there are in this row
			for (x = minX; x <= maxX; x++) {

				//x space is not covered
				if (xSpacesCoveredInRow.find(x) == xSpacesCoveredInRow.end()) {
					//repeaded blank space
					if (numOfIntervals >= 1 && !ongoingIntervall) {
						//this isn't the beacon we're looking for, too many blank spaces in a row
						numOfIntervals = -1;
						break;
					}
					//intervall ended
					if (numOfIntervals >= 1 && ongoingIntervall) {
						ongoingIntervall = false;

						xOfEmptyTile = x;
					}
				}
				//x is covered
				else {
					if (numOfIntervals >= 2 && !ongoingIntervall) {
						numOfIntervals = -1;
						break;
					}
					else if (!ongoingIntervall) {
						ongoingIntervall = true;
						numOfIntervals++;
					}
				}
			}

			//y and x have been found
			if (numOfIntervals == 2) {
				x = xOfEmptyTile;
				break;
			}
		}

		//can be found by multiplying the beacons x coordinate by 4000000 and then adding its y coordinate
		return x * 4000000ull + y;
	}
	*/
}