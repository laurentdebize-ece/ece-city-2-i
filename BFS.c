#include "BFS.h"
#include "Graphe.h"



int BFS(Sommet2 ** Psommet2, int nbbathab){ // prend en parametre le graphe (sous forme de liste d'adjacence) et le sommet initial

    int tabDistanceChateau[10][15];
    //premier indice : numéro chateau ,2e indice : numéro maison

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
        while (temp2 != NULL && temp2->marque !=1) {
            //on vérifie que l'on peut aller au sommet suivant

            while(temp2->typeUsineEau != 1){
                //on passe au sommet suivant tant que le sommet actuel n'est pas un chateau d'eau

                temp2->marque = 1;
                (*Psommet2)->distance++;
                temp2 = temp2->next;

            }
            //si le sommet actuel est un chateau d'eau, on note la distance dans le tableau qui recense toutes les distances de
            tabDistanceChateau[(temp2)->numeroChateau][j] = (*Psommet2)->distance;

        }
        //reset des marques avant de passer au sommet habitation suivant
        while(temp1->next->marque != 0){
            temp1->marque = 0;
            temp1 = temp1->next;
        }

    }
    //faire une fonction qui trie les distances
    return 0;
}
