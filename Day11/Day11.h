#pragma once

#include <vector>
#include <string>

namespace dayEleven {
	class Monkey {
		private:
			int numOfInspectedItems;
			int leastCommonMultiple;
			std::vector<Monkey*> monkeys;
			std::vector<size_t> items;
			std::string operation; 
			int divisibleBy;
			int throwToMonkey[2];
		public:
			Monkey(std::vector<size_t>, std::string, int, int, int);
			void SetMonkeyVectorReferences(std::vector<Monkey*>&);
			void SetCommonMultiple(int);
			void ThrowAllItems(bool);
			void AddItem(size_t);
			int GetNumOfInspectedItems();
	};

	unsigned long long GetMultipliedMonkeyBusiness(bool);
	void ConvertStringToIntVector(std::string&, std::vector<size_t>&);
}