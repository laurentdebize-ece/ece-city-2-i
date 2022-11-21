#ifndef ECE_CITY_2_I_GRAPHE_H
#define ECE_CITY_2_I_GRAPHE_H
#include <stdio.h>
#include <stdlib.h>
//#include "map.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#define TUILE_LARGEUR_ISO 24
#define TUILE_HAUTEUR_ISO 12
#define LIGNES 35
#define COLONNES 45
#define DEBUT_X 500
#define DEBUT_Y 60
//#include "Affichage.h"


struct Arc {
    int i_sommet;
    int j_sommet;
    int poids;
    int sommet;
    struct Arc* arc_suivant;
};

typedef struct Arc* pArc;

struct Sommet {
    struct Arc* arc;
    int valeur, marque, pred;
};

typedef struct Sommet* pSommet;

typedef struct Graphe {
    int orientation;
    int ordre;
    pSommet* pSommet;
} Graphe;

typedef struct {
    int occupe;
    int routeOccupe;
    int occupBat;
    int type;
    int id_bat_pose;
    //pointeur personnage
    int x1, x2, y1, y2;
    int numeroCase;
    int numeroJoueur;
    int joueurSurCase;
    int viable;
    int valeurCompteurAuClic;
}Cases;

typedef struct {
    int x, y;
    int occupee;
    int id_bat_pose;
    int type;
} Case;

typedef struct {
    float x, y;
} Point;

typedef struct {
    float x, y;
} Vecteur;

typedef struct {
    Point O;
    Point I;
    Point J;
} Repere;

typedef struct {
    int pos_x, pos_y;
    int type;
    int nb_cases_largeur, nb_cases_hauteur;
    bool viable;
} Construction;

typedef struct {
    int monnaie, nb_habitants, capa_eau, capa_elec;
} Donnees_globales;

Graphe* creerGraphe(int ordre);
pSommet* CreerArete(pSommet* sommet, int i, int j, int i_bis, int j_bis, int numeroCase, int numeroCaseARelie);
void check_relier_cases(Graphe* g, int i_constant, int j_constant, int i , int j, int i_bis, int j_bis, bool pose_de_route, Construction* tab_constru, Cases tab[COLONNES][COLONNES]);
#endif
