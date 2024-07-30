#include "efi.h"
#include "graphics.h"
#include "common.h"

const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL white = {0xff, 0xff, 0xff, 0xff};
const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL yellow = {0x00, 0xff, 0xff, 0xff};

void draw_pixel(unsigned int x, unsigned int y, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL color)
{
    unsigned int hr = GOP->Mode->Info->HorizontalResolution; // 水平解像度

    struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = (struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GOP->Mode->FrameBufferBase; // フレームバッファの先頭アドレス

    struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (hr * y) + x; // 描画するピクセルのアドレス

    p->Blue = color.Blue;
    p->Green = color.Green;
    p->Red = color.Red;
    p->Reserved = color.Reserved;
}

void draw_rect(struct RECT r, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL c)
{
    unsigned int i;

    for (i = r.x; i < (r.x + r.w); i++)
        draw_pixel(i, r.y, c);
    for (i = r.x; i < (r.x + r.w); i++)
        draw_pixel(i, r.y + r.h - 1, c);

    for (i = r.y; i < (r.y + r.h); i++)
        draw_pixel(r.x, i, c);
    for (i = r.y; i < (r.y + r.h); i++)
        draw_pixel(r.x + r.w - 1, i, c);
}

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL get_pixel(unsigned int x, unsigned int y)
{
    unsigned int hr = GOP->Mode->Info->HorizontalResolution; // 水平解像度

    struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = (struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GOP->Mode->FrameBufferBase; // フレームバッファの先頭アドレス

    struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (hr * y) + x; // 描画するピクセルのアドレス

    return *p;
}

unsigned char is_in_rect(unsigned int x, unsigned int y, struct RECT r)
{
    if (r.x <= x && x < (r.x + r.w - 1) && r.y <= y && y < (r.y + r.h - 1))
        return TRUE;
    else
        return FALSE;
}