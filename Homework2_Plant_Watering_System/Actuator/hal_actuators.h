#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

#include "config.h"

/**
 * @brief   Initialize the actuator hardware (GPIO for Pump and LEDs).
 */
void HAL_Actuators_Init(void);

/**
 * @brief   Turn on water pump.
 * @details Sets the GPIO pin high to activate the relay/transistor.
 */
void HAL_TurnOnWaterPump(void);

/**
 * @brief   Turn off water pump.
 * @details Sets the GPIO pin low to deactivate the relay/transistor.
 */
void HAL_TurnOffWaterPump(void);

/**
 * @brief   Set the System LED color/state.
 * @param   state  The target state (NORMAL, WATERING, ERROR, etc.)
 * @details Based on the state, this will light up Green, Yellow, or Red.
 */
void HAL_SetSystemLed(LedState_t state);

#endif