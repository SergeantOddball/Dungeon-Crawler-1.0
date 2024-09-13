#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "enemy.h"

class Enemy;
class Player{
public:
    Player();

    //Stats
    int health;
    int attackPower;
    int defense;
    int level;
    int xp;

    void attack(Enemy& enemy);
    void takeDamage(int damage);
    void gainXP(int amount);
    void levelup();
    void displayStats();
};

#endif

