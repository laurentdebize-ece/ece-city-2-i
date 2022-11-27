#include "Affichage.h"

void drawLine(Ligne lignes, int x, int y) {

    for (int i = 0; i < NB_CASESY; ++i) {
        for (int j = 0; j < NB_CASES; ++j) {
            al_draw_rectangle(X_DEPART + (j*LARGEUR_CASE), Y_DEPART + (i * HAUTEUR_CASE),(X_DEPART + LARGEUR_CASE) + (j * LARGEUR_CASE),(Y_DEPART + HAUTEUR_CASE) + (i * HAUTEUR_CASE), al_map_rgb(0, 0, 0), 1);
        }
    }
}

bool CasesViableAutourDesHabitation(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int i, int j){
    bool HabViable = FALSE;
    for (int k = i-1; k <= i+NB_Cases_Place_ConstruX+1; ++k) {
        for (int l = j - NB_Cases_Place_ConstruY - 1; l <= j + 1; ++l) {
            if(tabPlateau[k][l].routeOccupe == 1){

                HabViable = TRUE;
            }
        }
    }

    return HabViable;
}

bool CasesViableAutourDesHabitationBis(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int i, int j){
    bool HabViable = FALSE;
    for (int k = i-1; k <= i+NB_Cases_Place_ConstruX+1; ++k) {
        for (int l = j - NB_Cases_Place_ConstruY - 1; l <= j + 1; ++l) {
            if(tabPlateau[k][l].routeOccupe == 1){
                if(tabPlateau[k][l].viable == 1){
                    HabViable = TRUE;
                }
            }
        }
    }

    return HabViable;
}

bool incendie(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int k){
    int chance1sur2 = rand()%2;
    bool Incendie = FALSE;
    if(chance1sur2 == 1){
        //Incendie = TRUE;
        Incendie = FALSE;
    }
    return Incendie;
}

void drawFondEtCases(ALLEGRO_BITMAP* NuageFond, ALLEGRO_BITMAP* MapFond){
    al_draw_bitmap(NuageFond, 0,0,0);
    al_draw_bitmap(MapFond, X_DEPART, Y_DEPART,0);
}

