#include <stdio.h>
#include "alltests.h"

int main(void)
{
    client_alltests();
    printf("Client-specific tests :\n");
    williamsClient_alltests();

    return 0;
}