#pragma once

#include <vector>

#include "StatusLED.h"
#include "Timestamp.h"

class CatflapManager {
   private:
    Timestamp& timestamp;
    StatusLED& statusLED;
    std::vector<int> dummyData;  // Placeholder for actual data members
   public:
    CatflapManager(StatusLED& led, Timestamp& ts);

    std::vector<int> getData();
    void scan();
};
