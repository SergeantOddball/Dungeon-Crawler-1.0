#include "player.h"
#include "enemy.h"
#include "floor1.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

Enemy generateRandomEnemy(){
    int enemyType = rand() % 2;

    switch (enemyType){
        case 0:
            return Enemy("Slime", 20, 5, 5, 5);
        case 1:
            return Enemy("Goblin", 30, 6, 6, 15);
        default:
            return Enemy("", 0, 0, 0, 0);
    }
}

vector<Enemy> generateAmbush(int numEnemies){
    vector<Enemy> enemies;
    for(int i = 0; i < numEnemies; i++){
        enemies.push_back(generateRandomEnemy());
    }
    return enemies;
}

Enemy generateBoss(){
    return Enemy("King Slime", 75, 10, 10, 100);
}

void runfloor1(Player& player, int floorNumber, int requiredSteps){
    int stepsTaken = 0;
    bool exploring = true;
    bool encounterHappened = false;

    cout << "Welcome to the dungeon.\n";
    cout << "You are on Floor 1.\n";

    while(exploring && player.health > 0 && stepsTaken < requiredSteps){
        cout << "Choose a direction (left, right, straight, quit): ";
        string direction;
        cin >> direction;

        if(direction == "quit"){
            exploring = false;
            cout << "You have chosen to leave the dungeon.\n";
            player.displayStats();
        }
        else if(direction == "left" || direction == "right" || direction == "straight"){
            cout << "You walk " << direction << "...\n";
            bool ambushHappened = (rand() % 100 < 30); // 30% chance for ambush

            if(ambushHappened){
                int numEnemies = rand() % 2 + 1;
                vector<Enemy> enemies = generateAmbush(numEnemies);
                cout << "You have been ambused by " << enemies.size() << " enemies.\n";

                for(Enemy& enemy : enemies){
                    enemy.displayEnemy();
                    enemy.attack(player);

                    if(player.health <= 0){
                        cout << "You have been defeated.\n";
                        return;
                    }
                }

                while(!enemies.empty() && player.health > 0){
                    cout << "Remaining enemies: \n";
                    for (size_t i = 0; i < enemies.size(); ++i){
                        cout << (i + 1) << ". " << enemies[i].name << " : " << enemies[i].health << "\n";
                    }

                    int enemyChoice;
                    cout << "Choose an enemy to attack (1-" << enemies.size() << "): ";
                    cin >> enemyChoice;

                    if(enemyChoice < 1 || enemyChoice > enemies.size()){
                        cout << "Invalid choice. You lose your turn.\n";
                        continue;
                    }

                    Enemy& chosenEnemy = enemies[enemyChoice - 1];
                    player.attack(chosenEnemy);

                    if(!chosenEnemy.isAlive()){
                        cout << "You have defeated " << chosenEnemy.name << ".\n";
                        player.gainXP(chosenEnemy.xpReward);
                        enemies.erase(enemies.begin() + (enemyChoice - 1));
                    }

                    for(Enemy& enemy : enemies){
                        enemy.attack(player);

                        if(player.health <= 0){
                            cout << " You have been defeated.\n";
                            return;
                        }
                    }
                } 
            }
            
        
            else{
                bool regularEncounter = (rand() % 100 < 30);
                if(regularEncounter){
                    encounterHappened = true;
                    Enemy enemy = generateRandomEnemy();
                    enemy.displayEnemy();

                    while(enemy.isAlive() && player.health > 0){
                        cout << "1. Attack\n";
                        cout << "2. Flee\n";
                        cout << "3. Guard" << endl;
                        cout << "What will you do? : ";
                        string action;
                        cin >> action;

                        if(action == "1"){
                            player.attack(enemy);

                            if(!enemy.isAlive()){
                                cout << "You have defeated " << enemy.name << ".\n";
                                player.gainXP(enemy.xpReward);
                            }
                            else{
                                enemy.attack(player);
                            }
                        }
                        else if(action == "2"){
                            cout << " You have fled from combat.\n";
                            break;
                        }
                        else if(action == "3"){
                            player.guard();
                            enemy.attack(player);
                            player.stopGuard();
                        }
                        else{
                            cout << "Invalid action. You have lost your turn.\n";
                            enemy.attack(player);
                        }

                        if(player.health <= 0){
                            cout << "You have been defeated.\n";
                            return;
                        }
                    }

                }
                else{
                    cout << "No enemies encountered." << endl;
                }
                stepsTaken++;
            }
        }
        else{
            cout << "Invalid direction.\n";
        }
       
    }

    if(stepsTaken >= requiredSteps){
        cout << "There is a boss fight ahead." << endl;
        Enemy boss = generateBoss();
        boss.displayEnemy();
        while(boss.isAlive() && player.health > 0){
            cout << "1. Attack\n";
            cout << "2. Flee\n";
            cout << "3. Guard" << endl;
            cout << "What will you do? : ";
            string action;
            cin >> action;

            if(action == "1"){
                player.attack(boss);

                if(!boss.isAlive()){
                    cout << " You have defeated " << boss.name << ".\n";
                    player.gainXP(boss.xpReward);
                }
                else{
                    boss.attack(player);
                }
                        }
            else if(action == "2"){
                cout << " You are unable to flee.\n";
            }
            else if(action == "3"){
                player.guard();
                boss.attack(player);
                player.stopGuard();
            }
            else{
                cout << "Invalid action. You have lost your turn.\n";
                boss.attack(player);
            }

            if(player.health <= 0){
                cout << "You have been defeated.\n";
                return;
            }

        }
    }
}