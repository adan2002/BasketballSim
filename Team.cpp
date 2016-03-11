//
// Created by Jonah.Sternthal on 2/25/2016.
//

#include "Team.h"
#include <iostream>
#include <sstream> // reading in strings as buffers
#include <fstream> // read in data
#include <math.h>
#include <stdlib.h>
#include <ctime>


Team::Team() // default constructor
{
	name = "";
	wins = 0; //function find win percent and loss percent
	losses = 0;
	addedProb = 0; //needs function that will updatate( this is the added probability that a team will win)
	conference=0;
	division=0;
	wstreak = 0;
	lstreak = 0;
	index = -1; // id in matrix
	numplayers = 0;
	avgWins = 0.0;
}

Team::~Team() 
{

}

void Team::enumerate(int num)
{
	index = num;
}

float Team::winpercent()
{
	int total_games = wins + losses; // num of games played

	return (float(wins) / float(total_games));
}	

float Team::losspercent()
{
	int total_games = wins + losses;

	return (float(losses) / float(total_games));
}

int Team::getWins()
{
	return wins;
}

int Team::getLosses()
{
	return losses;
}

void Team::upwin()
{
	wins = wins + 1; // increment
}

void Team::uploss(){
	losses = losses + 1;
}

//do we need a function that allows you to add/subtract players one at a time?
void Team::setroster(Player* players, int num_players) // first 5 players should be the starters
{
	roster = new Player[num_players]; // instantiate array
	for (int j = 0; j < num_players; j++)
	{
		roster[j] = players[j];
		roster[j].setProbInj();
	}
}

//still need to look at this-don't want to update roster!
//i thought setstarters might be a static array, and pig would pull from this and subout players that are injured-j
//but i think that if we have the starters in the first 5 of roster- your way works -j
float Team::setstarters()
{
	//CASE if both players from a position is hurt
	// account for case where both players
	// think about adding a function that returns
	// players for a given position
	int player_id;
	int pos = 1;
	injuryOnTeam=false;
	int injuredPlayers[10];
	int icount=0;
	float penaltyForInj=0;
	//cout << "entering while loop!\n" << endl;
	while (pos<6){
		//cout << "position of interest: " << pos << endl;
		for (player_id=0; player_id<numplayers;player_id++){
			//cout << player_id << endl;
			//cout << roster[player_id].getPosition() << endl;
			if (roster[player_id].getPosition()==pos){
				//cout << roster[player_id].getPosition() << endl;
				if (roster[player_id].ifInjured()){
					//cout << "player injured! \n" << endl;
					injuryOnTeam=true;
					injuredPlayers[icount]=player_id;
					icount++;
				}
				//if all players of a position are injured, it goes back to an index of the injured players and places them as starters
					if(player_id==numplayers){
						cout<<"injured in game"<<endl;
						int icount2=0;
						while (roster[injuredPlayers[icount2]].getPosition()!=pos){
							icount2++;
							cout<<"probofInj"<<roster[injuredPlayers[icount2]].getProbofInj()<<endl;
							penaltyForInj=penaltyForInj+roster[injuredPlayers[icount2]].getSevOfinj();
							cout<<"subtractedprob of winning"<<penaltyForInj;
						}
						starters[pos-1]=injuredPlayers[icount2];
					}
				else {
					starters[pos-1]=player_id;
					pos++;
				}
			}
		}

	}
	return penaltyForInj;
}


//i think we probably dont need this one anymore. after each game we can add a standard amt of time to the starters
//and a standard amount of time to the non-starters that is less than that of the starters
// think more about...
void Team::setpig()
{

}

void Team::addLstreak() {
    if (wstreak>0){
        wstreak=0;
    }
    lstreak++;
}

void Team::addWstreak(){
    if (lstreak>0){
        lstreak=0;
    }
    wstreak++;
}

void Team::setName(string namein) {
    name=namein;
}

void Team::setNumPlayers(int num){
	numplayers = num;
}

int Team::getNumPlayers(){

	return numplayers;
}


void Team::aftergame(char WoL) {
    //adds a win or a loss depending on the outcome of the game
    switch (WoL){
        case 'w':
        case 'W':
            wins++;
			addWstreak();
            break;
        case 'l':
        case 'L':
            losses++;
			addLstreak();
            break;
        default:
            break;
    }
    //REQUIRE THAT ALL OF THE PLAYERS ARE PASSED BY REFERENCE
    int i,j;
	float rand;
	//srand(time(NULL));
	//mins added to starters playing time
    int StarterMinAdded=30;
	//mins added to backup playing time
	//90 divided by number of players on bench
    int backupMinAdded=90/(numplayers-5);
	//keep track of player names so they arent updated twice
	string playersupdated[5];
	//buffer for searching
	string holdName;
	bool YN;

	//updates the starters mins played and creates array with starter names
    for (i=0; i<5; i++){
        roster[starters[i]].addMinPl(StarterMinAdded);
		roster[starters[i]].InjuredInGame();
		roster[starters[i]].setProbInj();
		playersupdated[i]=roster[starters[i]].getName();
    }
	//updates the mins played of non starters by searching for starters and injured players and filtering them out of the update
	//update includes running the probability that a player is injured
	//FIX
	for (i=0;i<numplayers-1;i++){
		holdName=roster[i].getName();
		YN=false;
		for (j=0;j<5;j++){
			//won't update if player is injured
			if (holdName==playersupdated[j]){
				YN=true;
			}
		}
		//if injured then decrement a game out
		if(roster[i].ifInjured()){
			roster[i].decGamesOut();
			YN=true;
		}
		if (!YN){
			roster[i].addMinPl(backupMinAdded);
			roster[i].InjuredInGame();
			roster[i].setProbInj();
		}
	}
}

