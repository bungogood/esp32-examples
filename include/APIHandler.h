#pragma once

#include <ArduinoJson.h>
#include <WebServer.h>

#include <functional>

class APIHandler {
   private:
    WebServer* server;
    JsonDocument response;
    char jsonString[1024];

    void clearResponse();
    void logRequest();
    void logResponse(int statusCode, unsigned long duration);
    void sendResponse(int statusCode, const JsonDocument& json);

   public:
    APIHandler(WebServer* server);
    void setupRoutes();

    void apiRoute(const Uri& uri, HTTPMethod method,
                  std::function<int(void)> handler);
    void apiHandler(std::function<int(void)> handler);

    int healthCheck();
    int routeNotFound();
};

String methodToString(HTTPMethod method);
