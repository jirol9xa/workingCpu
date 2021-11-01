#include "/home/voffk4/Cpu/CPU/Cpu.h"

is_debug_lvl_0(FILE *logs = fopen("logs", "w"));


int main(void)
{
    FILE *Code = fopen("/home/voffk4/Cpu/ASM/Binary", "r");
    is_debug_lvl_0(CHECK_PTR(Code));

    Header header = {};

    fread(&header, 1, sizeof(Header), Code);
    
    if (header.sign = 'MH')
    {
        char *binary_code = (char *) calloc(header.code_length + 1, sizeof(char));
        fread(binary_code, header.code_length, sizeof(char), Code);

        CREATE_CPU(cpu);
        cpu.code_size = header.code_length;
        cpu.real_size = header.real_length;

        if (processing(&header, binary_code, &cpu) == CMD_HLT)
        {
            free(binary_code);
            stackDtor(&cpu.stk);
            fclose(Code);
            is_debug_lvl_0(fclose(logs));
            return 0;
        }
    }  
    else
    {
        is_debug_lvl_0(
            fprintf(logs, "\n\n##################################################" 
                            "\n\nERR_WRONG_SIGNATURE\n\n"
                            "##################################################\n");
        )
        fclose(Code);
        is_debug_lvl_0(fclose(logs));
    }

    return 0;
}
