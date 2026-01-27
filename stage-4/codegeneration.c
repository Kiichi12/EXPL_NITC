#include "register.h"
#include "codegeneration.h"
#include "labels.h"
#include "memory.h"
#include <stdlib.h>

void fileinit(FILE *target_file)
{
    fprintf(target_file, "0\n2056\n0\n0\n0\n0\n0\n0\nBRKP\n");
}

void emitExit(FILE *target_file) {
    fprintf(target_file, "MOV R0, \"Exit\"\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "CALL 0\n");
    fprintf(target_file, "SUB SP, 5\n");
}

int getAddrReg(tnode *t, FILE *target_file) {
    int addr_reg = getReg();

    if (t->nodetype == NODE_ARRAY_ELEMENT) {
        int index_reg = codeGen(t->right, target_file);
        fprintf(target_file, "MOV R%d, %d\n", addr_reg, t->Gentry->binding);
        fprintf(target_file, "ADD R%d, R%d\n", addr_reg, index_reg);
        freeReg(index_reg);
        return addr_reg;
    } 
    else if (t->nodetype == NODE_2D_ARRAY_ELEMENT) {
        int row_reg = codeGen(t->right->left, target_file);
        int col_reg = codeGen(t->right->right, target_file);
        int offset_reg = getReg();
        
        fprintf(target_file, "MOV R%d, %d\n", offset_reg, t->Gentry->cols);
        fprintf(target_file, "MUL R%d, R%d\n", offset_reg, row_reg);
        fprintf(target_file, "ADD R%d, R%d\n", offset_reg, col_reg);
        
        fprintf(target_file, "MOV R%d, %d\n", addr_reg, t->Gentry->binding);
        fprintf(target_file, "ADD R%d, R%d\n", addr_reg, offset_reg);
        
        freeReg(row_reg);
        freeReg(col_reg);
        freeReg(offset_reg);
        return addr_reg;
    }

    fprintf(stderr, "Internal Error: Cannot get address of nodetype %d\n", t->nodetype);
    exit(1);
}

int codeGen(tnode *t, FILE *target_file)
{
    if (t == NULL)
        return -1;

    switch (t->nodetype)
    {
        case NODE_NUM:
        {
            int r1 = getReg();
            fprintf(target_file, "MOV R%d, %d\n", r1, t->val);
            return r1;
        }
        
        case NODE_STRING:
        {
            int r1 = getReg();
            fprintf(target_file, "MOV R%d, %s\n", r1, t->strVal);
            return r1;
        }

        case NODE_ID: 
        {
            struct Gsymbol *g = t->Gentry;
            if (!g) {
                printf("Undeclared variable '%s' in codeGen\n", t->varname);
                exit(1);
            }
            int r1 = getReg();
            fprintf(target_file, "MOV R%d, [%d]\n", r1, g->binding);
            return r1;
        }

        case NODE_ARRAY_ELEMENT:
        {
            struct Gsymbol *g = t->Gentry;
            if (!g) {
                fprintf(stderr, "Undeclared array '%s'\n", t->varname);
                exit(1);
            }
            
           
            int index_reg = codeGen(t->right, target_file);
            
            int addr_reg = getReg();
            fprintf(target_file, "MOV R%d, R%d\n", addr_reg, index_reg);
            fprintf(target_file, "ADD R%d, %d\n", addr_reg, g->binding);
            
            int result_reg = getReg();
            fprintf(target_file, "MOV R%d, [R%d]\n", result_reg, addr_reg);
            
            freeReg(addr_reg);   
            freeReg(index_reg);   
            
            return result_reg;
        }

        case NODE_2D_ARRAY_ELEMENT:
        {
            struct Gsymbol *g = t->Gentry;
            if (!g) {
                fprintf(stderr, "Undeclared array '%s'\n", t->varname);
                exit(1);
            }

            int row_reg = codeGen(t->right->left, target_file);
            int col_reg = codeGen(t->right->right, target_file);

            int offset_reg = getReg();
            fprintf(target_file, "MOV R%d, %d\n", offset_reg, g->cols);
            fprintf(target_file, "MUL R%d, R%d\n", offset_reg, row_reg);

            fprintf(target_file, "ADD R%d, R%d\n", offset_reg, col_reg);

            int addr_reg = getReg();
            fprintf(target_file, "MOV R%d, R%d\n", addr_reg, offset_reg);
            fprintf(target_file, "ADD R%d, %d\n", addr_reg, g->binding);

            int result_reg = getReg();
            fprintf(target_file, "MOV R%d, [R%d]\n", result_reg, addr_reg);

            freeReg(addr_reg);
            freeReg(offset_reg);
            freeReg(col_reg);
            freeReg(row_reg);

            return result_reg;
        }


        case NODE_POINTER:
        {
            struct Gsymbol *g = t->left->Gentry;
            if (!g) {
                fprintf(stderr, "CodeGen: Undeclared variable in address-of\n");
                exit(1);
            }
            
            int addr_reg = getReg();
             
            fprintf(target_file, "MOV R%d, %d\n", addr_reg, g->binding);
            return addr_reg;
        }

        case NODE_DEREF:
        {
            int ptr_reg = codeGen(t->left, target_file);
            
            int result_reg = getReg();
            fprintf(target_file, "MOV R%d, [R%d]\n", result_reg, ptr_reg);
            
            freeReg(ptr_reg);
            return result_reg;
        }



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
        {
            int left_reg = codeGen(t->left, target_file);
            int right_reg = codeGen(t->right, target_file);

            switch (t->nodetype)
            {
                case NODE_PLUS:  fprintf(target_file, "ADD R%d, R%d\n", left_reg, right_reg); break;
                case NODE_MINUS: fprintf(target_file, "SUB R%d, R%d\n", left_reg, right_reg); break;
                case NODE_MUL:   fprintf(target_file, "MUL R%d, R%d\n", left_reg, right_reg); break;
                case NODE_DIV:   fprintf(target_file, "DIV R%d, R%d\n", left_reg, right_reg); break;
                case NODE_LT:    fprintf(target_file, "LT R%d, R%d\n", left_reg, right_reg); break;
                case NODE_LE:    fprintf(target_file, "LE R%d, R%d\n", left_reg, right_reg); break;
                case NODE_GT:    fprintf(target_file, "GT R%d, R%d\n", left_reg, right_reg); break;
                case NODE_GE:    fprintf(target_file, "GE R%d, R%d\n", left_reg, right_reg); break;
                case NODE_EQ:    fprintf(target_file, "EQ R%d, R%d\n", left_reg, right_reg); break;
                case NODE_NE:    fprintf(target_file, "NE R%d, R%d\n", left_reg, right_reg); break;
                default: break;
            }

            freeReg(right_reg);  // Free right operand result
            return left_reg;
        }

        case NODE_ASSIGN:
        case NODE_ARRAY_ASSIGN:
        case NODE_2D_ARRAY_ASSIGN:
        {
            int addr_reg = getAddrReg(t->left, target_file);
            int val_reg = codeGen(t->right, target_file);
            
            fprintf(target_file, "MOV [R%d], R%d\n", addr_reg, val_reg);
            
            freeReg(addr_reg);
            freeReg(val_reg);
            return -1;
        }


        case NODE_READ:
        {
            // Calculate the target address
            int addr_reg = getAddrReg(t->left, target_file);
            int temp_reg = getReg();

            fprintf(target_file, "MOV R%d, \"Read\"\n", temp_reg);
            fprintf(target_file, "PUSH R%d\n", temp_reg); // Func Code
            fprintf(target_file, "MOV R%d, -1\n", temp_reg);
            fprintf(target_file, "PUSH R%d\n", temp_reg); // Arg 1: File Desc
            fprintf(target_file, "PUSH R%d\n", addr_reg); // Arg 2: Target Address
            fprintf(target_file, "PUSH R%d\n", temp_reg); // Dummy
            fprintf(target_file, "PUSH R%d\n", temp_reg); // Dummy
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file, "SUB SP, 5\n");
            
            freeReg(addr_reg);
            freeReg(temp_reg);
            return -1;
        }

        case NODE_WRITE:
        {
            int value_reg = codeGen(t->left, target_file);
            int syscall_reg = getReg();
            
            fprintf(target_file, "MOV R%d, \"Write\"\n", syscall_reg);
            fprintf(target_file, "PUSH R%d\n", syscall_reg);
            fprintf(target_file, "MOV R%d, -2\n", syscall_reg);
            fprintf(target_file, "PUSH R%d\n", syscall_reg);
            fprintf(target_file, "PUSH R%d\n", value_reg);
            fprintf(target_file, "PUSH R%d\n", syscall_reg);
            fprintf(target_file, "PUSH R%d\n", syscall_reg);
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file, "SUB SP, 5\n");
            
            freeReg(syscall_reg);
            freeReg(value_reg);
            return -1;
        }

        case NODE_IF:
        {
            int endLabel = getLabel();
            int cond_reg = codeGen(t->left, target_file);
            fprintf(target_file, "JZ R%d, L%d\n", cond_reg, endLabel);
            freeReg(cond_reg);
            
            codeGen(t->right, target_file);
            emitLabel(target_file, endLabel);
            return -1;
        }

        case NODE_IFELSE:
        {
            int elseLabel = getLabel();
            int endLabel  = getLabel();
            
            int cond_reg = codeGen(t->left, target_file);
            fprintf(target_file, "JZ R%d, L%d\n", cond_reg, elseLabel);
            freeReg(cond_reg);
            
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
            
            int cond_reg = codeGen(t->left, target_file);
            fprintf(target_file, "JZ R%d, L%d\n", cond_reg, endLabel);
            freeReg(cond_reg);
            
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
            
            int cond_reg = codeGen(t->right, target_file);
            fprintf(target_file, "JNZ R%d, L%d\n", cond_reg, startLabel);
            freeReg(cond_reg);
            
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
            
            codeGen(t->left, target_file);  // Body first
            
            int cond_reg = codeGen(t->right, target_file);
            fprintf(target_file, "JZ R%d, L%d\n", cond_reg, startLabel);
            freeReg(cond_reg);
            
            emitLabel(target_file, endLabel);
            popLoopContext();
            return -1;
        }

        default:
        {
            printf("Unknown nodetype %d\n", t->nodetype);
            exit(1);
        }
    }
}
