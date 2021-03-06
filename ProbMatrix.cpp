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
	numTeams = 0; // no teams in league
}

ProbMatrix::~ProbMatrix() // destructor
{
	cout << "deleting the matrix" << endl;
	delete[] teams; teams = NULL; // remove pointer from memory
	delete[] matrix; matrix = NULL;
}

void ProbMatrix::setSize(int num_teams)
{
	numTeams = num_teams;
}

void ProbMatrix::addTeams(Team* &list_teams, int num_teams) // parameterized constructor

{  // think about linking ProbMatrix with Team class
	teams = list_teams;
}

ProbMatrix::ProbMatrix(int num_teams, Team* list_teams) // parameterized constructor

{  // think about linking ProbMatrix with Team class
	teams = new Team [num_teams]; //  create an array of Teams
	for (int i=0; i < num_teams; i++){
		teams[i] = list_teams[i]; // copy over
		teams[i].enumerate(i); // enumerate each variable
	}
	
}

// overload [] operator to 
void ProbMatrix::setProb(string fname) // requries index in table
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

	//initialize matrix
	matrix = new float*[numTeams];
	//fill matrix
	for (int row = 0; row < numTeams; row++){
		matrix[row] = new float[numTeams]; // add a row
		getline(inFile, line); // read in row

		for (int col = 0; col < numTeams; col++){
			stringstream lineStream(line);
			getline(lineStream, bit, ',');
			matrix[row][col] = stof(bit);
		}
	}

}


//function that returns probability of hometeam winning
float ProbMatrix::getProb(Team &home, Team &away){
	return(matrix[home.getIndex()][away.getIndex()]);
}

// other functions

//RUN A GAME
void ProbMatrix::runGame(Team &home, Team &away){
	//srand(time(NULL));
	float rando;

	float homePenalty, awayPenalty; // use to keep track of 
		// reduced probability if an injured player if forced to 
		// start.
	//get probability of winning for the home team
	float hometeamwins=getProb(home, away);
	//cout << "Probability of home team winning: " << hometeamwins << endl;
	homePenalty=home.setstarters();
	awayPenalty=away.setstarters();

	//if there is an injury on either team, a modification to the static probability must be made
	if (home.ifInjuryOnTeam()||away.ifInjuryOnTeam()){

		//compare the starters rating of the home team to the away team
		//if there is an injury, then a usual starter is replaced by a backup

		//gets the sum of the rankings of the starters on the home and away teams
		int HTR = home.getStarterRating(); //home team ratings
		int ATR = away.getStarterRating(); //away team ratings
		
		//re-evaluates the proability that the home team wins based on the new starters
		hometeamwins=hometeamwins-(ATR-HTR)/((HTR+ATR)/4);

	}

	//adds probability to the home team winning if away team has an injured starter
	//subtracts if home teams as an injured starter
	hometeamwins = hometeamwins + awayPenalty - homePenalty;

	//account for win streak and losing streak here
	if (home.getWstreak()>0){
		hometeamwins=hometeamwins+0.01;
	}
	if (away.getWstreak()>0){
		hometeamwins=hometeamwins-0.01;
	}
	if (away.getLstreak()>0){
		hometeamwins=hometeamwins+0.01;
	}
	if (home.getLstreak()>0){
		hometeamwins=hometeamwins-0.01;
	}


	//generate a random number and determine winner of game 
	rando = rand() / (float)RAND_MAX;
	//cout << "Random number generated to determine winner of game: " << rando << endl;
	//if larger, home team loses, if smaller home team wins

	//run aftergame
	if (rando<hometeamwins){
		//cout<<" home wins"<<endl;
		home.aftergame('W');
		away.aftergame('L');
	}else{
		home.aftergame('L');
		away.aftergame('W');
	}
}

