#include "test.h"
int main(int argc, const char *argv[])
{
    if (argc < 3)
        return 0;

    int n = atoi(strstr(argv[1], "data") + 4);

    if (n <= 5)
        task1_main(argv);
    else if (n <= 10)
        task2_main(argv);
    else if (n <= 15)
        task3_main(argv);
    else
        task4_main(argv);

    return 0;
}
