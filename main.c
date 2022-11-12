#include "jeu.h"


int main(){
    int finDuJeu = 0;
    jeuPrincipale(&finDuJeu);
    return 0;
}

//le graphe est une liste d'adjascence : donc chaque sommet est repéré par graphe->pSommet[numero du sommet]
//numero du sommet est trouvé par l'indice : (i*NBCOLONNES + j)      avec i l'indice de la ligne dans notre grille et j l'indice de la colonne
//chaque case de notre matrice est un sommet 
//un sommet est relié seulement si l'une des cases collées a lui est une route : dans ce cas on créé une arete entre les deux
//toutes les routes qui sont collées sont reliées dans notre graphe
