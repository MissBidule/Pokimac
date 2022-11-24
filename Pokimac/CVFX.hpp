//
//  CVFX.hpp
//  Pokimac
//
//  Created by LouLiLou on 12/01/2022.
//

#ifndef CVFX_hpp
#define CVFX_hpp

#include <stdio.h>
#include "CAnimation.hpp"
#include "CSurface.hpp"
#include "CCamera.hpp"

class CVFX : public CAnimation {
    
private:
    SDL_Surface* Surf_VFX;
    
private:
    int nbW;
    int width;
    int height;
    
public:
    int X;
    int Y;
    
    int frameCol;
    int frameRow;
    
    int currentFrameCol;
    int currentFrameRow;
    
public:
    CVFX();
    
public:
    //Regarde et arrete le VFX une fois qu'il a fini
    bool VFX_end();
    void Start();
    void Stop();
    
    bool OnLoad(char* file, int width, int height, int maxFrames, bool transparency, int R=0, int G=0, int B=0);
    void OnRender(SDL_Surface* Surf_Display);
    void OnCleanup();
};

#endif /* CVFX_hpp */
