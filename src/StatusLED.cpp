#include "StatusLED.h"

// Constructor
StatusLED::StatusLED(uint8_t pin, uint8_t numLeds, uint8_t defaultBrightness)
    : rgbLed(numLeds, pin, NEO_GRB + NEO_KHZ800),
      currentBrightness(defaultBrightness),
      defaultBrightness(defaultBrightness) {}

// Initialize the statusLED
void StatusLED::begin() {
    rgbLed.begin();
    rgbLed.show();
}

// Set default brightness
void StatusLED::setBrightness(uint8_t brightness) {
    defaultBrightness = brightness;
}

// Set color using RGB values (0-255)
void StatusLED::setColor(uint8_t red, uint8_t green, uint8_t blue,
                         uint8_t brightness) {
    currentBrightness = brightness;
    uint16_t scale = (uint16_t)brightness * 255 / 100;
    uint8_t r = (uint8_t)(((uint16_t)red * scale) / 255);
    uint8_t g = (uint8_t)(((uint16_t)green * scale) / 255);
    uint8_t b = (uint8_t)(((uint16_t)blue * scale) / 255);
    rgbLed.setPixelColor(0, rgbLed.Color(g, r, b));
    rgbLed.show();
}

// Set color using RGB values (0-255) with default brightness
void StatusLED::setColor(uint8_t red, uint8_t green, uint8_t blue) {
    setColor(red, green, blue, defaultBrightness);
}

// Set color using enum
void StatusLED::setColor(Color color, uint8_t brightness) {
    switch (color) {
        case Color::OFF:
            setColor(0, 0, 0, 0);
            break;
        case Color::RED:
            setColor(255, 0, 0, brightness);
            break;
        case Color::GREEN:
            setColor(0, 255, 0, brightness);
            break;
        case Color::BLUE:
            setColor(0, 0, 255, brightness);
            break;
        case Color::WHITE:
            setColor(255, 255, 255, brightness);
            break;
        case Color::YELLOW:
            setColor(255, 255, 0, brightness);
            break;
        case Color::MAGENTA:
            setColor(255, 0, 255, brightness);
            break;
        case Color::CYAN:
            setColor(0, 255, 255, brightness);
            break;
        case Color::ORANGE:
            setColor(255, 165, 0, brightness);
            break;
        case Color::PURPLE:
            setColor(128, 0, 128, brightness);
            break;
        case Color::PINK:
            setColor(255, 192, 203, brightness);
            break;
        case Color::LIME:
            setColor(50, 205, 50, brightness);
            break;
        case Color::INDIGO:
            setColor(75, 0, 130, brightness);
            break;
        case Color::TEAL:
            setColor(0, 128, 128, brightness);
            break;
    }
}

// Set color using enum with default brightness
void StatusLED::setColor(Color color) { setColor(color, defaultBrightness); }
