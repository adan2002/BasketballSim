// Adan Rivas
// ENGS 65
// 16W
// 1/29/16

// Project 3: Symmetric Matrices

/*
Objective: Build an ADT for symmetric matrix that catlogs travel distances between cities. 

In a symmetric matrix the cells in the upper right are the same as the cells in the lower
left, i.e entry (i,j) = (j,i). So this ends up reducing to to an upper triangular matrix 
of size N-1xN-1 because the main diagonal is full of zeros. So we only need to store either 
the upper and lower diagonal entries.

My data structure will reduce the table of miles to a 1D array and thus store only half of 
the matrix. But the user will still believe that they are interacting with a matrix/table.

final 1D is going to look like:

[1108, 708, 994,  756,   1753,  279,  2191,  3017,  2048,  2288,  854,  222,  809,  649,  2794]

Assume matrix has already exists...

Since mileage maps are indexed by city names, we may consider using enumerated types.

	Atl   Bos   Chi   Det   LA    NY
Atl  0    1108  708   756  2191   854
Bos 1108    0   994  1753  3017   222
Chi 708    994    0   279  2048   809
Det 756   1753  279     0  2288   649
LA 2191   3017 2048  2288     0  2794
NY  854    222  809   649  2794     0

Assume data types are floats for some precision of distance in miles.

I can expect that a NxN symmetric matrix with its main diagonal filled with zeros will
have a total of (N-1)*N/2 elements to store (similar algorithm to a triangular matrix of size (N-1)x(N-1). 

An auxilliary function would include adding another city to the table and how I would need 
to redefine my 1D array. I can also consider creating a dynamic structure out the milage table
*/

#include <iostream>
#include "sym_mat.h"

using namespace std;

int main()
{
	cout << "program starting...\n\n";

	// enumerate city names by index in table
	int Atl = 0;
	int Bos = 1;
	int Chi = 2;
	int Det = 3;
	int LA = 4;
	int NY = 5;

	int num_of_cities = 6; // size of table

	// create miles table
	float distances[6][6] = {
		{ 0.0, 1108.0, 708.0, 756.0, 2191.0, 854.0 },
		{ 1108.0, 0.0, 994.0, 1753.0, 3017.0, 222.0 },
		{ 708.0, 994.0, 0.0, 279.0, 2048.0, 809.0 },
		{ 756.0, 1753.0, 279.0, 0.0, 2288.0, 649.0 },
		{ 2191.0, 3017.0, 2048.0, 2288.0, 0.0, 2794.0 },
		{ 854.0, 222.0, 809.0, 649.0, 2794.0, 0.0 }
	};

	// create mileage table through a dynamically allocated 2D array
	cout << "creating dynamic 2D array\n" << endl; 
 	float ** miles_tbl = new float*[num_of_cities]; //allocate array of float pointers
	
	//run a for loop to instatiante a 2D array
	for (int i = 0; i < num_of_cities; i++)
	{
		miles_tbl[i] = new float[num_of_cities]; //allocate each array of floats
		for (int j = 0; j < num_of_cities; j++)
		{
			miles_tbl[i][j] = distances[i][j]; // assign a value
		}
	}

	// delete matrix
	//delete[] distances;

	Sym_Mat sym_matrix(num_of_cities, miles_tbl); // create class 
	cout << "Distance from Boston to Atlanta: ";
	cout << sym_matrix.get_distance(Bos, Atl) << endl; 
	cout << endl; // add white space

	cout << "Distance from Chicago to Detroit: ";
	cout << sym_matrix.get_distance(Chi, Det) << endl;
	cout << endl; // add white space

	cout << "Distance from Detroit to Chicago: ";
	cout << sym_matrix.get_distance(Det, Chi) << endl;
	cout << endl; // add white space
	
	// Test change distance member function
	cout << "Update distance between Boston and Chicago. " << endl;
	cout << "Original value: " << sym_matrix.get_distance(Bos, Chi) << endl;
	sym_matrix.change_distance(Bos, Chi, 200);
	cout << "New value: " << sym_matrix.get_distance(Bos, Chi) << endl;
	cout << "Distance from Chicago to Boston: ";
	cout << sym_matrix.get_distance(Chi, Bos) << endl;
	cout << endl;
	
	cout << "convert table indices to corresponding vector ones: \n";
	cout << "(LA, NY) = " << fromMatrixToVector(LA, NY) << endl;
	cout << "(5, 2) = " << fromMatrixToVector(5, 2) << endl;
	
	cout << "\nExiting program. Press enter to exit." << endl;

	cin.get();

	return 0;

}

