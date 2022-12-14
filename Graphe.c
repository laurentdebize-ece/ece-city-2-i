#include "Graphe.h"
/*
int TrouverNumeroCase(int iCase, int jCase){
    int numeroCase = iCase + jCase*COLONNES;
    return numeroCase;
}*/

void ajouterCompoConnexe(Sommet2** sommet, Cases tabPlateau[COLONNES][COLONNES], int i, int j){
    Sommet2** m = sommet;
    while (*m != NULL){
        (*sommet)->numeroCompoConnexe = tabPlateau[i][j].numeroCompoConnexe;
        (*m) = (*m)->next;
    }
}

void Parcourir(Sommet2 * m, Cases tabPlateau[COLONNES][COLONNES], int i, int j, int compteurUsineEau, int compteurUsineElec, int numConnexeUsineEAu, int numConnexeUsineElec){
    Sommet2* temp = m;
    while (m != NULL){

        if(m->typeUsineEau == 1){
            compteurUsineEau = 1;
            numConnexeUsineEAu = tabPlateau[m->i][m->j].numeroCompoConnexe;
            //printf("1\n");
        }
        if(m->typeUsineElec == 1){
            compteurUsineElec = 1;
            numConnexeUsineElec = tabPlateau[m->i][m->j].numeroCompoConnexe;
            //printf("2\n");
        }

        m = m->next;
    }
    if(compteurUsineEau >= 1 && compteurUsineElec >= 1 && tabPlateau[i] && numConnexeUsineEAu == numConnexeUsineElec){
        //printf("(");
        while (temp != NULL){
            if(tabPlateau[temp->i][temp->j].numeroCompoConnexe == numConnexeUsineElec) {
                tabPlateau[temp->i][temp->j].viable = 1;
            }
            temp = temp->next;
        }
    }
}

void SupprimerArete(Sommet2** sommet,Cases tabPlateau[COLONNES][COLONNES], int i, int j){
    /// Sert a remplacer le type de la route devant une maison (elle passe de type route a type maison)
    Sommet2* temp = NULL;
    Sommet2* n = NULL;
    temp = (*sommet);
    while (temp->next != NULL){
        if(temp->numeroCase == temp->next->numeroCase){
            n = temp->next;
            temp->next = n->next;
        }else{
            temp = temp->next;
        }
    }

}

void afficher(Sommet2 * m, Cases tabPlateau[COLONNES][COLONNES], int i, int j){
    while (m != NULL){
        //if(tabPlateau[i][j].)
        if(m->typeRoutes == 1) {
            printf("Routes : %d %d: %d\n", m->i, m->j, m->NumeroDelaRoutePose);

        }
        if(m->typeHab == 1){
            printf("Maison : %d %d: %d (bat autour %d) prec : %d\n", m->i, m->j, m->numeroCase, m->tabMaisonAutourRoutes, m->sommetPrecedent);

        }
        if(m->typeUsineEau == 1){
            printf("UsineEau : %d %d: %d (bat autour %d) prec : %d\n", m->i, m->j, m->numeroCase, m->tabMaisonAutourRoutes, m->sommetPrecedent);
        }
        if(m->typeUsineElec == 1){
            printf("UsineELec : %d %d: %d (bat autour %d) prec : %d\n", m->i, m->j, m->numeroCase, m->tabMaisonAutourRoutes, m->sommetPrecedent);
        }
        m = m->next;
    }
    printf("\n");
}

