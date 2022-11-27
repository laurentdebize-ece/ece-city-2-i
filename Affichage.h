#ifndef ECE_CITY_2_I_AFFICHAGE_H
#define ECE_CITY_2_I_AFFICHAGE_H

//#include "jeu.h"
#include "Graphe.h"


#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define LARGEUR 1920
#define HAUTEUR 1080

#define HAUTEUR_FE 830
#define LARGEUR_FE 1436
#define NBJOUEURMAX 4
#define X_DEPART 500
#define Y_DEPART 60
#define NB_CASES 45
#define NB_CASESY 35
#define LARGEUR_CASE 20
#define HAUTEUR_CASE 20
#define NB_MAX_BAT 30
#define NB_Cases_Place_ConstruX 2
#define NB_Cases_Place_ConstruY 2
#define NB_Cases_Place_UsineX 5
#define NB_Cases_Place_UsineY 3
#define TEMPS_DE_CONSTRUCTION 100///50///700        /// Pour 15 sec : 1850
#define TEMPS_DE_CONSTRUCTION2 200



typedef struct {
    ALLEGRO_BITMAP* Bitamp1;
    int batPose;
    int UsineEauPose;
    int UsineElecPose;
    int valeurCompteurAuClic;
    int empecherDeRentrerPlusieursFoisDAnsLaBoucle;
    int timerPasAfficherSansArret;
    int changemetnBat;
    int chance1sur4;
    int nbHabitant;
    int changementBatBloque;
    bool incendie;
    int i, j;
}Bitmap;




typedef struct {
    float ligneX1, ligneX2, ligneY1, ligneY2;
}Ligne;



void drawLine(Ligne lignes, int x, int y);
void drawFondEtCases(ALLEGRO_BITMAP* NuageFond, ALLEGRO_BITMAP* MapFond);
void dessinerRoutes(Cases tabPlateau [NB_CASES][NB_CASES], ALLEGRO_BITMAP* RouteDroite, ALLEGRO_BITMAP* RouteDroite2, ALLEGRO_BITMAP* Tournant, ALLEGRO_BITMAP* Tournant2, ALLEGRO_BITMAP* Tournant3, ALLEGRO_BITMAP* Tournant4, ALLEGRO_BITMAP* DoubleTournant, ALLEGRO_BITMAP* DoubleTournant2, ALLEGRO_BITMAP* DoubleTournant3, ALLEGRO_BITMAP* DoubleTournant4, ALLEGRO_BITMAP* Croisement, ALLEGRO_TIMER* timer, ALLEGRO_FONT* police, ALLEGRO_FONT* policePetite, bool affichageRoute, bool affichageEau, bool affichageElec);
void drawMaison(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int nbNombreBatPose, bool affichageEau, bool affichageElec, ALLEGRO_TIMER* timer, ALLEGRO_FONT* policePetite,ALLEGRO_BITMAP* TerrainVague, ALLEGRO_BITMAP* Maison1, ALLEGRO_BITMAP* Maison2, ALLEGRO_BITMAP* Maison3, ALLEGRO_BITMAP* Maison4, ALLEGRO_BITMAP* Ruine, ALLEGRO_BITMAP* Immeuble, ALLEGRO_BITMAP* GratteCiel, ALLEGRO_BITMAP* Cabane, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* Habitant, ALLEGRO_BITMAP* CentralElectrique, ALLEGRO_BITMAP* ChateauEau, ALLEGRO_BITMAP* CroixRouge);
void drawUsineEau(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT],  ALLEGRO_TIMER* timer, ALLEGRO_FONT* policePetite, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* ChateauEau, int k);
void drawUsineElec(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT],  ALLEGRO_TIMER* timer, ALLEGRO_FONT* policePetite, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* CentralElectrique, int k);
void BoiteAOutilEtTimer(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int sourisDessusX, int sourisDessusY, int nbNombreBatPose, int valeurSourisX, int valeurSourisY, int minutes,int* nbHabTotal,int* ecefloos ,bool clickCarreBleu,bool choixUsineElec, bool choixUsineEau, ALLEGRO_TIMER* timer, ALLEGRO_TIMER* timer1sec, ALLEGRO_FONT* police, ALLEGRO_BITMAP* TerrainVague, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* Habitant, ALLEGRO_BITMAP* CentralElectrique, ALLEGRO_BITMAP* ChateauEau, ALLEGRO_BITMAP* eau, ALLEGRO_BITMAP* eclair, ALLEGRO_BITMAP* construction ,ALLEGRO_BITMAP* route2,ALLEGRO_BITMAP* caserne,ALLEGRO_BITMAP* barreoutil, ALLEGRO_BITMAP* chateau);
bool CasesViableAutourDesHabitationBis(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int i, int j);
bool CasesViableAutourDesHabitation(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int i, int j);
bool incendie(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int k);
void dessinerLeJeu(Cases tabPlateau[NB_CASES][NB_CASES], Bitmap tabBit[NB_MAX_BAT], int sourisDessusX, int sourisDessusY, Ligne ligne, int nbNombreBatPose,int nbNombreUsineEauPose,int nbNombreUsineElecPose, int valeurSourisX, int valeurSourisY, int minutes,int* nbHabTotal, int* ecefloos,bool clickCarreBleu, bool affichageRoute, bool affichageEau, bool affichageElec,bool choixUsineElec, bool choixUsineEau,bool RouteColleBat,  ALLEGRO_TIMER* timer, ALLEGRO_TIMER* timer1sec, ALLEGRO_FONT* police,ALLEGRO_FONT* policePetite, ALLEGRO_BITMAP* RouteDroite, ALLEGRO_BITMAP* RouteDroite2, ALLEGRO_BITMAP* Tournant, ALLEGRO_BITMAP* Tournant2, ALLEGRO_BITMAP* Tournant3, ALLEGRO_BITMAP* Tournant4, ALLEGRO_BITMAP* DoubleTournant, ALLEGRO_BITMAP* DoubleTournant2, ALLEGRO_BITMAP* DoubleTournant3, ALLEGRO_BITMAP* DoubleTournant4, ALLEGRO_BITMAP* Croisement, ALLEGRO_BITMAP* TerrainVague, ALLEGRO_BITMAP* Maison1, ALLEGRO_BITMAP* Maison2, ALLEGRO_BITMAP* Maison3, ALLEGRO_BITMAP* Maison4, ALLEGRO_BITMAP* MapFond, ALLEGRO_BITMAP* NuageFond, ALLEGRO_BITMAP* Ruine, ALLEGRO_BITMAP* Immeuble, ALLEGRO_BITMAP* GratteCiel, ALLEGRO_BITMAP* Cabane, ALLEGRO_BITMAP* PieceMonnaie, ALLEGRO_BITMAP* Habitant, ALLEGRO_BITMAP* CentralElectrique, ALLEGRO_BITMAP* ChateauEau,  ALLEGRO_BITMAP* CroixRouge);


#endif
