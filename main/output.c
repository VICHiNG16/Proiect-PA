#include <stdio.h>
#include "output.h"

// Functie pentru afisarea distributiei cartilor
void afiseaza_distributie(int** distributie, int numar_angajati) {
    printf("Distributia cartilor:\n");
    for (int i = 0; i < numar_angajati; i++) {
        printf("Angajat %d: ", i + 1);
        for (int j = 0; distributie[i][j] != 0; j++) {
            if (distributie[i][j] != 0) {
                printf("%d ", distributie[i][j]);
            }
        }
        printf("\n");
    }
}
