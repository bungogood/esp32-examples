#include <Arduino.h>
#include <WiFi.h>

#include "StatusLED.h"
#include "Website.h"
#include "secrets.h"

// Create status LED instance
constexpr uint8_t LED_PIN = 8;
StatusLED statusLED(LED_PIN);
Website website("catflap");

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
}

void loop() {
    website.handleClient();
    // // Check WiFi connection status and show appropriate color
    // if (WiFi.status() == WL_CONNECTED) {
    //     // Connected - breathe green slowly
    //     statusLED.setColor(Color::GREEN, 50);
    //     delay(500);
    //     statusLED.setColor(Color::OFF);
    //     delay(500);

    // } else {
    //     // Disconnected - blink red
    //     Serial.println("WiFi disconnected! Attempting to reconnect...");
    //     statusLED.setColor(Color::RED, 50);
    //     delay(500);
    //     statusLED.setColor(Color::OFF);
    //     delay(500);

    //     // Try to reconnect (but not too frequently)
    //     static unsigned long lastReconnect = 0;
    //     if (millis() - lastReconnect > 10000) {
    //         connectToWiFi(WIFI_SSID, WIFI_PASSWORD, &statusLED);
    //         lastReconnect = millis();
    //     }
    // }
}
