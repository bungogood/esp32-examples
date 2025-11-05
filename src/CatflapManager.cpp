#include "CatflapManager.h"

CatflapManager::CatflapManager(StatusLED& led) : statusLED(led) {
    // Initialize dummy data
    dummyData = {1, 2, 3, 4, 5};
}

std::vector<int> CatflapManager::getData() { return dummyData; }

void CatflapManager::scan() {}
