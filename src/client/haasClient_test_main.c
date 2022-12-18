#include <stdio.h>
#include "alltests.h"

int main(void)
{
    client_alltests();
    printf("Client-specific tests :\n");
    haasClient_alltests();

    return 0;
}