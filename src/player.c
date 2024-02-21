#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../include/player.h"

Player *create_player() {
    Player *player = malloc(sizeof(struct Player));
    player->next=NULL;
    player->xcoord=0;
    player->ycoord=0;
    player->color.r=0;
    player->color.g=0;
    player->color.b=0;
    player->color.a=0;
    return player;
}
void set_player(Player *player, int xcoord, int ycoord, SDL_Color color) {
    player->xcoord=xcoord;
    player->ycoord=ycoord;
    player->color.r=color.r;
    player->color.g=color.g;
    player->color.b=color.b;
    player->color.a=color.a;
}
void set_PlayerColor(Player *player, SDL_Color color) {
    player->color.r=color.r;
    player->color.g=color.g;
    player->color.b=color.b;
    player->color.a=color.a;
}
void extend_player(Player *player, int xcoord, int ycoord){
    Player *tmpplayer = create_player();
    *tmpplayer=*player;
    set_player(player, xcoord, ycoord, player->color);
    player->next=tmpplayer;
}
void move_player(Player *player, int xcoord, int ycoord){
    if (player->next!=NULL){
        move_player(player->next, player->xcoord, player->ycoord);
    }
    player->xcoord=xcoord;
    player->ycoord=ycoord;
}
bool is_player(Player *player, int xcoord, int ycoord){
    if (player->xcoord==xcoord && player->ycoord==ycoord){
        return true;
    }
    if (player->next==NULL){
        return false;
    }
    return is_player(player->next, xcoord, ycoord);
}