#include "/home/voffk4/Cpu/CPU/cpu_header.h"

FILE *logs = fopen("logs", "w");

int main(void)
{
    FILE *Code = fopen("/home/voffk4/Cpu/ASM/Binary", "r");
    CHECK_PTR(Code);

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
            #if DEBUG_LVL > 0
                fclose(logs);
            #endif
        }
    }  
    else
    {
        #if DEBUG_LVL > 0
            fprintf(logs, "\n\n##################################################" 
                            "\n\nERR_WRONG_SIGNATURE\n\n"
                            "##################################################\n");
        #endif
        fclose(Code);
        #if DEBUG_LVL > 0
            fclose(logs);
        #endif
    }

    return 0;
}
