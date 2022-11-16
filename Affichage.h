#ifndef ECE_CITY_2_I_AFFICHAGE_H
#define ECE_CITY_2_I_AFFICHAGE_H
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define HAUTEUR_FE 830
#define LARGEUR_FE 1436
#define NBJOUEURMAX 4
#define X_DEPART 500
#define Y_DEPART 60
#define NB_CASES 45
#define NB_CASESY 35
#define LARGEUR_CASE 20
#define HAUTEUR_CASE 20
#define NB_MAX_BAT 30
#define NB_Cases_Place_ConstruX 2
#define NB_Cases_Place_ConstruY 2
#define TEMPS_DE_CONSTRUCTION 700        /// Pour 15 sec : 1850
#define PMMax 3


#define TRIANGLE_MILIEU_DROIT_X X_DEPART + LARGEUR_CASE
#define TRIANGLE_MILIEU_DROIT_Y Y_DEPART + HAUTEUR_CASE
#define TRIANGLE_MILIEU_GAUCHE_X X_DEPART - LARGEUR_CASE
#define TRIANGLE_MILIEU_GAUCHE_Y Y_DEPART + HAUTEUR_CASE
#define TRIANGLE_BAS_Y Y_DEPART + 2*HAUTEUR_CASE


typedef struct {
    int x, y, largeur, hauteur, vitesse;
    ALLEGRO_COLOR couleur;
} Rect;

typedef struct {
    float x1, x2,x3, y1, y2, y3;
}Triangle;

typedef struct {
    int i, j;
}PosDepart;

typedef struct {
    int posX, posY, indiceJoueur;
    ALLEGRO_COLOR color;
    int iDeLaCase, jDeLaCase;
    int Classe, PV, PA, PM;
    int numeroJoueur;
    ALLEGRO_BITMAP* Personnage;
    ALLEGRO_BITMAP* AniPerso;
    ALLEGRO_BITMAP* BitClassement;
    ALLEGRO_BITMAP* Grande;
    int numeroBitmap;
    int enJeu;
    int PositionClassement;
}Player;

typedef struct {
    ALLEGRO_BITMAP* Bitamp1;
    int batPose;
    int valeurCompteurAuClic;
    int empecherDeRentrerPlusieursFoisDAnsLaBoucle;
    int timerPasAfficherSansArret;
    int changemetnBat;
    int chance1sur4;
    int nbHabitant;
    int changementBatBloque;
    bool incendie;
    int i, j;
}Bitmap;

typedef struct {
    int sortDeSoin;
    int lanceeDepee;
    int lianedefeu;
    int coupDepee;
}DegatSortClasse1;

typedef struct {
    int sortDeSoin;
    int lanceeDepee;
    int lianedefeu;
    int coupDepee;
}PASortClasse1;

typedef struct {
    DegatSortClasse1 degatSortClasse1;
    PASortClasse1 paSortClasse1;
    int numeroJoueur;
}Classe1;

typedef struct {
    int bouleDeFeu;
    int nuageDeFeu;
    int griffe;
    int coupDeBalai;
}DegatSortClasse2;

typedef struct {
    int bouleDeFeu;
    int nuageDeFeu;
    int griffe;
    int coupDeBalai;
}PASortClasse2;

typedef struct {
    DegatSortClasse2 degatSortClasse2;
    PASortClasse2 paSortClasse2;
    int numeroJoueur;
}Classe2;

typedef struct {
    int tornade;
    int poison;
    int nuageDeFeu;
    int coupDepee;
}DegatSortClasse3;

typedef struct {
    int tornade;
    int poison;
    int nuageDeFeu;
    int coupDepee;
}PASortClasse3;

typedef struct {
    DegatSortClasse3 degatSortClasse3;
    PASortClasse3 paSortClasse3;
    int numeroJoueur;
}Classe3;

typedef struct {
    int fleche;
    int flecheEmflamme;
    int sortDeSoin;
    int coupDeMasse;
}DegatSortClasse4;

typedef struct {
    int fleche;
    int flecheEmflamme;
    int sortDeSoin;
    int coupDeMasse;
}PASortClasse4;

typedef struct {
    DegatSortClasse4 degatSortClasse4;
    PASortClasse4 paSortClasse4;
    int numeroJoueur;
}Classe4;


typedef struct {
    int occupe;
    int routeOccupe;
    int occupBat;
    //pointeur personnage
    int x1, x2, y1, y2;
    int numeroCase;
    int numeroJoueur;
    int joueurSurCase;
    int valeurCompteurAuClic;
}Cases;

typedef struct {
    float ligneX1, ligneX2, ligneY1, ligneY2;
}Ligne;

typedef struct {
    int x,y;
}Deplacement;

Classe1 classe1;
Classe2 classe2;
Classe3 classe3;
Classe4 classe4;

void drawLine(Ligne lignes, int x, int y);
bool incendie(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int k);
void dessinerLeJeu(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int sourisDessusX, int sourisDessusY, Ligne ligne, int nbNombreBatPose, int valeurSourisX, int valeurSourisY, int minutes,int* nbHabTotal, int* ecefloos,bool clickCarreBleu, bool affichageRoute, bool affichageEau, bool affichageElec, ALLEGRO_TIMER* timer, ALLEGRO_TIMER* timer1sec, ALLEGRO_FONT* police,ALLEGRO_FONT* policePetite, ALLEGRO_BITMAP* RouteDroite, ALLEGRO_BITMAP* RouteDroite2, ALLEGRO_BITMAP* Tournant, ALLEGRO_BITMAP* Tournant2, ALLEGRO_BITMAP* Tournant3, ALLEGRO_BITMAP* Tournant4, ALLEGRO_BITMAP* DoubleTournant, ALLEGRO_BITMAP* DoubleTournant2, ALLEGRO_BITMAP* DoubleTournant3, ALLEGRO_BITMAP* DoubleTournant4, ALLEGRO_BITMAP* Croisement, ALLEGRO_BITMAP* TerrainVague, ALLEGRO_BITMAP* Maison1, ALLEGRO_BITMAP* Maison2, ALLEGRO_BITMAP* Maison3, ALLEGRO_BITMAP* Maison4, ALLEGRO_BITMAP* MapFond, ALLEGRO_BITMAP* NuageFond, ALLEGRO_BITMAP* Ruine, ALLEGRO_BITMAP* Immeuble, ALLEGRO_BITMAP* GratteCiel, ALLEGRO_BITMAP* Cabane, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* Habitant);

#endif
