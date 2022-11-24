//
//  CApp_OnInit.cpp
//  Pokimac
//
//  Created by LouLiLou on 30/12/2021.
//

#include <stdio.h>
#include "CApp.h"

bool CApp::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
        return false;
    
    SDL_WM_SetCaption("Pokimac", "Pokimac");
    if ((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    
    //Initialisation feux d'artifices
    char FW1_file[255];
    strcpy(FW1_file, CSurface::Abs_path);
    strcat(FW1_file, "img/FW1.png");
    if (!(VFX_FW1.OnLoad(FW1_file, 372, 368, 61, false))) {
        return false;
    }
    VFX_FW1.SetFrameRate(18);
    
    char FW2_file[255];
    strcpy(FW2_file, CSurface::Abs_path);
    strcat(FW2_file, "img/FW2.png");
    if (!(VFX_FW2.OnLoad(FW2_file, 368, 376, 58, false))) {
        return false;
    }
    VFX_FW2.SetFrameRate(18);
    
    //Initialisation pokimacs
    char file_name[255] = "map/PKM.info";
    if (CPokimac::PKMinit(file_name, 32, 32, 2, false) == false) {
        return false;
    }
    
    //On les ajoute a la liste des entites
    for (int i = 0; i < CPokimac::PKM_list.size(); i++) {
        if (!CPokimac::PKM_list[i]) continue;
        
        CEntity::EntityList.push_back(CPokimac::PKM_list[i]);
    }
    
    //Initialisation du joueur
    char img_name[255] = "img/hero.png";
    char img_Path[255];
    strcpy(img_Path, CSurface::Abs_path);
    strcat(img_Path, img_name);
    if ((player.OnLoad(img_Path, 32, 32, 4, false)) == false) {
        return false;
    }
    
    //Initialisation de la carte
    strcpy(file_name, "map/zone.area");
    if (CArea::AreaControl.OnLoad(file_name) == false) {
        return false;
    }
    
    //Initialisation de la maison
    strcpy(img_Path, CSurface::Abs_path);
    strcat(img_Path, "img/house.png");
    if (CHouse::OnLoad(img_Path, 96, 128, false) == false) {
        return false;
    }
    
    //Initialisation du menu
    strcpy(file_name, "map/menu.area");
    if (menu.OnLoad(file_name) == false) {
        return false;
    }
    
    //Initialisation des combats
    if (battle.OnLoad() == false) {
        return false;
    }
    
    //On accepte la repetition des touches
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    
    //Placement et ajout du joueur dans les entites
    player.X = 95;
    player.Y= 110;
    CEntity::EntityList.push_back(&player);
    
    return true;
}
