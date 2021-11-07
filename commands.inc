DEF_CMD(0, IN,   0, {
    printf("Enter the value:\n");
    int value = 0;
    while (scanf("%d", &value) != 1)
    {
        printf("Enter correct value (((((\n");
    }
    stackPush(&(cpu->stk), value);
})
DEF_CMD(1, HLT,  0, {
    return CMD_HLT;
})
DEF_CMD(2, PUSH, 1, {

    if (((code[cpu->ip - 1] & IS_REG) != 0) && ((code[cpu->ip - 1] & IS_RAM) != 0))
    {
        workWithParsedRAM(cpu, code, 0);
    }
    else if ((code[cpu->ip - 1] & IS_REG) != 0)
    {
        stackPush(&(cpu->stk), cpu->regs[*((int *) (code + cpu->ip))]);
        cpu->ip += sizeof(int);
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else if (((code[cpu->ip - 1] & IS_RAM) != 0))
    {   
        sleep(0.5);
        stackPush(&(cpu->stk), cpu->RAM[*((int *) (code + cpu->ip))]);
        cpu->ip += sizeof(int);
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else
    {
    int value = *((int*) (code + cpu->ip));
    stackPush(&(cpu->stk), value);
    cpu->ip += sizeof(int);
    is_debug_lvl_0(cpu->real_ip ++);
    }
})
DEF_CMD(3, OUT,  0, {
    int value = 0;
    stackPop(&(cpu->stk), &value);
    printf("%d\n", value);
    stackPush(&(cpu->stk), value);
})
DEF_CMD(4, ADD,  0, {
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    stackPush(&(cpu->stk), first + second);
})
DEF_CMD(5, SUB,  0, {
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    stackPush(&(cpu->stk), second - first);
})
DEF_CMD(6, MUL,  0, {
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    stackPush(&(cpu->stk), first * second);
})
DEF_CMD(7, DIV,  0, {
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    stackPush(&(cpu->stk), second / first);
})
DEF_CMD(8, POP,  1,
{   
    if ((code[cpu->ip - 1] & IS_REG) != 0 && (code[cpu->ip - 1] & IS_RAM) != 0)
    {
        workWithParsedRAM(cpu, code, 1);
    }
    else if ((code[cpu->ip - 1] & IS_REG) != 0)
    {
        stackPop(&(cpu->stk), &(cpu->regs[*((int *) (code + cpu->ip))]));
        cpu->ip += sizeof(int);
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else if ((code[cpu->ip - 1] & IS_RAM) != 0)
    {
        sleep(0.5);
        stackPop(&(cpu->stk), &(cpu->RAM[*((int *) (code + cpu->ip))]));
        cpu->ip += sizeof(int);
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else
    {
        int value = 0;
        stackPop(&(cpu->stk), &value);
    }
})
DEF_CMD(9, JMP,  1,
{
    cpu->ip = *((int *) (code + cpu->ip));
    is_debug_lvl_0(cpu->real_ip ++);
})
DEF_CMD(10, MRK, 1,
{
    ;
})
DEF_CMD(11, JA, 1,
{
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    if (second > first)
    {
        cpu->ip = *((int *) (code + cpu->ip));
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else
    {
        cpu->ip += sizeof(int);
        cpu->real_ip ++;
    }
})
DEF_CMD(12, JAE, 1,
{
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    if (second >= first)
    {
        cpu->ip = *((int *) (code + cpu->ip));
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else
    {
        cpu->ip += sizeof(int);
        cpu->real_ip ++;
    }
})
DEF_CMD(13, JB, 1,
{
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    if (second < first)
    {
        cpu->ip = *((int *) (code + cpu->ip));
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else
    {
        cpu->ip += sizeof(int);
        cpu->real_ip ++;
    }
})
DEF_CMD(14, JBE, 1,
{
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    if (second <= first)
    {
        cpu->ip = *((int *) (code + cpu->ip));
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else
    {
        cpu->ip += sizeof(int);
        cpu->real_ip ++;
    }
})
DEF_CMD(15, JE, 1,
{
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    if (second == first)
    {
        cpu->ip = *((int *) (code + cpu->ip));
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else
    {
        cpu->ip += sizeof(int);
        cpu->real_ip ++;
    }
})
DEF_CMD(16, JNE, 1,
{
    int first = 0;
    int second = 0;
    stackPop(&(cpu->stk), &first);
    stackPop(&(cpu->stk), &second);
    if (second != first)
    {
        cpu->ip = *((int *) (code + cpu->ip));
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else
    {
        cpu->ip += sizeof(int);
        cpu->real_ip ++;
    }
})
DEF_CMD(17, CALL, 1,
{
    stackPush(&(cpu->ret), cpu->ip + sizeof(type_t));
    cpu->ip = *((int *) (code + cpu->ip));
})
DEF_CMD(18, RET, 1,
{
    stackPop(&(cpu->ret), &(cpu->ip));
})


/*#define DEF_IFJMP(name, sign)                                 \
    DEF_CMD('sign', name, 1,                                    \
    {                                                           \
        int first = 0;                                          \
        int second = 0;                                         \
        stackPop(&(cpu->stk), &first);                          \
        stackPop(&(cpu->stk), &second);                         \
        if (second sign first)                                  \
        {                                                       \
            cpu->ip = *((int *) (code + cpu->ip));              \
            is_debug_lvl_0(cpu->real_ip ++);                    \
        }                                                       \
        else                                                    \
        {                                                       \
            cpu->ip += sizeof(int);                             \
            cpu->real_ip ++;                                    \
        }                                                       \
    })
DEF_IFJMP(JA, >);
DEF_IFJMP(JAE, >=);
DEF_IFJMP(JB, <);
DEF_IFJMP(JBE, <=);
DEF_IFJMP(JE, ==);
DEF_IFJMP(JNE, !=);*/