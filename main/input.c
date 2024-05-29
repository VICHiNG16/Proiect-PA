#include <stdio.h>
#include <stdlib.h>
#include "input.h"

// Functie pentru citirea dimensiunilor cartilor de la utilizator
int* citeste_dimensiuni_carti(int* numar_carti) {
    printf("Introdu numarul de carti: ");
    scanf("%d", numar_carti);

    // Alocare memorie pentru dimensiunile cartilor
    int* dimensiuni_carti = (int*)malloc(*numar_carti * sizeof(int));
    if (dimensiuni_carti == NULL) {
        perror("Nu se poate aloca memoria");
        exit(EXIT_FAILURE);
    }

    // Citirea dimensiunilor cartilor
    printf("Introdu dimensiunile cartilor: ");
    for (int i = 0; i < *numar_carti; i++) {
        scanf("%d", &dimensiuni_carti[i]);
    }

    return dimensiuni_carti;
}
