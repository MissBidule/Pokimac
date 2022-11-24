//
//  CApp_OnEvent.cpp
//  Pokimac
//
//  Created by LouLiLou on 30/12/2021.
//

#include <stdio.h>
#include "CApp.h"

void CApp::OnEvent(SDL_Event *Event) {
    CEvent::OnEvent(Event);
}

void CApp::OnLButtonDown(int mX, int mY) {
    if (inMenu) {
        //On renvoie vrai si on sort du menu
        if (menu.OnEvent(mX, mY)) {
            inMenu = false;
            inMap = true;
        }
    }
    
    if (inFight) {
        battle.OnEvent(mX, mY);
    }
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    if (inMap) {
        switch (sym) {
            case SDLK_LEFT:
                player.moveLeft = true;
                break;
                
            case SDLK_RIGHT:
                player.moveRight = true;
                break;
                
            case SDLK_UP:
                player.moveUp = true;
                break;
                
            case SDLK_DOWN:
                player.moveDown = true;
                break;
                
            case SDLK_SPACE:
                player.Jump();
                break;
                
            default:
                break;
        }
    }
}

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    if (sym == SDLK_ESCAPE) {
        OnExit();
        return;
    }
        
    if (inMap) {
        switch (sym) {
            case SDLK_LEFT:
                player.moveLeft = false;
                break;
                
            case SDLK_RIGHT:
                player.moveRight = false;
                break;
                
            case SDLK_UP:
                player.moveUp = false;
                break;
                
            case SDLK_DOWN:
                player.moveDown = false;
                break;
                
            default:
                break;
        }
    }
}

void CApp::OnExit() {
    Running = false;
}
