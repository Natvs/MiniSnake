#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../include/colors.h"

#define PLAYER_COLOR color_orange
#define PLAYER_LOSTCOLOR color_black
#define PLAYER_XCOORD 0
#define PLAYER_YCOORD 0
#define PLAYER_MAXLENGTH 20

struct Player {
    int xcoord;
    int ycoord;
    SDL_Color color;
    struct Player *next;
};
typedef struct Player Player;

Player *create_player();
void set_player(Player *player, int xcoord, int ycoord, SDL_Color color);
void set_PlayerColor(Player *player, SDL_Color color);
void extend_player(Player *player, int xcoord, int ycoord);
void move_player(Player *player, int xcoord, int ycoord);
bool is_player(Player *player, int xcoord, int ycoord);