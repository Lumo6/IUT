#include <stdio.h> // Fonctions d�entree / sortie (printf, scanf,...)
#include <stdlib.h> // Fonctions d�allocation, al�atoire, conversion,... (malloc, free, rand,...)
#include <math.h>
int main(int argc, char* argv[])
{
	float montant_pret, taux_interet_annuel, mensualite;
    int duree_pret;
    
    // Saisie des donn�es
    printf("Entrez le montant du pr�t : ");
    scanf_s("%f", &montant_pret);
    
    printf("Entrez le taux d'int�r�t annuel (en pourcentage) : ");
    scanf_s("%f", &taux_interet_annuel);
    
    printf("Entrez la dur�e du pr�t (en mois) : ");
    scanf_s("%d", &duree_pret);
    
    // Conversion du taux d'int�r�t annuel en taux mensuel
    float taux_interet_mensuel = taux_interet_annuel / 12 / 100;
    
    // Calcul de la mensualit�
    mensualite = (montant_pret * taux_interet_mensuel) / (1 - pow(1 + taux_interet_mensuel, -duree_pret));
    
    // Calcul du co�t total du cr�dit
    float cout_total_credit = mensualite * duree_pret - montant_pret;
    
    // Affichage des r�sultats
    printf("\nLa mensualite est de : %.2f\n", mensualite);
    printf("Le cout total du credit est de : %.2f\n", cout_total_credit);
    
    return 0;
}