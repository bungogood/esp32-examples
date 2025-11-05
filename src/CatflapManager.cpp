#include "CatflapManager.h"

CatflapManager::CatflapManager(StatusLED& led, Timestamp& ts)
    : statusLED(led), timestamp(ts) {
    // Initialize dummy data
    dummyData = {1, 2, 3, 4, 5};
}

std::vector<int> CatflapManager::getData() { return dummyData; }

void CatflapManager::scan() {}
