//
//  CTile.hpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#ifndef CTile_hpp
#define CTile_hpp

#include <stdio.h>
#include "Define.h"

//Détermine qui peut se deplacer ou
enum {
    TILE_TYPE_NONE = 0,
    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK,
    TILE_TYPE_ENEMY_BLOCK
};

class CTile {
    
public:
    int tileID;
    int typeID;
    
public:
    CTile();
};

#endif /* CTile_hpp */
