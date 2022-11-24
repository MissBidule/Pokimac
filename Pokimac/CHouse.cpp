//
//  CHouse.cpp
//  Pokimac
//
//  Created by LouLiLou on 07/01/2022.
//

#include "CHouse.hpp"
#include "CPlayer.hpp"

CHouse::CHouse() {
    type = ENTITY_TYPE_HOUSE;
    X = 64;
    Y = 0;
    col_Width = 24;
    col_X = 12;
    col_Height = 5;
    col_Y = 4;
    anim_Control.maxFrames = 0;
}

bool CHouse::OnLoad(char *File, int width, int height, bool transparency, int R, int G, int B) {
    
    CHouse* temp = new CHouse;
    if (!temp->CEntity::OnLoad(File, width, height, temp->anim_Control.maxFrames, transparency, R, G, B)) return false;
    
    CEntity::EntityList.push_back(temp);
    return true;
}

void CHouse::OnLoop() {
    CEntity::OnLoop();
}

void CHouse::OnRender(SDL_Surface *Surf_Display) {
    CEntity::OnRender(Surf_Display);
}

void CHouse::OnCleanup() {
    CEntity::OnCleanup();
}

void CHouse::OnAnimate() {
    CEntity::OnAnimate();
    frameRow = 0;
    anim_Control.maxFrames = 0;
}

bool CHouse::OnCollision(CEntity *entity) {
    //Quand le joueur traverse la maison, celle-ci s'anime et se met a "dormir"
    frameRow = 1;
    anim_Control.maxFrames = 6;
    
    return true;
}
