#include "RFIDReader.h"

// Constructor
RFIDReader::RFIDReader(int uart_num, int rx_pin)
    : rfidSerial(uart_num), buffer_index(0) {
    rfidSerial.setPins(rx_pin, -1);  // Set RX pin, TX not used
}

// Initialize the RFID reader
void RFIDReader::begin(int baud_rate) { rfidSerial.begin(baud_rate); }

// Validate checksum of received frame
bool RFIDReader::validateChecksum() {
    uint8_t checksum = 0;
    uint8_t msg_checksum = buffer[11];

    // XOR checksum validation on bytes 1–10
    for (int i = 1; i < 11; i++) {
        checksum ^= buffer[i];
    }

    return (checksum == msg_checksum);
}

// Extract tag data from buffer
bool RFIDReader::extractTag() {
    if (!validateChecksum()) {
        return false;
    }

    // Extract country code (bytes 4-5)
    detectedTag.country = (static_cast<uint16_t>(buffer[4]) << 8) | buffer[5];

    // Extract tag ID (bytes 6-10)
    detectedTag.tagId = (static_cast<uint64_t>(buffer[6]) << 32) |
                        (static_cast<uint64_t>(buffer[7]) << 24) |
                        (static_cast<uint64_t>(buffer[8]) << 16) |
                        (static_cast<uint64_t>(buffer[9]) << 8) | buffer[10];

    return true;
}

// Read and process RFID tag data
RFIDTag* RFIDReader::readTag() {
    if (!rfidSerial.available()) {
        return nullptr;
    }

    int byteRead = rfidSerial.read();
    if (byteRead == -1) return nullptr;

    // Start frame (0xAA)
    if (byteRead == 0xAA && buffer_index == 0) {
        buffer[buffer_index++] = byteRead;
        return nullptr;
    }

    // Continue filling buffer
    if (buffer_index > 0 && buffer_index < BUFFER_SIZE) {
        buffer[buffer_index++] = byteRead;
    }

    // End frame (0xBB) - complete frame received
    if (byteRead == 0xBB && buffer_index == BUFFER_SIZE && extractTag()) {
        buffer_index = 0;
        return &detectedTag;
    }

    // Reset if out of sync
    if (buffer_index >= BUFFER_SIZE) {
        buffer_index = 0;
    }

    return nullptr;
}
