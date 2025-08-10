#include "vga.h"
#include "keyboard.h"

#define INPUT_BUFFER_SIZE 256
char input_buffer[INPUT_BUFFER_SIZE];
int input_index = 0;

void kmain(void) {
    Reset(); // Clear screen
    print("Simple Terminal Mode:\r\n");

    bool terminal = true;
    int x = 0, y = 2; // Start typing from line 2

    while (1) {
        int key = getKey();

        if (key >= 32 && key <= 126) {
            // Printable ASCII character
            setCharAt(x, y, (char)key, COLOR8_WHITE, COLOR8_BLACK);
            x++;

            if (terminal && input_index < INPUT_BUFFER_SIZE - 1) {
                input_buffer[input_index++] = (char)key;
                input_buffer[input_index] = '\0'; // Null-terminate for safety
            }

            // Wrap to next line if end of screen width
            if (x >= width) {
                x = 0;
                y++;
                if (y >= height) {
                    scrollUp();
                    y = height - 1;
                }
            }

        } else if (key == KEY_BACKSPACE) {
            if (x > 0) {
                x--;
            } else if (y > 2) {
                y--;
                x = width - 1;
            }

            if (terminal && input_index > 0) {
                input_index--;
                input_buffer[input_index] = '\0'; // Clear last char
            }

            setCharAt(x, y, ' ', COLOR8_WHITE, COLOR8_BLACK);
        } else if (key == KEY_ENTER) {
            if (terminal) {
                // Example: Echo the full command back
                print(input_buffer); // Or write to VGA using setCharAt, char by char

                // Reset buffer
                input_index = 0;
                input_buffer[0] = '\0';

                // Move to next line
                x = 0;
                y++;
                // ... scroll check
                if (y >= height) {
                    scrollUp();
                    y = height - 1;
                }
            } else {
                x = 0;
                y++;
                if (y >= height) {
                    scrollUp();
                    y = height - 1;
                }

            }
        }
    }
}
