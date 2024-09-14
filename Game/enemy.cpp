#include "enemy.h"
#include "player.h"
#include <iostream>

using namespace std;

// Constructor
Enemy::Enemy(std::string name, int h, int ap, int def, int xp) : name(name), health(h), attackPower(ap), defense(def), xpReward(xp) {}

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

void Enemy::displayEnemy(){
    cout << "You have encountered " << name << " .\n";
    cout << "Health: " << health << " , Attack: " << attackPower << " , Defense: " << defense << "\n";
}
