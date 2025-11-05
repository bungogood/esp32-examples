#pragma once

#include <WebServer.h>

#include "APIHandler.h"
#include "StatusLED.h"

bool connectToWiFi(const char* ssid, const char* password,
                   StatusLED* statusLED = nullptr);

class Website {
   private:
    const char* hostname;
    WebServer server;
    APIHandler api;

    void setupRoutes();
    void handleStaticFile(String path);

   public:
    Website(const char* hostname, uint16_t port = 80);

    // Add website-related methods here in the future
    void begin();

    void handleClient() { server.handleClient(); }
};
