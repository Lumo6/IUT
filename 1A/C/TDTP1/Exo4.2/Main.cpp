#include <stdio.h>
#include <stdlib.h>

// D�finition de la structure d'un n�ud de la liste
struct Node {
    int data;           // Donn�e de ce n�ud
    struct Node* next;  // Pointeur vers le prochain n�ud dans la liste
};

int main() {
    // Cr�ation des cinq n�uds
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;
    struct Node* fourth = NULL;
    struct Node* fifth = NULL;

    // Allocation de m�moire pour chaque n�ud
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    fourth = (struct Node*)malloc(sizeof(struct Node));
    fifth = (struct Node*)malloc(sizeof(struct Node));

    // Assignation des donn�es et des pointeurs
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

    // Lib�ration de la m�moire allou�e pour les n�uds
    free(head);
    free(second);
    free(third);
    free(fourth);
    free(fifth);

    return 0;
}