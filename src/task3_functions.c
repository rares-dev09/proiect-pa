#include "test.h"
void create_root_node(const char *filename, TreeNode **root)
{
    FILE *f = fopen(filename, "r");
    char buff[2000];
    *root = (TreeNode *)malloc(sizeof(TreeNode));
    (*root)->stocks = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;
    StockList *first = NULL;
    StockList *prev = NULL;
    if (fgets(buff, sizeof(buff), f) != NULL)
    {
        const char *name = strtok(buff, ",\n");
        first = (*root)->stocks;
        while (name != NULL)
        {
            StockList *help_list = (StockList *)malloc(sizeof(StockList));
            strcpy(help_list->symbol, name);
            help_list->stock = NULL;
            help_list->next = NULL;
            if (first == NULL)
                first = help_list;
            else
                prev->next = help_list;
            prev = help_list;
            name = strtok(NULL, ",\n");
        }
        if (prev != NULL)
            prev->next = first;
        (*root)->stocks = first;
    }
    while (fgets(buff, sizeof(buff), f) != NULL)
    {
        const char *digit = strtok(buff, ",\n");
        StockList *rootStock = (*root)->stocks;
        while (digit != NULL)
        {
            stock *help_stock = (stock *)malloc(sizeof(stock));
            help_stock->val = atof(digit);
            help_stock->next = NULL;
            if (rootStock->stock == NULL)
                rootStock->stock = help_stock;
            else
            {
                stock *tail = rootStock->stock;
                while (tail->next != NULL)
                    tail = tail->next;
                tail->next = help_stock;
            }
            rootStock = rootStock->next;
            digit = strtok(NULL, ",\n");
        }
    }
};
void create_tree(TreeNode **root)
{
    if (root == NULL || *root == NULL)
        return;
    TreeNode *copy = *root;
    if (copy->stocks == NULL || copy->stocks->stock == NULL || copy->stocks->stock->next == NULL)
        return;
    StockList *first = copy->stocks;
    StockList *cur = first;
    int ct = 0;
    while (!ct)
    {
        if (cur->next == first)
            ct = 1;
        if (cur->stock->val > cur->stock->next->val)
            if (copy->left != NULL)
            {
                StockList *help_list = (StockList *)malloc(sizeof(StockList));
                strcpy(help_list->symbol, cur->symbol);
                help_list->stock = cur->stock->next;
                help_list->print = 0;
                StockList *last = copy->left->stocks;
                while (last->next != copy->left->stocks)
                    last = last->next;
                last->next = help_list;
                help_list->next = copy->left->stocks;
            }
            else
            {
                StockList *help_list = (StockList *)malloc(sizeof(StockList));
                strcpy(help_list->symbol, cur->symbol);
                help_list->stock = cur->stock->next;
                help_list->print = 0;
                help_list->next = help_list;
                copy->left = (TreeNode *)malloc(sizeof(TreeNode));
                copy->left->stocks = help_list;
                copy->left->left = NULL;
                copy->left->right = NULL;
            }
        else
        {
            if (copy->right != NULL)
            {
                StockList *help_list = (StockList *)malloc(sizeof(StockList));
                strcpy(help_list->symbol, cur->symbol);
                help_list->stock = cur->stock->next;
                help_list->print = 0;
                StockList *last = copy->right->stocks;
                while (last->next != copy->right->stocks)
                    last = last->next;
                last->next = help_list;
                help_list->next = copy->right->stocks;
            }
            else
            {
                StockList *help_list = (StockList *)malloc(sizeof(StockList));
                strcpy(help_list->symbol, cur->symbol);
                help_list->stock = cur->stock->next;
                help_list->print = 0;
                help_list->next = help_list;
                copy->right = (TreeNode *)malloc(sizeof(TreeNode));
                copy->right->stocks = help_list;
                copy->right->left = NULL;
                copy->right->right = NULL;
            }
        }
        cur = cur->next;
    }
    create_tree(&copy->left);
    create_tree(&copy->right);
}
void path(StockList *node, char v[])
{
    stock *aux = node->stock;
    int i = 0;
    while (aux != NULL && aux->next != NULL)
    {
        if (aux->val > aux->next->val)
            v[i] = 'L';
        else
            v[i] = 'R';
        i++;
        aux = aux->next;
    }
    v[i] = '\0';
}
void reverse_char(char v[])
{
    int i = 0;
    while (v[i] != 0)
        if (v[i] == 'R')
        {
            v[i] = 'L';
            i++;
        }
        else
        {
            v[i] = 'R';
            i++;
        }
}
StockList *find_mirror(TreeNode **root, const char v[])
{
    TreeNode *aux = *root;
    int i = 0;
    while (v[i] != 0)
    {
        if (v[i] == 'R')
        {
            if (aux->right == NULL)
                return NULL;
            aux = aux->right;
        }
        else if (v[i] == 'L')
        {
            if (aux->left == NULL)
                return NULL;
            aux = aux->left;
        }
        i++;
    }
    return aux->stocks;
}
int comes_before(StockList *first, const char *sym1, const char *sym2)
{
    StockList *cur = first;
    int ct = 0;
    while (!ct)
    {
        if (cur->next == first)
            ct = 1;
        if (strcmp(cur->symbol, sym1) == 0)
            return 1;
        if (strcmp(cur->symbol, sym2) == 0)
            return 0;
        cur = cur->next;
    }
    return 0;
}
void print_paths(TreeNode **root, FILE *f)
{
    StockList *aux = (*root)->stocks;
    StockList *first = (*root)->stocks;
    int ct = 0;
    int first_pair = 1;
    char v[10];
    while (!ct)
    {
        if (aux->next == first)
            ct = 1;
        path(aux, v);
        reverse_char(v);
        StockList *aux2 = find_mirror(root, v);
        if (aux2 != NULL)
        {
            StockList *first2 = aux2;
            int ct2 = 0;
            while (!ct2)
            {
                if (aux2->next == first2)
                    ct2 = 1;
                if (comes_before((*root)->stocks, aux->symbol, aux2->symbol))
                {
                    if (!first_pair)
                        fprintf(f, "\n");
                    fprintf(f, "%s-%s", aux->symbol, aux2->symbol);
                    first_pair = 0;
                }
                aux2 = aux2->next;
            }
        }
        aux = aux->next;
    }
}
void free_tree(TreeNode *node, int is_root)
{
    if (node == NULL)
        return;
    free_tree(node->left, 0);
    free_tree(node->right, 0);
    if (node->stocks != NULL)
    {
        StockList *cur = node->stocks;
        StockList *last = cur;
        while (last->next != node->stocks)
            last = last->next;
        last->next = NULL;
        while (cur != NULL)
        {
            StockList *next = cur->next;
            if (is_root)
            {
                stock *s = cur->stock;
                while (s != NULL)
                {
                    stock *sn = s->next;
                    free(s);
                    s = sn;
                }
            }
            free(cur);
            cur = next;
        }
    }
    free(node);
}
void task3_main(const char *argv[])
{
    TreeNode *root = NULL;
    create_root_node(argv[1], &root);
    create_tree(&root);
    FILE *f = fopen(argv[2], "w");
    print_paths(&root, f);
    fclose(f);
    free_tree(root, 1);
}