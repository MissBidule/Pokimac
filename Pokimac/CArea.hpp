//
//  CArea.hpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#ifndef CArea_hpp
#define CArea_hpp

#include <stdio.h>
#include "CMap.hpp"
#include "CSurface.hpp"

class CArea {
    
public:
    static CArea AreaControl;
    
public:
    std::vector<CMap>   MapList;
    
private:
    //Utile pour les grandes cartes
    int areaSize;
    SDL_Surface* Surf_Tileset;
    SDL_Surface* Surf_Decoset;
    
public:
    CArea();
    bool OnLoad(char* File);
    void OnRender(SDL_Surface* Surf_Display, int cameraX, int cameraY);
    void OnCleanup();
    
public:
    //A quel bout de carte correspond les coordonnees envoyees ?
    //Pas utilise ici
    CMap* GetMap(int X, int Y);
    CTile* GetTile(int X, int Y);
};

#endif /* CArea_hpp */
