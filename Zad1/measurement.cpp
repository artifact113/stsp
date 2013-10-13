#include "measurement.h"

void measureAlgorythmPerformance(algorythmFunction aFunc, AlgorythmData* aData, int minDurationInSec, int minRepeats){

	long repeats = 0;
	int rate = 0;
	std::vector<int> result;

	clock_t start = clock();

	do {
		result = aFunc(aData);
		rate += rateResult(aData, result);
		repeats++;

	} while (clock() - start < minDurationInSec * 1000000 || repeats < minRepeats); 

	clock_t end = (clock() - start);

	std::cout << "Time total: " << end << ", repeats: " << repeats << std::endl;
	std::cout << "Time per function: " << (double) end / (double) repeats << std::endl;
	std::cout << "Avg rate: " << (double) rate / repeats << std::endl; 

};

int rateResult(AlgorythmData* aData, std::vector<int> vec) {
	int rate = 0, lastIdx = vec.size() - 1;
	
	for (int i = 0; i < lastIdx; i++) {
		rate += aData->distances[vec[i]][vec[i + 1]];
	}
	rate += (aData->distances[vec[0]][vec[lastIdx]]);
	
	return rate;
};

