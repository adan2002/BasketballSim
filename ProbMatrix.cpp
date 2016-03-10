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

/*void ProbMatrix::addTeams(Team* list_teams, int num_teams) // parameterized constructor

{  // think about linking ProbMatrix with Team class
	teams = new Team[num_teams]; //  create an array of Teams
	for (int i = 0; i < num_teams; i++){
		teams[i] = list_teams[i]; // copy over
	}
}*/

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

void ProbMatrix::runGame(Team &home, Team &away){
	float rando;
	//get probability of winning for the home team
	float hometeamwins=getProb(home, away);
	//cout << "Probability of home team, " << home.getName() << ", winning: " << hometeamwins << endl;
	//cout << "Probability of away team, " << away.getName() << ", winning: " << (1.0-hometeamwins) << endl;
	//cout << "Setting starters for home team\n";
	home.setstarters();
	//cout << "Setting starters for away team\n";
	away.setstarters();

	//cout << "Starters set for each team \n" << endl;
	if (home.ifInjuryOnTeam()||away.ifInjuryOnTeam()){
		//cout << "Injury!";
		int HTR = home.getStarterRating(); //home team ratings
		//cout << "Starter rating for home team: " << HTR << endl;
		//cout << "\n\n";
		int ATR = away.getStarterRating(); //away team ratings
		//cout << "Starter rating for home team: " << ATR << endl;
		///////changed to this...is this the best way?
		hometeamwins=hometeamwins-(ATR-HTR)/((HTR+ATR)/4);
		//add rankings of both teams.
	}
	//see if there are any probability additons for the home team and add it to a dummy variable
	//see if there are any probability additions for the away team and subtract that from the dummy variable
	hometeamwins=hometeamwins+home.getAddedProb()-away.getAddedProb();

	//account for win streak and losing streak here
	if (home.getWstreak()>0){
		hometeamwins=+0.01;
	}
	if (away.getWstreak()>0){
		hometeamwins=-0.01;
	}
	if (away.getLstreak()>0){
		hometeamwins=+0.01;
	}
	if (home.getLstreak()>0){
		hometeamwins=-0.01;
	}
	//generate a random number and determine if it is larger or smaller than the probability that the home team wins
	//cout << "\ngenerating random number...\n\n";
	rando = float(rand()) / RAND_MAX;
	//cout << "random number generated: " << rando << endl;
	//if larger, home team loses, if smaller home team wins
	//run aftergame
	if (rando<hometeamwins){
		home.aftergame('W');
		away.aftergame('L');
		//cout << "Home team wins!!!\n";
	}else{
		home.aftergame('L');
		away.aftergame('W');
		//cout << "Away team wins!!!\n";
	}
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
			//cout << "team name: " << bit << endl;
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
		//cout << "\nGame number: " << i+1 << "\n";
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

// other functions

/*
NBA has six teams and each division hosts 5 teams.
Therefore this will return a 6x5 matrix. Each divison will 
matcht the row index - 1, assuming the count begins at 0. 
*/

//Team** genStandings(Team* teams){ // rank teams by conference and records
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
			//cout << "Team name: " << teams[idx].getName() << endl;
			divisions[i][j] = teams[idx];
			idx++; // move onto to nex team
		}
	}

	// now sort teams in each divsion by wins

	for (int i = 0; i < 6; i++){ // for each division
		// use bubble sort algorithm to arrange from best to worst records
		for (int c = 0; c < 5 - 1; c++){ // 5 teams in each division
			for (int d = 0; d < 5 - c - 1; d++){
				if (divisions[i][d].getAvgWins() < divisions[i][d + 1].getAvgWins()){
					swap = divisions[i][d];
					divisions[i][d] = divisions[i][d + 1];
					divisions[i][d + 1] = swap;
				}
			}
		}

	}

	// separate teams by conference
	Team eastConf[15]; // list for eastern conference teams
	Team westConf[15]; // list for western conference teams

	idx = 0; //reset counter
	for (int i = 0; i < 3; i++){
		//cout << i << endl;
		for (int j = 0; j < 5; j++){
			eastConf[idx] = divisions[i][j];
			westConf[idx] = divisions[i + 3][j];
			idx++;
		}

	}

	// Another method of sorting teams by conference
	// or sort by columns and then concatenate rankings
	Team* e1 = new Team[3]; // 1st place finishers of east divisions
	Team* e2 = new Team[3]; // 2nd place finishers of east divisions...
	Team* e3 = new Team[3];
	Team* e4 = new Team[3]; 
	Team* e5 = new Team[3];

	Team* w1 = new Team[3]; // 1st place finishers of western divisions..
	Team* w2 = new Team[3];
	Team* w3 = new Team[3];
	Team* w4 = new Team[3];
	Team* w5 = new Team[3];

	for (int i = 0; i < 3; i++){
		e1[i] = divisions[i][0]; // all the first
		e2[i] = divisions[i][1];
		e3[i] = divisions[i][2];
		e4[i] = divisions[i][3];
		e5[i] = divisions[i][4];

		w1[i] = divisions[i + 3][0];
		w2[i] = divisions[i + 3][1];
		w3[i] = divisions[i + 3][2];
		w4[i] = divisions[i + 3][1];
		w5[i] = divisions[i + 3][2];
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

	Team* top4EC = new  Team[4]; // top four teams from eastern conference
	Team* bot11EC = new Team[11]; // bottom eleven teams from EC
	Team* top4WC = new Team[4]; // top four teams from western conference
	Team* bot11WC = new Team[11]; // bottom eleven teams from WC

	// manually insert
	top4EC[0] = e1[0];
	top4EC[1] = e1[1];
	top4EC[2] = e1[2];
	top4EC[3] = e2[0];

	bot11EC[0] = e2[1];
	bot11EC[1] = e2[2];

	top4WC[0] = w1[0];
	top4WC[1] = w1[1];
	top4WC[2] = w1[2];
	top4WC[3] = w2[0];

	bot11WC[0] = w2[1];
	bot11WC[1] = w2[2];

	for (int j = 0; j < 3; j++){
		bot11EC[j + 2] = e3[j]; // teams 7-9 in conference
		bot11EC[j + 5] = e4[j]; // teams 10-12
		bot11EC[j + 8] = e5[j]; // teams 13-15

		bot11WC[j + 2] = w3[j]; // teams 7-9 in conference
		bot11WC[j + 5] = w4[j]; // teams 10-12
		bot11WC[j + 8] = w5[j]; // teams 13-15
	}

	cout << "\nSorting top four teams from eastern conference\n";


	// once last bubble sort for top 4
	for (int c = 0; c < 4 - 1; c++){ // 3 teams in each list
		for (int d = 0; d < 4 - c - 1; d++){
			if (top4EC[d].getAvgWins() < top4EC[d + 1].getAvgWins()){
				//cout << "swapping eastern teams\n"; // debug statement
				swap = top4EC[d];
				top4EC[d] = top4EC[d + 1];
				top4EC[d + 1] = swap;
			}

			if (top4WC[d].getAvgWins() < top4WC[d + 1].getAvgWins()){
				//cout << "swapping western teams\n"; // debug statement
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
			cout << "    Wins: " << bot11EC[k].getAvgWins() << endl;
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
			cout << "    Wins: " << bot11WC[k].getAvgWins() << endl;
		}
	}

	/*
	Team** standings; // by 2x15 array
	standings = new Team*[2];
	standings[0] = eastConf;
	standings[1] = westConf;

	return standings;
	*/
}