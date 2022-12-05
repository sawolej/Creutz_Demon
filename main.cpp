#include <iostream>
#include <fstream>
#include "table.h"

using namespace std;


int main() {

	int x, y, n, a;
	vector<int> demonInit;
	ifstream file;
	ofstream fileOut;
	ofstream fileOut2;
	fileOut2.open("MxCzas.txt");
	fileOut.open("MxT.txt");
	file.open("data.txt");

	int i;
	file >> x >> y >> n >> a;
	while (file >> i) {
		demonInit.push_back(i);
	}

	for (int i = 0; i < a; i++) {
		vector<float> m;
		vector<float> E;
		float mM=0;
		int size;
		Table demon (x, y, demonInit[i]);
		for (int j = 0; j < n; j++) {
			do {
				demon.changeJ();
			} while (demon.error == 1);
			demon.calcM();
			fileOut2 << j << " " << demon.M << "\n";
			m.push_back(demon.M);			
		}
		demon.analyse();
		size = m.size();
		int dowhile = n - demon.stab;
		while (!m.empty()&& dowhile>0) {
			dowhile--;
			mM += m.back();
			m.pop_back();			
		}
		fileOut << log(demon.T) << " " << mM / size << "\n";
	}


	return 0;    

}