void CreerArete2(Sommet2 ** Psommet2, int i, int j, int i_bis, int j_bis, int numeroCase, int PremierSommet, int tabMarque[45*35], Cases tabPlateau[COLONNES][COLONNES], int* sommetPrec, int nbRoutesPose, int* numChateau) {
    Sommet2 * temp = NULL;
    if(*Psommet2 == NULL){
        *Psommet2 = malloc(sizeof (Sommet2));
        (*Psommet2)->next = NULL;
        (*Psommet2)->numeroCase = numeroCase;
        (*Psommet2)->sommetPrecedent = -1;
        *sommetPrec = numeroCase;
        (*Psommet2)->i = i;
        (*Psommet2)->j = j;
        (*Psommet2)->NumeroDelaRoutePose = nbRoutesPose;
        (*Psommet2)->tabMaisonAutourRoutes = tabPlateau[i][j].tabMaisonAutourRoutes;
        (*Psommet2)->typeRoutes = tabPlateau[i][j].sommetDansLeGraphe;
        (*Psommet2)->typeHab = tabPlateau[i][j].sommetDansLeGrapheHab;
        (*Psommet2)->typeUsineEau = tabPlateau[i][j].sommetDansLeGrapheUsineEau;
        if((*Psommet2)->typeUsineEau == 1){

        }
        (*Psommet2)->typeUsineElec = tabPlateau[i][j].sommetDansLeGrapheUsineElec;
        //printf("%d %d\n", (*Psommet2)->typeUsineElec, (*Psommet2)->typeUsineEau);

    }
    else{
        temp = *Psommet2;
        Sommet2* nBis = malloc(sizeof(Sommet2));
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nBis;
        temp->next->numeroCase = numeroCase;
        temp->next->sommetPrecedent = *sommetPrec;
        *sommetPrec = numeroCase;
        temp->next->i = i;
        temp->next->j = j;
        temp->next->typeRoutes = tabPlateau[i][j].sommetDansLeGraphe;
        temp->next->typeHab = tabPlateau[i][j].sommetDansLeGrapheHab;
        temp->next->NumeroDelaRoutePose = nbRoutesPose;
        temp->next->typeUsineEau = tabPlateau[i][j].sommetDansLeGrapheUsineEau;
        /*if(temp->next->typeUsineEau == 1){
            *numChateau++;
            temp->numeroChateau = *numChateau;
        }*/
        temp->next->typeUsineElec = tabPlateau[i][j].sommetDansLeGrapheUsineElec;
        temp->next->tabMaisonAutourRoutes =tabPlateau[i][j].tabMaisonAutourRoutes;
        //printf("%d %d\n", temp->next->typeUsineElec, temp->next->typeUsineEau);
        temp->next->next = NULL;


    }
}

Sommet2 * TrierDansLeBonSensDeLaPose(Sommet2 * m){
    Sommet2 * temp, *p;
    int Pr;
    int test;
    if(m != NULL){

        for (temp = m; temp->next != NULL; temp = temp->next) {
            for (p = temp; p != NULL ; p = p->next) {
                if(p->NumeroDelaRoutePose <= temp->NumeroDelaRoutePose){

                    Pr = p->numeroCase;
                    p->numeroCase = temp->numeroCase;
                    temp->numeroCase = Pr;

                    test = p->NumeroDelaRoutePose;
                    p->NumeroDelaRoutePose = temp->NumeroDelaRoutePose;
                    temp->NumeroDelaRoutePose = test;

                    test = p->i;
                    p->i = temp->i;
                    temp->i = test;

                    test = p->j;
                    p->j = temp->j;
                    temp->j = test;

                    test = p->tabMaisonAutourRoutes;
                    p->tabMaisonAutourRoutes = temp->tabMaisonAutourRoutes;
                    temp->tabMaisonAutourRoutes = test;

                    test = p->typeRoutes;
                    p->typeRoutes = temp->typeRoutes;
                    temp->typeRoutes = test;

                    test = p->typeHab;
                    p->typeHab = temp->typeHab;
                    temp->typeHab = test;

                    test = p->typeUsineEau;
                    p->typeUsineEau = temp->typeUsineEau;
                    temp->typeUsineEau = test;

                    test = p->typeUsineElec;
                    p->typeUsineElec = temp->typeUsineElec;
                    temp->typeUsineElec = test;
                }
            }
        }
    }
    return m;
}

