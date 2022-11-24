//
//  CAnimation.cpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#include "CAnimation.hpp"

CAnimation::CAnimation() {
    currentFrame = 0;
    maxFrames = 0;
    frameInc = 1;
    
    frameRate = 100; //Milliseconds
    oldTime = 0;
    
    //Animation qui boucle ou boomerang
    oscillate = false;
}

void CAnimation::OnAnimate() {
    if (oldTime + frameRate > SDL_GetTicks()) {
        return;
    }
    
    oldTime = SDL_GetTicks();
    
    currentFrame += frameInc;
    
    if (oscillate) {
        if (frameInc > 0) {
            if (currentFrame >= maxFrames) {
                frameInc = -frameInc;
            }
        }
        else if (currentFrame <= 0) {
            frameInc = -frameInc;
        }
    }
    else if (currentFrame >= maxFrames) {
        currentFrame = 0;
    }

}

void CAnimation::SetFrameRate(int rate) {
    frameRate = rate;
}

void CAnimation::SetCurrentFrame(int frame) {
    if (frame < 0 || frame >= maxFrames) return;
    
    currentFrame = frame;
}

int CAnimation::GetCurrentFrame() {
    return currentFrame;
}
