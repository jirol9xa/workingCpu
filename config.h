/* THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
THE FILE IS GENERATED AUTOMATICALLY!!!!!!!!!
*/




#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include "/home/voffk4/Cpu/onegin.h"
#include "/home/voffk4/Cpu/stack.h"

#define DEBUG_LVL 1


enum COMMANDS
{
    CMD_IN   = 0,
    CMD_HLT  = 1,
    CMD_PUSH = 2,
    CMD_OUT  = 3,
    CMD_ADD  = 4,
    CMD_SUB  = 5,
    CMD_MUL  = 6,
    CMD_DIV  = 7,
    CMD_POP  = 8,
    CMD_JMP  = 9,
    CMD_MRK  = 10,
    CMD_JA   = 11,
    CMD_JAE  = 12,
    CMD_JB   = 13,
    CMD_JBE  = 14,
    CMD_JE   = 15,
    CMD_JNE  = 16
};

struct Header
{
    int sign;
    int ver;
    int hash;
    int code_length;
    int real_length;
};


#define MEMCPY(type, arg)                                                            \
{                                                                                    \
    MemCpy(CODE + code_size, &arg, sizeof(type));                                    \
    code_size += sizeof(type);                                                       \
}            

#if DEBUG_LVL > 0
    #define PRINT_RESHETKA(logs) fprintf(logs, "#################################################################\n");
    #define PRINT_LINE() printf("[%s:%d]\n", __func__, __LINE__);
#endif