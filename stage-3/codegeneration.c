#include "register.h"
#include "codegeneration.h"
#include "memory.h"
#include "labels.h"
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



int codeGen(tnode *t, FILE *target_file)
{
    int r1, r2;

    if (t == NULL)
        return -1;

    switch (t->nodetype)
    {
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
        case NODE_MINUS:
        case NODE_MUL:
        case NODE_DIV:
        case NODE_LT:
        case NODE_LE:
        case NODE_GT:
        case NODE_GE:
        case NODE_EQ:
        case NODE_NE:

            r1 = codeGen(t->left, target_file);
            r2 = codeGen(t->right, target_file);

            switch (t->nodetype)
            {
                case NODE_PLUS: fprintf(target_file, "ADD R%d, R%d\n", r1, r2); break;
                case NODE_MINUS: fprintf(target_file, "SUB R%d, R%d\n", r1, r2); break;
                case NODE_MUL: fprintf(target_file, "MUL R%d, R%d\n", r1, r2); break;
                case NODE_DIV: fprintf(target_file, "DIV R%d, R%d\n", r1, r2); break;
                case NODE_LT: fprintf(target_file, "LT R%d, R%d\n", r1, r2); break;
                case NODE_LE: fprintf(target_file, "LE R%d, R%d\n", r1, r2); break;
                case NODE_GT: fprintf(target_file, "GT R%d, R%d\n", r1, r2); break;
                case NODE_GE: fprintf(target_file, "GE R%d, R%d\n", r1, r2); break;
                case NODE_EQ: fprintf(target_file, "EQ R%d, R%d\n", r1, r2); break;
                case NODE_NE: fprintf(target_file, "NE R%d, R%d\n", r1, r2); break;
                default: break;
            }

            freeReg();   
            return r1;

        case NODE_ASSIGN:
            r1 = codeGen(t->right, target_file);
            fprintf(target_file, "MOV [%d], R%d\n",
                    getAddress(t->varname[0]), r1);
            freeReg();
            return -1;

        case NODE_READ:
            r1 = getReg();
            fprintf(target_file, "MOV R%d, \"Read\"\n", r1);
            fprintf(target_file, "PUSH R%d\n", r1);
            fprintf(target_file, "MOV R%d, -1\n", r1);
            fprintf(target_file, "PUSH R%d\n", r1);
            fprintf(target_file, "MOV R%d, %d\n", r1, getAddress(t->varname[0]));
            fprintf(target_file, "PUSH R%d\n", r1);
            fprintf(target_file, "PUSH R%d\n", r1);
            fprintf(target_file, "PUSH R%d\n", r1);
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file, "POP R0\nPOP R0\nPOP R0\nPOP R0\nPOP R0\n");
            freeReg();
            return -1;

        case NODE_WRITE:
            r1 = codeGen(t->left, target_file);
            r2 = getReg();
            fprintf(target_file, "MOV R%d, \"Write\"\n", r2);
            fprintf(target_file, "PUSH R%d\n", r2);
            fprintf(target_file, "MOV R%d, -2\n", r2);
            fprintf(target_file, "PUSH R%d\n", r2);
            fprintf(target_file, "PUSH R%d\n", r1);
            fprintf(target_file, "PUSH R%d\n", r2);
            fprintf(target_file, "PUSH R%d\n", r2);
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file, "POP R0\nPOP R0\nPOP R0\nPOP R0\nPOP R0\n");
            freeReg();   
            freeReg();   
            return -1;

        case NODE_IF:
        {
            int endLabel = getLabel();

            r1 = codeGen(t->left, target_file);
            fprintf(target_file, "JZ R%d, L%d\n", r1, endLabel);
            freeReg();

            codeGen(t->right, target_file);

            emitLabel(target_file, endLabel);
            return -1;
        }

        case NODE_IFELSE:
        {
            int elseLabel = getLabel();
            int endLabel  = getLabel();

            r1 = codeGen(t->left, target_file);
            fprintf(target_file, "JZ R%d, L%d\n", r1, elseLabel);
            freeReg();

            codeGen(t->right->left, target_file);
            fprintf(target_file, "JMP L%d\n", endLabel);

            emitLabel(target_file, elseLabel);
            codeGen(t->right->right, target_file);

            emitLabel(target_file, endLabel);
            return -1;
        }

        case NODE_WHILE:
        {
            int startLabel = getLabel();
            int endLabel = getLabel();
            
            pushLoopContext(endLabel, startLabel);  
            
            emitLabel(target_file, startLabel);
            r1 = codeGen(t->left, target_file);
            fprintf(target_file, "JZ R%d, L%d\n", r1, endLabel);
            freeReg();
            codeGen(t->right, target_file);
            fprintf(target_file, "JMP L%d\n", startLabel);
            emitLabel(target_file, endLabel);
            
            popLoopContext();  
        
            return -1;
        }

        case NODE_CONNECTOR:
        {
            codeGen(t->left, target_file);
            codeGen(t->right, target_file);
            return -1;
        }

        case NODE_BREAK:
        {
            if (isInsideLoop()) {
                LoopContext* ctx = getCurrentLoopContext();
                fprintf(target_file, "JMP L%d\n", ctx->breakLabel);
            }
            return -1;
        }

        case NODE_CONTINUE:
        {
            if (isInsideLoop()) {
            LoopContext* ctx = getCurrentLoopContext();
            fprintf(target_file, "JMP L%d\n", ctx->continueLabel);
            }
            return -1;
        }


        case NODE_DOWHILE:
        {
            int startLabel = getLabel();
            int endLabel = getLabel();
            
            pushLoopContext(endLabel, startLabel);
            
            emitLabel(target_file, startLabel);
            codeGen(t->left, target_file);  // Body first
            r1 = codeGen(t->right, target_file); // Condition
            fprintf(target_file, "JNZ R%d, L%d\n", r1, startLabel);
            freeReg();
            emitLabel(target_file, endLabel);
            
            popLoopContext();
            
            return -1;
        }
        
        case NODE_REPEAT:
        {
            int startLabel = getLabel();
            int endLabel = getLabel();
            
            pushLoopContext(endLabel, startLabel);
            
            emitLabel(target_file, startLabel);
            codeGen(t->left, target_file); // Body first
            r1 = codeGen(t->right, target_file); 
            fprintf(target_file, "JZ R%d, L%d\n", r1, startLabel);
            freeReg();
            emitLabel(target_file, endLabel);
            
            popLoopContext();
    
            return -1;
        }

        default:
            printf("Unknown nodetype\n");
            exit(1);
    }
}
