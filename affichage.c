#include "affichage.h"


void valeur_teinte_jour_nuit(int* black_fader, bool* fin_jour_nuit) {
    if(*black_fader == 0) {
        *fin_jour_nuit = false;
    }
    if(*black_fader <= 120 && !(*fin_jour_nuit)) {
        *black_fader += 3;
    }
    else {
        *black_fader -= 3;
        *fin_jour_nuit = true;
    }
}
