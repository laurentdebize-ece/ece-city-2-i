#include "Initialisation.h"

void initialiser(Cases tabPlateau[NB_CASES][NB_CASES],Bitmap tabBit[NB_MAX_BAT]){
    int compteur = 0;
    int compteur2 = 0;
    int numero = 0;
    int ajoutX = 0;
    int ajoutY = 0;

    for (int i = 0; i < NB_MAX_BAT; ++i) {
        tabBit[i].batPose = 0;
        tabBit[i].changementBatBloque = 0;
    }

    for (int i = 0; i < NB_CASES; ++i) {
        for (int j = 0; j < NB_CASES; ++j) {
            tabPlateau[i][j].x1 = X_DEPART+ (compteur2 * LARGEUR_CASE);
            tabPlateau[i][j].y1 = Y_DEPART+ (compteur * HAUTEUR_CASE);
            tabPlateau[i][j].numeroCase = numero+1;
            tabPlateau[i][j].occupe = 0;
            tabPlateau[i][j].routeOccupe = 0;
            compteur++;
            numero++;
            tabPlateau[i][j].joueurSurCase = 0;
        }
        compteur2++;
        compteur = 0;
        ajoutX += LARGEUR_CASE;
        ajoutY += HAUTEUR_CASE;
    }
}
