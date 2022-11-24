//
//  CBattle.cpp
//  Pokimac
//
//  Created by LouLiLou on 10/01/2022.
//

#include "CBattle.hpp"
    
CBattle::CBattle() {
    Surf_BG = NULL;
    Surf_HB = NULL;

    opponent = nullptr;
    clock.Stop();
    pause = 0;
    turn = true;
    difficulty = 0;
    flee = false;
    lost = false;
    win = false;
    caught = false;
    suspense = false;
    
    strcpy(text1, "");
    strcpy(text2, "");
    strcpy(text3, "");
}

bool CBattle::OnLoad() {
    char surf_file[255];
    strcpy(surf_file, CSurface::Abs_path);
    size_t length = strlen(surf_file);
    strcat(surf_file, "img/Combat_BG.png");
    
    if (!(Surf_BG = CSurface::OnLoad(surf_file))) {
        return false;
    }
    
    //Chargement des VFX
    surf_file[length] = '\0';
    strcat(surf_file, "img/I_explosion.png");
    if (!(VFX_I.OnLoad(surf_file, 128, 128, 50, false))) {
        return false;
    }
    VFX_I.SetFrameRate(33);
        
    surf_file[length] = '\0';
    strcat(surf_file, "img/M_explosion.png");
    if (!(VFX_M.OnLoad(surf_file, 128, 128, 57, false))) {
        return false;
    }
    VFX_M.SetFrameRate(33);
        
    surf_file[length] = '\0';
    strcat(surf_file, "img/A_explosion.png");
    if (!(VFX_A.OnLoad(surf_file, 128, 128, 50, false))) {
        return false;
    }
    VFX_A.SetFrameRate(33);
    
    surf_file[length] = '\0';
    strcat(surf_file, "img/C_explosion.png");
    if (!(VFX_C.OnLoad(surf_file, 128, 128, 37, false))) {
        return false;
    }
    VFX_C.SetFrameRate(33);
    
    surf_file[length] = '\0';
    strcat(surf_file, "img/pokeball.png");
    if (!(VFX_PKBall.OnLoad(surf_file, 160, 160, 5, false))) {
        return false;
    }
        
    VFX_PKBall.SetFrameRate(1000);
        
    surf_file[length] = '\0';
    strcat(surf_file, "img/health_bar.png");
    if (!(Surf_HB = CSurface::OnLoad(surf_file))) {
        return false;
    }
 
    return true;
}

void CBattle::Start(CPokimac *PKM_opponent) {
    flee = false;
    lost = false;
    win = false;
    turn = true;
    caught = false;
    suspense = false;
    opponent = PKM_opponent;
    //On debloque le pokimac sinon on ne peut pas sortir du combat
    opponent->inCombat = false;
    pause = 4000;
    clock.Start();
    strcpy(text1, "Vous rencontrez ");
    strcat(text1, opponent->GetName());
    strcpy(text2, "Preparez-vous a l'affronter !");
    strcpy(text3, CPlayer::PKM_team[0]->GetName());
    strcat(text3, " en avant !");
}

