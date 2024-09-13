#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

float* Saisie(int*); //Creer un tableau dynamique de la taille rentrée a l'appel de la fonction

void Affiche(float*, int); //Affiche toute les valeurs d'un tableau

int NbElementsIntervalle(float*, int,float,float); //Compte le nombre d'éléments du tableau qui sont compris dans l'intervalle choisie

bool TriAbsolu(float, float); //Permet de tester que la premiere valeur soit inférieur a la deuxieme en valeur absolue

void TriTabAbsolu(float*, int); //Tri le tableau de manière croissante avec leurs valeurs absolues

int main() {
    int n;
    float* tab = Saisie(&n);
    
    Affiche(tab,n);

    int cnt = 0;
    float binf = 0;
    float bsup = 0;
    printf("Entrez les bornes inf et sup de l'intervalle recherche.: ");
    scanf_s("%f%f", &binf,&bsup);
    cnt = NbElementsIntervalle(tab, n, binf, bsup);
    printf("Il y a %d elements du tableau compris dans l'intervalle donnee.\n", cnt);

    TriTabAbsolu(tab, n);
    Affiche(tab, n);

    free(tab);
    return 0;
}

float* Saisie(int* n) {
    printf("Entrez le nombre d'elements du tableau: ");
    scanf_s("%d", n);

    if (*n <= 0) {
        printf("Le nombre d'elements doit etre positif.\n");
        return NULL;
    }

    float* tableau = (float*)malloc((*n) * sizeof(float));

    if (tableau == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < *n; i++) {
        tableau[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    }

    return tableau;
}

void Affiche(float* tab, int n) {
    printf("Tableau genere aleatoirement:\n");
    for (int i = 0; i < n; i++) {
        printf("%f ", tab[i]);
    }
    printf("\n");
}

int NbElementsIntervalle(float* tab, int n, float Binf, float Bsup) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (tab[i]<Bsup && tab[i]>Binf)
            cnt++;
    }
    return cnt;
}

bool TriAbsolu(float x1, float x2) {
    if (fabs(x1) < fabs(x2))
        return true;
    else
        return false;
}

void TriTabAbsolu(float* tab, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (!TriAbsolu(tab[j], tab[j + 1])) {
                float temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}