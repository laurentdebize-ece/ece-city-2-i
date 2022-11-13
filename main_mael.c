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

#include "map.h"
#include "Graphe.h"
#include "File.h"

#define LARGEUR 1024
#define HAUTEUR 768


int main() {

    bool fin_page_accueil = false, fin_choix_mode = true, curseur_sur_communiste = false, curseur_sur_capitaliste = false;
    bool case_occupee = false, clique = false, choix_route = false, choix_maison = false, choix_centrale = false;
    int place_souris_x = 0, place_souris_y = 0;
    int i_flottant = 0, j_flottant = 0, i_constant = 0, j_constant = 0;
    int nb_element_terrain = 0, timer_secondes = 0, timer_minutes = 0;
    bool timer_2 = false;

    int* curseur_x = &place_souris_x;
    int* curseur_y = &place_souris_y;

    Construction tab_constru[LIGNES*COLONNES];

    Repere repere_grille;

    Donnees_globales mairie;

    Graphe* graphe = creerGraphe(LIGNES*COLONNES);


    repere_grille.O.x = DEBUT_X;
    repere_grille.O.y = DEBUT_Y;

    repere_grille.I.x = DEBUT_X + TUILE_LARGEUR_ISO/2;
    repere_grille.I.y = DEBUT_Y + TUILE_HAUTEUR_ISO/2;

    repere_grille.J.x = DEBUT_X - TUILE_LARGEUR_ISO/2;
    repere_grille.J.y = DEBUT_Y + TUILE_HAUTEUR_ISO/2;

    init_mairie(&mairie);


    srand(time(NULL));

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER* temps_cycle = NULL;

    ALLEGRO_EVENT event = {0};

    ALLEGRO_BITMAP *image_accueil = NULL;
    ALLEGRO_BITMAP *titre_accueil = NULL;
    ALLEGRO_BITMAP *mode_communiste = NULL;
    ALLEGRO_BITMAP *mode_capitaliste = NULL;
    ALLEGRO_BITMAP *fade = NULL;

    ALLEGRO_FONT* police = NULL;

    ALLEGRO_SAMPLE *clic = NULL;


    assert(al_init());
    assert(al_install_keyboard());
    assert(al_install_mouse());
    assert(al_install_audio());
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    display = al_create_display(LARGEUR, HAUTEUR);
    al_set_window_title(display, "***ECE-City***");
    assert(display != NULL);

    timer = al_create_timer(1.0 / 10.0);
    temps_cycle = al_create_timer(1.0);


    queue = al_create_event_queue();
    assert(queue != NULL);

    police = al_load_font("../Fonts/IndieFlower-Regular.ttf", 25, 0);

    //image_accueil = al_load_bitmap("../Bitmaps/ecran_accueil.png");
    titre_accueil = al_load_bitmap("../Bitmaps/titreV3.png");
    mode_communiste = al_load_bitmap("../Bitmaps/choix_mode_communiste.png");
    mode_capitaliste = al_load_bitmap("../Bitmaps/choix_mode_capitaliste.png");
    fade = al_load_bitmap("../Bitmaps/black_fade.png");

    al_reserve_samples(10);

    clic = al_load_sample("../Sound/BRUIT_-_CLIC.ogg");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(temps_cycle));

    for(int a = 0; a < LIGNES; a++) {
        for(int b = 0; b < COLONNES; b++) {
            tab[a][b].x = DEBUT_X + b*(TUILE_LARGEUR_ISO/2) - a*(TUILE_LARGEUR_ISO/2);
            tab[a][b].y = DEBUT_Y+(TUILE_HAUTEUR_ISO/2) + b*(TUILE_HAUTEUR_ISO/2) + a*(TUILE_HAUTEUR_ISO/2);
            tab[a][b].occupee = 0;
            tab[a][b].type = -1;
        }
    }

    for(int i = 0; i < LIGNES*COLONNES; i++) {
        tab_constru[i].type = -1;
        tab_constru[i].viable = false;
        tab_constru[i].nb_cases_hauteur = tab_constru[i].nb_cases_largeur = 0;
    }

    al_start_timer(timer);
    al_start_timer(temps_cycle);

    //al_draw_bitmap(image_accueil, 0, 0, 0);
    //al_draw_bitmap(titre_accueil, 120, 10, 0);
    /*for(int i = 0; i < LIGNES; i++) {
        for(int j = 0; j < COLONNES; j++) {
            al_draw_filled_circle(tab[i][j].x, tab[i][j].y, 2, al_map_rgb(255, 0, 0));
        }
    }*/

    //al_flip_display();

    while(!fin_page_accueil) {

        if(!al_is_event_queue_empty(queue)) {
            al_wait_for_event(queue, &event);
        }

        switch(event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fin_page_accueil = true;
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN: {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        fin_page_accueil = true;
                        break;
                    }
                    case ALLEGRO_KEY_R: {
                        choix_maison = false;
                        choix_centrale = false;
                        choix_route = true;
                        break;
                    }
                    case ALLEGRO_KEY_M: {
                        choix_maison = true;
                        choix_centrale = false;
                        choix_route = false;
                        break;
                    }
                    case ALLEGRO_KEY_C: {
                        choix_maison = false;
                        choix_centrale = true;
                        choix_route = false;
                        break;
                    }
                }
                break;
            }

            case ALLEGRO_EVENT_MOUSE_AXES: {
                *curseur_x = event.mouse.x;
                *curseur_y = event.mouse.y;

                i_flottant = collision_iso_i(repere_grille.O, repere_grille.I, repere_grille.J, *curseur_x, *curseur_y);
                j_flottant = collision_iso_j(repere_grille.O, repere_grille.I, repere_grille.J, *curseur_x, *curseur_y);

                break;
            }

            case ALLEGRO_EVENT_TIMER: {
                if(event.timer.source == timer) {
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    afficherGrille();


                    if(timer_2) {
                        timer_secondes++;
                    }
                    timer_2 = false;
                    if(timer_secondes == 60) {
                        timer_secondes = 0;
                        timer_minutes++;
                    }
                    if(timer_secondes < 10 && timer_minutes < 10) {
                        al_draw_textf(police, al_map_rgb(0, 0, 0), 100, 100, 0, "%d%d : %d%d", 0, timer_minutes, 0,timer_secondes);
                    }
                    else if(timer_minutes < 10 && timer_secondes >= 10) {
                        al_draw_textf(police, al_map_rgb(0, 0, 0), 100, 100, 0, "%d%d : %d", 0, timer_minutes, timer_secondes);
                    }
                    else if(timer_minutes >= 10 && timer_secondes < 10) {
                        al_draw_textf(police, al_map_rgb(0, 0, 0), 100, 100, 0, "%d : %d%d", timer_minutes, 0, timer_secondes);
                    }
                    else {
                        al_draw_textf(police, al_map_rgb(0, 0, 0), 100, 100, 0, "%d : %d", timer_minutes, timer_secondes);
                    }


                    al_draw_textf(police, al_map_rgb(0, 0, 0), 100, 50, 0, "ECE-Flouz : %d", mairie.monnaie);


                    if(tab[i_flottant][j_flottant].occupee == 1) {
                        al_draw_textf(police, al_map_rgb(206, 3, 219), 400, 500, 0, "Cette case est occupee !");
                    }


                    if(clique) {
                        nb_element_terrain++;
                    }
                    clique = false;

                    if(nb_element_terrain > 0) {
                        for(int z = 0; z < LIGNES*COLONNES; z++) {
                            if(tab_constru[z].type == 0) {
                                draw_cases_route(tab_constru, z);
                            }
                            if(tab_constru[z].type == 1) {
                                draw_cases_maison(tab_constru, z);
                            }
                            if(tab_constru[z].type == 2) {
                                draw_cases_centrale(tab_constru, z);
                            }
                        }
                    }

                    al_flip_display();
                }
                else if(event.timer.source == temps_cycle) {
                    timer_2 = true;
                }
            }

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if(event.mouse.button == 1) {
                    al_play_sample(clic, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

                    i_constant = i_flottant;
                    j_constant = j_flottant;

                    if (choix_route) {
                        if (tab[i_constant][j_constant].occupee == 0 && mairie.monnaie >= 10) {
                            clique = true;

                            tab[i_constant][j_constant].occupee = 1;
                            tab[i_constant][j_constant].type = 0;
                            tab[i_constant][j_constant].id_bat_pose = i_constant * COLONNES + j_constant;

                            tab_constru[i_constant * COLONNES + j_constant].pos_x = tab[i_constant][j_constant].x;
                            tab_constru[i_constant * COLONNES + j_constant].pos_y = tab[i_constant][j_constant].y;
                            tab_constru[i_constant * COLONNES + j_constant].type = 0;
                            tab_constru[i_constant * COLONNES + j_constant].nb_cases_largeur = tab_constru[nb_element_terrain].nb_cases_hauteur = 1;

                            check_relier_cases(graphe, i_constant, j_constant, 0, 0, i_constant - 1, j_constant, true, tab_constru);
                            check_relier_cases(graphe, i_constant, j_constant, 0, 0, i_constant + 1, j_constant, true, tab_constru);
                            check_relier_cases(graphe, i_constant, j_constant, 0, 0, i_constant, j_constant - 1, true, tab_constru);
                            check_relier_cases(graphe, i_constant, j_constant, 0, 0, i_constant, j_constant + 1, true, tab_constru);


                            mairie.monnaie -= 10;
                        }
                    }

                    if (choix_maison) {
                        if (tab[i_constant][j_constant].occupee == 0 && tab[i_constant - 1][j_constant - 1].occupee == 0 && tab[i_constant + 1][j_constant + 1].occupee == 0
                            && tab[i_constant - 1][j_constant].occupee == 0 && tab[i_constant + 1][j_constant].occupee == 0 && tab[i_constant][j_constant - 1].occupee == 0
                            && tab[i_constant][j_constant + 1].occupee == 0 && tab[i_constant - 1][j_constant + 1].occupee == 0 && tab[i_constant + 1][j_constant - 1].occupee == 0
                            && mairie.monnaie >= 1000) {

                            clique = true;

                            for (int i = -1; i < 2; i++) {
                                for (int j = -1; j < 2; j++) {
                                    tab[i_constant + i][j_constant + j].occupee = 1;
                                    tab[i_constant + i][j_constant + j].id_bat_pose = i_constant * COLONNES + j_constant;

                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant - 1, j_constant,false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + 1, j_constant,false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant, j_constant - 1,false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant, j_constant + 1,false, tab_constru);

                                }
                            }


                            tab_constru[i_constant * COLONNES + j_constant].pos_x = tab[i_constant][j_constant].x;
                            tab_constru[i_constant * COLONNES + j_constant].pos_y = tab[i_constant][j_constant].y;
                            tab_constru[i_constant * COLONNES + j_constant].type = 1;
                            tab_constru[i_constant * COLONNES + j_constant].nb_cases_largeur = tab_constru[nb_element_terrain].nb_cases_hauteur = 3;

                            mairie.monnaie -= 1000;
                            mairie.nb_habitants += 10;

                        }
                    }

                    if (choix_centrale) {
                        if (tab[i_constant - 2][j_constant - 3].occupee == 0 && tab[i_constant - 2][j_constant - 2].occupee == 0 && tab[i_constant - 2][j_constant - 1].occupee == 0
                            && tab[i_constant - 2][j_constant].occupee == 0 && tab[i_constant - 2][j_constant + 1].occupee == 0 && tab[i_constant - 2][j_constant + 2].occupee == 0
                            && tab[i_constant - 1][j_constant - 3].occupee == 0 && tab[i_constant - 1][j_constant - 2].occupee == 0 && tab[i_constant - 1][j_constant - 1].occupee == 0
                            && tab[i_constant - 1][j_constant].occupee == 0 && tab[i_constant - 1][j_constant + 1].occupee == 0 && tab[i_constant - 1][j_constant + 2].occupee == 0
                            && tab[i_constant][j_constant - 3].occupee == 0 && tab[i_constant][j_constant - 2].occupee == 0 && tab[i_constant][j_constant - 1].occupee == 0
                            && tab[i_constant][j_constant].occupee == 0 && tab[i_constant][j_constant + 1].occupee == 0 && tab[i_constant][j_constant + 2].occupee == 0
                            && tab[i_constant + 1][j_constant - 3].occupee == 0 && tab[i_constant + 1][j_constant - 2].occupee == 0 && tab[i_constant + 1][j_constant - 1].occupee == 0
                            && tab[i_constant + 1][j_constant].occupee == 0 && tab[i_constant + 1][j_constant + 1].occupee == 0 && tab[i_constant + 1][j_constant + 2].occupee == 0
                            && mairie.monnaie >= 100000) {

                            clique = true;

                            for (int i = -2; i < 2; i++) {
                                for (int j = -3; j < 3; j++) {

                                    tab[i_constant + i][j_constant + j].occupee = 1;
                                    tab[i_constant + i][j_constant + j].id_bat_pose =
                                            i_constant * COLONNES + j_constant;
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + i - 1,j_constant + j, false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + i + 1,j_constant + j, false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + i,j_constant + j - 1, false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + i,j_constant + j + 1, false, tab_constru);

                                }
                            }


                            tab_constru[i_constant * COLONNES + j_constant].pos_x = tab[i_constant][j_constant].x;
                            tab_constru[i_constant * COLONNES + j_constant].pos_y = tab[i_constant][j_constant].y;
                            tab_constru[i_constant * COLONNES + j_constant].type = 2;
                            tab_constru[i_constant * COLONNES + j_constant].nb_cases_largeur = 6;
                            tab_constru[i_constant * COLONNES + j_constant].nb_cases_hauteur = 4;

                            mairie.monnaie -= 100000;

                        }

                    }

                    for(int a = 0; a < LIGNES; a++) {
                        for(int b = 0; b < COLONNES; b++) {
                            if(tab_constru[a*COLONNES + b].viable) {
                                for(int c = 0; c < LIGNES; c++) {
                                    for(int d = 0; d < COLONNES; d++) {
                                        if(tab[c][d].id_bat_pose == tab[a][b].id_bat_pose) {
                                            tab_constru[c*COLONNES + d].viable = true;
                                        }
                                    }
                                }
                            }
                        }
                    }

                }
                break;
            }

        }

    }

    printf("%d\n", nb_element_terrain);

    for(int k = 0; k < LIGNES; k++) {
        for(int l = 0; l < COLONNES; l++) {
            if(tab[k][l].occupee == 1) {
                printf("\n%d | %d\n", tab[k][l].id_bat_pose, tab_constru[k*COLONNES + l].viable);
            }
        }
    }




    /*while(!fin_choix_mode) {

        if(!al_is_event_queue_empty(queue)) {
            al_wait_for_event(queue, &event);
        }

        switch(event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fin_choix_mode = true;
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN: {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        fin_choix_mode = true;
                        break;
                    }
                }
                break;
            }

            case ALLEGRO_EVENT_TIMER: {
                if(curseur_sur_communiste) {
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(mode_communiste, 0, 0, 0);
                    al_draw_bitmap(mode_capitaliste, 512, 0, 0);
                    al_draw_tinted_bitmap(fade, al_map_rgba(0, 0, 0, 100), 0, 0, 0);
                    al_flip_display();
                }
                else if(curseur_sur_capitaliste) {
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(mode_communiste, 0, 0, 0);
                    al_draw_bitmap(mode_capitaliste, 512, 0, 0);
                    al_draw_tinted_bitmap(fade, al_map_rgba(0, 0, 0, 100), 512, 0, 0);
                    al_flip_display();
                }
                else {
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(mode_communiste, 0, 0, 0);
                    al_draw_bitmap(mode_capitaliste, 512, 0, 0);
                    al_flip_display();
                }
                break;
            }

            case ALLEGRO_EVENT_MOUSE_AXES: {
                *curseur_x = event.mouse.x;
                *curseur_y = event.mouse.y;
                if(*curseur_x >= 5 && *curseur_x <= 512 && *curseur_y >= 1 && *curseur_y <= 767) {
                    curseur_sur_communiste = true;
                    curseur_sur_capitaliste = false;
                }
                else if(*curseur_x > 512 && *curseur_x <= 10018 && *curseur_y >= 1 && *curseur_y <= 767) {
                    curseur_sur_capitaliste = true;
                    curseur_sur_communiste = false;
                }
                else {
                    curseur_sur_capitaliste = false;
                    curseur_sur_communiste = false;
                }
                break;
            }

        }
    }*/

    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_sample(clic);
    al_destroy_bitmap(image_accueil);

    return 0;
}
