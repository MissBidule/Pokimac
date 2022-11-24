//
//  CMenu.hpp
//  Pokimac
//
//  Created by LouLiLou on 07/01/2022.
//

#ifndef CMenu_hpp
#define CMenu_hpp

#include <stdio.h>
#include "CSurface.hpp"
#include "Define.h"
#include "CPokimac.hpp"

class CMenu {
    
private:
    SDL_Surface* Surf_Title;
    SDL_Surface* Surf_Options;
    SDL_Surface* Surf_Simple;
    
private:
    //Nombre d'affrontements souhaites par l'utilisateur
    int screen_Battle_Goal;
    int battle_Goal;
    int max_Battle_Goal;
    
private:
    //Variables de navigations dans le menu
    bool options;
    bool rules;
    bool starter;
    int rules_nb;
    
public:
    CMenu();
    
    bool OnLoad(char* File);
    bool OnEvent(int mouse_x, int mouse_y);
    void OnRender(SDL_Surface* Surf_Display);
    void OnCleanup();
    
private:
    void OnRenderMenu(SDL_Surface* Surf_Display);
    void OnRenderOptions(SDL_Surface* Surf_Display);
    void OnRenderRules(SDL_Surface* Surf_Display);
    void OnRenderStarter(SDL_Surface* Surf_Display);
    
public:
    int GetBattleGoal();
    
private:
    void SetBattleGoal(bool increase);
};


#endif /* CMenu_hpp */
