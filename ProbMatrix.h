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
	float** matrix; // 2D array containing the probabilities that the home team wins
	Team* teams; // list of teams
public:
	ProbMatrix(); //constructor
	~ProbMatrix(); //destructor
	ProbMatrix(int num_teams, Team* list_teams); //parameterized constructor
	void setSize(int num_teams); //set size of the matrix
	void addTeams(Team* &list, int num_teams); //add teams to the matrix-input type: team array
	void setProb(string fname, int num_teams); // set probability-input: csv with calculated probabilities
	float getProb(Team &home, Team &away); //get a probability that a home team will win
	void runGame(Team &home, Team &away); //run a game between two teams
	void runSeason(string seasonfile); //run a season-input: csv file with the list of games
};

// other functions

//Team** genStandings(Team* teams);
void genStandings(Team* teams);

#endif //PROBMATRIX_H