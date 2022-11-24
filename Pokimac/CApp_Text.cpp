//
//  CApp_Text.cpp
//  Pokimac
//
//  Created by LouLiLou on 02/01/2022.
//

#include <stdio.h>
#include "CApp.h"
#include "Define.h"

void DrawText(SDL_Surface *Surf_Display, char *string, int size, short x, short y, uint8_t R, uint8_t G, uint8_t B, int outline) {
    
    char font_name[] = "font/ARCADEPI.ttf";
    char font_Path[strlen(CSurface::Abs_path) + strlen(font_name)];
    strcpy(font_Path, CSurface::Abs_path);
    strcat(font_Path + strlen(font_Path), font_name);
    
    TTF_Font* font = TTF_OpenFont(font_Path, size);
    
    SDL_Color textColor = { R, G, B };
    
    TTF_SetFontOutline(font, outline);
    
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, string, textColor);
    
    SDL_Rect textLocation = { x, y, 0, 0};
    
    SDL_BlitSurface(textSurface, NULL, Surf_Display, &textLocation);
    
    SDL_FreeSurface(textSurface);
    
    TTF_CloseFont(font);
}
