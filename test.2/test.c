#include "sys/stat.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    struct stat buf;


    if (stat(argv[1], &buf) == 0 && argc == 2)
    {
        printf("ok %i\n", buf.st_mode);
    }
    return (0);
}