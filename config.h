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


#define DEBUG_LVL 3

typedef int type_t;

const int is_reg = 1 << 5;  //при использовании регистра
const int is_ram = 1 << 6;  //при использовании оперативки

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
    CMD_JNE  = 16,
    CMD_CALL = 17,
    CMD_RET  = 18
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
    MemCpy(CODE + code_size, &arg, sizeof(type_t));                                    \
    code_size += sizeof(type_t);                                                       \
}            

#if DEBUG_LVL > 0
    #define PRINT_RESHETKA(logs) fprintf(logs, "#################################################################\n");
    #define PRINT_LINE() printf("[%s:%d]\n", __func__, __LINE__);
#endif