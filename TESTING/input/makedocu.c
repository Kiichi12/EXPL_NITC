#include <stdio.h>

int main()
{
    
    int i;
    for (i = 1; i <= 3; i++) {
        char filename[20];
        sprintf(filename, "s7t%d-in.txt", i);
        FILE *out = fopen(filename, "w");
        fclose(out);
    }
    return 0;
}


