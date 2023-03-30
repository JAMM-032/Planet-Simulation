#pragma once

#include <SDL2/SDL.h>

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

void display(SDL_Renderer *renderer);

void caca_fill(SDL_Renderer *renderer, int x, int y);

void set_color(SDL_Renderer *renderer, int r, int g, int b);

void reset_col(SDL_Renderer *renderer);

void line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);