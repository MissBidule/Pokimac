//
//  CPokimac.cpp
//  Pokimac
//
//  Created by LouLiLou on 06/01/2022.
//

#include <string>
#include "CPokimac.hpp"
#include "CPlayer.hpp"

std::vector<CPokimac*> CPokimac::PKM_list;

void CPokimac::SetStarter(int starter) {
    //Determine la position du pokimac qui n'a pas de coordonnees
    CEntity::EntityList[0]->X = CEntity::EntityList[starter]->X;
    CEntity::EntityList[0]->Y = CEntity::EntityList[starter]->Y;
    //Ajoute le starter dans l'equipe et le supprime de la liste d'entites
    std::swap(CEntity::EntityList[starter],CEntity::EntityList[0]);
    CPlayer::PKM_team.push_back((CPokimac *) CEntity::EntityList[0]);
    CEntity::EntityList.erase(CEntity::EntityList.begin());
}

CPokimac::CPokimac() {
    type = ENTITY_TYPE_POKIMAC;
    col_Width = 10;
    col_X = 5;
    col_Height = 18;
    col_Y = 24;
    anim_Control.maxFrames = 4;
    specie = 0;
    health = 100;
    end_clock = 0;
    Surf_Boss = NULL;
    name = nullptr;
    S_Attack = nullptr;
    N_Attack = nullptr;
    inCombat = false;
    
    //Initialiser le generateur lié a la fonction generAlea
    srand( (unsigned) time( NULL ) );
}

bool CPokimac::PKMinit(char* File, int width, int height, int maxFrames, bool transparency, int R, int G, int B) {
    
    PKM_list.clear();
    char PKM_file[strlen(CSurface::Abs_path) + 13];
    strcpy(PKM_file, CSurface::Abs_path);
    size_t length = strlen(PKM_file);
    
    char coord_file[strlen(CSurface::Abs_path) + strlen(File)];
    strcpy(coord_file, CSurface::Abs_path);
    strcat(coord_file, File);
    
    FILE* FileHandle = fopen(coord_file, "r");
    
    if (FileHandle == NULL) {
        return false;
    }
    
    int nbPKM;
    fscanf(FileHandle, "%d\n", &nbPKM);
    
    CPokimac* temp = nullptr;
    
    //Les pokimacs ont des noms de fichier generique, tres facile a recuperer
    for (int i = 1; i <= nbPKM; i++) {
        
        temp = new CPokimac;
        
        std::string i_char = std::to_string((int)i);
        char file[255] = "img/PKM_";
        strcat(file, i_char.c_str());
        strcat(file, ".png");
        PKM_file[length] = '\0';
        strcat(PKM_file, file);
        
        if (!temp->OnLoad(PKM_file, width, height, maxFrames, transparency)) {
            return false;
        }
        
        char boss_file[255] = "img/boss_";
        strcat(boss_file, i_char.c_str());
        strcat(boss_file, ".png");
        PKM_file[length] = '\0';
        strcat(PKM_file, boss_file);
        
        if ((temp->Surf_Boss = CSurface::OnLoad(PKM_file, transparency)) == NULL) {
            return false;
        }
        
        if (transparency) {
            CSurface::Transparent(temp->Surf_Boss, R, G, B);
        }
        
        char* temp_name = new char[255];
        char* temp_S_att = new char[255];
        char* temp_N_att = new char[255];
        fscanf(FileHandle, "%f %f %d %s %s %s\n", &temp->X, &temp->Y, &temp->specie, temp_name, temp_S_att, temp_N_att);
        
        temp->name = temp_name;
        temp->S_Attack = temp_S_att;
        temp->N_Attack = temp_N_att;
        
        PKM_list.push_back(temp);
    }
    
    fclose(FileHandle);
    
    return true;
    
}

bool CPokimac::OnLoad(char *File, int width, int height, int maxFrames, bool transparency, int R, int G, int B) {
    
    if (!CEntity::OnLoad(File, width, height, maxFrames, transparency, R, G, B)) return false;
    
    return true;
}

void CPokimac::OnLoop() {
    CEntity::OnLoop();
}

void CPokimac::OnRender(SDL_Surface *Surf_Display) {
    CEntity::OnRender(Surf_Display);
}

void CPokimac::OnCleanup() {
    if (Surf_Boss) {
        SDL_FreeSurface(Surf_Boss);
    }
    
    Surf_Boss = NULL;
    
    CEntity::OnCleanup();
}

bool CPokimac::OnRoutine() {
    return clock.Is_started();
}

void CPokimac::Routine() {
    if (OnRoutine()) {
        //Si on a atteint la fin de la dernier routine, on l'arrete
        if (clock.Get_ticks() < end_clock) {
            return;
        }
        clock.Stop();
    }
    if (GenerAlea(CFPS::FPSControl.GetFPS()) > 0.75f*CFPS::FPSControl.GetFPS()) {
        //La routine du pokimac va durer un temps aleatoire entre 0.5 et 1.5s
        end_clock = GenerAlea(1000)+500;
        int direction = GenerAlea(10);
        switch (direction) {
            case 1:
                moveUp = true;
                break;
                
            case 2:
                moveDown = true;
                break;
                
            case 3:
                moveRight = true;
                break;
                
            case 4:
                moveLeft = true;
                break;
                
            default:
                moveUp = false;
                moveDown = false;
                moveLeft = false;
                moveRight = false;
                break;
        }
        
        clock.Start();
    }
}

void CPokimac::OnAnimate() {
    Routine();
    
    if ((speedX != 0) || (speedY != 0)) {
        frameCol = 2;
    }
    else {
        frameCol = 0;
    }
    
    if (moveUp) {
        frameRow = 4;
    }
    else if (moveDown) {
        frameRow = 0;
    }
    
    CEntity::OnAnimate();
}

bool CPokimac::OnCollision(CEntity *entity) {
    if (entity->type == ENTITY_TYPE_PLAYER) {
        inCombat = true;
    }
    
    return true;
}

char* CPokimac::GetName() {
    return name;
}

SDL_Surface* CPokimac::GetBoss() {
    return Surf_Boss;
}

int CPokimac::GetSpecie() {
    return specie;
}

char* CPokimac::GetATK(int n) {
    if (n == 1)
        return S_Attack;
    if (n == 2)
        return N_Attack;
    return nullptr;
}
