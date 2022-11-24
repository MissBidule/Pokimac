//
//  CEntity.hpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#ifndef CEntity_hpp
#define CEntity_hpp

#include <stdio.h>
#include <vector>
#include "CArea.hpp"
#include "CAnimation.hpp"
#include "CCamera.hpp"
#include "CFPS.hpp"
#include "CSurface.hpp"
#include "CTimer.hpp"

//Permet de differencier les entites
enum {
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_POKIMAC,
    ENTITY_TYPE_HOUSE
};

//Pas utilise ici
enum {
    ENTITY_FLAG_NONE = 0,
    ENTITY_FLAG_GRAVITY = 0x00000001,
    ENTITY_FLAG_GHOST = 0x00000002,
    ENTITY_FLAG_MAPONLY = 0x00000004
};

class CEntity {

public:
    static std::vector<CEntity*> EntityList;
    
protected:
    CAnimation anim_Control;
    SDL_Surface* Surf_Entity;
    
public:
    float X;
    float Y;
    
    int width;
    int height;
    
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    
public:
    int type;
    
    bool dead;
    int flags;
    
protected:
    float speedX;
    float speedY;
    
    float accelX;
    float accelY;
    
public:
    float maxSpeedX;
    float maxSpeedY;
    
protected:
    int currentFrameCol;
    int currentFrameRow;
    int frameCol;
    int frameRow;
    
//Determine la zone de collision de l'entite
protected:
    int col_X;
    int col_Y;
    int col_Width;
    int col_Height;
    
protected:
    bool canJump;
    Timer clock;
    int end_clock;
    
public:
    CEntity();
    virtual ~CEntity();
    
public:
    virtual bool OnLoad(char* File, int width, int height, int maxFrames, bool transparency, int R=0, int G=0, int B=0);
    virtual void OnLoop();
    virtual void OnRender(SDL_Surface* Surf_Display);
    virtual void OnCleanup();
    virtual void OnAnimate();
    virtual bool OnCollision(CEntity* entity);
    
public:
    void OnMove(float moveX, float moveY);
    //On ralentit l'entite au lieu de l'arreter net
    void StopMoveX();
    void StopMoveY();
    //Pas utilise ici
    bool Jump();
    
public:
    //Regarde si la collision a lieu
    bool Collides(int oX, int oY, int oW, int oH);
    
private:
    bool PosValid(int newX, int newY);
    //Regarde si il y a un obstacle sur le chemin
    bool PosValidTile(CTile* tile);
    
protected:
    //Regarde si il y a une entite sur le chemin
    bool PosValidEntity(CEntity* entity, int newX, int newY);
    
public:
    //Tri les entites en y pour ne pas qu'elles se chevauchent
    static bool SortEntity (CEntity* entityA, CEntity* entityB);
};

class CEntityCol {
    
public:
    //Liste de collisions detectes
    static std::vector<CEntityCol> EntityColList;
    
public:
    CEntity* entityA;
    CEntity* entityB;
    
public:
    CEntityCol();
};
#endif /* CEntity_hpp */
