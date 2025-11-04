#include <Arduino.h>

#include "StatusLED.h"

// Create status LED instance
constexpr uint8_t LED_PIN = 8;
StatusLED statusLED(LED_PIN);

void setup() {
    statusLED.begin();
    Serial.begin(115200);
}

void loop() {
    // Example usage: Cycle through colors
    statusLED.setColor(Color::RED);
    delay(1000);
    statusLED.setColor(Color::OFF);
    delay(1000);
}
