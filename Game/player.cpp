#include "player.h"
#include <iostream>

using namespace std;

// Constructor initializes player stats
Player::Player(){
    health = 100;
    attackPower = 15;
    defense = 10;
    xp = 0;
    level = 1;
    xpToLevel = 100;
    isGuarding = false;
}

void Player::attack(Enemy& enemy) {
    int damage = attackPower - (1 - enemy.defense / 100);
    if (damage < 0) damage = 0;
    enemy.health -= damage;
    cout << "You dealt " << damage << " damage to the enemy!\n";
}

// void Player::takeDamage(int damage) {
//     int netDamage = damage - defense;
//     if (netDamage < 0) netDamage = 0;
//     health -= netDamage;
//     cout << "You took " << netDamage << " damage!\n";
// }

void Player::takeDamage(int damage){
    if(isGuarding){
        damage = damage * 0.5;
        cout << "You took " << damage << " damage!" << endl;
    }
    else{
        cout << "You took " << damage << " damage!" << endl;
    }
    health -= damage;
}

void Player::guard(){
    isGuarding = true;
    cout << "You guard." << endl;
}

void Player::stopGuard(){
    isGuarding = false;
}

void Player::gainXP(int amount){
    xp += amount;
    cout << "You gained " << amount << " XP.\n";
    levelup();
}

void Player::levelup() {
    if (xp >= 100) {
        xp -= xpToLevel;
        xpToLevel += 25;
        level++;
        attackPower += 5;
        defense += 3;
        health += 10;
        // xp = 0; 
        cout << "You leveled up! Level: " << level << "\n";
    }
}

void Player::displayStats() {
    cout << "Health: " << health << "\n";
    cout << "Attack Power: " << attackPower << "\n";
    cout << "Defense: " << defense << "\n";
    cout << "Level: " << level << "\n";
    cout << "XP: " << xp << "/100\n";
}
