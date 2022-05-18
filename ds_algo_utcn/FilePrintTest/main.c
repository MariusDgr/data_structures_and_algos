#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fpointer;
    fpointer = fopen("test.txt", "w");
    fprintf(fpointer, "ols write \n");

    fclose(fpointer);
}
