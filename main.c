struct EFI_INPUT_KEY
{
    unsigned short ScanCode;
    unsigned short UnicodeChar;
};

struct EFI_SYSTEM_TABLE
{
    char _buf[44];
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL
    {
        unsigned long long _buf;
        unsigned long long (*ReadKeyStroke)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, struct EFI_INPUT_KEY *Key);
        void *WaitForKey;
    } *ConIn;
    unsigned long long _buf2;
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
    {
        unsigned long long _buf;
        unsigned long long (*OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, unsigned short *String);
        unsigned long long _buf2[4];
        unsigned long long (*ClearScreen)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    } *ConOut;
    unsigned long long _buf3[3];
    struct EFI_BOOT_SERVICES
    {
        unsigned long long _buf[10];
        unsigned long long (*WaitForEvent)(unsigned long long NumberOfEvents, void **Event, unsigned long long *Index);
    } *BootServices;
};

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    struct EFI_INPUT_KEY Key;
    unsigned long long waitidx;
    unsigned short str[3];
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    while (1)
    {
        // キー入力まで待機
        SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &waitidx);
        if (!SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key))
        {
            if (Key.UnicodeChar != L'\r')
            {
                str[0] = Key.UnicodeChar;
                str[1] = L'\0';
            }
            else
            {
                str[0] = L'\r';
                str[1] = L'\n';
                str[2] = L'\0';
            }
            SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
        }
    }
}