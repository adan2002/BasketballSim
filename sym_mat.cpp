#include "sym_mat.h"

#include <iostream>
#include <string> # allows the use of strings
#include <array>

using namespace std;

// constructor
Sym_Mat::Sym_Mat()
{
	arr[10];
}

// destructor
Sym_Mat::~Sym_Mat()
{
}

// parameterized constructor
Sym_Mat::Sym_Mat(int N, float** tbl)
{
	int size;
	size = sizeOfArray(N);
	cout << "size of array " << size << endl;
	cout << endl;
	arr = new float[size]; // instatiante size of class member

	
	int idx = 0;
	// loop through table and store valid entries
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			if (i > j){ // only looking at entries below main diagonal
				arr[idx] = tbl[i][j];
				//cout << "index: " << idx << endl; 
				idx++;
			}
		}
	}
}


// updatae distance between two cities in table
void Sym_Mat::change_distance(int city1, int city2, float new_distance)
{
	int index = fromMatrixToVector(city1, city2); // get 1D array matrix
	arr[index] = new_distance; // change value
}

// obtain travelling distance between two cities
float Sym_Mat::get_distance(int city1, int city2) //assume valid city abbrv has been inputted
{
	int index = fromMatrixToVector(city1, city2);
	float distance = arr[index];
	return (distance);
}


// other functions 

int fromMatrixToVector(int row, int col) // input and row index and column index
{
	if (row >= col)
		return (row - 1)*row / 2 + col;
	else if (row  == col)
	{
		cout << "Start and End cities are the same" << endl;
		return -1;
	}
	else
		return (col - 1)*col / 2 + row;
}

/*
I stored the lower diagonal entries into the 1D row by row. Therefore each succeding row will
have one more additonal entry than the previous one, ranging from 1 to N-1 objects.
Therefore I could use the formula (i-1)*i/2 to count the all the objects in the i rows before
it. This works because our index starts at 0. After that, we can use the j index (columns) to
determine how many object across the row our element of interest is.
*/
int sizeOfArray(int N)
{
	int size;
	size = (N - 1)*N / 2;
	return size;
}
