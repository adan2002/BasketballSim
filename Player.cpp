//
// Created by Jonah.Sternthal on 2/25/2016.
//

#include "Player.h"
#include <iostream>
#include <cmath>
#include<stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

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
void Player::isInjured(){
    float rand;
    rand=rand()/RAND_MAX;
    injury=rand>pOFi;
    if (injury){
        rand=rand()/RAND_MAX;
        if (rand<=.7){
            gamesWithInjleft=1;
        }
        if (rand>.7&&rand<.9){
            gamesWithInjleft=5;
        }
        if(rand>=.9){
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
    gamesWithInjleft--;
}