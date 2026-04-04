#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Node
{
    double valoare;
    double randament;
    struct Node *next;
};
typedef struct Node Node;
double round3(double x);
void addAtBeggining(Node **head, double value);
void free_function(Node **head);
void newNode(Node **head, double value);
void randament(Node **head);
void volatilitate_f(Node **head, int n, double *volatilitate, double randamentul_mediu);
void randament_mediu(Node **head, int n, double *randament_mediu);