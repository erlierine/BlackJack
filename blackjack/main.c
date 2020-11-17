#include <stdio.h>
#include <stdlib.h>

void error(char* msg, int exit_code) {
    printf ("%s\n", msg);
    exit(exit_code);
}

int main()
{
    return 0;
}
