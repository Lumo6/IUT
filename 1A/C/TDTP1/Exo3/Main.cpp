#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)
int main()
{
    FILE* in, * out;
    char oldFileName[100], newFileName[100];
    char tampon;

    // Saisie du nom de fichier par l'utilisateur
    printf("Entrez le nom du fichier de log : ");
    scanf("%s", oldFileName);

    

    // Ouverture du fichier de log en lecture
    in = fopen(oldFileName, "r");
    if (in == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", oldFileName);
        return 1;
    }

    char* extension = strrchr(oldFileName, '.');
    if (extension != NULL) {
        *extension = '\0';
    }

    // Création du nom du fichier de sauvegarde
    strcpy(newFileName, oldFileName);
    strcat(newFileName, ".bak");

    // Ouverture du fichier de sauvegarde en écriture
    out = fopen(newFileName, "w");
    if (out == NULL) {
        printf("Erreur : Impossible de créer le fichier de sauvegarde %s\n", newFileName);
        fclose(in);
        return 1;
    }

    // Copie du contenu du fichier de log vers le fichier de sauvegarde
    while (fread(&tampon, sizeof(char), 1, in) == 1) {
        fwrite(&tampon, sizeof(char), 1, out);
    }

    // Fermeture des fichiers
    fclose(in);
    fclose(out);

    printf("Le fichier de log a été sauvegardé avec succès sous le nom : %s\n", newFileName);

    return 0;
}