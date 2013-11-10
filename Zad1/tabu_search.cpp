#include "tabu_search.h"

std::vector<int> tabuSearchSolver(AlgorythmData* aData) {
	std::vector<int> result, tempResult;
	double rate;
	int iterationsWithoutImprovement = 0, iterationsOfMasterList =
			aData->maxIterationsMasterList, visitedResults = 0, steps = 0;
	std::map<std::string, int> tabuList;

	NeighbourGenerator neighbourGenerator = NeighbourGenerator(aData->size);
	result = randomSolver(aData);
	tempResult.assign(result.begin(), result.end());
	rate = rateResult(aData, result);

	std::multimap<double, TSData> masterList;

	std::cout << "f " << rate << std::endl;
	while (1) {

		if (iterationsOfMasterList >= aData->maxIterationsMasterList || masterList.size() == 0) {
			masterList
					= createMasterList(aData, tempResult, neighbourGenerator);
			iterationsOfMasterList = 0;
			visitedResults += aData->size * (aData->size - 1) / 2;
		} else {
			masterList = updateMasterList(aData, masterList, tempResult);
		}
		std::pair<double, TSData> currentMove = chooseMove(masterList, tabuList,
				rate);
		tempResult = currentMove.second.solution;
		tabuList = updateTabuList(tabuList, currentMove.second,
				aData->tabuListSize);
		masterList.erase(masterList.find(currentMove.first));
		steps++;

		if (currentMove.second.rate >= rate) {
			iterationsWithoutImprovement++;
		} else {
			iterationsWithoutImprovement = 0;
			rate = currentMove.second.rate;
			result = currentMove.second.solution;
		}

		if (iterationsWithoutImprovement
				>= aData->maxIterationsWithoutImprovement) {
			break;
		}
	}
	std::cout << "s " << steps << std::endl;
	std::cout << "v " << visitedResults << std::endl;
	return result;
}

std::multimap<double, TSData> updateMasterList(AlgorythmData* aData,
		std::multimap<double, TSData> masterList, std::vector<int> tempResult) {
	NeighbourGenerator neighbourGenerator(aData->size);
	std::multimap<double, TSData> newMasterList;
	std::multimap<double, TSData>::iterator it;
	for (it = masterList.begin(); it != masterList.end(); ++it) {
		TSData ts;
		ts.firstChanged = it->second.firstChanged;
		ts.secondChanged = it->second.secondChanged;
		ts.solution = neighbourGenerator.getNeighbourForValues(
				it->second.solution, ts.firstChanged, ts.secondChanged);
		ts.rate = rateResult(aData, ts.solution); 
		
		newMasterList.insert(std::pair<double, TSData>(ts.rate, ts));
	}
	return newMasterList;
}

std::pair<double, TSData> chooseMove(std::multimap<double, TSData> masterList,
		std::map<std::string, int> tabuList, int bestRate) {
	std::multimap<double, TSData>::iterator it;
	for (it = masterList.begin(); it != masterList.end(); ++it) {
		//kryterium aspiracji -- nawet jesli jest tabu, a daje lepsze rozwiazanie, to bierzemy
		if (it->first < bestRate) {
			return std::pair<double, TSData>(it->first, it->second);
		} else {
			std::string tabuKey = getKey(it->second.firstChanged,
					it->second.secondChanged);
			//jesli nie ma na liscie tabu, to bierzemy
			if (tabuList.find(tabuKey) == tabuList.end()) {
				return std::pair<double, TSData>(it->first, it->second);
			}
		}
	}
	//jesli nie ma zadnego niezabronionego, to bierzemy najmniej tabu
	return minTabuMove(masterList, tabuList);
}

std::pair<double, TSData>  minTabuMove(std::multimap<double, TSData> masterList, std::map<std::string, int> tabuList) {
	std::multimap<double, TSData>::iterator it = masterList.begin();
	std::pair<double, TSData> minResult(it->first, it->second);
	int minTabu = tabuList[getKey(it->second.firstChanged, it->second.secondChanged)];
		for (it = masterList.begin(); it != masterList.end(); ++it) {
			int tabu = tabuList[getKey(it->second.firstChanged, it->second.secondChanged)];
			if(tabu < minTabu) {
				minResult = std::pair<double, TSData>(it->first, it->second);
				minTabu = tabu;
			}
		}
	return minResult;
}

std::map<std::string, int> updateTabuList(std::map<std::string, int> tabuList,
		TSData currentMove, int tabuListSize) {
	std::map<std::string, int>::iterator it;
	for (it = tabuList.begin(); it != tabuList.end();) {
		it->second = it->second - 1;
		if (it->second == 0) {
			tabuList.erase(it++);
		} else {
			++it;
		}
	}
	tabuList.insert(std::pair<std::string, int>(getKey(currentMove.firstChanged, currentMove.secondChanged),
			tabuListSize));
	return tabuList;
}

std::string getKey(int a, int b) {
	std::stringstream ss;
	ss << a;
	std::string sA = ss.str();
	ss << b;
	std::string sB = ss.str();
	return (a < b) ? sA + sB : sB + sA;
}

std::multimap<double, TSData> createMasterList(AlgorythmData* aData,
		std::vector<int> result, NeighbourGenerator neighbourGenerator) {
	int size = aData->masterListSize;
	std::multimap<double, TSData> tempMasterList, masterList;
	neighbourGenerator.init();
	while (1) {
		TSData tempTS;
		tempTS.solution = neighbourGenerator.nextNeighbour(result);
		if (tempTS.solution.empty()) {
			break;
		}
		tempTS.firstChanged = result[neighbourGenerator.firstCurrent];
		tempTS.secondChanged = result[neighbourGenerator.secondCurrent];
		tempTS.rate = rateResult(aData, tempTS.solution);
		masterList.insert(std::pair<double, TSData>(tempTS.rate, tempTS));
	}

	masterList = cutMasterList(masterList, size);

	return masterList;
}

std::multimap<double, TSData> cutMasterList(
		std::multimap<double, TSData> masterList, int firstElementsCount) {
	std::multimap<double, TSData> newMasterList;
	std::multimap<double, TSData>::iterator it;
	int i = 0;
	for (it = masterList.begin(); it != masterList.end(); ++it) {
		newMasterList.insert(std::pair<double, TSData>(it->first, it->second));
		if (i == firstElementsCount - 1) {
			break;
		}
		i++;
	}

	return newMasterList;

}