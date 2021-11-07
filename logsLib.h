#ifndef LOGSLIB_H
    #define LOGSLIB_H

    int openLogs();
    void writeLogs(const char *format, ...);
    int closeLogs();
    void FFlush();
    void printReshetka();

#endif