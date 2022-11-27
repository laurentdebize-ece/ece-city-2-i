#include "jeu.h"


void menuprincipal(){
    bool fin_page_accueil = false, fin_choix_mode = false, fin_jeu = false, curseur_sur_communiste = false, curseur_sur_capitaliste = false;
    bool clic_sur_commencer = false, clic_sur_quitter = false;

    int lancer_son = 0;

    int place_souris_x = 0, place_souris_y = 0;
    int* curseur_x = &place_souris_x;
    int* curseur_y = &place_souris_y;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* queue = NULL;
    ALLEGRO_TIMER* timer = NULL;

    ALLEGRO_EVENT event = {0};

    ALLEGRO_BITMAP *image_accueil = NULL;
    ALLEGRO_BITMAP *titre_accueil = NULL;
    ALLEGRO_BITMAP *bouton_commencer_normal = NULL;
    ALLEGRO_BITMAP *bouton_quitter_normal = NULL;
    ALLEGRO_BITMAP *bouton_commencer_grand = NULL;
    ALLEGRO_BITMAP *bouton_quitter_grand = NULL;
    ALLEGRO_BITMAP *fond_choix_mode = NULL;
    ALLEGRO_BITMAP *panneau_capitalisme = NULL;
    ALLEGRO_BITMAP *panneau_communisme = NULL;
    ALLEGRO_BITMAP *mode_communiste_normal = NULL;
    ALLEGRO_BITMAP *mode_capitaliste_normal = NULL;
    ALLEGRO_BITMAP *mode_communiste_grand = NULL;
    ALLEGRO_BITMAP *mode_capitaliste_grand = NULL;


    ALLEGRO_SAMPLE* clic = NULL;
    ALLEGRO_SAMPLE* musique_accueil = NULL;
    ALLEGRO_SAMPLE_INSTANCE* musique_fond_accueil = NULL;
    ALLEGRO_SAMPLE* musique_choix = NULL;
    ALLEGRO_SAMPLE_INSTANCE* musique_fond_choix = NULL;
    ALLEGRO_SAMPLE* son_choix = NULL;
    //  ALLEGRO_SAMPLE_ID  my_id;

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

    queue = al_create_event_queue();
    assert(queue != NULL);

    image_accueil = al_load_bitmap("../ecran_accueil.png"); //ok
    titre_accueil = al_load_bitmap("../titre.png");//ok
    bouton_commencer_normal = al_load_bitmap("../bitmap_bouton_commencer.png");//ok
    bouton_quitter_normal = al_load_bitmap("../bitmap_bouton_quitter.png");//ok
    bouton_commencer_grand = al_load_bitmap("../bouton_commencer_grand.png");//ok
    bouton_quitter_grand = al_load_bitmap("../bouton_quitter_grand.png");//ok
    fond_choix_mode = al_load_bitmap("../fond_mode.png");//ok
    panneau_capitalisme = al_load_bitmap("../bouton_capitalisme.png");//ok
    panneau_communisme = al_load_bitmap("../bouton_communisme.png");//ok
    mode_communiste_normal = al_load_bitmap("../bitmap_communisme.png");//ok
    mode_capitaliste_normal = al_load_bitmap("../bitmap_capitalisme.png");//ok
    mode_communiste_grand = al_load_bitmap("../bitmap_communisme_grand.png");//ok
    mode_capitaliste_grand = al_load_bitmap("../bitmap_capitalisme_grand.png");//ok

    al_reserve_samples(15);

    clic = al_load_sample("../BRUIT_-_CLIC.ogg");//ok
    son_choix = al_load_sample("../magic-mobil-1.ogg");//ok

    musique_accueil = al_load_sample("../SimCity-_-2013-_-Soundtrack-01.-SimCity-Theme.ogg");//ok
    musique_fond_accueil = al_create_sample_instance(musique_accueil);
    al_set_sample_instance_playmode(musique_fond_accueil, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musique_fond_accueil, al_get_default_mixer());

    musique_choix = al_load_sample("../Son_choix_mode.ogg");//ok
    musique_fond_choix = al_create_sample_instance(musique_choix);
    al_set_sample_instance_playmode(musique_fond_choix, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musique_fond_choix, al_get_default_mixer());

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


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
                    al_draw_bitmap(bouton_quitter_grand, 1590, 175, 0);
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

                        // al_play_sample(son_choix, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &my_id);

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

                        //  al_play_sample(son_choix, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &my_id);

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

                    // al_stop_sample(&my_id);

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
                    //al_stop_sample(&my_id);
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


    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_sample(clic);
    al_destroy_sample(musique_accueil);
    al_destroy_sample_instance(musique_fond_accueil);
    al_destroy_sample(musique_choix);
    al_destroy_sample_instance(musique_fond_choix);
    al_destroy_bitmap(image_accueil);
    al_destroy_bitmap(titre_accueil);
    al_destroy_bitmap(bouton_quitter_normal);
    al_destroy_bitmap(bouton_quitter_grand);
    al_destroy_bitmap(bouton_commencer_normal);
    al_destroy_bitmap(bouton_commencer_grand);
    al_destroy_bitmap(fond_choix_mode);
    al_destroy_bitmap(panneau_capitalisme);
    al_destroy_bitmap(panneau_communisme);
    al_destroy_bitmap(mode_capitaliste_normal);
    al_destroy_bitmap(mode_capitaliste_grand);
    al_destroy_bitmap(mode_communiste_normal);
    al_destroy_bitmap(mode_communiste_grand);


}


