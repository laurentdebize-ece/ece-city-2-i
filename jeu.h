#ifndef ECE_CITY_2_I_JEU_H
#define ECE_CITY_2_I_JEU_H

#include "Affichage.h"
#include "Initialisation.h"
//#include "map.h"
#include "Graphe.h"

void jeuPrincipale(int* finDuJeu);
int TrouverNumeroCase(int iCase, int jCase);
void ComposanteConnexeDuGraphe(Cases tabPlateau[NB_CASES][NB_CASES], Sommet2* Psommet2,bool compteurUsineEau,bool compteurUsineElec, int numeroConneDeUsineEau, int numeroConnexeDeUsineElec);
void SourisSurCase(Cases tabPlateau[NB_CASES][NB_CASES], int* valeurSourisX, int* valeurSourisY, int* sourisDessusX, int* sourisDessusY, ALLEGRO_EVENT event);
void RegarderCaseAutour(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int comptbitmap1, int* nbBatAutourDesRoutes, ALLEGRO_TIMER* timer, int i, int j);
void choixModes(ALLEGRO_EVENT event, bool* clickCarreBleu, bool* choixCarreRoute, bool* affichageElec, bool* affichageEau, bool* affichageRoute, bool* choixUsineEau, bool* choixUsineElec, ALLEGRO_FONT* police);


#endif
