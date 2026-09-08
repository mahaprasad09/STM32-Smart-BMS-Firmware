#include <stdint.h>
#include <stdio.h> // Needed for sprintf

int main(void)
{
    // Step A: Sensor Variables
    uint16_t raw_adc_voltage = 2607;
    float battery_voltage = 0.0;
    float temperature_celsius = 32.5;

    // Step B: Safety Relay Switch (1 = ON, 0 = Emergency SHUTOFF)
    uint8_t relay_status = 1;

    // Step C: Cloud Telemetry Setup
    char api_key[] = "5RKU0YD4M1L3QA09";
    char cloud_message_buffer[128];

    /* Infinite Loop */
    for(;;)
    {
        // --- STEP A: SENSOR CALCULATIONS ---
        float pin_voltage = ((float)raw_adc_voltage / 4095.0) * 3.3;
        battery_voltage = pin_voltage * 2.0;

        // --- STEP B: SAFETY GUARD RULES ---
        if (battery_voltage > 4.2 || battery_voltage < 3.0 || temperature_celsius > 50.0) {
            relay_status = 0; // Cut off power!
        } else {
            relay_status = 1; // All good!
        }

        // --- STEP C: FORMAT CLOUD TELEMETRY MESSAGE ---
        sprintf(cloud_message_buffer,
                "GET /update?api_key=%s&field1=%.2f&field2=%.2f&field3=%d\r\n",
                api_key, battery_voltage, temperature_celsius, relay_status);

        // Delay loop
        for(volatile uint32_t i = 0; i < 500000; i++);
    }
}
