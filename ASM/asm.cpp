#include "/home/voffk4/cpu/ASM/Asm-header.h"

FILE *logs = fopen("logs", "w");
const int is_reg = 32;  //при использовании регистра
const int is_ram = 64;  //при использовании оперативки

is_debug_lvl_0( FILE *listing = fopen("Listing", "w") );

int main(void)
{   
    FILE *sourse = fopen("Sourse", "r");
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

    Mark_array marks = {};
    marks.mark = (Mark *) calloc(10, sizeof(Mark));
    getMarks(&commands, &marks);
    header.code_length += sizeof(Header);
    
    bool is_hlt = 0;
    char *CMD = nullptr;
    CMD = (char *) calloc(32, sizeof(char));
    PRINT_LINE();

    for (int i = 0; i < commands.string_amount; i++)
    {   
        int arg = 0;
        char regsRAM[32] = {};
        int arg_amount = sscanf(commands.text[i].string, "%s %d", CMD, &arg) - 1;

        if (arg_amount < 0)
        {
            PRINT_RESHETKA(logs);
            fprintf(logs, "not valid format for command\n");
            PRINT_RESHETKA(logs);
        }
        else if (arg_amount == 0)
        {
            if (GetLine(regsRAM, commands.text[i].string + strlen(CMD)) > 0)
            {
                arg_amount = -1;
            }
        }

        if (CMD[0] == ':')
        {
            PRINT_LINE();
            writeMark(binary_code, &marks, CMD + 1, &header);
            continue;
        }
        PRINT_LINE();
        #define DEF_CMD(num, name, num_arg, code)                                                           \
        if (strcmp(CMD, #name) == 0)                                                                        \
        {                                                                                                   \
            if (num_arg == 1)                                                                               \
            {                                                                                               \
                if (arg_amount == 1)                                                                        \
                {                                                                                           \
                    printf("cmd -- %s\n", CMD);                                                             \
                    binary_code[header.code_length++] = num;  /*если обычный пуш*/                          \
                    header.real_length ++;                                                                  \
                    *((int *) (binary_code + header.code_length)) = arg;                                    \
                    list(CMD, &arg, binary_code[header.code_length - 1], 0);                                \
                    header.code_length += sizeof(int);                                                      \
                    header.real_length ++;                                                                  \
                    printf("PIPISKA\n"); \
                }                                                                                           \
                else if (arg_amount == -1)                                                                  \
                {                                                                                           \
                    regsAndRAM(regsRAM, &(header), binary_code, num);                                       \
                    list(CMD, regsRAM, (int) *(binary_code + header.code_length - sizeof(int) - 1), 1);     \
                }                                                                                           \
            }                                                                                               \
            else                                                                                            \
            {                                                                                               \
                binary_code[header.code_length++] = CMD_##name;                                             \
                header.real_length ++;                                                                      \
                list(CMD, &arg, binary_code[header.code_length - 1], 0);                                    \
            }                                                                                               \
        }                                                                                                   \
        else   

        #include "/home/voffk4/cpu/commands.h"

        /*else*/
        {
            printf("ERROR\n");
        }

        #undef DEF_CMD
    }
    
    printf("code_size before writting = %d\n", header.code_length);
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

    PRINT_LINE();
    printf("code_size = %d\n", header.code_length);
    printf("sizeof(Header) = %d\n", sizeof(Header));
    return 0;
}