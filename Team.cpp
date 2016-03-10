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
	conference=0;
	division=0;
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
	int injuredPlayers[10];
	int icount=0;
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
						int icount2=0;
						while (roster[injuredPlayers[icount2]].getPosition()!=pos){
							icount2++;
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
	//mins added to starters playing time
    int StarterMinAdded=30;
	//mins added to backup playing time
	//90 divided by average roster length
    int backupMinAdded=90/(5);
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
	return (this->index);
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

int Team::getWins(){
	//cout<<wins<<endl;
	return(wins);
}

int Team::getLosses() {
	//cout<<losses<<endl;
	return(losses);
}