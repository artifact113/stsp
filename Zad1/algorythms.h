#ifndef ALGORYTHMS_H
#define ALGORYTHMS_H

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "data_structure.h"

std::vector<int> randomSolver(AlgorythmData* aData);
std::vector<int> greedyHeuristic(AlgorythmData* aData);
int getNearest(int vertex, AlgorythmData* aData, std::vector<int> v);
std::vector<int> greedySolveFromVertex(int vertex, AlgorythmData* aData);

#endif //ALGORYTHMS_H
