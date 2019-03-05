#include <iostream>
#include <fstream>

// To convert a directed graph with weight to incidence matrix, edge listing, positive direction table and adjacency list

using namespace std;

int main() {
	ifstream input;
	input.open("input.txt", ios::in);
	int n, m = 0;
	input >> n;
//	cout << n <<endl;
	int *weight = new int[n * n];
	// Do NOT new a n*n matrix. That's disgusting.
	for (int i = 0; i < n * n; i++) {
		input >> weight[i];
		if (weight[i] > 0)
			m++;
	}
	input.close();

	// incidence matrix
	int *incidence = new int[n * m]();  // init with 0
	// edge listing
	int *edgeList = new int[3 * m];
	// positive direction table
	int *positiveHead = new int[n + 1](); // init with 0
	positiveHead[n] = m + 1;
	int *positive = new int[2 * m];
	int ite = 0;
	// adjacency list
	int *adjacent = new int[2 * m + n];
	int adIte = 0, flag = 0;
	for (int i = 0; i < n * n; i++){
		if (weight[i] > 0){
			incidence[(i / n) * m + ite] = 1;
			incidence[(i % n) * m + ite] = -1;

			edgeList[ite] = i / n + 1;  // Since the points start at 1
			edgeList[ite + m] = i % n + 1;
			edgeList[ite + 2 * m] = weight[i];

			if (positiveHead[i / n] == 0)
				positiveHead[i / n] = ite + 1; // not +1 when output
			positive[ite] = i % n + 1;  // Not +1 when output
			positive[ite + m] = weight[i];

			if ((i / n) != flag) {
				flag++;
				adjacent[adIte++] = 0;
			}
			adjacent[adIte++] = weight[i];
			adjacent[adIte++] = i % n + 1;

			ite++;
		}
	}

	ofstream output;
	output.open("output.txt", ios::out);

	for (int i = 0; i < n * m;){
		output << incidence[i++] << " ";
		if (i % n == 0)
			output << "\n";
	}
	delete[] incidence;

	for (int i = 0; i < 3 * m;){
		output << edgeList[i++] << " ";
		if (i % m == 0) {
			output << "\n";
		}
	}
	delete[] edgeList;

	for (int i = 0; i < n + 1; i++) {
		output << positiveHead[i] << " ";
	}
	delete[] positiveHead;

	for (int i = 0; i < 2 * m; i++) {
		if (i % m == 0) {
			output << "\n";
		}
		output << positive[i] << " ";
	}
	delete[] positive;

	output << "\n";
	for (int i = 0; i < 2 * m + n; i++) {
		if (adjacent[i] == 0){
			output << "\n";
		} else {
			output << adjacent[i] << " ";
		}
	}
	delete[] adjacent;
	output << "\n";
	output.close();

	return 0;
}