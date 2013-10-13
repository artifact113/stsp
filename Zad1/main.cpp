//example usage : ./main problems/eil51.tsp 2 10


#include "main.h"

using namespace std;


int main(int argc, char** argv) {
	int minRepeats, minTimeInSec;
	char* fileName; 

	if(argc < 4) {
 		std::cout << "Wrong arguments. Usage : <filename> <minTimeInSec> <minRepeats>\n";
		return -1;
	} else {
		fileName = argv[1];
		minTimeInSec = atoi(argv[2]);
		minRepeats = atoi(argv[3]);
	}

	AlgorythmData *aData = 0;

	srand(time(0));
	aData = loadData(fileName);
	if(aData == 0) {
		std::cout << "Error while reading file\n";
		return -1;
	} else {
 		measureAlgorythmPerformance(&randomSolver, aData, minTimeInSec, minRepeats);
	}

	delete aData;
	return 0;
}
