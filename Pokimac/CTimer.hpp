//
//  CTimer.hpp
//  Pokimac
//
//  Created by LouLiLou on 04/01/2022.
//

#ifndef CTimer_hpp
#define CTimer_hpp

#include <stdio.h>
#include "SDL/SDL.h"

//Le Timer
class Timer {
    
private:
    //Le temps quand le tomer est lance
    int startTicks;
    //Le temps enregistre quand le Timer a ete mis en pause
    int pausedTicks;
    
    //Le statut du timer
    bool paused;
    bool started;
    
public:
    //Initialise les variables
    Timer();
    
public:
    //Les différentes actions du Timer
    void Start();
    void Stop();
    void Pause();
    void Unpause();
    
    //Récupère le nombre de millisecondes depuis le debut du timer ou
    //le temps enregistre depuis sa mise en pause
    int Get_ticks();
    
    //Fonctions de verifications du statut du Timer
    bool Is_started();
    bool Is_paused();
};

#endif /* CTimer_hpp */
