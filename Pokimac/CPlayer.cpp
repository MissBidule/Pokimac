//
//  CPlayer.cpp
//  Pokimac
//
//  Created by LouLiLou on 02/01/2022.
//

#include "CPlayer.hpp"

std::vector<CPokimac*> CPlayer::PKM_team;

CPlayer::CPlayer() {
    type = ENTITY_TYPE_PLAYER;
    col_Width = 10;
    col_X = 5;
    col_Height = 18;
    col_Y = 24;
    anim_Control.maxFrames = 4;
    battle_won = 0;
}

bool CPlayer::OnLoad(char *File, int Width, int Height, int MaxFrames, bool transparency, int R, int G, int B) {
    if (!CEntity::OnLoad(File, Width, Height, MaxFrames, transparency, R, G, B)) return false;
    
    return true;
}

void CPlayer::OnLoop() {
    CEntity::OnLoop();
    for (int i = 0; i < CEntity::EntityList.size(); i++) {
        if (CEntity::EntityList[i]->type == ENTITY_TYPE_HOUSE) {
            PosValidEntity(CEntity::EntityList[i], this->X, this->Y);
        }
    }
}

void CPlayer::OnRender(SDL_Surface *Surf_Display) {
    CEntity::OnRender(Surf_Display);
}

void CPlayer::OnCleanup() {
    CEntity::OnCleanup();
    for (int i = 0; i < PKM_team.size(); i++) {
        if (!PKM_team[i]) continue;
        
        PKM_team[i]->OnCleanup();
    }
    
    PKM_team.clear();
}

void CPlayer::OnAnimate() {
    if ((speedX != 0) || (speedY != 0)) {
        frameRow = 4;
    }
    else {
        frameRow = 0;
    }
    
    if (moveUp) {
        frameCol = 2;
    }
    else if (moveDown) {
        frameCol = 0;
    }
    
    CEntity::OnAnimate();
}

bool CPlayer::OnCollision(CEntity *entity) {
    //Soigne l'equipe du joueur des qu'on rentre dans la maison
    if (entity->type == ENTITY_TYPE_HOUSE) {
        for (int i = 0; i < PKM_team.size(); i++) {
            if (!PKM_team[i]) continue;
            
            PKM_team[i]->health = 100;
        }
        //Disparait
        frameCol+=8;
    }
    
    return true;
}
