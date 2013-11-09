#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H 

#include <cmath>
#include <iostream>

struct AlgorythmData {
	int size;
	int *longtitudes;
	int *latitudes;
	double **distances;
	double duration;
	double temperature = 10.0;
	double coolingRate = 0.1;
	double repeatsPerStep = 100;

	void calculateDistances();

	AlgorythmData();

	AlgorythmData(int size) ;
	
	~AlgorythmData() ;	
 };

#endif //DATA_STRUCTURE_H
