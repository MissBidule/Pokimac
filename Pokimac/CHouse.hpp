//
//  CHouse.hpp
//  Pokimac
//
//  Created by LouLiLou on 07/01/2022.
//

#ifndef CHouse_hpp
#define CHouse_hpp

#include <SDL/SDL.h>
#include <stdio.h>
// Pour utiliser srand et rand
#include <cstdlib>
#include "CEntity.hpp"

class CHouse : public CEntity {

public:
    CHouse();
    
    static bool OnLoad(char* File, int width, int height, bool transparency, int R=0, int G=0, int B=0);
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
    void OnCleanup();
    void OnAnimate();
    bool OnCollision(CEntity* entity);
};

#endif /* CHouse_hpp */
