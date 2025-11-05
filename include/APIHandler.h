#pragma once

#include <ArduinoJson.h>
#include <WebServer.h>

#include <functional>

#include "CatflapManager.h"

class APIHandler {
   private:
    WebServer& server;
    JsonDocument response;
    char jsonString[1024];

    CatflapManager& catflapManager;

    void clearResponse();
    void logRequest();
    void logResponse(int statusCode, unsigned long duration);
    void sendResponse(int statusCode, const JsonDocument& json);

    void apiHandler(std::function<int(JsonDocument&, CatflapManager&)> handler);

   public:
    APIHandler(WebServer& server, CatflapManager& catflapManager);
    void setupRoutes();
    void routeNotFound();

    void apiRoute(const Uri& uri, HTTPMethod method,
                  std::function<int(JsonDocument&, CatflapManager&)> handler);
};

String methodToString(HTTPMethod method);
