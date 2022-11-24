//
//  CCamera.cpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#include "CCamera.hpp"

CCamera CCamera::CameraControl;

CCamera::CCamera() {
    X = Y = 0;
    
    targetX = targetY = NULL;
    
    targetMode = TARGET_MODE_NORMAL;
}

void CCamera::OnMove(float moveX, float moveY) {
    X += moveX;
    Y += moveY;
}

float CCamera::GetX() {
    if (targetX != NULL) {
        if (targetMode == TARGET_MODE_CENTER) {
            return *targetX - (WWIDTH / 2);
        }
        
        return *targetX;
    }
    
    return X;
}

float CCamera::GetY() {
    if (targetY != NULL) {
        if (targetMode == TARGET_MODE_CENTER) {
            return *targetY - (WHEIGHT / 2);
        }
        
        return *targetY;
    }
    
    return Y;
}

void CCamera::SetPos(float X, float Y) {
    this->X = X;
    this->Y = Y;
}

void CCamera::SetTarget(float *X, float *Y) {
    targetX = X;
    targetY = Y;
}
