#include "/home/voffk4/cpu/config.h"

struct CPU {
    int regs[4];    //ax, bx, cx, dx
    Stack stk;
    int ip;
    int RAM[1000];
    int code_size;
    is_debug_lvl_0(
    int real_size;
    int real_ip;
    )
};

int processing(Header *header, char *code, CPU *cpu);

#define CREATE_CPU(name)                                                                            \
    CPU name = {};                                                                                  \
    stackCtor(&name.stk, 0);                                                                           


