/*
Authors: Adan Rivas and Jonah Sternthal
ENGS 65 Engineering Design
16W

Final Project: Markov Chain Simulation of Basketball teams

General probability matrix where the row index denotes the home team:

	Atl   Bos   Chi   Det   LA    NY
Atl  0    1108  708   756  2191   854
Bos 1108    0   994  1753  3017   222
Chi 708    994    0   279  2048   809
Det 756   1753  279     0  2288   649
LA 2191   3017 2048  2288     0  2794
NY  854    222  809   649  2794     0


To find the probability that the visiting teams wins, we simply find the
complement of the entery (home, away)

*/

#include <iostream>
#include <string>
#include <stdlib.h> // srand rand 
#include <vector>
#include <sstream> // reading in strings as buffers
#include <fstream> // read in data

#include "Team.h"
#include "Player.h"
#include "ProbMatrix.h"

void runGame(Team home, Team away){
	//get probability of winning for the home team
	//see if there are any probability additons for the home team and add it to a dummy variable
	//see if there are any probability additions for the away team and subtract that from the dummy variable
	//generate a random number and determine if it is larger or smaller than the probability that the home team wins
	//if larger, home team loses, if smaller home team wins
	//run team.aftergame for both teams.
}

using namespace std;

int main()
{
	cout << "program starting...\n\n";


		
	

	cout << "creating NBA teams..." << endl;

	int numTeams = 30;

	// replace vector with array of Teams
	Team* teams; // create empty array of Teams
	teams = new Team[numTeams];

	string line;

	string file = "team_counts.csv"; // establish size of rosters

	ifstream  inFile(file);


	if (!inFile){
		cout << "Error opening - " << file << endl;
		cout << "\nPress enter to exit." << endl;
		cin.get();
		return -1;
	}

	getline(inFile, line); // skip first row

	int i = 0;
	while (getline(inFile, line))
	{
		teams[i].enumerate(i);
				
		stringstream lineStream(line);
		string bit;
		getline(lineStream, bit, ','); // get first element (i.e. team name)
		string name = bit; // locally store team name
			
		teams[i].setName(name);
		getline(lineStream, bit, ','); // get second element (i.e. number of players on team)
		int num_players = stoi(bit); // store number
		cout << "Number of players for " << name << " : " << num_players << endl;
		teams[i].setNumPlayers(num_players);

		// intialize roster
		Player* players; // create empty array
		players = new Player[num_players];

		//cout << name << " has " << num_players << " in main rotation.\n\n";

		string fname = "NBA_roster_ratings.csv"; 
		ifstream  roster(fname); // open new file
		
		if (!roster){
			cout << "\nError opening - " << fname << endl;
			cout << "\nPress enter to exit." << endl;
			cin.get();

			return -1;
		}

		getline(roster, line); // skip first row (just header)

		int idx = 0;
		while (getline(roster, line)){
			// read file line by line
			stringstream lineStream(line);

			getline(lineStream, bit, ','); // get first element (i.e. team name)
			//int idx = 0; // keep track of player in array
			
			if (name == bit){ // do the team names match?

				cout << "team name: " << bit << endl;
				getline(lineStream, bit, ','); // get second element (i.e. player name)
				cout << "name: " << bit << endl;
				players[idx].setName(bit);
				
				getline(lineStream, bit, ','); // get third element (i.e. player age)
				players[idx].setAge(stoi(bit));

				getline(lineStream, bit, ','); // get fourth element (i.e. player pos)
				cout << "player position: " << bit << endl;
				// enumerate player position
				if (bit == "PG"){
					players[idx].setPosition(1);
				}

				else if (bit == "SG"){
					players[idx].setPosition(2);
				}

				else if (bit == "SF"){
					players[idx].setPosition(3);
				}

				else if (bit == "PF"){
					players[idx].setPosition(4);
				}

				else{ // o.w. player is center
					players[idx].setPosition(5);
				}

				cout << "player position (enumerated): " << players[idx].getPosition() << endl;


				getline(lineStream, bit, ','); // get fifth element (i.e. player rank)
				players[idx].setRank(stoi(bit));
				

				getline(lineStream, bit, ','); // get sixth element (i.e. player rating)
				players[idx].setAge(stoi(bit));
			

				idx++;
				
			}

		}
		

		roster.close();
		teams[i].setroster(players, num_players);
		i++; // move to next element in vector
		cout << "team number: " << i << endl;
	}

	cout << "Closing CSV files\n\n";
	inFile.close();
	

	cout << "Filling in probability matrix: " << endl;
	ProbMatrix pmat;
	pmat.setSize(numTeams);
	pmat.addTeams(teams, numTeams);

	string fn = "probs.txt"; // probabilities file
	
	pmat.setProb(fn, numTeams);
	cout << pmat.getProb(teams[1], teams[4]) << endl;
	pmat.runGame(teams[1], teams[4]);




	/*
		
	// initialize counts to zero

	Atl.count = 0;
	Bos.count = 0;
	Chi.count = 0;
	Det.count = 0;
	LA.count = 0;
	NY.count = 0;

	team teams[6] = { Atl, Bos, Chi, Det, LA, NY };

	int num_of_cities = 6; // size of table

	// probability matrix
	float prob_matrix[6][6] = {
		{ 0.2, 0.25, 0.56, 0.45, 0.33, 0.34 },
		{ 0.45, 0.60, 0.85, 0.56, 0.23, 0.65 },
		{ 0.43, 0.56, 0.56, 0.56, 0.34, 0.56 },
		{ 0.70, 0.45, 0.6, 0.15, 0.50, 0.65 },
		{ 0.43,0.56, .87, 0.54, 0.40, .50 },
		{ 0.34, 0.45, 0.45, 0.56, 0.67, 0.47 }
	};

	int team1 = rand() % 6;  // rand_num in the range 0 to 5
	float n = 50; // number of simulations

	// random number generator
	for (int i = 0; i < n; i++){
		
		//int home = rand() % 6;  // rand_num in the range 0 to 5
		int team2 = rand() % 6;
		while (team2 == team1){
			team2 = rand() % 6;
		}

		// who is playing home? 

		float p = ((float)rand() / (RAND_MAX)); // random number between 0 and 1

		if (p < 0.5){ // if less than 0.5 than team 1 is at home

			cout << "home team: ";
			cout << teams[team1].name << endl;

			cout << "away team: ";
			cout << teams[team2].name << endl;

			cout << "probability of home team winning: " << prob_matrix[team1][team2] << endl;

			float r = ((float)rand() / (RAND_MAX)); // random number between 0 and 1

			if (r > prob_matrix[team1][team2]){
				cout << "Away team won!";
				teams[team2].count += 1;
				team1 = team2; // set winner as new top team
			}
			else {
				cout << "Home team won!";
				teams[team1].count += 1;
			}

		}
		else { // otherwise team2 is at home
			cout << "home team: ";
			cout << teams[team2].name << endl;

			cout << "away team: ";
			cout << teams[team1].name << endl;

			cout << "probability of home team winning: " << prob_matrix[team2][team1] << endl;

			float r = ((float)rand() / (RAND_MAX)); // random number between 0 and 1

			if (r > prob_matrix[team2][team1]){
				cout << "\nAway team won!";
				teams[team1].count += 1;
			}
			else {
				cout << "\nHome team won!";
				teams[team2].count += 1;
				team1 = team2;
			}
		}

		
		cout << endl;
		cout << endl;

	}

	// sick about using merge sort technique to order teams
	for (int i = 0; i < 6; i++){

		cout << "frequency of " << teams[i].name << " being best team: " << (teams[i].count / n) << endl;

	}

	*/
	cout << "\nExiting program. Press enter to exit." << endl;

	cin.get();

	return 0;

}




