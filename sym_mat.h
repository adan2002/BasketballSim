#pragma once

#ifndef SYM_MAT_H_
#define SYM_MAT_H_

#include <iostream>
#include <string> // allows the use of strings
using namespace std;

class Sym_Mat
{
private:
	float* arr; // core class member, 1D array
public:
	Sym_Mat(); // empty constructor
	Sym_Mat(int N, float** tbl); // parameterized constructor
	~Sym_Mat(); // destructor
	float get_distance(int city1, int city2); // city names are enumerated
	void change_distance(int city1, int city2, float new_distance);
};

// other functions

int fromMatrixToVector(int row, int col); // conver matrix index to corresponding one in array
int sizeOfArray(int N); // determine the size of array to create based on dimension of symmertic matrix

#endif /* SYM_MAT_H_ */