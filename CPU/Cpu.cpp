#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cmath>
#include "../config.h"

#if DEBUG_LVL > 0
    extern FILE *logs;
#endif

#include "../textLib.h"
#include "../stackLib.h"
#include "../ASM/Asm.h"
#include "Cpu.h"


is_debug_lvl_0(
    /*!
        \brief  Функция дампа для проца
        \param  [CPU *]cpu Указатель на процессор
        \param  [char *]binary_code Массив с кодом
        \param  [FILE *]logs Лог файл, куда будет
                записываться дамп
    */
    static void cpuDump(CPU *cpu, char *binary_code, FILE *logs)
    {
        PRINT_RESHETKA(logs);
        PRINT_RESHETKA(logs);
        PRINT_RESHETKA(logs);
        fprintf(logs, "        ");
        for (int i = 0; i < cpu->real_size; i++)
        {
            fprintf(logs, " %2d", i);
        }
        fprintf(logs, "\n");
        fprintf(logs, "Commands");
        for (int i = 0; i < cpu->code_size; i++)
        {
            fprintf(logs, " %2d", (int) binary_code[i]);                                                                                                                              
            if ((binary_code[i] && is_reg) != 0 || (binary_code[i] && is_ram) != 0)       
            {                                   
                i ++;                                                      
                fprintf(logs, " %2d", *((int *) (binary_code + i)));                            
                i += sizeof(int) - 1;                                                               
            }                                                                                                                                                                                      
        }
        fprintf(logs, "\n");
        fprintf(logs, "%*s----------- current command\n", cpu->real_ip * 3 + 8, "^");

        fprintf(logs, "Regs\n" "ax --- %d\n" "bx --- %d\n" "cx --- %d\n" "dx --- %d\n", cpu->regs[0], 
                cpu->regs[1], cpu->regs[2], cpu->regs[3]);
        
        PRINT_RESHETKA(logs);
        PRINT_RESHETKA(logs);
        PRINT_RESHETKA(logs);
        fprintf(logs, "\n\n\n");
    }
)


int createCpu(CPU *cpu)
{
    CHECK_PTR(cpu);

    stackCtor(&(cpu->stk), 0);
    stackCtor(&(cpu->ret), 0);
    return 0;
}


/*!
    \brief  Функция работы процессора
    \param  [Header *]header Указатель на
            хедер бинарника
    \param  [CPU *]cpu Указатель на процессор
    \return 0 в случае успеха, 1 в противном
            случае
*/
int processing(Header *header, char *code, CPU *cpu)
{
    is_debug_lvl_0(
        CHECK_PTR(header);
        CHECK_PTR(code);
        CHECK_PTR(cpu);
    );

    cpu->ip = 0;
    while (cpu->ip < header->code_length)
    {
        switch (code[cpu->ip ++] & (is_reg - 1))
        {

            #define DEF_CMD(num, name, num_args, cmd_code)                                                       \
            case CMD_##name:                                                                                     \
                is_debug_lvl_0(cpu->real_ip ++);                                                                 \
                is_debug_lvl_0(cpuDump(cpu, code, logs));                                                        \
                cmd_code;                                                                                        \
            break;

            #include "../commands.inc"
            #undef DEF_CMD
        }
    }
    return 0;
}
