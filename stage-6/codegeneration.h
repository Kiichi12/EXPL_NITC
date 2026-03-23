#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <stdio.h>
#include "tree.h"
#include "typetable.h"

void fileinit(FILE *target_file); // to place the header and the replacement of stack pointer
void emitExit(FILE *target_file); // to place exit instructions

int codeGen(tnode *root, FILE *target_file);

#endif