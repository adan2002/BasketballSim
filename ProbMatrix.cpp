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
		cout << "Press enter to exit." << endl;
		cin.get();
		exit(0);
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
	cout << "Probability of home team, " << home.getName() << ", winning: " << hometeamwins << endl;
	cout << "Probability of away team, " << away.getName() << ", winning: " << (1.0-hometeamwins) << endl;
	cout << "Setting starters for home team\n";
	home.setstarters();
	cout << "Setting starters for away team\n";
	away.setstarters();

	cout << "Starters set for each team \n" << endl;
	if (home.ifInjuryOnTeam()||away.ifInjuryOnTeam()){
		cout << "Injury!";
		int HTR = home.getStarterRating(); //home team ratings
		cout << "Starter rating for home team: " << HTR << endl;
		cout << "\n\n";
		int ATR = away.getStarterRating(); //away team ratings
		cout << "Starter rating for home team: " << ATR << endl;
		///////changed to this...is this the best way?
		hometeamwins=hometeamwins-(HTR-ATR)/((HTR+ATR)/4);
		//add rankings of both teams.
	}
	//see if there are any probability additons for the home team and add it to a dummy variable
	//see if there are any probability additions for the away team and subtract that from the dummy variable
	hometeamwins=hometeamwins+home.getAddedProb()-away.getAddedProb();

	//account for win streak and losing streak here

	//generate a random number and determine if it is larger or smaller than the probability that the home team wins
	cout << "\ngenerating random number...\n\n";
	rando = float(rand()) / RAND_MAX;
	cout << "random number generated: " << rando << endl;
	//if larger, home team loses, if smaller home team wins
	//run aftergame
	if (rando<hometeamwins){
		home.aftergame('W');
		away.aftergame('L');
		cout << "\nHome team wins!!!\n\n";
	}else{
		home.aftergame('L');
		away.aftergame('W');
		cout << "\nAway team wins!!!\n\n";
	}

	cout << "\nend of game simulation...\n\n";

}


void ProbMatrix::runSeason(string seasonfile) {
	int i,j=0;
	int gamesInSeason=1230;
	//might need to allocate dynamically/or at lease at runtime
	string** games;
	games = new string*[gamesInSeason];
	for (i = 0; i < gamesInSeason; i++){
		games[i] = new string[2];
		//games[1] = new string[2];
	}
	cout << "hello" << endl;
	string line, bit;
	ifstream  inFile(seasonfile);
	if (!inFile){
		cout << "Error opening - " << seasonfile << endl;
		cout << "Press enter to exit." << endl;
		cin.get();
		exit;
	}
	getline(inFile, line); // skip header
	while (getline(inFile,line)){
		stringstream inLine(line);
		for (i=0;i<2;i++){
			getline(inLine,bit,',');
			cout << "team name: " << bit << endl;
			if (bit.find("\r")>0&&bit.find("\r")<4){
			bit.replace(bit.find("\r"),1,"");}

			games[j][i]=bit;
		}
		j++;
	}
	inFile.close();
	i=0;
	j=0;
	int k=0,l=0;

	for(i=0;i<gamesInSeason;i++){
		cout << "\nGame number: " << i+1 << "\n";
		while(teams[j].getName()!=games[i][k]){ // finding home team
			j++;
		}
		k++;
		while(teams[l].getName()!=games[i][k]){ // finding away team
			l++;
		}
		runGame(teams[j],teams[l]);
		k = 0; // reset counters
		l = 0;
		j = 0;
	}

}
