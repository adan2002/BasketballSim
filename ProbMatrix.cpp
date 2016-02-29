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


//function that returns probability of hometeam winning
float ProbMatrix::getProb(int home, int away){
	return(matrix[home][away]);
}

// other functions

void ProbMatrix::runGame(Team home, Team away){
	float rand;
	//get probability of winning for the home team
	float hometeamwins=getProb(home.getIndex(), away.getIndex());

	//see if there are any probability additons for the home team and add it to a dummy variable
	//see if there are any probability additions for the away team and subtract that from the dummy variable
	hometeamwins=hometeamwins+home.getAddedProb()-away.getAddedProb();

	//generate a random number and determine if it is larger or smaller than the probability that the home team wins
	rand=rand()/RAND_MAX;
	//if larger, home team loses, if smaller home team wins
	//run aftergame
	if (rand<hometeamwins){
		home.aftergame('W');
		away.aftergame('L');
	}else{
		home.aftergame('L');
		away.aftergame('W');
	}

}

