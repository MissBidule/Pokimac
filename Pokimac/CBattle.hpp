//
//  CBattle.hpp
//  Pokimac
//
//  Created by LouLiLou on 10/01/2022.
//

#ifndef CBattle_hpp
#define CBattle_hpp

#include <stdio.h>
#include <string>
#include "CSurface.hpp"
#include "Define.h"
#include "CPokimac.hpp"
#include "CPlayer.hpp"
#include "CTimer.hpp"
#include "CVFX.hpp"

class CBattle {
    
private:
    SDL_Surface* Surf_BG;
    SDL_Surface* Surf_HB;
    
    //Explosion et animation de la Pokiball
    CVFX VFX_I;
    CVFX VFX_M;
    CVFX VFX_A;
    CVFX VFX_C;
    CVFX VFX_PKBall;
    
private:
    Timer clock;
    int pause;
    CPokimac* opponent;
    bool turn;
    int difficulty;
    bool flee;
    bool win;
    bool lost;
    bool caught;
    bool suspense;
    
    //Textes divers pour decrire les actions en combat
    char text1[255];
    char text2[255];
    char text3[255];
    
public:
    CBattle();
    
    bool OnLoad();
    //Initialisation de chaque combat
    void Start(CPokimac* PKM_opponent);
    void OnEvent(int mouse_x, int mouse_y);
    int OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
    void OnCleanup();
    
private:
    void OnRenderP1(SDL_Surface* Surf_Display);
    void OnRenderP2(SDL_Surface* Surf_Display);
    void Attack(int n);
    //Determine l'attaque que l'ennemi va effectuer
    void OppAttack();
    void Change_PKM(int n);
    void PKBall();
    void Flee();
    void Win();
    void Lost();
    //Compare les resistances et les faiblesses des types
    float ComparerTypes(int attack, int defense);
};

#endif /* CBattle_hpp */
