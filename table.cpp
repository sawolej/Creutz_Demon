#include "table.h"
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <cstdlib>
#include<cmath>

using namespace std; 

//-----------------------------------------------------
//constructor
//-----------------------------------------------------
Table::Table(int sizeX, int sizeY, float p_demon) {
    sX= sizeX;
    sY = sizeX;
    arr = new int* [sizeX];
    demon = testDemon= p_demon;
    histDemon.push_back(demon);
    if (arr) {
        for (int i = 0; i < sizeX; i++) {
            arr[i] = new int[sizeY];
        }
    }
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
       arr[i][j] = 1;
        }
    }
    testJ = J = -1 *(sizeX * sizeY * 2);
    maxDemon = demon;    
}

//-----------------------------------------------------
//test function to check if optimalised method is correct
//-----------------------------------------------------

void Table::calcJ() {
    int temp = 0;
    for (int j = 0; j < sY; j++) {
        for (int i= 0; i < sX; i++) {
            if (j == sY-1 && i == 0) {
                temp += -1 * (arr[i][j] * arr[sX - 1][j] + arr[i][j] * arr[0][0]);
            }
            else if (i == 0) {
                temp += -1 *(arr[i][j] * arr[sX - 1][j] + arr[i][j] * arr[i][j + 1]);
            }
            else if (j == sY - 1) {
                temp += -1 * (arr[i][j] *  arr[i - 1][j] + arr[i][j] * arr[i][0]);
            }
            else {
                temp += -1 * (arr[i][j] * arr[i - 1][j] + arr[i][j] * arr[i][j + 1]);
            }
            
        }
    }
    testJ = temp;

}

//-----------------------------------------------------
//show the array
//-----------------------------------------------------

void Table::show() {
    for (int i = 0; i < sX; i++) {
        for (int j = 0; j < sY; j++) {
            cout<< arr[i][j]<<" ";
        }
        cout << "\n";
    }
}

//-----------------------------------------------------
//func to randomly choose and change spin -> change demon and array energy
//-----------------------------------------------------

void Table::changeJ() {

    int x, y;
    error = 0;
    random_device rd;
    uniform_int_distribution<int> distX(0, sX-1);
    uniform_int_distribution<int> distY(0, sY - 1);
    int change;

    x = distX(rd);
    y = distY(rd);

    arr[x][y] *= -1;
    int how=0;

    int xR= (x == sX-1) ? 0 : x+1;
    int yD= (y == sY -1) ? 0 : y+1;
    int xL = (x ==0) ? sX-1 : x-1;
    int yU = (y ==0) ? sY-1 : y-1;
    if (arr[xR][y] == -1) how++;
    if (arr[xL][y] == -1) how++;
    if (arr[x][yU] == -1) how++;
    if (arr[x][yD] == -1) how++;

    if (how == 2) {
        change = 0;
        histDemon.push_back(demon);
        
    }
    else if (how == 4) {
        change = 8;
        if (arr[x][y] == 1) {
            if (demon - change >= 0) {
                demon -= change;
                J += change;
                histDemon.push_back(demon);
            }
            else {
                arr[x][y] *= -1;
                error = 1;
            }
        }
        else {
            demon += change;
            J -= change;
            histDemon.push_back(demon);
        }
        
    }
    else if (how == 3) {
        change = 4;
        if (arr[x][y] == 1) {
        if (demon - change >= 0) {
            demon -= change;
            J += change;
            histDemon.push_back(demon);
        }
        else {
            arr[x][y] *= -1;
            error = 1;
        }
    }
        else {
            demon += change;
            J -= change;
            histDemon.push_back(demon);
        }
    }
    else if (how == 1) {
        change = 4;
       
        
        if (arr[x][y] == 1) {
            demon += change;
            J -= change;
            histDemon.push_back(demon);
           
        }
        else {
            if (demon - change >= 0) {
                demon -= change;
                J += change;
                histDemon.push_back(demon);
            }
            else {
                arr[x][y] *= -1;
                error = 1;
            }
        }
    }
    else if (how == 0) {
        change = 8;
        if (arr[x][y] == 1) {
            demon += change;
            J -= change;
            histDemon.push_back(demon);

        }
        else {
            if (demon - change >= 0) {
                demon -= change;
                J += change;

                histDemon.push_back(demon);
            }
            else {
                arr[x][y] *= -1;
                error = 1;
            }
        }

    }

 
}

