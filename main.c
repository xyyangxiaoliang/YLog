#include <stdio.h>

#include "YLog.h"


int main(int argc, char** argv)
{
    printf("%s\n", __FUNCTION__);

    ylog_main(argc, argv);

    return 0;
}
