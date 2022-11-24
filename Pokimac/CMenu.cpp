//
//  CMenu.cpp
//  Pokimac
//
//  Created by LouLiLou on 07/01/2022.
//

#include <string>
#include <vector>
#include <iostream>
#include "CMenu.hpp"

CMenu::CMenu() {
    screen_Battle_Goal = 1;
    battle_Goal = 1;

    options = true;
    rules = starter = false;
    
    Surf_Title = NULL;
    Surf_Options = NULL;
    Surf_Simple = NULL;
    
    max_Battle_Goal = 0;
    
    rules_nb = 1;
}

bool CMenu::OnLoad(char *File) {
    char menu_file[strlen(CSurface::Abs_path) + strlen(File)];
    strcpy(menu_file, CSurface::Abs_path);
    strcat(menu_file, File);
    
    FILE* FileHandle = fopen(menu_file, "r");
    
    if (FileHandle == NULL) {
        return false;
    }
    
    char menu1_Path[255];
    char menu1_File[255];
    strcpy(menu1_File, CSurface::Abs_path);
    char menu2_Path[255];
    char menu2_File[255];
    strcpy(menu2_File, CSurface::Abs_path);
    char menu3_Path[255];
    char menu3_File[255];
    strcpy(menu3_File, CSurface::Abs_path);
   
    fscanf(FileHandle, "%s %s %s", menu1_Path, menu2_Path, menu3_Path);
    
    strcat(menu1_File, menu1_Path);
    strcat(menu2_File, menu2_Path);
    strcat(menu3_File, menu3_Path);
    
    if (!(Surf_Title = CSurface::OnLoad(menu1_File))) {
        fclose(FileHandle);
        return false;
    }
    if (!(Surf_Options = CSurface::OnLoad(menu2_File))) {
        fclose(FileHandle);
        return false;
    }
    if (!(Surf_Simple = CSurface::OnLoad(menu3_File))) {
        fclose(FileHandle);
        return false;
    }
    
    fclose(FileHandle);
    
    max_Battle_Goal = (int) CPokimac::PKM_list.size();
    
    return true;
}

bool CMenu::OnEvent(int mouse_x, int mouse_y) {
    if (options) {
        if (((mouse_x > 660) && (mouse_x < 680)) && ((mouse_y > 230) && (mouse_y < 255))) {
            SetBattleGoal(false);
        }
        if (((mouse_x > 755) && (mouse_x < 775)) && ((mouse_y > 230) && (mouse_y < 255))) {
            SetBattleGoal(true);
        }
        
        if (((mouse_x > 760) && (mouse_x < 895)) && ((mouse_y > 340) && (mouse_y < 380))) {
            options = false;
            rules = true;
        }
        
        if (((mouse_x > 540) && (mouse_x < 675)) && ((mouse_y > 340) && (mouse_y < 380))) {
            options = false;
            starter = true;
            
            battle_Goal = screen_Battle_Goal;
        }
    }
    else {
        if (((mouse_x > 480) && (mouse_x < 730)) && ((mouse_y > 10) && (mouse_y < 30))) {
            starter = false;
            rules = false;
            options = true;
            rules_nb = 1;
        }
    }
        
    if (rules) {
        if (rules_nb != 1) {
            if (((mouse_x > 480) && (mouse_x < 655)) && ((mouse_y > 610) && (mouse_y < 630))) {
                rules_nb--;
            }
        }
        if (rules_nb !=3) {
            if (((mouse_x > 820) && (mouse_x < 950)) && ((mouse_y > 610) && (mouse_y < 630))) {
                rules_nb++;
            }
        }
    }
    
    if (starter) {
        if (((mouse_x > 480) && (mouse_x < 680)) && ((mouse_y > 140) && (mouse_y < 340))) {
            CPokimac::SetStarter(0);
            starter = false;
            options = true;
            
            return true;
        }
        if (((mouse_x > 730) && (mouse_x < 930)) && ((mouse_y > 140) && (mouse_y < 340))) {
            CPokimac::SetStarter(1);
            starter = false;
            options = true;
            
            return true;
        }
        if (((mouse_x > 480) && (mouse_x < 680)) && ((mouse_y > 395) && (mouse_y < 620))) {
            CPokimac::SetStarter(2);
            starter = false;
            options = true;
            
            return true;
        }
        if (((mouse_x > 730) && (mouse_x < 930)) && ((mouse_y > 410) && (mouse_y < 620))) {
            CPokimac::SetStarter(3);
            starter = false;
            options = true;
            
            return true;
        }
    }
    
    return false;
}