//run season
void ProbMatrix::runSeason(string seasonfile) {
	int i,j=0;
	//amount of games in the season
	int gamesInSeason=1230;
	//dynamically allocates memory
	string** games;
	//games is allocated to 1230
	games = new string*[gamesInSeason];

	//imports the csv file into games array
	for (i = 0; i < gamesInSeason; i++){
		games[i] = new string[2];
	}
	string line, bit;
	ifstream  inFile(seasonfile);
	if (!inFile){
		cout << "Error opening - " << seasonfile << endl;
		cout << "Press enter to exit." << endl;
		cin.get();
		exit(0);
	}
	// store season match wins into a 2Darray
	getline(inFile, line); // skip header
	while (getline(inFile,line)){
		stringstream inLine(line);
		for (i=0;i<2;i++){
			getline(inLine,bit,',');
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

	//function iterates through the games in season and runs each game
	for(i=0;i<gamesInSeason;i++){
		//cout << "\nGame number: " << i+1 << "\n\n";
		while(teams[j].getName()!=games[i][k]){ // finding home team
			j++;
		}
		k++;
		while(teams[l].getName()!=games[i][k]){ // finding away team
			l++;
		}
		//run game between home and away team
		runGame(teams[j],teams[l]);
		k = 0; // reset counters
		l = 0;
		j = 0;
	}

}

// other functions

/*
The function belows prints out the standings for each conference
based off wins over a season. The NBA has six divisions and each division 
consist of 5 teams. One way to sort them is by creating a 6x5 matrix, where
each divison will match the row index + 1, assuming the count begins at 0. 
Teams in division 1-3 are eastern conference teams, while divisions 4-6 represent
western conference teams.
*/

void genStandings(Team* teams){
	Team** divisions = 0; // 2D array 
	divisions = new Team*[6]; // 6 rows (one for each division)
	int numTeams = 30; // number of NBA franchises
	Team swap; 

	// bubble sort algorithm, sort teams array by division enumeration
	// i.e. group teams by division from list of teams
	for (int i = 0; i < numTeams - 1; i++){ // go up to second to last elements
		for (int j = 0; j < numTeams - i - 1; j++){
			if (teams[j].getDiv() > teams[j + 1].getDiv()){ /* For decreasing order use < */
				swap = teams[j];
				teams[j] = teams[j + 1];
				teams[j + 1] = swap;
			}
		}
	}

	// teams are sorted, now store into divisions matrix, 6X5
	int idx = 0;
	for (int i = 0; i < 6; i++){ // for every division
		divisions[i] = new Team[5]; // create 5 elements
			// each division consists of five teams
		for (int j = 0; j < 5; j++){ // add teams that belong to that row
			divisions[i][j] = teams[idx];
			idx++; // move onto to nex team
		}
	}

	// now sort teams in each divsion by wins in descending order

	for (int i = 0; i < 6; i++){ // for each division
		// use bubble sort algorithm to arrange from best to worst records
		for (int c = 0; c < 5 - 1; c++){ // 5 teams in each division
			for (int d = 0; d < 5 - c - 1; d++){
				if (divisions[i][d].getAvgWins() < divisions[i][d + 1].getAvgWins()){ // if next teams has more wins
							// then swap.
					swap = divisions[i][d];
					divisions[i][d] = divisions[i][d + 1];
					divisions[i][d + 1] = swap;
				}
			}
		}

	}


	/*
	The sorting algorithm used was to group each team based off the place they finished
	in their respecitve division/conference. Thus, for each conference we have five groups
	of three teams, which we sort by wins.
	
	The top eight teams from each conference makes the playoffs. But the top four is comprised 
	of the 3 division winners and the team with the best record from the other 12 in a 
	conference. These four teams are sorted based off record, and so are the reamining teams
	in the conference.
	*/

	Team* e1 = new Team[3]; // 1st place finishers of east divisions
	Team* e2 = new Team[3]; // 2nd place finishers of east divisions...
	Team* e3 = new Team[3]; Team* e4 = new Team[3]; 
	Team* e5 = new Team[3];

	Team* w1 = new Team[3]; // 1st place finishers of western divisions..
	Team* w2 = new Team[3]; Team* w3 = new Team[3];
	Team* w4 = new Team[3]; Team* w5 = new Team[3];

	for (int i = 0; i < 3; i++){
		e1[i] = divisions[i][0]; // all the 1st place teams from eastern divisions
		e2[i] = divisions[i][1]; e3[i] = divisions[i][2];
		e4[i] = divisions[i][3]; e5[i] = divisions[i][4];

		w1[i] = divisions[i + 3][0]; // all the 1st place teams from western divisions
		w2[i] = divisions[i + 3][1]; w3[i] = divisions[i + 3][2];
		w4[i] = divisions[i + 3][3]; w5[i] = divisions[i + 3][4];
	}

	// use bubble sort algorithm to arrange from best to worst records
	for (int c = 0; c < 3 - 1; c++){ // 3 teams in each list
		for (int d = 0; d < 3 - c - 1; d++){
			if (e1[d].getAvgWins() < e1[d + 1].getAvgWins()){
				swap = e1[d];
				e1[d] = e1[d + 1];
				e1[d + 1] = swap;
			}
			if (e2[d].getAvgWins() < e2[d + 1].getAvgWins()){
				swap = e2[d];
				e2[d] = e2[d + 1];
				e2[d + 1] = swap;
			}
			if (w1[d].getAvgWins() < w1[d + 1].getAvgWins()){
				swap = w1[d];
				w1[d] = w1[d + 1];
				w1[d + 1] = swap;
			}
			if (w2[d].getAvgWins() < w2[d + 1].getAvgWins()){
				swap = w2[d];
				w2[d] = w2[d + 1];
				w2[d + 1] = swap;
			}
		}
	}

	/*
	We can isolate the top four teams for a conference by looking the 3 division winners
	and the team with the best record from the group of second place finishers. And we 
	can sort those four teams by record. And we do the same for the bottom eleven teams.
	*/

	Team* top4EC = new  Team[4]; // top four teams from eastern conference
	Team* bot11EC = new Team[11]; // bottom eleven teams from EC
	Team* top4WC = new Team[4]; // top four teams from western conference
	Team* bot11WC = new Team[11]; // bottom eleven teams from WC

	// manually insert top four teams and top 2 of the 
	// bottom 11
	top4EC[0] = e1[0]; 	top4EC[1] = e1[1];
	top4EC[2] = e1[2]; 	top4EC[3] = e2[0];

	bot11EC[0] = e2[1]; bot11EC[1] = e2[2];

	top4WC[0] = w1[0]; 	top4WC[1] = w1[1];
	top4WC[2] = w1[2]; 	top4WC[3] = w2[0];

	bot11WC[0] = w2[1]; bot11WC[1] = w2[2];

	for (int j = 0; j < 3; j++){
		bot11EC[j + 2] = e3[j]; // teams 7-9 in conference
		bot11EC[j + 5] = e4[j]; // teams 10-12
		bot11EC[j + 8] = e5[j]; // teams 13-15

		bot11WC[j + 2] = w3[j]; // teams 7-9 in conference
		bot11WC[j + 5] = w4[j]; // teams 10-12
		bot11WC[j + 8] = w5[j]; // teams 13-15
	}

	// once last bubble sort for top 4
	for (int c = 0; c < 4 - 1; c++){ // 3 teams in each list
		for (int d = 0; d < 4 - c - 1; d++){
			if (top4EC[d].getAvgWins() < top4EC[d + 1].getAvgWins()){
				swap = top4EC[d];
				top4EC[d] = top4EC[d + 1];
				top4EC[d + 1] = swap;
			}

			if (top4WC[d].getAvgWins() < top4WC[d + 1].getAvgWins()){
				swap = top4WC[d];
				top4WC[d] = top4WC[d + 1];
				top4WC[d + 1] = swap;
			}
		}
	}

	// once last bubble sort for bottom 11 teams in each conference
	for (int c = 0; c < 11 - 1; c++){ // 3 teams in each list
		for (int d = 0; d < 11 - c - 1; d++){
			if (bot11EC[d].getAvgWins() < bot11EC[d + 1].getAvgWins()){
				swap = bot11EC[d];
				bot11EC[d] = bot11EC[d + 1];
				bot11EC[d + 1] = swap; 
			}
			if (bot11WC[d].getAvgWins() < bot11WC[d + 1].getAvgWins()){
				swap = bot11WC[d];
				bot11WC[d] = bot11WC[d + 1];
				bot11WC[d + 1] = swap;
			}
		}
	}

	// print out best teams

	for (int k = 0; k < 15; k++){
		if (k < 4){
			cout << "Eastern Conference Seed number " << k + 1;
			cout << " : " << top4EC[k].getName();
			cout << "    Wins: " << top4EC[k].getAvgWins() << endl;
		}
		else{
			cout << "Eastern Conference Seed number " << k + 1;
			cout << " : " << bot11EC[k - 4].getName();
			cout << "    Wins: " << bot11EC[k-4].getAvgWins() << endl;
		}
	}

	cout << endl; // white space
	for (int k = 0; k < 15; k++){
		if (k < 4){
			cout << "Western Conference Seed number " << k + 1;
			cout << " : " << top4WC[k].getName();
			cout << "    Wins: " << top4WC[k].getAvgWins() << endl;
		}
		else{
			cout << "Western Conference Seed number " << k + 1;
			cout << " : " << bot11WC[k - 4].getName();
			cout << "    Wins: " << bot11WC[k-4].getAvgWins() << endl;
		}
	}

	// delete dynamically allocated arrays and set pointers equal to NULL
	delete[] e1; e1 = NULL;

	delete[] e2; e2 = NULL;
	delete[] e3; e3 = NULL;
	delete[] e4; e4 = NULL;
	delete[] e5; e5 = NULL;
	delete[] w1; w1 = NULL;
	delete[] w2; w2 = NULL;
	delete[] w3; w3 = NULL;
	delete[] w4; w4 = NULL;
	delete[] w5; w5 = NULL;
	delete[] divisions; divisions = NULL;
	delete[] top4EC; top4EC = NULL;
	delete[] top4WC; top4WC = NULL;
	delete[] bot11EC; bot11EC = NULL;
	delete[] bot11WC; bot11WC = NULL;

	// if we want to return 2D arrays then do the following
	/*
	Team** standings; // by 2x15 array
	standings = new Team*[2];

	// Store top 4 first for each conference, then the bottom 11 teams...

	return standings;
	*/
}