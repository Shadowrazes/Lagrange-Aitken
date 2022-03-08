#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<iomanip>
#include <cmath>

using namespace std;

const double X = 2.25;

struct Eq {
    double x = 0;
    double y = 0;
};

void printVector(vector <Eq>& vect) {
    cout << "X: ";
    for (const auto& it : vect)
        cout << it.x << " ";
    cout << endl;
    cout << "Y: ";
    for (const auto& it : vect)
        cout << it.y << " ";
    cout << endl << endl;
}

void strokeWrap(string& strokeX, string& strokeY, vector <Eq>& equations) {
    while (strokeX.find(" ") != -1) {
        Eq buff = {stod(strokeX.substr(0, strokeX.find(" "))), stod(strokeY.substr(0, strokeY.find(" "))) };
        strokeX.erase(0, strokeX.find(" ") + 1);
        strokeY.erase(0, strokeY.find(" ") + 1);
        equations.push_back(buff);
    }
}

double func(vector <Eq>& equations, int xInd) {
    double mul = 1;
    for (int i = 0; i < equations.size(); i++) {
        if (i != xInd) {
            mul *= (X - equations[i].x) / (equations[xInd].x - equations[i].x);
        }
    }
    return mul;
}

void eitkenFunc(vector <Eq>& equations, vector <Eq>& equationsCopy, int itNum) {
    for (int i = 0; i < equations.size() - itNum; i++) {
        equationsCopy[i].y = 1.0 / (equations[i + itNum].x - equations[i].x) *
            (equationsCopy[i].y * (equations[i + itNum].x - X) - equationsCopy[i + 1].y * (equations[i].x - X));
    }
}

void lagrange(vector <Eq>& equations, vector <Eq>& equationsCopy) {
    for (int i = 0; i < equationsCopy.size(); i++) {
        equationsCopy[i].x = func(equations, i);
    }
    double sum = 0;
    for (int i = 0; i < equationsCopy.size(); i++) {
        sum += equationsCopy[i].x * equationsCopy[i].y;
    }
    cout << "Lagrange: " << sum << endl;
}

void eitken(vector <Eq>& equations, vector <Eq>& equationsCopy) {
    for (int i = 0; i < equationsCopy.size() - 1; i++) {
        eitkenFunc(equations, equationsCopy, i + 1);
    }
    cout << "Eitken: " << equationsCopy[0].y << endl;
}

int main()
{
    fstream matrixData("Polynomial.txt");
    vector <Eq> equations;

    while (!matrixData.eof()) {
        string buffX;
        string buffY;
        getline(matrixData, buffX);
        getline(matrixData, buffY);
        strokeWrap(buffX, buffY, equations);
    }
    vector <Eq> equationsCopy = equations;
    printVector(equations);
    lagrange(equations, equationsCopy);
    equationsCopy = equations;
    eitken(equations, equationsCopy);
}