void CBattle::OnEvent(int mouse_x, int mouse_y) {
    //Bloque les interactions quand du texte est affiche
    if (clock.Is_started()) {
        return;
    }
        
    if (((mouse_x > 190) && (mouse_x < 550)) && ((mouse_y > 555) && (mouse_y < 585))) {
        Attack(1);
    }
    if (((mouse_x > 190) && (mouse_x < 550)) && ((mouse_y > 595) && (mouse_y < 625))) {
        Attack(2);
    }
    if (((mouse_x > 610) && (mouse_x < 780)) && ((mouse_y > 555) && (mouse_y < 585))) {
        PKBall();
    }
    if (((mouse_x > 610) && (mouse_x < 780)) && ((mouse_y > 595) && (mouse_y < 625))) {
        Flee();
    }
    
    //Interactions Equipe
    if (((mouse_x > 20) && (mouse_x < 165)) && ((mouse_y > 50) && (mouse_y < 70))) {
        if (CPlayer::PKM_team.size() > 1) {
            Change_PKM(1);
        }
    }
    if (((mouse_x > 20) && (mouse_x < 165)) && ((mouse_y > 80) && (mouse_y < 100))) {
        if (CPlayer::PKM_team.size() > 2) {
            Change_PKM(2);
        }
    }
    if (((mouse_x > 20) && (mouse_x < 165)) && ((mouse_y > 110) && (mouse_y < 130))) {
        if (CPlayer::PKM_team.size() > 3) {
            Change_PKM(3);
        }
    }
    if (((mouse_x > 20) && (mouse_x < 165)) && ((mouse_y > 140) && (mouse_y < 160))) {
        if (CPlayer::PKM_team.size() > 4) {
            Change_PKM(4);
        }
    }
    if (((mouse_x > 20) && (mouse_x < 165)) && ((mouse_y > 170) && (mouse_y < 190))) {
        if (CPlayer::PKM_team.size() > 5) {
            Change_PKM(5);
        }
    }
}

int CBattle::OnLoop() {
    if (clock.Is_started()) {
        if (clock.Get_ticks() >= pause) {
            pause = 0;
            clock.Stop();
            //1 on a gagne le combat
            if ((win) || (caught)) {
                //Évite un doublon du combat
                opponent->dead = true;
                difficulty += 2;
                return 1;
            }
            //2 on a perdu le combat
            if (lost) {
                return 2;
            }
            //3 on a fuit le combat
            if (flee) {
                return 3;
            }
            if (!turn && !win) {
                OppAttack();
            }
            if (CPlayer::PKM_team[0]->health <= 0) {
                Lost();
            }
        }
    }
    
    VFX_I.OnAnimate();
    VFX_M.OnAnimate();
    VFX_A.OnAnimate();
    VFX_C.OnAnimate();
    VFX_PKBall.OnAnimate();
    //0 On est toujours en combat
    return 0;
}

void CBattle::OnRender(SDL_Surface* Surf_Display) {
    CSurface::OnDraw(Surf_Display, Surf_BG, 0, 0);
    
    OnRenderP1(Surf_Display);
    OnRenderP2(Surf_Display);
    
    if (clock.Is_started()) {
        DrawText(Surf_Display, text1, 35, 120, 510, 123, 125, 128);
        DrawText(Surf_Display, text2, 35, 120, 550, 123, 125, 128);
        DrawText(Surf_Display, text3, 35, 120, 590, 123, 125, 128);
    }
    
    VFX_I.OnRender(Surf_Display);
    VFX_M.OnRender(Surf_Display);
    VFX_A.OnRender(Surf_Display);
    VFX_C.OnRender(Surf_Display);
    VFX_PKBall.OnRender(Surf_Display);
}