//-----------------------------------------------------
//function to analyse taken data - make histogram and calculate temperature
//-----------------------------------------------------
void Table::analyse() {
    ofstream plik;
    plik.open("histogram.txt");
    float a, b, x=0, Sxy = 0, Sx = 0, Sy = 0, Sxx = 0, Syy = 0, srX, srY, sigmaX = 0, sigmaY = 0, srXY = 0, Sx2 = 0, Sy2 = 0, srSx2 = 0, srSy2 = 0, X=0, Y=0;
    int n = histDemon.size();
    int iter = 0;
    int* arrH = new int[maxDemon+1];
    vector <int> temp;
    vector <int> temp2 = histDemon;
    temp = histDemon;
   
    for (int i = 0; i <= maxDemon; i++) {
        
        arrH[i] = 0;
       
    }
    //calculate stable phase
    calcStab();
    //save demon energy in time to file
    //DemonToFile();
    stab *= 200;
    //make histogram
    for (int i = 0; i < (histDemon.size()- stab); i++)
    {
        arrH[histDemon.back()]++;
        histDemon.pop_back();
    }
   // save histogram to file
    int range = 0;
   for (int i=0;i<maxDemon;i++) {
       if (arrH[i] != 0) {
           range++;
           plik << i << " " << arrH[i] << "\n";
           Sx += i;
           Sy += log(arrH[i]);
           Sxx += (i ) * (i);
           Sxy += log(arrH[i]) * (i);
       }
    }

        a = (range * Sxy - Sx * Sy) / (range * Sxx - Sx * Sx);
        a *= -1;
        T = ( 1) / a;
        histDemon.clear();
        MtoFile();
        delete[] arrH;
    }

//-----------------------------------------------------
//calculate magnetism
//-----------------------------------------------------
void Table::calcM() {
        float m = 0;
        for (int i = 0; i < sX; i++) {
            for (int j = 0; j < sY; j++) {
                m+=arr[i][j];
            }
        }
        M = m / float(sX * sY);
        vM.push_back(M);
}
//-----------------------------------------------------
//save magnetism x time to file
//-----------------------------------------------------
void Table::MtoFile() {
    ofstream plik3;
    plik3.open("MxCzas.txt");
    for (int i = 0; i < vM.size(); i++) {
        plik3 << i << " " << vM[i] << "\n";
    }
    vM.clear();
}
//-----------------------------------------------------
//save demon energy x time
//-----------------------------------------------------
void Table::DemonToFile() {
    ofstream plik2;
    plik2.open("Jtime.txt");
    for (int i = 0; i < histDemon.size(); i++) {
        plik2 << i << " " << histDemon[i] << "\n";
    }
    plik2.close();
}
//-----------------------------------------------------
//calc stable phase
//-----------------------------------------------------
void Table::calcStab() {
    int range = histDemon.size() / 200;
    int x, set;
    float srx=0, x2, war;
    float prev = INTMAX_MAX;
    for (int i = 0; i < range; i++) {
        war = 0;
        set = i * 200;
        srx = 0;
        for (int j = 0; j < 200; j++) {
            srx += histDemon[set+ j];
        }
        srx /= 200;
        for (int j = 0; j < 200; j++) {
            float in = histDemon[set + j] - srx;
            war += pow(in, 2);
        }
        war /= 200;
        if (war > prev) {
            stab = i;
            break;
        }
        else {
            prev = war;
        }
    }
    
}