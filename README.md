# UEIFの学習

参考資料:http://yuma.ohgami.jp/ubmp/UEFI-Bare-Metal-Programming_20170811.pdf
UEFI仕様書:https://uefi.org/sites/default/files/resources/UEFI_Spec_2_3_1.pdf

### ビルド
```bash
x86_64-w64-mingw32-gcc -Wall -Wextra -e efi_main -nostdinc -nostdlib -fno-builtin -Wl,--subsystem,10 -I. -o BOOTX64.EFI main.c common.c efi.c shell.c graphics.c gui.c
```
OR
```bash
make
```
USBメモリの`/EFI/BOOT/BOOTX64.EFI`に設置