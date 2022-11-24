//
//  CApp_OnCleanup.cpp
//  Pokimac
//
//  Created by LouLiLou on 30/12/2021.
//

#include <stdio.h>
#include "CApp.h"

void CApp::OnCleanup() {
    menu.OnCleanup();
    
    for (int i = 0; i < CEntity::EntityList.size(); i++) {
        if (!CEntity::EntityList[i]) continue;
        
        CEntity::EntityList[i]->OnCleanup();
    }
    
    for (int i = 0; i < CPokimac::PKM_list.size(); i++) {
        if (!CPokimac::PKM_list[i]) continue;
        
        CPokimac::PKM_list[i]->OnCleanup();
    }
    
    player.OnCleanup();
    
    CEntity::EntityList.clear();
    CPokimac::PKM_list.clear();
    
    CArea::AreaControl.OnCleanup();
    
    VFX_FW1.OnCleanup();
    VFX_FW2.OnCleanup();
    
    TTF_Quit();
    SDL_Quit();
}
