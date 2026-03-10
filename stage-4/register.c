#include "register.h"
#include <stdlib.h>
#include <stdbool.h>

// track how many registers are currently in use
bool registers[MAX_REGS];

// initialize or reset register counter
void initReg() 
{
    for (int i = 0; i < MAX_REGS; i++) {
        registers[i] = true;
    }
}

// allocate the lowest numbered free register
int getReg() 
{
    for (int i = 0; i < MAX_REGS; i++) {
        if (registers[i]) {
            registers[i] = false;
            return i;
        }
    }
    
    printf("Out of registers\n");
    exit(1);
}

// free the highest numbered register currently in use
void freeReg(int regNo) 
{
    registers[regNo] = true;
}

