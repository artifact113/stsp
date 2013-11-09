//example usage : ./main problems/eil51.tsp 2 10

#include "main.h"

using namespace std;

algorythmFunction getAlgorithmFunc(char algorithm) {

	switch (algorithm) {

	case 's':
		return &steepestSolver;
	case 'g':
		return &greedySolver;
	case 'h':
		return &greedyHeuristic;
	case 'r':
		return &randomSolver;
	case 'a':
		return &simulatedAnnealing;
	default:
		return &randomSolver;

	}
}

int main(int argc, char** argv) {
	int minRepeats, minTimeInSec;
	char* fileName;
	char algorithm; // r - random, g - greedy, s - steepest, h - heuristic, a - simulated annealing

	if (argc < 5) {
		std::cout
				<< "Wrong arguments. Usage : <algorithm (r, g, s, h)> <filename> <minTimeInSec> <minRepeats> <randomTimeInSec>\n";
		return -1;
	} else {
		algorithm = argv[1][0];
		fileName = argv[2];
		minTimeInSec = atoi(argv[3]);
		minRepeats = atoi(argv[4]);
	}

	std::cout << "# preparing aData" << std::endl;
	AlgorythmData *aData = 0;
	std::cout << "# preparing aData is done" << std::endl;

	srand(time(0));
	aData = loadData(fileName);
	std::cout << "# reading file " << fileName << std::endl;
	if (aData == 0) {
		std::cout << "Error while reading file\n";
		return -1;
	} else {
		std::cout << "# " << algorithm << "_" << fileName << std::endl;
		if(algorithm == 'r') {
			aData->duration = atoi(argv[5]);
		}
		if(algorithm == 'a') {
					std::cout << "# choosen algorithm is simulated annealing" << std::endl;
					aData->temperature = atof(argv[5]);
					aData->coolingRate = atof(argv[6]);
					aData->repeatsPerStep = atoi(argv[7]);
		}
		algorythmFunction aFunc = getAlgorithmFunc(algorithm);
		measureAlgorythmPerformance(aFunc, aData, minTimeInSec, minRepeats);
	}

	delete aData;
	return 0;
}
