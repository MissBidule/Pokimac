//
//  CApp_OnLoop.cpp
//  Pokimac
//
//  Created by LouLiLou on 30/12/2021.
//

#include <iostream>
#include <stdio.h>
#include "CApp.h"

void CApp::OnLoop() {
    CFPS::FPSControl.OnLoop();
    
    if (inMap || inVictory || inDefeat) {
        
        //Lancement des routines de toutes les entites
        for (int i = 0; i < CEntity::EntityList.size(); i++) {
            if (!CEntity::EntityList[i]) continue;
            
            CEntity::EntityList[i]->OnLoop();
        }
        
        //On gere toutes les collisions provoquees
        //pendant la frame
        for (int i = 0; i < CEntityCol::EntityColList.size(); i++) {
            CEntity* entityA = CEntityCol::EntityColList[i].entityA;
            CEntity* entityB = CEntityCol::EntityColList[i].entityB;
            
            if (entityA == NULL || entityB == NULL) continue;
            
            //On renvoie vrai si on ''communique'' la
            //collision a l'entite touchee
            if (entityA->OnCollision(entityB)) {
                entityB->OnCollision(entityA);
            }
        }
        
        //On reinitialise les collisions
        CEntityCol::EntityColList.clear();
        
        //On regarde si un combat a ete declenche
        for (int i = 0; i < CPokimac::PKM_list.size(); i++) {
            if (CPokimac::PKM_list[i]->inCombat) {
                inFight = true;
                inMap = false;
                std::swap(CPokimac::PKM_list[i],CPokimac::PKM_list[0]);
                battle.Start(CPokimac::PKM_list[0]);
                player.moveLeft = false;
                player.moveRight = false;
                player.moveUp = false;
                player.moveDown = false;
                break;
            }
        }
    }
    else if (inFight) {
        //On retourne l'etat du combat actuel
        switch (battle.OnLoop()) {
            //On a gagne
            case 1:
                //On regarde si la partie est terminee
                if (++player.battle_won == menu.GetBattleGoal()) {
                    inFight = false;
                    inVictory = true;
                    clock.Start();
                }
                else {
                    inFight = false;
                    inMap = true;
                }
                break;
            //On a perdu
            case 2:
                inFight = false;
                inDefeat = true;
                break;
            //On a fuit
            case 3:
                inFight = false;
                inMap = true;
                player.X = 95;
                player.Y= 110;
                break;
            default:
                break;
        }
    }
    
    if (inVictory) {
        //Routine des feux d'artifices
        if (clock.Is_started()) {
            if (clock.Get_ticks() >= 500) {
                FW = !FW;
                int x = GenerAlea(WWIDTH - 376/2);
                int y = GenerAlea(WHEIGHT - 376/2);
                if (FW) {
                    VFX_FW1.Stop();
                    VFX_FW1.Start();
                    VFX_FW1.X = x;
                    VFX_FW1.Y = y;
                }
                else {
                    VFX_FW2.Stop();
                    VFX_FW2.Start();
                    VFX_FW2.X = x;
                    VFX_FW2.Y = y;
                }
                clock.Start();
            }
        }
        VFX_FW1.OnAnimate();
        VFX_FW2.OnAnimate();
    }
}
