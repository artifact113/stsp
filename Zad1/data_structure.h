#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H 

#include <cmath>
#include <iostream>

struct AlgorythmData {
	int size;
	int *longtitudes;
	int *latitudes;
	double **distances;

	void calculateDistances();

	AlgorythmData();

	AlgorythmData(int size) ;
	
	~AlgorythmData() ;	
 };

#endif //DATA_STRUCTURE_H
