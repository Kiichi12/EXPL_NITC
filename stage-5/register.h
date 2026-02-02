#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>

// Maximum number of registers we assume
// (XSM typically has 20 general-purpose registers)
#define MAX_REGS 20

// Initializes the register allocator
void initReg();

// Allocate a free register and return its index
int getReg();

// Free the most recently allocated register
void freeReg(int regNo);


#endif // REGISTER_H
