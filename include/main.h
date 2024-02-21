#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../include/gamedatas.h"
#include "../include/grid.h"
#include "../include/player.h"
#include "../include/goal.h"

#define DISPLAY_INTERVAL 200
#define DISPLAY_LOSTINTERVAL 100

#define MOVEDIRECTION_UP 1
#define MOVEDIRECTION_DOWN 2
#define MOVEDIRECTION_LEFT 3
#define MOVEDIRECTION_RIGHT 4

int main(void);
void start_game(SDL_Renderer *renderer, GameDatas *gamedatas);
SDL_Surface *create_gridSurface(Grid *grid, Player *player, Goal *goal);
void draw_grid(SDL_Renderer *renderer, Grid *grid, Player *player, Goal *goal);
void msg_state(int status);

void set_newGoal(Goal *goal, Grid *grid, Player *player);
void keydown_events(SDL_Event event, int *move_direction, GameDatas *gamedatas);

void player_moveright(Grid *grid, Player *player, Goal *goal, GameDatas *gamedatas);
void player_moveleft(Grid *grid, Player *player, Goal *goal, GameDatas *gamedatas);
void player_moveup(Grid *grid, Player *player, Goal *goal, GameDatas *gamedatas);
void player_movedown(Grid *grid, Player *player, Goal *goal, GameDatas *gamedatas);