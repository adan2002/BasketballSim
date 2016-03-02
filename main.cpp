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
#include <sstream> // reading in strings
#include <fstream> // read in data

#include "sym_mat.h"
#include "Team.h"
#include "Player.h"
#include "ProbMatrix.h"


using namespace std;

int main()
{
	cout << "program starting...\n\n";


		
	

	cout << "creating NBA teams..." << endl;

	int num_teams = 30;

	vector<Team> teams(num_teams, Team()); // vector of Team class

	string filename, line;
	vector<string>DataStore; // objec to store data

	string file = "team_counts.csv"; // establish size of rosters

	ifstream  inFile(file);


	if (!inFile){
		cout << "Error opening - " << filename << endl;
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

		// intialize roster
		Player* players; // create empty array
		players = new Player[num_players];

		cout << name << " has " << num_players << " in main rotation.\n\n";

		string fname = "NBA_roster_ratings.csv"; 
		ifstream  roster(fname); // open new file
		
		if (!roster){
			cout << "\nError opening - " << fname << endl;
			cout << "\Press enter to exit." << endl;
			cin.get();

			return -1;
		}

		getline(roster, line); // skip first row (just header)

		int j = 0;
		while (getline(roster, line)){
			// read file line by line
			stringstream lineStream2(line);

			getline(lineStream2, bit, ','); // get first element (i.e. team name)
			cout << "team name: " << bit << endl;
			int idx = 0; // keep track of player in array
			
			//cout << name << " vs " << bit << endl;
			if (name == bit){ // do the team names match?

				cout << (name == bit) << endl;
				cout << name << " : " << idx;
				
				getline(lineStream, bit, ','); // get second element (i.e. player rating)
				players[idx].setRating(stoi(bit));

				getline(lineStream, bit, ','); // get third element (i.e. player rank)
				players[idx].setRank(stoi(bit));

				getline(lineStream, bit, ','); // get fourth element (i.e. player name)
				players[idx].setName(bit);

				getline(lineStream, bit, ','); // get fifth element (i.e. player position)
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
					players[idx].setPosition(4);
				}
				

				getline(lineStream, bit, ','); // get sixth element (i.e. player age)
				players[idx].setAge(stoi(bit));
			

				idx++;
				
			}

			

			//cout << j << endl;
			j++;
		}
		
		roster.close();
		i++; // move to next element in vector
	}


	

		//ATL, BKN, BOS, CHA, CHI, CLE,
		//DAL, DEN, DET, GSW, HOU, IND };
		/*
		//LAC, LAL; }
		//MEM MIA MIL MIN NO NYK OKC ORL
		//PHI PHO POR SAC SAS TOR UTH WAS

		*/



	//data.close();

	/*
	// create struct for teams

	struct team{
		int num; // factor
		int count; // keeps track of wins
		string name;
	};

	team Atl, Bos, Chi, Det, LA, NY;
	
	// set team names
	Atl.name = "Atlanta";
	Bos.name = "Boston";
	Chi.name = "Chicago";
	Det.name = "Detroit";
	LA.name = "Los Angeles";
	NY.name = "New York";

	// enumerate city names by index in table
	Atl.num = 0;
	Bos.num = 1;
	Chi.num = 2;
	Det.num = 3;
	LA.num = 4;
	NY.num = 5;

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

	/*
	// create mileage table through a dynamically allocated 2D array
	cout << "creating dynamic 2D array\n" << endl; 
 	float ** miles_tbl = new float*[num_of_cities]; //allocate array of float pointers
	
	//run a for loop to instatiante a 2D array
	for (int i = 0; i < num_of_cities; i++)
	{
		miles_tbl[i] = new float[num_of_cities]; //allocate each array of floats
		for (int j = 0; j < num_of_cities; j++)
		{
			miles_tbl[i][j] = distances[i][j]; // assign a value
		}
	}

	// initialize class
	Sym_Mat sym_matrix(num_of_cities, miles_tbl); // creat class
	
	cout << "Distance from Detroit to Chicago: ";
	cout << sym_matrix.get_distance(Det, Chi) << endl;
	cout << endl; // add white space
	
	// Test change distance member function
	cout << "Update distance between Boston and Chicago. " << endl;
	cout << "Original value: " << sym_matrix.get_distance(Bos, Chi) << endl;
	sym_matrix.change_distance(Bos, Chi, 200);
	cout << "New value: " << sym_matrix.get_distance(Bos, Chi) << endl;
	cout << "Distance from Chicago to Boston: ";
	cout << sym_matrix.get_distance(Chi, Bos) << endl;
	cout << endl;
	
	cout << "convert table indices to corresponding vector ones: \n";
	cout << "(LA, NY) = " << fromMatrixToVector(LA, NY) << endl;
	cout << "(5, 2) = " << fromMatrixToVector(5, 2) << endl;
	
	*/


	cout << "\nExiting program. Press enter to exit." << endl;

	cin.get();

	return 0;

}