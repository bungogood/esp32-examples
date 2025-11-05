#pragma once

#include <vector>

#include "StatusLED.h"

class CatflapManager {
   private:
    StatusLED& statusLED;
    std::vector<int> dummyData;  // Placeholder for actual data members
   public:
    CatflapManager(StatusLED& led);

    std::vector<int> getData();
    void scan();
};
