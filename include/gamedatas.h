#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct GameDatas{
    bool quit;
    bool restart;
    bool lost;
};
typedef struct GameDatas GameDatas;
GameDatas *create_gamedatas();