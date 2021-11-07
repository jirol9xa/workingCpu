#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "logsLib.h"

static FILE *logs = nullptr;


int openLogs()
{
    logs = fopen("/home/voffk4/Cpu/LOGS/logs", "a");

    if (logs == nullptr)
    {
        printf("!!! ERROR can't open log file !!!\n");
        return -1;
    }

    return 0;
}


int closeLogs()
{
    fclose(logs);
}


void writeLogs(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    vfprintf(logs, format, args);

    va_end(args);
}


void FFlush()
{
    fflush(logs);
}


void printReshetka()
{
    writeLogs("#################################################################\n");
}
