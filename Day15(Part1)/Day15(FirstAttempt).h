#pragma once

#include <vector>

namespace dayFifteenOLD {
	int GetPositionsWhereBeaconsCanNotBePresenetedInRow(); 
	void printSensorRanges(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>&, bool*, int, int, int, int, int, int);
}