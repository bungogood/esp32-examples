#include "CatflapManager.h"

CatflapManager::CatflapManager(StatusLED& led, RFIDReader& rfid, Timestamp& ts)
    : statusLED(led), rfidReader(rfid), timestamp(ts) {
    addCatInfo({100000023268, "Meg"});
    addCatInfo({100000024525, "Coco"});
    addCatInfo({10789766, "Test"});
}

void CatflapManager::begin() { Serial.println("CatflapManager initialized"); }

void CatflapManager::addCatInfo(CatInfo info) { catlogMap[info.tagId] = info; }

void CatflapManager::scan() {
    // Scan for RFID tags
    RFIDTag* tag = rfidReader.readTag();
    if (tag) {
        // Process the detected tag
        statusLED.setColor(Color::MAGENTA);
        Serial.printf("RFID Tag Detected - Tag ID: %010llX\n", tag->tagId);
        CatEvent event = {tag->tagId, timestamp.now()};
        catlog.push_back(event);

        // Update timestamp
        delay(200);  // Simulate processing delay
        statusLED.setColor(Color::GREEN);
    }
}
