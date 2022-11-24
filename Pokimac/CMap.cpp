//
//  CMap.cpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#include "CMap.hpp"

CMap::CMap() {
    Surf_Tileset = NULL;
}

bool CMap::OnLoad(char *FileMap, char* FileDeco) {
    TileList.clear();
    
    FILE* FileHandle = fopen(FileMap, "r");
    
    if (FileHandle == NULL) {
        return false;
    }
    
    for (int Y = 0; Y < MAP_HEIGHT; Y++) {
        for (int X = 0; X < MAP_WIDTH; X++) {
            CTile tempTile;
            
            fscanf(FileHandle, "%d:%d", &tempTile.tileID, &tempTile.typeID);
            
            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }
    
    fclose(FileHandle);
    
    FileHandle = fopen(FileDeco, "r");
    
    if (FileHandle == NULL) {
        return false;
    }
    
    for (int Y = 0; Y < MAP_HEIGHT; Y++) {
        for (int X = 0; X < MAP_WIDTH; X++) {
            CTile tempTile;
            
            fscanf(FileHandle, "%d", &tempTile.tileID);
            
            tempTile.typeID = 1;
            DecoList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }
    
    fclose(FileHandle);
    
    return true;
}

void CMap::OnRender(SDL_Surface *Surf_Display, int mapX, int mapY) {
    if (Surf_Tileset == NULL) return;
    
    int tileSetWidth = Surf_Tileset->w / TILE_SIZE;
    //int TileSetHeight = Surf_Tileset->h / TILE_SIZE;
    
    int decoSetWidth = Surf_Decoset->w / TILE_SIZE;
    //int DecoSetHeight = Surf_Decoset->h / TILE_SIZE;
    
    int ID = 0;
    
    for (int Y = 0; Y < MAP_HEIGHT; Y++) {
        for (int X = 0; X < MAP_WIDTH; X++) {
            if (TileList[ID].typeID == TILE_TYPE_NONE) {
                ID++;
                continue;
            }
            
            int tx = mapX + (X * TILE_SIZE);
            int ty = mapY + (Y * TILE_SIZE);
            
            int tilesetX = (TileList[ID].tileID % tileSetWidth) * TILE_SIZE;
            int tilesetY = (TileList[ID].tileID / tileSetWidth) * TILE_SIZE;
            
            CSurface::OnDraw(Surf_Display, Surf_Tileset, tx, ty, tilesetX, tilesetY, TILE_SIZE, TILE_SIZE);
            
            if (DecoList[ID].typeID == TILE_TYPE_NONE) {
                ID++;
                continue;
            }

            int decosetX = (DecoList[ID].tileID % decoSetWidth) * TILE_SIZE;
            int decosetY = (DecoList[ID].tileID / decoSetWidth) * TILE_SIZE;
            
            CSurface::OnDraw(Surf_Display, Surf_Decoset, tx, ty, decosetX, decosetY, TILE_SIZE, TILE_SIZE);
            
            ID++;
        }
    }
}

CTile* CMap::GetTile(int X, int Y) {
    int ID = 0;
    
    ID = X / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (Y / TILE_SIZE));
    
    if (ID < 0 || ID >= TileList.size()) return NULL;
    
    return &TileList[ID];
}
