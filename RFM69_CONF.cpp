/*
 *  Dynamically create a configuration array
 *
 *
 *
 *
 */

#include "RFM69_CONF.h"

// Use default config as specified in base RFM69 class
RFM69Config::RFM69Config() {}

const uint8_t RFM69Config::getConfigVal(uint8_t rfm_register, uint8_t value)
{
    return RegisterConfig[rfm_register][value];
}

//     syncBytes: Byte array to hold the bytes of the sync word
// syncByteCount: Number of bytes in the sync word
//      syncWord: The sync word. ex: 0xAABBCC00112233

// RFM69 supports sync word sizes of 1 to 8 bytes
void RFM69Config::splitSyncWord(uint8_t* syncBytes, uint8_t syncByteCount, uint64_t syncWord)
{
    for (int i = 0; i < syncByteCount; i++)
        syncBytes[i] = (syncWord >> ((syncByteCount - i - 1) * 8)) & 0xFF;
        // Index 0 contains most significant byte
}

