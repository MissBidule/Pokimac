//
//  CEntity.cpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#include "CEntity.hpp"

std::vector<CEntity*> CEntity::EntityList;

bool CEntity::SortEntity(CEntity *entityA, CEntity *entityB) {
    return (entityA->Y < entityB->Y);
}

CEntity::CEntity() {
    Surf_Entity = NULL;
    
    X = Y = 0.0f;
    width = height = 0;
    
    moveLeft = moveRight = false;
    moveUp = moveDown = false;
    flags = ENTITY_FLAG_NONE;
    type = ENTITY_TYPE_GENERIC;
    dead = false;
    
    speedX = speedY = 0;
    accelX = accelY = 0;
    maxSpeedX = 4;
    maxSpeedY = 4;
    
    currentFrameCol = 0;
    currentFrameRow = 0;
    frameCol = 0;
    frameRow = 0;
    
    col_X = col_Y = 0;
    col_Width = col_Height = 0;
    
    canJump = false;
}

CEntity::~CEntity() {
    
}

bool CEntity::OnLoad(char* File, int width, int height, int maxFrames, bool transparency, int R, int G, int B) {
    if ((Surf_Entity = CSurface::OnLoad(File, transparency)) == NULL) {
        return false;
    }
    
    if (transparency) {
        CSurface::Transparent(Surf_Entity, R, G, B);
    }
    
    this->width = width;
    this->height = height;
    
    anim_Control.maxFrames = maxFrames;
    
    return true;
}

void CEntity::OnLoop() {
    //We're not moving
    if (moveLeft == false && moveRight == false)
            StopMoveX();
    
    //Si l'entite n'est pas soumis a la gravite on prend en compte son
    //deplacement en Y
    if ((flags ^ ENTITY_FLAG_GRAVITY) && (moveUp == false && moveDown == false))
        StopMoveY();
    
    if (moveLeft) {
        accelX = -0.5;
    }
    else if (moveRight) {
        accelX = 0.5;
    }
    
    //Si l'entite subit la gravite, elle tombera jusqu'à toucher le "sol"
    if (flags & ENTITY_FLAG_GRAVITY) {
        accelY = 0.75f;
    }
    else {
        if (moveUp) {
            accelY = -0.5f;
        }
        else if (moveDown) {
            accelY = 0.5f;
        }
    }
    
    //On avance en fonction des FPS du jeu
    speedX += accelX * CFPS::FPSControl.GetSpeedFactor();
    speedY += accelY * CFPS::FPSControl.GetSpeedFactor();
    
    //On limite la vitesse du joueur a maxSpeed
    if (speedX > maxSpeedX) speedX = maxSpeedX;
    if (speedX < -maxSpeedX) speedX = -maxSpeedX;
    if (speedY > maxSpeedY) speedY = maxSpeedY;
    if (speedY < -maxSpeedY) speedY = -maxSpeedY;
    
    OnAnimate();
    OnMove(speedX, speedY);
}

void CEntity::OnRender(SDL_Surface* Surf_Display) {
    if (Surf_Entity == NULL || Surf_Display == NULL) return;
    
    //Si la camera suit le joueur on dessine le joueur au centre
    //Le cas echeant, on calcule ses coordonnees
    CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY(), (frameCol + currentFrameCol) * width, ((frameRow + currentFrameRow) + anim_Control.GetCurrentFrame()) * height, width, height);
}

void CEntity::OnCleanup() {
    if (Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }
    
    Surf_Entity = NULL;
}

void CEntity::OnAnimate() {
    if (moveLeft) {
        currentFrameCol = 1;
    }
    else if (moveRight) {
        currentFrameCol = 0;
    }
    
    anim_Control.OnAnimate();
}

bool CEntity::OnCollision(CEntity *entity) {
    return false;
}

