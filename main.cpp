#include <iostream>

#include "table.h"

using namespace std;

/*
#1 create a 2d table and initialise it with max energy values
#2 create Demon and initialise its energy
#3 make public vector with demon energy changing in time
#4 random(?) swap values in the table and update demon energy (add to vector) (how many times?)
#5 make a histogram of energy (how many occurance)


*/
int main() {

	Table Demon(4, 40); //table size, demon energy
	Demon.show();
	cout << "energy: " << Demon.J << "\ndemon energy: " << Demon.demon <<"\n";
	Demon.changeJ();
	cout << "energy: " << Demon.J << "\ndemon energy: " << Demon.demon << "\n";
	for(int i =0; i<100; i++){
	Demon.changeJ();
	//cout << "energy: " << Demon.J << "\ndemon energy: " << Demon.demon << "\n";
}
Demon.histogram();
	Demon.show();
	cout << "energy: " << Demon.J << "\ndemon energy: " << Demon.demon << "\n";
	return 0;    
}