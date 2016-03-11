/*
Authors: Adan Rivas and Jonah Sternthal
ENGS 65 Engineering Design
16W

Final Project: Monte Carlo Simulation of Basketball teams

General probability matrix where the row index denotes the home team:

	 Atl     Bos    Chi   Det    LA    NY
Atl .304   .110   .708   .756  .219   .854
Bos .110   .510   .994   .175  .301   .222
Chi .708   .994   .430   .279  .244   .809
Det .756   .175   .279   .320  .228   .649
LA  .219   .301   .204   .228  .654   .279
NY  .854   .222   .809   .649  .270   .561


The values give the likilhood of the home team winning.
To find the probability that the visiting teams wins, we simply find the
complement of the entery (home, away)

Our simulation is very similar to a markove chain, except we do take into
account a team's recent performance in terms of winning and losing streaks.
We a run simulation for the 2015/2016 season 1000 times to get the average wins 
per season of every team. We then identify the top 8 teams from each conference
(in accordance with NBA ranking procedures), and thus predict which teams make
the playoffs.

*/

#include <iostream>
#include <string>
#include <stdlib.h> // srand rand 
#include <sstream> // reading in strings as buffers
#include <fstream> // read in data
#include <ctime> 

// Loading in class files
#include "Team.h"
#include "Player.h"
#include "ProbMatrix.h"


using namespace std;

int main()
{
	/*float k,j;
	cout<<time(NULL)<<endl;
	srand((time(NULL)));
	k=rand()/(float)RAND_MAX;
	j=rand()/(float)RAND_MAX;
	cout<<k<<endl;
	cout<<j<<endl;
	cout<<RAND_MAX<<endl;*/

	srand(time(NULL));

	cout << "Program starting...\n\n";

	int numTeams = 30; // number of teams in NBA

	Team* teams; // create empty array of Team class
	teams = new Team[numTeams]; // allocate array size of 30

	//string file = "C:\\Users\\Jonah.Sternthal\\Documents\\Dartmouth\\W16\\ENGS65\\BBALLSIM\\BasketballSim\\team_counts.csv"; // establish size of rosters
	string file = "team_counts.csv"; // player count for each team

	//string fname = "C:\\Users\\Jonah.Sternthal\\Documents\\Dartmouth\\W16\\ENGS65\\BBALLSIM\\BasketballSim\\NBA_roster_ratings.csv";
	string fname = "NBA_roster_ratings.csv"; // player information

	cout << "\nInstantiating NBA basketball teams and rosters...\n\n";
	createTeams(teams, file, fname);

	cout << "Filling in probability matrix\n" << endl;
	ProbMatrix pmat;
	pmat.setSize(numTeams); // dynamically allocate matrix
	pmat.addTeams(teams, numTeams); // create list of teams

	//string fn = "C:\\Users\\Jonah.Sternthal\\Documents\\Dartmouth\\W16\\ENGS65\\BBALLSIM\\BasketballSim\\probs.txt"; // probabilities file
	string fn = "probs.txt"; // probabilities file
	pmat.setProb(fn, numTeams); // intialize probabilit matrix values

	//pmat.runSeason("C:\\Users\\Jonah.Sternthal\\Documents\\Dartmouth\\W16\\ENGS65\\BBALLSIM\\BasketballSim\\2016schedule.csv");
	cout << "Simulating multiple full season\n";
	pmat.runSeason("2016schedule.csv");
	
	// multiple season simulation
	
	for (int s = 0; s < 25; s++){
		cout << "Simulating season number " << s+1 << endl;
		//pmat.runSeason("C:\\Users\\Jonah.Sternthal\\Documents\\Dartmouth\\W16\\ENGS65\\BBALLSIM\\BasketballSim\\2016schedule.csv");
		pmat.runSeason("2016schedule.csv");
		updateWins(teams, s); // update average wins for all teams and reset win counter for next season

	}

	cout << "Number of player on roster for " << teams[7].getName() << ": " << teams[7].getNumPlayers() << endl;
	
	cout << "\nSorting team array by conference\n";
	genStandings(teams); // functions prints out standings
			// for each conference Top eight from each conference 
			// are predicted to make the playoffs
	
	// delete all arrays and reset pointers
	delete[] teams; teams = NULL;

	cout << "\nExiting program. Press enter to exit.";

	cin.get();

	return 0;

}




