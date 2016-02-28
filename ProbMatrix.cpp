#include "ProbMatrix.h"
#include "Team.h"
#include <stdlib.h> // srand rand 

ProbMatrix::ProbMatrix() // default constructor
{
	n = 0;
	matrix = 0;
	teams = new Team[]; // empty array
}

ProbMatrix::ProbMatrix(int num_teams, Team* list_teams) // parameterized constructor
{  // think about linkin ProbMatrix with Team class
	teams = new Team [num_teams]; //  create an array of Teams
	for (int i=0; i < num_teams; i++){
		teams[i] = list_teams[i]; // copy over
		teams[i].enumerate(i); // enumerate each variable
	}
	n = 0;

	float** matrix = new float*[num_teams]; //allocate array of float pointers

	// initialize values in matrix
	for (int j = 0; j < num_teams; j++)
	{
		matrix[j] = new float[num_teams]; //allocate each array of floats
		for (int k = 0; k < num_teams; k++)
		{
			setProb(j, k); // assign a value
		}
	}
	
	teams = 0;
}

ProbMatrix::~ProbMatrix()
{
}

// overload [] operator to 
void ProbMatrix::setProb(int row, int col) // requries index in table
{
	float r = ((float)rand() / (RAND_MAX)); // random number between 0 and 1

	matrix[row][col] = r;
}


// other functions

