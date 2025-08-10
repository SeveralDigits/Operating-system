#pragma once
#include "stdint.h"

// Special key codes
enum {
    KEY_NONE = 0,
    KEY_ESC  = 27,
    KEY_ENTER = '\n',
    KEY_BACKSPACE = '\b',
    KEY_TAB = '\t',

    // Special non-ASCII keys (start at 128)
    KEY_UP = 128,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_HOME,
    KEY_END,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_INSERT,
    KEY_DELETE,

    KEY_UNKNOWN = 255
};

// Function declarations
uint8_t getScanCode();
int keyboardAvailable();
uint8_t inb(uint16_t port);
int getKey(); // Returns ASCII or special key constant
