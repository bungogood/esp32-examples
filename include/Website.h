#pragma once

#include "StatusLED.h"

bool connectToWiFi(const char* ssid, const char* password,
                   StatusLED* statusLED = nullptr);
