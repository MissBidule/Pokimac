//
//  CFPS.cpp
//  Pokimac
//
//  Created by LouLiLou on 02/01/2022.
//

#include "CFPS.hpp"

CFPS CFPS::FPSControl;

CFPS::CFPS() {
    oldTime = 0;
    lastTime = 0;
    
    speedFactor = 0;
    
    frames = 0;
    numFrames = 0;
}

void CFPS::OnLoop() {
    //Compte quand une seconde est passee
    if (oldTime + 1000 < SDL_GetTicks()) {
        oldTime = SDL_GetTicks();
        
        numFrames = frames;
        
        frames = 0;
    }
    
    //Donnee calculee en partant de la vitesse "ideale" de 32FPS
    speedFactor = ((SDL_GetTicks() - lastTime) / 1000.0f) * 32.0f;
    
    lastTime = SDL_GetTicks();
    
    frames++;
}

int CFPS::GetFPS() {
    return numFrames;
}

float CFPS::GetSpeedFactor() {
    return speedFactor;
}
