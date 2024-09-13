#include "player.h"
#include "enemy.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(){
    Player player;
    vector<Enemy> enemies;

    enemies.push_back(Enemy(50, 8, 2, 30));
    enemies.push_back(Enemy(70, 10, 5, 50));
    enemies.push_back(Enemy(100, 12, 8, 80));

    cout << "Enemy Ambush!\n";

    while(!enemies.empty() && player.health > 0){
        cout << "There are " << enemies.size() << " enemies.\n";

        for (size_t i = 0; i < enemies.size(); i++){
            cout << i + 1 << ". Enemy " << i + 1 << " - Health: " << enemies[i].health << "\n";

        }

        cout << "You have " << player.health << " hitpoints.\n";

        int enemyChoice;
        cout << "Choose an enemy to attack (1 - " << enemies.size() << "): ";
        cin >> enemyChoice;

        if (enemyChoice < 1 || enemyChoice > enemies.size()){
            cout << "Invalid choice. You lost your turn.\n";
            continue;
        }

        Enemy& chosenEnemy = enemies[enemyChoice - 1];
        player.attack(chosenEnemy);

        if(!chosenEnemy.isAlive()){
            cout << "You have defeated the enemy.\n";
            player.gainXP(chosenEnemy.xpReward);
            enemies.erase(enemies.begin() + (enemyChoice - 1));
        }

        for(Enemy& enemy : enemies){
            enemy.attack(player);
            if(player.health <= 0){
                cout << "You have been defeated.\n";
                cout << "GAME OVER\n";
                return 0;
            }
        }

    }

    if(player.health > 0){
        cout << "You have defeated all enemies.\n";
        player.displayStats();
    } 


    return 0;

}