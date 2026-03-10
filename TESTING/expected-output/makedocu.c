#include <stdio.h>

int main()
{
    
    int i;
    for (i = 1; i <= 8; i++) {
        char filename[20];
        sprintf(filename, "s5t%d.txt", i);
        FILE *out = fopen(filename, "w");
        fclose(out);
    }
    return 0;
}


