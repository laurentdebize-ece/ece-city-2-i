#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#define TUILE_LARGEUR_ISO 24
#define TUILE_HAUTEUR_ISO 12
#define LIGNES 35
#define COLONNES 45
#define DEBUT_X 430
#define DEBUT_Y 50

typedef struct {
    int x, y;
    int occupee;
    int id_bat_pose;
    int type;
} Case;

typedef struct {
    float x, y;
} Point;

typedef struct {
    float x, y;
} Vecteur;

typedef struct {
    Point O;
    Point I;
    Point J;
} Repere;

typedef struct {
    int pos_x, pos_y;
    int type;
    int nb_cases_largeur, nb_cases_hauteur;
    bool viable;
} Construction;

typedef struct {
    int monnaie, nb_habitants, capa_eau, capa_elec;
} Donnees_globales;

Case tab[LIGNES][COLONNES];

void afficherGrille();
int collision_iso_i(Point O, Point A, Point B, float x, float y);
int collision_iso_j(Point O, Point A, Point B, float x, float y);
void draw_cases_route(Construction* tab_constru, int z);
void draw_cases_centrale(Construction* tab_constru, int z);
void draw_cases_maison(Construction* tab_constru, int z);
void init_mairie(Donnees_globales* mairie);
