#include <stdio.h>
#include <stdlib.h>

// Définition de la structure d'un nœud de la liste
struct Node {
    int data;           // Donnée de ce nœud
    struct Node* next;  // Pointeur vers le prochain nœud dans la liste
};

int main() {
    // Création des cinq nœuds
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;
    struct Node* fourth = NULL;
    struct Node* fifth = NULL;

    // Allocation de mémoire pour chaque nœud
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    fourth = (struct Node*)malloc(sizeof(struct Node));
    fifth = (struct Node*)malloc(sizeof(struct Node));

    // Assignation des données et des pointeurs
    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = fourth;

    fourth->data = 4;
    fourth->next = fifth;

    fifth->data = 5;
    fifth->next = NULL;

    // Parcours et affichage de la liste
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    // Libération de la mémoire allouée pour les nœuds
    free(head);
    free(second);
    free(third);
    free(fourth);
    free(fifth);

    return 0;
}