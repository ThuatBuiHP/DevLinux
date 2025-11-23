#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

/* System mode */
typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode_t;

/* Pump state */
typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState_t;

/* Led state */
typedef enum {
    LED_NORMAL,                 /* Green: Normal, waiting */
    LED_WATERING,               /* Yellow: Watering */
    LED_LOW_MOISTURE_ALERT,     /* Red on off: Low moisture, alert */
    LED_ERROR                   /* Red continuous: Error */
} LedState_t;

/* Sensor data */
typedef struct {
    float soilMoisturePercent;
    float airTemperatureCelsius;
} SensorData_t;

/* System settings */
typedef struct {
    float minMoistureThreshold;    /* Min moisture threshold to start watering */
    float maxMoistureThreshold;    /* Max moisture threshold to stop watering */
    uint32_t maxWateringDuration_s;  /* Max watering duration (seconds) */
    uint32_t sensorReadInterval_s;   /* Sensor read cycle (seconds) */
    uint32_t manualWateringDuration_s;  /* Manual watering duration (seconds) */
} SystemSettings_t;

/* System state */
typedef struct {
    SystemMode_t currentMode;
    PumpState_t pumpState;
    LedState_t ledState;
    uint32_t wateringTimeCounter; /* Counting watering time */
    uint32_t sensorReadingCycleCounter;  /* Counting sensor-reading cycle */
} SystemState_t;

#endif