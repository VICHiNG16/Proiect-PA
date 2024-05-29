#include <stdlib.h>
#include <limits.h>
#include "distributie.h"

// Functie de backtracking pentru gasirea celei mai bune distributii
void backtrack(int* dimensiuni_carti, int numar_carti, int numar_angajati, int* distributie_curenta, int** cea_mai_buna_distributie, int* min_diferenta, int* sume, int carte_curenta) {
    if (carte_curenta == numar_carti) {
        // Calcularea diferentelor maxime si minime ale sumelor pentru distributia curenta
        int suma_maxima = INT_MIN;
        int suma_minima = INT_MAX;
        for (int i = 0; i < numar_angajati; i++) {
            if (sume[i] > suma_maxima) suma_maxima = sume[i];
            if (sume[i] < suma_minima) suma_minima = sume[i];
        }
        int diferenta = suma_maxima - suma_minima;
        // Actualizarea celei mai bune distributii daca diferenta este mai mica
        if (diferenta < *min_diferenta) {
            *min_diferenta = diferenta;
            for (int i = 0; i < numar_carti; i++) {
                cea_mai_buna_distributie[i][0] = distributie_curenta[i];
            }
        }
        return;
    }

    for (int i = 0; i < numar_angajati; i++) {
        distributie_curenta[carte_curenta] = i;
        sume[i] += dimensiuni_carti[carte_curenta];
        backtrack(dimensiuni_carti, numar_carti, numar_angajati, distributie_curenta, cea_mai_buna_distributie, min_diferenta, sume, carte_curenta + 1);
        sume[i] -= dimensiuni_carti[carte_curenta];
    }
}

// Functie pentru distribuirea cartilor intre angajati folosind backtracking
int** distribuie_carti(int* dimensiuni_carti, int numar_carti, int numar_angajati) {
    int** cea_mai_buna_distributie = (int**)malloc(numar_carti * sizeof(int*));
    for (int i = 0; i < numar_carti; i++) {
        cea_mai_buna_distributie[i] = (int*)malloc(sizeof(int));
    }

    int* distributie_curenta = (int*)malloc(numar_carti * sizeof(int));
    int* sume = (int*)calloc(numar_angajati, sizeof(int));
    int min_diferenta = INT_MAX;

    // Apelare functie de backtracking
    backtrack(dimensiuni_carti, numar_carti, numar_angajati, distributie_curenta, cea_mai_buna_distributie, &min_diferenta, sume, 0);

    free(distributie_curenta);
    free(sume);

    // Alocare memorie pentru distributia finala
    int** distributie_finala = (int**)malloc(numar_angajati * sizeof(int*));
    for (int i = 0; i < numar_angajati; i++) {
        distributie_finala[i] = (int*)malloc(numar_carti * sizeof(int));
        for (int j = 0; j < numar_carti; j++) {
            distributie_finala[i][j] = 0;
        }
    }

    // Copierea celei mai bune distributii in distributia finala
    for (int i = 0; i < numar_carti; i++) {
        int angajat = cea_mai_buna_distributie[i][0];
        for (int j = 0; j < numar_carti; j++) {
            if (distributie_finala[angajat][j] == 0) {
                distributie_finala[angajat][j] = dimensiuni_carti[i];
                break;
            }
        }
    }

    for (int i = 0; i < numar_carti; i++) {
        free(cea_mai_buna_distributie[i]);
    }
    free(cea_mai_buna_distributie);

    return distributie_finala;
}
