#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "data_structure.h"
#include "algorithms.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

typedef std::vector<int> (*algorythmFunction)(AlgorythmData*);

void measureAlgorythmPerformance(algorythmFunction aFunc, AlgorythmData* aData, int minDurationInSec, int minRepeats);


#endif //MEASUREMENT_H
