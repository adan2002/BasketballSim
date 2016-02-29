#ifndef PROBMATRIX_H
#define PROBMATRIX_H
#include <stdlib.h> // srand rand 

#include "Team.h"

class ProbMatrix
{
private:
	int n; // number of teams
	float** matrix; // 2D array 
	Team* teams; // list of teams
public:
	ProbMatrix();
	ProbMatrix(int num_teams, Team* list_teams);
	~ProbMatrix();
	void setProb(int row, int col);
	float getProb(int home, int away);
};

// other functions

#endif PROBMATRIX_H