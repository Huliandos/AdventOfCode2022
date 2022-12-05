#pragma once

#include <unordered_set>

namespace dayThree {
	int GetCombinedRucksackPriority();
	int GetCombinedGroupBadgePriority();
	std::unordered_set<char> GetCommonCharacters(std::unordered_set<char>&, std::string);
}