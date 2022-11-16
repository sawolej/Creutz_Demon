#pragma once
#include <vector>
#ifndef TABLE_H
#define TABLE_H

using namespace std; 

class Table {
private:
	int s;
	int** arr;
	int minJ;


public:
	vector <int> histDemon;
	int demon;
	int J;
	Table(int size, float p_demon);
	void calcJ();
	void changeJ(int x = 666, int y = 666);
	void show();
	void histogram();
	void sSum();

};

#endif // !TABLE_H


