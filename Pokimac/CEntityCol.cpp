//
//  CEntityCol.cpp
//  Pokimac
//
//  Created by LouLiLou on 02/01/2022.
//

#include <stdio.h>
#include "CEntity.hpp"

std::vector<CEntityCol> CEntityCol::EntityColList;

//EntityA a hurte EntityB
CEntityCol::CEntityCol() {
    entityA = NULL;
    entityB = NULL;
}
