#pragma once

#include <vector>

namespace dayFifteen {
	void ReadInputData(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>&);
	int GetNumPositionsWithoutBeacon(); 
	unsigned long long GetInputFrequencyOfFreeSpace();
}