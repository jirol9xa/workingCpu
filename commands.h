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
    if ((code[cpu->ip - 1] & 32) != 0)
    {
        stackPush(&(cpu->stk), cpu->regs[*((int *) (code + cpu->ip))]);
        cpu->ip += sizeof(int);
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else if (((code[cpu->ip - 1] & 64) != 0))
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
    if ((code[cpu->ip - 1] & 32) != 0)
    {
        sleep(0.5);
        stackPop(&(cpu->stk), &(cpu->regs[*((int *) (code + cpu->ip))]));
        cpu->ip += sizeof(int);
        is_debug_lvl_0(cpu->real_ip ++);
    }
    else if ((code[cpu->ip - 1] & 64) != 0)
    {
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
})
DEF_CMD(10, MRK, 1,
{
    cpu->ip += sizeof(int) + 1;
})