#include "/home/voffk4/Cpu/config.h"
#include <string.h>

extern FILE *listing;
extern FILE *logs;


struct Mark
{
    char name[10];
    int  ip_number;
};


struct Mark_array
{
    Mark *mark;
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

int GetLine(char *dest, char *sourse);

int regsAndRAM(char *regsRAM, Header *header, char *code, int num);

int getMarks(Text *command, Mark_array *marks);


int writeMark(char *binary_code, Mark_array *marks, char *mark_name, Header *header);