void CEntity::OnMove(float moveX, float moveY) {
    canJump = false;
    
    if (moveX == 0 && moveY == 0) return;
    
    double newX = 0;
    double newY = 0;
    
    moveX *= CFPS::FPSControl.GetSpeedFactor();
    moveY *= CFPS::FPSControl.GetSpeedFactor();
    
    if (moveX != 0) {
        if (moveX >=0) newX = CFPS::FPSControl.GetSpeedFactor();
        else newX = -CFPS::FPSControl.GetSpeedFactor();
    }
    
    if (moveY != 0) {
        if (moveY >=0) newY = CFPS::FPSControl.GetSpeedFactor();
        else newY = -CFPS::FPSControl.GetSpeedFactor();
    }
    
    //On deplace l'entite jusqu'a sa position souhaitee ou
    //jusqu'au prochain obstacle.
    while (true) {
        if (flags & ENTITY_FLAG_GHOST) {
            PosValid((int) (X + newX), (int) (Y + newY));
            
            X += newX;
            Y += newY;
        }
        else {
            if (PosValid((int) (X + newX), (int) (Y))) {
                X += newX;
            }
            else {
                speedX = 0;
            }
            
            if (PosValid((int) (X), (int) (Y + newY))) {
                Y += newY;
            }
            else {
                if ((moveY > 0) && (flags & ENTITY_FLAG_GRAVITY)) {
                    canJump = true;
                }
                speedY = 0;
            }
        }
        
        moveX += -newX;
        moveY += -newY;
        
        if (newX > 0 && moveX <= 0) newX = 0;
        if (newX < 0 && moveX >= 0) newX = 0;
        
        if (newY > 0 && moveY <= 0) newY = 0;
        if (newY < 0 && moveY >= 0) newY = 0;
        
        if (moveX == 0) newX = 0;
        if (moveY == 0) newY = 0;
        
        if (moveX == 0 && moveY ==0) break;
        if (newX == 0 && newY == 0) break;
    }
}

void CEntity::StopMoveX() {
    if (speedX > 0) {
        accelX = -1;
    }
    
    if (speedX < 0) {
        accelX = 1;
    }
    
    if (speedX < 2.0f && speedX > -2.0f) {
        accelX = 0;
        speedX = 0;
    }
}

void CEntity::StopMoveY() {
    if (speedY > 0) {
        accelY = -1;
    }
    
    if (speedY < 0) {
        accelY = 1;
    }
    
    if (speedY < 2.0f && speedY > -2.0f) {
        accelY = 0;
        speedY = 0;
    }
}

bool CEntity::Jump() {
    if (!canJump) return false;
    
    speedY = -maxSpeedY;
    
    return true;
}

bool CEntity::Collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;
    
    int tX = (int)X + col_X;
    int tY = (int)Y + col_Y;
    
    left1 = tX;
    left2 = oX;
    
    right1 = left1 + width - 1 - col_Width;
    right2 = oX + oW - 1;
    
    top1 = tY;
    top2 = oY;
    
    bottom1 = top1 + height - 1 - col_Height;
    bottom2 = oY + oH - 1;
    
    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;
    
    if (right1 < left2) return false;
    if (left1 > right2) return false;
    
    return true;
}

bool CEntity::PosValid(int newX, int newY) {
    bool Return = true;
    
    int startX = (newX + col_X) / TILE_SIZE;
    int startY = (newY + col_Y) / TILE_SIZE;
    
    int endX = ((newX + col_X) + width - col_Width - 1) / TILE_SIZE;
    int endY = ((newY + col_Y) + height - col_Height - 1) / TILE_SIZE;
    
    for (int iY = startY; iY <= endY; iY++) {
        for (int iX = startX; iX <= endX; iX++) {
            CTile* tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
            
            //On arrete les routines des pokimacs pour ne pas qu'ils courent
            //dans le vide
            if (!PosValidTile(tile)) {
                this->clock.Stop();
                Return = false;
            }
        }
    }
    
    if (flags ^ ENTITY_FLAG_MAPONLY) {
        for (int i = 0; i < EntityList.size(); i++) {
            //On arrete les routines des pokimacs pour ne pas qu'ils courent
            //dans le vide
            if (!PosValidEntity(EntityList[i], newX, newY)) {
                this->clock.Stop();
                Return = false;
            }
        }
    }
    
    return Return;
}

bool CEntity::PosValidTile(CTile *tile) {
    if (tile == NULL) return true;
    
    if (tile->typeID == TILE_TYPE_BLOCK) return false;
    //On confine les pokimacs a certaines zones et pas toute la map
    if ((this->type == ENTITY_TYPE_POKIMAC) && (tile->typeID == TILE_TYPE_ENEMY_BLOCK)) {
        return false;
    }
    
    return true;
}

bool CEntity::PosValidEntity(CEntity* entity, int newX, int newY) {
    if (((((this != entity) && (entity != NULL)) && !entity->dead) && entity->flags ^ ENTITY_FLAG_MAPONLY) && entity->Collides(newX + col_X, newY + col_Y, width - col_Width - 1, height - col_Height - 1)) {
        
        CEntityCol entityCol;
        entityCol.entityA = this;
        entityCol.entityB = entity;
        
        CEntityCol::EntityColList.push_back(entityCol);
        
        //Le joueur peut marcher a travers la maison
        if (entity->type == ENTITY_TYPE_HOUSE) return true;
        
        return false;
    }
    
    return true;
}
