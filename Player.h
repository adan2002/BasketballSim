//
// Created by Jonah.Sternthal on 2/25/2016.
//

#ifndef BASKETBALLSIM_PLAYER_H
#define BASKETBALLSIM_PLAYER_H


class Player {
private:
    int age;
    int position; //1-PG,2-SG,3-SF,4-PF,5-C
    float pOFi; //probabilty of injury
    int rating;
    int minutes; //minutes played
    bool injury;
    int gamesWithInjleft; //games played with injury
public:
    //set age
    //getage
    //set position
    //get position
    //set probability of injury (based on age/minutes played)
    //get prob of inj
    //set rating
    //get rating
    //set minutes
    //add minutes
    //get minutes
    //change injury
    //set games with Injury left
    //decrease games with injury left
};


#endif //BASKETBALLSIM_PLAYER_H
