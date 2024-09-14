#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"

class Player;

class Enemy {
public:

    Enemy(std::string name, int h, int ap, int def, int xp);

    // Enemy attributes
    std::string name;
    int health;
    int attackPower;
    int defense;
    int xpReward;

    // Enemy methods
    void attack(Player& player); 
    void takeDamage(int amount);  
    bool isAlive(); 
    void displayEnemy();              
};

#endif
