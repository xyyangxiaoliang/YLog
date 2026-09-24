#include <stdio.h>

#include "YLog.h"


int main(int argc, char** argv)
{
    printf("%s\n", __FUNCTION__);

    printf("\033[1;30;42;mabcd1234\033[0m\n");

    ylog_main(argc, argv);

    return 0;
}
