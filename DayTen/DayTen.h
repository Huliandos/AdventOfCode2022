#pragma once

#include <string>

namespace dayTen {
	int GetTotalSignalStrength();
	std::string GenerateSprite();
	void RunCycle(int&, int&, int&, int);
	void RunCycle(int&, std::string&, int);
}