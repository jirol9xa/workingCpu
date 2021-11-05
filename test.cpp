#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define DEBUG_LVL 3
typedef int type_t;
FILE *logs = fopen("testlogs", "w");

#include "stackLib.h"

#define PRINT_LINE() printf("[%s:%d]\n", __func__, __LINE__);


int main(void)
{
    Stack stk = {};
    PRINT_LINE();
    stackCtor(&stk, 1);
    //STACK_DUMP(&stk);
    PRINT_LINE();
    stackPush(&stk, 5);
    printf("capacity --- %d\n", stk.data[0]);
    type_t a = {};
    PRINT_LINE();
    stackPop(&stk, &a);

    printf("%d\n", a);
    return 0;
}