//
// Created by Jonah.Sternthal on 2/25/2016.
//

#include "Team.h"
#include <iostream>
#include <stdlib.h>


Team::Team() // default constructor
{
	name = "";
	wins = 0; //function find win percent and loss percent
	losses = 0;
	addedProb = 0; //needs function that will updatate( this is the added probability that a team will win)
	//roster[10] = {}; // empty array of players
	//starters[5] = {}; // empty array of players
	//pig[5] = {}; // empty array
	wstreak = 0; // why bool? --b/c it can be-if wstreak the +.1 to prob of winning next game
	lstreak = 0; // why bool? --same as above
	index = -1; // id in matrix
	numplayers = 0;
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

void Team::upwin()
{
	wins += 1; // increment
}

void Team::uploss(){
	losses += 1;
}

//do we need a function that allows you to add/subtract players one at a time?
void Team::setroster(Player* players, int num_players) // first 5 players should be the starters
{
	roster = new Player[num_players]; // instantiate array
	for (int j = 0; j < num_players; j++)
	{
		//cout << "player name: " << players[j].getName() << endl;
		roster[j] = players[j];
	}
}

//still need to look at this-don't want to update roster!
//i thought setstarters might be a static array, and pig would pull from this and subout players that are injured-j
//but i think that if we have the starters in the first 5 of roster- your way works -j
void Team::setstarters()
{
	//CASE if both players from a position is hurt
	// account for case where both players
	// think about adding a function that returns
	// players for a given position
	int player_id;
	int pos = 1;
	injuryOnTeam=false;
	cout << "entering while loop!\n" << endl;
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
					//NEED TO PUT SOMETHING HERE!
				}
				else {
					cout << "found a match for the " << pos << " position. " << endl;
					//cout << "position of player: " << roster[player_id].getPosition() << endl;
 					starters[pos-1]=player_id;
					pos++;
				}
			}
			/*
			cout << "looking at player " << player_id << " in roster " << endl;
			cout << "position of player: " << roster[player_id].getPosition() << endl;
			cout << "looking for player at " << roster[player_id].getPosition() << " position" << endl;
			cout << "Moving to player after " << player_id << " in roster.\n\n";
			*/
		}

	}

}


//i think we probably dont need this one anymore. after each game we can add a standard amt of time to the starters
//and a standard amount of time to the non-starters that is less than that of the starters
// think more about...
void Team::setpig()
{

}

void Team::changeLstreak() {
    if (lstreak){
        lstreak=false;
    }
    else {lstreak=true;}
}

void Team::changeWstreak() {
    if (wstreak){
        wstreak=false;
    }
    else {wstreak=true;}
}

void Team::setName(string namein) {
    name=namein;
}

void Team::setNumPlayers(int num){
	numplayers = num;
}

void Team::aftergame(char WoL) {
    //adds a win or a loss depending on the outcome of the game
    switch (WoL){
        case 'w':
        case 'W':
            wins++;
            break;
        case 'l':
        case 'L':
            losses++;
            break;
        default:
            break;
    }
    //REQUIRE THAT ALL OF THE PLAYERS ARE PASSED BY REFERENCE
    int i,j;
	float rand;
	//mins added to starters playing time
    int StarterMinAdded=30;
	//mins added to backup playing time
    int backupMinAdded=90/(legthOFroster-5);
	//keep track of player names so they arent updated twice
	string playersupdated[5];
	//buffer for searching
	string holdName;
	bool YN;

	//updates the starters mins played and creates array with starter names
    for (i=0; i<5; i++){
        roster[starters[i]].addMinPl(StarterMinAdded);
		roster[starters[i]].InjuredInGame();
		playersupdated[i]=roster[starters[i]].getName();
    }
	//updates the mins played of non starters by searching for starters and injured players and filtering them out of the update
	//update includes running the probability that a player is injured
	for (i=0;i<legthOFroster-1;i++){
		holdName=roster[i].getName();
		YN=false;
		for (j=0;j<5;j++){
			//won't update if player is injured
			if (holdName==playersupdated[i]||roster[i].ifInjured()){
				YN=true;
				//if injured decrement games out
				if (roster[i].ifInjured()){roster[i].decGamesOut();}
			}
		}
		if (!YN){
			roster[i].addMinPl(backupMinAdded);
			roster[i].InjuredInGame();
		}
	}
}

int Team::getIndex() {
	return (index);
}

void Team::setLengthofRoster(int inLength) {
	legthOFroster=inLength;
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
		cout << "\nlooking at starter number " << i + 1 << endl;
		cout << roster[starters[i]].getName() << " rating is " << roster[starters[i]].getRating() << endl;
		sum+=roster[starters[i]].getRating();
	}
	return(sum);
}

string Team::getName() {
	return (name);
}