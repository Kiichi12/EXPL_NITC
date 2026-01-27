#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <stdio.h>
#include "tree.h"

void fileinit(FILE *target_file); // to place the header and the replacement of stack pointer
void emitExit(FILE *target_file); // to place exit instructions

// Generate code for an AST and
// Writes instructions to the target file and
int codeGen(tnode *root, FILE *target_file);

#endif