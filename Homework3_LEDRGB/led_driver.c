#include "led_driver.h"
#include <stdlib.h> // For calloc, free
#include <string.h> // For memset

// Private variables to manage state
static uint32_t* led_buffer = NULL;
static size_t pixel_count = 0;

int led_init(size_t num_pixels) {
    if (num_pixels == 0) {
        return -1;
    }

    // Allocate memory and initialize to 0 (calloc)
    // We store the pointer in the static variable 'led_buffer'
    led_buffer = (uint32_t*)calloc(num_pixels, sizeof(uint32_t));

    if (led_buffer == NULL) {
        // Memory allocation failed
        return -1;
    }

    pixel_count = num_pixels;
    return 0; // Success
}

void led_shutdown() {
    if (led_buffer != NULL) {
        free(led_buffer);
        led_buffer = NULL;
    }
    pixel_count = 0;
}

void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b) {
    // 1. Safety Check: Ensure buffer exists and index is valid
    if (led_buffer == NULL || index >= pixel_count) {
        return; // Silently ignore out-of-bounds or uninitialized access
    }

    // 2. Bit Manipulation: Pack 3 bytes into one uint32_t
    // Format required: 00000000 GGGGGGGG RRRRRRRR BBBBBBBB
    // We cast to uint32_t before shifting to prevent overflow on 16-bit systems
    uint32_t color_value = ((uint32_t)g << 16) | 
                           ((uint32_t)r << 8)  | 
                           (uint32_t)b;

    // 3. Store the value in the buffer
    led_buffer[index] = color_value;
}

void led_fill(uint8_t r, uint8_t g, uint8_t b) {
    if (led_buffer == NULL) return;

    // Calculate the color value once
    uint32_t color_value = ((uint32_t)g << 16) | 
                           ((uint32_t)r << 8)  | 
                           (uint32_t)b;

    // Apply to all pixels
    for (size_t i = 0; i < pixel_count; i++) {
        led_buffer[i] = color_value;
    }
}

void led_clear() {
    // Check if buffer exists
    if (led_buffer != NULL && pixel_count > 0) {
        // Efficiently set memory to 0 using memset
        memset(led_buffer, 0, pixel_count * sizeof(uint32_t));
    }
}

const uint32_t* led_get_buffer() {
    return led_buffer;
}

size_t led_get_pixel_count() {
    return pixel_count;
}