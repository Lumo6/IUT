#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Affiche(const char*);
void Melange(char*);
int main() {
    char chaine1[] = "lapin";
    char chaine2[] = "chat";

    Affiche(chaine1);
    Melange(chaine1);

    Affiche(chaine2);
    Melange(chaine2);
    

    return 0;
}

void Affiche(const char* tab) {
    const char* ptr = tab;
    int cnt = 0;

    while (*ptr != '\0') {
        cnt++;
        ptr++;
    }

    printf("La chaine de caractere est de longueur : %d \n", cnt);

    printf("Chaine inverse:\n");
    for (int i = cnt - 1; i >= 0; i--) {
        printf("%c", tab[i]);
    }
    printf("\n");
}

void Melange(char* chaine) {
    int longueur = 0;
    while (chaine[longueur] != '\0') {
        longueur++;
    }

    for (int i = 0; i < longueur; i++) {
        char temp = chaine[i];
        chaine[i] = chaine[longueur - 1 - i];
        chaine[longueur - 1 - i] = temp;
    }

    printf("Chaine inverse:\n");
    for (int i = longueur - 1; i >= 0; i--) {
        printf("%c", chaine[i]);
    }
    printf("\n");
}