void CMenu::OnRender(SDL_Surface *Surf_Display) {
    CSurface::OnDraw(Surf_Display, Surf_Title, 0, 0);
    
    OnRenderMenu(Surf_Display);
    
    if (options) {
        OnRenderOptions(Surf_Display);
    }
    else {
        CSurface::OnDraw(Surf_Display, Surf_Simple, 480, 0);
        
        char back[] = "Retour au menu";
        DrawText(Surf_Display, back, 25, 485, 14, 122, 136, 152);
        DrawText(Surf_Display, back, 25, 478, 8, 112, 96, 80, 2);
        DrawText(Surf_Display, back, 25, 480, 10, 242, 255, 152);
        
        if (rules) {
            OnRenderRules(Surf_Display);
        }
        else if (starter) {
            OnRenderStarter(Surf_Display);
        }
    }
}

void CMenu::OnRenderMenu(SDL_Surface *Surf_Display) {
    char gameTitle[] = "POKIMAC";
    DrawText(Surf_Display, gameTitle, 80, 35, 90, 104, 136, 152);
    DrawText(Surf_Display, gameTitle, 80, 20, 75, 112, 96, 80, 5);
    DrawText(Surf_Display, gameTitle, 80, 25, 80, 242, 255, 152);
    
    char subhead[] = "version crous";
    DrawText(Surf_Display, subhead, 20, 148, 200, 123, 50, 56, 2);
    DrawText(Surf_Display, subhead, 20, 150, 202, 255, 255, 255);
    
    char year[] = " 2022 LOULILOU's CREATIVE GAMES";
    year[0] = '\xa9';
    DrawText(Surf_Display, year, 10, 120, 598, 0, 0, 0, 2);
    DrawText(Surf_Display, year, 10, 122, 600, 255, 255, 255);
}

void CMenu::OnRenderOptions(SDL_Surface *Surf_Display) {
    CSurface::OnDraw(Surf_Display, Surf_Options, 480, 0);
    
    DrawText(Surf_Display,(char*) "Bienvenue", 37, 606, 87, 77, 80, 86);
    
    DrawText(Surf_Display,(char*) "JOUER", 28, 553, 347, 77, 80, 86);
    
    DrawText(Surf_Display,(char*) "REGLES", 25, 769, 350, 77, 80, 86);
    
    char text1[] = "Choisis le nombre";
    char text2[] = "de Pokimacs que";
    char text3[] = "tu veux affronter";
    DrawText(Surf_Display, text1, 17, 708, 430, 77, 80, 86);
    DrawText(Surf_Display, text2, 17, 714, 450, 77, 80, 86);
    DrawText(Surf_Display, text3, 17, 708, 470, 77, 80, 86);
    
    char nb_text[255];
    std::string nb_Str = std::to_string(screen_Battle_Goal);
    char const *nb = nb_Str.c_str();
    if (screen_Battle_Goal < 10) {
        strcpy(nb_text, "0");
        strcat(nb_text, nb);
    }
    else strcpy(nb_text, nb);
    
    DrawText(Surf_Display,(char*) "Affronter", 30, 635, 190, 77, 80, 86);
    DrawText(Surf_Display, nb_text, 30, 702, 230, 77, 80, 86);
    DrawText(Surf_Display,(char*) "Pokimacs", 30, 640, 270, 77, 80, 86);
}

