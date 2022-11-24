//
//  CFPS.hpp
//  Pokimac
//
//  Created by LouLiLou on 02/01/2022.
//

#ifndef CFPS_hpp
#define CFPS_hpp

#include <stdio.h>
#include <SDL/SDL.h>

class CFPS {
    
public:
    static CFPS FPSControl;
    
private:
    int oldTime;
    int lastTime;
    
    //Donnee qui permet de s'adapter a la vitesse de l'ordinateur
    float speedFactor;
    
    int numFrames;
    int frames;
    
public:
    CFPS();
    
    void OnLoop();
    
public:
    int GetFPS();
    float GetSpeedFactor();
};

#endif /* CFPS_hpp */
