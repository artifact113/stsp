#ifndef NEIGHBOURGENERATOR_H_
#define NEIGHBOURGENERATOR_H_

#include <vector>
#include <stdlib.h> 
#include <iostream>
#include <algorithm>

struct NeighbourGenerator {
private:
	bool finished;
	int firstStart;
	int secondStart;
	void incrementPair();

public:
	int size;
	int firstCurrent;
	int secondCurrent;

	NeighbourGenerator(int size);

	void init();
	std::vector<int> nextNeighbour(std::vector<int> vec);
	std::vector<int> getNeighbour(std::vector<int> vec, int firstIdx,
			int secondIdx);
	std::vector<int> getNeighbourForValues(std::vector<int> vec,
			int firstItemValue, int secondItemValue);
	int getIdxOfItem(std::vector<int> vec, int val);
};

#endif /*NEIGHBOURGENERATOR_H_*/
