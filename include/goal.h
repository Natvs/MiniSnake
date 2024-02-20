#include <SDL2/SDL.h>

SDL_Color get_goalColor();
#define GOAL_COLOR get_goalColor()
#define GOAL_XCOORD 3
#define GOAL_YCOORD 3

struct Goal {
    int xcoord;
    int ycoord;
    SDL_Color color;
};
typedef struct Goal Goal;
Goal *create_goal();
void set_goal(Goal *goal, int xcoord, int ycoord, SDL_Color color);