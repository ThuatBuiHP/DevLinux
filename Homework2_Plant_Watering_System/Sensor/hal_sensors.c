#include "hal_sensors.h"
#include <stdio.h>
#include <stdlib.h> /* Used for rand() simulation */
#include <time.h>   /* Used to seed random numbers */

void HAL_Sensors_Init(void) {
    /* TODO: Hardware specific initialization 
       Example: HAL_ADC_Start(&hadc1); 
    */
    printf("[HAL] Sensors Initialized (ADC Configured).\n");
    
    /* Seeding random number generator for simulation purposes */
    srand(time(NULL));
}

float HAL_ReadSoilMoisture(void) {
    /* TODO: Replace with actual hardware read.
       Example: uint16_t raw = HAL_ADC_GetValue(&hadc1);
                return ConvertToPercentage(raw);
    */
    
    /* Simulation: Return a random float between 0.0 and 100.0 */
    float simulatedMoisture = (float)(rand() % 1000) / 10.0f;
    
    // printf("[HAL] Sensor Read: Soil Moisture = %.2f%%\n", simulatedMoisture);
    return simulatedMoisture;
}

float HAL_ReadTemperature(void) {
    /* TODO: Replace with actual hardware read.
    */

    /* Simulation: Return a random float between 20.0 and 35.0 */
    float simulatedTemp = 20.0f + ((float)(rand() % 150) / 10.0f);
    
    // printf("[HAL] Sensor Read: Temperature = %.2f C\n", simulatedTemp);
    return simulatedTemp;
}