#include "register.h"
#include <stdlib.h>

static int regCount;

void initReg() 
{
    regCount = -1;  // no registers allocated
}

int getReg() 
{
    if (regCount < MAX_REGS - 1) {
        regCount++;
        return regCount;
    }
    fprintf(stderr, "Out of registers\n");
    exit(1);
}

void freeReg() 
{
    if (regCount >= 0) {
        regCount--;
    }
}

