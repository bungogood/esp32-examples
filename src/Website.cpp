#include "Website.h"

#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <LittleFS.h>
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
    while (WiFi.status() != WL_CONNECTED && attempts < 50) {
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

Website::Website(const char* hostname, CatflapManager& catflapManager,
                 uint16_t port)
    : hostname(hostname), server(port), api(server, catflapManager) {}

void Website::begin() {
    if (!LittleFS.begin()) {
        Serial.println("LittleFS mount failed");
        return;
    }
    Serial.println("LittleFS mounted successfully");
    if (!MDNS.begin(hostname)) {
        Serial.println("Error setting up MDNS responder!");
        return;
    }
    Serial.print("MDNS started: ");
    Serial.print(hostname);
    Serial.println(".local");
    setupRoutes();
    server.begin();
    Serial.println("Web server started");
}

void Website::setupRoutes() {
    api.setupRoutes();
    server.onNotFound([this]() {
        if (server.uri().startsWith("/api/")) {
            api.routeNotFound();
        } else {
            handleStaticFile(server.uri());
        }
    });
}

void Website::handleStaticFile(String path) {
    if (path.endsWith("/")) path += "index.html";

    String contentType = "text/plain";
    if (path.endsWith(".html"))
        contentType = "text/html";
    else if (path.endsWith(".css"))
        contentType = "text/css";
    else if (path.endsWith(".js"))
        contentType = "application/javascript";
    else if (path.endsWith(".png"))
        contentType = "image/png";
    else if (path.endsWith(".jpg"))
        contentType = "image/jpeg";
    else if (path.endsWith(".gif"))
        contentType = "image/gif";
    else if (path.endsWith(".ico"))
        contentType = "image/x-icon";

    if (!LittleFS.exists(path)) {
        Serial.printf("[Website] File not found: %s\n", path.c_str());
        server.send(404, "text/plain", "File not found");
        return;
    }

    File file = LittleFS.open(path, "r");
    if (!file) {
        Serial.printf("[Website] Error opening file: %s\n", path.c_str());
        server.send(500, "text/plain", "Error opening file");
        return;
    }

    server.streamFile(file, contentType);
    file.close();
}