void CMenu::OnRenderRules(SDL_Surface *Surf_Display) {
    if (rules_nb!=1) {
        char previous[] = "PRECEDENT";
        DrawText(Surf_Display, previous, 25, 485, 614, 122, 136, 152);
        DrawText(Surf_Display, previous, 25, 478, 608, 112, 96, 80, 2);
        DrawText(Surf_Display, previous, 25, 480, 610, 242, 255, 152);
    }
    if (rules_nb!=3) {
        char next[] = "SUIVANT";
        DrawText(Surf_Display, next, 25, 824, 614, 122, 136, 152);
        DrawText(Surf_Display, next, 25, 818, 608, 112, 96, 80, 2);
        DrawText(Surf_Display, next, 25, 820, 610, 242, 255, 152);
    }
    
    if (rules_nb == 1) {
        char rules1[] = "POKIMAC se joue a la souris et au";
        char rules2[] = "clavier.";
        char rules3[] = "Utilise la souris dans le menu et";
        char rules4[] = "pendant les combats.";
        char rules5[] = "Utilise les fleches de ton clavier";
        char rules6[] = "pour te deplacer sur la carte et";
        char rules7[] = "rencontrer des Pokimacs.";
        char rules8[] = "Tu peux choisir combien de Pokimacs";
        char rules9[] = "tu souhaites affronter dans le menu.";
        char rules10[] = "Attraper ou tuer le Pokimac adverse";
        char rules11[] = "est considere comme une victoire.";
        DrawText(Surf_Display, rules1, 18, 480, 150, 33, 68, 162);
        DrawText(Surf_Display, rules2, 18, 480, 170, 33, 68, 162);
        DrawText(Surf_Display, rules3, 18, 480, 210, 33, 68, 162);
        DrawText(Surf_Display, rules4, 18, 480, 230, 33, 68, 162);
        DrawText(Surf_Display, rules5, 18, 480, 270, 33, 68, 162);
        DrawText(Surf_Display, rules6, 18, 480, 290, 33, 68, 162);
        DrawText(Surf_Display, rules7, 18, 480, 310, 33, 68, 162);
        DrawText(Surf_Display, rules8, 18, 480, 350, 33, 68, 162);
        DrawText(Surf_Display, rules9, 18, 480, 370, 33, 68, 162);
        DrawText(Surf_Display, rules10, 18, 480, 410, 33, 68, 162);
        DrawText(Surf_Display, rules11, 18, 480, 430, 33, 68, 162);
    }
    else if (rules_nb == 2) {
        char rules1[] = "Ton aventure commence dans ta";
        char rules2[] = "maison, reviens ici pour soigner ton";
        char rules3[] = "equipe.";
        char rules4[] = "Si tu touches un Pokimac, un combat";
        char rules5[] = "commence.";
        char rules6[] = "En combat, tu peux choisir une attaque,";
        char rules7[] = "lancer une Pokiball, fuir, ou changer";
        char rules8[] = "de Pokimac.";
        char rules9[] = "Tu peux attraper les Pokimacs avec";
        char rules10[] = "tes Pokiballs. Mais avant, tu dois avoir";
        char rules11[] = "affaiblis ces derniers.";
        char rules12[] = "Tu as le droit a 6 Pokimacs dans ton";
        char rules13[] = "equipe, apres cela tu ne pourras pas";
        char rules14[] = "attraper davantage de Pokimacs.";
        DrawText(Surf_Display, rules1, 18, 480, 150, 33, 68, 162);
        DrawText(Surf_Display, rules2, 18, 480, 170, 33, 68, 162);
        DrawText(Surf_Display, rules3, 18, 480, 190, 33, 68, 162);
        DrawText(Surf_Display, rules4, 18, 480, 230, 33, 68, 162);
        DrawText(Surf_Display, rules5, 18, 480, 250, 33, 68, 162);
        DrawText(Surf_Display, rules6, 18, 480, 290, 33, 68, 162);
        DrawText(Surf_Display, rules7, 18, 480, 310, 33, 68, 162);
        DrawText(Surf_Display, rules8, 18, 480, 330, 33, 68, 162);
        DrawText(Surf_Display, rules9, 18, 480, 370, 33, 68, 162);
        DrawText(Surf_Display, rules10, 18, 480, 390, 33, 68, 162);
        DrawText(Surf_Display, rules11, 18, 480, 410, 33, 68, 162);
        DrawText(Surf_Display, rules12, 18, 480, 450, 33, 68, 162);
        DrawText(Surf_Display, rules13, 18, 480, 470, 33, 68, 162);
        DrawText(Surf_Display, rules14, 18, 480, 490, 33, 68, 162);
    }
    else {
        char rules1[] = "Si toute ton equipe meurt, c'est";
        char rules2[] = "GAME OVER.";
        char rules3[] = "Chaque Pokimac a un type qui est plus";
        char rules4[] = "fort qu'un autre.";
        char rules5[] = "Sauf COMMUNICATION qui n'est pas";
        char rules6[] = "plus fort qu'un autre type.";
        char rules7[] = "Les types sont indiques durant le";
        char rules8[] = "combat.";
        char arrow[] = "->";
        char image[] = "IMAGE";
        char multi[] = "MULTIMEDIA";
        char audio[] = "AUDIOVISUEL";
        char comm[] = "COMMUNICATION";
        DrawText(Surf_Display, rules1, 18, 480, 150, 33, 68, 162);
        DrawText(Surf_Display, rules2, 18, 480, 170, 33, 68, 162);
        DrawText(Surf_Display, rules3, 18, 480, 210, 33, 68, 162);
        DrawText(Surf_Display, rules4, 18, 480, 230, 33, 68, 162);
        DrawText(Surf_Display, rules5, 18, 480, 270, 33, 68, 162);
        DrawText(Surf_Display, rules6, 18, 480, 290, 33, 68, 162);
        DrawText(Surf_Display, rules7, 18, 480, 330, 33, 68, 162);
        DrawText(Surf_Display, rules8, 18, 480, 350, 33, 68, 162);
        
        DrawText(Surf_Display, image, 18, 582, 390, 48, 197, 49);
        DrawText(Surf_Display, arrow, 18, 680, 390, 0, 0, 0);
        DrawText(Surf_Display, multi, 18, 730, 390, 10, 89, 153);
        
        DrawText(Surf_Display, multi, 18, 515, 430, 10, 89, 153);
        DrawText(Surf_Display, arrow, 18, 680, 430, 0, 0, 0);
        DrawText(Surf_Display, audio, 18, 730, 430, 250, 20, 27);
        
        DrawText(Surf_Display, audio, 18, 500, 470, 250, 20, 27);
        DrawText(Surf_Display, arrow, 18, 680, 470, 0, 0, 0);
        DrawText(Surf_Display, image, 18, 730, 470, 48, 197, 49);
        
        DrawText(Surf_Display, comm, 18, 600, 510, 251, 110, 33);
    }
}

