#pragma once
#include <vector>
#ifndef TABLE_H
#define TABLE_H

using namespace std; 

class Table {
private:
	int sX;
	int sY;
	int** arr;
	


public:
	vector <int> histDemon;
	vector <float> vM;
	int demon;
	int testDemon;
	int J;
	int testJ;
	int maxDemon;
	float M;
	float T;
	int iter;
	float A;
	bool error;
	int stab;


	Table(int sizeX, int sizeY, float p_demon);
	void calcJ();
	void changeJ();
	void show();
	void analyse();
	void calcM();
	void MtoFile();
	void DemonToFile();
	void calcStab();
};

#endif // !TABLE_H


