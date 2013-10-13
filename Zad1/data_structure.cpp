#include "data_structure.h"

void AlgorythmData::calculateDistances() {
		for (int i = 1; i <= this->size; i++) {
			for (int j = 1; j <= this->size; j++) {
				distances[i][j] = sqrt(
						pow((longtitudes[i] - longtitudes[j]), 2)
								+ pow((latitudes[i] - latitudes[j]), 2));
				distances[j][i] = distances[i][j];
			}
		}
	}

	AlgorythmData::AlgorythmData() {};

	AlgorythmData::AlgorythmData(int size) : size(size) {
		longtitudes = new int[size + 1];
		latitudes = new int[size + 1];
		distances = new int*[size + 1];
		for(int i = 0; i < size + 1; i++) {
			distances[i] = new int[size + 1];
		}	
	}
	
	AlgorythmData::~AlgorythmData() {
		for(int i = 0; i < size + 1; i++) {
			delete [] distances[i];
		}			

		delete [] longtitudes;
		delete [] latitudes;
		delete [] distances;
	} 
