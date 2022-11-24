//
//  CMap.hpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#ifndef CMap_hpp
#define CMap_hpp

#include <stdio.h>
#include <SDL/SDL.h>
#include <vector>
#include "CTile.hpp"
#include "CSurface.hpp"

class CMap {
    
public:
    SDL_Surface* Surf_Tileset;
    SDL_Surface* Surf_Decoset;
    
private:
    std::vector<CTile> TileList;
    std::vector<CTile> DecoList;
    
public:
    CMap();
    
public:
    bool OnLoad(char* FileMap, char* FileDeco);
    void OnRender(SDL_Surface* Surf_Display, int mapX, int mapY);
    
public:
    CTile* GetTile(int X, int Y);
};

#endif /* CMap_hpp */
