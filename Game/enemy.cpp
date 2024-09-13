#include "enemy.h"
#include "player.h"
#include <iostream>

using namespace std;

// Constructor
Enemy::Enemy(int h, int ap, int def, int xp) : health(h), attackPower(ap), defense(def), xpReward(xp) {}

void Enemy::attack(Player& player){
    int damage = attackPower - player.defense;
    if(damage < 0){
        damage = 0;
    }
    player.takeDamage(damage);
    //cout << "Enemy dealt " << damage << " damage to you.\n";

}

void Enemy::takeDamage(int amount){
    health -= amount;
    cout << "Enemy has taken " << " damage.\n";
}

bool Enemy::isAlive(){
    return health > 0;
}
