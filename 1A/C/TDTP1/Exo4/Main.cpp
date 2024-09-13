#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)
int main() {
    int taille;

    // Lecture de la taille du tableau depuis l'utilisateur
    printf("Entrez la taille du tableau : ");
    scanf("%d", &taille);

    // Allocation dynamique du tableau
    double* tableau = (double*)malloc(taille * sizeof(double));
    if (tableau == NULL) {
        printf("Erreur : Allocation de m�moire impossible\n");
        return 1;
    }

    // Initialisation du g�n�rateur de nombres al�atoires
    srand(time(NULL));

    // Remplissage du tableau avec des nombres al�atoires
    for (int i = 0; i < taille; i++) {
        tableau[i] = (double)rand() / RAND_MAX*500; // Nombre al�atoire entre 0 et 1
    }

    // Affichage du tableau
    printf("Tableau rempli de mani�re al�atoire :\n");
    for (int i = 0; i < taille; i++) {
        printf("%.2f ", tableau[i]);
    }
    printf("\n");

    // Lib�ration de la m�moire allou�e pour le tableau
    free(tableau);

    return 0;
}
