#include <stdio.h>

int main()
{
    
    int i;
    for (i = 1; i <= 4; i++) {
        char filename[20];
        sprintf(filename, "s8t%d.txt", i);
        FILE *out = fopen(filename, "w");
        fclose(out);
    }
    return 0;
}


