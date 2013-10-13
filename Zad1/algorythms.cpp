#include "algorythms.h"
#include "measurement.h"

std::vector<int> randomSolver(AlgorythmData* aData) {

	std::vector<int> result;

	for (int i = 1; i <= aData->size; i++) {
		result.push_back(i);
	}

	random_shuffle(result.begin(), result.end());

	return result;
}

std::vector<int> greedyHeuristic(AlgorythmData* aData) {

	std::vector<int> start;

	for (int i = 1; i <= aData->size; i++) {
		start.push_back(i);
	}

	std::vector<int> result = start;

	int current_rate = 0;

	for(unsigned int i = 0; i < start.size(); i++) {

		std::vector<int> current_result = greedySolveFromVertex(start[i], aData);
		if(rateResult(aData, current_result) > current_rate) {
			result = current_result;
			current_rate = rateResult(aData, current_result);
		}

	}

	return result;
}

int getNearest(int vertex, AlgorythmData* aData, std::vector<int> v) {

	int min = 999999;
	int choosen_vert = vertex;

	for (int i = 1; i <= aData->size; i++) {

		if (aData->distances[vertex][i] < min && vertex != i
				&& !(std::find(v.begin(), v.end(), i) != v.end())) {

			min = aData->distances[vertex][i];
			choosen_vert = i;

		}

	}

	return choosen_vert;

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

