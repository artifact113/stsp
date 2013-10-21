#include "neighbour_generator.h"

NeighbourGenerator::NeighbourGenerator(int size) : size(size) {	
}

void NeighbourGenerator::init() {
	 firstStart = rand() % (size - 1);
	 secondStart = firstStart + 1;
	 
	 firstCurrent = firstStart;
	 secondCurrent = secondStart;
	
	 finished = false;
}

void NeighbourGenerator::incrementPair() {
	if(secondCurrent == size - 1) {
			firstCurrent = (firstCurrent + 1) % (size - 1);
			secondCurrent = firstCurrent + 1;
	} else {
		secondCurrent++;
	}	
}

std::vector<int> NeighbourGenerator::nextNeighbour(std::vector<int> vec) {
	std::vector<int> neighbour;
	
	incrementPair();
	
	if(finished == true) {
		return neighbour;
	}
	
	if(firstCurrent == firstStart && secondCurrent == secondStart) {
		finished = true;
	}
	
	neighbour.assign(vec.begin(), vec.end());
	std::swap(neighbour[firstCurrent], neighbour[secondCurrent]);
	
	return neighbour;
	
}