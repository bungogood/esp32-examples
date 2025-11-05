#include <Arduino.h>
#include <WiFi.h>

#include "StatusLED.h"
#include "Website.h"
#include "secrets.h"

// Create status LED instance
constexpr uint8_t LED_PIN = 8;

StatusLED statusLED(LED_PIN);
Timestamp timestamp;
CatflapManager catflapManager(statusLED, timestamp);
Website website("catflap", catflapManager);

void setup() {
    // Initialize Serial first with higher baud rate
    Serial.begin(115200);
    delay(1000);

    // Initialize StatusLED after Serial
    statusLED.begin();

    // Connect to WiFi
    connectToWiFi(WIFI_SSID, WIFI_PASSWORD, &statusLED);

    // Initialize Website
    website.begin();

    // Configure NTP
    timestamp.configureNTP();
}

void loop() {
    website.handleClient();
    catflapManager.scan();
}
