#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>

// ESP32 134.2kHz FDX-B Animal Tag Reader
// Class-based RFID reader with struct return type

struct RFIDTag {
    uint16_t country;
    uint64_t tagId;
};

class RFIDReader {
   private:
    static const int BUFFER_SIZE = 13;
    HardwareSerial rfidSerial;
    RFIDTag detectedTag;
    uint8_t buffer[BUFFER_SIZE];
    int buffer_index;

    bool validateChecksum();
    bool extractTag();

   public:
    RFIDReader(int uart_num, int rx_pin);
    void begin(int baud_rate = 9600);
    RFIDTag* readTag();
};
