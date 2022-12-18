#pragma once

#include <tuple>
#include <unordered_set>

namespace dayEighteen {
	struct hashFunctionTuple
	{
		size_t operator()(const std::tuple<int, int, int>& tuple) const
		{
			return std::get<0>(tuple) ^ std::get<1>(tuple) ^ std::get<2>(tuple);
		}
	};

	void GenerateLavaBubbel(std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple>&);
	int GetSurfraceAreaOfLavaDrop();
	int GetSurfaceAreaOfLeaveDropExterior();
	void FloodFillAroundBubble(const std::tuple<int, int, int>&, const std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple>&, std::unordered_set<std::tuple<int, int, int>, hashFunctionTuple>&);
}