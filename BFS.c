#include "BFS.h"
#include "Graphe.h"

void enfiler(t_file *f,int num){
    t_maillon* tmp= malloc(sizeof(t_maillon));
    tmp->num=num;
    tmp->suiv=NULL;

    if(f->tete==NULL){
        f->tete=tmp;
        f->fin=tmp;
    }
    else{
        f->fin->suiv=tmp;
        f->fin=tmp;

    }

}

int defiler(t_file *f){

    t_maillon* tmp=f->tete;
    if(f->tete == f->fin){
        f->fin=NULL;
        f->tete=NULL;
    }
    else {
        f->tete = f->tete->suiv;
    }
    int num= tmp->num;
    free(tmp);

    return num;
}







int BFS(Graphe* g,int s0, Sommet2 ** Psommet2, int nbhab)// prend en parametre le graphe (sous forme de liste d'adjacence) et le sommet initial
{
    int tabDistanceChateau[10][15];
    //premier indice : numéro chateau ,2e indice : numéro maison

    while((*Psommet2)->next != NULL){
        if((*Psommet2)->typeHab == 1){
            (*Psommet2)->distance = 0;
        }
        (*Psommet2) = (*Psommet2)->next;
    }

    //BFS
    t_file f;
    f.tete = f.fin = NULL;

    for (int i = 0; i < g->ordre; i++) {
        g->pSommet[i]->couleur = 0;
    }



    enfiler(&f, s0);

    g->pSommet[s0]->couleur = 1;
    for(int i=0; i <nbhab; i++){ //effectue pour chaque habitation le calcul de distance
        while (f.tete != NULL) {
            int num = defiler(&f);
            struct Arc *temp = g->pSommet[num]->arc;
            while (temp != NULL) {
                while((*Psommet2)->typeUsineEau != 1){

                    //possiblement devoir créer un tableau de chateau avec dans chaque case son pointeur
                    //à la sortie ajouter l'association de la distance au chateau en question

                    //on récupère le numéro du sommet
                    // vers lequel conduit l'arc
                    int num2 = temp->sommet;
                    //si ce sommet n'est pas marqué
                    if (g->pSommet[num2]->couleur == 0) {
                        //? on l'enfile
                        enfiler(&f, num2);
                        //? on le marque
                        g->pSommet[num2]->couleur = 1;

                        (*Psommet2)->distance++;

                        temp = temp->arc_suivant;
                    }
                }
                //trouver comment obtenir le numéro du chateau pour tabDistanceChateau[10][i];
                //tabDistanceChateau[(*Psommet2)->numeroChateau][i] = (*Psommet2)->distance;
                temp = temp->arc_suivant;

            }
        }
    }

    for (int i = 0; i < g->ordre; i++) {
        g->pSommet[i]->debut=0;
        g->pSommet[i]->finxplo=0;
        g->pSommet[i]->connexe=-1;
    }

    for (int i = 0; i < g->ordre; i++) {
        g->pSommet[i]->couleur = 0;
    }



    return 0;
}
