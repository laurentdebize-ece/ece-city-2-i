#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "Graphe.h"
#include "File.h"


void enfiler(t_file* f, int sommet) {
    t_maillon* sommet_enfile = NULL;
    sommet_enfile = (t_maillon*) malloc(sizeof(t_maillon));
    sommet_enfile->num = sommet;
    sommet_enfile->suiv = NULL;
    if(f->fin == NULL && f->tete == NULL) {
        f->tete = f->fin = sommet_enfile;
    } else {
        sommet_enfile->suiv = f->tete;   //pour DFS : sommet_enfile->suiv = f->tete;
        f->tete = sommet_enfile;         //f->tete = sommet_enfile;
    }
}


int defiler(t_file* f) {
    int element;
    t_maillon* sortie = f->tete;
    element = sortie->num;
    if(f->tete == f->fin) {
        f->tete = f->fin = NULL;
    } else {
        f->tete = f->tete->suiv;
    }
    free(sortie);
    return element;
}


void parcours_profondeur(Graphe** g, t_file* f, int sommet_init, int* sommet_a_explorer, Construction** tab_constru) {

    enfiler(f, sommet_init);
    (*g)->pSommet[sommet_init]->marque = 1;
    while(f->tete) {
        *sommet_a_explorer = defiler(f);
        pArc temps = (*g)->pSommet[*sommet_a_explorer]->arc;

        while(temps) {

            if(temps) {
                tab_constru[*sommet_a_explorer]->viable = true;
                tab_constru[temps->i_sommet*COLONNES + temps->j_sommet]->viable = true;

                while(temps && ((*g)->pSommet[temps->i_sommet*COLONNES + temps->j_sommet]->marque != 0)) {
                    temps = temps->arc_suivant;
                }
            }
            if(temps) {
                enfiler(f, (temps->i_sommet*COLONNES + temps->j_sommet));
                (*g)->pSommet[temps->i_sommet*COLONNES + temps->j_sommet]->marque = 1;
                (*g)->pSommet[temps->i_sommet*COLONNES + temps->j_sommet]->pred = *sommet_a_explorer;
                temps = temps->arc_suivant;
            }
        }
        printf("%d ", (*g)->pSommet[*sommet_a_explorer]->valeur);
        (*g)->pSommet[*sommet_a_explorer]->marque = 2;
    }
}

void recherche_compo_connexes(Graphe** g, t_file* f, int* sommet_a_explorer, Construction** tab_constru) {
    for(int i = 0; i < (*g)->ordre; i++) {
        while ((*g)->pSommet[i]->marque != 2) {
            parcours_profondeur(g, f, i, sommet_a_explorer, tab_constru);
            printf("\n");
        }
    }
}


void viabilite(Graphe* g, int sommet_init, Construction* tab_constru) {
    t_file f;
    f.tete = f.fin = NULL;
    for(int i = 0; i < g->ordre; i++) {
        g->pSommet[i]->marque = 0;
        g->pSommet[i]->pred = -1;
    }

    recherche_compo_connexes(&g, &f, &sommet_init, &tab_constru);

    printf("\n");
}
