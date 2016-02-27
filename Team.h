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
	Player roster[10];
	Player starters[5];
	Player pig[5]; //players in game
	bool wstreak;
	bool lstreak;
	int index; // id in matrix
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
	void setroster(Player[10]);//first 5 players should be the starters
	//set starter
	void setstarters(Player[5]);
	//set pig
	void setpig();

	void setName(string name);

	void enumerate(int num);

	//win streak on/off
	void changeWstreak();
	//loss stream on/off
	void changeLstreak();




};


#endif //BASKETBALLSIM_TEAM_H
