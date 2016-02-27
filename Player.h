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
    Player();
    Player(int yo, int pos, int PofI, int rtng, bool inj, int GWIL);
    ~Player();
    //set age
    void setAge(int age);
    //getage
    int getAge();
    //set position
    void setPosition(int posNum);
    //get position
    int getPosition();
    //set probability of injury (based on age/minutes played)
    void setProbInj();//maybe this just goes into age?
    //get prob of inj
    float getProbofInj();
    //set rating
    void setRating(int rating);
    //get rating
    int getRating();
    //set minutes played
    void setMinPl(int mins);
    //get minutes
    int getMinPl();
    //did player get injury this game-if so how bad (70% miss 1 game, 20% miss 5 games, 10% miss season
    void InjuredInGame();
    //returns if player is injured
    bool ifInjured();
    //set games with Injury left
    int getGamesOut();
    //decrease games with injury left
    void decGamesOut();

};


#endif //BASKETBALLSIM_PLAYER_H
