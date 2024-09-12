#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:

    Enemy(int h, int ap, int def);

    // Enemy attributes
    int health;
    int attackPower;
    int defense;

    // Enemy methods
    void attack(Player& player); 
    void takeDamage(int amount);  
    bool isAlive();               
};

#endif
