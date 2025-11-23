#include "hal_buttons.h"
#include <stdio.h>

/* * HARDWARE MAPPING NOTE:
 * In a real scenario, you might map IDs to Pins like this:
 * static const int BUTTON_PINS[] = { GPIO_PIN_1, GPIO_PIN_2 };
 */

void HAL_Buttons_Init(void) {
    /* TODO: Configure GPIO pins as Inputs.
       Example: 
       HAL_GPIO_Init(GPIOA, BUTTON_MODE_PIN, GPIO_MODE_INPUT_PULLUP);
       HAL_GPIO_Init(GPIOA, BUTTON_WATER_PIN, GPIO_MODE_INPUT_PULLUP);
    */
    printf("[HAL] Buttons Initialized (GPIO Input Configured).\n");
}

ButtonState_t HAL_ReadButton(ButtonID_t buttonId) {
    /* Default state */
    ButtonState_t state = BUTTON_RELEASED;

    /* Hardware Check Logic */
    switch (buttonId) {
        case BUTTON_MODE_TOGGLE:
            /* TODO: Replace with actual hardware read.
               Example (Active Low logic):
               if (HAL_GPIO_ReadPin(GPIOA, PIN_1) == RESET) { state = BUTTON_PRESSED; }
            */
            
            // SIMULATION: To test, you can temporarily force this to PRESSED 
            // or connect it to a keyboard input if running on PC.
            state = BUTTON_RELEASED; 
            break;

        case BUTTON_MANUAL_WATER:
            /* TODO: Replace with actual hardware read. */
            state = BUTTON_RELEASED;
            break;

        default:
            // Unknown button
            break;
    }

    /* Debug print - strictly for testing, remove in production as it floods console */
    // if (state == BUTTON_PRESSED) {
    //    printf("[HAL] Button %d Pressed\n", buttonId);
    // }

    return state;
}