#include "reader.h"	

AlgorythmData* loadData(char* fileName) {
	AlgorythmData* aData = 0;
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			std::vector<std::string> v;
			split(line, v, ':');
			if (v[0][0] == 'D' && v[0][1] == 'I' && v[0][2] == 'M') {
				int size = atoi(v[1].c_str());
				aData = new AlgorythmData(size);
				std::cout << "SIZE: " << size << " " << aData->size << std::endl;
			} else {
				split(line, v, ' ');
				int vertex = atoi(v[0].c_str());
				if (vertex > 0) {
					aData->longtitudes[vertex] = atoi(v[1].c_str());
					aData->latitudes[vertex] = atoi(v[2].c_str());
				}
			}
		}
		aData->calculateDistances();
		myfile.close();
	}
	return aData;
};


unsigned int split(const std::string &txt, std::vector<std::string> &strs,
		char ch) {
	unsigned long pos = txt.find(ch);
	unsigned long initialPos = 0;
	strs.clear();

	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	strs.push_back(
			txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}
