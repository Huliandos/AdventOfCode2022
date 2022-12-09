#include "DayEight.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>

namespace dayEight {
	std::vector<std::vector<int>> Generate2DMapOfForrest() {
		std::ifstream consoleOutput("./InputFiles/DayEight_NeighbouringTrees.txt", std::ifstream::in);

		//2d vector representing the forest
		std::vector<std::vector<int>> forest;
		//read out data
		if (consoleOutput.is_open())
		{
			std::string line{};

			//Get input lines
			while (std::getline(consoleOutput, line)) {
				std::vector<int> forestLine;

				for (char c : line) {
					//scale tree height from 0
					forestLine.push_back(c - '0');
				}

				forest.push_back(forestLine);
			}

			//close file
			consoleOutput.close();
		}

		return forest;
	}

	int GetNumOfVisibleTrees() {
		std::vector<std::vector<int>> forest = Generate2DMapOfForrest();

		//trees on the edge are always visible
		//left side, right side, top side and bottom side -4 (so trees in the corners aren't counted twice)
		//only works for squared input data
		int visibleTrees = forest.size() * 4 - 4;

		//optimization, so that trees above don't have to be checked, as we just needed to check against the tallest trees in these rows
		std::vector<int> heightTallestTreeAbove = forest[0];

		for (int y = 1; y < forest.size()-1; y++) {
			//optimization, so that trees to the left don't have to be checked, as we just needed to check against the tallest tree
			int heightTallestTreeLeft = forest[y][0];

			for (int x = 1; x < forest[y].size()-1; x++) {
				//are all trees to the left lower?
				if (heightTallestTreeLeft < forest[y][x]) {
					heightTallestTreeLeft = forest[y][x];
					visibleTrees++;
					//also update heighest tree above if this tree is heigher than any tree of this row
					if (heightTallestTreeAbove[x] < forest[y][x]) {
						heightTallestTreeAbove[x] = forest[y][x];
					}
				}
				//are all trees above lower
				else if (heightTallestTreeAbove[x] < forest[y][x]) {
					heightTallestTreeAbove[x] = forest[y][x];
					visibleTrees++;
				}
				else {
					bool higherTreeRight = false;
					//higher tree to the right?
					for (int i = x + 1; i < forest[y].size(); i++) {
						//a higher or same height tree has been found, so this tree can't be visible from the right
						if (forest[y][i] >= forest[y][x]) {
							higherTreeRight = true;
							break;
						}
					}
					if (!higherTreeRight) {
						visibleTrees++;
					}
					else {
						bool higherTreeBelow = false;
						//higher tree below?
						for (int i = y + 1; i < forest.size(); i++) {
							//a higher or same height tree has been found, so this tree can't be visible from below
							if (forest[i][x] >= forest[y][x]) {
								higherTreeBelow = true;
								break;
							}
						}
						if (!higherTreeBelow) {
							visibleTrees++;
						}
					}
				}
			}
		}

		return visibleTrees;
	}

	int GetHighestScenicScore() {
		std::vector<std::vector<int>> forest = Generate2DMapOfForrest();

		int highestScenicScore = 0;

		//can ignore edge, as their scenic score is always 0
		for (int y = 1; y < forest.size()-1; y++) {
			for (int x = 1; x < forest[y].size()-1; x++) {
				int treeScenicScore = 1;


				//finding score to the left
				int i = x - 1;
				while (i > 0) {
					if (forest[y][i] >= forest[y][x])
						break;
					i--;
				}
				//this is taken out of the loop so that trees seeing until the edge of the board still get their score multiplier applied
				//* distance between i and x (x first because i is smaller than x)
				treeScenicScore *= x - i;


				//finding score to the top
				i = y - 1;
				while (i > 0) {
					if (forest[i][x] >= forest[y][x])
						break;
					i--;
				}
				//this is taken out of the loop so that trees seeing until the edge of the board still get their score multiplier applied
				//* distance between i and y (y first because i is smaller than y)
				treeScenicScore *= y - i;


				//finding score to the right
				i = x + 1;
				//once i reached size()-1 we're at the edge of the forest
				while (i < forest[y].size()-1) {
					if (forest[y][i] >= forest[y][x])
						break;
					i++;
				}
				//this is taken out of the loop so that trees seeing until the edge of the board still get their score multiplier applied
				//* distance between i and x (i first because x is smaller than i)
				treeScenicScore *= i - x;

				//finding score to the bottom
				i = y + 1;
				//once i reached size()-1 we're at the edge of the forest
				while (i < forest.size()-1) {
					if (forest[i][x] >= forest[y][x])
						break;
					i++;
				}
				//this is taken out of the loop so that trees seeing until the edge of the board still get their score multiplier applied
				//* distance between i and y (i first because y is smaller than i)
				treeScenicScore *= i - y;

				if (treeScenicScore > highestScenicScore)
					highestScenicScore = treeScenicScore;
			}
		}


		return highestScenicScore;
	}
}