void dessinerRoutes(Cases tabPlateau [NB_CASES][NB_CASES], ALLEGRO_BITMAP* RouteDroite, ALLEGRO_BITMAP* RouteDroite2, ALLEGRO_BITMAP* Tournant, ALLEGRO_BITMAP* Tournant2, ALLEGRO_BITMAP* Tournant3, ALLEGRO_BITMAP* Tournant4, ALLEGRO_BITMAP* DoubleTournant, ALLEGRO_BITMAP* DoubleTournant2, ALLEGRO_BITMAP* DoubleTournant3, ALLEGRO_BITMAP* DoubleTournant4, ALLEGRO_BITMAP* Croisement, ALLEGRO_TIMER* timer, ALLEGRO_FONT* police, ALLEGRO_FONT* policePetite, bool affichageRoute, bool affichageEau, bool affichageElec){
    for (int i = 0; i < NB_CASES; ++i) {
        for (int j = 0; j < NB_CASES; ++j) {
            /// Rouges les cases occupe
            if(tabPlateau[i][j].occupe == 1){
                //al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 + LARGEUR_CASE, tabPlateau[i][j].y1+HAUTEUR_CASE,al_map_rgb(255,0,0));
            }
            if(tabPlateau[i][j].routeOccupe == 1 && affichageRoute == TRUE){
                if((al_get_timer_count(timer)) <= (tabPlateau[i][j].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1)){
                    al_draw_text(policePetite, al_map_rgb(255,0,0), tabPlateau[i][j].x1 - 15, tabPlateau[i][j].y1 - 20, 0, "-10");
                }
                /// Si pas de route autour de la route normale
                if((tabPlateau[i+1][j].routeOccupe == 0 && tabPlateau[i-1][j].routeOccupe == 0) || (tabPlateau[i][j+1].routeOccupe == 0 && tabPlateau[i][j-1].routeOccupe == 0)){
                    al_draw_bitmap(RouteDroite, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }
                /// Route normale choix vers le haut/bas ou sur le cote
                if(tabPlateau[i+1][j].routeOccupe == 1 || tabPlateau[i-1][j].routeOccupe == 1){
                    al_draw_bitmap(RouteDroite2, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }
                if(tabPlateau[i][j+1].routeOccupe == 1 || tabPlateau[i][j-1].routeOccupe == 1){
                    al_draw_bitmap(RouteDroite, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,
                                                 al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,
                                                 al_map_rgba(255,0,0,150));
                    }
                }
                /// Choix du bon tournant
                if(tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(Tournant, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }


                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(Tournant2, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }


                if(tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1){
                    al_draw_bitmap(Tournant3, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }


                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1){
                    al_draw_bitmap(Tournant4, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }
                /// choix du bouble tournant
                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(DoubleTournant3, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }


                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1 && tabPlateau[i][j-1].routeOccupe == 1){
                    al_draw_bitmap(DoubleTournant4, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }


                if(tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(DoubleTournant, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }


                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(DoubleTournant2, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }
                /// Gros croisement
                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1){
                    al_draw_bitmap(Croisement, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                    if(tabPlateau[i][j].viable == 1) {
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(0,255,0, 150));
                    }else{
                        al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 +2, tabPlateau[i][j].y1+2,al_map_rgba(255,0,0,150));
                    }
                }
            }
            if(tabPlateau[i][j].routeOccupe == 1 && affichageEau == TRUE){
                al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 + LARGEUR_CASE, tabPlateau[i][j].y1+HAUTEUR_CASE,al_map_rgb(0,120,255));
                al_draw_text(police, al_map_rgb(0,0,0), 100, 120, 0, "Niveau -1");
            }
            if (tabPlateau[i][j].routeOccupe == 1 && affichageElec == TRUE){
                al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 + LARGEUR_CASE, tabPlateau[i][j].y1+HAUTEUR_CASE,al_map_rgb(255,255,0));
                al_draw_text(police, al_map_rgb(0,0,0), 100, 220, 0, "Niveau -2");
            }
        }
    }
}

