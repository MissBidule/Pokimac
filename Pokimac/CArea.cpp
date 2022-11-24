//
//  CArea.cpp
//  Pokimac
//
//  Created by LouLiLou on 01/01/2022.
//

#include "CArea.hpp"

CArea CArea::AreaControl;

CArea::CArea() {
    areaSize = 0;
}

bool CArea::OnLoad(char* File) {
    MapList.clear();
    
    char area_file[strlen(CSurface::Abs_path) + strlen(File)];
    strcpy(area_file, CSurface::Abs_path);
    strcat(area_file, File);
    
    FILE* FileHandle = fopen(area_file, "r");
    
    if (FileHandle == NULL) {
        return false;
    }
    
    char tilesetPath[255];
    char tilesetFile[255];
    strcpy(tilesetFile, CSurface::Abs_path);
    char decoPath[255];
    char decoFile[255];
    strcpy(decoFile, CSurface::Abs_path);
    
    fscanf(FileHandle, "%s %s\n", tilesetPath, decoPath);
    
    strcat(tilesetFile, tilesetPath);
    strcat(decoFile, decoPath);
    
    if (!(Surf_Tileset = CSurface::OnLoad(tilesetFile))) {
        fclose(FileHandle);
        return false;
    }
    
    if (!(Surf_Decoset = CSurface::OnLoad(decoFile))) {
        fclose(FileHandle);
        return false;
    }
    
    fscanf(FileHandle, "%d\n", &areaSize);
    
    for (int Y = 0; Y < areaSize; Y++) {
        for (int X = 0; X < areaSize; X++) {
            char mapPath[255];
            char mapFile[255];
            char decoPath[255];
            char decoFile[255];
            strcpy(mapFile, CSurface::Abs_path);
            strcpy(decoFile, CSurface::Abs_path);
            
            fscanf(FileHandle, "%s %s", mapPath, decoPath);
            
            strcat(mapFile, mapPath);
            strcat(decoFile, decoPath);
            
            CMap tempMap;
            if (!tempMap.OnLoad(mapFile, decoFile)) {
                fclose(FileHandle);
                return false;
            }
            
            tempMap.Surf_Tileset = Surf_Tileset;
            tempMap.Surf_Decoset = Surf_Decoset;
            
            MapList.push_back(tempMap);
        }
        fscanf(FileHandle, "\n");
    }
    fclose(FileHandle);
    
    return true;
    
}

void CArea::OnRender(SDL_Surface* Surf_Display, int cameraX, int cameraY) {
    int mapWidth = MAP_WIDTH * TILE_SIZE;
    int mapHeight = MAP_HEIGHT * TILE_SIZE;
    
    //Selon les reglages de la camera, on determine quelles cartes on dessinera
    //Ici on n'en a qu'une mais ça peut changer
    int firstID = -cameraX / mapWidth;
    firstID = firstID + ((-cameraY / mapHeight) * areaSize);
    
    for (int i = 0; i < 4; i++) {
        int ID = firstID + ((i / 2) * areaSize) + (i%2);
        
        if (ID < 0 || ID >= MapList.size()) continue;
        
        int X = ((ID % areaSize) * mapWidth) + cameraX;
        int Y = ((ID / areaSize) * mapHeight) + cameraY;
        
        MapList[ID].OnRender(Surf_Display, X, Y);
    }
}

void CArea::OnCleanup() {
    if (Surf_Tileset) {
        SDL_FreeSurface(Surf_Tileset);
    }
    
    MapList.clear();
}

CMap* CArea::GetMap(int X, int Y) {
    int mapWidth = MAP_WIDTH * TILE_SIZE;
    int mapHeight = MAP_HEIGHT * TILE_SIZE;
    
    int ID = X / mapWidth;
    ID = ID + ((Y / mapHeight) * areaSize);
    
    if (ID < 0 || ID >= MapList.size()) {
        return NULL;
    }
    
    return  &MapList[ID];
}

CTile* CArea::GetTile(int X, int Y) {
    int mapWidth = MAP_WIDTH * TILE_SIZE;
    int mapHeight = MAP_HEIGHT * TILE_SIZE;
    
    CMap* map = GetMap(X, Y);
    
    if (map == NULL) return NULL;
    
    X = X%mapWidth;
    Y = Y%mapHeight;
    
    return map->GetTile(X, Y);
}
