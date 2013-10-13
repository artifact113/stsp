#ifndef READER_H
#define READER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "data_structure.h"

AlgorythmData* loadData(char* fileName);
unsigned int split(const std::string &txt, std::vector<std::string> &strs,
		char ch);
#endif //READER_H
