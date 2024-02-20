#include <SDL2/SDL.h>
#include "../include/colors.h"

#define GRID_XMARGIN 50
#define GRID_YMARGIN 50
#define GRID_XCELLS 20
#define GRID_YCELLS 20
#define GRID_WIDTH GRID_XCELLS*CELL_WIDTH
#define GRID_HEIGHT GRID_YCELLS*CELL_HEIGT
#define CELL_WIDTH 30
#define CELL_HEIGT 30
#define CELL_COLORFORMAT 32
#define CELL_MARGIN 2
#define CELL_COLOR color_cyan

SDL_Color get_cellColor();
#define CELL_COLOR get_cellColor()

struct Cell {
    SDL_Rect rect;
    SDL_Color color;
    int margin;
};
typedef struct Cell Cell;
Cell *create_Cell();
void set_Cell(Cell *cell, SDL_Rect rect, SDL_Color color, int margin);
void set_CellColor(Cell *cell, SDL_Color color);

struct Grid {
    SDL_Rect rect;
    int xcells;
    int ycells;
    Cell *cells;
};
typedef struct Grid Grid;
Grid *create_Grid();
void set_Grid(Grid *grid, SDL_Rect rect, int xcells, int ycells, Cell *cells);
void init_gridDimensions(Grid *grid, int xcells, int ycells);
Cell *get_gridCell(Grid *grid, int x, int y);

SDL_Surface* Grid_createCellSurface(Cell cell);
SDL_Surface* Grid_createSurface(Grid grid);
void printrect(SDL_Rect rect);