void CBattle::OnRenderP1(SDL_Surface *Surf_Display) {
    if (!clock.Is_started()) {
        DrawText(Surf_Display,(char*) "Attaques", 30, 190, 510, 123, 125, 128);
        DrawText(Surf_Display, CPlayer::PKM_team[0]->GetATK(1), 35, 190, 550, 77, 80, 86);
        DrawText(Surf_Display, CPlayer::PKM_team[0]->GetATK(2), 35, 190, 590, 77, 80, 86);
        
        switch (CPlayer::PKM_team[0]->GetSpecie()) {
            case IMAGE:
                DrawText(Surf_Display,(char*) "I", 35, 150, 550, 48, 197, 49);
                break;
            case MULTIMEDIA:
                DrawText(Surf_Display,(char*) "M", 35, 150, 550, 10, 89, 153);
                break;
            case AUDIOVISUEL:
                DrawText(Surf_Display,(char*) "A", 35, 150, 550, 250, 20, 27);
                break;
            case COMMUNICATION:
                DrawText(Surf_Display,(char*) "C", 35, 150, 550, 251, 110, 33);
                break;
                
            default:
                break;
        }
        DrawText(Surf_Display,(char*) "C", 35, 150, 590, 251, 110, 33);
        
        DrawText(Surf_Display,(char*) "Actions", 30, 610, 510, 123, 125, 128);
        DrawText(Surf_Display,(char*) "Pokiball", 35, 610, 550, 77, 80, 86);
        DrawText(Surf_Display,(char*) "Fuir", 35, 610, 590, 77, 80, 86);
        
    }
    DrawText(Surf_Display, CPlayer::PKM_team[0]->GetName(), 20, 610, 350, 77, 80, 86);
    DrawText(Surf_Display,(char*) "PV :", 20, 610, 391, 77, 80, 86);
    
    //Determine l'etat actuel de la barre de vie
    int HB_state = CPlayer::PKM_team[0]->health==100?10:(int)(CPlayer::PKM_team[0]->health%100/10)+1;
    if (HB_state < 0 || CPlayer::PKM_team[0]->health < 0)
        HB_state = 0;
    CSurface::OnDraw(Surf_Display, Surf_HB, 670, 390, 0, 23*(HB_state), 128, 23);
    
    switch (CPlayer::PKM_team[0]->GetSpecie()) {
        case IMAGE:
            DrawText(Surf_Display,(char*) "I", 20, 610, 430, 48, 197, 49);
            break;
        case MULTIMEDIA:
            DrawText(Surf_Display,(char*) "M", 20, 610, 430, 10, 89, 153);
            break;
        case AUDIOVISUEL:
            DrawText(Surf_Display,(char*) "A", 20, 610, 430, 250, 20, 27);
            break;
        case COMMUNICATION:
            DrawText(Surf_Display,(char*) "C", 20, 610, 430, 251, 110, 33);
            break;
            
        default:
            break;
    }
    
    char current_PV[255];
    int health = (CPlayer::PKM_team[0]->health>=0?CPlayer::PKM_team[0]->health:0);
    std::string pv_Str = std::to_string(health);
    strcpy(current_PV, (char*) pv_Str.c_str());
    strcat(current_PV,(char*) "/100");
    DrawText(Surf_Display,current_PV, 20, 690, 430, 77, 80, 86);
    
    if (!lost)
        CSurface::OnDraw(Surf_Display, CPlayer::PKM_team[0]->GetBoss(), 200, 285);
    
    //Affichage des pokemon de l'equipe
    int Y[] = { 55, 85, 115, 145, 175 };
    for (int i = 1; i < CPlayer::PKM_team.size(); i++) {
        DrawText(Surf_Display, CPlayer::PKM_team[i]->GetName(), 16, 28, Y[i-1], 77, 80, 86);
    }
}

void CBattle::OnRenderP2(SDL_Surface *Surf_Display) {
    DrawText(Surf_Display, opponent->GetName(), 20, 255, 80, 77, 80, 86);
    DrawText(Surf_Display,(char*) "PV :", 20, 255, 106, 77, 80, 86);
    //Determine l'etat actuel de la barre de vie
    int HB_state = opponent->health==100?10:(int)(opponent->health%100/10)+1;
    if (HB_state < 0 || opponent->health < 0)
        HB_state = 0;
    CSurface::OnDraw(Surf_Display, Surf_HB, 315, 105, 0, 23*(HB_state), 128, 23);
    
    switch (opponent->GetSpecie()) {
        case IMAGE:
            DrawText(Surf_Display,(char*) "IMAGE", 18, 255, 135, 48, 197, 49);
            break;
        case MULTIMEDIA:
            DrawText(Surf_Display,(char*) "MULTIMEDIA", 18, 255, 135, 10, 89, 153);
            break;
        case AUDIOVISUEL:
            DrawText(Surf_Display,(char*) "AUDIOVISUEL", 18, 255, 135, 250, 20, 27);
            break;
        case COMMUNICATION:
            DrawText(Surf_Display,(char*) "COMMUNICATION", 18, 255, 135, 251, 110, 33);
            break;
            
        default:
            break;
    }
    
    //Fais reapparaitre le pokimac si on ne l'a pas attrape
    if (suspense && !caught) {
        if (VFX_PKBall.VFX_end()) suspense = false;
    }
    
    if (!suspense && !caught && !win)
        CSurface::OnDraw(Surf_Display, opponent->GetBoss(), 585, 60);
}

