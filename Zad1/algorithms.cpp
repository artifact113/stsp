#include "algorithms.h"

std::vector<int> randomSolver(AlgorythmData* aData) {

	std::vector<int> result, minResult;
	double rate, minRate = 1000000;
	clock_t start = clock();

	do {
		result.clear();
		for (int i = 1; i <= aData->size; i++) {
			result.push_back(i);
		}

		random_shuffle(result.begin(), result.end());
		rate = rateResult(aData, result);
		if (rate < minRate) {
			minRate = rate;
			minResult = result;
		}
	} while (clock() - start < aData->duration * 1000000);

	return result;
}

std::vector<int> greedySolver(AlgorythmData* aData) {
	std::vector<int> result, tempResult;
	double rate, tempRate;
	int steps = 0;
	int visitedResults = 0;
	NeighbourGenerator neighbourGenerator = NeighbourGenerator(aData->size);

	neighbourGenerator.init();
	result = randomSolver(aData);
	tempResult.assign(result.begin(), result.end());
	rate = rateResult(aData, result);
	std::cout << "f " << rate << std::endl;

	while (1) {
		tempResult = neighbourGenerator.nextNeighbour(result);
		visitedResults++;
		if (tempResult.empty()) {
			break;
		} else {
				tempRate = rateResult(aData, tempResult);
			if (tempRate < rate) {
				rate = tempRate;
				result.assign(tempResult.begin(), tempResult.end());
				neighbourGenerator.init();
				steps++;
			}
		}
	}
	std::cout << "s " << steps << std::endl;
	std::cout << "v " << visitedResults << std::endl;
	return result;
}

std::vector<int> simulatedAnnealing(AlgorythmData* aData) {

	//std::cout << "#annealing starts" << std::endl;

	std::vector<int> result, tempResult;
	double rate, tempRate;
	double temperature = aData->temperature;
	double coolingRate = aData->coolingRate;
	double repeats = aData->repeatsPerStep;
	int steps = 0;
	int visitedResults = 0;
	NeighbourGenerator neighbourGenerator = NeighbourGenerator(aData->size);

	neighbourGenerator.init();
	result = randomSolver(aData);
	tempResult.assign(result.begin(), result.end());
	rate = rateResult(aData, result);
	std::cout << "f " << rate << std::endl;

	while (1) {
		tempResult = neighbourGenerator.nextNeighbour(result);
		visitedResults++;
		if (tempResult.empty()) {
			break;
		} else {
				tempRate = rateResult(aData, tempResult);
			if (tempRate < rate) {
				rate = tempRate;
				result.assign(tempResult.begin(), tempResult.end());
				neighbourGenerator.init();
				steps++;
			} else {
				if (exp((-(tempRate - rate)) / temperature) > ((double) rand()
						/ (RAND_MAX))) {
					rate = tempRate;
					result.assign(tempResult.begin(), tempResult.end());
					neighbourGenerator.init();
					steps++;
				}
			}
		}
		if (temperature < 0.000000001) {
			break;
		}
		if (steps % (int) repeats == 0) {
			//break;
			temperature *= 1 - coolingRate;
			//std::cout << "# temperature " << temperature << std::endl;
		}
	}
	std::cout << "s " << steps << std::endl;
	std::cout << "v " << visitedResults << std::endl;
	return result;

}

std::vector<int> steepestSolver(AlgorythmData* aData) {
	std::vector<int> result, currentResult, tempResult;
	double rate, currentRate, tempRate;
	int steps = 0;
	int visitedResults = 0;
	NeighbourGenerator neighbourGenerator = NeighbourGenerator(aData->size);

	neighbourGenerator.init();
	result = randomSolver(aData);
	currentResult.assign(result.begin(), result.end());
	tempResult.assign(result.begin(), result.end());
	rate = rateResult(aData, result);
	tempRate = rate;
	currentRate = rate;

	std::cout << "f " << rate << std::endl;

	while (1) {
		tempResult = neighbourGenerator.nextNeighbour(result);
		visitedResults++;
		if (tempResult.empty()) {
			if (currentRate >= rate) {
				break;
			} else {
				rate = currentRate;
				result.assign(currentResult.begin(), currentResult.end());
				neighbourGenerator.init();
				steps++;
			}
		} else {
			tempRate = rateResult(aData, tempResult);
			if (tempRate < currentRate) {
				currentRate = tempRate;
				currentResult.assign(tempResult.begin(), tempResult.end());
			}
		}
	}
	std::cout << "s " << steps << std::endl;
	std::cout << "v " << visitedResults << std::endl;
	return result;
}

std::vector<int> greedyHeuristic(AlgorythmData* aData) {

	std::vector<int> start, result;

	for (int i = 1; i <= aData->size; i++) {
		start.push_back(i);
	}

	result.assign(start.begin(), start.end());

	double current_rate = 10000000;

	for (unsigned int i = 0; i < start.size(); i++) {

		std::vector<int> current_result = greedySolveFromVertex(start[i], aData);
		if (rateResult(aData, current_result) < current_rate) {
			result = current_result;
			current_rate = rateResult(aData, current_result);
		}

	}

	return result;
}

std::vector<int> greedySolveFromVertex(int vertex, AlgorythmData* aData) {

	std::vector<int> result;

	int current = vertex;

	while (((int) result.size()) < aData->size) {

		result.push_back(current);
		current = getNearest(current, aData, result);

	}

	return result;

}

int getNearest(int vertex, AlgorythmData* aData, std::vector<int> v) {

	int min = 10000000;
	int choosen_vert = vertex;

	for (int i = 1; i <= aData->size; i++) {

		if (aData->distances[vertex][i] < min && vertex != i && !(std::find(
				v.begin(), v.end(), i) != v.end())) {

			min = aData->distances[vertex][i];
			choosen_vert = i;

		}

	}
	return choosen_vert;

}

double rateDelta(AlgorythmData* aData, std::vector<int> prevResult,
		std::vector<int> nextResult, int firstIdxChanged, int secondIdxChanged) {
	int size = aData->size;
	double oldRate = aData->distances[prevResult[firstIdxChanged]][prevResult[(firstIdxChanged - 1 + size) % size]]
			+ aData->distances[prevResult[secondIdxChanged]][prevResult[(secondIdxChanged + 1) % size]];
	double newRate = aData->distances[nextResult[firstIdxChanged]][nextResult[(firstIdxChanged - 1 + size) % size]]
			+ aData->distances[nextResult[secondIdxChanged]][nextResult[(secondIdxChanged + 1) % size]];

	return newRate - oldRate;
}

double rateResult(AlgorythmData* aData, std::vector<int> vec) {
	double rate = 0, lastIdx = vec.size() - 1;

	for (int i = 0; i < lastIdx; i++) {
		rate += aData->distances[vec[i]][vec[i + 1]];
	}
	rate += (aData->distances[vec[0]][vec[lastIdx]]);

	return rate;
}