void drawMaison(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int nbNombreBatPose, bool affichageEau, bool affichageElec, ALLEGRO_TIMER* timer, ALLEGRO_FONT* policePetite,ALLEGRO_BITMAP* TerrainVague, ALLEGRO_BITMAP* Maison1, ALLEGRO_BITMAP* Maison2, ALLEGRO_BITMAP* Maison3, ALLEGRO_BITMAP* Maison4, ALLEGRO_BITMAP* Ruine, ALLEGRO_BITMAP* Immeuble, ALLEGRO_BITMAP* GratteCiel, ALLEGRO_BITMAP* Cabane, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* Habitant, ALLEGRO_BITMAP* CentralElectrique, ALLEGRO_BITMAP* ChateauEau, ALLEGRO_BITMAP* CroixRouge){
    for (int k = 0; k < nbNombreBatPose; k++) {
        if (CasesViableAutourDesHabitation(tabPlateau, tabBit, tabBit[k].i, tabBit[k].j) == 1) {
            if (tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 0) {
                al_draw_bitmap(TerrainVague, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                               tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                //printf(" au clic : %d\n", tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1);
                //printf("  timer : %d\n", al_get_timer_count(timer));
                if ((al_get_timer_count(timer)) <= (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1)) {
                    al_draw_text(policePetite, al_map_rgb(255, 0, 0), tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 60, 0, "-1000");
                    al_draw_bitmap(PieceMonnaie, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                                   tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 70, 0);
                }
            }
            if (tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 1) {
                //Incendie = incendie(tabPlateau, tabBit, k);
                if (tabBit[k].incendie == FALSE) {
                    if (CasesViableAutourDesHabitationBis(tabPlateau, tabBit, tabBit[k].i, tabBit[k].j) == 0) {
                        al_draw_bitmap(Cabane, tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 10,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                        al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                                 al_map_rgba(255, 0, 0, 30));
                    } else {
                        al_draw_bitmap(Cabane, tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 10,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                    }

                    if ((al_get_timer_count(timer)) <=
                        (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1)) {
                        al_draw_text(policePetite, al_map_rgb(0, 255, 0),
                                     tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 20,
                                     tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 60, 0, "+10");
                        al_draw_bitmap(Habitant, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 70, 0);
                    }
                } else {
                    al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                             al_map_rgb(255, 0, 0));
                    if ((al_get_timer_count(timer)) <=
                        (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1)) {
                        al_draw_text(policePetite, al_map_rgb(0, 255, 0),
                                     tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 20,
                                     tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 60, 0, "Inencendie");
                    }
                    tabBit[k].changementBatBloque = 1;
                }
            }
            if (tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 2) {
                if (tabBit[k].chance1sur4 == 0) {
                    if (CasesViableAutourDesHabitationBis(tabPlateau, tabBit, tabBit[k].i, tabBit[k].j) == 0) {
                        al_draw_bitmap(Maison1, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                        al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                                 al_map_rgba(255, 0, 0, 30));
                    } else {
                        al_draw_bitmap(Maison1, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                    }
                } else if (tabBit[k].chance1sur4 == 1) {
                    if (CasesViableAutourDesHabitationBis(tabPlateau, tabBit, tabBit[k].i, tabBit[k].j) == 0) {
                        al_draw_bitmap(Maison2, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                        al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                                 al_map_rgba(255, 0, 0, 30));
                    } else {
                        al_draw_bitmap(Maison2, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                    }
                } else if (tabBit[k].chance1sur4 == 2) {
                    if (CasesViableAutourDesHabitationBis(tabPlateau, tabBit, tabBit[k].i, tabBit[k].j) == 0) {
                        al_draw_bitmap(Maison3, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                        al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                                 al_map_rgba(255, 0, 0, 30));
                    } else {
                        al_draw_bitmap(Maison3, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                    }
                } else if (tabBit[k].chance1sur4 == 3) {
                    if (CasesViableAutourDesHabitationBis(tabPlateau, tabBit, tabBit[k].i, tabBit[k].j) == 0) {
                        al_draw_bitmap(Maison4, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                        al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                                 al_map_rgba(255, 0, 0, 30));
                    } else {
                        al_draw_bitmap(Maison4, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                    }
                }
                if ((al_get_timer_count(timer)) <= (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1)) {
                    al_draw_text(policePetite, al_map_rgb(0, 255, 0), tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 20,
                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 60, 0, "+50");
                    al_draw_bitmap(Habitant, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                                   tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 70, 0);
                }
            }
            if (tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 3) {
                if (CasesViableAutourDesHabitationBis(tabPlateau, tabBit, tabBit[k].i, tabBit[k].j) == 0) {
                    al_draw_bitmap(Immeuble, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                   tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                    al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                             al_map_rgba(255, 0, 0, 30));
                } else {
                    al_draw_bitmap(Immeuble, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                   tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE, 0);
                }


                if ((al_get_timer_count(timer)) <= (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1)) {
                    al_draw_text(policePetite, al_map_rgb(0, 255, 0), tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 10,
                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 60, 0, "+100");
                    al_draw_bitmap(Habitant, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                                   tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 70, 0);
                }
            }
            if (tabBit[k].batPose == 1 && tabBit[k].changemetnBat >= 4) {
                if (CasesViableAutourDesHabitationBis(tabPlateau, tabBit, tabBit[k].i, tabBit[k].j) == 0) {
                    al_draw_bitmap(GratteCiel, tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 2,
                                   tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE - 6, 0);
                    al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                             al_map_rgba(255, 0, 0, 30));
                } else {
                    al_draw_bitmap(GratteCiel, tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 2,
                                   tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE - 6, 0);
                }


                if (affichageElec == TRUE || affichageEau == TRUE) {
                    al_draw_filled_rectangle(tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 + HAUTEUR_CASE,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 3 * LARGEUR_CASE,
                                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 2 * HAUTEUR_CASE,
                                             al_map_rgba(0, 0, 0, 150));
                }
                if ((al_get_timer_count(timer)) <= (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1) &&
                    tabBit[k].changemetnBat == 4) {
                    al_draw_text(policePetite, al_map_rgb(0, 255, 0), tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                                 tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 90, 0, "+1000");

                    al_draw_bitmap(Habitant, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                                   tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 100, 0);
                }
            }

        } else {
            for (int l = 0; l < nbNombreBatPose; l++) {
                if (tabBit[l].batPose == 1 && tabBit[l].changemetnBat == 0) {
                    al_draw_bitmap(TerrainVague, tabPlateau[tabBit[l].i][tabBit[l].j].x1,
                                   tabPlateau[tabBit[l].i][tabBit[l].j].y1 - 2 * HAUTEUR_CASE, 0);
                    al_draw_bitmap(CroixRouge, tabPlateau[tabBit[l].i][tabBit[l].j].x1 + LARGEUR_CASE,
                                   tabPlateau[tabBit[l].i][tabBit[l].j].y1 - HAUTEUR_CASE, 0);
                }
            }
        }
        drawUsineEau(tabPlateau, tabBit, timer, policePetite, PieceMonnaie, ChateauEau, k);
        drawUsineElec(tabPlateau, tabBit, timer, policePetite, PieceMonnaie, CentralElectrique, k);
        /*if (tabBit[k].UsineEauPose == 1) {
            al_draw_bitmap(ChateauEau, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                           tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE, 0);
            if ((al_get_timer_count(timer)) <= (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1) &&
                (tabBit[k].changemetnBat == 0)) {
                al_draw_text(policePetite, al_map_rgb(255, 0, 0), tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 90, 0, "-5000");
                al_draw_bitmap(PieceMonnaie, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                               tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 100, 0);
            }
        }
        if (tabBit[k].UsineElecPose == 1) {
            al_draw_bitmap(CentralElectrique, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                           tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE, 0);
            if ((al_get_timer_count(timer)) <= (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1) &&
                (tabBit[k].changemetnBat == 0)) {
                al_draw_text(policePetite, al_map_rgb(255, 0, 0), tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                             tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 90, 0, "-5000");
                al_draw_bitmap(PieceMonnaie, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                               tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 100, 0);
            }
        }*/
    }
}

void drawUsineEau(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT],  ALLEGRO_TIMER* timer, ALLEGRO_FONT* policePetite, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* ChateauEau, int k){
    if (tabBit[k].UsineEauPose == 1) {
        al_draw_bitmap(ChateauEau, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE, 0);
        if ((al_get_timer_count(timer)) <= (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1) &&
            (tabBit[k].changemetnBat == 0)) {
            al_draw_text(policePetite, al_map_rgb(255, 0, 0), tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                         tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 90, 0, "-5000");
            al_draw_bitmap(PieceMonnaie, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                           tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 100, 0);
        }
    }
}

void drawUsineElec(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT],  ALLEGRO_TIMER* timer, ALLEGRO_FONT* policePetite, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* CentralElectrique, int k){

    if (tabBit[k].UsineElecPose == 1) {
        al_draw_bitmap(CentralElectrique, tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                       tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE, 0);
        if ((al_get_timer_count(timer)) <= (tabBit[k].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1) &&
            (tabBit[k].changemetnBat == 0)) {
            al_draw_text(policePetite, al_map_rgb(255, 0, 0), tabPlateau[tabBit[k].i][tabBit[k].j].x1,
                         tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 90, 0, "-5000");
            al_draw_bitmap(PieceMonnaie, tabPlateau[tabBit[k].i][tabBit[k].j].x1 + 70,
                           tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 100, 0);
        }
    }
}



void BoiteAOutilEtTimer(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int sourisDessusX, int sourisDessusY, int nbNombreBatPose, int valeurSourisX, int valeurSourisY, int minutes,int* nbHabTotal,int* ecefloos ,bool clickCarreBleu,bool choixUsineElec, bool choixUsineEau, ALLEGRO_TIMER* timer, ALLEGRO_TIMER* timer1sec, ALLEGRO_FONT* police, ALLEGRO_BITMAP* TerrainVague, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* Habitant, ALLEGRO_BITMAP* CentralElectrique, ALLEGRO_BITMAP* ChateauEau){
    //al_clear_to_color(al_map_rgb(255,255,255));

    ALLEGRO_BITMAP* eau = NULL;
    ALLEGRO_BITMAP* eclair = NULL;
    ALLEGRO_BITMAP* construction = NULL;
    ALLEGRO_BITMAP* route2 = NULL;
    ALLEGRO_BITMAP* caserne = NULL;
    ALLEGRO_BITMAP* barreoutil = NULL;
    ALLEGRO_BITMAP* chateau = NULL;


    /// tracer les carrés rouges quand on cliques dessus (tracer les routes)

    /// dessiner les carrés noir, le plateau
    /// Draw la bitmap de la maison
    
    
    
    al_init_image_addon();
    eau = al_load_bitmap("../bitmap/eau.png");
    eclair = al_load_bitmap("../bitmap/eclair.png");
    construction = al_load_bitmap("../bitmap/construction.png");
    route2 = al_load_bitmap("../bitmap/route2.png");
    caserne = al_load_bitmap("../bitmap/caserne.png");
    barreoutil = al_load_bitmap("../bitmap/barreoutilimage.png");
    chateau = al_load_bitmap("../bitmap/iconechateau.png");

    /// draw le rectangle bleu pour avoir le bat en main
    //al_draw_filled_rectangle(20,500, 70, 550, al_map_rgb(20,50,180));
    ///carre quitter mode bat
    //al_draw_filled_rectangle(20,700, 70, 750, al_map_rgb(150,150,0));
    /// carre rouge pour les routes
    //al_draw_filled_rectangle(20,400, 70, 450, al_map_rgb(100,0,0));
    /// Niveau -1
    //al_draw_filled_rectangle(20,100, 70, 150, al_map_rgb(0,0,255));
    /// Niveau -2
    //al_draw_filled_rectangle(20,200, 70, 250, al_map_rgb(255,255,0));
    /// carre vert Pour eau
    //al_draw_filled_rectangle(20,570, 70, 620, al_map_rgb(0,255,0));
    /// carre noir ppour elec
    //al_draw_filled_rectangle(20,630, 70, 680, al_map_rgb(0,0,0));
    
    
    al_draw_bitmap(barreoutil, -2, 0, 0);
    al_draw_bitmap(route2, 25, 400, 0);
    al_draw_bitmap(eau, 23, 100, 0);
    al_draw_bitmap(eclair, 25, 200, 0);
    al_draw_bitmap(caserne, 24, 650, 0);
    al_draw_bitmap(construction, 22, 500, 0);
    al_draw_bitmap(chateau, 25, 575, 0);
    al_flip_display();

    //encadrement bare à outil icone construction
    al_draw_rectangle(20, 500, 80, 550, al_map_rgb(0, 0, 0), 7);
    //encadrelent barre à outil icone route2
    al_draw_rectangle(20, 400, 80, 450, al_map_rgb(0, 0, 0), 7);
    //encadrement bare à outil icone eau
    al_draw_rectangle(20, 100, 80, 150, al_map_rgb(0, 0, 0), 7);
    //encadrement bare à outil icone eclair
    al_draw_rectangle(20, 200, 80, 250, al_map_rgb(0, 0, 0), 7);
    //encadrement bare à outil icone chateau
    al_draw_rectangle(20, 575, 80, 625, al_map_rgb(0, 0, 0), 7);
    //encadrement bare à outil icone caserne
    al_draw_rectangle(20, 650, 80, 700, al_map_rgb(0, 0, 0), 7);



    /// pour avoir le bat en main selon la pose de la souris
    if(clickCarreBleu == TRUE && valeurSourisX > X_DEPART && valeurSourisX < X_DEPART + 45*LARGEUR_CASE && valeurSourisY> Y_DEPART && valeurSourisY < Y_DEPART + 35*HAUTEUR_CASE ) {
        al_draw_bitmap(TerrainVague, tabPlateau[sourisDessusX][sourisDessusY].x1, tabPlateau[sourisDessusX][sourisDessusY].y1 - 2 * HAUTEUR_CASE, 0);
    }
    /// pour avoir l'usine eau en main selon la pose de la souris
    if(choixUsineEau == TRUE && valeurSourisX > X_DEPART && valeurSourisX < X_DEPART + 45*LARGEUR_CASE && valeurSourisY> Y_DEPART && valeurSourisY < Y_DEPART + 35*HAUTEUR_CASE ) {
        al_draw_bitmap(ChateauEau, tabPlateau[sourisDessusX][sourisDessusY].x1, tabPlateau[sourisDessusX][sourisDessusY].y1 - 3 * HAUTEUR_CASE, 0);
    }
    /// pour avoir l'usine elec en main selon la pose de la souris
    if(choixUsineElec == TRUE && valeurSourisX > X_DEPART && valeurSourisX < X_DEPART + 45*LARGEUR_CASE && valeurSourisY> Y_DEPART && valeurSourisY < Y_DEPART + 35*HAUTEUR_CASE ) {
        al_draw_bitmap(CentralElectrique, tabPlateau[sourisDessusX][sourisDessusY].x1, tabPlateau[sourisDessusX][sourisDessusY].y1 - 3 * HAUTEUR_CASE, 0);
    }
    /// tracer les carrés verts quand on est sur la map
    al_draw_filled_rectangle(tabPlateau[sourisDessusX][sourisDessusY].x1, tabPlateau[sourisDessusX][sourisDessusY].y1, tabPlateau[sourisDessusX][sourisDessusY].x1 + LARGEUR_CASE, tabPlateau[sourisDessusX][sourisDessusY].y1+HAUTEUR_CASE,al_map_rgb(0,255,0));
    al_draw_rectangle(tabPlateau[sourisDessusX][sourisDessusY].x1, tabPlateau[sourisDessusX][sourisDessusY].y1, tabPlateau[sourisDessusX][sourisDessusY].x1 + LARGEUR_CASE, tabPlateau[sourisDessusX][sourisDessusY].y1+HAUTEUR_CASE,al_map_rgb(0,0,0), 1);


    /// draw les differnet timer
    /// timer 15sec

    for (int i = 0; i < nbNombreBatPose; ++i) {
        if(CasesViableAutourDesHabitation(tabPlateau, tabBit, tabBit[i].i, tabBit[i].j) == 1 && tabBit[i].batPose == 1) {
            if ((al_get_timer_count(timer)) <= (tabBit[i].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION2 + 1) && (al_get_timer_count(timer)) >= (tabBit[i].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION2 - 1)) {
                tabBit[i].valeurCompteurAuClic = al_get_timer_count(timer);
                tabBit[i].timerPasAfficherSansArret = al_get_timer_count(timer);
                if (tabBit[i].changemetnBat <= 4) {
                    if (tabBit[i].changementBatBloque == 0) {
                        tabBit[i].changemetnBat = tabBit[i].changemetnBat + 1;
                    }
                    if (tabBit[i].changemetnBat == 1 && tabBit[i].changementBatBloque == 0) {
                        tabBit[i].incendie = incendie(tabPlateau, tabBit, i);
                    }
                    if (tabBit[i].changementBatBloque == 0) {
                        *nbHabTotal = *nbHabTotal + tabBit[tabBit[i].changemetnBat].nbHabitant;
                    }
                }
                tabBit[i].empecherDeRentrerPlusieursFoisDAnsLaBoucle = 1;
            }
        }
    }

    ///timer jeu complet
    al_draw_textf(police, al_map_rgb(0, 0, 0), 220, 20, 0, "%d s", al_get_timer_count(timer1sec));
    al_draw_textf(police, al_map_rgb(0, 0, 0), 180, 20, 0, "%d: ", minutes);
    al_draw_bitmap(PieceMonnaie, 1200, 10, 0);
    al_draw_textf(police, al_map_rgb(0, 0, 0), 1255, 20, 0, ": %d ", *ecefloos);
    al_draw_bitmap(Habitant, 750, 10, 0);
    al_draw_textf(police, al_map_rgb(0, 0, 0), 800, 20, 0, ": %d ", *nbHabTotal);
    al_flip_display();
    
    al_destroy_bitmap(eau);
    al_destroy_bitmap(eclair);
    al_destroy_bitmap(construction);
    al_destroy_bitmap(route2);
    al_destroy_bitmap(caserne);
}
