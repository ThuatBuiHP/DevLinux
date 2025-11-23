#include "SPWS_Controller/spws_controller.h"
#include <stdio.h>

/* * NOTE on Simulation:
 * Since this runs on a PC, the while(1) loop runs extremely fast.
 * In a real MCU, you might have a delay or use a timer interrupt.
 * We will add a fake delay here to simulate 1 second per loop iteration.
 */

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(x) Sleep(x)
#else
#include <unistd.h>
#define SLEEP_MS(x) usleep(x * 1000)
#endif

int main(void) {
    printf("=== Smart Plant Watering System (SPWS) Start ===\n");

    /* 1. Initialize System */
    SPWS_Init();

    /* 2. Main Loop */
    while (1) {
        /* Run the System Logic */
        SPWS_Run();

        /* Simulation delay: 1 second per loop */
        SLEEP_MS(1000); 
    }

    return 0;
}