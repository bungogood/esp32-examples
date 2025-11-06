#pragma once

#include <map>
#include <vector>

#include "RFIDReader.h"
#include "StatusLED.h"
#include "Timestamp.h"

struct CatEvent {
    uint64_t tagId;
    time_t timestamp;
};

struct CatInfo {
    uint64_t tagId;
    String name;
};

class CatflapManager {
   private:
    RFIDReader& rfidReader;
    Timestamp& timestamp;
    StatusLED& statusLED;

   public:
    std::map<uint64_t, CatInfo> catlogMap;
    std::vector<CatEvent> catlog;

    CatflapManager(StatusLED& led, RFIDReader& rfid, Timestamp& ts);

    void begin();

    void addCatInfo(CatInfo info);
    void scan();
};
