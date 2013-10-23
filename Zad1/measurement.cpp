#include "measurement.h"

void measureAlgorythmPerformance(algorythmFunction aFunc, AlgorythmData* aData,
		int minDurationInSec, int minRepeats) {

	long repeats = 0;
	double rate = 0;
	std::vector<int> result;

	clock_t start = clock();

	do {
		result = aFunc(aData);
		rate = rateResult(aData, result);
		std::cout << "r " << rate << " ";
		for(int i = 0; i < result.size(); i++) {
			std::cout << result[i] << " ";
		}
		std::cout << std::endl;
		repeats++;

	} while (clock() - start < minDurationInSec * 1000000
			|| repeats < minRepeats);

	clock_t end = (clock() - start);

	double totalAvgTime = (double) end / ((double) repeats);

	std::cout << "t " << totalAvgTime / 1000000 << std::endl;

}
;

