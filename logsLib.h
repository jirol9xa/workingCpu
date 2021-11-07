#ifndef LOGSLIB_H
    #define LOGSLIB_H


    static FILE *logs = fopen("logs", "a");


    #define PRINT_RESHETKA fprintf(logs, "#################################################################\n");
    #define LOGSPRINT(...) fprintf(logs, __VA_ARGS__);
    #define LOGSCLOSE fclose(logs);

    
#endif