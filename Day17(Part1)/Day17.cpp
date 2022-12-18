#include "Day17.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <array>

/// <summary>
/// TODO part 2: What if instead of 2022 rocks 1000000000000 rocks fall.
/// Idea: Every now and then the rocks form a completely closed of row. Use that and the airflow to find repeating patterns
/// Once repeating patterns have been found, they can be used to interpolate how high the tower would have to be if 1000000000000 rocks fell
/// </summary>

namespace daySeventeen {
	const int cavesize = 7;
	int rockToWaitFor = 2022;
	const int spawnHeightOfNextTile = 4;

	Rock::Rock(Rocktype rocktype) {
		height = 0;
		switch (rocktype) {
			case MINUS:
				/*
				R###
				*/
				for(int x=0; x<4; x++)
					rockTilesLocalSpace.push_back(std::pair<int, int>{x, 0});

				leftEdgingTiles.push_back(&rockTilesLocalSpace[0]);

				rightEdgingTiles.push_back(&rockTilesLocalSpace[3]);

				for (std::pair<int, int>& pos : rockTilesLocalSpace)
					bottomEdgingTiles.push_back(&pos);

				height = 1;
				break;
			case PLUS:
				/*
				.#.
				###
				R#.
				*/
				for (int x = 0; x < 3; x++)
					rockTilesLocalSpace.push_back(std::pair<int, int>{x, 1});
				rockTilesLocalSpace.push_back(std::pair<int, int>{1, 2});
				rockTilesLocalSpace.push_back(std::pair<int, int>{1, 0});

				leftEdgingTiles.push_back(&rockTilesLocalSpace[0]);
				leftEdgingTiles.push_back(&rockTilesLocalSpace[3]);
				leftEdgingTiles.push_back(&rockTilesLocalSpace[4]);

				rightEdgingTiles.push_back(&rockTilesLocalSpace[2]);
				rightEdgingTiles.push_back(&rockTilesLocalSpace[3]);
				rightEdgingTiles.push_back(&rockTilesLocalSpace[4]);

				bottomEdgingTiles.push_back(&rockTilesLocalSpace[0]);
				bottomEdgingTiles.push_back(&rockTilesLocalSpace[4]);
				bottomEdgingTiles.push_back(&rockTilesLocalSpace[2]);

				height = 3;
				break;
			case FLIPPED_L:
				/*
				..#
				..#
				R##
				*/
				for (int x = 0; x < 3; x++)
					rockTilesLocalSpace.push_back(std::pair<int, int>{x, 0});
				rockTilesLocalSpace.push_back(std::pair<int, int>{2, 1});
				rockTilesLocalSpace.push_back(std::pair<int, int>{2, 2});

				leftEdgingTiles.push_back(&rockTilesLocalSpace[0]);
				leftEdgingTiles.push_back(&rockTilesLocalSpace[3]);
				leftEdgingTiles.push_back(&rockTilesLocalSpace[4]);

				rightEdgingTiles.push_back(&rockTilesLocalSpace[2]);
				rightEdgingTiles.push_back(&rockTilesLocalSpace[3]);
				rightEdgingTiles.push_back(&rockTilesLocalSpace[4]);

				bottomEdgingTiles.push_back(&rockTilesLocalSpace[0]);
				bottomEdgingTiles.push_back(&rockTilesLocalSpace[1]);
				bottomEdgingTiles.push_back(&rockTilesLocalSpace[2]);

				height = 3;
				break;
			case I:
				/*
				#
				#
				#
				R
				*/
				for (int y = 0; y < 4; y++)
					rockTilesLocalSpace.push_back(std::pair<int, int>{0, y});

				for (std::pair<int, int>& pos : rockTilesLocalSpace)
					leftEdgingTiles.push_back(&pos);

				for (std::pair<int, int>& pos : rockTilesLocalSpace)
					rightEdgingTiles.push_back(&pos);

				bottomEdgingTiles.push_back(&rockTilesLocalSpace[0]);

				height = 4;
				break;
			case TWO_BY_TWO:
				/*
				##
				R#
				*/
				for (int y = 0; y < 2; y++)
					for (int x = 0; x < 2; x++)
						rockTilesLocalSpace.push_back(std::pair<int, int>{x, y});

				leftEdgingTiles.push_back(&rockTilesLocalSpace[0]);
				leftEdgingTiles.push_back(&rockTilesLocalSpace[2]);

				rightEdgingTiles.push_back(&rockTilesLocalSpace[1]);
				rightEdgingTiles.push_back(&rockTilesLocalSpace[3]);

				bottomEdgingTiles.push_back(&rockTilesLocalSpace[0]);
				bottomEdgingTiles.push_back(&rockTilesLocalSpace[1]);

				height = 2;
				break;
		}
	}

