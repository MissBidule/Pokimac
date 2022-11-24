//
//  CPokimac.hpp
//  Pokimac
//
//  Created by LouLiLou on 06/01/2022.
//

#ifndef CPokimac_hpp
#define CPokimac_hpp

#include <SDL/SDL.h>
#include <stdio.h>
#include "CEntity.hpp"
#include "Define.h"

//Les types de pokimacs
enum {
    IMAGE = 0,
    MULTIMEDIA,
    AUDIOVISUEL,
    COMMUNICATION
};

class CPokimac : public CEntity {
    
public:
    static std::vector<CPokimac*> PKM_list;
    //Determmine le pokimac de depart
    static void SetStarter(int starter);
    
private:
    char* name;
    SDL_Surface* Surf_Boss;
    int specie;
    char* S_Attack;
    char* N_Attack;
    
public:
    int health;
    int state;
    //Permet de trouver quel pokimac nous avons rencontre
    bool inCombat;
    
public:
    CPokimac();
    
    bool OnLoad(char* File, int width, int height, int maxFrames, bool transparency, int R=0, int G=0, int B=0);
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
    void OnCleanup();
    void OnAnimate();
    bool OnCollision(CEntity* entity);
    
private:
    //Fait se déplacer les pokimacs de maniere autonome
    void Routine();
    bool OnRoutine();
    
public:
    static bool PKMinit(char* File, int width, int height, int maxFrames, bool transparency, int R=0, int G=0, int B=0);
    char* GetName();
    //Renvoie l'image du pokimac en combat
    SDL_Surface* GetBoss();
    int GetSpecie();
    char* GetATK(int n);
};


#endif /* CPokimac_hpp */
