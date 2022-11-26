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







int BFS(Sommet2 ** Psommet2, int nbbathab){ // prend en parametre le graphe (sous forme de liste d'adjacence) et le sommet initial

    int tabDistanceChateau[10][15];
    //premier indice : numéro chateau ,2e indice : numéro maison

    bool end = false;

    //On met la distance de tous les sommet habitation à 0 :
    Sommet2* temp1 = *Psommet2;
    while(temp1->next != NULL){
        if(temp1->typeHab == 1){
            temp1->distance = 0;
        }
        temp1 = temp1->next;
    }



    for(int j=0; j <nbbathab; j++){ //effectue pour chaque habitation le calcul de distance
        Sommet2* temp2 = *Psommet2;
        while(!end){
            while (temp2 != NULL) {
                while(temp2->typeUsineEau != 1){
                    if(temp2->marque !=1){
                        temp2->marque = 1;
                        (*Psommet2)->distance++;
                        temp2 = temp2->next;
                    }
                    end = true;

                    //à la sortie ajouter l'association de la distance au chateau en question


                }
                //trouver comment obtenir le numéro du chateau pour tabDistanceChateau[10][j];
                tabDistanceChateau[(temp2)->numeroChateau][j] = (*Psommet2)->distance;


            }
        }
        //reset des marques
        while(temp1->next->marque != 0){
            temp1->marque = 0;
            temp1 = temp1->next;
        }


    }

    return 0;
}