	void Rock::MoveHorizontal(bool left, std::vector<std::vector<bool>>& cave) {
		//move left
		if (left) {
			//check if all left edging tiles have no direct left neighbor
			for (std::pair<int, int>* leftEdgingTile : leftEdgingTiles) {
				//if tile is at the left edge of the board, or position to the left of it is blocked, then the rock can't move left -> skip
				if ((positionInWorldSpace.first == 0) || 
					(cave[positionInWorldSpace.second + (*leftEdgingTile).second][positionInWorldSpace.first + (*leftEdgingTile).first - 1] == true))
					return;
			}

			//if no tile is blocked to the left, then move rock one space to the left
			positionInWorldSpace.first--;
			return;
		}
		//move right
		for (std::pair<int, int>* rightEdgingTile : rightEdgingTiles) {
			//if position to the right of it is blocked, then the rock can't move right -> skip
			if ((positionInWorldSpace.first + (*rightEdgingTile).first == cavesize-1) || 
				(cave[positionInWorldSpace.second + (*rightEdgingTile).second][positionInWorldSpace.first + (*rightEdgingTile).first + 1] == true))
				return;
		}

		//if no tile is blocked to the right, then move rock one space to the right
		positionInWorldSpace.first++;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="cave">level layout</param>
	/// <returns>true = tile is now resting, false = tile is still falling</returns>
	bool Rock::MoveDownwards(std::vector<std::vector<bool>>& cave) {
		//check if all left edging tiles have no direct left neighbor
		for (std::pair<int, int>* bottomEdgingTile : bottomEdgingTiles) {
			//if tile is at the bottom edge of the cave, or position to the bottom of it is blocked, then the rock can't move down -> it comes to rest
			if ((positionInWorldSpace.second + (*bottomEdgingTile).second == 0) || 
				cave[positionInWorldSpace.second + (*bottomEdgingTile).second - 1][positionInWorldSpace.first + (*bottomEdgingTile).first] == true) {
				for (std::pair<int, int>& rockTiles : rockTilesLocalSpace) {
					//block all tiles in cave that this rock covers
					cave[positionInWorldSpace.second + rockTiles.second][positionInWorldSpace.first + rockTiles.first] = true;
				}

				return true;
			}
		}

		//if no tile is blocked to the bottom, then move rock one space down
		positionInWorldSpace.second--;
		return false;
	}

	std::pair<int, int> Rock::GetPosition() {
		return positionInWorldSpace;
	}

	//this is needed to increase the size of the cave vector, as every new rock is spawned 4 tiles over the current highest pos
	int Rock::GetHeight() {
		return height;
	}

	void Rock::SetPosition(std::pair<int, int> pos) {
		this->positionInWorldSpace = pos;
	}

	int GetHeightOfTowerAfterStacking(int numOfRocksToWaitFor) {
		rockToWaitFor = numOfRocksToWaitFor;

		std::ifstream airflowOrder("./InputFiles/Day17_Airflow.txt", std::ifstream::in);
		//std::ifstream airflowOrder("./InputFiles/_Test.txt", std::ifstream::in);

		std::string rockHorizontalPushOrder{};
		//read out data and figure out how big the array has to be to display all
		if (airflowOrder.is_open())
		{
			//there's only one line, so this happens just once
			std::getline(airflowOrder, rockHorizontalPushOrder);

			//close file
			airflowOrder.close();
		}

		//generate initial cave of size 4*7
		std::vector<std::vector<bool>> cave;
		for (int i = 0; i < spawnHeightOfNextTile; i++)
		{
			std::vector<bool> row;
			for (int i = 0; i < cavesize; i++)
				row.push_back(false);

			cave.push_back(row);
		}

		Rock rocks[5]{Rock(Rock::Rocktype::MINUS), Rock(Rock::Rocktype::PLUS) , Rock(Rock::Rocktype::FLIPPED_L) , Rock(Rock::Rocktype::I) , Rock(Rock::Rocktype::TWO_BY_TWO) };
		int rockSpawnNum = 0;
		Rock currentRock = rocks[rockSpawnNum];
		//first rock spawns one tile lower than the rest in the example @advent of code
		currentRock.SetPosition({ 0, -1 });

		int rockHorizontalPushPos = 0;
		int rocksLanded = 0;
		
		int caveHighpointY = 0;
		while (rocksLanded < rockToWaitFor) {
		//while (rocksLanded < 10) {
			currentRock = rocks[rockSpawnNum];
			rockSpawnNum = (rockSpawnNum + 1) % (sizeof(rocks) / sizeof(*rocks));

			//set initial rock position (-1 to account for first row indexed with 0)
			currentRock.SetPosition(std::pair<int, int> {2, caveHighpointY + (spawnHeightOfNextTile-1)});

			bool rockIsResting = false;
			//move rock until it's resting
			while (!rockIsResting) {
				//horizontal push
				switch (rockHorizontalPushOrder[rockHorizontalPushPos]) {
					//push to left
					case '<':
						currentRock.MoveHorizontal(true, cave);
						break;
					//push to right
					case '>':
						currentRock.MoveHorizontal(false, cave);
						break;
				}

				rockHorizontalPushPos = (rockHorizontalPushPos + 1) % rockHorizontalPushOrder.size();

				//drop down a tile
				rockIsResting = currentRock.MoveDownwards(cave);
			}
			rocksLanded++;

			//set highpoint of cave
			if (currentRock.GetPosition().second + currentRock.GetHeight() > caveHighpointY)
				caveHighpointY = currentRock.GetPosition().second + currentRock.GetHeight();

			//increase size of cave vector to fit the next rock with max height of last rock + spawn height of next tile (4) + height of next rock
			int nextRockYNeeded = caveHighpointY + spawnHeightOfNextTile + rocks[rockSpawnNum].GetHeight();

			//save this outside of the loop, else the cave size inreasing will affect the number of iterations in the loop
			int sizeCaveVector = cave.size();
			for (int i = 0; i < nextRockYNeeded- sizeCaveVector; i++)
			{
				std::vector<bool> row;
				for (int i = 0; i < cavesize; i++)
					row.push_back(false);

				cave.push_back(row);
			}

			//DebugCave(cave);
		}
		std::cout << "rocks landed: " << rocksLanded << std::endl;
		DebugCave(cave);

		return caveHighpointY;
	}

	void DebugCave(std::vector < std::vector<bool> > & cave) {
		for (int y = cave.size() - 1; y >= 0; y--) {
			std::cout << "|";
			for (int x = 0; x < cavesize; x++) {
				if (cave[y][x] == true)
					std::cout << "#";
				else
					std::cout << ".";
			}
			std::cout << "|" << std::endl;
		}
		std::cout << "+-------+" << std::endl;
	}
}