//
//  Define.h
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#ifndef Define_h
#define Define_h

#include <SDL/SDL_ttf.h>
// Pour utiliser srand et rand
#include <cstdlib>
#include <time.h>

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

#define TILE_SIZE 32

#define WWIDTH 960
#define WHEIGHT 640

void DrawText(SDL_Surface* Surf_Display, char* string, int size, short x, short y, uint8_t R, uint8_t G, uint8_t B, int outline = 0);

int GenerAlea(int maxi, int mini = 1);

#endif /* Define_h */

