//
//  CCamera.hpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#ifndef CCamera_hpp
#define CCamera_hpp

#include <stdio.h>
#include <SDL/SDL.h>
#include "Define.h"

//Type de suivi camera
enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera {
    
public:
    static CCamera CameraControl;
    
private:
    float X;
    float Y;
    
    //Coordonnees dependant de la cible suivie
    float* targetX;
    float* targetY;
    
public:
    int targetMode;
    
public:
    CCamera();
    
public:
    void OnMove(float moveX, float moveY);
    
public:
    float GetX();
    float GetY();
    
public:
    void SetPos(float X, float Y);
    void SetTarget(float* X, float* Y);
};

#endif /* CCamera_hpp */
