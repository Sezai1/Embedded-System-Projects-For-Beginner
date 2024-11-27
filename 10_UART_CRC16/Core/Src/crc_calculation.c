#include "crc_calculation.h"
#include <stdio.h>

uint16_t crc_calculation(const unsigned char* data, size_t length) {
    uint16_t CRC_poly = 0xA001;
    uint16_t CRC = 0xFFFF;

    for (size_t i = 0; i < length; i++) {
        CRC ^= data[i];  // CRC'yi mevcut byte ile XOR'la

        for (int bit = 0; bit < 8; bit++) {  // Her bit için işlem yap
            if (CRC & 0x0001) {  // En düşük bit '1' ise
                CRC = (CRC >> 1) ^ CRC_poly;
            } else {
                CRC >>= 1;
            }
        }
    }
    return CRC & 0xFFFF;  // 16-bit sınırında tutmak için maskeleme
}
