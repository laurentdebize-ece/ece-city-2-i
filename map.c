#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


void afficherGrille() {

    for(int i = 0; i < LIGNES+1; i++) {
        al_draw_line(DEBUT_X - i*(TUILE_LARGEUR_ISO/2), DEBUT_Y + i*(TUILE_HAUTEUR_ISO/2), DEBUT_X+(TUILE_LARGEUR_ISO/2 * COLONNES) - i*(TUILE_LARGEUR_ISO/2) , DEBUT_Y+(TUILE_HAUTEUR_ISO/2 * COLONNES) + i*(TUILE_HAUTEUR_ISO/2) , al_map_rgba(129, 114, 123, 0.26), 1);
    }

    for(int j = 0; j < COLONNES+1; j++) {
        al_draw_line(DEBUT_X + j*(TUILE_LARGEUR_ISO/2), DEBUT_Y + j*(TUILE_HAUTEUR_ISO/2), DEBUT_X-(TUILE_LARGEUR_ISO/2 * LIGNES) + j*(TUILE_LARGEUR_ISO/2), DEBUT_Y+(TUILE_HAUTEUR_ISO/2 * LIGNES) + j*(TUILE_HAUTEUR_ISO/2), al_map_rgba(129, 114, 123, 0.26), 1);
    }

}


void init_mairie(Donnees_globales* mairie) {
    mairie->monnaie = 500000;
    mairie->capa_eau = 0;
    mairie->capa_elec = 0;
    mairie->nb_habitants = 0;
}


int collision_iso_i(Point O, Point A, Point B, float x, float y) {

    Vecteur X, Y;

    X.x = B.x - O.x;
    X.y = B.y - O.y;
    Y.x = A.x - O.x;
    Y.y = A.y - O.y;

    float denom = X.x*Y.y - X.y*Y.x;

    float fi = (Y.y*x - Y.x*y + Y.x*O.y - O.x*Y.y)/denom;

    int i = (int)fi;

    return i;

}


int collision_iso_j(Point O, Point A, Point B, float x, float y) {

    Vecteur X, Y;

    X.x = B.x - O.x;
    X.y = B.y - O.y;
    Y.x = A.x - O.x;
    Y.y = A.y - O.y;

    float denom = X.x * Y.y - X.y * Y.x;

    float fj = -(X.y * x - X.x * y + X.x * O.y - O.x * X.y) / denom;

    int j = (int) fj;

    return j;
}


void draw_cases_route(Construction* tab_constru, int z) {
    /*if(tab_constru[z].viable) {
        al_draw_filled_triangle(tab_constru[z].pos_x - TUILE_LARGEUR_ISO/2 + 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(0, 255, 0));
        al_draw_filled_triangle(tab_constru[z].pos_x + TUILE_LARGEUR_ISO/2 - 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(0, 255, 0));
    }
    else {
        al_draw_filled_triangle(tab_constru[z].pos_x - TUILE_LARGEUR_ISO/2 + 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(255, 0, 0));
        al_draw_filled_triangle(tab_constru[z].pos_x + TUILE_LARGEUR_ISO/2 - 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(255, 0, 0));
    }*/
    al_draw_bitmap(tab_constru[z].icone, tab_constru[z].pos_x - TUILE_LARGEUR_ISO/2, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2, 0);
}


void draw_cases_maison(Construction* tab_constru, int z) {
    if(tab_constru[z].viable) {

        al_draw_filled_triangle(tab_constru[z].pos_x - TUILE_LARGEUR_ISO/2 + 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(0, 255, 0));
        al_draw_filled_triangle(tab_constru[z].pos_x + TUILE_LARGEUR_ISO/2 - 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(0, 255, 0));
    }
    else {
        al_draw_filled_triangle(tab_constru[z].pos_x - TUILE_LARGEUR_ISO/2 + 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(255, 0, 0));
        al_draw_filled_triangle(tab_constru[z].pos_x + TUILE_LARGEUR_ISO/2 - 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(255, 0, 0));
    }
}


void draw_cases_centrale(Construction* tab_constru, int z) {
    if(tab_constru[z].viable) {
        al_draw_filled_triangle(tab_constru[z].pos_x - TUILE_LARGEUR_ISO/2 + 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(0, 255, 0));
        al_draw_filled_triangle(tab_constru[z].pos_x + TUILE_LARGEUR_ISO/2 - 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(0, 255, 0));
    }
    else {
        al_draw_filled_triangle(tab_constru[z].pos_x - TUILE_LARGEUR_ISO/2 + 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(255, 0, 0));
        al_draw_filled_triangle(tab_constru[z].pos_x + TUILE_LARGEUR_ISO/2 - 1, tab_constru[z].pos_y, tab_constru[z].pos_x, tab_constru[z].pos_y - TUILE_HAUTEUR_ISO/2 + 1,
                                tab_constru[z].pos_x, tab_constru[z].pos_y + TUILE_HAUTEUR_ISO/2 - 1, al_map_rgb(255, 0, 0));
    }
}


/*void affichage_temps(int* timer_secondes, int* timer_minutes, ALLEGRO_FONT* police, float x, float y, bool timer_2) {
    if(timer_2) {
        timer_secondes++;
    }
    if(*timer_secondes == 60) {
        *timer_secondes = 0;
        *timer_minutes++;
    }
    al_draw_textf(police, al_map_rgb(0, 0, 0), x, y, 0, "%d : %d", *timer_minutes, *timer_secondes);
}*/

