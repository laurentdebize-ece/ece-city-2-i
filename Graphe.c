#include "Graphe.h"
#include "File.h"


pSommet* CreerArete(pSommet* sommet, int i, int j, int i_bis, int j_bis) {

    if(sommet[i*COLONNES + j]->arc == NULL) {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->i_sommet = i_bis;
        Newarc->j_sommet = j_bis;
        Newarc->arc_suivant = NULL;
        sommet[i*COLONNES + j]->arc = Newarc;
    }
    else {
        pArc temp = sommet[i*COLONNES + j]->arc;
        while(temp->arc_suivant != NULL) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->i_sommet = i_bis;
        Newarc->j_sommet = j_bis;
        Newarc->arc_suivant = NULL;

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


void check_relier_cases(Graphe* g, int i_constant, int j_constant, int i , int j, int i_bis, int j_bis, bool pose_de_route, Construction* tab_constru) {
    if(i_bis+i >= 0 && i_bis+i <= 34 && j_bis+j >= 0 && j_bis+j <= 44) {
        if((pose_de_route && tab[i_bis+i][j_bis+j].occupee == 1) || (tab[i_bis+i][j_bis+j].type == 0)) {

            g->pSommet = CreerArete(g->pSommet, i_constant+i, j_constant+j, i_bis+i, j_bis+j);
            g->pSommet = CreerArete(g->pSommet, i_bis+i, j_bis+j, i_constant+i, j_constant+j);

            //printf("\n%d | %d %d\n", g->pSommet[(i_constant+i)*COLONNES + j_constant+j]->valeur, g->pSommet[(i_constant+i)*COLONNES + j_constant+j]->arc->i_sommet, g->pSommet[i_constant+i*COLONNES + j_constant+j]->arc->j_sommet);

            tab_constru[i_constant*COLONNES + j_constant].viable = true;
            tab_constru[(i_bis+i)*COLONNES + j_bis+j].viable = true;

            /*for(int a = 0; a <LIGNES; a++) {
                for (int b = 0; b < COLONNES; b++) {
                    if(tab[a][b].id_bat_pose == tab[i_constant+i][j_constant+j].id_bat_pose) {
                        tab_constru[a*COLONNES + b].viable = true;
                    }
                    if(tab[a][b].id_bat_pose == tab[i_bis+i][j_bis+j].id_bat_pose) {
                        tab_constru[i_bis*COLONNES + j_bis].viable = true;
                    }

                }
            }*/
        }
    }
}
