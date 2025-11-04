#include "Website.h"

#include <WiFi.h>

// WiFi connection function
bool connectToWiFi(const char* ssid, const char* password,
                   StatusLED* statusLED) {
    Serial.print("Connecting to WiFi network: ");
    Serial.println(ssid);

    if (statusLED) {
        statusLED->setColor(Color::YELLOW);
    }

    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(100);
        Serial.print(".");
        attempts++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi connected successfully!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());

        // Show success with green
        if (statusLED) {
            statusLED->setColor(Color::GREEN);
        }
        return true;
    } else {
        Serial.println("Failed to connect to WiFi!");

        // Show failure with red
        if (statusLED) {
            statusLED->setColor(Color::RED);
        }
        return false;
    }
}
