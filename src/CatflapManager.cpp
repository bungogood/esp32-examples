#include "CatflapManager.h"

CatflapManager::CatflapManager(StatusLED& led, RFIDReader& rfid, Timestamp& ts)
    : statusLED(led), rfidReader(rfid), timestamp(ts) {
    // Initialize dummy data
    dummyData = {1, 2, 3, 4, 5};
}

std::vector<int> CatflapManager::getData() { return dummyData; }

void CatflapManager::scan() {
    // Scan for RFID tags
    RFIDTag* tag = rfidReader.readTag();
    if (tag) {
        // Process the detected tag
        statusLED.setColor(Color::BLUE, 100);
        Serial.printf("RFID Tag Detected - Country: %u, Tag ID: %010llX\n",
                      tag->country, tag->tagId);
        // Update timestamp
        delay(100);  // Simulate processing delay
        statusLED.setColor(Color::GREEN, 100);
        timestamp.update();
    }
}
