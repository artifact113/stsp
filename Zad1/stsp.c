#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;

#define TIME 100
#define REPEATS 10
#define SIZE 320

int longtitudes[SIZE];
int latitudes[SIZE];

int distances[SIZE][SIZE];

int places = 0;

int power(int a, int b) {
	int res = 1;
	for (int i = 1; i < b; i++) {
		res *= b;
	}
	return res;
}

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

vector<int> random_solve() {

	vector<int> result;

	for (int i = 1; i <= places; i++) {
		result.push_back(i);
	}

	random_shuffle(result.begin(), result.end());

	return result;

}

void nasza_funkcja() {
	for (int i = 0; i < power(2, 14); i++) {
		for (int j = 0; j < power(2, 6); j++) {
			power(2, i + j);
		}
	}
}

int rate_solve(vector<int> vec) {
	int rate = 0;
	for (int i = 0; i < vec.size() - 1; i++) {
		rate += distances[vec[i]][vec[i + 1]];
	}
	rate += (distances[vec[0]][vec[-1]]);
	return rate;
}

int main() {

	srand(time(0));

	string line;
	ifstream myfile("problems/eil51.tsp");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			vector<string> v;
			split(line, v, ':');
			if (v[0][0] == 'D' && v[0][1] == 'I' && v[0][2] == 'M') {
				cout << v[1] << endl;

				int a = atoi(v[1].c_str());

				places = a;

				cout << "SIZE: " << places << endl;

			} else {
				split(line, v, ' ');
				int vertex = atoi(v[0].c_str());
				if (vertex > 0) {
					longtitudes[vertex] = atoi(v[1].c_str());
					latitudes[vertex] = atoi(v[2].c_str());
				}
			}
		}
		myfile.close();
	}

	else
		cout << "Unable to open file";

	for (int i = 1; i <= places; i++) {
		for (int j = 1; j <= places; j++) {
			distances[i][j] = sqrt(
					power((longtitudes[i] - longtitudes[j]), 2)
							+ power((latitudes[i] - latitudes[j]), 2));
			distances[j][i] = distances[i][j];
		}
	}

	clock_t start = clock();

	long repeats = 0;
	int rate = 0;

	do {

		rate += rate_solve(random_solve());
		repeats++;

	} while (clock() - start < 2000000 || repeats < 10); // 2 sec

	clock_t end = (clock() - start);

	cout << "Time total: " << end << ", repeats: " << repeats << endl;

	cout << "Time per function: " << (double) end / (double) repeats << endl;

	cout << "Avg rate: " << (double) rate / repeats << endl;

	return 0;

}
