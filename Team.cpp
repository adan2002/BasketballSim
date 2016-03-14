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
	conference=0;
	division=0;
	wstreak = 0;
	lstreak = 0;
	index = -1; // id in matrix
	numplayers = 0; // number of players in roster
	avgWins = 0.0;
}
//destructor
Team::~Team() 
{
	delete[] roster; roster=NULL;

}

//gives value to index
void Team::enumerate(int num)
{
	index = num;
}

//calculates the win percent
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

//increments wins
void Team::upwin()
{
	wins = wins + 1; // increment
}

//increment losses
void Team::uploss(){
	losses = losses + 1;
}

// inport array of players and set as roster
void Team::setroster(Player* players, int num_players){
	roster = new Player[num_players]; // instantiate array
	//put players in roster--use this methodology to prevent the user from alter the roster outside the function
	for (int j = 0; j < num_players; j++)
	{
		roster[j] = players[j];
		roster[j].setProbInj();
	}
}


//set starters in game
float Team::setstarters()
{
	int player_id; //counter
	int pos = 1; //inititalize position array
	injuryOnTeam=false; //set injury on team to false
	int injuredPlayers[10]; ///set array that calls injured players by index(will at max be 10)
	int icount=0; //initilaize counter

	float penaltyForInj=0; //initialize penalty for injury

	//search for players to fill position 1-5
	while (pos<6){
		//seach through roster to find if player matches posititon
		for (player_id=0; player_id<numplayers;player_id++){
			//cout << roster[player_id].getName() << " " << roster[player_id].getPosition() << endl;
			//cout << "probofInj" << roster[player_id].getProbofInj() << endl;

			if (roster[player_id].getPosition() == pos){
				//check to see if that player is injured
				if (roster[player_id].ifInjured()){
					//cout << "player injured! \n" << endl;
					injuryOnTeam = true; //update "injury on team"
					injuredPlayers[icount] = player_id; //add player to injured players list

					icount++;
				}

				// if player matches desired pos, then add him to the list
				if (roster[player_id].getPosition() == pos && !roster[player_id].ifInjured()){
					starters[pos - 1] = player_id;
				}
				//if all players of a position are injured, it looks in the index of the injured players and places them as starters
				else if (player_id==numplayers-1) {
					//make sure that indexed player [numplayers-1] isnt injured and doesnt fill posititon
					if (roster[numplayers-1].getPosition()==pos && !roster[numplayers-1].ifInjured()){
						starters[pos-1]=numplayers-1;
						break;
					}
					int icount2 = 0;
					while (roster[injuredPlayers[icount2]].getPosition()!=pos){

						//if it puts an injured player in the starting line up, then it returns a number that decrements
						//the teams chance of winning
<<<<<<< HEAD
						penaltyForInj=penaltyForInj+roster[injuredPlayers[icount2]].getSevOfinj();
=======

						//cout<<"subtracted prob of winning "<<penaltyForInj<<endl;
						//cout<<roster[injuredPlayers[icount2]].getPosition()<<endl;

>>>>>>> 55c5ba4a448c22662605b9e3ea42e568c4e7c9ce
						icount2++;

					}
					//if it puts an injured player in the starting line up, then it returns a number that decrements
					//the teams chance of winning
					penaltyForInj=penaltyForInj+roster[injuredPlayers[icount2]].getSevOfinj();
					starters[pos-1]=injuredPlayers[icount2];
					//cout<<"playing injured player's position: "<<roster[injuredPlayers[icount2]].getPosition()<<endl;
					//cout<<"pOFi"<<roster[injuredPlayers[icount2]].getProbofInj()<<endl;
				}
				
			}
		}
		pos++;

	}
	//return the probability penalty for injury-this will be used when calculating a teams probability of winning
	return penaltyForInj;
}

//loosing streak
void Team::addLstreak() {
    if (wstreak>0){ //if winstreak > 0
        wstreak=0; //set it to zero
    }
    lstreak++; //increment lstreak
}

//winning streak, same as ad L streak
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

//function run after every game to update the team
void Team::aftergame(char WoL) {
    //adds a win or a loss depending on the outcome of the game
    switch (WoL){ //depending on whether or not a team has won or lost
        case 'w':
        case 'W':
            wins++; //increment wins, add to win streak
			addWstreak();
            break;
        case 'l':
        case 'L':
            losses++;  //increment losses add to loosing steak
			addLstreak();
            break;
        default:
            break;
    }
    int i,j;
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
	//updates the mins played of non starters by searching for starters
	// and injured players and filtering them out of the update
	//update includes running the probability that a player is injured
	for (i=0;i<numplayers-1;i++){

		holdName=roster[i].getName();
		YN=false;
		for (j=0;j<5;j++){
			//won't update if player is injured (they didnt play)
			if (holdName==playersupdated[j]){
				YN=true;
			}
		}
		//if injured then decrement a game out
		if(roster[i].ifInjured()){
			roster[i].decGamesOut();
			YN=true;
		}
		//update in player has not been selected as already updated or injured
		if (!YN){
			roster[i].addMinPl(backupMinAdded); //add mins
			roster[i].InjuredInGame(); //determine if they have been injured
			roster[i].setProbInj(); //reset probability of getting injured
		}
	}
}

int Team::getIndex() {
	return (this->index);
}

bool Team::ifInjuryOnTeam() {
	return(injuryOnTeam);
}

int Team::getStarterRating() {
	int i;
	int sum=0;
	for(i=0;i<5;i++){
		sum+=roster[starters[i]].getRating();
	}
	return(sum);
}

string Team::getName() {
	return (name);
}

void Team::setDiv(int inDiv) {
	division=inDiv; // stored as stored as integer
	  // eastern divisions are values 1,2,3
	// western divisions are values 4,5,6
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


// other non-class based functions
void updateWins(Team* teams, int num){ // to be done after every simulation
	// n tracks what number simulation we are on
	
	for (int i = 0; i < 30; i++){ // for every team in the league
		float avg;
		avg = ( num*teams[i].getAvgWins() + teams[i].getWins() )/(num + 1); // recalc average
		teams[i].setAvgWins(avg);
		teams[i].resetWins(); // reset wins counter
	}
}

/*
The following functions reads through two separate csv files which contains
the number of players for each team and the respective player information
including name, positions, age, and rating.
*/

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

				players[idx].setProbInj();

				players[idx].setMinPl(0);

				idx++;

			}

		}


		roster.close();
		teams[i].setroster(players, num_players);
		i++; // move to next element in vector

		delete[] players; players = NULL; 	// delete players array
	}

	cout << "Closing CSV files\n\n";
	inFile.close();

}