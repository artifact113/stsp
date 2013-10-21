#ifndef NEIGHBOURGENERATOR_H_
#define NEIGHBOURGENERATOR_H_

#include <vector>
#include <stdlib.h> 
#include <iostream>
#include <algorithm>

struct NeighbourGenerator {
private :
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
};

#endif /*NEIGHBOURGENERATOR_H_*/
