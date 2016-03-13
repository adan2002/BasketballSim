//
// Created by Jonah.Sternthal on 2/25/2016.
//

#ifndef BASKETBALLSIM_TEAM_H
#define BASKETBALLSIM_TEAM_H


#include "Player.h"
#include <string>

using namespace std;

class Team{
private:
	string name; //Stores the name of the team
	int conference; //the conference of the team
	int division; //team's division
	int wins; //teams wins over the season
	int losses;  //team losses over the season
	float addedProb; //needs function that will updatate( this is the added probability that a team will win)
	Player* roster; //list of players in the roster
	int starters[5]; //an int array that holds the index of the starting players
	Player* pig; //players in game
	bool injuryOnTeam; //indicates an injury on the team T-injury on team
	int wstreak;//keeps track of the wins in a row
	int lstreak; //keeps track of losses in a row
	int index; // id in matrix
	int numplayers; //records the number of players on the team
	float avgWins; // keeps track of averages wins after
					// multiple simulations
public:
	Team();
	~Team();
	//win percent
	float winpercent();
	//loss percent
	float losspercent();
	//update win
	void upwin();
	//update loss
	void uploss();
	//set roster
	void setroster(Player* player, int num);//first 5 players should be the starters
	//set starter
	float setstarters();
	//set pig
	void setpig();
	//setName of team
	void setName(string namein);
	void setDiv(int inDiv);

	void setConf(int inConf);

	int getDiv();

	int getConf();

	void enumerate(int num);

	void setNumPlayers(int num);
	int getNumPlayers();

	//adding to winstrek
	void addWstreak();
	//adding to lose streak
	void addLstreak();

	bool ifInjuryOnTeam();

	//things that should happen to team after the game...
	//idk if this is the best way to implement
	void aftergame(char WoL);
	float getAddedProb();
	int getIndex();
	void addProb(float inProb);
	int getStarterRating();
	int getLstreak();
	int getWstreak();
	int getWins();
	int getLosses();
	string getName();
	void setAvgWins(float num);
	float getAvgWins();
	void resetWins();

};

// other functions
void updateWins(Team* teams, int num);
void createTeams(Team* teams, string fname1, string fname2); // reads through roster csv file
		// and generates team rosters

#endif //BASKETBALLSIM_TEAM_H
