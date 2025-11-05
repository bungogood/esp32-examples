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
    uint8_t defaultBrightness;

   public:
    // Constructor
    StatusLED(uint8_t pin, uint8_t numLeds = 1,
              uint8_t defaultBrightness = 100);

    // Initialize the statusLED
    void begin();

    // Set default brightness
    void setBrightness(uint8_t brightness);

    // Set color using RGB values (0-255) with specified brightness
    void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);

    // Set color using RGB values (0-255) with default brightness
    void setColor(uint8_t red, uint8_t green, uint8_t blue);

    // Set color using enum with specified brightness
    void setColor(Color color, uint8_t brightness);

    // Set color using enum with default brightness
    void setColor(Color color);
};
