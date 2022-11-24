//
//  CSurface.cpp
//  Pokimac
//
//  Created by LouLiLou on 30/12/2021.
//

#include "CSurface.hpp"

//Necessaire si l'executable ne cherche pas les fichiers
//au bon endroit
char* CSurface::Abs_path = nullptr;

CSurface::CSurface(){
}

SDL_Surface* CSurface::OnLoad(char* File, bool transparency){
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;
    
    if ((Surf_Temp = IMG_Load(File))==NULL) {
        return NULL;
    }
    
    //Si transparency est à vrai, on demande de retirer
    //une couleur precise avec un fond transparent mais
    //cela ne marche pas avec SDL_DisplayFormatAlpha
    if (!transparency) {
        Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
        SDL_FreeSurface(Surf_Temp);
    }
    else {
        Surf_Return = SDL_DisplayFormat(Surf_Temp);
        SDL_FreeSurface(Surf_Temp);
    }
    
    return Surf_Return;
    
}

//On dessine toute une image à un endroit precis
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
    if ((Surf_Dest == NULL) || (Surf_Src == NULL)) {
        return false;
    }
    
    SDL_Rect DestR;
    
    DestR.x = X;
    DestR.y = Y;
    
    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);
    
    return true;
}

//On ne dessine qu'une portion de l'image
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
    if ((Surf_Dest == NULL) || (Surf_Src == NULL)) {
        return false;
    }
    
    SDL_Rect DestR;
    
    DestR.x = X;
    DestR.y = Y;
    
    SDL_Rect SrcR;
    
    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;
    
    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

    return true;
}

//Rend tranparent une certaine couleur
bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) {
    if (Surf_Dest == NULL) {
        return false;
    }
    
    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));
    
    return true;
}
