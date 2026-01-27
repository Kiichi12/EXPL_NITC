#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <stdio.h>
#include "tree.h"

int fileinit(FILE *target_file); // to place the header
void emitExit(FILE *target_file); // to place exit instructions

// Generate code for an expression tree
// Writes instructions to the target file and
// returns the register index holding the result
int codeGen(tnode *root, FILE *target_file);

#endif