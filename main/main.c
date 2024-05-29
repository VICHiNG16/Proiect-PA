#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "distributie.h"
#include "output.h"

int main() {
    int* dimensiuni_carti = NULL;
    int numar_carti = 0;
    int numar_angajati = 3;

    // Citirea dimensiunilor cartilor
    dimensiuni_carti = citeste_dimensiuni_carti(&numar_carti);

    // Distribuirea cartilor
    int** distributie = distribuie_carti(dimensiuni_carti, numar_carti, numar_angajati);

    // Afisarea rezultatului
    afiseaza_distributie(distributie, numar_angajati);

    // Eliberarea memoriei alocate
    free(dimensiuni_carti);
    for (int i = 0; i < numar_angajati; i++) {
        free(distributie[i]);
    }
    free(distributie);

    return 0;
}
