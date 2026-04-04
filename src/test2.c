#include "test.h"
void addAtBeggining(Node **head, double value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->valoare = value;
    node->randament = 0;
    node->next = *head;
    *head = node;
}
void free_function(Node **head)
{
    while (*head != NULL)
    {
        Node *aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}
void newNode(Node **head, double value)
{
    if (*head == NULL)
    {
        addAtBeggining(head, value);
        return;
    }
    Node *aux = *head;
    Node *node = (Node *)malloc(sizeof(Node));
    node->valoare = value;
    node->randament = 0;
    node->next = NULL;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    aux->next = node;
}
void randament(Node **head)
{
    const Node *previous = *head;
    Node *current = (*head)->next;
    while (current != NULL)
    {
        current->randament = (current->valoare - previous->valoare) / previous->valoare;
        previous = current;
        current = current->next;
    }
}
void randament_mediu(Node **head, int n, double *randament_mediu)
{
    Node *aux = (*head)->next;
    while (aux != NULL)
    {
        *randament_mediu = *randament_mediu + aux->randament;
        aux = aux->next;
    }
    *randament_mediu = *randament_mediu / n;
}
void volatilitate_f(Node **head, int n, double *volatilitate, double randamentul_mediu)
{
    Node *aux = (*head)->next;
    while (aux != NULL)
    {
        *volatilitate = *volatilitate + pow((aux->randament - randamentul_mediu), 2);
        aux = aux->next;
    }
    *volatilitate = *volatilitate / n;
    *volatilitate = sqrt(*volatilitate);
}