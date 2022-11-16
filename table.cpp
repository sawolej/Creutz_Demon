#include "table.h"
#include <iostream>
#include <random>
#include <vector>
#include <fstream>

using namespace std; 

Table::Table(int size, float p_demon) {
    arr = new int* [size];
    s = size;
    demon = p_demon;
    histDemon.push_back(demon);
    if (arr) {
        for (int i = 0; i < size; i++) {
            arr[i] = new int[size];
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            /*if((i+j)%2==0) arr[i][j] = -1;
            else arr[i][j] = 1;*/
       arr[i][j] = 1;
        }
    }
    calcJ();
}

void Table::calcJ() {
    int temp = 0;
   // cout << "start: " << temp <<"\n";
    for (int j = 0; j < s; j++) {
        for (int i= 0; i < s; i++) {
            if (j == s-1 && i == 0) {
                temp += -1 * (arr[i][j] * arr[s - 1][j] + arr[i][j] * arr[0][0]);
               // cout << "step róg: " << temp << "\n";
            }
            else if (i == 0) {
                temp += -1 *(arr[i][j] * arr[s - 1][j] + arr[i][j] * arr[i][j + 1]);
               // cout << "step i==0: " << temp << "\n";
            }
            else if (j == s - 1) {
                temp += -1 * (arr[i][j] *  arr[i - 1][j] + arr[i][j] * arr[i][0]);
               // cout << "step: j koniec" << temp << "\n";
            }
            else {
                temp += -1 * (arr[i][j] * arr[i - 1][j] + arr[i][j] * arr[i][j + 1]);
              //  cout << "step: else " << temp << "\n";
            }
            
        }
    }
    J = temp;
}
void Table::show() {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            cout<< arr[i][j]<<" ";
        }
        cout << "\n";
    }
}
void Table::changeJ(int x, int y) {

    random_device rd;
    uniform_int_distribution<int> dist(0, s-1);
    int change;
    if (x >= s && y >= s) {
        x = dist(rd);
        y = dist(rd);
    }

    //temp += -1 * (arr[i][j] * arr[i - 1][j] + arr[i][j] * arr[i][j + 1]);
    // 
    cout << "x i y: " << x << " " << y << "\n";

    if (y == s - 1 && x == 0) {
        if (arr[s - 1][y] == -1 && arr[x][0] == -1) change = 0;
        else if (arr[s - 1][y] == -1 || arr[x][0] == -1) change = 4;
        else change = 8;
    }
    else if (x == 0) {
        if (arr[s-1][y] == -1 && arr[x][y + 1] == -1) change = 0;
        else if (arr[s-1][y] == -1 || arr[x][y + 1] == -1) change = 4;
        else change = 8;
    }
    else if (y == s - 1) {  
        if (arr[x - 1][y] == -1 && arr[x][0] == -1) change = 0;
        else if (arr[x - 1][y] == -1 || arr[x][0] == -1) change = 4;
        else change = 8;
    }
    else {
        if (arr[x - 1][y] == -1 && arr[x][y + 1] == -1) change = 0;
        else if (arr[x - 1][y] == -1 || arr[x][y + 1] == -1) change = 4;
        else change = 8;
    }
  //  cout << "i: " << x << ", j: " <<y << "\n";
    arr[x][y] *= -1;

    //cout << diff << "\n";
    if (arr[x][y]==1) { // new energy is lower, demon inscrease energy 
        //cout << prevJ << " - " << J << " demon increase energy \n";
        demon += change;
        J -= change;
    }
    else { // new energy higher, demon lose energy
       // cout << prevJ << " - " << J << " demon loose energy \n";
       // cout << demon << " <demonE, " << diff << "zmiana \n";
        if (demon - change>=0) {
            demon -= change;
            J += change;
           
        }
        else {
         //   cout << "no! ho doesnt have energy! \n";
            arr[x][y] *= -1;
            
        }
 
    }
    histDemon.push_back(demon);
}

void Table:: histogram() {
    fstream plik;
    float a, b, Sxy = 0, Sx = 0, Sy = 0, Sxx = 0, Syy = 0, srX, srY, sigmaX = 0, sigmaY=0;
    int n = histDemon.size();
    plik.open("time.txt", ios::out | ios::app);
    int iter = 0;
    int arr[100000] = { 0 };
    vector <int> temp;
    temp = histDemon;
    while (!histDemon.empty())
    {
        arr[histDemon.back()]++;
        histDemon.pop_back();
    }
    
    if (plik.good() == true)
    {
        plik << temp.size() << " J x TIME \n";
        
        for (int i = 0; i < temp.size(); i++) {
            plik << temp[i];
           /* for (int j = 0; j < temp[i]; j++) {
                plik << "*";
            }*/
            plik << "\n";
        }
        plik.close();
    }


    for (int i = 0; i <= 100000; i++) {
        
        if(arr[i]>0){
            //wyniki
        cout << i << ": ";
        if (i < 10) cout << "  ";
        else if(i<100) cout << " ";
        for (int j = 0; j < arr[i]; j++) {
            cout << "*";
        }
        cout << "\n";
        //obliczenia
        Sx += i;
        Sy += arr[i];
        Sxx += i * i;
        Syy += arr[i]*arr[i];
        Sxy += arr[i] * i;
        iter++;
        }
    }

    srX = Sx / iter;
    srY = Sy / iter;
    for (int i = 0; i <= 100000; i++) {
        if (arr[i] > 0) {
            sigmaX += pow((i - srX), 2);
            sigmaY += pow((arr[i] - srY), 2);
        }
    }
    sigmaX /= n;
    sigmaY /= n;
    sigmaX = sqrt(sigmaX);
    sigmaY = sqrt(sigmaY);
    cout << " sigma X i Y: " << sigmaX << " " << sigmaY << "\n";
    cout << Sxy << " jezus\n";
    cout << Sx * Sy << " jezus\n";
    float r = (Sxy - (Sx * Sy)) / sigmaX * sigmaY;
    cout << "wspolczynnik korelacji: " << r << "\n";
}

void Table::sSum() {
  
}