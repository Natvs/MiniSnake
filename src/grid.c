#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../include/grid.h"

SDL_Color get_cellColor() {
    SDL_Color color = {0, 255, 255, 255};
    return color;
}

SDL_Surface *Grid_createCellSurface(Cell cell) {
    SDL_Surface *surface = SDL_CreateRGBSurface(0, cell.rect.w, cell.rect.h, CELL_COLORFORMAT, 0, 0, 0, 0);
    const SDL_Rect rect = {cell.margin, cell.margin, cell.rect.w-cell.margin, cell.rect.h-cell.margin};
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, cell.color.r, cell.color.g, cell.color.b));
    return surface;
}
SDL_Surface *Grid_createSurface(Grid grid) {
    SDL_Surface *surface = SDL_CreateRGBSurface(0, grid.rect.w, grid.rect.h, CELL_COLORFORMAT, 0, 0, 0, 0);
    Cell *cell = malloc(sizeof(struct Cell));
    SDL_Surface *cell_surface = malloc(sizeof(SDL_Surface));
    for (int i=0; i<grid.xcells*grid.ycells; i++){
        cell_surface = Grid_createCellSurface(grid.cells[i]);
        *cell = grid.cells[i];
        SDL_Rect srcrect = {0,0,cell->rect.w,cell->rect.h};
        SDL_Rect desrect = {cell->rect.x, cell->rect.y, cell->rect.w, cell->rect.h};
        SDL_BlitSurface(cell_surface, &srcrect, surface, &desrect);
    }
    free(cell);
    SDL_FreeSurface(cell_surface);
    return surface;
}

void printrect(SDL_Rect rect) {
    printf("x=%d, y=%d, w=%d, h=%d", rect.x, rect.y, rect.w, rect.h);
}

Cell *create_Cell() {
    Cell *cell = malloc(sizeof(Cell));
    cell->rect.x=0;
    cell->rect.y=0;
    cell->rect.w=10;
    cell->rect.h=10;
    cell->color.r=0;
    cell->color.g=0;
    cell->color.b=0;
    cell->color.a=0;
    return cell;
}
void set_Cell(Cell *cell, SDL_Rect rect, SDL_Color color, int margin){
    cell->rect.x=rect.x;
    cell->rect.y=rect.y;
    cell->rect.w=rect.w;
    cell->rect.h=rect.h;
    cell->color.r=color.r;
    cell->color.g=color.g;
    cell->color.b=color.b;
    cell->color.a=color.a;
    cell->margin=margin;
}
void set_CellColor(Cell *cell, SDL_Color color){
    cell->color.r=color.r;
    cell->color.g=color.g;
    cell->color.b=color.b;
    cell->color.a=color.a;
}

Grid *create_Grid() {
    Grid *grid = malloc(sizeof(Grid));
    grid->cells = malloc(sizeof(Cell));
    grid->rect.x=0;
    grid->rect.y=0;
    grid->rect.w=100;
    grid->rect.h=100;
    grid->xcells=0;
    grid->ycells=0;
    return grid;
}
void set_grid(Grid *grid, SDL_Rect rect, int xcells, int ycells, Cell *cells) {
    grid->cells=cells;
    grid->rect.x=rect.x;
    grid->rect.y=rect.y;
    grid->rect.w=rect.w;
    grid->rect.h=rect.h;
    grid->xcells=xcells;
    grid->ycells=ycells;
}
Cell *get_gridCell(Grid *grid, int x, int y) {
    return &(grid->cells[x*grid->xcells+y]);
}
void init_gridDimensions(Grid *grid, int xcells, int ycells){
    grid->xcells=xcells;
    grid->ycells=ycells;
    grid->cells=malloc((grid->xcells)*(grid->ycells)*sizeof(struct Cell));
} 