#ifndef TABU_SEARCH_H_
#define TABU_SEARCH_H_

#include "algorithms.h"
#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sstream>

struct TSData {
	std::vector<int> solution;
	double rate;
	int firstChanged;
	int secondChanged;
};

std::vector<int> tabuSearchSolver(AlgorythmData* aData);

std::multimap<double, TSData> createMasterList(AlgorythmData* aData,
		std::vector<int> result, NeighbourGenerator neighbourGenerator);

std::multimap<double, TSData> cutMasterList(
		std::multimap<double, TSData> masterList, int firstElementsCount);

std::map<std::string, int> updateTabuList(std::map<std::string, int> tabuList,
		TSData currentMove, int tabuListSize);

std::string getKey(int a, int b);

std::pair<double, TSData> chooseMove(std::multimap<double, TSData> masterList,
		std::map<std::string, int> tabuList, int bestRate);

std::multimap<double, TSData> updateMasterList(AlgorythmData* aData,
		std::multimap<double, TSData> masterList, std::vector<int> tempResult);

std::pair<double, TSData> minTabuMove(std::multimap<double, TSData> masterList,
		std::map<std::string, int> tabuList);

#endif /*TABU_SEARCH_H_*/