void CBattle::OnCleanup() {
    if (Surf_BG)
        SDL_FreeSurface(Surf_BG);
    if (Surf_HB)
        SDL_FreeSurface(Surf_HB);
    VFX_I.OnCleanup();
    VFX_M.OnCleanup();
    VFX_A.OnCleanup();
    VFX_C.OnCleanup();
    VFX_PKBall.OnCleanup();
    
    Surf_BG = NULL;
    Surf_HB = NULL;
}

void CBattle::Attack(int n) {
    int mini, maxi, puissance;
    float x;
    int type;
    mini=10;
    maxi=30;
    
    if (turn) {
        if (n == 1){
            x = ComparerTypes(CPlayer::PKM_team[0]->GetSpecie(), opponent->GetSpecie());
            type = CPlayer::PKM_team[0]->GetSpecie();
        }
        else {
            x = 1;
            type = COMMUNICATION;
        }
        
        puissance = GenerAlea(maxi, mini);
        opponent->health -= (int) (x * (float)puissance);
        
        char attack[255] = "Vous utilisez ";
        strcat(attack, CPlayer::PKM_team[0]->GetATK(n));
        strcpy(text1, attack);
        switch ((int)(x*10)) {
            case 5:
                strcpy(text2, "Ce n'est pas tres efficace...");
                break;
            case 20:
                strcpy(text2, "C'est super efficace !");
                break;
                
            default:
                strcpy(text2, "");
                break;
        }
        strcpy(text3, "");
            
        //Affiche le VFX lie a l'attaque lance
        switch (type) {
            case IMAGE:
                VFX_I.Stop();
                VFX_I.X = 685 - (128/2);
                VFX_I.Y = 160 - (128/2);
                VFX_I.Start();
                break;
            case MULTIMEDIA:
                VFX_M.Stop();
                VFX_M.X = 685 - (128/2);
                VFX_M.Y = 160 - (128/2);
                VFX_M.Start();
                break;
            case AUDIOVISUEL:
                VFX_A.Stop();
                VFX_A.X = 685 - (128/2);
                VFX_A.Y = 160 - (128/2);
                VFX_A.Start();
                break;
            case COMMUNICATION:
                VFX_C.Stop();
                VFX_C.X = 685 - (128/2);
                VFX_C.Y = 160 - (128/2);
                VFX_C.Start();
                break;
                
            default:
                break;
        }
        
        opponent->OnLoop();
        
        if (opponent->health <= 0) {
            Win();
            return;
        }
    }
    else {
        if (n == 1){
            x = ComparerTypes(opponent->GetSpecie(), CPlayer::PKM_team[0]->GetSpecie());
            type = opponent->GetSpecie();
        }
        else {
            x = 1;
            type = COMMUNICATION;
        }
        
        //En theorie ca augmente la difficulte au fur et a mesure des combats
        puissance = GenerAlea(maxi + difficulty, mini + difficulty);
        CPlayer::PKM_team[0]->health -= (int) (x * (float)puissance);
        
        char attack[255];
        strcpy(attack, opponent->GetName());
        strcat(attack, " utilise");
        strcpy(text1, attack);
        strcpy(text2, opponent->GetATK(n));
        
        switch ((int)(x*10)) {
            case 5:
                strcpy(text3, "Ce n'est pas tres efficace...");
                break;
            case 20:
                strcpy(text3, "C'est super efficace !");
                break;
                
            default:
                strcpy(text3, "");
                break;
        }
            
        //Affiche le VFX lie a l'attaque lance
        switch (type) {
            case IMAGE:
                VFX_I.Stop();
                VFX_I.X = 300 - (128/2);
                VFX_I.Y = 385 - (128/2);
                VFX_I.Start();
                break;
            case MULTIMEDIA:
                VFX_M.Stop();
                VFX_M.X = 300 - (128/2);
                VFX_M.Y = 385 - (128/2);
                VFX_M.Start();
                break;
            case AUDIOVISUEL:
                VFX_A.Stop();
                VFX_A.X = 300 - (128/2);
                VFX_A.Y = 385 - (128/2);
                VFX_A.Start();
                break;
            case COMMUNICATION:
                VFX_C.Stop();
                VFX_C.X = 300 - (128/2);
                VFX_C.Y = 385 - (128/2);
                VFX_C.Start();
                break;
                
            default:
                break;
        }
    }
    
    pause = 3000;
    turn = !turn;
    clock.Start();

}

