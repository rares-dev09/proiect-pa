#include "test.h"
int main(int argc, const char *argv[])
{
    double value = 0, randament_m = 0, volatilitate = 0, randament_fara_risc = 0, shape_ratio = 0;
    if (argc < 3)
        return 0;
    FILE *f;
    f = fopen(argv[1], "r");
    if (!f)
        return 0;
    int n;
    if (fscanf(f, "%d", &n) != 1)
    {
        fclose(f);
        return 0;
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
            return 0;
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

    return 0;
}