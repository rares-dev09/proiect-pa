#include "src/test.h"
int main(int argc, const char *argv[])
{
    if (argc < 3)
        return 0;

    /* Extrag numarul din numele fisierului (ex: "data16.in" -> 16) */
    const char *basename = strrchr(argv[1], '/');
    basename = basename ? basename + 1 : argv[1];

    int file_num = 0;
    if (sscanf(basename, "data%d", &file_num) != 1)
        return 1;

    if (file_num >= 1 && file_num <= 5)
        task1_main(argv);
    else if (file_num >= 6 && file_num <= 10)
        task2_main(argv);
    else if (file_num >= 11 && file_num <= 15)
        task3_main(argv);
    else if (file_num >= 16 && file_num <= 20)
        task4_main(argv);

    return 0;
}
