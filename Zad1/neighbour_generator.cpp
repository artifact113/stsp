#include "neighbour_generator.h"

NeighbourGenerator::NeighbourGenerator(int size) :
	size(size) {
}

void NeighbourGenerator::init() {
	firstStart = rand() % (size - 1);
	secondStart = firstStart + 1;

	firstCurrent = firstStart;
	secondCurrent = secondStart;

	finished = false;
}

void NeighbourGenerator::incrementPair() {
	if (secondCurrent == size - 1) {
		firstCurrent = (firstCurrent + 1) % (size - 1);
		secondCurrent = firstCurrent + 1;
	} else {
		secondCurrent++;
	}
}

std::vector<int> NeighbourGenerator::nextNeighbour(std::vector<int> vec) {
	incrementPair();
	std::vector<int> neighbour;
	
	if (finished == true) {
		return neighbour;
	}

	if (firstCurrent == firstStart && secondCurrent == secondStart) {
		finished = true;
	}

	return getNeighbour(vec, firstCurrent, secondCurrent);

}

std::vector<int> NeighbourGenerator::getNeighbour(std::vector<int> vec,
		int firstIdx, int secondIdx) {
	std::vector<int> neighbour;
	
	neighbour.assign(vec.begin(), vec.end());

	//std::swap(neighbour[firstCurrent], neighbour[secondCurrent]);
	std::reverse(neighbour.begin() + firstIdx, neighbour.begin()
			+ secondIdx + 1);

	return neighbour;
}

std::vector<int> NeighbourGenerator::getNeighbourForValues(std::vector<int> vec,
	int firstItemValue, int secondItemValue) {
	int firstIdx, secondIdx;
	
	firstIdx = getIdxOfItem(vec, firstItemValue);
	secondIdx = getIdxOfItem(vec, secondItemValue);

	return getNeighbour(vec, firstIdx, secondIdx);
}

int NeighbourGenerator::getIdxOfItem(std::vector<int> vec, int val) {
	for(int i = 0; i < vec.size(); i++) {
		if(vec[i] == val) {
			return i;
		}
	}
	return -1;
}
