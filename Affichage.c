#include "Affichage.h"

void drawLine(Ligne lignes, int x, int y) {

    for (int i = 0; i < NB_CASESY; ++i) {
        for (int j = 0; j < NB_CASES; ++j) {
            al_draw_rectangle(X_DEPART + (j*LARGEUR_CASE), Y_DEPART + (i * HAUTEUR_CASE),(X_DEPART + LARGEUR_CASE) + (j * LARGEUR_CASE),(Y_DEPART + HAUTEUR_CASE) + (i * HAUTEUR_CASE), al_map_rgb(0, 0, 155), 1);
        }
    }
}

void dessinerLeJeu(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int sourisDessusX, int sourisDessusY, Ligne ligne, int nbNombreBatPose, int valeurSourisX, int valeurSourisY, int minutes, bool clickCarreBleu, ALLEGRO_TIMER* timer, ALLEGRO_TIMER* timer1sec, ALLEGRO_FONT* police, ALLEGRO_BITMAP* RouteDroite, ALLEGRO_BITMAP* RouteDroite2, ALLEGRO_BITMAP* Tournant, ALLEGRO_BITMAP* Tournant2, ALLEGRO_BITMAP* Tournant3, ALLEGRO_BITMAP* Tournant4, ALLEGRO_BITMAP* DoubleTournant,  ALLEGRO_BITMAP* DoubleTournant2,  ALLEGRO_BITMAP* DoubleTournant3,  ALLEGRO_BITMAP* DoubleTournant4,  ALLEGRO_BITMAP* Croisement,  ALLEGRO_BITMAP* Bat2D,  ALLEGRO_BITMAP* Cabane){
    al_clear_to_color(al_map_rgb(255,255,255));
    /// tracer les carrés rouges quand on cliques dessus (tracer les routes)
    for (int i = 0; i < NB_CASES; ++i) {
        for (int j = 0; j < NB_CASES; ++j) {
            //al_draw_circle(tabPlateau[i][j].x1, tabPlateau[i][j].y1,5 ,al_map_rgb(255,0,0), 1);
            if(tabPlateau[i][j].occupe == 1){
                al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 + LARGEUR_CASE, tabPlateau[i][j].y1+HAUTEUR_CASE,al_map_rgb(255,0,0));
            }
            if(tabPlateau[i][j].routeOccupe == 1){
                /// Si pas de route autour de la route normale
                if((tabPlateau[i+1][j].routeOccupe == 0 && tabPlateau[i-1][j].routeOccupe == 0) || (tabPlateau[i][j+1].routeOccupe == 0 && tabPlateau[i][j-1].routeOccupe == 0)){
                    al_draw_bitmap(RouteDroite, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                /// Route normale choix vers le haut/bas ou sur le cote
                if(tabPlateau[i+1][j].routeOccupe == 1 || tabPlateau[i-1][j].routeOccupe == 1){
                    al_draw_bitmap(RouteDroite2, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                if(tabPlateau[i][j+1].routeOccupe == 1 || tabPlateau[i][j-1].routeOccupe == 1){
                    al_draw_bitmap(RouteDroite, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                /// Choix du bon tournant
                if(tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(Tournant, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(Tournant2, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                if(tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1){
                    al_draw_bitmap(Tournant3, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1){
                    al_draw_bitmap(Tournant4, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                /// choix du bouble tournant
                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(DoubleTournant3, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1 && tabPlateau[i][j-1].routeOccupe == 1){
                    al_draw_bitmap(DoubleTournant4, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                if(tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(DoubleTournant, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1){
                    al_draw_bitmap(DoubleTournant2, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
                /// Gros croisement
                if(tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i][j-1].routeOccupe == 1 && tabPlateau[i+1][j].routeOccupe == 1 && tabPlateau[i-1][j].routeOccupe == 1){
                    al_draw_bitmap(Croisement, tabPlateau[i][j].x1, tabPlateau[i][j].y1,0);
                }
            }
        }
    }
    /// tracer les carrés verts quand on est sur la map
    al_draw_filled_rectangle(tabPlateau[sourisDessusX][sourisDessusY].x1, tabPlateau[sourisDessusX][sourisDessusY].y1, tabPlateau[sourisDessusX][sourisDessusY].x1 + LARGEUR_CASE, tabPlateau[sourisDessusX][sourisDessusY].y1+HAUTEUR_CASE,al_map_rgb(0,255,0));

    /// dessiner les carrés noir, le plateau
    drawLine(ligne, X_DEPART, Y_DEPART);


    /// Draw la bitmap de la maison
    for(int k = 0; k < nbNombreBatPose; k++){
        if(tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 0){
            al_draw_bitmap(Bat2D, tabPlateau[tabBit[k].i][tabBit[k].j].x1,tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 4 * HAUTEUR_CASE, 0);
        }
        if(tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 1){
            al_draw_bitmap(Cabane, tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 10,tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE, 0);
        }
        if(tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 2){
            al_draw_bitmap(RouteDroite, tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 10,tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE, 0);
        }
        if(tabBit[k].batPose == 1 && tabBit[k].changemetnBat > 2){
            al_draw_bitmap(Tournant, tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 10,tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE, 0);
        }
    }
    /// draw le rectangle bleu pour avoir le bat en main
    al_draw_filled_rectangle(20,500, 70, 550, al_map_rgb(20,50,180));
    ///carre quitter mode bat
    al_draw_filled_rectangle(20,650, 70, 700, al_map_rgb(150,150,0));
    /// carre rouge pour les routes
    al_draw_filled_rectangle(20,400, 70, 450, al_map_rgb(100,0,0));

    /// pour avoir le bat en main selon la pose de la souris
    if(clickCarreBleu == TRUE && valeurSourisX > X_DEPART && valeurSourisX < X_DEPART + 45*LARGEUR_CASE && valeurSourisY> Y_DEPART && valeurSourisY < Y_DEPART + 35*HAUTEUR_CASE ) {
        al_draw_bitmap(Bat2D, tabPlateau[sourisDessusX][sourisDessusY].x1,tabPlateau[sourisDessusX][sourisDessusY].y1 - 4 * HAUTEUR_CASE, 0);
    }


    /// draw les differnet timer
    /// timer 15sec

    for (int i = 0; i < nbNombreBatPose; ++i) {
        if((al_get_timer_count(timer)) <= (tabBit[i].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION + 1) && (al_get_timer_count(timer)) >= (tabBit[i].valeurCompteurAuClic + TEMPS_DE_CONSTRUCTION - 1)) {
            tabBit[i].valeurCompteurAuClic = al_get_timer_count(timer);
            tabBit[i].timerPasAfficherSansArret = al_get_timer_count(timer);
            tabBit[i].changemetnBat = tabBit[i].changemetnBat + 1;
            tabBit[i].empecherDeRentrerPlusieursFoisDAnsLaBoucle = 1;
        }
    }
    ///timer jeu complet
    al_draw_textf(police, al_map_rgb(0, 0, 0), 220, 20, 0, "%d s", al_get_timer_count(timer1sec));
    if(al_get_timer_count(timer1sec) == 60){
        al_stop_timer(timer1sec);
        al_set_timer_count(timer1sec, 0);
        al_start_timer(timer1sec);
        minutes++;
    }
    al_draw_textf(police, al_map_rgb(0, 0, 0), 180, 20, 0, "%d: ", minutes);
    al_flip_display();
}
