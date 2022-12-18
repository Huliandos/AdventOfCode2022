#include "Day18.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <sstream>

namespace dayEighteen {
	int minX, maxX, minY, maxY, minZ, maxZ;

	void GenerateLavaBubbel(std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple>& lavaCoordinates) {
		std::ifstream lavaCoordinatesInput("./InputFiles/Day18_LavaCoordinates.txt", std::ifstream::in);
		//std::ifstream lavaCoordinatesInput("./InputFiles/_Test.txt", std::ifstream::in);

		//read out data and figure out how big the array has to be to display all
		if (lavaCoordinatesInput.is_open())
		{
			std::string delimiter = ",";
			std::string line{};
			//there's only one line, so this happens just once
			while (std::getline(lavaCoordinatesInput, line)) {
				std::tuple<int, int, int> tuple{ 0, 0, 0 };

				int last = 0, next = 0;
				next = line.find(delimiter, last);
				std::get<0>(tuple) = std::stoi(line.substr(last, next - last));
				last = next + 1;

				next = line.find(delimiter, last);
				std::get<1>(tuple) = std::stoi(line.substr(last, next - last));
				last = next + 1;

				std::get<2>(tuple) = std::stoi(line.substr(last));

				lavaCoordinates.insert(tuple);
			}

			//close file
			lavaCoordinatesInput.close();
		}
	
	}

