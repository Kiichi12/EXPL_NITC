#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <stdio.h>
#include "tree.h"

void fileinit(FILE *target_file); // to place the header and the replacement of stack pointer
void emitExit(FILE *target_file); // to place exit instructions


// Writes instructions to the target file according to the AST
int codeGen(tnode *root, FILE *target_file);

#endif