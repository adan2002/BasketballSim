//
// Created by Jonah.Sternthal on 2/25/2016.
//

#include "Team.h"


Team::Team() // default constructor
{
	name = "";
	wins = 0; //function find win percent and loss percent
	losses = 0;
	addedProb = 0; //needs function that will updatate( this is the added probability that a team will win)
	roster[10] = {}; // empty array of players
	starters[5] = {}; // empty array of players
	pig[5] = {}; // empty array
	wstreak = 0; // why bool?
	lstreak = 0; // why bool?
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


void Team::setroster(Player* players) // first 5 players should be the starters
{
	roster = new Player[10]; // instantiate array
	for (int j = 0; j < 10; j++)
	{
		roster[j] = players[j];
	}
}

void Team::setstarters(Player[5])
{
	// account for case where both players
	// think about adding a function that returns
	// players for a given position
	for (int i = 0; i < 5; i++)
	{
		int player_id = 0;
		Player player = roster[player_id];

		while (player.getPosition() != (i + 1) & player.ifInjured() != 1){ // position doesn't match
								// and player not injured
			player_id += 1; // look at next player in roster
			player = roster[player_id];
		}
		
	}
}

// think more about...
void Team::setpig()
{

}