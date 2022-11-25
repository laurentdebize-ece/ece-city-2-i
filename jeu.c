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
                                        if(i+1 < 45) {
                                            //tabPlateau[i + 1][j].viable = 1;
                                            if(tabPlateau[i+1][j].occupeBat == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i+1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                nbBatAutourDesRoutes++;
                                            }
                                            if(tabPlateau[i+1][j].occupeUsineEau == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i+1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                nbBatAutourDesRoutes++;
                                            }
                                            if(tabPlateau[i+1][j].occupeUsineElec == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i+1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                nbBatAutourDesRoutes++;
                                            }

                                        }
                                        if(i-1 >= 0) {
                                            //tabPlateau[i - 1][j].viable = 1;
                                            if(tabPlateau[i-1][j].occupeBat == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i-1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                nbBatAutourDesRoutes++;
                                            }
                                            if(tabPlateau[i-1][j].occupeUsineEau == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i-1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                nbBatAutourDesRoutes++;
                                            }
                                            if(tabPlateau[i-1][j].occupeUsineElec == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i-1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;

                                                nbBatAutourDesRoutes++;
                                            }
                                        }
                                        if(j+1 < 45) {
                                            //tabPlateau[i][j + 1].viable = 1;
                                            if(tabPlateau[i][j+1].occupeBat == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j+1;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                nbBatAutourDesRoutes++;
                                            }
                                            if(tabPlateau[i][j+1].occupeUsineEau == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j+1;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                nbBatAutourDesRoutes++;
                                            }
                                            if(tabPlateau[i][j+1].occupeUsineElec == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j+1;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                nbBatAutourDesRoutes++;
                                            }
                                        }
                                        if(j-1 >= 0) {
                                            //tabPlateau[i][j - 1].viable = 1;
                                            if(tabPlateau[i][j-1].occupeBat == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j-1;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                nbBatAutourDesRoutes++;
                                            }
                                            if(tabPlateau[i][j-1].occupeUsineEau == 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 0;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j-1;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                nbBatAutourDesRoutes++;
                                            }
                                            if(tabPlateau[i][j-1].occupeUsineElec== 1){
                                                tabPlateau[i][j].sommetDansLeGraphe = 1;
                                                tabPlateau[i][j].sommetDansLeGrapheHab = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineEau = 0;
                                                tabPlateau[i][j].sommetDansLeGrapheUsineElec = 1;
                                                tabPlateau[i][j].tabMaisonAutourRoutesi[nbBatAutourDesRoutes] = i;
                                                tabPlateau[i][j].tabMaisonAutourRoutesj[nbBatAutourDesRoutes] = j-1;
                                                tabPlateau[i][j].tabMaisonAutourRoutes++;
                                                nbBatAutourDesRoutes++;
                                            }

                                        }
                                        /// Attente
                                        if(tabPlateau[i+1][j].routeOccupe == 0 && tabPlateau[i-1][j].routeOccupe == 0 && tabPlateau[i][j+1].routeOccupe == 0 && tabPlateau[i][j-1].routeOccupe == 0){
                                            numCompoConnexe++;
                                            tabPlateau[i][j].numeroCompoConnexe = numCompoConnexe;
                                        }
                                        /*if (tabPlateau[i + 1][j].routeOccupe == 1) {
                                            tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i+1][j].numeroCompoConnexe;
                                        }else if (tabPlateau[i - 1][j].routeOccupe == 1) {
                                             tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i-1][j].numeroCompoConnexe;
                                        }else if (tabPlateau[i][j + 1].routeOccupe == 1) {
                                            tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i][j+1].numeroCompoConnexe;
                                        }else if (tabPlateau[i][j - 1].routeOccupe == 1) {
                                            tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i][j-1].numeroCompoConnexe;
                                        }else if (tabPlateau[i + 1][j].routeOccupe == 1 && tabPlateau[i - 1][j].routeOccupe == 1){
                                            tabPlateau[i][j].numeroCompoConnexe = 1;
                                        }else if (tabPlateau[i][j+1].routeOccupe == 1 && tabPlateau[i][j-1].routeOccupe == 1){
                                            tabPlateau[i][j].numeroCompoConnexe = 1;
                                        }*/
                                        ///
                                        tabPlateau[i][j].sommetGrapheI = i;
                                        tabPlateau[i][j].sommetGrapheJ = j;
                                        if(tabPlateau[tabPlateau[i][j].sommetGrapheI][tabPlateau[i][j].sommetGrapheJ].sommetDansLeGraphe == 1 /*|| tabPlateau[tabPlateau[i][j].sommetGrapheI][tabPlateau[i][j].sommetGrapheJ].sommetDansLeGrapheHab == 1*/) {
                                            CreerArete2(&Psommet2, tabPlateau[i][j].sommetGrapheI, tabPlateau[i][j].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[i][j].sommetGrapheI, tabPlateau[i][j].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau, &sommetPrec, nombreRoutePose);
                                            //Psommet2 = Trier(Psommet2);
                                            //SupprimerArete(&Psommet2,tabPlateau, i, j);
                                            //Psommet2 = TrierDansLeBonSensDeLaPose(Psommet2);
                                            //Parcourir(Psommet2, tabPlateau, i, j, compteurUsineEau, compteurUsineElec, numeroConneDeUsineEau, numeroConnexeDeUsineElec);
                                            //afficher(Psommet2, tabPlateau, i, j);
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
                                                        //printf("gg");
                                                        //tabBit[comptbitmap1].valeurCompteurAuClic = al_get_timer_count(timer);
                                                        //printf("%d\n", tabBit[comptbitmap1].valeurCompteurAuClic);
                                                        if ((k == i-1) && (l != j - NB_Cases_Place_ConstruY-1) && (l != j+1)){
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 1;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 0;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;
                                                            /*if(tabPlateau[k][l].viable == 1){
                                                                HabiViable = TRUE;
                                                            }*/
                                                        }
                                                        if ((l == j - NB_Cases_Place_ConstruY-1) && (k != i-1) && (k != i+NB_Cases_Place_ConstruX+1)){
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 1;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;
                                                            /*if(tabPlateau[k][l].viable == 1){
                                                                HabiViable = TRUE;
                                                            }*/
                                                        }
                                                        if ((l == j+1) && (k != i-1) && (k != i+NB_Cases_Place_ConstruX+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 1;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;
                                                            /*if(tabPlateau[k][l].viable == 1){
                                                                HabiViable = TRUE;
                                                            }*/
                                                        }
                                                        if ((k == i+NB_Cases_Place_ConstruX+1) && (l != j - NB_Cases_Place_ConstruY-1) && (l != j+1)){

                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 1;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;
                                                            /*if(tabPlateau[k][l].viable == 1){
                                                                HabiViable = TRUE;
                                                            }*/
                                                        }
                                                        tabPlateau[k][l].tabMaisonAutourRoutes++;
                                                        if( tabPlateau[tabPlateau[k][l].sommetGrapheI][tabPlateau[k][l].sommetGrapheJ].sommetDansLeGrapheHab == 1) {
                                                            CreerArete2(&Psommet2, tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau, &sommetPrec, nombreRoutePose);
                                                            //Psommet2 = Trier(Psommet2);
                                                            //SupprimerArete(&Psommet2,tabPlateau, i, j);
                                                            //Psommet2 = TrierDansLeBonSensDeLaPose(Psommet2);
                                                            //Parcourir(Psommet2, tabPlateau, i, j, compteurUsineEau, compteurUsineElec, numeroConneDeUsineEau, numeroConnexeDeUsineElec);
                                                            //afficher(Psommet2, tabPlateau, i, j);
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
                                                            //printf("1");
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 1;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 0;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j - NB_Cases_Place_UsineY-1) && (k != i-1) && (k != i+NB_Cases_Place_UsineX+1)){
                                                            //printf("2");
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 1;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 0;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j+1) && (k != i-1) && (k != i+NB_Cases_Place_UsineY+1)){
                                                            //printf("3");
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 1;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 0;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((k == i+NB_Cases_Place_UsineX+1) && (l != j - NB_Cases_Place_UsineY-1) && (l != j+1)){
                                                            //printf("4");
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 1;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 0;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        tabPlateau[k][l].tabMaisonAutourRoutes++;
                                                        if(tabPlateau[tabPlateau[k][l].sommetGrapheI][tabPlateau[k][l].sommetGrapheJ].sommetDansLeGrapheUsineEau == 1) {
                                                            CreerArete2(&Psommet2, tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau, &sommetPrec, nombreRoutePose);
                                                            //Psommet2 = Trier(Psommet2);
                                                            //SupprimerArete(&Psommet2,tabPlateau, i, j);
                                                            //Psommet2 = TrierDansLeBonSensDeLaPose(Psommet2);
                                                            //Parcourir(Psommet2, tabPlateau, i, j, compteurUsineEau, compteurUsineElec, numeroConneDeUsineEau, numeroConnexeDeUsineElec);
                                                            //afficher(Psommet2, tabPlateau, i, j);
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
                                                            //printf("1");
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 1;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 0;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j - NB_Cases_Place_UsineY-1) && (k != i-1) && (k != i+NB_Cases_Place_UsineX+1)){
                                                            //printf("2");
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 1;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((l == j+1) && (k != i-1) && (k != i+NB_Cases_Place_UsineY+1)){
                                                            //printf("3");
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 1;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        if ((k == i+NB_Cases_Place_UsineX+1) && (l != j - NB_Cases_Place_UsineY-1) && (l != j+1)){
                                                            //printf("4");
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineEau = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheUsineElec = 1;
                                                            tabPlateau[k][l].sommetDansLeGraphe = 0;
                                                            tabPlateau[k][l].sommetDansLeGrapheHab = 0;
                                                            tabPlateau[k][l].sommetGrapheI = k;
                                                            tabPlateau[k][l].sommetGrapheJ = l;

                                                        }
                                                        tabPlateau[k][l].tabMaisonAutourRoutes++;
                                                        if(tabPlateau[tabPlateau[k][l].sommetGrapheI][tabPlateau[k][l].sommetGrapheJ].sommetDansLeGrapheUsineElec == 1) {
                                                            CreerArete2(&Psommet2, tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[k][l].sommetGrapheI, tabPlateau[k][l].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau, &sommetPrec,nombreRoutePose);
                                                            //Psommet2 = Trier(Psommet2);
                                                            //SupprimerArete(&Psommet2,tabPlateau, i, j);
                                                            //Psommet2 = TrierDansLeBonSensDeLaPose(Psommet2);
                                                            //Parcourir(Psommet2, tabPlateau, i, j, compteurUsineEau, compteurUsineElec, numeroConneDeUsineEau, numeroConnexeDeUsineElec);
                                                            //afficher(Psommet2, tabPlateau, i, j);
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
                                //printf("%d %d\n", iHabPourAretes, jHabPourAretes);
                                ///
                                /*if(tabPlateau[tabPlateau[i][j].sommetGrapheI][tabPlateau[i][j].sommetGrapheJ].sommetDansLeGraphe == 1 || tabPlateau[tabPlateau[i][j].sommetGrapheI][tabPlateau[i][j].sommetGrapheJ].sommetDansLeGrapheHab == 1) {
                                CreerArete2(&Psommet2, tabPlateau[i][j].sommetGrapheI, tabPlateau[i][j].sommetGrapheJ, premierSommeti, premierSommetj,TrouverNumeroCase(tabPlateau[i][j].sommetGrapheI, tabPlateau[i][j].sommetGrapheJ),TrouverNumeroCase(premierSommeti, premierSommetj), tabMArque,tabPlateau);
                                Psommet2 = Trier(Psommet2);
                                SupprimerArete(&Psommet2,tabPlateau, i, j);
                                afficher(Psommet2, tabPlateau, i, j);
                                }*/

                            }
                            /// mode bat
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 500 && event.mouse.y < 550){
                                clickCarreBleu = TRUE;
                                choixCarreRoute = FALSE;
                                affichageElec = FALSE;
                                affichageEau = FALSE;
                                affichageRoute = TRUE;
                                choixUsineEau = FALSE,
                                choixUsineElec = FALSE;
                            }
                            /// Quitter le mode choix des bat et routes
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 700 && event.mouse.y < 750){
                                clickCarreBleu = FALSE;
                                choixCarreRoute = FALSE;
                                affichageElec = FALSE;
                                affichageEau = FALSE;
                                affichageRoute = TRUE;
                                choixUsineEau = FALSE,
                                choixUsineElec = FALSE;
                            }
                            /// mode route
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 400 && event.mouse.y < 450){
                                choixCarreRoute = TRUE;
                                affichageRoute = TRUE;
                                clickCarreBleu = FALSE;
                                affichageElec = FALSE;
                                affichageEau = FALSE;
                                choixUsineEau = FALSE,
                                choixUsineElec = FALSE;
                            }
                            /// choix carre eau vert
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 570 && event.mouse.y < 620){
                                choixCarreRoute = FALSE;
                                affichageRoute = TRUE;
                                clickCarreBleu = FALSE;
                                affichageElec = FALSE;
                                affichageEau = FALSE;
                                choixUsineEau = TRUE;
                                choixUsineElec = FALSE;
                            }
                            /// choix carre ele noir
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 630 && event.mouse.y < 680){
                                choixCarreRoute = FALSE;
                                affichageRoute = TRUE;
                                clickCarreBleu = FALSE;
                                affichageElec = FALSE;
                                affichageEau = FALSE;
                                choixUsineEau = FALSE,
                                choixUsineElec = TRUE;
                            }
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 100 && event.mouse.y < 150){
                                affichageRoute = FALSE;
                                affichageElec = FALSE;
                                affichageEau = TRUE;
                                choixUsineEau = FALSE,
                                choixUsineElec = FALSE;
                                al_draw_text(police, al_map_rgb(0,0,0), 100, 120, 0, "Niveau -1");
                            }
                            if(event.mouse.x > 20 && event.mouse.x < 70 && event.mouse.y > 200 && event.mouse.y < 250){
                                affichageRoute = FALSE;
                                affichageElec = TRUE;
                                affichageEau = FALSE;
                                choixUsineEau = FALSE,
                                choixUsineElec = FALSE;
                                al_draw_text(police, al_map_rgb(0,0,0), 100, 220, 0, "Niveau -2");
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
                    /*if(tabPlateau[premierSommeti+1][premierSommetj].routeOccupe == 0 && tabPlateau[premierSommeti-1][premierSommetj].routeOccupe == 0 && tabPlateau[premierSommeti][premierSommetj+1].routeOccupe == 0 && tabPlateau[premierSommeti][premierSommetj-1].routeOccupe == 0){
                        //numCompoConnexe++;
                        //tabPlateau[premierSommeti][premierSommetj].numeroCompoConnexe = numCompoConnexe;
                    }else*/
                    /*if(tabPlateau[premierSommeti+1][premierSommetj].routeOccupe == 1){
                        tabPlateau[premierSommeti+1][premierSommetj].numeroCompoConnexe = tabPlateau[premierSommeti][premierSommetj].numeroCompoConnexe;
                    }else if(tabPlateau[premierSommeti-1][premierSommetj].routeOccupe == 1){
                        tabPlateau[premierSommeti-1][premierSommetj].numeroCompoConnexe=tabPlateau[premierSommeti][premierSommetj].numeroCompoConnexe;
                    }else if(tabPlateau[premierSommeti][premierSommetj+1].routeOccupe == 1){
                        tabPlateau[premierSommeti][premierSommetj+1].numeroCompoConnexe = tabPlateau[premierSommeti][premierSommetj].numeroCompoConnexe ;
                    }else if(tabPlateau[premierSommeti][premierSommetj-1].routeOccupe == 1){
                        tabPlateau[premierSommeti][premierSommetj-1].numeroCompoConnexe=tabPlateau[premierSommeti][premierSommetj].numeroCompoConnexe;
                    }*/
                    for (int i = 0; i < NB_CASES; ++i) {
                        for (int j = 0; j < NB_CASES; ++j) {
                            if(tabPlateau[i][j].routeOccupe == 1) {
                                if (tabPlateau[i + 1][j].routeOccupe == 1 && tabPlateau[i + 1][j].numeroCompoConnexe > 0 && tabPlateau[i + 1][j].numeroCompoConnexe > tabPlateau[i][j].numeroCompoConnexe) {
                                    tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i + 1][j].numeroCompoConnexe;
                                } else if (tabPlateau[i - 1][j].routeOccupe == 1 && tabPlateau[i - 1][j].numeroCompoConnexe > 0 && tabPlateau[i - 1][j].numeroCompoConnexe > tabPlateau[i][j].numeroCompoConnexe) {
                                    //printf("%d\n", tabPlateau[i][j].numeroCompoConnexe);
                                    //printf("2 %d\n\n", tabPlateau[i-1][j].numeroCompoConnexe);
                                    tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i - 1][j].numeroCompoConnexe;
                                } else if (tabPlateau[i][j + 1].routeOccupe == 1 && tabPlateau[i][j+1].numeroCompoConnexe > 0 && tabPlateau[i][j+1].numeroCompoConnexe > tabPlateau[i][j].numeroCompoConnexe) {
                                    tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i][j + 1].numeroCompoConnexe;
                                } else if (tabPlateau[i][j - 1].routeOccupe == 1 && tabPlateau[i][j-1].numeroCompoConnexe > 0&& tabPlateau[i][j-1].numeroCompoConnexe > tabPlateau[i][j].numeroCompoConnexe) {
                                    tabPlateau[i][j].numeroCompoConnexe = tabPlateau[i][j - 1].numeroCompoConnexe;
                                }
                                Parcourir(Psommet2, tabPlateau, i, j, compteurUsineEau, compteurUsineElec, numeroConneDeUsineEau, numeroConnexeDeUsineElec);
                                //printf(" timer  : %d\n", tabPlateau[1][1].numeroCompoConnexe);
                                //printf("%d %d : %d\n", i, j, tabPlateau[i][j].numeroCompoConnexe);
                                //ajouterCompoConnexe(&Psommet2, tabPlateau, i, j);
                            }
                        }
                    }
                            changementCompoConnexe = FALSE;



                dessinerLeJeu(tabPlateau, tabBit, sourisDessusX, sourisDessusY, ligne, nbNombreBatPose,nbNombreUsineEauPose, nbNombreUsineElecPose,valeurSourisX, valeurSourisY, minutes, nbHabTotal, &eceFloos, clickCarreBleu,affichageRoute, affichageEau, affichageElec,choixUsineElec,choixUsineEau,RouteColleBat, timer, timer1sec, police, policePetite,RouteDroite, RouteDroite2, Tournant, Tournant2, Tournant3, Tournant4, DoubleTournant,DoubleTournant2, DoubleTournant3, DoubleTournant4, Croisement, TerrainVague, Maison1,Maison2, Maison3, Maison4, MapFond, NuageFond, Ruine, Immeuble, GratteCiel, Cabane,PieceMonnaie, Habitant, CentralElectrique, ChateauEau, CroixRouge);
                }
                break;
            }
        }
    }
}
