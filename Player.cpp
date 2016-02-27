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
    return(position)
}

//set probability of injury (based on age/minutes played)
void Player::setProbInj(){
    pOFi=float log(float 2*age)
}

//get prob of inj
float Player::getProbofInj(){}

//set rating
void Player::setRating(int rating){}

//get rating
int Player::getRating(){}

//set minutes played
void Player::setMinPl(int mins){}

//get minutes
int Player::getMinPl(){}

//change injury //did you get an injury this game-if so how bad (70% miss 1 game, 20% miss 5 games, 10% miss season
void Player::isInjured(){}

//set games with Injury left
void Player::setGamesOut(int numofgames){}

//decrease games with injury left
void Player::decGamesOut() { }