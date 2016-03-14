//
// Created by Jonah.Sternthal on 2/25/2016.
//

#ifndef BASKETBALLSIM_PLAYER_H
#define BASKETBALLSIM_PLAYER_H


#include <string>
using namespace std;

//player class
class Player {
private:
    string name;
    int age;
    int position; //1-PG,2-SG,3-SF,4-PF,5-C
	int rank; // 1 = starter, 2 = backup
    float pOFi; //probabilty of injury
    int rating; //over all rating in the league
    int minutes; //minutes played
    bool injury; //T/F if a player is injured-true
    int gamesWithInjleft; //games played with injury
    float sevOFinj; //keeps track of the random number generated when the player was injured
public:
    Player();
    Player(string namein, int yo, int pos, int rankin, int PofI, int rtng, bool inj, int GWIL);
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
    void addMinPl(int minsadded);
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
    //sets player name
    void setName(string inName);
    //returns name of player
    string getName();
	void setRank(int num); // keep track of players
		// rank in depth chart
    float getSevOfinj(); // keep track of random number
		// to determine the severit of player injur.
		// This has implications if an injured player if forced to start.
};


#endif //BASKETBALLSIM_PLAYER_H
