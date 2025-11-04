#pragma once

#include <Adafruit_NeoPixel.h>

// Color enumeration
enum class Color {
    OFF,
    RED,
    GREEN,
    BLUE,
    WHITE,
    YELLOW,
    MAGENTA,
    CYAN,
    ORANGE,
    PURPLE,
    PINK,
    LIME,
    INDIGO,
    TEAL
};

class StatusLED {
   private:
    Adafruit_NeoPixel rgbLed;
    uint8_t currentBrightness;

   public:
    // Constructor
    StatusLED(uint8_t pin, uint8_t numLeds = 1);

    // Initialize the statusLED
    void begin();

    // Set color using RGB values (0-255)
    void setColor(uint8_t red, uint8_t green, uint8_t blue,
                  uint8_t brightness = 100);

    // Set color using enum
    void setColor(Color color, uint8_t brightness = 100);
};
