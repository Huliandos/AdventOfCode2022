#include "Day13.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>
#include <stack>

namespace dayThirteen {


	/*
	int GetSumOfIndicesInRightOrder() {
		//std::ifstream distressSignal("./InputFiles/Day13_DistressSignal.txt", std::ifstream::in);
		std::ifstream distressSignal("./InputFiles/_Test.txt", std::ifstream::in);

		NestedData<std::vector<int>> test { std::vector<int>{0} };

		//NestedData<std::vector<NestedData<std::vector<int>>>> test2{ std::vector < NestedData<std::vector<int>>>{std::vector<int> {1, 2}} > {} };

		std::vector<std::vector<int> > testLeft{ {1},{2,3,4} };
		std::vector<std::vector<int> > testRight{ {1} ,{4} };

		std::cout << "test compare resolves to: " << Compare(testLeft, testRight) << std::endl;

		//read out data
		if (distressSignal.is_open())
		{
			std::string pairLeft{}, pairRight{};

			//used to track starting indices of brackets
			std::stack<int> bracketStartingIndex;

			while (std::getline(distressSignal, pairLeft)) {

				for (int i = 0; i < pairLeft.size(); i++) {
					//find pairs of brackets
					if (pairLeft[i] == '[')
						bracketStartingIndex.push(i);
					else if (pairLeft[i] == ']') {
						int startingIndex = bracketStartingIndex.top();
						bracketStartingIndex.pop();
						//convert to vector
						//NestedData<int> test{0};
						//NestedData<std::vector<int>> test{ {0, 0, 0} };
					}
				}
				std::getline(distressSignal, pairRight);
				//skip empty line
				std::getline(distressSignal, pairRight);
			}

			//close file
			distressSignal.close();
		}

		return 0;
	}

	/// <summary>
	/// compares a pair of two lists with unknown depth of nesting recursively with overloaded functions
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <returns></returns>
	template <typename T>
	int Compare(std::vector<T> left, std::vector<T> right) {
		for (int i = 0; i < left.size(); i++) {
			//right list has run out of elements, inputs are in wrong order
			if (i >= right.size())
				return 1;

			int compareResolvedIn = Compare(left[i], right[i]);

			//if compare didn't declare both values equal return, else continue loop
			if (compareResolvedIn != 0)
				return compareResolvedIn;
		}
		//left list ran out of values first, so inputs are in right order
		if (left.size() < right.size())
			return -1;

		//both vectors are equal
		return 0;
	}

	/// <summary>
	/// convert left to list and recursively call overloaded function
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <returns></returns>
	template <typename T>
	int Compare(int left, std::vector<T> right) {
		std::vector<int> leftAsVector{ left };
		return Compare(leftAsVector, right);
	}

	/// <summary>
	/// convert right to list and recursively call overloaded function
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <returns></returns>
	template <typename T>
	int Compare(std::vector<T> left, int right) {
		std::vector<int> rightAsVector{ right };
		return Compare(left, rightAsVector);
	}

	/// <summary>
	/// -1 means left integer is higher, 0 that both are the same value and 1 that right value is higher
	/// </summary>
	/// <param name="left">left integer of pair</param>
	/// <param name="right">left integer of pair</param>
	/// <returns></returns>
	int Compare(int left, int right) {
		if (left < right)
			return -1;
		else if (left == right)
			return 0;
		return 1;
	}
	*/
}