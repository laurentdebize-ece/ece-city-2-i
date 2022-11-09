#include "jeu.h"

void drawLine(Ligne lignes, int x, int y) {
    int n = NB_CASES;
    for (int i = 0; i < 35; ++i) {
        for (int j = 0; j < n; ++j) {
            al_draw_rectangle(X_DEPART + (j*LARGEUR_CASE)/*+ (i*LARGEUR_CASE)*/, Y_DEPART + (i * HAUTEUR_CASE),(X_DEPART + LARGEUR_CASE) + (j * LARGEUR_CASE)/*+ (i * LARGEUR_CASE)*/,(Y_DEPART + HAUTEUR_CASE) + (i * HAUTEUR_CASE), al_map_rgb(0, 0, 155), 1);
            //al_draw_line(x + (i*LARGEUR_CASE), y + (i*HAUTEUR_CASE), (x - 35 * LARGEUR_CASE) + (i * LARGEUR_CASE), (y + 35 * HAUTEUR_CASE) + (i * HAUTEUR_CASE), al_map_rgb(0, 0, 0), 1);
        }
    }
    //for (int i = 0; i <= 35; ++i) {
    //  al_draw_rectangle(X_DEPART + (i*LARGEUR_CASE), Y_DEPART /*+ (i*HAUTEUR_CASE)*/, (X_DEPART + LARGEUR_CASE) + (i * LARGEUR_CASE), (Y_DEPART + HAUTEUR_CASE) /*+ (i * HAUTEUR_CASE)*/, al_map_rgb(0, 0, 155), 1);
    //al_draw_line((x + NB_CASES * LARGEUR_CASE) - (i * LARGEUR_CASE), (y + NB_CASES * HAUTEUR_CASE) + (i * HAUTEUR_CASE), x - (i * LARGEUR_CASE), y + (i * HAUTEUR_CASE),al_map_rgb(0, 0, 0), 1);
    //}
}






void jeuPrincipale(Player tabPlayer[], int nbJoueur, int* finDuJeu, PosDepart tabPosDepart[NBJOUEURMAX]) {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timer1sec = NULL;
    ALLEGRO_TIMER *timer15sec = NULL;
    ALLEGRO_BITMAP *Bat2D = NULL;
    ALLEGRO_BITMAP *Cabane = NULL;
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


    ALLEGRO_FONT* police = NULL;

    int fin = 0;
    int sourisDessusX = 0;
    int sourisDessusY = 0;
    Ligne ligne;

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

    display = al_create_display(LARGEUR_FE, HAUTEUR_FE);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "Dofus");
    queue = al_create_event_queue();
    timer = al_create_timer(0.006);
    timer1sec = al_create_timer(1);
    timer15sec = al_create_timer(1);

    //Immeuble = al_load_bitmap("../Image/immeuble (2).png");
    Bat2D = al_load_bitmap("../Image/bat2Dtest.png");
    Cabane = al_load_bitmap("../Image/cabanes.png");
    RouteDroite = al_load_bitmap("../Image/routeDroite .png");
    RouteDroite2 = al_load_bitmap("../Image/routeDroite2 .png");
    Tournant = al_load_bitmap("../Image/tournant.png");
    Tournant2 = al_load_bitmap("../Image/tournant2.png");
    Tournant3 = al_load_bitmap("../Image/tournant3.png");
    Tournant4 = al_load_bitmap("../Image/tournant4.png");
    DoubleTournant = al_load_bitmap("../Image/doubletournant.png");
    DoubleTournant2 = al_load_bitmap("../Image/doubletournant2.png");
    DoubleTournant3 = al_load_bitmap("../Image/doubletournant3.png");
    DoubleTournant4 = al_load_bitmap("../Image/doubletournant4.png");
    Croisement = al_load_bitmap("../Image/croisement.png");
    police = al_load_font("../Police/ARCADE_R.TTF",20, 0);


