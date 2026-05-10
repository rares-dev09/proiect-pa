#include "test.h"
int main(int argc, const char *argv[])
{
    if (argc < 3)
        return 0;
    FILE *f = fopen(argv[1], "r");
    if (!f)
        return 1;
    char buff[3];
    fgets(buff, 3, f);
    fclose(f);
    if (isdigit(buff[0]))
        task1_main(argv);
    else if (('A' <= buff[0] && buff[0] <= 'Z') && ('a' <= buff[1] && buff[1] <= 'z'))
    {
        task2_main(argv);
    }
    else if (('A' <= buff[0] && buff[0] <= 'Z') && ('A' <= buff[1] && buff[1] <= 'Z'))
    {
        task3_main(argv);
    }
    return 0;
}