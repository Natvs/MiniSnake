#include <stdlib.h>
#include <stdio.h>

#include "../include/gamedatas.h"

GameDatas *create_gamedatas(){
    GameDatas *gamedatas = malloc(sizeof(GameDatas));
    gamedatas->quit=false;
    gamedatas->restart=false;
    return gamedatas;
}