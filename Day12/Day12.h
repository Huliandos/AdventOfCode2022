#pragma once

#include <vector>

namespace dayTwelve {
	struct Tile {
		//used to later initialize valid neighbors to traverse to
		int x, y;
		int height;

		int costFromStart;
		//consider changing this to float
		int airDistance;

		std::vector<Tile*> neighbours;

		Tile(int, int, int);
	};

	int GetMinNumOfNodesToVisit(bool);
	int DistanceToGoalWithAStar(std::vector<std::vector<Tile*>>&, Tile*, Tile*);
}