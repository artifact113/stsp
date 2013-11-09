#ifndef ALGORYTHMS_H
#define ALGORYTHMS_H

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "data_structure.h"
#include "neighbour_generator.h"

std::vector<int> randomSolver(AlgorythmData* aData);

std::vector<int> greedySolver(AlgorythmData* aData);
std::vector<int> steepestSolver(AlgorythmData* aData);

std::vector<int> simulatedAnnealing(AlgorythmData* aData);

std::vector<int> greedyHeuristic(AlgorythmData* aData);
int getNearest(int vertex, AlgorythmData* aData, std::vector<int> v);
std::vector<int> greedySolveFromVertex(int vertex, AlgorythmData* aData);

double rateResult(AlgorythmData* aData, std::vector<int> vec);
double rateDelta(AlgorythmData* aData, std::vector<int> prevResult,
		std::vector<int> nextResult, int firstIdxChanged, int secondIdxChanged);

#endif //ALGORYTHMS_H
