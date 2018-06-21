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

// Get the config byte for specified RFM register
const uint8_t RFM69Config::getRegisterVal(uint8_t rfm_register, RegisterIndex idx)
{
    return registerConfig[rfm_register][idx];
}

void RFM69Config::writeBitrate(uint16_t targetBitrate)
{
    bitrate = targetBitrate;
    uint16_t br = RFM_FXOSC / bitrate;

    uint8_t bitrateBytes[2] = { 0, 0 };

    RFM69Config::splitWord(bitrateBytes, 2, bitrate);

    for (int i = 0; i < 2; i++)
    {
        RFM69Config::registerConfig[i + REG_BITRATEMSB][RegisterIndex::VALUE] = bitrateBytes[i];
        RFM69Config::registerConfig[i + REG_BITRATEMSB][RegisterIndex::WILL_WRITE] = 1;
    }
}

void RFM69Config::writeFrequencyDeviation(uint16_t targetFreqDev)
{
    frequencyDeviation = targetFreqDev;
    uint16_t br = frequencyDeviation / RFM_FSTEP;

    uint8_t fDevBytes[2] = { 0, 0 };

    RFM69Config::splitWord(fDevBytes, 2, frequencyDeviation);

    for (int i = 0; i < 2; i++)
    {
        RFM69Config::registerConfig[i + REG_FDEVMSB][RegisterIndex::VALUE] = fDevBytes[i];
        RFM69Config::registerConfig[i + REG_FDEVMSB][RegisterIndex::WILL_WRITE] = 1;
    }
}


// No checking for valid frequency ranges is done
// It's up to you to use the correct values
// The following is US only. If you are in another region, 
// it's up to you to find the correct values.
//
// Per FCC Regulations as of June 12, 2018
// https://transition.fcc.gov/oet/spectrum/table/fcctable.pdf
// 433 MHz band: 433,050,000 Hz - 434,790,000 Hz : Section 5.280
// 915 MHz band: 902,000,000 Hz - 928,000,000 Hz : Sections 5.150, US275

// YOU MUST SET THE FREQUENCY. YOU MUST CALL THIS FUNCTION.
// Example: For a target frequency of 912.9 MHz, enter 912900000 for targetFrequency
void RFM69Config::writeCarrierFrequency(uint32_t targetFrequency)
{
    centerFrequency = targetFrequency;

    uint32_t Frf = centerFrequency / RFM_FSTEP;

    uint8_t centerFrequencyBytes[3] = {};

    RFM69Config::splitWord(centerFrequencyBytes, 3, Frf);

    for (int i = 0; i < 3; i++)
    {
        RFM69Config::registerConfig[i + REG_FRFMSB][RegisterIndex::VALUE] = centerFrequencyBytes[i];
        RFM69Config::registerConfig[i + REG_FRFMSB][RegisterIndex::WILL_WRITE] = 1;
    }
}

void RFM69Config::writeSyncEnable(SyncEnable willSync)
{
    RFM69Config::registerConfig[REG_SYNCCONFIG][RegisterIndex::VALUE] =
        RFM69Config::registerConfig[REG_SYNCCONFIG][RegisterIndex::VALUE] & 0x7F | willSync;
}

void RFM69Config::writeSyncWord(uint8_t syncWordByteCount, uint64_t syncWord)
{
    uint8_t* syncWordBytes = new uint8_t[syncWordByteCount];

    RFM69Config::splitWord(syncWordBytes, syncWordByteCount, syncWord);

    for (uint8_t i = 0; i <= syncWordByteCount; i++)
    {
        RFM69Config::registerConfig[i + REG_SYNCVALUE1][RegisterIndex::VALUE] = syncWordBytes[i];
        RFM69Config::registerConfig[i + REG_SYNCVALUE1][RegisterIndex::WILL_WRITE] = 1;
    }

    delete syncWordBytes;

    RFM69Config::registerConfig[REG_SYNCCONFIG][RegisterIndex::VALUE] =
        RFM69Config::registerConfig[REG_SYNCCONFIG][RegisterIndex::VALUE] & 0xC7 | (syncWordByteCount - 1 << 3);
}

// Allow 0-7 bits of error tolerance in the sync word
void RFM69Config::writeSyncWordErrorTolerance(SyncWordErrorTolerance errorTol)
{
    RFM69Config::registerConfig[REG_SYNCCONFIG][RegisterIndex::VALUE] =
        RFM69Config::registerConfig[REG_SYNCCONFIG][RegisterIndex::VALUE] & 0xF8 | errorTol;
}

void RFM69Config::writeAESKey(uint64_t AES_MSB, uint64_t AES_LSB)
{
    uint8_t WD[16] = {};

    RFM69Config::splitWord(&WD[0], 8, AES_MSB);
    RFM69Config::splitWord(&WD[8], 8, AES_LSB);

    for (uint8_t i = 0; i < 16; i++)
    {
        RFM69Config::registerConfig[i + REG_AESKEY1][RegisterIndex::VALUE] = WD[i];
        RFM69Config::registerConfig[i + REG_AESKEY1][RegisterIndex::WILL_WRITE] = 1;
    }
}

//     syncBytes: Byte array to hold the bytes of the sync word
// syncByteCount: Number of bytes in the sync word
//      syncWord: The sync word. ex: 0xAABBCC00112233

// RFM69 supports sync word sizes of 1 to 8 bytes
void RFM69Config::splitWord(uint8_t* wordBytes, uint8_t wordByteCount, uint64_t word)
{
    for (int i = 0; i < wordByteCount; i++)
        wordBytes[i] = (word >> ((wordByteCount - i - 1) * 8)) & 0xFF; // Truncate
}

