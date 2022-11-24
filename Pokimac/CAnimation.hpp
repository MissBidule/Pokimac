//
//  CAnimation.hpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#ifndef CAnimation_hpp
#define CAnimation_hpp

#include <stdio.h>
#include <SDL/SDL.h>

class CAnimation {
    
protected:
    int currentFrame;

private:
    int frameInc;
    
private:
    int frameRate;//Milliseconds
    long oldTime;
    
public:
    int maxFrames;
    bool oscillate;
    
public:
    CAnimation();
    //Calcul du changement de frame de l'animation
    void OnAnimate();
    
public:
    //Determine la vitesse de l'animation en millisecondes
    void SetFrameRate(int rate);
    void SetCurrentFrame(int frame);
    int GetCurrentFrame();

};

#endif /* CAnimation_hpp */
