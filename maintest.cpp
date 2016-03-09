//
// Created by Jonah.Sternthal on 2/27/2016.
//

#include <iostream>
#include "Player.h"
using namespace std;


int main(){
    Player a, b;

    a.setAge(25);
    cout<<a.getAge()<<endl;
    a.setMinPl(1500);
    a.setProbInj();
    a.InjuredInGame();
    cout<<a.ifInjured()<<endl;
    cout<<a.getGamesOut()<<endl<<endl;

    b.setAge(25);
    cout<<a.getAge()<<endl;
    b.setMinPl(1500);
    b.setProbInj();
    b.InjuredInGame();
    cout<<b.ifInjured()<<endl;
    cout<<b.getGamesOut()<<endl;

    return 0;
}