int Team::getIndex() {
	return (this->index);
}

float Team::getAddedProb() {
	return(addedProb);
}

void Team::addProb(float inProb) {
	addedProb=+inProb;
}

bool Team::ifInjuryOnTeam() {
	return(injuryOnTeam);
}

int Team::getStarterRating() {
	int i;
	int sum=0;
	for(i=0;i<5;i++){
		//cout << "\nlooking at starter number " << i + 1 << endl;
		//cout << roster[starters[i]].getName() << " rating is " << roster[starters[i]].getRating() << endl;
		sum+=roster[starters[i]].getRating();
	}
	return(sum);
}

string Team::getName() {
	return (name);
}

void Team::setDiv(int inDiv) {
	division=inDiv;
}

void Team::setConf(int inConf) {
	conference=inConf;
}

int Team::getDiv(){
	return (division);
}

int Team::getConf(){
	return(conference);
}

int Team::getLstreak() {
	return(lstreak);
}

int Team::getWstreak() {
	return(wstreak);
}

float Team::getAvgWins(){
	return avgWins;
}

void Team::setAvgWins(float n){ 
	avgWins = n;
}

void Team::resetWins(){
	wins = 0;
	losses=0; //update losses too
}


// other functions
void updateWins(Team* teams, int num){ // to be done after every simulation
	// n tracks what number simulation we are on
	
	for (int i = 0; i < 30; i++){ // for every team in the league
		float avg;
		avg = ( num*teams[i].getAvgWins() + teams[i].getWins() )/(num + 1); // recalc average
		teams[i].setAvgWins(avg);
		teams[i].resetWins(); // reset wins counter
	}
}

void createTeams(Team* teams, string depthcounts, string rosterFile){

	ifstream  inFile(depthcounts);
	string line;

	if (!inFile){
		cout << "Error opening - " << depthcounts << endl;
		cout << "\nPress enter to exit." << endl;
		cin.get();
		exit(0);
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
		//cout << "Number of players for " << name << " : " << num_players << endl;
		teams[i].setNumPlayers(num_players);

		getline(lineStream, bit, ','); // get third element (i.e. team conference 1 = eastern, 0 = western)
		int conf = stoi(bit); // store number
		teams[i].setConf(conf);

		getline(lineStream, bit, ','); // get fourth element (i.e. team division, which is enumerated)
		// (1,2,3 are in east and 4,5,6 are in west)
		int div = stoi(bit); // store number
		//cout << "Number of players for " << name << " : " << num_players << endl;
		teams[i].setDiv(div);

		// intialize roster
		Player* players; // create empty array
		players = new Player[num_players];

		//cout << name << " has " << num_players << " in main rotation.\n\n";

		//string fname = "C:\\Users\\Jonah.Sternthal\\Documents\\Dartmouth\\W16\\ENGS65\\BBALLSIM\\BasketballSim\\NBA_roster_ratings.csv";
		//string fname = "NBA_roster_ratings.csv";

		ifstream  roster(rosterFile); // open new file

		if (!roster){
			cout << "\nError opening - " << rosterFile << endl;
			cout << "\nPress enter to exit." << endl;
			cin.get();

			exit(0);
		}
		
		getline(roster, line); // skip first row (just header)

		int idx = 0;
		while (getline(roster, line)){
			// read file line by line
			stringstream lineStream(line);

			getline(lineStream, bit, ','); // get first element (i.e. team name)
			//int idx = 0; // keep track of player in array

			if (name == bit){ // do the team names match?

				//cout << "team name: " << bit << endl;
				getline(lineStream, bit, ','); // get second element (i.e. player name)
				players[idx].setName(bit);

				getline(lineStream, bit, ','); // get third element (i.e. player age)
				players[idx].setAge(stoi(bit));

				getline(lineStream, bit, ','); // get fourth element (i.e. player pos)
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

				//cout << "player position (enumerated): " << players[idx].getPosition() << endl;

				getline(lineStream, bit, ','); // get fifth element (i.e. player rank)
				players[idx].setRank(stoi(bit));


				getline(lineStream, bit, ','); // get sixth element (i.e. player rating)
				players[idx].setRating(stoi(bit));


				idx++;

			}

		}


		roster.close();
		teams[i].setroster(players, num_players);
		i++; // move to next element in vector
		//cout << "team number: " << i << endl;

		delete[] players; players = NULL; 	// delete players array
	}

	cout << "Closing CSV files\n\n";
	inFile.close();

}