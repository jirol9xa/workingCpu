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
    #define DEF_CMD(num, name, num_agrs, code)                         \
    CMD_##name = num,
    
    #include "commands.inc"

    #undef DEF_CMD
};

struct Header
{
    int sign;
    int ver;
    int hash;
    int code_length;
    int real_length;
};


#define MEMCPY(type, arg)                                                              \
{                                                                                      \
    MemCpy(CODE + code_size, &arg, sizeof(type_t));                                    \
    code_size += sizeof(type_t);                                                       \
}            

#if DEBUG_LVL > 0
    #define PRINT_RESHETKA(logs) fprintf(logs, "#################################################################\n");
    #define PRINT_LINE() printf("[%s:%d]\n", __func__, __LINE__);
#endif