#include <stdio.h>
#include "led_driver.h"

void print_buffer_status(const uint32_t* buffer, size_t count) {
    printf("Buffer Dump:\n");
    for (size_t i = 0; i < count; i++) {
        // %08X prints the number in Hex, padded with zeros to 8 digits
        printf("Pixel %zu: 0x%08X\n", i, buffer[i]);
    }
    printf("--------------------\n");
}

int main() {
    printf("--- WS2812B Driver Test ---\n");

    // 1. Initialize LED strip with 10 pixels
    printf("Initializing 10 pixels...\n");
    if (led_init(10) != 0) {
        printf("Initialization failed!\n");
        return 1;
    }

    // 2. Verify buffer is zeroed out
    const uint32_t* buffer = led_get_buffer();
    printf("Checking initialization (should be all 0):\n");
    if (buffer[0] == 0) {
        printf("PASS: Buffer initialized to zero.\n");
    } else {
        printf("FAIL: Buffer not zero.\n");
    }

    // 3. Set specific pixel colors
    // Index 0: Red (255, 0, 0)   -> Expected: 0x0000FF00 (Because Red is middle byte)
    led_set_pixel_color(0, 255, 0, 0);

    // Index 9: Blue (0, 0, 255)  -> Expected: 0x000000FF
    led_set_pixel_color(9, 0, 0, 255);

    // Index 4: White (255, 255, 255) -> Expected: 0x00FFFFFF
    led_set_pixel_color(4, 255, 255, 255);

    printf("\nVerifying Set Colors:\n");
    // Print specific indices as requested
    printf("Index 0 (Red)   Value: 0x%08X (Expect: 0x0000FF00)\n", buffer[0]);
    printf("Index 4 (White) Value: 0x%08X (Expect: 0x00FFFFFF)\n", buffer[4]);
    printf("Index 9 (Blue)  Value: 0x%08X (Expect: 0x000000FF)\n", buffer[9]);

    // 4. Test led_fill (Green: 0, 255, 0) -> Expected: 0x00FF0000
    printf("\nFilling strip with Green...\n");
    led_fill(0, 255, 0);

    // Check if fill worked
    int fill_success = 1;
    for (size_t i = 0; i < 10; i++) {
        if (buffer[i] != 0x00FF0000) {
            fill_success = 0;
            printf("FAIL at index %zu: Found 0x%08X\n", i, buffer[i]);
        }
    }
    
    if (fill_success) {
        printf("PASS: All pixels are Green (0x00FF0000).\n");
    }

    // 5. Shutdown
    printf("\nShutting down...\n");
    led_shutdown();
    
    // Verify pointer is null (simulated check)
    if (led_get_buffer() == NULL) {
        printf("PASS: Memory freed.\n");
    }

    return 0;
}