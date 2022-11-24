//
//  CApp.cpp
//  Pokimac
//
//  Created by LouLiLou on 15/01/2022.
//

#include <stdio.h>
#include "CApp.h"

CApp::CApp(char* path) {
    clock.Stop();
    FW = false;
    //On recupere le chemin absolu du repertoire courant
    char * temp = nullptr;
    temp = strrchr(path, '/');
    if (!temp) {
        temp = strrchr(path, '\\');
    }
    *++temp = '\0';
    CSurface::Abs_path = path;
    
    //Initialisation obligatoire de l'outil texte
    TTF_Init();
    Surf_Display = NULL;
    Running = true;
    inMenu = true;
    inMap = false;
    inFight = false;
    inVictory = false;
    inDefeat = false;
}

int CApp::OnExecute() {
    if (OnInit()==false)
        return -1;
    
    SDL_Event Event;
    
    //Fenetre active
    while (Running) {
        //File d'attente d'evenements
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
        
        //Coeur du jeu
        OnLoop();
        OnRender();
    }
    
    //Liberation de la memoire
    OnCleanup();
    
    return 0;
}
