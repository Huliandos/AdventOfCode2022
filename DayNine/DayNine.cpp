#include "DayNine.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <unordered_set>
#include <stdlib.h>     // abs
#include <algorithm>	//clamp

namespace dayNine {
	Position::Position(int x, int y) : x(x), y(y) {}

	bool Position::operator == (const Position& point) const {
		return (point.x == x) && (point.y == y);
	}

	size_t PositionHash::operator () (const Position& pos) const {
		std::hash<int> hasher;
		std::size_t seed = 0;
		//basically does what boost::hash_combine does
		seed ^= hasher(pos.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= hasher(pos.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}

	int GetNumOfPositionsVisited(int numOfKnotsInRope) {
		std::ifstream movementInstructions("./InputFiles/DayNine_RopeMovements.txt", std::ifstream::in);
		//std::ifstream movementInstructions("./InputFiles/_Test.txt", std::ifstream::in);

		Position* knots = (Position*)malloc(numOfKnotsInRope * sizeof(Position));
		
		//init knots at 0/0
		for (int i = 0; i < numOfKnotsInRope; i++)
			new (knots + i)Position(0, 0);

		std::unordered_set<Position, PositionHash> tailPositionsVisited;
		//add start position of tail
		tailPositionsVisited.insert(knots[numOfKnotsInRope-1]);

		//read out data
		if (movementInstructions.is_open())
		{
			std::string line{};

			//Get input lines
			while (std::getline(movementInstructions, line)) {
				//iterations are everything in the line from character 2 on out
				int iterations = std::stoi(line.substr(2, line.size()-2));
				int horizontalMovement = 0, verticalMovement = 0;

				switch (line[0]) {
					//up
					case 'U':
						verticalMovement = 1;
						break;
					//down
					case 'D':
						verticalMovement = -1;
						break;
					//left
					case 'L':
						horizontalMovement = -1;
						break;
					//right, case R
					default:
						horizontalMovement = 1;
						break;
				}

				for (int i = 0; i < iterations; i++) {
					//move head
					knots[0].x += horizontalMovement;
					knots[0].y += verticalMovement;

					//move all knots in the row according the knot before it
					for (int i = 1; i < numOfKnotsInRope; i++)
						CheckMoveFollowing(knots[i], knots[i-1]);
					
					//add position of tail to unordered set (only adds non duplicates)
					tailPositionsVisited.insert(knots[numOfKnotsInRope - 1]);
				}
			}

			//close file
			movementInstructions.close();
		}

		//free up memory
		for (int i = 0; i < numOfKnotsInRope; i++)
			knots[i].~Position();
		free(knots);

		return tailPositionsVisited.size();
	}

	void CheckMoveFollowing(Position& following, Position& leading) {
		//once the following rope reaches distance 2 on any of its axis
		if ((abs(following.x - leading.x) >= 2) || (abs(following.y - leading.y) >= 2)) {
			//move one step towards the leading rope
			//clamp movement between -1 and 1
			following.x += std::max(-1, std::min(leading.x - following.x, 1));;
			following.y += std::max(-1, std::min(leading.y - following.y, 1));;
		}
	}
}