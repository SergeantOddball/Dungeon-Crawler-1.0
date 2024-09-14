#include "player.h"
#include "enemy.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

bool randomEncounter(){
    int chance = rand() % 100;
    return chance < 30;
}

Enemy generateRandomEnemy(bool& encounterHappened){
    int enemyType = rand() % 5;

    switch (enemyType){
        case 0:
            encounterHappened = true;
            return Enemy("Orc", 70, 10, 5, 30);
        case 1:
            encounterHappened = true;
            return Enemy("Skeleton", 60, 20, 10, 35);
        case 2:
            encounterHappened = true;
            return Enemy("Goblin", 50, 8, 2, 15);
        case 3:
            encounterHappened = true;
            return Enemy("Mimic", 200, 1, 10, 100);
        case 4:
            encounterHappened = false;
            return Enemy("", 0, 0, 0, 0);
        default:
            encounterHappened = false;
            return Enemy("", 0, 0, 0, 0);
    }
}

int main(){
    srand(time(0));
    Player player;
    bool exploring = true;

    cout << "Welcome to the dungeon!\n";

    while(exploring && player.health > 0){
        cout << "Choose a direction (left, right, straight, or quit)\n";
        string direction;
        cin >> direction;

        if(direction == "quit"){
            exploring = false;
            cout << "You have chosen to leave the dungeon.\n";
            break;
        }
        else if(direction == "left" || direction == "right" || direction == "straight"){
            cout << "You walk " << direction << "...\n";

            if(randomEncounter()){
                cout << "You have encountered an enemy!\n";
                bool encounterHappened = false;
                Enemy enemy = generateRandomEnemy(encounterHappened);
                enemy.displayEnemy();

                while(enemy.isAlive() && player.health > 0){
                    cout << "What will you do? (attack or flee): ";
                    string action;
                    cin >> action;

                    if(action == "attack"){
                        player.attack(enemy);

                        if(!enemy.isAlive()){
                            cout << "You have defeated " << enemy.name << ".\n";
                            player.gainXP(enemy.xpReward);
                        }
                        else{
                            enemy.attack(player);
                        }
                    }
                    else if(action == "flee"){
                        cout << "You have successflly fled.\n";
                        break;
                    }
                    else{
                        cout << "Invalid input. You lost your turn.\n";
                        enemy.attack(player);
                    }

                    if(player.health <= 0){
                        cout << "You have been defeated.\n";
                        return 0;
                    }
                }
        
            }
            else{
                cout << "No enemies encountered at this time.\n";
            }
        }
        else{
            cout << "Invalid input.\n";
        }
        
    } 



    if(player.health > 0){
        cout << "You have survived.\n";
        player.displayStats();
    } 


    return 0;

}