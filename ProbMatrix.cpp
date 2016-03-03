#include "ProbMatrix.h"
#include "Team.h"

#include <iostream>
#include <stdlib.h> // srand rand 
#include <vector>
#include <sstream> // reading in strings as buffers
#include <fstream> // read in data
#include <string>

using namespace std;

ProbMatrix::ProbMatrix() // default constructor
{
	numTeams = 0;
}

void ProbMatrix::setSize(int num_teams)
{
	numTeams = num_teams;
}

void ProbMatrix::addTeams(Team* list_teams, int num_teams) // parameterized constructor

{  // think about linking ProbMatrix with Team class
	teams = new Team[num_teams]; //  create an array of Teams
	for (int i = 0; i < num_teams; i++){
		teams[i] = list_teams[i]; // copy over
	}
}


ProbMatrix::ProbMatrix(int num_teams, Team* list_teams) // parameterized constructor

{  // think about linking ProbMatrix with Team class
	teams = new Team [num_teams]; //  create an array of Teams
	for (int i=0; i < num_teams; i++){
		teams[i] = list_teams[i]; // copy over
		teams[i].enumerate(i); // enumerate each variable
	}
	

	float** matrix = new float*[num_teams]; //allocate array of float pointers

	// initialize values in matrix
	for (int j = 0; j < num_teams; j++)
	{
		matrix[j] = new float[num_teams]; //allocate each array of floats
		for (int k = 0; k < num_teams; k++)
		{
			matrix[j][k] = 4;
		}
	}
	
	
}

ProbMatrix::~ProbMatrix() // destructor
{ 
}

// overload [] operator to 
void ProbMatrix::setProb(string fname, int num_teams) // requries index in table
{
	// read csv file

	string line, bit;
	ifstream  inFile(fname);
	
	if (!inFile){
		cout << "Error opening - " << fname << endl;
		cout << "\Press enter to exit." << endl;
		cin.get();
		exit;
	}

	matrix = new float*[num_teams];
	
	for (int row = 0; row < numTeams; row++){
		matrix[row] = new float[num_teams]; // add a row
		getline(inFile, line); // read in row

		for (int col = 0; col < numTeams; col++){
			stringstream lineStream(line);
			getline(lineStream, bit, ',');
			matrix[row][col] = stof(bit);


		}
	}
	float r = 4.0;//((float)rand() / (RAND_MAX)); // random number between 0 and 1

}


//function that returns probability of hometeam winning
float ProbMatrix::getProb(Team home, Team away){
	return(matrix[home.getIndex()][away.getIndex()]);
}

// other functions

void ProbMatrix::runGame(Team home, Team away){
	float rando;
	//get probability of winning for the home team
	float hometeamwins=getProb(home, away);
	home.setstarters();
	away.setstarters();

	if (home.ifInjuryOnTeam()||away.ifInjuryOnTeam()){
		int HTR=home.getStarterRating(); //home team ratings
		int ATR=away.getStarterRating(); //away team ratings
		///////NOT GOOD ENOUGH/not proportional
		hometeamwins=hometeamwins-ATR/HTR;
		//add rankings of both teams.
	}
	//see if there are any probability additons for the home team and add it to a dummy variable
	//see if there are any probability additions for the away team and subtract that from the dummy variable
	hometeamwins=hometeamwins+home.getAddedProb()-away.getAddedProb();

	//generate a random number and determine if it is larger or smaller than the probability that the home team wins
	rando=rand()/RAND_MAX;
	//if larger, home team loses, if smaller home team wins
	//run aftergame
	if (rando<hometeamwins){
		home.aftergame('W');
		away.aftergame('L');
	}else{
		home.aftergame('L');
		away.aftergame('W');
	}

}

