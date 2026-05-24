#include "test.h"
void scan_fucntion(Stack_arr *arr, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        return;
    }
    char buffer[200];
    int i = 0;
    fgets(arr[i].name, sizeof(arr[i].name), f);
    arr[i].name[strcspn(arr[i].name, "\n")] = 0;
    while (i < 3 && fgets(buffer, sizeof(buffer), f))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        if (isdigit(buffer[0]))
        {
            push(arr, i, atof(buffer));
        }
        else
        {
            i++;
            if (i < 3)
                strcpy(arr[i].name, buffer);
        }
    }
    fclose(f);
}
void push(Stack_arr *arr, int index, double value)
{
    Stack *node = (Stack *)malloc(sizeof(Stack));
    node->value = value;
    node->next = arr[index].top;
    arr[index].top = node;
}
void free_stacks(Stack_arr *arr)
{
    for (int i = 0; i < 3; i++)
    {
        while (arr[i].top != NULL)
        {
            Stack *tmp = arr[i].top;
            arr[i].top = arr[i].top->next;
            free(tmp);
        }
    }
}
void free_queue(Queue *queue)
{
    Queue *current = queue;
    while (current != NULL)
    {
        Queue *tmp = current;
        current = current->front;
        free(tmp);
    }
}
double pop(Stack_arr *arr, int index)
{
    if (arr[index].top == NULL)
    {
        return -1;
    }
    Stack *temp = arr[index].top;
    double value = temp->value;
    arr[index].top = arr[index].top->next;
    free(temp);
    return value;
}
void create_queueNode(Queue **queue, const char *name, int day, double difference)
{
    Queue *node = (Queue *)malloc(sizeof(Queue));
    node->day = day;
    node->difference = difference;
    strcpy(node->name, name);
    node->front = NULL;
    node->rear = NULL;
    if (*queue == NULL)
    {
        *queue = node;
        (*queue)->rear = node;
    }
    else
    {
        (*queue)->rear->front = node;
        (*queue)->rear = node;
    }
}
void compare_function(Stack_arr *arr, Queue **queue, int day)
{
    double v[3];
    for (int i = 0; i < 3; i++)
    {
        v[i] = pop(arr, i);
    }
    if (v[0] == v[1] && v[1] != v[2])
    {
        double value = 0;
        if (v[2] > v[0])
        {
            value = v[2] - v[0];
        }
        else
        {
            value = v[0] - v[2];
        }
        create_queueNode(queue, arr[2].name, day, value);
    }
    else if (v[0] == v[2] && v[2] != v[1])
    {
        double value = 0;
        if (v[1] > v[0])
        {
            value = v[1] - v[0];
        }
        else
        {
            value = v[0] - v[1];
        }
        create_queueNode(queue, arr[1].name, day, value);
    }
    else if (v[1] == v[2] && v[2] != v[0])
    {
        double value = 0;
        if (v[0] > v[1])
        {
            value = v[0] - v[1];
        }
        else
        {
            value = v[1] - v[0];
        }
        create_queueNode(queue, arr[0].name, day, value);
    }
}
void print_queue(Queue *queue, FILE *g)
{
    Queue *current = queue;
    while (current != NULL)
    {
        fprintf(g, "ziua %d - %.2f - %s\n", current->day, current->difference, current->name);
        current = current->front;
    }
}
void task2_main(const char *argv[])
{
    Stack_arr arr[3];
    for (int i = 0; i < 3; i++)
    {
        arr[i].top = NULL;
    }
    scan_fucntion(arr, argv[1]);
    Queue *queue = NULL;
    int day = 1;
    while (arr[0].top != NULL && arr[1].top != NULL && arr[2].top != NULL)
    {
        compare_function(arr, &queue, day);
        day++;
    }
    free_stacks(arr);
    FILE *g = fopen(argv[2], "w");
    if (g)
    {
        print_queue(queue, g);
        fclose(g);
    }
    free_queue(queue);
}