void CBattle::Change_PKM(int n) {
    strcpy(text1, "Repose toi ");
    strcat(text1, CPlayer::PKM_team[0]->GetName());
    
    std::swap(CPlayer::PKM_team[n],CPlayer::PKM_team[0]);
    
    strcpy(text2, CPlayer::PKM_team[0]->GetName());
    strcat(text2, " en avant !");
    strcpy(text3, "");
    
    pause = 3000;
    turn = !turn;
    clock.Start();
}

//====================================================================
//DESCRIPTION: Capturer le PokiSauvage
//====================================================================
void CBattle::PKBall() {
    if (CPlayer::PKM_team.size() == 6) {
        strcpy(text1, "Votre equipe est deja complete.");
        strcpy(text2, "");
        strcpy(text3, "");
        
        pause = 3000;
        clock.Start();
        return;
    }
    
    suspense = true;
    
    int x;
    if (opponent->health >= 50)
    {
        strcpy(text1, "Vous n'avez pas reussi a");
        strcpy(text2, "capturer ");
        strcat(text2, opponent->GetName());
        strcpy(text3, "Il est encore trop puissant.");
    }
    else if (opponent->state >= 25)
    {
        x = GenerAlea(3);
        if (x==1)
        {
            strcpy(text1, "Bravo, vous avez reussi a");
            strcpy(text2, "capturer ");
            strcat(text2, opponent->GetName());
            strcpy(text3, "Pensez a vous soigner.");
            CPlayer::PKM_team.push_back(opponent);
            for (int i = 0; i < CEntity::EntityList.size(); i++) {
                if (CEntity::EntityList[i]->type == ENTITY_TYPE_POKIMAC)
                    if(strcmp(opponent->GetName(), ((CPokimac*) CEntity::EntityList[i])->GetName()) == 0) {
                        CEntity::EntityList.erase(CEntity::EntityList.begin()+i);
                        break;
                    }
            }
            caught = true;
        }
        else{

            strcpy(text1, "Vous n'avez pas reussi a");
            strcpy(text2, "capturer ");
            strcat(text2, opponent->GetName());
            strcpy(text3, "Il est encore trop puissant.");
        }
    }
    else
    {
        x=GenerAlea(5);
        if (x==3)
        {
            strcpy(text1, "Vous n'avez pas reussi a");
            strcpy(text2, "capturer ");
            strcat(text2, opponent->GetName());
            strcpy(text3, "Il est encore trop puissant.");
        }
        else{
           strcpy(text1, "Bravo, vous avez reussi a");
           strcpy(text2, "capturer ");
           strcat(text2, opponent->GetName());
           strcpy(text3, "Pensez a vous soigner.");
           CPlayer::PKM_team.push_back(opponent);
           for (int i = 0; i < CEntity::EntityList.size(); i++) {
               if (CEntity::EntityList[i]->type == ENTITY_TYPE_POKIMAC)
                   if(strcmp(opponent->GetName(), ((CPokimac*) CEntity::EntityList[i])->GetName()) == 0) {
                       CEntity::EntityList.erase(CEntity::EntityList.begin()+i);
                       break;
                   }
           }
           caught = true;
       }
    }
    
    //On affiche l'animation complete si on a reussi a attrape l'ennemi
    if (caught) {
        VFX_PKBall.maxFrames = 5;
        pause = 5000;
    }
    //On s'arrete une image avant si on a rate
    else {
        VFX_PKBall.maxFrames = 4;
        pause = 3000;
    }
    
    turn = !turn;
    clock.Start();
    
    VFX_PKBall.Stop();
    VFX_PKBall.X = 685 - (160/2);
    VFX_PKBall.Y = 160 - (160/2);
    VFX_PKBall.Start();
}

