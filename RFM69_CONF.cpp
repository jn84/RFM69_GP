/*
 *  Dynamically create a configuration array
 *
 *
 *
 *
 */

#include "RFM69_CONF.h"

// Use default config as specified in base RFM69 class
RFM69Config::RFM69Config()
{
    RegisterConfig[REG_OPMODE][VALUE] = RF_OPMODE_SEQUENCER_ON | RF_OPMODE_LISTEN_OFF | RF_OPMODE_STANDBY;
    RegisterConfig[REG_OPMODE][WILL_WRITE] = 1;

    RegisterConfig[REG_DATAMODUL][VALUE] = RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_00;
    RegisterConfig[REG_DATAMODUL][WILL_WRITE] = 1;

    RegisterConfig[REG_BITRATEMSB][VALUE] = RF_BITRATEMSB_55555;
    RegisterConfig[REG_BITRATEMSB][WILL_WRITE] = 1;
    
    RegisterConfig[REG_BITRATELSB][VALUE] = RF_BITRATELSB_55555;
    RegisterConfig[REG_BITRATELSB][WILL_WRITE] = 1;

    RegisterConfig[REG_FDEVMSB][VALUE] = RF_FDEVMSB_50000;
    RegisterConfig[REG_FDEVMSB][WILL_WRITE] = 1;

    RegisterConfig[REG_FDEVLSB][VALUE] = RF_FDEVLSB_50000;
    RegisterConfig[REG_FDEVLSB][WILL_WRITE] = 1;

    RegisterConfig[REG_FRFMSB][VALUE] = RF_FRFMSB_915;
    RegisterConfig[REG_FRFMSB][WILL_WRITE] = 1;
    
    RegisterConfig[REG_FRFMID][VALUE] = RF_FRFMID_915;
    RegisterConfig[REG_FRFMID][WILL_WRITE] = 1;
    
    RegisterConfig[REG_FRFLSB][VALUE] = RF_FRFLSB_915;
    RegisterConfig[REG_FRFLSB][WILL_WRITE] = 1;

    RegisterConfig[REG_RXBW][VALUE] = RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_16 | RF_RXBW_EXP_2;
    RegisterConfig[REG_RXBW][WILL_WRITE] = 1;

    RegisterConfig[REG_DIOMAPPING1][VALUE] = RF_DIOMAPPING1_DIO0_01;
    RegisterConfig[REG_DIOMAPPING1][WILL_WRITE] = 1;
    
    RegisterConfig[REG_DIOMAPPING2][VALUE] = RF_DIOMAPPING2_CLKOUT_OFF;
    RegisterConfig[REG_DIOMAPPING2][WILL_WRITE] = 1;
    
    RegisterConfig[REG_IRQFLAGS2][VALUE] = RF_IRQFLAGS2_FIFOOVERRUN;
    RegisterConfig[REG_IRQFLAGS2][WILL_WRITE] = 1;
    
    RegisterConfig[REG_RSSITHRESH][VALUE] = 220;
    RegisterConfig[REG_RSSITHRESH][WILL_WRITE] = 1;
    
    RegisterConfig[REG_SYNCCONFIG][VALUE] = RF_SYNC_ON | RF_SYNC_FIFOFILL_AUTO | RF_SYNC_SIZE_2 | RF_SYNC_TOL_0;
    RegisterConfig[REG_SYNCCONFIG][WILL_WRITE] = 1;
    
    RegisterConfig[REG_SYNCVALUE1][VALUE] = 0x2D;
    RegisterConfig[REG_SYNCVALUE1][WILL_WRITE] = 1;
    
    RegisterConfig[REG_SYNCVALUE2][VALUE] = 0x00; // networkID 0
    RegisterConfig[REG_SYNCVALUE2][WILL_WRITE] = 1;
    
    RegisterConfig[REG_PACKETCONFIG1][VALUE] = RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRCAUTOCLEAR_ON | RF_PACKET1_ADRSFILTERING_OFF;
    RegisterConfig[REG_PACKETCONFIG1][WILL_WRITE] = 1;

    RegisterConfig[REG_PAYLOADLENGTH][VALUE] = 66;
    RegisterConfig[REG_PAYLOADLENGTH][WILL_WRITE] = 1;

    RegisterConfig[REG_FIFOTHRESH][VALUE] = RF_FIFOTHRESH_TXSTART_FIFONOTEMPTY | RF_FIFOTHRESH_VALUE;
    RegisterConfig[REG_FIFOTHRESH][WILL_WRITE] = 1;

    RegisterConfig[REG_PACKETCONFIG2][VALUE] = RF_PACKET2_RXRESTARTDELAY_2BITS | RF_PACKET2_AUTORXRESTART_ON | RF_PACKET2_AES_OFF;
    RegisterConfig[REG_PACKETCONFIG2][WILL_WRITE] = 1;

    RegisterConfig[REG_TESTDAGC][VALUE] = RF_DAGC_IMPROVED_LOWBETA0;
    RegisterConfig[REG_TESTDAGC][WILL_WRITE] = 1;
}

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

