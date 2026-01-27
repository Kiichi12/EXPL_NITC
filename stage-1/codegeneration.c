#include "register.h"
#include "codegeneration.h"
#include <stdlib.h>

int fileinit(FILE *target_file)
{
    // if (!root) return -1;

    fprintf(target_file, "0\n2056\n0\n0\n0\n0\n0\n0\nBRKP\n");
    return 0;
}

void emitExit(FILE *target_file) {
    fprintf(target_file, "BRKP\n");
    fprintf(target_file, "MOV R0, \"Exit\"\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "CALL 0\n");
    fprintf(target_file, "SUB SP, 5");
}

// Recursively generate code for expression tree
int codeGen(tnode *root, FILE *target_file) {
    if (!root) return -1;

    // If leaf node (NUM)
    if (root->op == NULL) {
        int reg = getReg();
        fprintf(target_file, "MOV R%d, %d\n", reg, root->val);
        return reg;
    }

    // Evaluate left subtree
    int leftReg = codeGen(root->left, target_file);

    // Evaluate right subtree
    int rightReg = codeGen(root->right, target_file);

    // Emit code for operator
    // Always store result in the lower register
    if (leftReg < rightReg) {
        switch (root->op[0]) {
            case '+':
                fprintf(target_file, "ADD R%d, R%d\n", leftReg, rightReg);
                break;
            case '-':
                fprintf(target_file, "SUB R%d, R%d\n", leftReg, rightReg);
                break;
            case '*':
                fprintf(target_file, "MUL R%d, R%d\n", leftReg, rightReg);
                break;
            case '/':
                fprintf(target_file, "DIV R%d, R%d\n", leftReg, rightReg);
                break;
            default:
                fprintf(stderr, "Unknown operator %s\n", root->op);
                exit(1);
        }
        freeReg();  // Release the higher register
        return leftReg;
    } else {
        switch (root->op[0]) {
            case '+':
                fprintf(target_file, "ADD R%d, R%d\n", rightReg, leftReg);
                break;
            case '-':
                fprintf(target_file, "SUB R%d, R%d\n", rightReg, leftReg);
                break;
            case '*':
                fprintf(target_file, "MUL R%d, R%d\n", rightReg, leftReg);
                break;
            case '/':
                fprintf(target_file, "DIV R%d, R%d\n", rightReg, leftReg);
                break;
            default:
                fprintf(stderr, "Unknown operator %s\n", root->op);
                exit(1);
        }

        freeReg();
        return rightReg;
    }

}