int TrouverNumeroCase(int iCase, int jCase){
    int numeroCase = iCase + jCase*NB_CASES;
    return numeroCase;
}

void ComposanteConnexeDuGraphe(Cases tabPlateau[NB_CASES][NB_CASES], Sommet2* Psommet2,bool compteurUsineEau,bool compteurUsineElec, int numeroConneDeUsineEau, int numeroConnexeDeUsineElec){
    for (int i = 0; i < NB_CASES; ++i) {
        for (int j = 0; j < NB_CASES; ++j) {
            if(tabPlateau[i][j].routeOccupe == 1) {
                if (tabPlateau[i + 1][j].routeOccupe == 1 && tabPlateau[i + 1][j].numeroCompoConnexe > 0 && tabPlateau[i + 1][j].numeroCompoConnexe > tabPlateau[i][j].numeroCompoConnexe) {
                    tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i + 1][j].numeroCompoConnexe;
                } else if (tabPlateau[i - 1][j].routeOccupe == 1 && tabPlateau[i - 1][j].numeroCompoConnexe > 0 && tabPlateau[i - 1][j].numeroCompoConnexe > tabPlateau[i][j].numeroCompoConnexe) {
                    tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i - 1][j].numeroCompoConnexe;
                } else if (tabPlateau[i][j + 1].routeOccupe == 1 && tabPlateau[i][j+1].numeroCompoConnexe > 0 && tabPlateau[i][j+1].numeroCompoConnexe > tabPlateau[i][j].numeroCompoConnexe) {
                    tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i][j + 1].numeroCompoConnexe;
                } else if (tabPlateau[i][j - 1].routeOccupe == 1 && tabPlateau[i][j-1].numeroCompoConnexe > 0&& tabPlateau[i][j-1].numeroCompoConnexe > tabPlateau[i][j].numeroCompoConnexe) {
                    tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i][j - 1].numeroCompoConnexe;
                }
                Parcourir(Psommet2, tabPlateau, i, j, compteurUsineEau, compteurUsineElec, numeroConneDeUsineEau, numeroConnexeDeUsineElec);
            }
        }
    }
}

void SourisSurCase(Cases tabPlateau[NB_CASES][NB_CASES], int* valeurSourisX, int* valeurSourisY, int* sourisDessusX, int* sourisDessusY, ALLEGRO_EVENT event){
    for (int i = 0; i < NB_CASES; ++i) {
        for (int j = 0; j < NB_CASESY; ++j) {

            *valeurSourisX = event.mouse.x;
            *valeurSourisY = event.mouse.y;
            if(event.mouse.x > tabPlateau[i][j].x1 && event.mouse.x < tabPlateau[i][j].x1 + LARGEUR_CASE && event.mouse.y > tabPlateau[i][j].y1 && event.mouse.y < tabPlateau[i][j].y1 + HAUTEUR_CASE){
                *sourisDessusX = i;
                *sourisDessusY = j;
            }
        }
    }
}

