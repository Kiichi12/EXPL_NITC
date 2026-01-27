#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>

#define MAX_REGS 20

// Initializes the register allocator
void initReg();

// Allocate a free register and return its index
int getReg();

// Free the most recently allocated register
void freeReg();


#endif 
