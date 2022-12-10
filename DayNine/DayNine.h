#pragma once

namespace dayNine {
	struct Position {
		int x;
		int y;

		Position(int x, int y);

		bool operator == (const Position&) const;
	};

	struct PositionHash {
		size_t operator()(const Position&) const;
	};

	int GetNumOfPositionsVisited(int);
	void CheckMoveFollowing(Position&, Position&);
}