#include <iostream>
#include <string>
#include <stdlib.h> // srand rand 
#include <sstream> // reading in strings
#include <fstream> // read in data

#include "sym_mat.h"
#include "Team.h"
#include "Player.h"
#include "ProbMatrix.h"


using namespace std;

int main2()
{
	string file = "NBA_roster_ratings.csv";

	ifstream  data(file);

	string line;
	while (getline(data, line)) // read file line by lines
	{
		stringstream  lineStream(line);
		string        cell;
		while (getline(lineStream, cell, ','))
		{
			cout << cell << endl;
		}
	}



	cout << "\nExiting program. Press enter to exit." << endl;

	cin.get();

	return 0;

}
