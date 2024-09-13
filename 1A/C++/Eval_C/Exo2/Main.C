#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* Saisie(int*); //Creer un tableau dynamique de la taille rentrée a l'appel de la fonction
void Affiche(int*, int); //Affiche toute les valeurs d'un tableau
void Echange(int* tab, int n); //Echange les valeurs en 1e et 3e position, puis celles en 2e et 4e position, puis celle en 5e et 7e position, etc...

int main() {
    int n;
    int* tab = Saisie(&n);

    Affiche(tab, n);

    Echange(tab, n);
    Affiche(tab, n);

    free(tab);
    return 0;
}

int* Saisie(int* n) {
    printf("Entrez le nombre d'elements du tableau: ");
    scanf_s("%d", n);


    if (*n % 4 != 0) {
        *n += 4 - (*n % 4);
    }

    if (*n <= 0) {
        printf("Le nombre d'elements doit etre positif.\n");
        return NULL;
    }

    int* tableau = (int*)malloc((*n) * sizeof(int));

    if (tableau == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < *n; i++) {
        tableau[i] = rand();
    }

    return tableau;
}

void Affiche(int* tab, int n) {
    printf("Tableau genere aleatoirement:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void Echange(int* tab, int n) {
    int* ptr = tab;

    for (int i = 0; i < n / 2; i += 4) {
        int temp = *(ptr + i);
        *(ptr + i) = *(ptr + i + 2);
        *(ptr + i + 2) = temp;

        temp = *(ptr + i + 1);
        *(ptr + i + 1) = *(ptr + i + 3);
        *(ptr + i + 3) = temp;
    }
}