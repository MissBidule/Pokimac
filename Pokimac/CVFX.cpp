//
//  CVFX.cpp
//  Pokimac
//
//  Created by LouLiLou on 12/01/2022.
//

#include "CVFX.hpp"

CVFX::CVFX() {
    X = 0;
    Y = 0;
    nbW = 0;
    width = 0;
    height = 0;
    frameCol = 0;
    frameRow = -1;
    currentFrameCol = 0;
    currentFrameRow = 0;
    Surf_VFX = NULL;
}

bool CVFX::VFX_end() {
    if ((GetCurrentFrame() >= maxFrames-1) || (frameRow == -1)){
        frameRow = -1;
        currentFrame = 0;
        return true;
    }
    return false;
}

void CVFX::Start() {
    frameRow = 0;
}

void CVFX::Stop() {
    frameRow = -1;
    currentFrame = 0;
}

bool CVFX::OnLoad(char* File, int width, int height, int maxFrames, bool transparency, int R, int G, int B) {
    if ((Surf_VFX = CSurface::OnLoad(File, transparency)) == NULL) {
        return false;
    }
    
    if (transparency) {
        CSurface::Transparent(Surf_VFX, R, G, B);
    }
    
    this->nbW = Surf_VFX->w / width;
    this->width = width;
    this->height = height;
    
    this->maxFrames = maxFrames;
    
    return true;
}

void CVFX::OnRender(SDL_Surface* Surf_Display) {
    if (Surf_VFX == NULL || Surf_Display == NULL) return;
    
    if (VFX_end()) return;
    
    CSurface::OnDraw(Surf_Display, Surf_VFX, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY(), (frameCol + GetCurrentFrame()%nbW) * width, (frameRow + GetCurrentFrame()/nbW) * height, width, height);
}

void CVFX::OnCleanup() {
    if (Surf_VFX) {
        SDL_FreeSurface(Surf_VFX);
    }
    
    Surf_VFX = NULL;
}
