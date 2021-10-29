#include "/home/voffk4/Cpu/ASM/Asm-header.h"
#include <cmath>

extern FILE *logs;


static int Atoi(char *number, int size = 0)
{
    int num = 0;
    if (size == 0) size = strlen(number);
    printf("size ----> %d\n", size);

    for (int i = 0; i < size && number[i] != '\0'; i++)
    {
        num += (number[i] - 48) * pow(10, size - 1 - i);
    }

    return num;
}


#if DEBUG_LVL > 0
    /*!
        \brief  Функция печати листинга
        \param  [char *]CODE массив с кодом
        \param  [int]arg аргумент
        \param  [int]code Код команды
        \return 0, если все успешно, 1
                в противном случае
    */
    int list(char *CODE, void* arg, int code, int is_ram)
    {
        CHECK_PTR(CODE);

        if (!is_ram)
        {
        int *Arg = (int *) arg;
        fprintf(listing, "%4s %10d    ------------->  %4d %10d\n", CODE, *Arg, code, *Arg);
        return 0;
        }
        else
        {
            PRINT_LINE();
            char *Arg = (char *) arg;
            if (Arg[0] == '[')
            {
                int adr = Atoi(Arg + 1, strlen(Arg) - 2);
                fprintf(listing, "%4s %10s    ------------->  %4d %10d\n", CODE, Arg, code, adr);
            }
            else
            {   
                fprintf(listing, "%4s %10s    ------------->  %4d %10d\n", CODE, Arg, code, Arg[0] - 96);   
            }
            return 0;
        }
    }


    /*!
        \brief  Функция печати ошибки
        \param  [int]err Код ошибки
    */
    int print_err_asm(int err)
    {
        switch (err)
        {
            case ERRASM_NO_HLT:
                fprintf(logs, "ERRASM_NO_HLT\n");
                break;
        }
    }
#endif


/*!
    \brief  Функция считывания строки
    \param  [char *]arg Строка, 
*/
int GetLine(char *dest, char *sourse)
{
    int i = 0, j = 0;

    while (sourse[j] == ' ') 
    {
        j ++;
        continue;
    }
    for (; sourse[i + j] != '\n' && sourse[i + j] != '\0'; i++)
    {
        dest[i] = sourse[i + j];
    }

    return i;
}


int regsAndRAM(char *regsRAM, Header *header, char *code, int num)
{
    if (regsRAM[0] == '[')
    {
        code[header->code_length++] = (num | 64);
        header->real_length ++;
        int adress = Atoi(regsRAM + 1, strlen(regsRAM) - 2);
        *((int*) (code + header->code_length)) = adress;
        //list(regsRAM, &adress, num | 64, 1);
        header->code_length += sizeof(int);
        header->real_length ++;
    }
    else{
        code[header->code_length++] = (num | 32);
        header->real_length ++;
        switch(regsRAM[0])
        {
            case 'a':
                *((int*) (code + header->code_length)) = 0;
                header->code_length += sizeof(int);
                header->real_length ++;
                break;
            case 'b':
                *((int*) (code + header->code_length)) = 1;
                header->code_length += sizeof(int);
                header->real_length ++;
                break;
            case 'c':
                *((int*) (code + header->code_length)) = 2;
                header->code_length += sizeof(int);
                header->real_length ++;
                break;
            case 'd':
                *((int*) (code + header->code_length)) = 3;
                header->code_length += sizeof(int);
                header->real_length ++;
                break;
        }
        //list(regsRAM, code - 1, num | 32, 1);
    }
    //каким-то образом записать в бинарник код регистра или оперативкиы
    
    return 0;
}


int getMarks(Text *command, Mark_array *marks)
{
    int getMarks_ip = 0;

    for (int i = 0; i < command->string_amount; i++)
    {

        #define DEF_CMD(num, name, num_arg, code)                                                                       \
        if (strncmp(#name, command->text[i].string, strlen(#name)) == 0)                                                \
        {                                                                                                               \
            if (num_arg > 0)                                                                                            \
            {                                                                                                           \
                getMarks_ip += 1 + sizeof(int);                                                                         \
            }                                                                                                           \
            else                                                                                                        \
            {                                                                                                           \
                getMarks_ip ++;                                                                                         \
            }                                                                                                           \
        }
        
        #include "/home/voffk4/Cpu/commands.h"
        #undef DEF_CMD
        if (command->text[i].string[0] == ':')
        {
            if (marks->marks_amount + 1 < marks->capacity)
            {
                void *temp_ptr = nullptr;
                temp_ptr = realloc(marks->mark, sizeof(Mark) * marks->capacity * 2);
                marks->mark = (Mark *) temp_ptr;
                marks->capacity *= 2;
            }

            int sscanf_status = sscanf(command->text[i].string + 1, "%s", marks->mark[marks->marks_amount].name);
            if (sscanf_status)
            {
                //getMarks_ip += sizeof(int) + 1;
                marks->mark[marks->marks_amount++].ip_number = getMarks_ip;
            }
            else
            {
                printf("getMarks ERROR\n");
                return 1;
            }
        }
    }

    return 0;
}


int writeMark(char *binary_code, Mark_array *marks, char *mark_name, Header *header)
{   
    PRINT_LINE();
    for (int i = 0; i < marks->marks_amount; i++)
    {
        PRINT_LINE();
        if (strcmp(marks->mark[i].name, mark_name) == 0)
        {
            PRINT_LINE();
            binary_code[header->code_length ++] = CMD_JMP;
            header->real_length ++;
            *((int *) (binary_code + header->code_length)) = marks->mark[i].ip_number;
            printf("###MARKS###\ncode -- %d, arg -- %d\n", binary_code[header->code_length - 1], binary_code[header->code_length]);
            header->code_length += sizeof(int);
            header->real_length ++;
            return 0;
        }
    }
}
