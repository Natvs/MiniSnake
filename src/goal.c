#include "../include/goal.h"

Goal *create_goal(){
    Goal *goal = malloc(sizeof(struct Goal));
    goal->xcoord=0;
    goal->ycoord=0;
    goal->color.a=0;
    goal->color.r=0;
    goal->color.g=0;
    goal->color.a=255;
    return goal;
}
void set_goal(Goal *goal, int xcoord, int ycoord, SDL_Color color){
    goal->xcoord=xcoord;
    goal->ycoord=ycoord;
    goal->color.r=color.r;
    goal->color.g=color.g;
    goal->color.b=color.b;
    goal->color.a=color.a;
}
SDL_Color get_goalColor() {
    SDL_Color color = {255, 0, 0, 255};
    return color;
}