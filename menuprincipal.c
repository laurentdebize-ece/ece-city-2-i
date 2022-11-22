//
// Created by User on 09/11/2022.
//

#include "menuprincipal.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
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



#define LARGEUR 1920
#define HAUTEUR 1080


void menuprincipal() {

    bool fin_page_accueil = false, fin_choix_mode = false, fin_jeu = false, curseur_sur_communiste = false, curseur_sur_capitaliste = false;
    bool clic_sur_commencer = false, clic_sur_quitter = false;
    bool case_occupee = false, clique = false, choix_route = false, choix_maison = false, choix_centrale = false;
    int place_souris_x = 0, place_souris_y = 0;
    int i_flottant = 0, j_flottant = 0, i_constant = 0, j_constant = 0;
    int nb_element_terrain = 0, timer_secondes = 0, timer_minutes = 0;
    int fader = 0, lancer_son = 0;
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

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_TIMER* temps_cycle = NULL;

    ALLEGRO_EVENT event = {0};

    ALLEGRO_BITMAP *image_accueil = NULL;
    ALLEGRO_BITMAP *titre_accueil = NULL;
    ALLEGRO_BITMAP* bouton_commencer_normal = NULL;
    ALLEGRO_BITMAP* bouton_quitter_normal = NULL;
    ALLEGRO_BITMAP* bouton_commencer_grand = NULL;
    ALLEGRO_BITMAP* bouton_quitter_grand = NULL;
    ALLEGRO_BITMAP* fond_choix_mode = NULL;
    ALLEGRO_BITMAP *panneau_capitalisme = NULL;
    ALLEGRO_BITMAP *panneau_communisme = NULL;
    ALLEGRO_BITMAP *mode_communiste_normal = NULL;
    ALLEGRO_BITMAP *mode_capitaliste_normal = NULL;
    ALLEGRO_BITMAP *mode_communiste_grand = NULL;
    ALLEGRO_BITMAP *mode_capitaliste_grand = NULL;
    ALLEGRO_BITMAP *image_jeu = NULL;


    ALLEGRO_BITMAP *fade = NULL;

    ALLEGRO_FONT* police = NULL;

    ALLEGRO_SAMPLE* clic = NULL;
    ALLEGRO_SAMPLE* bruit_constru = NULL;
    ALLEGRO_SAMPLE* musique_accueil = NULL;
    ALLEGRO_SAMPLE_INSTANCE* musique_fond_accueil = NULL;
    ALLEGRO_SAMPLE* musique_choix = NULL;
    ALLEGRO_SAMPLE_INSTANCE* musique_fond_choix = NULL;
    ALLEGRO_SAMPLE* musique_jeu = NULL;
    ALLEGRO_SAMPLE_INSTANCE* musique_fond_jeu = NULL;
    ALLEGRO_SAMPLE* son_choix = NULL;
    ALLEGRO_SAMPLE_ID  my_id;


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

    police = al_load_font("../Fonts/good-timing-bd.ttf", 25, 0);

    image_accueil = al_load_bitmap("../Bitmaps/ecran_accueil.png");
    titre_accueil = al_load_bitmap("../Bitmaps/titre.png");
    bouton_commencer_normal = al_load_bitmap("../Bitmaps/bitmap_bouton_commencer.png");
    bouton_quitter_normal = al_load_bitmap("../Bitmaps/bitmap_bouton_quitter.png");
    bouton_commencer_grand = al_load_bitmap("../Bitmaps/bouton_commencer_grand.png");
    bouton_quitter_grand = al_load_bitmap("../Bitmaps/bouton_quitter_grand.png");
    //fond_choix_mode = al_load_bitmap("../Bitmaps/fond_mode.png");
    panneau_capitalisme = al_load_bitmap("../Bitmaps/bouton_capitalisme.png");
    panneau_communisme = al_load_bitmap("../Bitmaps/bouton_communisme.png");
    mode_communiste_normal = al_load_bitmap("../Bitmaps/bitmap_communisme.png");
    mode_capitaliste_normal = al_load_bitmap("../Bitmaps/bitmap_capitalisme.png");
    mode_communiste_grand = al_load_bitmap("../Bitmaps/bitmap_communisme_grand.png");
    mode_capitaliste_grand = al_load_bitmap("../Bitmaps/bitmap_capitalisme_grand.png");
    fade = al_load_bitmap("../Bitmaps/black_fade.png");
    image_jeu = al_load_bitmap("../Bitmaps/imagefond_jeu.png");


    al_reserve_samples(15);

    clic = al_load_sample("../Sound/BRUIT_-_CLIC.ogg");
    bruit_constru = al_load_sample("../Sound/Marteau.ogg");
    son_choix = al_load_sample("../Sound/magic-mobil-1.ogg");

    musique_accueil = al_load_sample("../Sound/SimCity-_-2013-_-Soundtrack-01.-SimCity-Theme.ogg");
    musique_fond_accueil = al_create_sample_instance(musique_accueil);
    al_set_sample_instance_playmode(musique_fond_accueil, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musique_fond_accueil, al_get_default_mixer());

    musique_choix = al_load_sample("../Sound/Son_choix_mode.ogg");
    musique_fond_choix = al_create_sample_instance(musique_choix);
    al_set_sample_instance_playmode(musique_fond_choix, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musique_fond_choix, al_get_default_mixer());

    musique_jeu = al_load_sample("../Sound/Son_jeu_lance.ogg");
    musique_fond_jeu = al_create_sample_instance(musique_jeu);
    al_set_sample_instance_playmode(musique_fond_jeu, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musique_fond_jeu, al_get_default_mixer());


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

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(image_accueil, 0, 0, 0);
    al_draw_bitmap(titre_accueil, al_get_display_width(display)/2 - al_get_bitmap_width(titre_accueil)/2, 0, 0);
    al_draw_bitmap(bouton_commencer_normal, 1600, 60, 0);
    al_draw_bitmap(bouton_quitter_normal, 1600, 180, 0);
    al_flip_display();

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
                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        fin_page_accueil = true;
                        break;
                    }
                }
            }

            case ALLEGRO_EVENT_MOUSE_AXES: {
                *curseur_x = event.mouse.x;
                *curseur_y = event.mouse.y;

                if(*curseur_x >= 1600 && *curseur_x <= 1883 && *curseur_y >= 60 && *curseur_y <= 169) {

                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(image_accueil, 0, 0, 0);
                    al_draw_bitmap(titre_accueil, al_get_display_width(display)/2 - al_get_bitmap_width(titre_accueil)/2, 0, 0);
                    al_draw_bitmap(bouton_commencer_grand, 1589, 55, 0);
                    al_draw_bitmap(bouton_quitter_normal, 1600, 180, 0);
                    al_flip_display();

                    clic_sur_commencer = true;

                }
                else if(*curseur_x >= 1600 && *curseur_x <= 1883 && *curseur_y >= 180 && *curseur_y <= 289) {

                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(image_accueil, 0, 0, 0);
                    al_draw_bitmap(titre_accueil, al_get_display_width(display)/2 - al_get_bitmap_width(titre_accueil)/2, 0, 0);
                    al_draw_bitmap(bouton_commencer_normal, 1600, 60, 0);
                    al_draw_bitmap(bouton_quitter_normal, 1589, 175, 0);
                    al_flip_display();

                    clic_sur_quitter = true;

                }
                else {

                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(image_accueil, 0, 0, 0);
                    al_draw_bitmap(titre_accueil, al_get_display_width(display)/2 - al_get_bitmap_width(titre_accueil)/2, 0, 0);
                    al_draw_bitmap(bouton_commencer_normal, 1600, 60, 0);
                    al_draw_bitmap(bouton_quitter_normal, 1600, 180, 0);
                    al_flip_display();

                    clic_sur_commencer = false;
                    clic_sur_quitter = false;

                }
                break;
            }

            case ALLEGRO_EVENT_TIMER: {
                al_play_sample_instance(musique_fond_accueil);
                break;
            }

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if(event.mouse.button == 1) {
                    al_play_sample(clic, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    if(clic_sur_commencer) {
                        al_stop_sample_instance(musique_fond_accueil);
                        fin_page_accueil = true;
                    }
                    else if(clic_sur_quitter) {
                        al_stop_sample_instance(musique_fond_accueil);
                        fin_page_accueil = true;
                        fin_choix_mode = true;
                        fin_jeu = true;
                    }
                    break;
                }
                break;
            }
        }
    }


    while(!fin_choix_mode) {

        if(!al_is_event_queue_empty(queue)) {
            al_wait_for_event(queue, &event);
        }

        switch(event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fin_choix_mode = true;
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN: {
                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        fin_choix_mode = true;
                        break;
                    }
                }
                break;
            }

            case ALLEGRO_EVENT_MOUSE_AXES: {
                *curseur_x = event.mouse.x;
                *curseur_y = event.mouse.y;

                if(*curseur_x >= 600 && *curseur_x <= 790 && *curseur_y >= 360 && *curseur_y <= 671) {
                    if(lancer_son == 0) {

                        al_play_sample(son_choix, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &my_id);

                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_bitmap(fond_choix_mode, 0, 0, 0);
                        al_draw_bitmap(panneau_communisme, 612, 760, 0);
                        al_draw_bitmap(panneau_capitalisme, 1144, 760, 0);
                        al_draw_bitmap(mode_communiste_grand, 588, 340, 0);
                        al_draw_bitmap(mode_capitaliste_normal, 1110, 370, 0);
                        al_flip_display();
                    }
                    lancer_son = 1;

                    curseur_sur_communiste = true;

                }
                else if(*curseur_x >= 1110 && *curseur_x <= 1311 && *curseur_y >= 370 && *curseur_y <= 681) {
                    if(lancer_son == 0) {

                        al_play_sample(son_choix, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &my_id);

                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_bitmap(fond_choix_mode, 0, 0, 0);
                        al_draw_bitmap(panneau_communisme, 612, 760, 0);
                        al_draw_bitmap(panneau_capitalisme, 1144, 760, 0);
                        al_draw_bitmap(mode_communiste_normal, 600, 360, 0);
                        al_draw_bitmap(mode_capitaliste_grand, 1086, 333, 0);
                        al_flip_display();
                    }
                    lancer_son = 1;

                    curseur_sur_capitaliste = true;

                }
                else {

                    al_stop_sample(&my_id);

                    lancer_son = 0;

                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(fond_choix_mode, 0, 0, 0);
                    al_draw_bitmap(panneau_communisme, 612, 760, 0);
                    al_draw_bitmap(panneau_capitalisme, 1144, 760, 0);
                    al_draw_bitmap(mode_communiste_normal, 600, 360, 0);
                    al_draw_bitmap(mode_capitaliste_normal, 1110, 370, 0);
                    al_flip_display();

                    curseur_sur_communiste = false;
                    curseur_sur_capitaliste = false;

                }
                break;
            }

            case ALLEGRO_EVENT_TIMER: {
                al_play_sample_instance(musique_fond_choix);
                break;
            }

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if(event.mouse.button == 1) {
                    al_stop_sample(&my_id);
                    al_play_sample(clic, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    if(curseur_sur_capitaliste || curseur_sur_communiste) {
                        al_stop_sample_instance(musique_fond_choix);
                        fin_choix_mode = true;
                    }
                }
                break;
            }
        }
    }


  /*  al_start_timer(temps_cycle);

    while(!fin_jeu) {

        -*
        if(!al_is_event_queue_empty(queue)) {
            al_wait_for_event(queue, &event);
        }

        switch(event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fin_jeu = true;
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN: {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        fin_jeu = true;
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
                al_play_sample_instance(musique_fond_jeu);
                if(event.timer.source == timer) {
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_bitmap(image_jeu, 0, 0, 0);
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

                    i_constant = i_flottant;
                    j_constant = j_flottant;

                    if(choix_route) {
                        if (tab[i_constant][j_constant].occupee == 0 && mairie.monnaie >= 10) {
                            al_play_sample(bruit_constru, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
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

                    else if(choix_maison) {
                        if (tab[i_constant][j_constant].occupee == 0 && tab[i_constant - 1][j_constant - 1].occupee == 0 && tab[i_constant + 1][j_constant + 1].occupee == 0
                            && tab[i_constant - 1][j_constant].occupee == 0 && tab[i_constant + 1][j_constant].occupee == 0 && tab[i_constant][j_constant - 1].occupee == 0
                            && tab[i_constant][j_constant + 1].occupee == 0 && tab[i_constant - 1][j_constant + 1].occupee == 0 && tab[i_constant + 1][j_constant - 1].occupee == 0
                            && mairie.monnaie >= 1000) {

                            al_play_sample(bruit_constru, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
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

                    else if(choix_centrale) {
                        if (tab[i_constant - 2][j_constant - 3].occupee == 0 && tab[i_constant - 2][j_constant - 2].occupee == 0 && tab[i_constant - 2][j_constant - 1].occupee == 0
                            && tab[i_constant - 2][j_constant].occupee == 0 && tab[i_constant - 2][j_constant + 1].occupee == 0 && tab[i_constant - 2][j_constant + 2].occupee == 0
                            && tab[i_constant - 1][j_constant - 3].occupee == 0 && tab[i_constant - 1][j_constant - 2].occupee == 0 && tab[i_constant - 1][j_constant - 1].occupee == 0
                            && tab[i_constant - 1][j_constant].occupee == 0 && tab[i_constant - 1][j_constant + 1].occupee == 0 && tab[i_constant - 1][j_constant + 2].occupee == 0
                            && tab[i_constant][j_constant - 3].occupee == 0 && tab[i_constant][j_constant - 2].occupee == 0 && tab[i_constant][j_constant - 1].occupee == 0
                            && tab[i_constant][j_constant].occupee == 0 && tab[i_constant][j_constant + 1].occupee == 0 && tab[i_constant][j_constant + 2].occupee == 0
                            && tab[i_constant + 1][j_constant - 3].occupee == 0 && tab[i_constant + 1][j_constant - 2].occupee == 0 && tab[i_constant + 1][j_constant - 1].occupee == 0
                            && tab[i_constant + 1][j_constant].occupee == 0 && tab[i_constant + 1][j_constant + 1].occupee == 0 && tab[i_constant + 1][j_constant + 2].occupee == 0
                            && mairie.monnaie >= 100000) {

                            al_play_sample(bruit_constru, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
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

                    else {
                        al_play_sample(clic, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
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
        for (int l = 0; l < COLONNES; l++) {
            if (tab[k][l].occupee == 1) {
                printf("\n%d | %d\n", tab[k][l].id_bat_pose, tab_constru[k * COLONNES + l].viable);
            }
        }
    }*/


    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_timer(temps_cycle);
    al_destroy_sample(clic);
    al_destroy_sample(bruit_constru);
    al_destroy_sample(musique_accueil);
    al_destroy_sample_instance(musique_fond_accueil);
    al_destroy_sample(musique_choix);
    al_destroy_sample_instance(musique_fond_choix);
    al_destroy_sample(musique_jeu);
    al_destroy_sample_instance(musique_fond_jeu);
    al_destroy_bitmap(image_accueil);

}