//====================================================================
//DESCRIPTION: Fuir le PokiSauvage
//====================================================================
void CBattle::Flee() {
    int x;
    x = GenerAlea(6);
    if (x == 1)
    {
        strcpy(text1, "Snif ! Vous n'avez pas reussi a");
        strcpy(text2, "vous enfuir. Vous aurez peut-etre");
        strcpy(text3, "plus de chance la prochaine fois.");
        
        flee = false;
    }
    else
    {
        strcpy(text1, "Bravo, vous avez furtivement");
        strcpy(text2, "pris la fuite sans que ");
        char fleeTxt[255] = "";
        strcat(fleeTxt, opponent->GetName());
        strcat(fleeTxt, " ne vous voie !!!");
        strcpy(text3, fleeTxt);
        
        flee = true;
    }
    turn = !turn;
    pause = 5000;
    clock.Start();
}

//====================================================================
//DESCRIPTION: Comparer les types
//====================================================================
 float CBattle::ComparerTypes(int attack, int defense)
 {
     //I > M > A > I | C n'a pas de faiblesse ni resistance
     if (attack == defense || attack == COMMUNICATION || defense == COMMUNICATION)
        return 1;
     else if (attack == MULTIMEDIA && defense == IMAGE)
            return 0.5;
    else if (attack == IMAGE && defense == AUDIOVISUEL)
            return 0.5;
    else if (attack == AUDIOVISUEL && defense == MULTIMEDIA)
            return 0.5;
            else
                return 2;
 }

//====================================================================
//DESCRIPTION: Fonction qui dit si le Pokisauvage fera une attaque speciale ou non
//====================================================================
void CBattle::OppAttack() {
    int x = GenerAlea(3);
    if (x==1)
        Attack(1);
    else
        Attack(2);
}

void CBattle::Lost() {
    strcpy(text1, "Votre Pokimac ");
    strcat(text1, CPlayer::PKM_team[0]->GetName());
    strcpy(text2, "est K.O.");
    CPlayer::PKM_team.erase(CPlayer::PKM_team.begin());
    
    //Si on a encore des pokimacs dans l'equipe, le combat continue
    if (CPlayer::PKM_team.size() > 0) {
        strcpy(text3, CPlayer::PKM_team[0]->GetName());
        strcat(text3, " sauve la mise !");
    }
    else {
        strcpy(text3, "Vous avez perdu...");
        
        //On retire le joueur des entites
        for (int i = 0; i < CEntity::EntityList.size(); i++) {
            if (CEntity::EntityList[i]->type == ENTITY_TYPE_PLAYER) {
                CEntity::EntityList.erase(CEntity::EntityList.begin()+i);
                break;
            }
        }
        
        lost = true;
    }
    
    pause = 5000;
    clock.Start();
}

void CBattle::Win() {
    win = true;
    strcpy(text1, "Le Pokimac ");
    strcat(text1, opponent->GetName());
    strcpy(text2, "est K.O.");
    strcpy(text3, "Vous sortez vainqueur.");
    
    for (int i = 0; i < CEntity::EntityList.size(); i++) {
        if (CEntity::EntityList[i]->type == ENTITY_TYPE_POKIMAC)
            if(strcmp(opponent->GetName(), ((CPokimac*) CEntity::EntityList[i])->GetName()) == 0) {
                CEntity::EntityList.erase(CEntity::EntityList.begin()+i);
                break;
            }
    }

    pause = 5000;
    clock.Start();
}
