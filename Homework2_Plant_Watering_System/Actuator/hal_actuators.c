#include "hal_actuators.h"
#include <stdio.h>

/* Internal state to track simulation status */
static int isPumpOn = 0;

void HAL_Actuators_Init(void) {
    /* TODO: Hardware specific initialization 
       Example: HAL_GPIO_Init(GPIOA, GPIO_PIN_5, &GPIO_InitStruct);
    */
    printf("[HAL] Actuators Initialized (GPIO Configured).\n");
}

void HAL_TurnOnWaterPump(void) {
    if (!isPumpOn) {
        /* TODO: Replace with actual hardware write.
           Example: HAL_GPIO_WritePin(GPIOA, PUMP_PIN, GPIO_PIN_SET); 
        */
        printf("[HAL] ACTION: Pump turned ON (Watering...)\n");
        isPumpOn = 1;
    }
}

void HAL_TurnOffWaterPump(void) {
    if (isPumpOn) {
        /* TODO: Replace with actual hardware write.
           Example: HAL_GPIO_WritePin(GPIOA, PUMP_PIN, GPIO_PIN_RESET); 
        */
        printf("[HAL] ACTION: Pump turned OFF.\n");
        isPumpOn = 0;
    }
}

void HAL_SetSystemLed(LedState_t state) {
    /* TODO: Write to RGB GPIO pins based on state */
    switch (state) {
        case LED_NORMAL:
            printf("[HAL] LED: Green (System OK)\n"); 
            break;
        case LED_WATERING:
            printf("[HAL] LED: Yellow (Watering)\n");
            break;
        case LED_LOW_MOISTURE_ALERT:
            printf("[HAL] LED: Red Blinking (Low Moisture!)\n");
            break;
        case LED_ERROR:
            printf("[HAL] LED: Red Continuous (Error)\n");
            break;
    }
}