void CMenu::OnRenderStarter(SDL_Surface *Surf_Display) {
    char title1[] = "Choisis ton Pokimac starter";
    DrawText(Surf_Display, title1, 20, 540, 50, 0, 0, 0);
    char title2[] = "pour commencer ton aventure !";
    DrawText(Surf_Display, title2, 20, 520, 75, 0, 0, 0);
    
    CSurface::OnDraw(Surf_Display, CPokimac::PKM_list[0]->GetBoss(), 480, 140);
    CSurface::OnDraw(Surf_Display, CPokimac::PKM_list[1]->GetBoss(), 730, 140);
    CSurface::OnDraw(Surf_Display, CPokimac::PKM_list[2]->GetBoss(), 480, 395);
    CSurface::OnDraw(Surf_Display, CPokimac::PKM_list[3]->GetBoss(), 730, 395);
    
    DrawText(Surf_Display, CPokimac::PKM_list[0]->GetName(), 18, 480, 115, 77, 80, 86);
    DrawText(Surf_Display, CPokimac::PKM_list[1]->GetName(), 18, 780, 115, 77, 80, 86);
    DrawText(Surf_Display, CPokimac::PKM_list[2]->GetName(), 18, 480, 605, 77, 80, 86);
    DrawText(Surf_Display, CPokimac::PKM_list[3]->GetName(), 18, 780, 605, 77, 80, 86);
    
    int X[4] = { 660, 730, 660, 730 };
    int Y[4] = { 115, 115, 605, 605 };
    
    for (int i = 0; i < 4; i++) {
        switch (CPokimac::PKM_list[i]->GetSpecie()) {
            case 0:
                DrawText(Surf_Display, (char*) "I", 18, X[i]-2, Y[i]-2, 77, 80, 86, 2);
                DrawText(Surf_Display, (char*) "I", 18, X[i], Y[i], 48, 197, 49);
                break;
            case 1:
                DrawText(Surf_Display, (char*) "M", 18, X[i]-2, Y[i]-2, 77, 80, 86, 2);
                DrawText(Surf_Display, (char*) "M", 18, X[i], Y[i], 10, 89, 153);
                break;
            case 2:
                DrawText(Surf_Display, (char*) "A", 18, X[i]-2, Y[i]-2, 77, 80, 86, 2);
                DrawText(Surf_Display, (char*) "A", 18, X[i], Y[i], 250, 20, 27);
                break;
            case 3:
                DrawText(Surf_Display, (char*) "C", 18, X[i]-2, Y[i]-2, 77, 80, 86, 2);
                DrawText(Surf_Display, (char*) "C", 18, X[i], Y[i], 251, 110, 33);
                break;
                
            default:
                break;
        }
    }
    
}

void CMenu::OnCleanup() {
    if (Surf_Title) {
        SDL_FreeSurface(Surf_Title);
    }
    if (Surf_Simple) {
        SDL_FreeSurface(Surf_Simple);
    }
    if (Surf_Options) {
        SDL_FreeSurface(Surf_Options);
    }
}

int CMenu::GetBattleGoal() {
    return battle_Goal;
}

void CMenu::SetBattleGoal(bool increase) {
    if (increase) {
        if (screen_Battle_Goal < max_Battle_Goal-1) {
            screen_Battle_Goal++;
        }
    }
    else {
        if (screen_Battle_Goal > 1) {
            screen_Battle_Goal--;
        }
    }
}

