#include "jeu.h"



void jeuPrincipale(int* finDuJeu) {

    Cases tabPlateau[NB_CASES][NB_CASES];
    Bitmap tabBit[NB_CASES];
    Ligne ligne;

    int comptbitmap1 = 0;
    int valeurSourisX =0;
    int valeurSourisY =0;
    int minutes = 0;
    int nbNombreBatPose = 0;
    int fin = 0;
    int sourisDessusX = 0;
    int sourisDessusY = 0;

    bool clickCarreBleu = FALSE;
    bool choixCarreRoute = FALSE;
    bool impossiblePlacerBat = FALSE;

    /// Pour la création de la fenetre
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};

    /// Different timer
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timer1sec = NULL;

    /// Bitmap
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

    /// Police
    ALLEGRO_FONT* police = NULL;

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
    al_set_window_title(display, "Dofus");
    queue = al_create_event_queue();

    /// valeur timer
    timer = al_create_timer(0.008);
    timer1sec = al_create_timer(1);

    /// Chargement bitmpa
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

    /// chargement police
    police = al_load_font("../Police/ARCADE_R.TTF",20, 0);


//AUDIO
/// Chargement des sons

    initialiser(tabPlateau, tabBit);



    // Premier affichage
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
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
                    for (int i = 0; i < NB_CASES; ++i) {
                        for (int j = 0; j < NB_CASESY; ++j) {

                            if(event.mouse.x > tabPlateau[i][j].x1 && event.mouse.x < tabPlateau[i][j].x1 + LARGEUR_CASE && event.mouse.y > tabPlateau[i][j].y1 && event.mouse.y < tabPlateau[i][j].y1 + HAUTEUR_CASE){
                                if(tabPlateau[i][j].occupe == 0){
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
                                                    tabBit[comptbitmap1].empecherDeRentrerPlusieursFoisDAnsLaBoucle = 0;
                                                    tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                    tabBit[comptbitmap1].i = i;
                                                    tabBit[comptbitmap1].j = j;

                                                    tabBit[comptbitmap1].changemetnBat = 0;
                                                }
                                            }
                                            nbNombreBatPose++;
                                        comptbitmap1++;
                                        }
                                        impossiblePlacerBat = FALSE;

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
                dessinerLeJeu(tabPlateau, tabBit, sourisDessusX, sourisDessusY, ligne, nbNombreBatPose, valeurSourisX, valeurSourisY, minutes, clickCarreBleu, timer, timer1sec, police, RouteDroite, RouteDroite2, Tournant, Tournant2, Tournant3, Tournant4, DoubleTournant, DoubleTournant2, DoubleTournant3, DoubleTournant4, Croisement, Bat2D, Cabane);
                break;
        }

    }
}
