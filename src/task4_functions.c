#include "test.h"

void stare(int stari[], int *nr_stari, const float preturi[], int n, float d)
{
    for (int i = 0; i < n; i++)
    {
        int k = 0;
        int ok = 0;
        int stare_init = (int)(preturi[i] / d);
        while (k < (*nr_stari))
        {
            if (stari[k] == stare_init)
                ok = 1;
            k++;
        }
        if (!ok)
        {
            stari[(*nr_stari)] = stare_init;
            (*nr_stari)++;
        }
    }
}

int index_stare(const int stari[], int nr_stari, int s)
{
    for (int i = 0; i < nr_stari; i++)
        if (stari[i] == s)
            return i;
    return -1;
}
int cmmdc(int a, int b)
{
    if (b == 0)
        return a;
    else
        return cmmdc(b, a % b);
}

void inmultire(int a, int b, int c, int d, int *rez_num, int *rez_den)
{
    *rez_num = a * c;
    *rez_den = b * d;
    int g = cmmdc(*rez_num, *rez_den);
    *rez_num /= g;
    *rez_den /= g;
}

void adunare(int a, int b, int c, int d, int *rez_num, int *rez_den)
{
    *rez_num = a * d + c * b;
    *rez_den = b * d;
    int g = cmmdc(*rez_num, *rez_den);
    *rez_num /= g;
    *rez_den /= g;
}

void creare_adj(int n, int adj[n][n], int pret_plecare[], const float pret[], int stari[], int nr_stari, float d)
{
    for (int i = 0; i < n - 1; i++)
    {
        int a = index_stare(stari, nr_stari, (int)(pret[i] / d));
        int b = index_stare(stari, nr_stari, (int)(pret[i + 1] / d));
        adj[a][b]++;
        pret_plecare[a]++;
    }
}

void task4_main(const char *argv[])
{
    int n, k;
    float d, P_start, P_target;
    FILE *f = fopen(argv[1], "r");
    if (!f)
        return;
    fscanf(f, "%d", &n);
    fscanf(f, "%f", &d);
    fscanf(f, "%d", &k);
    fscanf(f, "%f", &P_start);
    fscanf(f, "%f", &P_target);
    float pret[n];
    for (int i = 0; i < n; i++)
        fscanf(f, "%f", &pret[i]);
    fclose(f);

    int stari[n], nr_stari = 0;
    int adj[n][n], pret_plecare[n];

    for (int i = 0; i < n; i++)
    {
        pret_plecare[i] = 0;
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
    }

    stare(stari, &nr_stari, pret, n, d);
    creare_adj(n, adj, pret_plecare, pret, stari, nr_stari, d);

    int numarator[nr_stari], numitor[nr_stari];
    int numarator2[nr_stari], numitor2[nr_stari];

    int index_start = index_stare(stari, nr_stari, (int)(P_start / d));
    int index_final = index_stare(stari, nr_stari, (int)(P_target / d));

    for (int i = 0; i < nr_stari; i++)
    {
        numarator[i] = 0;
        numitor[i] = 1;
    }
    numarator[index_start] = 1;

    FILE *g = fopen(argv[2], "w");

    for (int zi = 0; zi < k; zi++)
    {
        if (numitor[index_final] == 1)
            fprintf(g, "%d%s", numarator[index_final], zi < k - 1 ? "\n" : "");
        else
            fprintf(g, "%d/%d%s", numarator[index_final], numitor[index_final], zi < k - 1 ? "\n" : "");

        for (int i = 0; i < nr_stari; i++)
        {
            numarator2[i] = 0;
            numitor2[i] = 1;
        }

        for (int i = 0; i < nr_stari; i++)
        {
            if (pret_plecare[i] == 0)
                continue;
            for (int j = 0; j < nr_stari; j++)
            {
                if (adj[i][j] == 0)
                    continue;
                int p, q;
                inmultire(numarator[i], numitor[i], adj[i][j], pret_plecare[i], &p, &q);
                adunare(numarator2[j], numitor2[j], p, q, &numarator2[j], &numitor2[j]);
            }
        }

        for (int i = 0; i < nr_stari; i++)
        {
            numarator[i] = numarator2[i];
            numitor[i] = numitor2[i];
        }
    }

    fclose(g);
}
