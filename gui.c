#include "efi.h"
#include "common.h"
#include "graphics.h"
#include "gui.h"
#include "file.h"

#define WIDTH_PER_CH 8
#define HEIGHT_PER_CH 20

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL cursor_tmp = {0, 0, 0, 0};
int cursor_old_x = 0;
int cursor_old_y = 0;

void draw_cursor(int x, int y)
{
    draw_pixel(x, y, white);
}

void save_cursor_area(int x, int y)
{
    cursor_tmp = get_pixel(x, y);
    cursor_tmp.Reserved = 0xff;
}

void load_cursor_area(int x, int y)
{
    draw_pixel(x, y, cursor_tmp);
}

void put_cursor(int x, int y)
{
    if (cursor_tmp.Reserved)
        load_cursor_area(cursor_old_x, cursor_old_y);

    save_cursor_area(x, y);

    draw_cursor(x, y);

    cursor_old_x = x;
    cursor_old_y = y;
}

int ls_gui(void)
{
    int file_num;
    struct RECT t;
    int idx;

    ST->ConOut->ClearScreen(ST->ConOut);

    file_num = ls();

    t.x = 0;
    t.y = 0;
    t.w = (MAX_FILE_NAME_LEN - 1) * WIDTH_PER_CH;
    t.h = HEIGHT_PER_CH;

    for (idx = 0; idx < file_num; idx++)
    {
        file_list[idx].rect.x = t.x;
        file_list[idx].rect.y = t.y;
        file_list[idx].rect.w = t.w;
        file_list[idx].rect.h = t.h;
        draw_rect(file_list[idx].rect, white);
        t.x += file_list[idx].rect.w + WIDTH_PER_CH;

        file_list[idx].is_highlight = FALSE;
    }

    return file_num;
}

void gui(void)
{
    struct RECT r = {10, 10, 20, 20};

    unsigned long long status;
    struct EFI_SIMPLE_POINTER_STATE s;
    int px = 0, py = 0;
    unsigned long long waitidx;
    unsigned char is_highlist = FALSE;
    int file_num;
    int idx;

    ST->ConOut->ClearScreen(ST->ConOut);
    SPP->Reset(SPP, FALSE);

    file_num = ls_gui();

    while (TRUE)
    {
        ST->BootServices->WaitForEvent(1, &(SPP->WaitForInput), &waitidx);
        status = SPP->GetState(SPP, &s);
        if (!status)
        {
            px += s.RelativeMovementX >> 13;
            if (px < 0)
                px = 0;
            else if (GOP->Mode->Info->HorizontalResolution <= (unsigned int)px)
                px = GOP->Mode->Info->HorizontalResolution - 1;
            py += s.RelativeMovementY >> 13;
            if (py < 0)
                py = 0;
            else if (GOP->Mode->Info->VerticalResolution <= (unsigned int)py)
                py = GOP->Mode->Info->VerticalResolution - 1;

            put_cursor(px, py); // カーソルを描画

            for (idx = 0; idx < file_num; idx++)
            {
                if (is_in_rect(px, py, file_list[idx].rect))
                {
                    if (!file_list[idx].is_highlight)
                    {
                        draw_rect(file_list[idx].rect, yellow);
                        file_list[idx].is_highlight = TRUE;
                    }
                }
                else
                {
                    if (file_list[idx].is_highlight)
                    {
                        draw_rect(file_list[idx].rect, white);
                        file_list[idx].is_highlight = FALSE;
                    }
                }
            }
        }
    }
}