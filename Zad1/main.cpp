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
	default:
		return &randomSolver;

	}
}

int main(int argc, char** argv) {
	int minRepeats, minTimeInSec;
	char* fileName;
	char algorithm; // r - random, g - greedy, s - steepest, h - heuristic

	if (argc < 4) {
		std::cout
				<< "Wrong arguments. Usage : <algorithm (r, g, s, h)> <filename> <minTimeInSec> <minRepeats>\n";
		return -1;
	} else {
		algorithm = argv[1][0];
		fileName = argv[2];
		minTimeInSec = atoi(argv[3]);
		minRepeats = atoi(argv[4]);
	}

	AlgorythmData *aData = 0;

	srand(time(0));
	aData = loadData(fileName);
	if (aData == 0) {
		std::cout << "Error while reading file\n";
		return -1;
	} else {
		std::cout << "# " << algorithm << "_" << fileName << std::endl;
		algorythmFunction aFunc = getAlgorithmFunc(algorithm);
		measureAlgorythmPerformance(aFunc, aData, minTimeInSec, minRepeats);
	}

	delete aData;
	return 0;
}
