#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stddef.h> // Required for size_t

// Initializes a buffer for the LED strip
int led_init(size_t num_pixels);

// Frees the memory allocated for the LED strip
void led_shutdown();

// Sets the color of a specific pixel (combines R, G, B into the GRB format)
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);

// Fills the entire strip with a single color
void led_fill(uint8_t r, uint8_t g, uint8_t b);

// Turns off all pixels
void led_clear();

// Gets the read-only buffer pointer (for sending data or testing)
const uint32_t* led_get_buffer();

// Gets the number of pixels currently managed
size_t led_get_pixel_count();

#endif // LED_DRIVER_H