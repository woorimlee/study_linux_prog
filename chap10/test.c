#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *a;

    printf("%d, %d", sizeof(a), sizeof(*a));
    return 0;
}
