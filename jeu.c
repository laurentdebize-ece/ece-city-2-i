#include "jeu.h"


int TrouverNumeroCase(int iCase, int jCase){
    int numeroCase = iCase + jCase*NB_CASES;
    return numeroCase;
}


void jeuPrincipale(int* finDuJeu) {

    Cases tabPlateau[NB_CASES][NB_CASES];
    Bitmap tabBit[NB_CASES];
    Construction tab_constru[LIGNES*COLONNES];
    Ligne ligne;
    Graphe* graphe = creerGraphe(LIGNES*COLONNES);

    int comptbitmap1 = 0;
    int valeurSourisX =0;
    int valeurSourisY =0;
    int minutes = 0;
    int nbNombreBatPose = 0;
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


    bool clickCarreBleu = FALSE;
    bool choixCarreRoute = FALSE;
    bool impossiblePlacerBat = FALSE;
    bool affichageRoute = FALSE;
    bool affichageEau = FALSE;
    bool affichageElec = FALSE;
    bool EnleverRoute = FALSE;

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

    /// Police
    ALLEGRO_FONT* police = NULL;
    ALLEGRO_FONT* policePetite = NULL;

    /*

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


    ALLEGRO_TIMER* temps_cycle = NULL;*/




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

    PieceMonnaie = al_load_bitmap("../bitmap/PieceMonnaie.png");
    Habitant = al_load_bitmap("../bitmap/nbPersonne.png");

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

                    for (int i = 0; i < NB_CASES; ++i) {
                        for (int j = 0; j < NB_CASESY; ++j) {

                            if(event.mouse.x > tabPlateau[i][j].x1 && event.mouse.x < tabPlateau[i][j].x1 + LARGEUR_CASE && event.mouse.y > tabPlateau[i][j].y1 && event.mouse.y < tabPlateau[i][j].y1 + HAUTEUR_CASE){
                                if(tabPlateau[i][j].routeOccupe == 1){
                                    tabPlateau[i][j].routeOccupe = 0;
                                    EnleverRoute = TRUE;
                                }
                                if(tabPlateau[i][j].occupe == 0){
                                    if(choixCarreRoute == TRUE ) {
                                        tabPlateau[i][j].occupe = 1;
                                        tabPlateau[i][j].routeOccupe = 1;
                                        nb_element_terrain++;
                                        eceFloos = eceFloos - 10;
                                        tabPlateau[i][j].valeurCompteurAuClic = al_get_timer_count(timer);
                                        if(i+1 < 45) {
                                            tabPlateau[i + 1][j].viable = 1;
                                        }
                                        if(i-1 > 0) {
                                            tabPlateau[i - 1][j].viable = 1;
                                        }
                                        if(j+1 < 45) {
                                            tabPlateau[i][j + 1].viable = 1;
                                        }
                                        if(j-1 > 0) {
                                            tabPlateau[i][j - 1].viable = 1;
                                        }
                                        tabPlateau[i][j].viable = 1;
                                        //CreerArete(graphe->pSommet, i,j,i,j,TrouverNumeroCase(i, j), );
                                    }
                                    if(clickCarreBleu == TRUE){
                                        //tabBit[comptbitmap1].batPose = 1;
                                        //tabBit[comptbitmap1].i = i;
                                        //tabBit[comptbitmap1].j = j;
                                        for (int k = i; k <= i+NB_Cases_Place_ConstruX; ++k) {
                                            for (int l = j-NB_Cases_Place_ConstruY; l <= j; ++l) {
                                                if(tabPlateau[k][l].occupe == 1 || j-NB_Cases_Place_ConstruY < 0 || i+NB_Cases_Place_ConstruX > 44){
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
                                                        tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(
                                                                timer);
                                                        tabBit[comptbitmap1].i = i;
                                                        tabBit[comptbitmap1].j = j;
                                                        tabBit[comptbitmap1].chance1sur4 = rand() % 3;
                                                        tabBit[comptbitmap1].changemetnBat = 0;

                                                }
                                            }
                                            nb_element_terrain++;
                                            nbNombreBatPose++;
                                            comptbitmap1++;
                                            eceFloos = eceFloos - 1000;
                                        }
                                        impossiblePlacerBat = FALSE;

                                    }
                                }else{
                                    if(EnleverRoute == TRUE){
                                        tabPlateau[i][j].occupe = 0;
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
                            /// mode bat
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 500 && event.mouse.y < 550){
                                clickCarreBleu = TRUE;
                                choixCarreRoute = FALSE;
                                affichageElec = FALSE;
                                affichageEau = FALSE;
                                affichageRoute = TRUE;
                            }
                            /// Quitter le mode choix des bat et routes
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 650 && event.mouse.y < 700){
                                clickCarreBleu = FALSE;
                                choixCarreRoute = FALSE;
                                affichageElec = FALSE;
                                affichageEau = FALSE;
                                affichageRoute = TRUE;
                            }
                            /// mode route
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 400 && event.mouse.y < 450){
                                choixCarreRoute = TRUE;
                                affichageRoute = TRUE;
                                clickCarreBleu = FALSE;
                                affichageElec = FALSE;
                                affichageEau = FALSE;
                            }
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 100 && event.mouse.y < 150){
                                affichageRoute = FALSE;
                                affichageElec = FALSE;
                                affichageEau = TRUE;
                                al_draw_text(police, al_map_rgb(0,0,0), 100, 120, 0, "Niveau -1");
                            }
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 200 && event.mouse.y < 250){
                                affichageRoute = FALSE;
                                affichageElec = TRUE;
                                affichageEau = FALSE;
                                al_draw_text(police, al_map_rgb(0,0,0), 100, 220, 0, "Niveau -2");
                            }
                        }
                    }


                    ///Mael
                    i_constant = i_flottant;
                    j_constant = j_flottant;

                    /*if (choixCarreRoute == TRUE) {
                        if (tabPlateau[i_constant][j_constant].occupe == 0) {

                            tabPlateau[i_constant][j_constant].occupe = 1;
                            tabPlateau[i_constant][j_constant].type = 0;
                            tabPlateau[i_constant][j_constant].id_bat_pose = i_constant * COLONNES + j_constant;

                            tab_constru[i_constant * COLONNES + j_constant].pos_x = tabPlateau[i_constant][j_constant].x1;
                            tab_constru[i_constant * COLONNES + j_constant].pos_y = tabPlateau[i_constant][j_constant].y1;
                            tab_constru[i_constant * COLONNES + j_constant].type = 0;
                            tab_constru[i_constant * COLONNES + j_constant].nb_cases_largeur = tab_constru[nb_element_terrain].nb_cases_hauteur = 1;


                            check_relier_cases(graphe, i_constant, j_constant, 0, 0, i_constant - 1, j_constant, true, tab_constru, tabPlateau);
                            check_relier_cases(graphe, i_constant, j_constant, 0, 0, i_constant + 1, j_constant, true, tab_constru, tabPlateau);
                            check_relier_cases(graphe, i_constant, j_constant, 0, 0, i_constant, j_constant - 1, true, tab_constru, tabPlateau);
                            check_relier_cases(graphe, i_constant, j_constant, 0, 0, i_constant, j_constant + 1, true, tab_constru, tabPlateau);


                        }
                    }*/

                    /*if (clickCarreBleu == TRUE) {
                        if (tabPlateau[i_constant][j_constant].occupe == 0 && tabPlateau[i_constant - 1][j_constant - 1].occupe == 0 && tabPlateau[i_constant + 1][j_constant + 1].occupe == 0
                            && tabPlateau[i_constant - 1][j_constant].occupe == 0 && tabPlateau[i_constant + 1][j_constant].occupe == 0 && tabPlateau[i_constant][j_constant - 1].occupe == 0
                            && tabPlateau[i_constant][j_constant + 1].occupe == 0 && tabPlateau[i_constant - 1][j_constant + 1].occupe == 0 && tabPlateau[i_constant + 1][j_constant - 1].occupe == 0) {


                            for (int i = -1; i < 2; i++) {
                                for (int j = -1; j < 2; j++) {
                                    tabPlateau[i_constant + i][j_constant + j].occupe = 1;
                                    tabPlateau[i_constant + i][j_constant + j].id_bat_pose = i_constant * COLONNES + j_constant;

                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant - 1, j_constant,false, tab_constru, tabPlateau);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + 1, j_constant,false, tab_constru, tabPlateau);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant, j_constant - 1,false, tab_constru, tabPlateau);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant, j_constant + 1,false, tab_constru, tabPlateau);

                                }
                            }


                            tab_constru[i_constant * COLONNES + j_constant].pos_x = tabPlateau[i_constant][j_constant].x1;
                            tab_constru[i_constant * COLONNES + j_constant].pos_y = tabPlateau[i_constant][j_constant].y1;
                            tab_constru[i_constant * COLONNES + j_constant].type = 1;
                            tab_constru[i_constant * COLONNES + j_constant].nb_cases_largeur = tab_constru[nb_element_terrain].nb_cases_hauteur = 3;


                        }
                    }*/

                    /*if (choix_centrale) {
                        if (tabPlateau[i_constant - 2][j_constant - 3].occupee == 0 && tabPlateau[i_constant - 2][j_constant - 2].occupee == 0 && tabPlateau[i_constant - 2][j_constant - 1].occupee == 0
                            && tabPlateau[i_constant - 2][j_constant].occupee == 0 && tabPlateau[i_constant - 2][j_constant + 1].occupee == 0 && tabPlateau[i_constant - 2][j_constant + 2].occupee == 0
                            && tabPlateau[i_constant - 1][j_constant - 3].occupee == 0 && tabPlateau[i_constant - 1][j_constant - 2].occupee == 0 && tabPlateau[i_constant - 1][j_constant - 1].occupee == 0
                            && tabPlateau[i_constant - 1][j_constant].occupee == 0 && tabPlateau[i_constant - 1][j_constant + 1].occupee == 0 && tabPlateau[i_constant - 1][j_constant + 2].occupee == 0
                            && tabPlateau[i_constant][j_constant - 3].occupee == 0 && tabPlateau[i_constant][j_constant - 2].occupee == 0 && tabPlateau[i_constant][j_constant - 1].occupee == 0
                            && tabPlateau[i_constant][j_constant].occupee == 0 && tabPlateau[i_constant][j_constant + 1].occupee == 0 && tabPlateau[i_constant][j_constant + 2].occupee == 0
                            && tabPlateau[i_constant + 1][j_constant - 3].occupee == 0 && tabPlateau[i_constant + 1][j_constant - 2].occupee == 0 && tabPlateau[i_constant + 1][j_constant - 1].occupee == 0
                            && tabPlateau[i_constant + 1][j_constant].occupee == 0 && tabPlateau[i_constant + 1][j_constant + 1].occupee == 0 && tabPlateau[i_constant + 1][j_constant + 2].occupee == 0
                            && mairie.monnaie >= 100000) {

                            clique = true;

                            for (int i = -2; i < 2; i++) {
                                for (int j = -3; j < 3; j++) {

                                    tabPlateau[i_constant + i][j_constant + j].occupee = 1;
                                    tabPlateau[i_constant + i][j_constant + j].id_bat_pose =
                                            i_constant * COLONNES + j_constant;
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + i - 1,j_constant + j, false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + i + 1,j_constant + j, false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + i,j_constant + j - 1, false, tab_constru);
                                    check_relier_cases(graphe, i_constant, j_constant, i, j, i_constant + i,j_constant + j + 1, false, tab_constru);

                                }
                            }


                            tab_constru[i_constant * COLONNES + j_constant].pos_x = tabPlateau[i_constant][j_constant].x;
                            tab_constru[i_constant * COLONNES + j_constant].pos_y = tabPlateau[i_constant][j_constant].y;
                            tab_constru[i_constant * COLONNES + j_constant].type = 2;
                            tab_constru[i_constant * COLONNES + j_constant].nb_cases_largeur = 6;
                            tab_constru[i_constant * COLONNES + j_constant].nb_cases_hauteur = 4;

                            mairie.monnaie -= 100000;

                        }

                    }*/

                    /*for(int a = 0; a < LIGNES; a++) {
                        for(int b = 0; b < COLONNES; b++) {
                            if(tab_constru[a*COLONNES + b].viable) {
                                for(int c = 0; c < LIGNES; c++) {
                                    for(int d = 0; d < COLONNES; d++) {
                                        if(tabPlateau[c][d].id_bat_pose == tabPlateau[a][b].id_bat_pose) {
                                            tab_constru[c*COLONNES + d].viable = true;
                                        }
                                    }
                                }
                            }
                        }
                    }*/

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
                            i_flottant = i;
                            j_flottant = j;
                        }
                    }
                }
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
                    dessinerLeJeu(tabPlateau, tabBit, sourisDessusX, sourisDessusY, ligne, nbNombreBatPose,valeurSourisX, valeurSourisY, minutes, &nbHabTotal, &eceFloos, clickCarreBleu,affichageRoute, affichageEau, affichageElec, timer, timer1sec, police, policePetite,RouteDroite, RouteDroite2, Tournant, Tournant2, Tournant3, Tournant4, DoubleTournant,DoubleTournant2, DoubleTournant3, DoubleTournant4, Croisement, TerrainVague, Maison1,Maison2, Maison3, Maison4, MapFond, NuageFond, Ruine, Immeuble, GratteCiel, Cabane,PieceMonnaie, Habitant);
                    for (int i=0; i<nb_element_terrain; i++) {
                        while (graphe->pSommet[i]->arc != NULL){
                            printf("%d\n",graphe->pSommet[i]->arc->i_sommet);
                            printf("%d\n\n",graphe->pSommet[i]->arc->j_sommet);
                            graphe->pSommet[i]->arc=graphe->pSommet[i]->arc->arc_suivant;
                        }
                    }
                }
                break;
            }
        }

    }
}
