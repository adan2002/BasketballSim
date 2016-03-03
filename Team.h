//
// Created by Jonah.Sternthal on 2/25/2016.
//

#ifndef BASKETBALLSIM_TEAM_H
#define BASKETBALLSIM_TEAM_H


#include "Player.h"
#include <string>

using namespace std;

class Team {
private:
	string name;
	int wins; //function find win percent and loss percent
	int losses;
	float addedProb; //needs function that will updatate( this is the added probability that a team will win)
	Player* roster;
	int starters[5];
	Player* pig; //players in game
	bool injuryOnTeam;
	bool wstreak; 
	bool lstreak;
	int legthOFroster;
	int index; // id in matrix
	int numplayers;
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
	void setstarters();
	//set pig
	void setpig();
	//setName of team
	void setName(string namein);

	void enumerate(int num);

	void setNumPlayers(int num);

	//win streak on/off
	void changeWstreak();
	//loss stream on/off
	void changeLstreak();

	bool ifInjuryOnTeam();

	//things that should happen to team after the game...
	//idk if this is the best way to implement
	void aftergame(char WoL);
	float getAddedProb();
	int getIndex();
	void setLengthofRoster(int inLength);
	void addProb(float inProb);

	int getStarterRating();

};


#endif //BASKETBALLSIM_TEAM_H
