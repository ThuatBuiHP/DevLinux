#ifndef SPWS_CONTROLLER_H
#define SPWS_CONTROLLER_H

#include "../config.h"

/**
 * @brief   Initialize the logic controller.
 * Sets default settings and states.
 */
void SPWS_Init(void);

/**
 * @brief   The main processing task.
 * Call this inside the main while(1) loop.
 * It handles sensors, buttons, and state transitions.
 */
void SPWS_Run(void);

#endif