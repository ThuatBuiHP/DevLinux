#include "spws_controller.h"
#include "hal_sensors.h"
#include "hal_actuators.h"
#include "hal_buttons.h"
#include <stdio.h>

/* Global System Objects */
static SystemSettings_t settings;
static SystemState_t currentState;
static SensorData_t sensorData;

/* Internal helper functions */
static void RunAutoMode(void);
static void RunManualMode(void);
static void ReadSensors(void);
static void HandleButtons(void);

void SPWS_Init(void) {
    /* 1. Setup Default Settings */
    settings.minMoistureThreshold = 30.0f;
    settings.maxMoistureThreshold = 80.0f;
    settings.maxWateringDuration_s = 10;       // Max 10s pump in Auto
    settings.manualWateringDuration_s = 5;     // Max 5s pump in Manual
    settings.sensorReadInterval_s = 2;         // Read every 2 loops (simplified for sim)

    /* 2. Setup Initial State */
    currentState.currentMode = MODE_AUTO;
    currentState.pumpState = PUMP_OFF;
    currentState.ledState = LED_NORMAL;
    currentState.wateringTimeCounter = 0;
    currentState.sensorReadingCycleCounter = 0;

    /* 3. Initialize Hardware */
    HAL_Sensors_Init();
    HAL_Actuators_Init();
    HAL_Buttons_Init();

    printf("[SPWS] System Initialized in AUTO Mode.\n");
}

void SPWS_Run(void) {
    /* 1. Handle User Input (Buttons) */
    HandleButtons();

    /* 2. Read Sensors (Periodically) */
    currentState.sensorReadingCycleCounter++;
    if (currentState.sensorReadingCycleCounter >= settings.sensorReadInterval_s) {
        ReadSensors();
        currentState.sensorReadingCycleCounter = 0;
    }

    /* 3. Run Logic based on Mode */
    switch (currentState.currentMode) {
        case MODE_AUTO:
            RunAutoMode();
            break;
        case MODE_MANUAL:
            RunManualMode();
            break;
    }

    /* 4. Update LED Output */
    HAL_SetSystemLed(currentState.ledState);
}

static void HandleButtons(void) {
    // Button 1: Toggle Mode
    if (HAL_ReadButton(BUTTON_MODE_TOGGLE) == BUTTON_PRESSED) {
        if (currentState.currentMode == MODE_AUTO) {
            currentState.currentMode = MODE_MANUAL;
            // Requirement: Turn off pump immediately when switching
            HAL_TurnOffWaterPump();
            currentState.pumpState = PUMP_OFF;
            printf("[SPWS] Switched to MANUAL Mode.\n");
        } else {
            currentState.currentMode = MODE_AUTO;
            printf("[SPWS] Switched to AUTO Mode.\n");
        }
    }

    // Button 2: Manual Water (Only works in Manual Mode)
    if (currentState.currentMode == MODE_MANUAL) {
        if (HAL_ReadButton(BUTTON_MANUAL_WATER) == BUTTON_PRESSED) {
            // Start manual watering cycle
            if (currentState.pumpState == PUMP_OFF) {
                currentState.pumpState = PUMP_ON;
                currentState.wateringTimeCounter = 0; // Reset counter
                HAL_TurnOnWaterPump();
                currentState.ledState = LED_WATERING;
            }
        }
    }
}

static void ReadSensors(void) {
    sensorData.soilMoisturePercent = HAL_ReadSoilMoisture();
    sensorData.airTemperatureCelsius = HAL_ReadTemperature();
    
    // Optional: Print data for debugging
    // printf("[Sensors] Moisture: %.1f%% | Temp: %.1f C\n", 
    //        sensorData.soilMoisturePercent, sensorData.airTemperatureCelsius);
}

static void RunAutoMode(void) {
    // State 1: Pump is OFF, check if we need to water
    if (currentState.pumpState == PUMP_OFF) {
        currentState.ledState = LED_NORMAL;
        
        if (sensorData.soilMoisturePercent < settings.minMoistureThreshold) {
            // Start Watering
            printf("[Auto] Moisture Low (%.1f%%). Pump ON.\n", sensorData.soilMoisturePercent);
            HAL_TurnOnWaterPump();
            currentState.pumpState = PUMP_ON;
            currentState.ledState = LED_WATERING;
            currentState.wateringTimeCounter = 0;
        }
    } 
    // State 2: Pump is ON, check if we need to stop
    else if (currentState.pumpState == PUMP_ON) {
        currentState.wateringTimeCounter++;

        // Check Stop Conditions
        int stop = 0;
        if (sensorData.soilMoisturePercent > settings.maxMoistureThreshold) {
            printf("[Auto] Max Moisture Reached. Stopping.\n");
            stop = 1;
        }
        else if (currentState.wateringTimeCounter >= settings.maxWateringDuration_s) {
            printf("[Auto] Max Duration Reached. Stopping.\n");
            stop = 1;
        }

        if (stop) {
            HAL_TurnOffWaterPump();
            currentState.pumpState = PUMP_OFF;
            currentState.ledState = LED_NORMAL;
        }
    }
}

static void RunManualMode(void) {
    // Logic for timing out the manual button press
    if (currentState.pumpState == PUMP_ON) {
        currentState.wateringTimeCounter++;
        
        if (currentState.wateringTimeCounter >= settings.manualWateringDuration_s) {
            printf("[Manual] Manual duration ended. Pump OFF.\n");
            HAL_TurnOffWaterPump();
            currentState.pumpState = PUMP_OFF;
            currentState.ledState = LED_NORMAL;
        }
    }
}