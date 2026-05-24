#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define SYM_MAX 5

struct Node
{
    double valoare;
    double randament;
    struct Node *next;
};
typedef struct Node Node;
typedef struct Stack
{
    double value;
    struct Stack *next;
} Stack;
typedef struct Stack_arr
{
    char name[200];
    Stack *top;
} Stack_arr;
typedef struct Queue
{
    int day;
    double difference;
    char name[200];
    struct Queue *front;
    struct Queue *rear;
} Queue;
typedef struct stock
{
    float val;
    struct stock *next;
} stock;
typedef struct StockList
{
    char symbol[SYM_MAX];
    struct stock *stock;
    struct StockList *next;
    int print;
} StockList;
typedef struct TreeNode
{
    StockList *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
void addAtBeggining(Node **head, double value);
void free_function(Node **head);
void newNode(Node **head, double value);
void randament(Node **head);
void volatilitate_f(Node **head, int n, double *volatilitate, double randamentul_mediu);
void randament_mediu(Node **head, int n, double *randament_mediu);
void task1_main(const char *argv[]);
void scan_fucntion(Stack_arr *arr, const char *filename);
void push(Stack_arr *arr, int index, double value);
double pop(Stack_arr *arr, int index);
void free_stacks(Stack_arr *arr);
void free_queue(Queue *queue);
void create_queueNode(Queue **queue, const char *name, int day, double difference);
void compare_function(Stack_arr *arr, Queue **queue, int day);
void print_queue(Queue *queue, FILE *g);
void task2_main(const char *argv[]);
void print_root_node(TreeNode *root);
void create_root_node(const char *filename, TreeNode **root);
void create_tree(TreeNode **root);
void path(StockList *node, char v[]);
void reverse_char(char v[]);
StockList *find_mirror(TreeNode **root, const char v[]);
int comes_before(StockList *first, const char *sym1, const char *sym2);
void print_paths(TreeNode **root, FILE *f);
void free_tree(TreeNode *node, int is_root);
void task3_main(const char *argv[]);
void stare(int stari[], int *nr_stari, const float preturi[], int n, float d);
int index_stare(const int stari[], int nr_stari, int s);
int cmmdc(int a, int b);
void inmultire(int a, int b, int c, int d, int *numarator, int *numitor);
void adunare(int a, int b, int c, int d, int *numarator, int *numitor);
void creare_adj(int n, int adj[n][n], int pret_plecare[], const float pret[], int stari[], int nr_stari, float d);
void task4_main(const char *argv[]);