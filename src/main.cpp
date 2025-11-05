#include <Arduino.h>
#include <WiFi.h>

#include "Website.h"
#include "secrets.h"

// Create status LED instance
constexpr uint8_t LED_PIN = 8;

StatusLED statusLED(LED_PIN);
RFIDReader rfidReader(1, 0);
Timestamp timestamp;
CatflapManager catflapManager(statusLED, rfidReader, timestamp);
Website website("catflap", catflapManager);

void setup() {
    // Initialize StatusLED after Serial
    statusLED.begin();
    statusLED.setBrightness(1);
    statusLED.setColor(Color::RED);

    // Initialize Serial first with higher baud rate
    Serial.begin(115200);
    delay(1000);

    connectToWiFi(WIFI_SSID, WIFI_PASSWORD, &statusLED);
    website.begin();
    timestamp.configureNTP();
    rfidReader.begin();
}

void loop() {
    website.handleClient();
    catflapManager.scan();

    if (WiFi.status() != WL_CONNECTED) {
        connectToWiFi(WIFI_SSID, WIFI_PASSWORD, &statusLED);
    }
}
