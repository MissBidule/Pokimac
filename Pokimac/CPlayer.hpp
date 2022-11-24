//
//  CPlayer.hpp
//  Pokimac
//
//  Created by LouLiLou on 02/01/2022.
//

#ifndef CPlayer_hpp
#define CPlayer_hpp

#include <stdio.h>
#include "CPokimac.hpp"

class CPlayer : public CEntity {
    
public:
    static std::vector<CPokimac*> PKM_team;

public:
    int battle_won;
    
public:
    CPlayer();
    
    bool OnLoad(char* File, int width, int height, int maxFrames, bool transparency, int R=0, int G=0, int B=0);
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
    void OnCleanup();
    void OnAnimate();
    bool OnCollision(CEntity* entity);
};

#endif /* CPlayer_hpp */
