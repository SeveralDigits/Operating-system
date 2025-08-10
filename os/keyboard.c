#include "keyboard.h"

uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

int keyboardAvailable() {
    return inb(0x64) & 1;
}

uint8_t getScanCode() {
    while (!keyboardAvailable());
    return inb(0x60);
}

// Simple ASCII map for basic scan codes (set 1)
static char scanCodeToChar[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0,'*',0,' ',
    // Add more keys as needed
};

int getKey() {
    uint8_t sc = getScanCode();

    // Check for extended scan codes (e.g., arrow keys, function keys)
    if (sc == 0xE0) {
        uint8_t ext = getScanCode(); // Read the next scan code after 0xE0

        switch (ext) {
            case 0x48: return KEY_UP;
            case 0x50: return KEY_DOWN;
            case 0x4B: return KEY_LEFT;
            case 0x4D: return KEY_RIGHT;
            case 0x47: return KEY_HOME;
            case 0x4F: return KEY_END;
            case 0x49: return KEY_PAGE_UP;
            case 0x51: return KEY_PAGE_DOWN;
            case 0x52: return KEY_INSERT;
            case 0x53: return KEY_DELETE;
            default: return KEY_UNKNOWN;
        }
    }

    // Regular scan code to ASCII character
    if (sc < 128)
        return scanCodeToChar[sc];

    return KEY_NONE;
}
