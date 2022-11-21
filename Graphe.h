#include <stdio.h>
#include <stdlib.h>
#include "map.h"


struct Arc {
    int i_sommet;
    int j_sommet;
    int poids;
    struct Arc* arc_suivant;
};

typedef struct Arc* pArc;

struct Sommet {
    struct Arc* arc;
    int valeur, marque, pred;
    int type;
};

typedef struct Sommet* pSommet;

typedef struct Graphe {
    int orientation;
    int ordre;
    pSommet* pSommet;
} Graphe;


Graphe* creerGraphe(int ordre);
pSommet* CreerArete(pSommet* sommet, int i, int j, int i_bis, int j_bis);
void check_relier_cases(Graphe* g, int i_constant, int j_constant, int i, int j, int i_bis, int j_bis, bool pose_de_route, Construction* tab_constru);
