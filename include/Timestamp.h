#pragma once

#include <Arduino.h>
#include <time.h>

// Forward declaration of utility function
String formatTime(time_t unixTime);

class Timestamp {
   private:
    time_t currentTime;
    struct tm timeInfo;

    // NTP configuration
    const char* ntpServer;
    long gmtOffset_sec;
    int daylightOffset_sec;
    bool timeConfigured;

   public:
    // Constructor
    Timestamp();

    // Constructor with custom NTP settings
    Timestamp(const char* server, long gmtOffset = 0, int daylightOffset = 0);

    // Configure NTP server and initialize time synchronization
    bool configureNTP(const char* server = "pool.ntp.org", long gmtOffset = 0,
                      int daylightOffset = 0);

    // Update the timestamp to current time
    void update();

    // Get Unix timestamp (seconds since epoch)
    time_t now();

    // Get time info
    struct tm* nowInfo();

    // Get formatted time string
    String nowFormatTime() { return formatTime(now()); }

    // Check if time is valid
    bool isValid();

    // Check if NTP has been configured
    bool isConfigured();
};
