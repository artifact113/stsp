#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H 

#include <cmath>
#include <iostream>

struct AlgorythmData {
	int size;
	int *longtitudes;
	int *latitudes;
	double **distances;
	//for random
	double duration;
	//for sa
	double temperature;
	double coolingRate;
	double repeatsPerStep;
	//for ts
	int tabuListSize; //przez ile iteracji nie mozna wykonac ruchu
	int masterListSize; //ile najlepszych elementow wybieramy do master listy
	int maxIterationsMasterList; //po ilu ruchach przebudowujemy masterListe
	double thresholdOfMasterList; //po jakim pogorszeniu jakosci przebudowujemy masterListe
	int maxIterationsWithoutImprovement; // ile iteracji bez polepszenia
	
	
	void calculateDistances();

	AlgorythmData();

	AlgorythmData(int size) ;
	
	~AlgorythmData() ;	
 };

#endif //DATA_STRUCTURE_H
