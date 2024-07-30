#include "common.h"
#include "shell.h"

#define MAX_COMMAND_LEN 100

void shell(void)
{
    unsigned short cmd[MAX_COMMAND_LEN];

    while (TRUE)
    {
        puts(L"poiOS> ");
        if(gets(cmd,MAX_COMMAND_LEN)<=0)
            continue;
        if(!strcmp(L"hello",cmd))
            puts(L"Hello UEFI!\n");
        else
            puts(L"Command not found.\n");
    }
    
}