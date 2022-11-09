#include "jeu.h"





int main(){
    Player tabPlayer[NBJOUEURMAX];
    Cases tabPlateau[NB_CASES][NB_CASES];
    int finDuJeu = 0;
    int nbJoueur = 0;
    int iPosDepart = 0;
    int jPosDepart = 0;
    PosDepart tabPosDepart[NBJOUEURMAX];
    while(finDuJeu == 0) {
        nbJoueur = 0;
        jeuPrincipale(tabPlayer, nbJoueur, &finDuJeu, tabPosDepart);
    }

    return 0;
}

