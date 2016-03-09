#ifndef PROBMATRIX_H
#define PROBMATRIX_H

#include <iostream>
#include <string>
#include <stdlib.h> // srand rand 

#include "Team.h"

using namespace std;

class ProbMatrix
{
private:
	int numTeams; // number of teams
	float** matrix; // 2D array 
	Team* teams; // list of teams
public:
	ProbMatrix();
	~ProbMatrix();
	ProbMatrix(int num_teams, Team* list_teams);
	void setSize(int num_teams);
	void addTeams(Team* list, int num_teams);
	void setProb(string fname, int num_teams); // pass in filename
	float getProb(Team home, Team away);
	void runGame(Team home, Team away);
	void runSeason(string seasonfile);
};

// other functions

Team** groupTeams(Team* teams);

#endif //PROBMATRIX_H