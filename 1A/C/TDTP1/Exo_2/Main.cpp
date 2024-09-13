#include <stdio.h> // Fonctions d’entree / sortie (printf, scanf,...)
#include <stdlib.h> // Fonctions d’allocation, aléatoire, conversion,... (malloc, free, rand,...)
#include <math.h>
int main(int argc, char* argv[])
{
	float montant_pret, taux_interet_annuel, mensualite;
    int duree_pret;
    
    // Saisie des données
    printf("Entrez le montant du prêt : ");
    scanf_s("%f", &montant_pret);
    
    printf("Entrez le taux d'intérêt annuel (en pourcentage) : ");
    scanf_s("%f", &taux_interet_annuel);
    
    printf("Entrez la durée du prêt (en mois) : ");
    scanf_s("%d", &duree_pret);
    
    // Conversion du taux d'intérêt annuel en taux mensuel
    float taux_interet_mensuel = taux_interet_annuel / 12 / 100;
    
    // Calcul de la mensualité
    mensualite = (montant_pret * taux_interet_mensuel) / (1 - pow(1 + taux_interet_mensuel, -duree_pret));
    
    // Calcul du coût total du crédit
    float cout_total_credit = mensualite * duree_pret - montant_pret;
    
    // Affichage des résultats
    printf("\nLa mensualite est de : %.2f\n", mensualite);
    printf("Le cout total du credit est de : %.2f\n", cout_total_credit);
    
    return 0;
}