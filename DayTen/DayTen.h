#pragma once

#include <string>

namespace dayTen {
	int GetSignalStrength();
	std::string GenerateSprite();
	void RunCycle(int&, int&, int&, int);
	void RunCycle(int&, std::string&, int);
}