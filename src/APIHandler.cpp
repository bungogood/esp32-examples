#include "APIHandler.h"

APIHandler::APIHandler(WebServer& server, CatflapManager& catflapManager)
    : server(server), catflapManager(catflapManager) {}

int healthCheck(JsonDocument& response, CatflapManager& catflapManager) {
    response["status"] = "ok";
    return 200;
}

int catlog(JsonDocument& response, CatflapManager& catflapManager) {
    JsonArray log = response["log"].to<JsonArray>();
    for (const auto& item : catflapManager.catlog) {
        JsonObject obj = log.createNestedObject();
        obj["tagId"] = item.tagId;
        obj["timestamp"] = item.timestamp;
    }
    JsonArray cats = response["cats"].to<JsonArray>();
    for (const auto& [tagId, info] : catflapManager.catlogMap) {
        JsonObject obj = cats.createNestedObject();
        obj["tagId"] = tagId;
        obj["name"] = info.name;
    }
    return 200;
}

int notFound(JsonDocument& response, CatflapManager& catflapManager) {
    response["error"] = "Endpoint not found";
    return 404;
}

void APIHandler::setupRoutes() {
    apiRoute("/api/health", HTTP_GET, &healthCheck);
    apiRoute("/api/catlog", HTTP_GET, &catlog);
}

// THIS IS CODE TO SETUP AND LOG API REQUESTS AND RESPONSES

void APIHandler::routeNotFound() { apiHandler(notFound); }

void APIHandler::apiRoute(
    const Uri& uri, HTTPMethod method,
    std::function<int(JsonDocument&, CatflapManager&)> handler) {
    server.on(uri, method, std::bind(&APIHandler::apiHandler, this, handler));
}

void APIHandler::apiHandler(
    std::function<int(JsonDocument&, CatflapManager&)> handler) {
    unsigned long startTime = millis();

    clearResponse();
    logRequest();

    int statusCode;

    try {
        statusCode = handler(response, catflapManager);
    } catch (...) {
        Serial.println("[API] Exception in handler");
        statusCode = 500;
    }

    sendResponse(statusCode, response);

    unsigned long duration = millis() - startTime;
    logResponse(statusCode, duration);
}

void APIHandler::sendResponse(int statusCode, const JsonDocument& body) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    serializeJson(body, jsonString);
    server.send(statusCode, "application/json", jsonString);
}

void APIHandler::logRequest() {
    String body = server.arg("plain");
    Serial.printf("[API] %s %s - Client: %s",
                  methodToString(server.method()).c_str(), server.uri().c_str(),
                  server.client().remoteIP().toString().c_str());

    if (body.length() > 0) {
        Serial.printf(" Body: %s", body.c_str());
    }
    Serial.println();
}

void APIHandler::logResponse(int statusCode, unsigned long duration) {
    Serial.printf("[API] %s -> %d (%lu ms) Body: %s\n", server.uri().c_str(),
                  statusCode, duration, jsonString);
}

void APIHandler::clearResponse() {
    response.clear();
    memset(jsonString, 0, sizeof(jsonString));
}

String methodToString(HTTPMethod method) {
    switch (method) {
        case HTTP_GET:
            return "GET";
        case HTTP_POST:
            return "POST";
        case HTTP_PUT:
            return "PUT";
        case HTTP_DELETE:
            return "DELETE";
        default:
            return "UNKNOWN";
    }
}
