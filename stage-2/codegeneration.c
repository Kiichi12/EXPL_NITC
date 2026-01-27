#include "register.h"
#include "codegeneration.h"
#include "memory.h"
#include <stdlib.h>

void fileinit(FILE *target_file)
{
    // if (!root) return -1;

    fprintf(target_file, "0\n2056\n0\n0\n0\n0\n0\n0\nBRKP\nMOV SP,4123\n");
}

void emitExit(FILE *target_file) {
    fprintf(target_file, "MOV R0, \"Exit\"\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "CALL 0\n");
    fprintf(target_file, "SUB SP, 5");
}


// Recursively generate code for AAST
int codeGen(tnode *t, FILE *target_file) {
    int r1, r2;

    if (t == NULL)
        return -1;

    switch (t->nodetype) {

        case NODE_NUM:
            r1 = getReg();
            fprintf(target_file, "MOV R%d, %d\n", r1, t->val);
            return r1;

        case NODE_ID:
            r1 = getReg();
            fprintf(target_file, "MOV R%d, [%d]\n",
                    r1, getAddress(t->varname[0]));
            return r1;

        case NODE_PLUS:
            r1 = codeGen(t->left, target_file);
            r2 = codeGen(t->right, target_file);
            fprintf(target_file, "ADD R%d, R%d\n", r1, r2);
            freeReg();
            return r1;

        case NODE_MINUS:
            r1 = codeGen(t->left, target_file);
            r2 = codeGen(t->right, target_file);
            fprintf(target_file, "SUB R%d, R%d\n", r1, r2);
            freeReg();
            return r1;

        case NODE_MUL:
            r1 = codeGen(t->left, target_file);
            r2 = codeGen(t->right, target_file);
            fprintf(target_file, "MUL R%d, R%d\n", r1, r2);
            freeReg();
            return r1;

        case NODE_DIV:
            r1 = codeGen(t->left, target_file);
            r2 = codeGen(t->right, target_file);
            fprintf(target_file, "DIV R%d, R%d\n", r1, r2);
            freeReg();
            return r1;

        case NODE_ASSIGN:
            r1 = codeGen(t->right, target_file);   // RHS expression
            fprintf(target_file, "MOV [%d], R%d\n",
                    getAddress(t->varname[0]), r1);
            freeReg();
            return -1;

        case NODE_READ:
            r1 = getReg();
            fprintf(target_file, "MOV R%d, \"Read\"\n",r1);
            fprintf(target_file, "PUSH R%d\n",r1);
            fprintf(target_file, "MOV R%d, -1\n",r1);
            fprintf(target_file, "PUSH R%d\n",r1);
            fprintf(target_file, "MOV R%d, %d\n",r1,
                    getAddress(t->varname[0]));
            fprintf(target_file, "PUSH R%d\n",r1);
            fprintf(target_file, "PUSH R%d\n",r1);
            fprintf(target_file, "PUSH R%d\n",r1);
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file,
                    "POP R0\nPOP R0\nPOP R0\nPOP R0\nPOP R0\n");
            return -1;

        case NODE_WRITE:
            r1 = codeGen(t->left, target_file);
            r2 = getReg();
            fprintf(target_file, "MOV R%d, \"Write\"\n",r2);
            fprintf(target_file, "PUSH R%d\n",r2);
            fprintf(target_file, "MOV R%d, -2\n",r2);
            fprintf(target_file, "PUSH R%d\n",r2);
            fprintf(target_file, "PUSH R%d\n", r1);
            fprintf(target_file, "PUSH R%d\n",r2);
            fprintf(target_file, "PUSH R%d\n",r2);
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file,
                    "POP R0\nPOP R0\nPOP R0\nPOP R0\nPOP R0\n");
            freeReg();
            return -1;

        case NODE_CONNECTOR:
            codeGen(t->left, target_file);
            codeGen(t->right, target_file);
            return -1;

        default:
            printf("Unknown nodetype\n");
            exit(1);
    }
}
