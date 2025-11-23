#ifndef HAL_SENSORS_H
#define HAL_SENSORS_H

/**
 * @brief   Initialize the sensor hardware (ADC, GPIO, etc).
 * @return  void
 */
void HAL_Sensors_Init(void);

/**
 * @brief   Read soil moisture.
 * @return  float   Value of soil moisture (percentage 0.0 - 100.0).
 */
float HAL_ReadSoilMoisture(void);

/**
 * @brief   Read temperature.
 * @return  float   Value of temperature (degrees Celsius).
 */
float HAL_ReadTemperature(void);

#endif