//AUDIO


    //ALLEGRO_SAMPLE_INSTANCE* al_lock_sample_id(ALLEGRO_SAMPLE_ID);



    ALLEGRO_KEYBOARD_STATE key;

    // la grande image de fond
    ALLEGRO_BITMAP*fond;
    // position et taille de l'image
    int x_depart, y_depart, tx, ty;
    // le déplacement
    int pas;
    Cases tabPlateau[NB_CASES][NB_CASES];
    Bitmap tabBit[NB_CASES];
    int compteur = 0;
    int comptbitmap1 = 0;
    int compteur2 = 0;
    int numero = 0;
    int ajoutX = 0;
    int ajoutY = 0;
    int valeurSourisX =0;
    int valeurSourisY =0;
    int minutes = 0;
    int changementBat = 0;
    int nbNombreBatPose = 0;
    bool clickCarreBleu = FALSE;
    bool choixCarreRoute = FALSE;
    bool impossiblePlacerBat = FALSE;
    // au départ l'image est calée sur le coin
    // haut-gauche
    x_depart = X_DEPART;
    y_depart = Y_DEPART;
    pas = 5;
    for (int i = 0; i < NB_MAX_BAT; ++i) {
        tabBit[i].batPose = 0;
    }

    for (int i = 0; i < NB_CASES; ++i) {
        for (int j = 0; j < 35; ++j) {
            tabPlateau[i][j].x1 = X_DEPART+ (compteur2 * LARGEUR_CASE);
            tabPlateau[i][j].y1 = Y_DEPART+ (compteur * HAUTEUR_CASE);
            tabPlateau[i][j].numeroCase = numero+1;
            tabPlateau[i][j].occupe = 0;
            compteur++;
            numero++;
            tabPlateau[i][j].joueurSurCase = 0;
        }
        compteur2++;
        compteur = 0;
        ajoutX += LARGEUR_CASE;
        ajoutY += HAUTEUR_CASE;
    }
    tabBit[0].Bitamp1 = Bat2D;


    // Premier affichage
    //dessinerTout(rectangle, police, policeTitre, policeDofus);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(timer1sec));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    al_start_timer(timer1sec);
    al_start_timer(timer15sec);
    al_start_timer(timer);

    al_clear_to_color(al_map_rgb(255,255,255));

    while (fin == 0) {

        al_get_keyboard_state(&key);

        if (al_key_down(&key, ALLEGRO_KEY_LEFT))
            x_depart = x_depart + pas;

        if (al_key_down(&key, ALLEGRO_KEY_RIGHT))
            x_depart = x_depart - pas;

        if (al_key_down(&key, ALLEGRO_KEY_UP))
            y_depart = y_depart + pas;

        if (al_key_down(&key, ALLEGRO_KEY_DOWN))
            y_depart = y_depart - pas;

        // affichage
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                *finDuJeu = 1;
                break;


            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if ((event.mouse.button & 1) == 1) {
                    for (int i = 0; i < NB_CASES; ++i) {
                        for (int j = 0; j < 35; ++j) {

                            if(event.mouse.x > tabPlateau[i][j].x1 && event.mouse.x < tabPlateau[i][j].x1 + LARGEUR_CASE && event.mouse.y > tabPlateau[i][j].y1 && event.mouse.y < tabPlateau[i][j].y1 + HAUTEUR_CASE){
                                //al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 + LARGEUR_CASE, tabPlateau[i][j].y1+HAUTEUR_CASE,al_map_rgb(255,0,0));
                                if(tabPlateau[i][j].occupe == 0){
                                    //al_draw_filled_triangle((tabPlateau[i][j].x1 + LARGEUR_CASE),tabPlateau[i][j].y1 + HAUTEUR_CASE,tabPlateau[i][j].x1,tabPlateau[i][j].y1,tabPlateau[i][j].x1,tabPlateau[i][j].y1 + (2*HAUTEUR_CASE),al_map_rgb(255,0,0));
                                    //al_draw_filled_triangle((tabPlateau[i][j].x1 - LARGEUR_CASE),tabPlateau[i][j].y1 + HAUTEUR_CASE,tabPlateau[i][j].x1,tabPlateau[i][j].y1,tabPlateau[i][j].x1,tabPlateau[i][j].y1 + (2*HAUTEUR_CASE),al_map_rgb(255,0,0));
                                    if(choixCarreRoute == TRUE ) {
                                        tabPlateau[i][j].occupe = 1;
                                        tabPlateau[i][j].routeOccupe = 1;
                                    }
                                    if(clickCarreBleu == TRUE){
                                        //tabBit[comptbitmap1].batPose = 1;
                                        //tabBit[comptbitmap1].i = i;
                                        //tabBit[comptbitmap1].j = j;
                                        for (int k = i; k <= i+NB_Cases_Place_ConstruX; ++k) {
                                            for (int l = j-NB_Cases_Place_ConstruY; l <= j; ++l) {
                                                if(tabPlateau[k][l].occupe == 1){
                                                    impossiblePlacerBat = TRUE;
                                                    tabBit[comptbitmap1].batPose = 0;
                                                }
                                            }
                                        }
                                        if(impossiblePlacerBat == FALSE){
                                            for (int k = i; k <= i+NB_Cases_Place_ConstruX; ++k) {
                                                for (int l = j - NB_Cases_Place_ConstruY; l <= j; ++l) {
                                                    tabPlateau[k][l].occupe = 1;
                                                    tabBit[comptbitmap1].batPose = 1;
                                                    tabBit[comptbitmap1].i = i;
                                                    tabBit[comptbitmap1].j = j;
                                                    /*for (int m = 0; m < nbNombreBatPose; ++m) {
                                                        //printf("%d : %d", m, tabBit[m].changemetnBat);
                                                        if(tabBit[m].changemetnBat == 1){
                                                            for (int n = i; n <= i+NB_Cases_Place_ConstruX+1; ++n) {
                                                                for (int o = j - NB_Cases_Place_ConstruY; o <= j+1 ; ++o) {
                                                                    tabPlateau[n][o].occupe = 1;
                                                                }
                                                            }
                                                            //tabBit[comptbitmap1].batPose = 0;
                                                        }
                                                    }*/
                                                    tabBit[comptbitmap1].changemetnBat = 0;
                                                }
                                            }
                                            nbNombreBatPose++;
                                        }
                                        impossiblePlacerBat = FALSE;
                                        comptbitmap1++;
                                        //clickCarreBleu = FALSE;
                                    }
                                }

                            }
                            /// mode bat
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 500 && event.mouse.y < 550){
                                clickCarreBleu = TRUE;
                                choixCarreRoute = FALSE;
                            }
                            /// Quitter le mode choix des bat et routes
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 650 && event.mouse.y < 700){
                                clickCarreBleu = FALSE;
                                choixCarreRoute = FALSE;
                            }
                            /// mode route
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 400 && event.mouse.y < 450){
                                choixCarreRoute = TRUE;
                                clickCarreBleu = FALSE;

                            }
                        }
                    }
                }
                break;

            case ALLEGRO_EVENT_MOUSE_AXES: {
                for (int i = 0; i < NB_CASES; ++i) {
                    for (int j = 0; j < 35; ++j) {
                        /*int calcul = 0;
                        calcul = (event.mouse.x - tabPlateau[i][j].x1) * (event.mouse.x - tabPlateau[i][j].x1) +
                                 (event.mouse.y - tabPlateau[i][j].y1 - HAUTEUR_CASE) *
                                 (event.mouse.y - tabPlateau[i][j].y1 - HAUTEUR_CASE);
                        if (calcul <= HAUTEUR_CASE * HAUTEUR_CASE) {
                        }*/
                        valeurSourisX = event.mouse.x;
                        valeurSourisY = event.mouse.y;
                        if(event.mouse.x > tabPlateau[i][j].x1 && event.mouse.x < tabPlateau[i][j].x1 + LARGEUR_CASE && event.mouse.y > tabPlateau[i][j].y1 && event.mouse.y < tabPlateau[i][j].y1 + HAUTEUR_CASE){
                            sourisDessusX = i;
                            sourisDessusY = j;
                        }
                    }
                }
                break;
            }

            case ALLEGRO_EVENT_TIMER:
                /// clear le fond en blanc
                al_clear_to_color(al_map_rgb(255,255,255));
                /// tracer les carrés rouges quand on cliques dessus (tracer les routes)
                for (int i = 0; i < NB_CASES; ++i) {
                    for (int j = 0; j < NB_CASES; ++j) {
                        //al_draw_circle(tabPlateau[i][j].x1, tabPlateau[i][j].y1,5 ,al_map_rgb(255,0,0), 1);
                        if(tabPlateau[i][j].occupe == 1){
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
                            //al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 + LARGEUR_CASE, tabPlateau[i][j].y1+HAUTEUR_CASE,al_map_rgb(255,0,0));
                        }
                        /*if(tabPlateau[i][j].occupe == 0){
                            al_draw_filled_rectangle(tabPlateau[i][j].x1, tabPlateau[i][j].y1, tabPlateau[i][j].x1 + LARGEUR_CASE, tabPlateau[i][j].y1+HAUTEUR_CASE,al_map_rgb(255,255,255));
                        }*/
                    }
                }
                /// tracer les carrés verts quand on est sur la map
                al_draw_filled_rectangle(tabPlateau[sourisDessusX][sourisDessusY].x1, tabPlateau[sourisDessusX][sourisDessusY].y1, tabPlateau[sourisDessusX][sourisDessusY].x1 + LARGEUR_CASE, tabPlateau[sourisDessusX][sourisDessusY].y1+HAUTEUR_CASE,al_map_rgb(0,255,0));

                /// dessiner les carrés noir, le plateau
                drawLine(ligne, x_depart, y_depart);


                /// Draw la bitmap de la maison
                for(int k = 0; k < NB_MAX_BAT; k++){
                    if(tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 0){
                        al_draw_bitmap(Bat2D, tabPlateau[tabBit[k].i][tabBit[k].j].x1,tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 4 * HAUTEUR_CASE, 0);
                    }
                    if(tabBit[k].batPose == 1 && tabBit[k].changemetnBat == 1){
                        al_draw_bitmap(Cabane, tabPlateau[tabBit[k].i][tabBit[k].j].x1 - 10,tabPlateau[tabBit[k].i][tabBit[k].j].y1 - 3 * HAUTEUR_CASE, 0);
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
                al_draw_textf(police, al_map_rgb(150, 80, 34), 300, 20, 0, "%d s", al_get_timer_count(timer15sec));
                if(al_get_timer_count(timer15sec) == 15){
                    al_stop_timer(timer15sec);
                    al_set_timer_count(timer15sec, 0);
                    al_start_timer(timer15sec);
                    changementBat++;
                    for (int i = 0; i < nbNombreBatPose; ++i) {
                        tabBit[i].changemetnBat = changementBat;
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
                break;
        }

    }
}
