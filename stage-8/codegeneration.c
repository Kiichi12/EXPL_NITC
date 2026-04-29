#include "register.h"
#include "codegeneration.h"
#include "labels.h"
#include "memory.h"
#include "constants.h"
#include "tree.h"

#include <stdbool.h>

#include <stdlib.h>

int getVFTBase(ClassTableEntry *cls)
{
    return STACK_START + (cls->classId - 1) * VFT_BLOCK_SIZE;
}
int getMethodIndex(ClassTableEntry *cls, const char *methodName)
{
    ClassTableEntry *curr = cls;

    while(curr)
    {
        int i = 0;
        MethodEntry *m = curr->methods;
        while(m)
        {
            if(strcmp(m->name,methodName) == 0)
                return i;
            i++;
             m = m->next;
        }

        curr = curr->parent;
    }
    return -1;
}

void EnterVFT(FILE *target_file)
{
    ClassTableEntry *cls = classTableHead;

    if(!cls)
    {
        return;
    }

    // fprintf(target_file, "/* ---- Virtual Function Table ---- */\n");

    int addr_reg = getReg();
    int val_reg = getReg();
    while(cls)
    {
        int vft_base = getVFTBase(cls);
        int i = 0;
        MethodEntry*m = cls->methods;
        while(m && i < VFT_BLOCK_SIZE)
        {
            int j = vft_base + i;
            fprintf(target_file, "MOV R%d, F%d\n", val_reg, m->flabel);
            fprintf(target_file, "MOV R%d, %d\n", addr_reg, j);
            fprintf(target_file, "MOV [R%d], R%d\n", addr_reg, val_reg);
            i++;
            m = m->next;
        }
        cls = cls->next;
    }
    freeReg(addr_reg);
    freeReg(val_reg);
    // fprintf(target_file, "/* ---- End Virtual Function Table ---- */\n");
}

extern bool registers[MAX_REGS]; // access register status

int saveRegisters(FILE *target_file, int *regs) 
{
    int count = 0;
    for (int i = 0; i < MAX_REGS; i++) {
        if (!registers[i]) 
        
        { // If not true, it's in use
            fprintf(target_file, "PUSH R%d\n", i);
            count++;
            regs[i] = 1;
        }
    }
    return count;
}


void restoreRegisters(FILE *target_file, int *regs, int count) 
{
    for (int i = MAX_REGS - 1; i >= 0; i--) {
        if (regs[i] == 1) {
            fprintf(target_file, "POP R%d\n", i);
            count--;
            if (count == 0) break;
        }
    }
}

int pushArgStack(tnode *temp, FILE *target_file, int argCount)
{
    if(!temp)
    {
        return 0;
    }
    
    if(temp->nodetype == NODE_CONNECTOR) 
    {
        int r = codeGen(temp->right, target_file, NULL);
        fprintf(target_file, "PUSH R%d\n", r);
        freeReg(r);

        argCount = 1 + pushArgStack(temp->left, target_file, argCount);
    } 
    else if(temp != NULL)
    {
        int r = codeGen(temp, target_file, NULL);
        fprintf(target_file, "PUSH R%d\n", r);
        freeReg(r);
        return 1;
    }

    return argCount;
}



void fileinit(FILE *target_file)
{
    fprintf(target_file, "0\nMAIN\n0\n0\n0\n0\n0\n0\nBRKP\n"); 
}

