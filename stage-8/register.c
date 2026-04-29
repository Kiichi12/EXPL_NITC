#include "register.h"
#include <stdlib.h>
#include <stdbool.h>

bool registers[MAX_REGS];

void initReg() 
{
    for (int i = 0; i < MAX_REGS; i++) 
    {
        registers[i] = true;
    }
}

int getReg() 
{
    for (int i = 0; i < MAX_REGS; i++) 
    {
        if (registers[i]) 
        {
            registers[i] = false;
            return i;
        }
    }
    
    printf("Out of registers\n");
    exit(1);
}

void freeReg(int regNo) 
{
    registers[regNo] = true;
}

