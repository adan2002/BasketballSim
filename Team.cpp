//
// Created by Jonah.Sternthal on 2/25/2016.
//

#include "Team.h"
#include <stdlib.h>


Team::Team() // default constructor
{
	name = "";
	wins = 0; //function find win percent and loss percent
	losses = 0;
	addedProb = 0; //needs function that will updatate( this is the added probability that a team will win)
	roster[10] = {}; // empty array of players
	starters[5] = {}; // empty array of players
	pig[5] = {}; // empty array
	wstreak = 0; // why bool? --b/c it can be-if wstreak the +.1 to prob of winning next game
	lstreak = 0; // why bool? --same as above
	index = -1; // id in matrix
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
void Team::setroster(Player* players) // first 5 players should be the starters
{
	roster = new Player[10]; // instantiate array
	for (int j = 0; j < 10; j++)
	{
		roster[j] = players[j];
	}
}

//still need to look at this-don't want to update roster!
//i thought setstarters might be a static array, and pig would pull from this and subout players that are injured-j
//but i think that if we have the starters in the first 5 of roster- your way works -j
void Team::setstarters(Player[5])
{
	// account for case where both players
	// think about adding a function that returns
	// players for a given position
	for (int i = 0; i < 5; i++)
	{
		int player_id = 0;
		Player player = roster[player_id];

		while (player.getPosition() != (i + 1) && player.ifInjured() != 1){ // position doesn't match
								// and player not injured
			player_id += 1; // look at next player in roster
			player = roster[player_id];
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
    int StarterMinAdded=25;
	//mins added to backup playing time
    int backupMinAdded=23;
	//keep track of player names so they arent updated twice
	string playersupdated[5];
	//buffer for searching
	string holdName;
	bool YN;

	//updates the starters mins played and creates array with starter names
    for (i=0; i<5; i++){
        starters[i].addMinPl(StarterMinAdded);
		starters[i].InjuredInGame();
		playersupdated[i]=starters[i].getName();
    }
	//updates the mins played of non starters by searching for starters and filtering them out of the update
	for (i=0;i<10;i++){
		holdName=roster[i].getName();
		YN=false;
		for (j=0;j<5;j++){
			//won't update if player is injured
			if (holdName==playersupdated[i]||!roster[i].ifInjured()){
				YN=true;
			}
		}
		if (!YN){
			roster[i].addMinPl(backupMinAdded);
		}
	}


}

