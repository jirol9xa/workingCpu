#ifndef LOGSLIB_H
    #define LOGSLIB_H


    FILE *logs = fopen("logs", "w");


    #define PRINT_RESHETKA fprintf(logs, "#################################################################\n");
    #define PRINT_LINE printf("[%s:%d]\n", __func__, __LINE__);
    #define LOGSPRINT(code) fprintf(logs, code);

    
#endif