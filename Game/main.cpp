#include "player.h"
#include "enemy.h"
#include "floor1.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    Player player;

    runfloor1(player, 1, 5);

    if(player.health > 0 ){
        cout << "You have survived with the following stats: " << endl;
        player.displayStats();
    }
    return 0;
}