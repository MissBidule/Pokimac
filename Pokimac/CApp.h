//
//  CApp.h
//  Pokimac
//
//  Created by LouLiLou on 30/12/2021.
//

#ifndef CApp_h
#define CApp_h

#include <algorithm>
#include <SDL/SDL.h>
#include "CPlayer.hpp"
#include "CSurface.hpp"
#include "CAnimation.hpp"
#include "CEvent.hpp"
#include "CArea.hpp"
#include "CCamera.hpp"
#include "CPokimac.hpp"
#include "CHouse.hpp"
#include "CMenu.hpp"
#include "CBattle.hpp"

class CApp : public CEvent {
    
private:
    bool Running;
    SDL_Surface* Surf_Display;
    CVFX VFX_FW1;
    CVFX VFX_FW2;
    
private:
    Timer clock;
    bool FW;
    CPlayer player;
    CMenu menu;
    CBattle battle;
    
public:
    bool inMenu;
    bool inMap;
    bool inFight;
    bool inVictory;
    bool inDefeat;
    
public:
    CApp(char * path);
    int OnExecute();
    
public:
    bool OnInit();
    void OnEvent(SDL_Event* Event);
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnLButtonDown(int mX, int mY);
    void OnExit();
    void OnLoop();
    void OnRender();
    void OnCleanup();
    
};

#endif /* CApp_h */
