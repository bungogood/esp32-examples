#pragma once

#include <vector>

#include "RFIDReader.h"
#include "StatusLED.h"
#include "Timestamp.h"

class CatflapManager {
   private:
    RFIDReader& rfidReader;
    Timestamp& timestamp;
    StatusLED& statusLED;
    std::vector<int> dummyData;  // Placeholder for actual data members
   public:
    CatflapManager(StatusLED& led, RFIDReader& rfid, Timestamp& ts);

    std::vector<int> getData();
    void scan();
};
