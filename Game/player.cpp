#include "player.h"
#include <iostream>

using namespace std;

// Constructor initializes player stats
Player::Player() : health(100), attackPower(25), defense(5), level(1), xp(0) {}

void Player::attack(Enemy& enemy) {
    int damage = attackPower - enemy.defense;
    if (damage < 0) damage = 0;
    enemy.health -= damage;
    cout << "You dealt " << damage << " damage to the enemy!\n";
}

void Player::takeDamage(int damage) {
    int netDamage = damage - defense;
    if (netDamage < 0) netDamage = 0;
    health -= netDamage;
    cout << "You took " << netDamage << " damage!\n";
}

void Player::gainXP(int amount){
    xp += amount;
    cout << "You gained " << amount << " XP.\n";
    levelup();
}

void Player::levelup() {
    if (xp >= 100) {
        level++;
        attackPower += 5;
        defense += 3;
        health += 10;
        xp = 0;  // Reset XP after leveling up
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
