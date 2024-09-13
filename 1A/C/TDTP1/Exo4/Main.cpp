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
        printf("Erreur : Allocation de mémoire impossible\n");
        return 1;
    }

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Remplissage du tableau avec des nombres aléatoires
    for (int i = 0; i < taille; i++) {
        tableau[i] = (double)rand() / RAND_MAX*500; // Nombre aléatoire entre 0 et 1
    }

    // Affichage du tableau
    printf("Tableau rempli de manière aléatoire :\n");
    for (int i = 0; i < taille; i++) {
        printf("%.2f ", tableau[i]);
    }
    printf("\n");

    // Libération de la mémoire allouée pour le tableau
    free(tableau);

    return 0;
}
