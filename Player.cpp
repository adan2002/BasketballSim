//
// Created by Jonah.Sternthal on 2/25/2016.
//

#include "Player.h"
#include <iostream>
#include <math.h>
#include<stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

//empty constructor
Player::Player() {
    age=0;
    position=0;
    pOFi=0;
    rating=0;
    rank=0;
    injury=false;
    gamesWithInjleft=0;
    sevOFinj=0;
}

//input constructor
Player::Player(string namein, int yo, int pos, int rankin, int PofI, int rtng, bool inj, int GWIL){
    name=namein;
    age=yo;
    position=pos;
    rank=rankin;
    pOFi=PofI;
    rating=rtng;
    injury=inj;
    gamesWithInjleft=GWIL;
    pOFi= (log(float (2*age)))+(minutes/150);
    pOFi=pOFi/100;
}
//destructor
Player::~Player(){}

//set age
void Player::setAge(int agein){
    age=agein;
    this->setProbInj();
}

//getage
int Player::getAge(){
    return(age);
}

//set position
void Player::setPosition(int posNum){
    position=posNum;
}

//get position
int Player::getPosition(){
    return(position);
}

//set probability of injury (based on age/minutes played)
// Based on age of player and minutes played throughout the season
// If minutes played exceeds 2400 (30 min on average over 80 games),
// then add extra term
void Player::setProbInj(){
	if (minutes > 2400) {
		pOFi = (log(float(2 * age))) + (minutes - 2400) / 120;
		pOFi = pOFi / 100;
	}

	else{
		pOFi = (log(float(2 * age))) / 100;
	}

}

//get prob of inj
float Player::getProbofInj(){
    this->setProbInj();
    return pOFi;
}

//set rating
void Player::setRating(int inrating){
    rating=inrating;
}

//get rating
int Player::getRating(){
    return rating;
}

//set minutes played
void Player::setMinPl(int mins){
    minutes=mins;
}

void Player::addMinPl(int minsadded) {
    minutes+=minsadded;
}

//get minutes
int Player::getMinPl(){
    return minutes;
}

//change injury //did you get an injury this game-if so how bad (70% miss 1 game, 20% miss 5 games, 10% miss 20 games
// think about printing out when a player gets injured/sidelined
void Player::InjuredInGame(){
    float rando;
    //srand((int)time(NULL));
    rando=rand()/(float) RAND_MAX;
    //cout<<"r"<<rando<<endl;
	if (rando < pOFi){ injury = true; }
    if (injury){
		//cout << name << " " << cout << position << endl;

        //subtract from added probability that a team wins
        sevOFinj=rand()/(float)RAND_MAX;
        if (sevOFinj<=.7){
            gamesWithInjleft=1;
        }
        if (sevOFinj>.7&&rando<.9){
            gamesWithInjleft=5;
        }
        if(sevOFinj>=.9){
            gamesWithInjleft=20;
        }
    sevOFinj=pow(sevOFinj,2)/10;}
}

bool Player::ifInjured(){
    return (injury);
}

//set games with Injury left
int Player::getGamesOut(){
    return gamesWithInjleft;
}

//decrease games with injury left, if one injury left-set injury to false
void Player::decGamesOut() {
    if (gamesWithInjleft==1){
        gamesWithInjleft=0;
        injury=false;
        //add probability back to the team winning
    }else if (gamesWithInjleft>1){
    gamesWithInjleft--;}
}

void Player::setName(string inName) {
    name=inName;
}

string Player::getName() {
    return(name);
}

void Player::setRank(int num) {
	rank = num;
}

float Player::getSevOfinj(){
    return(sevOFinj);
}