	int GetSurfraceAreaOfLavaDrop() {
		std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple> lavaCoordinates;

		GenerateLavaBubbel(lavaCoordinates);

		int surfaceArea = 0;
		for (std::tuple<int, int, int> tuple : lavaCoordinates) {
			//no right neighbor?
			if (lavaCoordinates.find({ std::get<0>(tuple) + 1, std::get<1>(tuple), std::get<2>(tuple) }) == lavaCoordinates.end())
				surfaceArea++;
			//no left neighbor?
			if (lavaCoordinates.find({ std::get<0>(tuple) - 1, std::get<1>(tuple), std::get<2>(tuple) }) == lavaCoordinates.end())
				surfaceArea++;
			//no above neighbor?
			if (lavaCoordinates.find({ std::get<0>(tuple), std::get<1>(tuple) + 1, std::get<2>(tuple) }) == lavaCoordinates.end())
				surfaceArea++;
			//no below neighbor?
			if (lavaCoordinates.find({ std::get<0>(tuple), std::get<1>(tuple) - 1, std::get<2>(tuple) }) == lavaCoordinates.end())
				surfaceArea++;
			//no ahead neighbor?
			if (lavaCoordinates.find({ std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple) + 1 }) == lavaCoordinates.end())
				surfaceArea++;
			//no behind neighbor?
			if (lavaCoordinates.find({ std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple) - 1 }) == lavaCoordinates.end())
				surfaceArea++;
		}

		return surfaceArea;
	}

	int GetSurfaceAreaOfLeaveDropExterior() {
		std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple> lavaCoordinates;
		std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple> exterior;

		GenerateLavaBubbel(lavaCoordinates);

		minX = INT_MAX; 
		maxX = 0;
		minY = INT_MAX;
		maxY = 0;
		minZ = INT_MAX;
		maxZ = 0;

		//find min and max borders

		for (std::tuple<int, int, int> tuple : lavaCoordinates) {
			if (std::get<0>(tuple) < minX)
				minX = std::get<0>(tuple);
			if (std::get<0>(tuple) > maxX)
				maxX = std::get<0>(tuple);
			if (std::get<1>(tuple) < minY)
				minY = std::get<1>(tuple);
			if (std::get<1>(tuple) > maxY)
				maxY = std::get<1>(tuple);
			if (std::get<2>(tuple) < minZ)
				minZ = std::get<2>(tuple);
			if (std::get<2>(tuple) > maxZ)
				maxZ = std::get<2>(tuple);
		}
		 
		//flood fill around the bubble by starting at a position that's definitely not in the bubble
		FloodFillAroundBubble(std::tuple<int, int, int> { minX - 1, minY - 1, minZ - 1 }, lavaCoordinates, exterior);

		int exteriorSurfaceArea = 0;
		//iterate each lava coordinate and see if its neighbors touch the exterior
		for (std::tuple<int, int, int> tuple : lavaCoordinates) {
			//no right neighbor?
			if (exterior.find({ std::get<0>(tuple) + 1, std::get<1>(tuple), std::get<2>(tuple) }) != exterior.end())
				exteriorSurfaceArea++;
			//no left neighbor?
			if (exterior.find({ std::get<0>(tuple) - 1, std::get<1>(tuple), std::get<2>(tuple) }) != exterior.end())
				exteriorSurfaceArea++;
			//no above neighbor?
			if (exterior.find({ std::get<0>(tuple), std::get<1>(tuple) + 1, std::get<2>(tuple) }) != exterior.end())
				exteriorSurfaceArea++;
			//no below neighbor?
			if (exterior.find({ std::get<0>(tuple), std::get<1>(tuple) - 1, std::get<2>(tuple) }) != exterior.end())
				exteriorSurfaceArea++;
			//no ahead neighbor?
			if (exterior.find({ std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple) + 1 }) != exterior.end())
				exteriorSurfaceArea++;
			//no behind neighbor?
			if (exterior.find({ std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple) - 1 }) != exterior.end())
				exteriorSurfaceArea++;
		}

		return exteriorSurfaceArea;
	}

	/*
	// Recursive flood fill. Lead to stack overflow so wasn't useable
	void FloodFillAroundBubble(const std::tuple<int, int, int>& tuple, const std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple>& lavaCoordinates, std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple>& exterior)
	{
		if (std::get<0>(tuple) >= minX - 1 && std::get<1>(tuple) >= minY - 1 && std::get<2>(tuple) >= minZ - 1 &&
			std::get<0>(tuple) <= maxX + 1 && std::get<1>(tuple) <= maxY + 1 && std::get<2>(tuple) <= maxZ + 1 &&
			lavaCoordinates.find(tuple) == lavaCoordinates.end() &&
			exterior.find(tuple) == exterior.end()) {

			exterior.insert(tuple);
			
			//recursively call for each neighbor
			//right
			//FloodFillAroundBubble(std::tuple<int, int, int> { std::get<0>(tuple) + 1, std::get<1>(tuple), std::get<2>(tuple) }, lavaCoordinates, exterior);
			//left
			FloodFillAroundBubble(std::tuple<int, int, int> { std::get<0>(tuple) - 1, std::get<1>(tuple), std::get<2>(tuple) }, lavaCoordinates, exterior);
			//above
			//FloodFillAroundBubble(std::tuple<int, int, int> { std::get<0>(tuple), std::get<1>(tuple) + 1, std::get<2>(tuple) }, lavaCoordinates, exterior);
			//below
			FloodFillAroundBubble(std::tuple<int, int, int> { std::get<0>(tuple), std::get<1>(tuple) - 1, std::get<2>(tuple) }, lavaCoordinates, exterior);
			//ahead
			FloodFillAroundBubble(std::tuple<int, int, int> { std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple) + 1 }, lavaCoordinates, exterior);
			//behind
			FloodFillAroundBubble(std::tuple<int, int, int> { std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple) - 1 }, lavaCoordinates, exterior);
		}
	}
	*/

	//iteratively
	void FloodFillAroundBubble(const std::tuple<int, int, int>& tuple, const std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple>& lavaCoordinates, std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple>& exterior)
	{
		std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple> checkedTuples, tuplesToCheck;

		tuplesToCheck.insert(tuple);

		while (tuplesToCheck.size() != 0)
		{
			std::tuple<int, int, int> currentTuple = *tuplesToCheck.begin();

			if (std::get<0>(currentTuple) >= minX - 1 && std::get<1>(currentTuple) >= minY - 1 && std::get<2>(currentTuple) >= minZ - 1 &&
				std::get<0>(currentTuple) <= maxX + 1 && std::get<1>(currentTuple) <= maxY + 1 && std::get<2>(currentTuple) <= maxZ + 1 &&
				lavaCoordinates.find(currentTuple) == lavaCoordinates.end() &&
				exterior.find(currentTuple) == exterior.end()) 
			{
				exterior.insert(currentTuple);

				//add neighbors to tuples to check if they aren't contained in it
				//right
				std::tuple<int, int, int> neighbor = std::tuple<int, int, int>{ std::get<0>(currentTuple) + 1, std::get<1>(currentTuple), std::get<2>(currentTuple) };
				if (checkedTuples.find(neighbor) == checkedTuples.end()) {
					//doesn't insert if it's not already contained, so we can ignore this call here
					tuplesToCheck.insert(neighbor);
				}

				//left
				neighbor = std::tuple<int, int, int>{ std::get<0>(currentTuple) - 1, std::get<1>(currentTuple), std::get<2>(currentTuple) };
				if (checkedTuples.find(neighbor) == checkedTuples.end()) {
					//doesn't insert if it's not already contained, so we can ignore this call here
					tuplesToCheck.insert(neighbor);
				}

				//above
				neighbor = std::tuple<int, int, int>{ std::get<0>(currentTuple), std::get<1>(currentTuple) + 1, std::get<2>(currentTuple) };
				if (checkedTuples.find(neighbor) == checkedTuples.end()) {
					//doesn't insert if it's not already contained, so we can ignore this call here
					tuplesToCheck.insert(neighbor);
				}

				//below
				neighbor = std::tuple<int, int, int>{ std::get<0>(currentTuple), std::get<1>(currentTuple) - 1, std::get<2>(currentTuple) };
				if (checkedTuples.find(neighbor) == checkedTuples.end()) {
					//doesn't insert if it's not already contained, so we can ignore this call here
					tuplesToCheck.insert(neighbor);
				}

				//ahead
				neighbor = std::tuple<int, int, int>{ std::get<0>(currentTuple), std::get<1>(currentTuple), std::get<2>(currentTuple) + 1};
				if (checkedTuples.find(neighbor) == checkedTuples.end()) {
					//doesn't insert if it's not already contained, so we can ignore this call here
					tuplesToCheck.insert(neighbor);
				}

				//behind
				neighbor = std::tuple<int, int, int>{ std::get<0>(currentTuple), std::get<1>(currentTuple), std::get<2>(currentTuple) - 1};
				if (checkedTuples.find(neighbor) == checkedTuples.end()) {
					//doesn't insert if it's not already contained, so we can ignore this call here
					tuplesToCheck.insert(neighbor);
				}
			}

			checkedTuples.insert(currentTuple);
			tuplesToCheck.erase(currentTuple);
		}
	}
}