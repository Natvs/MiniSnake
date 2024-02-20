#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <sys/random.h>
#include <time.h>

#include "../include/colors.h"
#include "../include/main.h"

int main(void){
    init_colors();
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameDatas *gamedatas = create_gamedatas();
    
    // initialisation of the window
    window = SDL_CreateWindow("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GRID_WIDTH + 2*GRID_XMARGIN, GRID_HEIGHT + 2*GRID_YMARGIN, SDL_WINDOW_SHOWN);
    if (window==NULL){
        printf("Error : SDL_CreateWindow : %s\n", SDL_GetError());
        msg_state(EXIT_FAILURE);
        abort();
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer==NULL){
        printf("Error : SDL_CreateRenderer : %s\n", SDL_GetError());
        msg_state(EXIT_FAILURE);
        abort();
    }

    start_game(renderer, gamedatas);
    while (!gamedatas->quit) {
        gamedatas->lost=false;
        if (gamedatas->restart){
            gamedatas->restart=false;
            start_game(renderer, gamedatas);
        }
        else {
            gamedatas->quit=true;
        }
    }

    // Allocated memory is made free here
    free(gamedatas);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    msg_state(EXIT_SUCCESS);
    return 0;
}

void start_game(SDL_Renderer *renderer, GameDatas *gamedatas){
    Grid *grid = create_Grid();
    Player *player = create_player();
    Goal *goal = create_goal();
    int move_direction = MOVEDIRECTION_RIGHT;

    // initialisation of the player
    set_player(player, PLAYER_XCOORD, PLAYER_YCOORD, PLAYER_COLOR);

    // initialisation of the goal
    set_goal(goal, GOAL_XCOORD, GOAL_YCOORD, GOAL_COLOR);

    // grid is drawn for the first time
    init_gridDimensions(grid, GRID_XCELLS, GRID_YCELLS);
    draw_grid(renderer, grid, player, goal);

    // game main loop
    SDL_Event event;
    while ((!gamedatas->quit) && (!gamedatas->restart)){
        draw_grid(renderer, grid, player, goal);
        SDL_Delay(DISPLAY_INTERVAL);
        while(SDL_PollEvent(&event)){          
            if (event.type==SDL_KEYDOWN){
                keydown_events(event, &move_direction, gamedatas);
            }
        }
        if (gamedatas -> lost){
            Player *next = player;
            while (next!=NULL){
                set_PlayerColor(next, PLAYER_LOSTCOLOR);
                draw_grid(renderer, grid, player, goal);
                SDL_Delay(DISPLAY_LOSTINTERVAL);
                next=next->next;
            }
            gamedatas->restart=true;
        }
        else if (move_direction==MOVEDIRECTION_DOWN){
            player_movedown(grid, player, goal, gamedatas);
        }
        else if (move_direction==MOVEDIRECTION_UP){
            player_moveup(grid, player, goal, gamedatas);
        }
        else if (move_direction==MOVEDIRECTION_RIGHT){
            player_moveright(grid, player, goal, gamedatas);
        }
        else if (move_direction==MOVEDIRECTION_LEFT){
            player_moveleft(grid, player, goal, gamedatas);
        }
    }

    // Game resources are made free here
    free(goal);
    free(player);
    free(grid);
}
void keydown_events(SDL_Event event, int *move_direction, GameDatas *gamedatas){
    if (event.key.keysym.sym==SDLK_q){
        gamedatas->quit=true;
    }
    if (event.key.keysym.sym==SDLK_r){
        gamedatas->restart=true;
    }
    if (event.key.keysym.sym==SDLK_UP){
        *move_direction=MOVEDIRECTION_UP;
    }
    if (event.key.keysym.sym==SDLK_LEFT){
        *move_direction=MOVEDIRECTION_LEFT;
    }
    if (event.key.keysym.sym==SDLK_DOWN){
        *move_direction=MOVEDIRECTION_DOWN;
    }
    if (event.key.keysym.sym==SDLK_RIGHT){
        *move_direction=MOVEDIRECTION_RIGHT;
    }
}

SDL_Surface *create_gridSurface(Grid *grid, Player *player, Goal *goal) {
    SDL_Surface *surface = malloc(sizeof(SDL_Surface));
    // Initialisation of grid and cells
    int i;
    init_gridDimensions(grid, GRID_XCELLS, GRID_YCELLS);
    for (int x=0; x<GRID_XCELLS; x++){
        for (int y=0; y<GRID_YCELLS; y++){
            i=x*GRID_XCELLS+y;
            if (goal->xcoord==x && goal->ycoord==y){
                set_CellColor(&(grid->cells[i]), goal->color);
            }
            else{
                set_CellColor(&(grid->cells[i]), CELL_COLOR);
            }
            grid->cells[i].rect.x = x*CELL_WIDTH;
            grid->cells[i].rect.y = y*CELL_HEIGT;
            grid->cells[i].rect.w = CELL_WIDTH;
            grid->cells[i].rect.h = CELL_HEIGT;
            grid->cells[i].margin = CELL_MARGIN;
        }
    }
    Player *next = player;
    int count = 0;
    while (next!=NULL){
        Cell *cell = get_gridCell(grid, next->xcoord, next->ycoord);
        set_CellColor(cell, next->color);
        next=next->next;
        count++;
    }
    grid->rect.x=0;
    grid->rect.y=0;
    grid->rect.w=GRID_XCELLS*CELL_WIDTH;
    grid->rect.h=GRID_YCELLS*CELL_HEIGT;
    grid->xcells=GRID_XCELLS;
    grid->ycells=GRID_YCELLS;
    surface=Grid_createSurface(*grid);
    if (surface==NULL){
        printf("Error: Grid_createSurface");
    }
    return surface;
}
void draw_grid(SDL_Renderer *renderer, Grid *grid, Player *player, Goal *goal){
    SDL_Texture *texture;
    SDL_Surface *grid_surface;
    grid_surface = create_gridSurface(grid, player, goal);
    if (grid_surface==NULL) {
        printf("Error : create_gridSurface");
    }

    // Grid is drawn on the texture
    texture = SDL_CreateTextureFromSurface(renderer, grid_surface);
    if (texture==NULL){
        printf("Error : SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        msg_state(EXIT_FAILURE);
        abort();
    }
    if  (0<SDL_SetRenderTarget(renderer, texture)) {
        printf("Error : SDL_SetRenderTarget : %s\n", SDL_GetError());
        msg_state(EXIT_FAILURE);
        abort();
    }
    int w; int h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect destrect = {GRID_XMARGIN, GRID_YMARGIN, w, h};
    if (0<SDL_RenderCopy(renderer, texture, NULL, &destrect)) {
        printf("Error : SDL_RenderCopy : %s\n", SDL_GetError());
        msg_state(EXIT_FAILURE);
        abort();
    }
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(grid_surface);
    SDL_DestroyTexture(texture);
}

void set_newGoal(Goal *goal, Grid *grid, Player *player){
    srand(time(NULL));
    int xrand = rand();
    int yrand = rand();
    extend_player(player, goal->xcoord, goal->ycoord);
    goal->xcoord=xrand%(grid->xcells);
    goal->ycoord=yrand%(grid->ycells);
}

void player_moveright(Grid *grid, Player *player, Goal *goal, GameDatas *gamedatas) {
    if (player->xcoord < grid->xcells-1 && !is_player(player, player->xcoord+1, player->ycoord)){
        move_player(player, player->xcoord+1, player->ycoord);
        if (player->xcoord == goal->xcoord && player->ycoord == goal->ycoord){
            set_newGoal(goal, grid, player);
        }
    }
    else {
        gamedatas->lost=true;
    }
}
void player_moveleft(Grid *grid, Player *player, Goal *goal, GameDatas *gamedatas) {
    if (player->xcoord > 0 && !is_player(player, player->xcoord-1, player->ycoord)){
        move_player(player, player->xcoord-1, player->ycoord);
        if (player->xcoord == goal->xcoord && player->ycoord == goal->ycoord){
            set_newGoal(goal, grid, player); 
        }
    }
    else {
        gamedatas->lost=true;
    }
}
void player_moveup(Grid *grid, Player *player, Goal *goal, GameDatas *gamedatas){
    if (player->ycoord > 0 && !is_player(player, player->xcoord, player->ycoord-1)){
        move_player(player, player->xcoord, player->ycoord-1);
        if (player->xcoord == goal->xcoord && player->ycoord == goal->ycoord){
            set_newGoal(goal, grid, player);
        }
    }
    else {
        gamedatas->lost=true;
    }
}
void player_movedown(Grid *grid, Player *player, Goal *goal, GameDatas *gamedatas){
    if (player->ycoord < grid->ycells-1 && !is_player(player, player->xcoord, player->ycoord+1)){
        move_player(player, player->xcoord, player->ycoord+1);
        if (player->xcoord == goal->xcoord && player->ycoord == goal->ycoord){
            set_newGoal(goal, grid, player);
        }
    }
    else {
        gamedatas->lost=true;
    }
}

void msg_state(int state) {
    printf("App ended with code %d\n", state);
}