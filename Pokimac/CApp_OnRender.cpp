//
//  CApp_OnRender.cpp
//  Pokimac
//
//  Created by LouLiLou on 30/12/2021.
//

#include <stdio.h>
#include "CApp.h"

void CApp::OnRender() {
    
    if (inMenu) {
        menu.OnRender(Surf_Display);
    }
    
    if (inFight) {
        battle.OnRender(Surf_Display);
    }
    
    if (inMap || inVictory || inDefeat) {
        CArea::AreaControl.OnRender(Surf_Display, 0, 0);
        
        //On trie les entites en 'y' pour qu'elles ne
        //se chevauchent pas
        std::sort(CEntity::EntityList.begin(), CEntity::EntityList.end(), CEntity::SortEntity);
        for (int i = 0; i < CEntity::EntityList.size(); i++) {
            if (!CEntity::EntityList[i]) continue;
            
            CEntity::EntityList[i]->OnRender(Surf_Display);
        }
    }
    
    if (inVictory) {
        VFX_FW1.OnRender(Surf_Display);
        VFX_FW2.OnRender(Surf_Display);
        
        DrawText(Surf_Display, (char*) "VICTOIRE", 130, 85, 235, 200, 0, 0, 5);
        DrawText(Surf_Display, (char*) "VICTOIRE", 130, 90, 240, 255, 195, 0);
    }
    else if (inDefeat) {
        DrawText(Surf_Display, (char*) "GAME OVER", 130, 20, 235, 200, 0, 0, 5);
        DrawText(Surf_Display, (char*) "GAME OVER", 130, 25, 240, 0, 0, 0);
    }

    SDL_Flip(Surf_Display);
}
