//
//  CRand.cpp
//  Pokimac
//
//  Created by LouLiLou on 10/01/2022.
//

#include <stdio.h>
#include "Define.h"

int GenerAlea(int maxi, int mini) {
    int entierAleatoire;
    //Entier entre mini et maxi inclus
    entierAleatoire = mini + rand() % (maxi-mini+1);
    return entierAleatoire;
}