Sommet2 * Trier(Sommet2 * m){
    Sommet2 * temp, *p;
    int Pr;
    int test;
    if(m != NULL){

        for (temp = m; temp->next != NULL; temp = temp->next) {
            for (p = temp; p != NULL ; p = p->next) {
                if(p->numeroCase <= temp->numeroCase){
                    Pr = p->numeroCase;
                    p->numeroCase = temp->numeroCase;
                    temp->numeroCase = Pr;

                    test = p->NumeroDelaRoutePose;
                    p->NumeroDelaRoutePose = temp->NumeroDelaRoutePose;
                    temp->NumeroDelaRoutePose = test;

                    test = p->i;
                    p->i = temp->i;
                    temp->i = test;

                    test = p->j;
                    p->j = temp->j;
                    temp->j = test;

                    test = p->tabMaisonAutourRoutes;
                    p->tabMaisonAutourRoutes = temp->tabMaisonAutourRoutes;
                    temp->tabMaisonAutourRoutes = test;

                    test = p->typeRoutes;
                    p->typeRoutes = temp->typeRoutes;
                    temp->typeRoutes = test;

                    test = p->typeHab;
                    p->typeHab = temp->typeHab;
                    temp->typeHab = test;

                    test = p->typeUsineEau;
                    p->typeUsineEau = temp->typeUsineEau;
                    temp->typeUsineEau = test;

                    test = p->typeUsineElec;
                    p->typeUsineElec = temp->typeUsineElec;
                    temp->typeUsineElec = test;
                }
            }
        }
    }
    return m;
}

pSommet* CreerArete(pSommet* sommet, int i, int j, int i_bis, int j_bis, int numeroCase, int PremierSommet, int tabMarque[45*35]) {

    if(sommet[PremierSommet]->arc == NULL) {
        printf("e");
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->i_sommet = i_bis;
        Newarc->j_sommet = j_bis;
        //printf("%d %d\n", i_bis, j_bis);
        Newarc->sommet = PremierSommet;
        tabMarque[PremierSommet] = 1;
        Newarc->marque = 1;
        Newarc->arc_suivant = NULL;
        sommet[PremierSommet]->arc = Newarc;
        return sommet;
    }
    else {
        printf("det");
        pArc temp = sommet[PremierSommet]->arc;
        while(temp->arc_suivant != NULL) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->i_sommet = i_bis;
        Newarc->j_sommet = j_bis;
        Newarc->arc_suivant = NULL;
        Newarc->sommet = PremierSommet;
        tabMarque[PremierSommet] = 1;
        Newarc->marque = 1;

        if(temp->sommet>numeroCase)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet = numeroCase;
            tabMarque[numeroCase] = 1;
            Newarc->i_sommet = i_bis;
            Newarc->j_sommet = j_bis;
            Newarc->marque = 1;
            temp->arc_suivant=Newarc;
            return sommet;
        }
        temp->arc_suivant = Newarc;
        return sommet;
    }
}


Graphe* creerGraphe(int ordre) {
    Graphe* Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i = 0; i < ordre; i++) {
        Newgraphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }

    Newgraphe->ordre = ordre;

    return Newgraphe;
}


void check_relier_cases(Graphe* g, int i_constant, int j_constant, int i , int j, int i_bis, int j_bis, bool pose_de_route, Construction* tab_constru, Cases tab[COLONNES][COLONNES]) {
    if(i_bis+i >= 0 && i_bis+i <= 34 && j_bis+j >= 0 && j_bis+j <= 44) {
        if((pose_de_route && tab[i_bis+i][j_bis+j].occupe == 1) || (tab[i_bis+i][j_bis+j].type == 0)) {
            //g->pSommet = CreerArete(g->pSommet, i_constant+i, j_constant+j, i_bis+i, j_bis+j, TrouverNumeroCase(i_constant, j_constant));
            //g->pSommet = CreerArete(g->pSommet, i_bis+i, j_bis+j, i_constant+i, j_constant+j, TrouverNumeroCase(i_constant, j_constant));

            tab_constru[i_constant*COLONNES + j_constant].viable = true;
            tab_constru[(i_bis+i)*COLONNES + j_bis+j].viable = true;
            tab[i_constant-1][j_constant].viable = 1;
            tab[i_constant+1][j_constant].viable = 1;
            tab[i_constant][j_constant+1].viable = 1;
            tab[i_constant][j_constant-1].viable = 1;


        }
    }
}
