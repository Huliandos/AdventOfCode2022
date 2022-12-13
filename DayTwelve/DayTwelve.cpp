#include "DayTwelve.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <math.h>	//pow, sqrt
#include <stdexcept>

namespace dayTwelve {
	Tile::Tile(int x, int y, int height) {
		this->x = x;
		this->y = y;
		this->height = height;

		costFromStart = 0;
		airDistance = 0;
	}

	int GetMinNumOfNodesToVisit(bool justInputMarket_S_IsStart) {
		std::ifstream hillMap("./InputFiles/DayTwelve_HillMap.txt", std::ifstream::in);
		//std::ifstream hillMap("./InputFiles/_Test.txt", std::ifstream::in);

		std::vector<std::vector<Tile*>> heightMap;
		std::vector <Tile*> startTiles;
		Tile* goalTile = NULL;

		//read out data
		if (hillMap.is_open())
		{
			std::string line{};


			//Get input lines and convert to graph
			int y = 0;
			while (std::getline(hillMap, line)) {

				std::vector<Tile*> row;

				for (int x = 0; x < line.size(); x++) {
					if (line[x] == 'S') {
						Tile* startTile = new Tile{ x, y, 0 };
						startTiles.push_back(startTile);
						row.push_back(startTile);
					}
					else if (line[x] == 'E') {
						goalTile = new Tile{ x, y, 25 };
						row.push_back(goalTile);
					}
					else {
						//cast character to int ranging from 0-31
						Tile* tile = new Tile{ x, y, line[x] - 'a' };
						row.push_back(tile);
						//also add a's to the possible start tiles, if the bool is set to false
						if (!justInputMarket_S_IsStart && line[x] == 'a') {
							startTiles.push_back(tile);
						}
					}
				}

				heightMap.push_back(row);
				y++;
			}

			//close file
			hillMap.close();
		}

		if (goalTile == NULL) {
			throw std::domain_error("Goal tile not found in input");
		}
		if (startTiles.size() == 0) {
			throw std::domain_error("No start found in input");
		}

		//init neighborhood
		for (int y = 0; y < heightMap.size(); y++) {
			for (int x = 0; x < heightMap[y].size(); x++) {
				std::vector<Tile*> neighbours;

				//left neighbour
				//only if height is at most 1 higher and iteration isn't at left border of grid
				if (x != 0 && heightMap[y][x-1]->height-1 <= heightMap[y][x]->height) {
					neighbours.push_back(heightMap[y][x-1]);
				}
				//top neighbour
				if (y != 0 && heightMap[y-1][x]->height - 1 <= heightMap[y][x]->height) {
					neighbours.push_back(heightMap[y-1][x]);
				}
				//right neighbour
				if (x != heightMap[y].size()-1 && heightMap[y][x + 1]->height - 1 <= heightMap[y][x]->height) {
					neighbours.push_back(heightMap[y][x + 1]);
				}
				//bottom neighbour
				if (y != heightMap.size()-1 && heightMap[y+1][x]->height - 1 <= heightMap[y][x]->height) {
					neighbours.push_back(heightMap[y+1][x]);
				}

				heightMap[y][x]->neighbours = neighbours;
			}
		}

		int shortestDistanceToGoal = INT_MAX;

		for (Tile* startTile : startTiles) {
			int possibleShorterDistance = DistanceToGoalWithAStar(heightMap, startTile, goalTile);
			//if there's a way found from the start tile to the goal tile and its distance is shorter than the currently saved distance
			if (possibleShorterDistance != -1 && possibleShorterDistance < shortestDistanceToGoal)
				shortestDistanceToGoal = possibleShorterDistance;
		}

		//free up space
		for (std::vector<Tile*>& row : heightMap) {
			for (Tile* tile : row)
				delete(tile);
		}

		//returning -1 means that the goal was never actually found
		return shortestDistanceToGoal;
	}

	int DistanceToGoalWithAStar(std::vector<std::vector<Tile*>>& heightMap, Tile* startTile, Tile* goalTile) {
		//ToDo: traverse the graph with A* and find the shortest path
		std::vector<Tile*> tilesToTraverse;
		std::vector<Tile*> tilesDoneTraversing;
		tilesToTraverse.push_back(startTile);
		startTile->costFromStart = 0;
		startTile->airDistance = std::sqrt(std::pow(goalTile->x - startTile->x, 2) + std::pow(goalTile->y - startTile->y, 2));
		Tile* currentTile = NULL;

		while (!tilesToTraverse.empty()) {
			//used to delete it out of the list
			std::vector<Tile*>::iterator currentTileIterator;
			//Find tile with smallest total cost in tiles to traverse
			for (std::vector<Tile*>::iterator it = tilesToTraverse.begin(); it != tilesToTraverse.end(); it++) {
				if (currentTile == NULL || (((*it)->costFromStart + (*it)->airDistance) < (currentTile->costFromStart + currentTile->airDistance))) {
					currentTile = (*it);
					currentTileIterator = it;
				}
			}
			//remove tile from tiles to traverse
			tilesToTraverse.erase(currentTileIterator);

			for (Tile* neighbour : currentTile->neighbours) {
				neighbour->costFromStart = currentTile->costFromStart + 1;
				//set air distance of each neighbour
				neighbour->airDistance = std::sqrt(std::pow(goalTile->x - neighbour->x, 2) + std::pow(goalTile->y - neighbour->y, 2));

				//stop search, goal found
				if (neighbour == goalTile) {
					//cost from start is exactly the number of tiles that have to be traversed to reach the goal
					return goalTile->costFromStart;
				}
				else {
					//check if the neighbour is already part of any of the two lists, else add it to the tiles to traverse
					bool neighbourAlreadyInList = false;
					for (Tile* tile : tilesToTraverse) {
						if (tile == neighbour) {
							neighbourAlreadyInList = true;
							break;
						}
					}
					for (Tile* tile : tilesDoneTraversing) {
						if (tile == neighbour) {
							neighbourAlreadyInList = true;
							break;
						}
					}
					if (!neighbourAlreadyInList)
						tilesToTraverse.push_back(neighbour);
				}
			}

			//add tile to tiles done traversing
			tilesDoneTraversing.push_back(currentTile);
			currentTile = NULL;
		}

		//returning -1 means that the goal was never actually found
		return -1;
	}
}