void RegarderCaseAutour(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int comptbitmap1, int* nbBatAutourDesRoutes, ALLEGRO_TIMER* timer, int i, int j){
    if(i+1 < 45) {
        //tabPlateau[i + 1][j].viable = 1;
        if(tabPlateau[i+1][j].occupeBat == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            tabPlateau[i][j].sommetDansLeGrapheHab = 1;
            //tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
            //tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i+1;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
        if(tabPlateau[i+1][j].occupeUsineEau == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            //tabPlateau[i][j].sommetDansLeGrapheHab = 0;
            tabPlateau[i][j].sommetDansLeGrapheUsineEau = 1;
            //tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i+1;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
        if(tabPlateau[i+1][j].occupeUsineElec == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            //tabPlateau[i][j].sommetDansLeGrapheHab = 0;
            //tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
            tabPlateau[i][j].sommetDansLeGrapheUsineElec = 1;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i+1;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }

    }
    if(i-1 >= 0) {
        //tabPlateau[i - 1][j].viable = 1;
        if(tabPlateau[i-1][j].occupeBat == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            tabPlateau[i][j].sommetDansLeGrapheHab = 1;
            //tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
            //tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i-1;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
        if(tabPlateau[i-1][j].occupeUsineEau == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            //tabPlateau[i][j].sommetDansLeGrapheHab = 0;
            tabPlateau[i][j].sommetDansLeGrapheUsineEau = 1;
            //tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i-1;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
        if(tabPlateau[i-1][j].occupeUsineElec == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            //tabPlateau[i][j].sommetDansLeGrapheHab = 0;
            //tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
            tabPlateau[i][j].sommetDansLeGrapheUsineElec = 1;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i-1;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j;
            tabPlateau[i][j].tabMaisonAutourRoutes++;

            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
    }
    if(j+1 < 45) {
        //tabPlateau[i][j + 1].viable = 1;
        if(tabPlateau[i][j+1].occupeBat == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            tabPlateau[i][j].sommetDansLeGrapheHab = 1;
            //tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
            //tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j+1;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
        if(tabPlateau[i][j+1].occupeUsineEau == 1){
            //printf("O\n");
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            //tabPlateau[i][j].sommetDansLeGrapheHab = 0;
            // tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
            tabPlateau[i][j].sommetDansLeGrapheUsineEau = 1;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j+1;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
        if(tabPlateau[i][j+1].occupeUsineElec == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            //tabPlateau[i][j].sommetDansLeGrapheHab = 0;
            tabPlateau[i][j].sommetDansLeGrapheUsineElec = 1;
            //tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j+1;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
    }
    if(j-1 >= 0) {
        //tabPlateau[i][j - 1].viable = 1;
        if(tabPlateau[i][j-1].occupeBat == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            tabPlateau[i][j].sommetDansLeGrapheHab = 1;
            //tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
            //tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j-1;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
        if(tabPlateau[i][j-1].occupeUsineEau == 1){
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            //tabPlateau[i][j].sommetDansLeGrapheHab = 0;
            tabPlateau[i][j].sommetDansLeGrapheUsineEau = 1;
            //tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j-1;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
        if(tabPlateau[i][j-1].occupeUsineElec == 1){
            //printf("Elec\n");
            tabPlateau[i][j].sommetDansLeGraphe = 1;
            //tabPlateau[i][j].sommetDansLeGrapheHab = 0;
            //tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
            tabPlateau[i][j].sommetDansLeGrapheUsineElec = 1;
            tabPlateau[i][j].tabMaisonAutourRoutesi[*nbBatAutourDesRoutes] = i;
            tabPlateau[i][j].tabMaisonAutourRoutesj[*nbBatAutourDesRoutes] = j-1;
            tabPlateau[i][j].tabMaisonAutourRoutes++;
            *nbBatAutourDesRoutes = *nbBatAutourDesRoutes + 1;
        }
    }
}

void choixModes(ALLEGRO_EVENT event, bool* clickCarreBleu, bool* choixCarreRoute, bool* affichageElec, bool* affichageEau, bool* affichageRoute, bool* choixUsineEau, bool* choixUsineElec, ALLEGRO_FONT* police){
    /// mode bat
    if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 500 && event.mouse.y < 550){
        *clickCarreBleu = TRUE;
        *choixCarreRoute = FALSE;
        *affichageElec = FALSE;
        *affichageEau = FALSE;
        *affichageRoute = TRUE;
        *choixUsineEau = FALSE,
        *choixUsineElec = FALSE;
    }
    /// Quitter le mode choix des bat et routes
    if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 700 && event.mouse.y < 750){
        *clickCarreBleu = FALSE;
        *choixCarreRoute = FALSE;
        *affichageElec = FALSE;
        *affichageEau = FALSE;
        *affichageRoute = TRUE;
        *choixUsineEau = FALSE,
        *choixUsineElec = FALSE;
    }
    /// mode route
    if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 400 && event.mouse.y < 450){
        *choixCarreRoute = TRUE;
        *affichageRoute = TRUE;
        *clickCarreBleu = FALSE;
        *affichageElec = FALSE;
        *affichageEau = FALSE;
        *choixUsineEau = FALSE,
        *choixUsineElec = FALSE;
    }
    /// choix carre eau vert
    if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 570 && event.mouse.y < 620){
        *choixCarreRoute = FALSE;
        *affichageRoute = TRUE;
        *clickCarreBleu = FALSE;
        *affichageElec = FALSE;
        *affichageEau = FALSE;
        *choixUsineEau = TRUE;
        *choixUsineElec = FALSE;
    }
    /// choix carre ele noir
    if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 630 && event.mouse.y < 680){
        *choixCarreRoute = FALSE;
        *affichageRoute = TRUE;
        *clickCarreBleu = FALSE;
        *affichageElec = FALSE;
        *affichageEau = FALSE;
        *choixUsineEau = FALSE,
        *choixUsineElec = TRUE;
    }
    /// Mode ChateauEau
    if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 100 && event.mouse.y < 150){
       *affichageRoute = FALSE;
       *affichageElec = FALSE;
       *affichageEau = TRUE;
       *choixUsineEau = FALSE,
       *choixUsineElec = FALSE;
       al_draw_text(police, al_map_rgb(0,0,0), 100, 120, 0, "Niveau -1");
    }
    /// ModeCentralElec
    if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 200 && event.mouse.y < 250){
        *affichageRoute = FALSE;
        *affichageElec = TRUE;
        *affichageEau = FALSE;
        *choixUsineEau = FALSE,
        *choixUsineElec = FALSE;
        al_draw_text(police, al_map_rgb(0,0,0), 100, 220, 0, "Niveau -2");
    }
}


void jeuPrincipale(int* finDuJeu) {

    Cases tabPlateau[NB_CASES][NB_CASES];
    Bitmap tabBit[NB_CASES];
    Construction tab_constru[LIGNES*COLONNES];
    Ligne ligne;
    Graphe* graphe = creerGraphe(LIGNES*COLONNES);
    Sommet2* Psommet2 = NULL;

    int comptbitmap1 = 0;
    int comptUEau = 0;
    int comptUElec = 0;
    int valeurSourisX =0;
    int valeurSourisY =0;
    int minutes = 0;
    int nbNombreBatPose = 0;
    int nbNombreUsineEauPose = 0;
    int nbNombreUsineElecPose = 0;
    int nbHabTotal = 0;
    int fin = 0;
    int sourisDessusX = 0;
    int sourisDessusY = 0;
    int eceFloos = 500000;
    int i_flottant = 0;
    int j_flottant = 0;
    int i_constant = 0;
    int j_constant = 0;
    int nb_element_terrain = 0;
    int premierSommeti = 0;
    int premierSommetj = 0;
    int tabMArque[45*35] = {0};
    int test1 = 0;
    int test2 = 1;
    int nbBatAutourDesRoutes = 0;
    int nbBatAutourDesRoutes2 = 1;
    int iHabPourAretes = 0;
    int jHabPourAretes = 0;
    int sommetPrec = 0;
    int nbDeSommetAdj = 0;
    int compteurUsineEau = 0;
    int compteurUsineElec = 0;
    int numCompoConnexe = 0;
    int nombreRoutePose = 0;
    int numeroConnexeDeUsineElec = 0;
    int numeroConneDeUsineEau = 0;
    int* numChateau = 0;


    bool clickCarreBleu = FALSE;
    bool choixCarreRoute = FALSE;
    bool impossiblePlacerBat = FALSE;
    bool affichageRoute = FALSE;
    bool affichageEau = FALSE;
    bool affichageElec = FALSE;
    bool EnleverRoute = FALSE;
    bool test = FALSE;
    bool click = FALSE;
    bool HabiViable = FALSE;
    bool choixUsineElec = FALSE;
    bool choixUsineEau = FALSE;
    bool changementCompoConnexe = FALSE;
    bool RouteColleBat = FALSE;

    /// Pour la création de la fenetre
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};

    /// Different timer
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timer1sec = NULL;

    /// Bitmap
    ALLEGRO_BITMAP *TerrainVague = NULL;
    ALLEGRO_BITMAP *Maison1 = NULL;
    ALLEGRO_BITMAP *Maison2 = NULL;
    ALLEGRO_BITMAP *Maison3 = NULL;
    ALLEGRO_BITMAP *Maison4 = NULL;
    ALLEGRO_BITMAP *MapFond = NULL;
    ALLEGRO_BITMAP *NuageFond = NULL;
    ALLEGRO_BITMAP *Ruine = NULL;
    ALLEGRO_BITMAP *Immeuble = NULL;
    ALLEGRO_BITMAP *GratteCiel = NULL;
    ALLEGRO_BITMAP *Cabane = NULL;
    ALLEGRO_BITMAP *CroixRouge = NULL;

    ALLEGRO_BITMAP *RouteDroite = NULL;
    ALLEGRO_BITMAP *RouteDroite2 = NULL;
    ALLEGRO_BITMAP *Tournant = NULL;
    ALLEGRO_BITMAP *Tournant2 = NULL;
    ALLEGRO_BITMAP *Tournant3 = NULL;
    ALLEGRO_BITMAP *Tournant4 = NULL;
    ALLEGRO_BITMAP *DoubleTournant = NULL;
    ALLEGRO_BITMAP *DoubleTournant2 = NULL;
    ALLEGRO_BITMAP *DoubleTournant3 = NULL;
    ALLEGRO_BITMAP *DoubleTournant4 = NULL;
    ALLEGRO_BITMAP *Croisement = NULL;

    ALLEGRO_BITMAP *PieceMonnaie = NULL;
    ALLEGRO_BITMAP *Habitant = NULL;
    ALLEGRO_BITMAP *CentralElectrique = NULL;
    ALLEGRO_BITMAP *ChateauEau = NULL;

    /// Police
    ALLEGRO_FONT* police = NULL;
    ALLEGRO_FONT* policePetite = NULL;





    // Initialisaton
    al_init();
    srand(time(NULL));
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_ttf_addon();
    al_init_acodec_addon();
    al_install_audio();


    // Creation
    /// creation fenetre
    display = al_create_display(LARGEUR_FE, HAUTEUR_FE);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "ECE City");
    queue = al_create_event_queue();

    /// valeur timer
    timer = al_create_timer(0.05);
    timer1sec = al_create_timer(1);
    //temps_cycle = al_create_timer(1.0);

    /// Chargement bitmpa
    TerrainVague = al_load_bitmap("../bitmap/terrainvague(true).png");
    Maison1 = al_load_bitmap("../bitmap/house1(bg)2.png");
    Maison2 = al_load_bitmap("../bitmap/house2(bg)2.png");
    Maison3 = al_load_bitmap("../bitmap/house3(bg).png");
    Maison4 = al_load_bitmap("../bitmap/house4(bg).png");
    MapFond = al_load_bitmap("../bitmap/mapfinie.png");
    NuageFond = al_load_bitmap("../bitmap/imageCiel.jpg");
    Ruine = al_load_bitmap("../bitmap/ruine(ng).png");
    Immeuble = al_load_bitmap("../bitmap/immeuble(bg).png");
    GratteCiel = al_load_bitmap("../bitmap/gratte-ciel(bg).png");
    Cabane = al_load_bitmap("../bitmap/cabanes.png");

    RouteDroite = al_load_bitmap("../bitmap/routeDroite .png");
    RouteDroite2 = al_load_bitmap("../bitmap/routeDroite2 .png");
    Tournant = al_load_bitmap("../bitmap/tournant.png");
    Tournant2 = al_load_bitmap("../bitmap/tournant2.png");
    Tournant3 = al_load_bitmap("../bitmap/tournant3.png");
    Tournant4 = al_load_bitmap("../bitmap/tournant4.png");
    DoubleTournant = al_load_bitmap("../bitmap/doubletournant.png");
    DoubleTournant2 = al_load_bitmap("../bitmap/doubletournant2.png");
    DoubleTournant3 = al_load_bitmap("../bitmap/doubletournant3.png");
    DoubleTournant4 = al_load_bitmap("../bitmap/doubletournant4.png");
    Croisement = al_load_bitmap("../bitmap/croisement.png");
    CentralElectrique = al_load_bitmap("../bitmap/centrale1Bis.png");
    ChateauEau = al_load_bitmap("../bitmap/chateaudeau.png");

    PieceMonnaie = al_load_bitmap("../bitmap/PieceMonnaie.png");
    Habitant = al_load_bitmap("../bitmap/nbPersonne.png");
    CroixRouge = al_load_bitmap("../bitmap/CroixRouge2.png");

    /// chargement police
    police = al_load_font("../Police/ARCADE_R.TTF",20, 0);
    policePetite = al_load_font("../Police/ARCADE_R.TTF",13, 0);



//AUDIO
/// Chargement des sons

    initialiser(tabPlateau, tabBit);
    tabBit[0].nbHabitant = 0;
    tabBit[1].nbHabitant = 10;
    tabBit[2].nbHabitant = 40;
    tabBit[3].nbHabitant = 50;
    tabBit[4].nbHabitant = 900;
    tabBit[5].nbHabitant = 0;


    // Premier affichage
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    //al_register_event_source(queue, al_get_timer_event_source(temps_cycle));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    al_start_timer(timer1sec);
    al_start_timer(timer);


    while (fin == 0) {

        // affichage
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                *finDuJeu = 1;
                break;


            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if ((event.mouse.button & 1) == 1) {
                    click = FALSE;
                    for (int i = 0; i < NB_CASES; ++i) {
                        for (int j = 0; j < NB_CASESY; ++j) {

                            if(event.mouse.x > tabPlateau[i][j].x1 && event.mouse.x < tabPlateau[i][j].x1 + LARGEUR_CASE && event.mouse.y > tabPlateau[i][j].y1 && event.mouse.y < tabPlateau[i][j].y1 + HAUTEUR_CASE){

                                if(tabPlateau[i][j].routeOccupe == 1){
                                    tabPlateau[i][j].routeOccupe = 0;
                                    EnleverRoute = TRUE;
                                }
                                if(tabPlateau[i][j].occupe == 0){
                                    if(choixCarreRoute == TRUE ) {
                                        click = TRUE;
                                        tabPlateau[i][j].occupe = 1;
                                        tabPlateau[i][j].routeOccupe = 1;
                                        if(nb_element_terrain == 0){
                                            premierSommeti = i;
                                            premierSommetj = j;
                                        }
                                        nb_element_terrain++;
                                        nombreRoutePose++;
                                        eceFloos = eceFloos - 10;
                                        tabPlateau[i][j].valeurCompteurAuClic = al_get_timer_count(timer);
                                        tabPlateau[i][j].sommetDansLeGraphe = 1;

                                        RegarderCaseAutour(tabPlateau, tabBit, comptbitmap1, &nbBatAutourDesRoutes, timer, i, j);


                                        /// Attente
                                        if(tabPlateau[i+1][j].routeOccupe == 0 && tabPlateau[i-1][j].routeOccupe == 0 && tabPlateau[i][j+1].routeOccupe == 0 && tabPlateau[i][j-1].routeOccupe == 0){
                                            numCompoConnexe++;
                                            tabPlateau[i][j].numeroCompoConnexe = numCompoConnexe;
                                        }
                                        ///
                                        tabPlateau[i][j].sommetGrapheI = i;
                                        tabPlateau[i][j].sommetGrapheJ = j;

                                        if(tabPlateau[tabPlateau[i][j].sommetGrapheI][tabPlateau[i][j].sommetGrapheJ].sommetDansLeGraphe >= 1 /*|| tabPlateau[tabPlateau[i][j].sommetGrapheI][tabPlateau[i][j].sommetGrapheJ].sommetDansLeGrapheHab == 1*/) {
                                            CreerArete2(&Psommet2, tabPlateau[i][j].sommetGrapheI, tabPlateau[i][j].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[i][j].sommetGrapheI, tabPlateau[i][j].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau, &sommetPrec, nombreRoutePose, numChateau);
                                        }
                                    }
                                    if(clickCarreBleu == TRUE){
                                        RouteColleBat = FALSE;
                                        for (int k = i; k <= i+NB_Cases_Place_ConstruX; ++k) {
                                            for (int l = j-NB_Cases_Place_ConstruY; l <= j; ++l) {
                                                if(tabPlateau[k][l].occupe == 1 || j-NB_Cases_Place_ConstruY < 0 || i+NB_Cases_Place_ConstruX > 44){
                                                    impossiblePlacerBat = TRUE;
                                                    tabBit[comptbitmap1].batPose = 0;
                                                    tabPlateau[k][l].occupeBat = 0;
                                                }
                                            }
                                        }
                                        if(impossiblePlacerBat == FALSE){
                                            for (int k = i; k <= i+NB_Cases_Place_ConstruX; ++k) {
                                                for (int l = j - NB_Cases_Place_ConstruY; l <= j; ++l) {
                                                    click = TRUE;
                                                    tabPlateau[k][l].occupe = 1;
                                                    tabPlateau[k][l].occupeBat = 1;
                                                    tabBit[comptbitmap1].batPose = 1;
                                                    tabBit[comptbitmap1].empecherDeRentrerPlusieursFoisDAnsLaBoucle = 0;
                                                    tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                    tabBit[comptbitmap1].i = i;
                                                    tabBit[comptbitmap1].j = j;
                                                    tabBit[comptbitmap1].chance1sur4 = rand() % 3;
                                                    tabBit[comptbitmap1].changemetnBat = 0;

                                                }
                                            }
                                            nb_element_terrain++;
                                            nbNombreBatPose++;
                                            //comptbitmap1++;
                                            eceFloos = eceFloos - 1000;

                                            for (int k = i-1; k <= i+NB_Cases_Place_ConstruX+1; ++k) {
                                                for (int l = j - NB_Cases_Place_ConstruY-1; l <= j+1; ++l) {
                                                    if(tabPlateau[k][l].routeOccupe == 1){
                                                        ///bool a true
                                                        RouteColleBat = TRUE;

                                                        if ((k == i-1) && (l != j - NB_Cases_Place_ConstruY-1) && (l != j+1)){
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;
                                                            /*if(tabPlateau[k][l].viable == 1){
                                                                HabiViable = TRUE;
                                                            }*/
                                                        }
                                                        if ((l == j - NB_Cases_Place_ConstruY-1) && (k != i-1) && (k != i+NB_Cases_Place_ConstruX+1)){
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j+1) && (k != i-1) && (k != i+NB_Cases_Place_ConstruX+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((k == i+NB_Cases_Place_ConstruX+1) && (l != j - NB_Cases_Place_ConstruY-1) && (l != j+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        tabPlateau[k][l].tabMaisonAutourRoutes++;
                                                        if( tabPlateau[tabPlateau[k][l].sommetGrapheI][tabPlateau[k][l].sommetGrapheJ].sommetDansLeGrapheHab == 1) {
                                                            CreerArete2(&Psommet2, tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau, &sommetPrec, nombreRoutePose, numChateau);

                                                        }
                                                    }
                                                }
                                            }
                                            comptbitmap1++;
                                        }
                                        impossiblePlacerBat = FALSE;

                                    }

                                    if(choixUsineEau == TRUE) {
                                        for (int k = i; k <= i + NB_Cases_Place_UsineX; ++k) {
                                            for (int l = j - NB_Cases_Place_UsineY; l <= j; ++l) {
                                                if (tabPlateau[k][l].occupe == 1 || j - NB_Cases_Place_UsineY < 0 ||
                                                    i + NB_Cases_Place_UsineX > 44) {
                                                    impossiblePlacerBat = TRUE;
                                                    tabBit[compteurUsineEau].batPose = 0;
                                                    tabPlateau[k][l].occupeBat = 0;
                                                }
                                            }
                                        }
                                        if (impossiblePlacerBat == FALSE) {
                                            for (int k = i; k <= i + NB_Cases_Place_UsineX; ++k) {
                                                for (int l = j - NB_Cases_Place_UsineY; l <= j; ++l) {
                                                    click = TRUE;
                                                    tabPlateau[k][l].occupe = 1;
                                                    tabPlateau[k][l].occupeUsineEau = 1;
                                                    tabBit[comptbitmap1].UsineEauPose = 1;
                                                    tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                    tabBit[comptbitmap1].empecherDeRentrerPlusieursFoisDAnsLaBoucle = 0;
                                                    tabBit[comptbitmap1].i = i;
                                                    tabBit[comptbitmap1].j = j;
                                                    tabBit[comptbitmap1].changemetnBat = 0;

                                                }
                                            }
                                            nb_element_terrain++;
                                            nbNombreBatPose++;
                                            comptbitmap1++;
                                            
                                            eceFloos = eceFloos - 5000;

                                            for (int k = i-1; k <= i+NB_Cases_Place_UsineX+1; ++k) {
                                                for (int l = j - NB_Cases_Place_UsineY-1; l <= j+1; ++l) {
                                                    if(tabPlateau[k][l].routeOccupe == 1){

                                                        if ((k == i-1) && (l != j - NB_Cases_Place_UsineX-1) && (l != j+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 1;


                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j - NB_Cases_Place_UsineY-1) && (k != i-1) && (k != i+NB_Cases_Place_UsineX+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j+1) && (k != i-1) && (k != i+NB_Cases_Place_UsineY+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((k == i+NB_Cases_Place_UsineX+1) && (l != j - NB_Cases_Place_UsineY-1) && (l != j+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        tabPlateau[k][l].tabMaisonAutourRoutes++;
                                                        if(tabPlateau[tabPlateau[k][l].sommetGrapheI][tabPlateau[k][l].sommetGrapheJ].sommetDansLeGrapheUsineEau == 1) {
                                                            CreerArete2(&Psommet2, tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau, &sommetPrec, nombreRoutePose, numChateau);

                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    impossiblePlacerBat = FALSE;

                                    if(choixUsineElec == TRUE) {
                                        for (int k = i; k <= i + NB_Cases_Place_UsineX; ++k) {
                                            for (int l = j - NB_Cases_Place_UsineY; l <= j; ++l) {
                                                if (tabPlateau[k][l].occupe == 1 || j - NB_Cases_Place_UsineY < 0 ||
                                                    i + NB_Cases_Place_UsineX > 44) {
                                                    impossiblePlacerBat = TRUE;
                                                    tabBit[compteurUsineElec].batPose = 0;
                                                    tabPlateau[k][l].occupeBat = 0;
                                                }
                                            }
                                        }
                                        if (impossiblePlacerBat == FALSE) {
                                            for (int k = i; k <= i + NB_Cases_Place_UsineX; ++k) {
                                                for (int l = j - NB_Cases_Place_UsineY; l <= j; ++l) {
                                                    click = TRUE;
                                                    tabPlateau[k][l].occupe = 1;
                                                    tabPlateau[k][l].occupeUsineElec = 1;
                                                    tabBit[comptbitmap1].UsineElecPose = 1;
                                                    tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                    tabBit[comptbitmap1].empecherDeRentrerPlusieursFoisDAnsLaBoucle = 0;
                                                    tabBit[comptbitmap1].i = i;
                                                    tabBit[comptbitmap1].j = j;
                                                    tabBit[comptbitmap1].changemetnBat = 0;

                                                }
                                            }
                                            nb_element_terrain++;
                                            nbNombreBatPose++;
                                            comptbitmap1++;
                                            eceFloos = eceFloos - 5000;

                                            for (int k = i-1; k <= i+NB_Cases_Place_UsineX+1; ++k) {
                                                for (int l = j - NB_Cases_Place_UsineY-1; l <= j+1; ++l) {
                                                    if(tabPlateau[k][l].routeOccupe == 1){

                                                        if ((k == i-1) && (l != j - NB_Cases_Place_UsineX-1) && (l != j+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 1;


                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j - NB_Cases_Place_UsineY-1) && (k != i-1) && (k != i+NB_Cases_Place_UsineX+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j+1) && (k != i-1) && (k != i+NB_Cases_Place_UsineY+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((k == i+NB_Cases_Place_UsineX+1) && (l != j - NB_Cases_Place_UsineY-1) && (l != j+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 1;

                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        tabPlateau[k][l].tabMaisonAutourRoutes++;
                                                        if(tabPlateau[tabPlateau[k][l].sommetGrapheI][tabPlateau[k][l].sommetGrapheJ].sommetDansLeGrapheUsineElec == 1) {
                                                            CreerArete2(&Psommet2, tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau, &sommetPrec,nombreRoutePose, numChateau);

                                                        }
                                                    }
                                                }
                                            }
                                        }

                                    }
                                    impossiblePlacerBat = FALSE;
                                }else{
                                    if(EnleverRoute == TRUE){
                                        tabPlateau[i][j].occupe = 0;
                                        tabPlateau[i][j].sommetDansLeGraphe = 0;
                                        if(tabPlateau[i+1][j].routeOccupe == 0) {
                                            tabPlateau[i + 1][j].viable = 0;
                                        }
                                        if(tabPlateau[i-1][j].routeOccupe == 0) {
                                            tabPlateau[i-1][j].viable = 0;

                                        }
                                        if(tabPlateau[i][j+1].routeOccupe == 0){
                                            tabPlateau[i][j+1].viable = 0;

                                        }
                                        if(tabPlateau[i][j-1].routeOccupe == 0){
                                            tabPlateau[i][j-1].viable = 0;
                                        }
                                        tabPlateau[i][j].viable = 0;
                                        nb_element_terrain--;
                                        EnleverRoute = FALSE;
                                    }
                                }


                            }
                            /// Choix dans la barre a outil
                            choixModes(event, &clickCarreBleu, &choixCarreRoute, &affichageElec, &affichageEau, &affichageRoute,&choixUsineEau, &choixUsineElec, police);

                        }
                    }
                }


                break;

            case ALLEGRO_EVENT_MOUSE_AXES: {
                SourisSurCase(tabPlateau, &valeurSourisX, &valeurSourisY, &sourisDessusX, &sourisDessusY, event);
                break;
            }


            case ALLEGRO_EVENT_TIMER: {
                if (event.timer.source == timer) {
                    //printf("%d\n", nb_element_terrain);
                    if (al_get_timer_count(timer1sec) == 60) {
                        al_stop_timer(timer1sec);
                        al_set_timer_count(timer1sec, 0);
                        al_start_timer(timer1sec);
                        minutes++;
                    }

                    ComposanteConnexeDuGraphe(tabPlateau, Psommet2, compteurUsineEau, compteurUsineElec, numeroConneDeUsineEau, numeroConnexeDeUsineElec);

                    drawFondEtCases(NuageFond,MapFond);
                    drawLine(ligne, X_DEPART, Y_DEPART);
                    dessinerRoutes(tabPlateau, RouteDroite, RouteDroite2, Tournant, Tournant2, Tournant3, Tournant4, DoubleTournant,DoubleTournant2, DoubleTournant3, DoubleTournant4, Croisement, timer, police, policePetite, affichageRoute, affichageEau, affichageElec);
                    drawMaison(tabPlateau, tabBit, nbNombreBatPose, affichageEau, affichageElec, timer, policePetite, TerrainVague, Maison1, Maison2, Maison3, Maison4, Ruine, Immeuble, GratteCiel, Cabane, PieceMonnaie, Habitant, CentralElectrique, ChateauEau, CroixRouge);
                    BoiteAOutilEtTimer(tabPlateau, tabBit, sourisDessusX, sourisDessusY, nbNombreBatPose, valeurSourisX, valeurSourisY, minutes, &nbHabTotal, &eceFloos, clickCarreBleu, choixUsineElec,choixUsineEau, timer, timer1sec, police, TerrainVague, PieceMonnaie, Habitant, CentralElectrique, ChateauEau);
                }
                break;
            }
        }
    }
}
