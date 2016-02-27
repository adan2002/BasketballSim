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
    injury=false;
    gamesWithInjleft=0;
}

//input constructor
Player::Player(int yo, int pos, int PofI, int rtng, bool inj, int GWIL){
    age=yo;
    position=pos;
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
}

//getage
int Player::getAge(){
    return(age);
}

//set position
void Player::setPosition(int posNum){
    posNum=position;
}

//get position
int Player::getPosition(){
    return(position);
}

//set probability of injury (based on age/minutes played)
void Player::setProbInj(){
    pOFi= (log(float (2*age)))+(minutes/150);
    pOFi=pOFi/100;
}

//get prob of inj
float Player::getProbofInj(){
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

//get minutes
int Player::getMinPl(){
    return minutes;
}

//change injury //did you get an injury this game-if so how bad (70% miss 1 game, 20% miss 5 games, 10% miss 20 games
void Player::InjuredInGame(){
    float rando;
    rando=(float)rand()/RAND_MAX;
    rando=(float)rand()/RAND_MAX;
    cout<<"r"<<rando<<endl;
    injury=rando<pOFi;
    if (injury){
        rando=(float)rand()/RAND_MAX;
        rando=(float)rand()/RAND_MAX;
        cout<<"r"<<rand<<endl; //DEBUG
        if (rando<=.7){
            gamesWithInjleft=1;
        }
        if (rando>.7&&rando<.9){
            gamesWithInjleft=5;
        }
        if(rando>=.9){
            gamesWithInjleft=20;
        }
        }
}

bool Player::ifInjured(){
    return (injury);
}

//set games with Injury left
int Player::getGamesOut(){
    return gamesWithInjleft;
}

//decrease games with injury left
void Player::decGamesOut() {
    if(gamesWithInjleft>0){
    gamesWithInjleft--;}
}