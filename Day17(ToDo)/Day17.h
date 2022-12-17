#pragma once

#include <vector>

namespace daySeventeen {
	class Rock {
	private:
		//x|y, bottom left position of object, can be on a tile that's not part of the object
		std::pair<int, int> positionInWorldSpace{0, 0};
		//root is always the leftmost position of the rock, that's also closest to the bottom of all leftmost tiles
		std::vector<std::pair<int, int>> rockTilesLocalSpace;
		//only the tiles on the left/right/bottom edge have to be checked against collision during movement.
		std::vector<std::pair<int, int>*> leftEdgingTiles, rightEdgingTiles, bottomEdgingTiles;

		int height;
	public:
		enum Rocktype
		{
			MINUS, PLUS, FLIPPED_L, I, TWO_BY_TWO
		};
		Rock(Rocktype);
		void MoveHorizontal(bool, std::vector<std::vector<bool>>&);
		bool MoveDownwards(std::vector<std::vector<bool>>&);
		int GetHeight();
		std::pair<int, int> GetPosition();
		void SetPosition(std::pair<int, int>);
	};

	int GetHeightOfTowerAfterStacking();
	void DebugCave(std::vector<std::vector<bool>>&);
}