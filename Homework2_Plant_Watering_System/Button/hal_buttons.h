#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdint.h>

/* Button Identifiers - abstract names for your physical buttons */
typedef enum {
    BUTTON_MODE_TOGGLE,    /* Button used to switch Auto/Manual */
    BUTTON_MANUAL_WATER,   /* Button used to trigger pump in Manual mode */
    /* Add more buttons here if needed */
    BUTTON_COUNT           /* Helper to know how many buttons exist */
} ButtonID_t;

/* Button States - normalizes hardware (Active Low vs Active High) */
typedef enum {
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED  = 1
} ButtonState_t;

/**
 * @brief   Initialize the button GPIO pins.
 * @return  void
 */
void HAL_Buttons_Init(void);

/**
 * @brief   Read the current state of a specific button.
 * @param   buttonId  The ID of the button to read (e.g., BUTTON_MODE_TOGGLE).
 * @return  ButtonState_t  Returns BUTTON_PRESSED or BUTTON_RELEASED.
 */
ButtonState_t HAL_ReadButton(ButtonID_t buttonId);

#endif // HAL_BUTTONS_H