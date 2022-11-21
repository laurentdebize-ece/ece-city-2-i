#include "Graphe.h"



pSommet* CreerArete(pSommet* sommet, int i, int j, int i_bis, int j_bis, int numeroCase, int numeroCaseARelie) {

    if(sommet[numeroCase]->arc == NULL) {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->i_sommet = i_bis;
        Newarc->j_sommet = j_bis;
        Newarc->sommet = numeroCase;
        Newarc->arc_suivant = NULL;
        sommet[numeroCase]->arc = Newarc;
    }
    else {
        pArc temp = sommet[numeroCase]->arc;
        while(temp->arc_suivant != NULL) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->i_sommet = i_bis;
        Newarc->j_sommet = j_bis;
        Newarc->arc_suivant = NULL;
        Newarc->sommet = numeroCaseARelie;
        temp->arc_suivant = Newarc;
    }
    return sommet;
}

Graphe* creerGraphe(int ordre) {
    Graphe* Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i = 0; i < ordre; i++) {
        Newgraphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }

    Newgraphe->ordre = ordre;

    return Newgraphe;
}


void check_relier_cases(Graphe* g, int i_constant, int j_constant, int i , int j, int i_bis, int j_bis, bool pose_de_route, Construction* tab_constru, Cases tab[COLONNES][COLONNES]) {
    if(i_bis+i >= 0 && i_bis+i <= 34 && j_bis+j >= 0 && j_bis+j <= 44) {
        if((pose_de_route && tab[i_bis+i][j_bis+j].occupe == 1) || (tab[i_bis+i][j_bis+j].type == 0)) {
            //g->pSommet = CreerArete(g->pSommet, i_constant+i, j_constant+j, i_bis+i, j_bis+j);
            //g->pSommet = CreerArete(g->pSommet, i_bis+i, j_bis+j, i_constant+i, j_constant+j);

            tab_constru[i_constant*COLONNES + j_constant].viable = true;
            tab_constru[(i_bis+i)*COLONNES + j_bis+j].viable = true;
            tab[i_constant-1][j_constant].viable = 1;
            tab[i_constant+1][j_constant].viable = 1;
            tab[i_constant][j_constant+1].viable = 1;
            tab[i_constant][j_constant-1].viable = 1;


        }
    }
}
