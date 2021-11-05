#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "../config.h"

#if DEBUG_LVL > 0
    FILE *logs = fopen("logs", "w");
#endif

#include "../textLib.h"
#include "../stackLib.h"
#include "../ASM/Asm.h"
#include "Cpu.h"


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

        CPU cpu = {};
        createCpu(&cpu);
        cpu.code_size = header.code_length;
        cpu.real_size = header.real_length;

        if (processing(&header, binary_code, &cpu) == CMD_HLT)
        {
            free(binary_code);
            stackDtor(&cpu.stk);
            stackDtor(&cpu.ret);
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
