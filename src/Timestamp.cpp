#include "Timestamp.h"

// Constructor
Timestamp::Timestamp() {
    ntpServer = "pool.ntp.org";
    gmtOffset_sec = 0;
    daylightOffset_sec = 0;
    timeConfigured = false;
    update();
}

// Constructor with custom NTP settings
Timestamp::Timestamp(const char* server, long gmtOffset, int daylightOffset) {
    ntpServer = server;
    gmtOffset_sec = gmtOffset;
    daylightOffset_sec = daylightOffset;
    timeConfigured = false;
    update();
}

// Configure NTP server and initialize time synchronization
bool Timestamp::configureNTP(const char* server, long gmtOffset,
                             int daylightOffset) {
    ntpServer = server;
    gmtOffset_sec = gmtOffset;
    daylightOffset_sec = daylightOffset;

    Serial.println("Configuring time with NTP server...");

    // Initialize and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Wait for time to be set
    struct tm timeinfo;
    int attempts = 0;
    while (!getLocalTime(&timeinfo) && attempts < 10) {
        Serial.print(".");
        delay(1000);
        attempts++;
    }

    if (attempts >= 10) {
        Serial.println("Failed to obtain time from NTP server");
        timeConfigured = false;
        return false;
    }

    Serial.println("\nTime synchronized with NTP server!");
    timeConfigured = true;
    return true;
}

// Update the timestamp to current time
void Timestamp::update() {
    time(&currentTime);
    localtime_r(&currentTime, &timeInfo);
}

// Get Unix timestamp (seconds since epoch)
time_t Timestamp::now() {
    update();
    return currentTime;
}

struct tm* Timestamp::nowInfo() {
    update();
    return &timeInfo;
}

// Check if time is valid
bool Timestamp::isValid() {
    return currentTime > 0 && timeInfo.tm_year > 100;  // Year > 2000
}

// Check if NTP has been configured
bool Timestamp::isConfigured() { return timeConfigured; }

// Utility function to format time
String formatTime(time_t unixTime) {
    struct tm* timeinfo;
    timeinfo = localtime(&unixTime);
    char buffer[25];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return String(buffer);
}