void emitExit(FILE *target_file) 
{
    fprintf(target_file, "MOV R0, \"Exit\"\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "PUSH R0\n");
    fprintf(target_file, "CALL 0\n");
    fprintf(target_file, "SUB SP, 5\n");
}

int getFieldAddr(tnode *t, FILE *target_file);

int getAddrReg(tnode *t, FILE *target_file) 
{
    int addr_reg = getReg();

    if (t->nodetype == NODE_DEREF) 
    {
        freeReg(addr_reg);
        return codeGen(t->left, target_file, NULL); 
    }

    if (t->nodetype == NODE_FIELD) 
    {
        freeReg(addr_reg);
        return getFieldAddr(t, target_file);
    }

    struct Lsymbol *l = LLookup(t->varname);
    if (l) 
    {
        fprintf(target_file, "MOV R%d, BP\n", addr_reg);
        fprintf(target_file, "ADD R%d, %d\n", addr_reg, l->binding);
        return addr_reg;
    }
    
    if (t->nodetype == NODE_ID) 
    {
        fprintf(target_file, "MOV R%d, %d\n", addr_reg, t->Gentry->binding);
        return addr_reg;
    }

    if (t->nodetype == NODE_POINTER) 
    {
        fprintf(target_file, "MOV R%d, %d\n", addr_reg, t->Gentry->binding);
        fprintf(target_file, "MOV R%d, [R%d]\n", addr_reg, addr_reg);
        return addr_reg;
    }

    if (t->nodetype == NODE_ARRAY_ELEMENT) 
    {
        int index_reg = codeGen(t->right, target_file, NULL);
        fprintf(target_file, "MOV R%d, %d\n", addr_reg, t->Gentry->binding);
        fprintf(target_file, "ADD R%d, R%d\n", addr_reg, index_reg);
        freeReg(index_reg);
        return addr_reg;
    }

    fprintf(stderr, "Internal Error: Cannot get address of nodetype %d\n", t->nodetype);
    exit(1);
}

int getFieldAddr(tnode *t, FILE *target_file)
{
    int base_reg = getReg();
    tnode *base = t->left;

    if (base->nodetype == NODE_ID) 
    {
        int var_addr = getAddrReg(base, target_file);
        fprintf(target_file, "MOV R%d, [R%d]\n", base_reg, var_addr);
        freeReg(var_addr);
    }
    else if (base->nodetype == NODE_FIELD)
    {
        int sub_addr = getFieldAddr(base, target_file);
        fprintf(target_file, "MOV R%d, [R%d]\n", base_reg, sub_addr);
        freeReg(sub_addr);
    }
    else if(base->nodetype == NODE_SELF)
    {
        struct Lsymbol *selfEntry = LLookup("self");
        if(!selfEntry)
        {
            fprintf(stderr, "Internal error: 'self' not found in LST\n");
            exit(1);
        }
        int self_ptr = getReg();
        fprintf(target_file, "MOV R%d, BP\n", self_ptr);
        fprintf(target_file, "ADD R%d, %d\n", self_ptr, selfEntry->binding);
        fprintf(target_file, "MOV R%d, [R%d]\n", base_reg, self_ptr);
        freeReg(self_ptr);
    }
    else
    {
        printf("Codegeneration error: UNexpected base nodetype in getfieldAddr\n");
        exit(1);
    }
    
    fprintf(target_file, "ADD R%d, %d\n", base_reg, t->fieldEntry->fieldOffset);
    return base_reg;
}

int codeGen(tnode *t, FILE *target_file, struct Gsymbol *func) 
{
    if (t == NULL)
        return -1;
    if(func)
    {
        if(strcmp(func->name, "MAIN") == 0)
        {
            fprintf(target_file, "MAIN:\n");
            fprintf(target_file, "BRKP\n");
            EnterVFT(target_file);
            moveStackPointer(target_file);
            
        }
        else
            fprintf(target_file, "F%d:\n", func->flabel);

        fprintf(target_file, "BRKP\n");
        fprintf(target_file, "PUSH BP\n");
        fprintf(target_file, "MOV BP, SP\n");
        
        locAlloc(target_file);
    }

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

        case NODE_NULL:
        {
            int r1 = getReg();
            fprintf(target_file, "MOV R%d, 0\n", r1); // NULL is represented as 0(invalid heap address)
            return r1;
        }

        case NODE_ID: 
        {
            int addr_reg = getAddrReg(t, target_file);
            int val_reg = getReg();
            fprintf(target_file, "MOV R%d, [R%d]\n", val_reg, addr_reg);
            freeReg(addr_reg);
            return val_reg;
        }

        case NODE_ARRAY_ELEMENT:
        {
            struct Gsymbol *g = t->Gentry;
            if (!g) {
                fprintf(stderr, "Undeclared array '%s'\n", t->varname);
                exit(1);
            }
            
           
            int index_reg = codeGen(t->right, target_file, NULL);
            
            int addr_reg = getReg();
            fprintf(target_file, "MOV R%d, R%d\n", addr_reg, index_reg);
            fprintf(target_file, "ADD R%d, %d\n", addr_reg, g->binding);
            
            int result_reg = getReg();
            fprintf(target_file, "MOV R%d, [R%d]\n", result_reg, addr_reg);
            
            freeReg(addr_reg);   
            freeReg(index_reg);   
            
            return result_reg;
        }

        case NODE_FIELD:
        {
            fprintf(target_file, "BRKP\n");
            int addr = getFieldAddr(t, target_file);
            int val  = getReg();
            fprintf(target_file, "MOV R%d, [R%d]\n", val, addr);
            freeReg(addr);
            return val;
        }



        case NODE_POINTER:
        {
            int addr_reg = getAddrReg(t->left, target_file);
            return addr_reg;
        }

        case NODE_DEREF:
        {
            int ptr_reg = codeGen(t->left, target_file, NULL);
            
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
            int left_reg = codeGen(t->left, target_file, NULL);
            int right_reg = codeGen(t->right, target_file, NULL);

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

        case NODE_AND:
        {
            int falseLabel = getLabel();
            int endLabel = getLabel();

            int l = codeGen(t->left, target_file, NULL);
            fprintf(target_file, "JZ R%d, L%d\n", l, falseLabel);
            freeReg(l);

            int r = codeGen(t->right, target_file, NULL);
            fprintf(target_file, "JZ R%d, L%d\n", r, falseLabel);
            freeReg(r);

            int result_reg = getReg();
            fprintf(target_file, "MOV R%d, 1\n", result_reg);
            fprintf(target_file, "JMP L%d\n", endLabel);

            emitLabel(target_file, falseLabel);
            fprintf(target_file, "MOV R%d, 0\n", result_reg);

            emitLabel(target_file, endLabel);
            return result_reg;
        }

        case NODE_OR:
        {
            int trueLabel = getLabel();
            int endLabel  = getLabel();

            int l = codeGen(t->left, target_file, NULL);
            fprintf(target_file, "JNZ R%d, L%d\n", l, trueLabel);
            freeReg(l);

            int r = codeGen(t->right, target_file, NULL);
            fprintf(target_file, "JNZ R%d, L%d\n", r, trueLabel);
            freeReg(r);

            int res = getReg();
            fprintf(target_file, "MOV R%d, 0\n", res);
            fprintf(target_file, "JMP L%d\n", endLabel);
            emitLabel(target_file, trueLabel);
            fprintf(target_file, "MOV R%d, 1\n", res);
            emitLabel(target_file, endLabel);
            return res;
        }

        case NODE_NOT:
        {
            int falseLabel = getLabel();
            int endLabel   = getLabel();

            int val = codeGen(t->left, target_file, NULL);
            fprintf(target_file, "JNZ R%d, L%d\n", val, falseLabel);
            freeReg(val);

            int res = getReg();
            fprintf(target_file, "MOV R%d, 1\n", res);
            fprintf(target_file, "JMP L%d\n", endLabel);
            emitLabel(target_file, falseLabel);
            fprintf(target_file, "MOV R%d, 0\n", res);
            emitLabel(target_file, endLabel);
            return res;
        }

        case NODE_ASSIGN:
        case NODE_ARRAY_ASSIGN:
        {
            tnode *lval = t->left;
            tnode *rval = t->right;
            fprintf(target_file, "BRKP\n");
            if((lval->type == TYPE_CLASS || lval->type == TYPE_USERDEF) && (lval->typeEntry && lookupClass(lval->typeEntry->name)))
            {
                if(rval->nodetype == NODE_NEW)
                {
                    ClassTableEntry *newCls = lookupClass(rval->varname);
                    int vft_base = getVFTBase(newCls);
                    
                    int addr_reg = getAddrReg(lval, target_file);
                    int heap_reg = codeGen(rval, target_file, NULL);

                    fprintf(target_file, "MOV [R%d], R%d\n", addr_reg, heap_reg);
                    freeReg(heap_reg);

                    int vft_reg = getReg();
                    fprintf(target_file, "MOV R%d, %d\n", vft_reg, vft_base);
                    fprintf(target_file, "ADD R%d, 1\n", addr_reg);
                    fprintf(target_file, "MOV [R%d], R%d\n", addr_reg, vft_reg);
                    freeReg(addr_reg);
                    freeReg(vft_reg);
                    return -1;
                }

                if(rval->nodetype != NODE_NULL)
                {
                    int addr_l = getAddrReg(lval, target_file);
                    int addr_r = getAddrReg(rval, target_file);

                    int tmp = getReg();

                    fprintf(target_file, "MOV R%d, [R%d]\n", tmp, addr_r);
                    fprintf(target_file, "MOV [R%d], R%d\n", addr_l, tmp);

                    fprintf(target_file, "ADD R%d, 1\n", addr_l);
                    fprintf(target_file, "ADD R%d, 1\n", addr_r);
                    fprintf(target_file, "MOV R%d, [R%d]\n", tmp, addr_r);
                    fprintf(target_file, "MOV [R%d], R%d\n", addr_l, tmp);

                    freeReg(tmp);
                    freeReg(addr_l);
                    freeReg(addr_r);
                    return -1;
                }
            }
            int addr_reg = getAddrReg(t->left, target_file);
            int val_reg = codeGen(t->right, target_file, NULL);
            
            fprintf(target_file, "MOV [R%d], R%d\n", addr_reg, val_reg);
            
            freeReg(addr_reg);
            freeReg(val_reg);
            return -1;
        }


        case NODE_READ:
        {
            int addr_reg = getAddrReg(t->left, target_file);
            int temp_reg = getReg();

            fprintf(target_file, "MOV R%d, \"Read\"\n", temp_reg);
            fprintf(target_file, "PUSH R%d\n", temp_reg); 
            fprintf(target_file, "MOV R%d, -1\n", temp_reg);
            fprintf(target_file, "PUSH R%d\n", temp_reg);
            fprintf(target_file, "PUSH R%d\n", addr_reg);
            fprintf(target_file, "PUSH R%d\n", temp_reg); // dummy
            fprintf(target_file, "PUSH R%d\n", temp_reg); // dummy
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file, "SUB SP, 5\n");
            fprintf(target_file, "BRKP\n");
            
            freeReg(addr_reg);
            freeReg(temp_reg);
            return -1;
        }

        case NODE_WRITE:
        {
            int value_reg = codeGen(t->left, target_file, NULL);
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
            // printf("BRKP\n");
            int endLabel = getLabel();
            int cond_reg = codeGen(t->left, target_file, NULL);
            fprintf(target_file, "JZ R%d, L%d\n", cond_reg, endLabel);
            freeReg(cond_reg);
            
            codeGen(t->right, target_file, NULL);
            emitLabel(target_file, endLabel);
            return -1;
        }

        case NODE_IFELSE:
        {
            int elseLabel = getLabel();
            int endLabel  = getLabel();
            
            int cond_reg = codeGen(t->left, target_file, NULL);
            fprintf(target_file, "JZ R%d, L%d\n", cond_reg, elseLabel);
            freeReg(cond_reg);
            
            codeGen(t->right->left, target_file, NULL);
            fprintf(target_file, "JMP L%d\n", endLabel);
            
            emitLabel(target_file, elseLabel);
            codeGen(t->right->right, target_file, NULL);
            emitLabel(target_file, endLabel);
            return -1;
        }

        case NODE_WHILE:
        {
            int startLabel = getLabel();
            int endLabel = getLabel();
            
            pushLoopContext(endLabel, startLabel);
            emitLabel(target_file, startLabel);
            
            int cond_reg = codeGen(t->left, target_file, NULL);
            fprintf(target_file, "JZ R%d, L%d\n", cond_reg, endLabel);
            freeReg(cond_reg);
            
            codeGen(t->right, target_file, NULL);
            fprintf(target_file, "JMP L%d\n", startLabel);
            emitLabel(target_file, endLabel);
            popLoopContext();
            return -1;
        }

        case NODE_CONNECTOR:
        {
            codeGen(t->left, target_file, NULL);
            codeGen(t->right, target_file, NULL);
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

        case NODE_FUNCALL:
        {
            int *regs = (int *)malloc(MAX_REGS * sizeof(int));
            for(int i = 0; i < MAX_REGS; i++)
            {
                regs[i] = 0;
            }
            int reg_pushed = saveRegisters(target_file, regs);
            
            tnode *arg = t->left;

            tnode *temp = arg;
            int argCount = pushArgStack(temp, target_file, 0);

            fprintf(target_file, "PUSH R0\n");

            fprintf(target_file, "BRKP\n");

            fprintf(target_file, "CALL F%d\n",t->Gentry->flabel);
            
            int resultReg = getReg();
            fprintf(target_file, "POP R%d\n", resultReg);

            for(int i = 0; i < argCount; i++) 
            {
                int dummy = getReg();
                fprintf(target_file, "POP R%d\n", dummy);
                freeReg(dummy);
            }

            restoreRegisters(target_file, regs, reg_pushed);

            return resultReg;
        }

        case NODE_RET:
        {
            if(strcmp(t->varname, "MAIN") == 0)
            {
                fprintf(target_file, "INT 10\n");
                return -1;
            }
            

            if(t->left)
            {
                int resultReg = codeGen(t->left, target_file, NULL);

                int temp = getReg();

                fprintf(target_file, "MOV R%d, BP\n", temp);
                fprintf(target_file, "ADD R%d, -2\n",temp);
                fprintf(target_file, "MOV [R%d], R%d\n", temp, resultReg);
                freeReg(temp);
                freeReg(resultReg);
            }
            
            fprintf(target_file, "MOV SP, BP\n");
            fprintf(target_file, "POP BP\n");
            fprintf(target_file, "RET\n");
            return -1;
        }

        case NODE_INITIALIZE:
        {
            int *regs = calloc(MAX_REGS, sizeof(int));
            int  saved = saveRegisters(target_file, regs);

            int tmp = getReg();
            fprintf(target_file, "MOV R%d, \"Heapset\"\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "MOV R%d, 0\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);  
            fprintf(target_file, "PUSH R%d\n", tmp);   
            fprintf(target_file, "PUSH R%d\n", tmp);   
            fprintf(target_file, "PUSH R%d\n", tmp);   
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file, "SUB SP, 5\n");
            fprintf(target_file, "BRKP\n");
            // must change to ADD SP, 3 or something to save numebr of lines

            freeReg(tmp);
            restoreRegisters(target_file, regs, saved);
            free(regs);
            return -1;
        }

        case NODE_ALLOC:
        {
            int *regs = calloc(MAX_REGS, sizeof(int));
            int saved = saveRegisters(target_file, regs);

            int tmp = getReg();
            fprintf(target_file, "MOV R%d, \"Alloc\"\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "MOV R%d, 0\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "CALL 0\n");

            int retReg = getReg();
            fprintf(target_file, "MOV R%d, SP\n", retReg);
            fprintf(target_file, "MOV R%d, [R%d]\n", retReg, retReg);
            fprintf(target_file, "SUB SP, 5\n");

            freeReg(tmp);
            restoreRegisters(target_file, regs, saved);
            fprintf(target_file, "BRKP\n");
            free(regs);
            return retReg;
        }

        case NODE_FREE:
        {
            int val_reg = codeGen(t->left, target_file, NULL);

            int *regs = calloc(MAX_REGS, sizeof(int));
            int  saved = saveRegisters(target_file, regs);

            int tmp = getReg();
            fprintf(target_file, "MOV R%d, \"Free\"\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);        
            fprintf(target_file, "PUSH R%d\n", val_reg);    
            fprintf(target_file, "MOV R%d, 0\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);        
            fprintf(target_file, "PUSH R%d\n", tmp);        
            fprintf(target_file, "PUSH R%d\n", tmp);        
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file, "SUB SP, 5\n");

            freeReg(val_reg);
            freeReg(tmp);
            restoreRegisters(target_file, regs, saved);
            free(regs);
            return -1;
        }

        case NODE_NEW:
        {
            int *regs = calloc(MAX_REGS, sizeof(int));
            int saved = saveRegisters(target_file, regs);

            int tmp = getReg();
            fprintf(target_file, "MOV R%d, \"Alloc\"\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "MOV R%d, 0\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "CALL 0\n");

            int retReg = getReg();
            fprintf(target_file, "MOV R%d, SP\n",    retReg);
            fprintf(target_file, "MOV R%d, [R%d]\n", retReg, retReg);
            fprintf(target_file, "SUB SP, 5\n");

            freeReg(tmp);
            restoreRegisters(target_file, regs, saved);
            fprintf(target_file, "BRKP\n");
            free(regs);
            return retReg;
        }

        case NODE_DELETE:
        {
            int addr_reg = getAddrReg(t->left, target_file);
            
            int mem_ptr = getReg();
            fprintf(target_file, "MOV R%d, [R%d]\n", mem_ptr, addr_reg);
            
            int *regs = calloc(MAX_REGS, sizeof(int));
            int saved = saveRegisters(target_file, regs);
            
            int tmp = getReg();
            fprintf(target_file, "MOV R%d, \"Free\"\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", mem_ptr);
            fprintf(target_file, "MOV R%d, 0\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "PUSH R%d\n", tmp);
            fprintf(target_file, "CALL 0\n");
            fprintf(target_file, "SUB SP, 5\n");
            
            freeReg(tmp);
            freeReg(mem_ptr);
            restoreRegisters(target_file, regs, saved);
            free(regs);

            int zero = getReg();
            fprintf(target_file, "MOV R%d, 0\n", zero);
            fprintf(target_file, "MOV [R%d], R%d\n", addr_reg, zero);
            fprintf(target_file, "ADD R%d, 1\n", addr_reg);
            fprintf(target_file, "MOV [R%d], R%d\n", addr_reg, zero);
            freeReg(zero);
            freeReg(addr_reg);
            return -1;
        }

        case NODE_SELF:
        {
            struct Lsymbol *selfEntry = LLookup("self");
            if(!selfEntry) {
                fprintf(stderr, "Internal error: 'self' not found in LST\n");
                exit(1);
            }
            
            int addr_reg = getReg();
            fprintf(target_file, "MOV R%d, BP\n", addr_reg);
            fprintf(target_file, "ADD R%d, %d\n", addr_reg, selfEntry->binding);
            int val_reg = getReg();
            fprintf(target_file, "MOV R%d, [R%d]\n", val_reg, addr_reg);
            freeReg(addr_reg);
            return val_reg;
        }

        case NODE_METHOD_CALL:
        {
            int *regs = calloc(MAX_REGS, sizeof(int));
            int reg_pushed = saveRegisters(target_file, regs);
            
            int argCount = pushArgStack(t->right, target_file, 0);

            if(t->left->nodetype == NODE_SELF) 
            {
                struct Lsymbol *selfEntry = LLookup("self");
                if(!selfEntry) {
                    fprintf(stderr, "Internal error: 'self' not found in LST\n");
                    exit(1);
                }
                
                int addr_reg = getReg();
                fprintf(target_file, "MOV R%d, BP\n", addr_reg);
                fprintf(target_file, "ADD R%d, %d\n", addr_reg, selfEntry->binding);
                int heap_reg = getReg();
                fprintf(target_file, "MOV R%d, [R%d]\n", heap_reg, addr_reg);

                fprintf(target_file, "SUB R%d, 1\n", addr_reg);
                int vft_reg = getReg();
                fprintf(target_file, "MOV R%d, [R%d]\n", vft_reg, addr_reg);

                fprintf(target_file, "PUSH R%d\n", vft_reg);
                fprintf(target_file, "PUSH R%d\n", heap_reg);
                freeReg(heap_reg);
                fprintf(target_file, "PUSH R0\n");

                ClassTableEntry *cls = lookupClass(t->left->typeEntry->name);
                int methodId = getMethodIndex(cls, t->varname);

                int method_addr = getReg();

                fprintf(target_file, "MOV R%d, R%d\n", method_addr, vft_reg);
                fprintf(target_file, "ADD R%d, %d\n", method_addr, methodId);
                fprintf(target_file, "MOV R%d, [R%d]\n", method_addr, method_addr);

                freeReg(vft_reg);

                fprintf(target_file, "CALL R%d\n", method_addr);
                freeReg(method_addr);



                // MethodEntry *m = lookupMethod(selfClassEntry, t->varname);

                // if(!m) {
                //     fprintf(stderr, "Internal error: method '%s' not found in selfClassEntry\n", t->varname);
                //     exit(1);
                // }

                // fprintf(target_file, "CALL F%d\n", m->flabel);
            }
            else
            {
                int obj_addr = getAddrReg(t->left, target_file);

                int mem_ptr = getReg();
                fprintf(target_file, "MOV R%d, [R%d]\n", mem_ptr, obj_addr);

                int vft_ptr = getReg();
                fprintf(target_file, "MOV R%d, R%d\n", vft_ptr, obj_addr);
                fprintf(target_file, "ADD R%d, 1\n", vft_ptr);
                fprintf(target_file, "MOV R%d, [R%d]\n", vft_ptr, vft_ptr);
                freeReg(obj_addr);

                fprintf(target_file, "PUSH R%d\n", vft_ptr);
                fprintf(target_file, "PUSH R%d\n", mem_ptr);
                freeReg(mem_ptr);
                fprintf(target_file, "PUSH R0\n");

                ClassTableEntry *cls = lookupClass(t->left->typeEntry->name);
                int methodId = getMethodIndex(cls, t->varname);

                int method_addr = getReg();

                fprintf(target_file, "MOV R%d, R%d\n", method_addr, vft_ptr);
                fprintf(target_file, "ADD R%d, %d\n", method_addr, methodId);
                fprintf(target_file, "MOV R%d, [R%d]\n", method_addr, method_addr);

                freeReg(vft_ptr);

                fprintf(target_file, "CALL R%d\n", method_addr);
                freeReg(method_addr);
            }

            int resultReg = getReg();
            fprintf(target_file, "POP R%d\n", resultReg);

            int selfReg = getReg();
            fprintf(target_file, "POP R%d\n", selfReg);
            freeReg(selfReg);
            int vftReg = getReg();
            fprintf(target_file, "POP R%d\n", vftReg);
            freeReg(vftReg);

            for(int i = 0; i < argCount; i++) {
                int dummy = getReg();
                fprintf(target_file, "POP R%d\n", dummy);
                freeReg(dummy);
            }
            
            restoreRegisters(target_file, regs, reg_pushed);
            free(regs);
            return resultReg;
        }

        default:
        {
            printf("Unknown nodetype %d\n", t->nodetype);
            printf("Nodetype:%s\n",nodeTypeToString(t->nodetype));
            exit(1);
        }
    }
}
