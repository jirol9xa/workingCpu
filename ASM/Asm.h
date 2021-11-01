#ifndef ASM.H
    #define ASM.h

    #include "/home/voffk4/Cpu/config.h"
    #include <string.h>


    struct Label
    {
        char name[10];
        int  ip_number;
    };

    struct Label_array
    {
        Label *mark;
        int  marks_amount;
        int capacity;
    };


    #if DEBUG_LVL > 0
        int list(char *CODE, void* arg, int code, int is_ram);
        int print_err_asm(int err);

        enum asm_errors
        {
            ERRASM_NO_HLT = 1
        };

    #endif

    int getLine(char *dest, char *sourse);

    int regsAndRAM(char *regsRAM, Header *header, char *code, int num);

    int getMarks(Text *command, Label_array *marks);

    int writeMark(char *binary_code, Label_array *marks, char *mark_name, Header *header, int CMD_TYPEJUMP);
#endif