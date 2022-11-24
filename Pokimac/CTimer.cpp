//
//  CTimer.cpp
//  Pokimac
//
//  Created by LouLiLou on 04/01/2022.
//

#include "CTimer.hpp"

Timer::Timer() {
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::Start() {
    //On demarre le Timer
    started = true;
    
    //On enleve la pause du Timer
    paused = false;
    
    //On récupère le temps courant
    startTicks = SDL_GetTicks();
}

void Timer::Stop() {
    //On stoppe le Timer
    started = false;
    
    //On enleve la pause
    paused = false;
}

int Timer::Get_ticks() {
    //si le Timer est en marche
    if (started) {
        //si le Timer est en pause
        if (paused) {
            //On retourne le dernier temps enregistre
            return pausedTicks;
        }
        else {
            //On retourne le temps courant moins le temps quand il a demarre
            return SDL_GetTicks() - startTicks;
        }
    }
    
    //Si le Timer n'a pas demarre
    return 0;
}

void Timer::Pause() {
    //Si le timer est en marche et pas encore en pause
    if (started && !paused) {
        //On met en pause le Timer
        paused = true;
        
        //On calcule le temps qu'on a deja chronometre
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::Unpause() {
    //Si le Timer est en pause
    if (paused) {
        //On enleve la pause
        paused = false;
        
        //On remet a zero le startTicks
        startTicks = SDL_GetTicks() - pausedTicks;
        
        //On enleve le temps enregistre precedemment
        pausedTicks = 0;
    }
}

bool Timer::Is_started() {
    return started;
}

bool Timer::Is_paused() {
    return paused;
}
