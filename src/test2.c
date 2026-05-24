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
void task1_main(const char *argv[])
{
    double value = 0, randament_m = 0, volatilitate = 0, randament_fara_risc = 0, shape_ratio = 0;
    FILE *f;
    f = fopen(argv[1], "r");
    if (!f)
        return;
    int n;
    if (fscanf(f, "%d", &n) != 1)
    {
        fclose(f);
        return;
    }
    Node *head = NULL;
    for (int i = 0; i < n; i++)
    {
        if (fscanf(f, "%lf", &value) == 1)
            newNode(&head, value);
        else
        {
            fclose(f);
            free_function(&head);
            return;
        }
    }

    fclose(f);
    randament(&head);
    randament_mediu(&head, n - 1, &randament_m);
    volatilitate_f(&head, n - 1, &volatilitate, randament_m);
    shape_ratio = (randament_m - randament_fara_risc) / volatilitate;
    FILE *g;
    g = fopen(argv[2], "w");
    randament_m = (int)(randament_m * 1000) / 1000.0;
    volatilitate = (int)(volatilitate * 1000) / 1000.0;
    shape_ratio = (int)(shape_ratio * 1000) / 1000.0;
    if (g)
    {
        fprintf(g, "%.3lf\n", randament_m);
        fprintf(g, "%.3lf\n", volatilitate);
        fprintf(g, "%.3lf\n", shape_ratio);
        fclose(g);
    }
    free_function(&head);
}