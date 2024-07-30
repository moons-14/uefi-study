#ifndef _FILE_H_
#define _FILE_H_

#include "graphics.h"

#define MAX_FILE_NAME_LEN 4
#define MAX_FILE_NUM 10
#define MAX_FILE_BUF 1024

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

struct FILE
{
    struct RECT rect;
    unsigned char is_highlight;
    unsigned short name[MAX_FILE_NAME_LEN];
};

extern struct FILE file_list[MAX_FILE_NUM];

#endif
