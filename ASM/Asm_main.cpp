#include "/home/voffk4/Cpu/ASM/Asm.h"

is_debug_lvl_0(
    FILE *logs = fopen("logs", "w");
    FILE *listing = fopen("Listing", "w"); 
)
int is_reg = 1 << 5;  //при использовании регистра
int is_ram = 1 << 6;  //при использовании оперативки


int main(void)
{   
    FILE *sourse = fopen("/home/voffk4/Cpu/ASM/Sourse", "r");
    FILE *binary = fopen("Binary", "wb");

    is_debug_lvl_0(
        CHECK_PTR(sourse);
        CHECK_PTR(binary);
    )

    Text commands = {};

    constructText(sourse, &commands);

    char *binary_code = (char *) calloc(commands.string_amount * 2, sizeof(int));
    is_debug_lvl_0(CHECK_PTR(binary_code));
    
    Header header = {};
    header.sign = 'HM';
    header.ver = 0;
    header.hash = 0;

    Label_array marks = {};
    marks.mark = (Label *) calloc(10, sizeof(Label));
    getMarks(&commands, &marks);
    header.code_length += sizeof(Header);
    
    bool is_hlt = 0;
    char *CMD = nullptr;
    CMD = (char *) calloc(32, sizeof(char));

    for (int i = 0; i < commands.string_amount; i++)
    {   
        int arg = 0;
        char regsRAM[32] = {};
        int arg_amount = sscanf(commands.text[i].string, "%s %d", CMD, &arg) - 1;

        if (arg_amount < 0)
        {
            is_debug_lvl_0(
                PRINT_RESHETKA(logs);
                fprintf(logs, "not valid format for command\n");
                PRINT_RESHETKA(logs);
            )
        }
        else if (arg_amount == 0)
        {
            if (getLine(regsRAM, commands.text[i].string + strlen(CMD)) > 0)
            {
                arg_amount = -1;
            }
        }

        if (CMD[0] == ':') continue;

        #define DEF_CMD(num, name, num_arg, code)                                                           \
        if (strcmp(CMD, #name) == 0)                                                                        \
        {                                                                                                   \
            if (num_arg == 1)                                                                               \
            {                                                                                               \
                if (arg_amount == 1)                                                                        \
                {                                                                                           \
                    binary_code[header.code_length++] = num;  /*если обычный пуш*/                          \
                    header.real_length ++;                                                                  \
                    *((int *) (binary_code + header.code_length)) = arg;                                    \
                    is_debug_lvl_0(list(CMD, &arg, binary_code[header.code_length - 1], 0));                \
                    header.code_length += sizeof(int);                                                      \
                    header.real_length ++;                                                                  \
                }                                                                                           \
                else if (num == CMD_JMP || num == CMD_JA || num == CMD_JAE || num == CMD_JB ||              \
                         num == CMD_JBE || num == CMD_JE || num == CMD_JNE)                                 \
                {                                                                                           \
                    char mark_name[10] = {};                                                                \
                    sscanf(commands.text[i].string + strlen(CMD), "%s", mark_name);                         \
                    writeMark(binary_code, &marks, mark_name, &header, num);                                \
                }                                                                                           \
                else if (arg_amount == -1)                                                                  \
                {                                                                                           \
                    regsAndRAM(regsRAM, &(header), binary_code, num);                                       \
                    is_debug_lvl_0(list(CMD, regsRAM,                                                       \
                                   (int) *(binary_code + header.code_length - sizeof(int) - 1), 1));        \
                }                                                                                           \
            }                                                                                               \
            else                                                                                            \
            {                                                                                               \
                binary_code[header.code_length++] = CMD_##name;                                             \
                header.real_length ++;                                                                      \
                is_debug_lvl_0(list(CMD, &arg, binary_code[header.code_length - 1], 0));                    \
            }                                                                                               \
        }                                                                                                   \
        else   

        #include "/home/voffk4/Cpu/commands.inc"

        /*else*/
        {
            printf("ERROR\n");
        }

        #undef DEF_CMD
    }
    
    header.code_length -= sizeof(Header);
    *((Header *) binary_code) = header;
    
    /*for (int i = 0; i < code_size; i++)
    {
        printf("%d\n", binary_code[i]);
    }*/
    
    /*is_debug_lvl_0(
        if (!is_hlt) 
        {   
            PRINT_RESHETKA(logs);
            fprintf(logs, "ASM was failed with error code: %d --- ", ERRASM_NO_HLT);
            print_err_asm(ERRASM_NO_HLT);
            PRINT_RESHETKA(logs);
        }
    )*/

    fwrite(binary_code, sizeof(char) * (header.code_length + sizeof(Header)), 1, binary);

    free(binary_code);
    fclose(sourse);
    fclose(binary);
    finish_poem(&commands);
    is_debug_lvl_0(
        fclose(listing);
        fclose(logs);
    )

    return 0;
}