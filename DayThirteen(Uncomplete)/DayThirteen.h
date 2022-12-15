#pragma once

#include <vector>
namespace dayThirteen {
	template <typename T>
	struct NestedData {
		T nestedData;

		NestedData(T nestedData) {
			this->nestedData = nestedData;
		}
	};

	int GetSumOfIndicesInRightOrder(); 

	template <typename T>
	int Compare(std::vector<T>, std::vector<T>);
	
	template <typename T>
	int Compare(int, std::vector<T>);

	template <typename T>
	int Compare(std::vector<T>, int);

	int Compare(int, int);
}