#ifndef RFM69_CONF_H
#define RFM69_CONF_H

#define REGISTER_COUNT 0x71

#define RFM_FSTEP 61

#define RFM_FXOSC 32000000

#include <Arduino.h>
#include <RFM69registers.h>

enum RegisterIndex : uint8_t 
{ 
    VALUE = 0, 
    WILL_WRITE = 1 
};

enum SyncWordErrorTolerance : uint8_t
{
    TOL_0 = 0x00,
    TOL_1 = 0x01,
    TOL_2 = 0x02,
    TOL_3 = 0x03,
    TOL_4 = 0x04,
    TOL_5 = 0x05,
    TOL_6 = 0x06,
    TOL_7 = 0x07,
};

enum SyncEnable : uint8_t 
{
    DISABLE = 0x00,
    ENABLE = 0x80
};

enum OperatingMode : uint8_t
{
    SLEEP      = RF_OPMODE_SLEEP       ,
    STANDBY    = RF_OPMODE_STANDBY     ,
    FREQ_SYNTH = RF_OPMODE_SYNTHESIZER ,
    TRANSMIT   = RF_OPMODE_TRANSMITTER ,
    RECEIVE    = RF_OPMODE_RECEIVER    
};

enum ListenMode : uint8_t
{
    OFF = RF_OPMODE_LISTEN_OFF,
    ON = RF_OPMODE_LISTEN_ON
};

enum DataMode : uint8_t
{
    PACKET = RF_DATAMODUL_DATAMODE_PACKET,
    CONTINUOUS = RF_DATAMODUL_DATAMODE_CONTINUOUS,
    CONTINUOUS_NOBITSYNC = RF_DATAMODUL_DATAMODE_CONTINUOUSNOBSYNC
};

enum ModulationType : uint8_t
{
    FSK = RF_DATAMODUL_MODULATIONTYPE_FSK,
    OOK = RF_DATAMODUL_MODULATIONTYPE_OOK
};

enum ModulationShapingFSK : uint8_t
{
    NONE = 0x00,
    GUASSIAN_BT1_0 = 0x01,
    GUASSIAN_BT0_5 = 0x02,
    GUASSIAN_BT0_3 = 0x03,
};

enum ModulationShapingFSK : uint8_t
{
    NONE = 0x00,
    GUASSIAN_BT1_0 = 0x01,
    GUASSIAN_BT0_5 = 0x02,
    GUASSIAN_BT0_3 = 0x03
};

enum ModulationShapingOOK : uint8_t
{
    NONE = 0x00,
    FCUTOFF_1BITRATE = 0x01,
    FCUTOFF_2BITRATE = 0x02
};

enum AFCLowBeta : uint8_t
{
    STANDARD = RF_AFCCTRL_LOWBETA_OFF,
    IMPROVED = RF_AFCCTRL_LOWBETA_ON
};

class RFM69Config
{
    public:

    RFM69Config();

    const uint8_t getRegisterVal(uint8_t rfm_register, RegisterIndex value);

    uint8_t &operator[] (uint8_t);

    void writeOperationMode(OperatingMode mode);
    // void writeListenMode(ListenMode mode);
    // void abortListen();

    void writeDataMode(DataMode mode);
    void writeModulationType(ModulationType modType);
    void writeModulationShapingFSK(ModulationShapingFSK shaping);
    void writeModulationShapingOOK(ModulationShapingOOK shaping);

    void writeBitrate(uint16_t targetBitrate);
    void writeFrequencyDeviation(uint16_t targetFreqDev);
    void writeCarrierFrequency(uint32_t targetFrequency);

    // RC Calibration in base class: rcCalibration()

    // Automatic Frequency Control
    void writeAFCLowBeta(AFCLowBeta afc);

    // void writeListenIdleTimeResolution();
    // void writeListenRXTimeResolution();
    // void writeListenPacketAcceptCriteria();
    // void writeListenEndAction();
    //// ListenIdleTime = ListenIdleTimeResolution * ListenIdleDurationCoefficient
    // void writeListenIdleDurationCoefficient(); 
    //// ListenRXTime = ListenRXTimeResolution * ListenRXDurationCoefficient
    // void writeListenRXDurationCoefficient();

    // uint8_t readChipVersion();

    // writePowerLevel(); // In Base RFM69 : setPowerLevel(...)

    //// Control TX power amplifier ramp time 
    // void writePaRamp();

    // void writePAOvercurrentProtect(); // Handled in Base RFM69
    // void writePAOCPTrim(uint8_t); // 95 mA default

    // Low Noise Amplifier
    // void writeLNAInputImpedance();
    // void writeLNACurrentGain();
    // void writeLNAGainSelect();

    // RXBW : 

    // AFCBW :

    // OOK Demodulation Config
    // void writeOOKThresholdType();
    // void writeOOKPeakThesholdStep();
    // void writeOOKPeakThresholdPeriod();

    // void writeOOKAverageThresholdFilterCoeff();

    // void writeOOKFixedThreshold();


    void writeSyncEnable(SyncEnable isSyncEnabled);
    void writeSyncWord(uint8_t syncWordByteCount, uint64_t syncWord);
    void writeSyncWordErrorTolerance(SyncWordErrorTolerance errorTol);

    void writeAESKey(uint64_t AES_MSB, uint64_t AES_LSB);

    private:

    uint8_t registerConfig[REGISTER_COUNT][2] = {                                                                   // Use defaults from base RFM69
        { 0, 0 },                                                                                                   // 0x00 : REG_FIFO
        { RF_OPMODE_SEQUENCER_ON | RF_OPMODE_LISTEN_OFF | RF_OPMODE_STANDBY, 1 },                                   // 0x01 : REG_OPMODE
        { RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_00, 1 },  // 0x02 : REG_DATAMODUL
        { RF_BITRATEMSB_55555, 1 },                                                                                 // 0x03 : REG_BITRATEMSB
        { RF_BITRATELSB_55555, 1 },                                                                                 // 0x04 : REG_BITRATELSB
        { RF_FDEVMSB_50000, 1 },                                                                                    // 0x05 : REG_FDEVMSB
        { RF_FDEVLSB_50000, 1 },                                                                                    // 0x06 : REG_FDEVLSB
        { 0, 1 },                                                                                                   // 0x07 : REG_FRFMSB
        { 0, 1 },                                                                                                   // 0x08 : REG_FRFMID
        { 0, 1 },                                                                                                   // 0x09 : REG_FRFLSB
        { 0, 0 },                                                                                                   // 0x0A : REG_OSC1
        { 0, 0 },                                                                                                   // 0x0x : REG_AFCCTRL
        { 0, 0 },                                                                                                   // 0x0C : REG_LOWBAT
        { 0, 0 },                                                                                                   // 0x0D : REG_LISTEN1
        { 0, 0 },                                                                                                   // 0x0E : REG_LISTEN2
        { 0, 0 },                                                                                                   // 0x0F : REG_LISTEN3
        { 0, 0 },                                                                                                   // 0x10 : REG_VERSION
        { 0, 0 },                                                                                                   // 0x11 : REG_PALEVEL
        { 0, 0 },                                                                                                   // 0x12 : REG_PARAMP
        { 0, 0 },                                                                                                   // 0x13 : REG_OCP
        { 0, 0 },                                                                                                   // 0x14 : REG_AGCREF     // not present on RFM69/SX1231
        { 0, 0 },                                                                                                   // 0x15 : REG_AGCTHRESH1 // not present on RFM69/SX1231
        { 0, 0 },                                                                                                   // 0x16 : REG_AGCTHRESH2 // not present on RFM69/SX1231
        { 0, 0 },                                                                                                   // 0x17 : REG_AGCTHRESH3 // not present on RFM69/SX1231
        { 0, 0 },                                                                                                   // 0x18 : REG_LNA
        { RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_16 | RF_RXBW_EXP_2, 1 },                                               // 0x19 : REG_RXBW
        { 0, 0 },                                                                                                   // 0x1A : REG_AFCBW
        { 0, 0 },                                                                                                   // 0x1B : REG_OOKPEAK
        { 0, 0 },                                                                                                   // 0x1C : REG_OOKAVG
        { 0, 0 },                                                                                                   // 0x1D : REG_OOKFIX
        { 0, 0 },                                                                                                   // 0x1E : REG_AFCFEI
        { 0, 0 },                                                                                                   // 0x1F : REG_AFCMSB
        { 0, 0 },                                                                                                   // 0x20 : REG_AFCLSB
        { 0, 0 },                                                                                                   // 0x21 : REG_FEIMSB
        { 0, 0 },                                                                                                   // 0x22 : REG_FEILSB
        { 0, 0 },                                                                                                   // 0x23 : REG_RSSICONFIG
        { 0, 0 },                                                                                                   // 0x24 : REG_RSSIVALUE
        { RF_DIOMAPPING1_DIO0_01, 1 },                                                                              // 0x25 : REG_DIOMAPPING1
        { RF_DIOMAPPING2_CLKOUT_OFF, 1 },                                                                           // 0x26 : REG_DIOMAPPING2
        { 0, 0 },                                                                                                   // 0x27 : REG_IRQFLAGS1
        { RF_IRQFLAGS2_FIFOOVERRUN, 1 },                                                                            // 0x28 : REG_IRQFLAGS2
        { 220, 1 },                                                                                                 // 0x29 : REG_RSSITHRESH
        { 0, 0 },                                                                                                   // 0x2A : REG_RXTIMEOUT1
        { 0, 0 },                                                                                                   // 0x2B : REG_RXTIMEOUT2
        { 0, 0 },                                                                                                   // 0x2C : REG_PREAMBLEMSB
        { 0, 0 },                                                                                                   // 0x2D : REG_PREAMBLELSB
        { RF_SYNC_ON | RF_SYNC_FIFOFILL_AUTO | RF_SYNC_SIZE_2 | RF_SYNC_TOL_0, 1 },                                 // 0x2E : REG_SYNCCONFIG
        { 0x2D, 1 },                                                                                                // 0x2F : REG_SYNCVALUE1
        { 0x00, 1 },                                                                                                // 0x30 : REG_SYNCVALUE2
        { 0, 0 },                                                                                                   // 0x31 : REG_SYNCVALUE3
        { 0, 0 },                                                                                                   // 0x32 : REG_SYNCVALUE4
        { 0, 0 },                                                                                                   // 0x33 : REG_SYNCVALUE5
        { 0, 0 },                                                                                                   // 0x34 : REG_SYNCVALUE6
        { 0, 0 },                                                                                                   // 0x35 : REG_SYNCVALUE7
        { 0, 0 },                                                                                                   // 0x36 : REG_SYNCVALUE8
        { RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRCAUTOCLEAR_ON | RF_PACKET1_ADRSFILTERING_OFF, 1 },  // 0x37 : REG_PACKETCONFIG1
        { 66, 1 },                                                                                                  // 0x38 : REG_PAYLOADLENGTH
        { 0, 0 },                                                                                                   // 0x39 : REG_NODEADRS
        { 0, 0 },                                                                                                   // 0x3A : REG_BROADCASTADRS
        { 0, 0 },                                                                                                   // 0x3B : REG_AUTOMODES
        { RF_FIFOTHRESH_TXSTART_FIFONOTEMPTY | RF_FIFOTHRESH_VALUE, 1 },                                            // 0x3C : REG_FIFOTHRESH
        { RF_PACKET2_RXRESTARTDELAY_2BITS | RF_PACKET2_AUTORXRESTART_ON | RF_PACKET2_AES_OFF, 1 },                  // 0x3D : REG_PACKETCONFIG2
        { 0, 0 },                                                                                                   // 0x3E : REG_AESKEY1
        { 0, 0 },                                                                                                   // 0x3F : REG_AESKEY2
        { 0, 0 },                                                                                                   // 0x40 : REG_AESKEY3
        { 0, 0 },                                                                                                   // 0x41 : REG_AESKEY4
        { 0, 0 },                                                                                                   // 0x42 : REG_AESKEY5
        { 0, 0 },                                                                                                   // 0x43 : REG_AESKEY6
        { 0, 0 },                                                                                                   // 0x44 : REG_AESKEY7
        { 0, 0 },                                                                                                   // 0x45 : REG_AESKEY8
        { 0, 0 },                                                                                                   // 0x46 : REG_AESKEY9
        { 0, 0 },                                                                                                   // 0x47 : REG_AESKEY10
        { 0, 0 },                                                                                                   // 0x48 : REG_AESKEY11
        { 0, 0 },                                                                                                   // 0x49 : REG_AESKEY12
        { 0, 0 },                                                                                                   // 0x4A : REG_AESKEY13
        { 0, 0 },                                                                                                   // 0x4B : REG_AESKEY14
        { 0, 0 },                                                                                                   // 0x4C : REG_AESKEY15
        { 0, 0 },                                                                                                   // 0x4D : REG_AESKEY16
        { 0, 0 },                                                                                                   // 0x4E : REG_TEMP1
        { 0, 0 },                                                                                                   // 0x4F : REG_TEMP2
        { 0, 0 },                                                                                                   // 0x50 : 0x50             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x51 : 0x51             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x52 : 0x52             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x53 : 0x53             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x54 : 0x54             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x55 : 0x55             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x56 : 0x56             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x57 : 0x57             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x58 : REG_TESTLNA
        { 0, 0 },                                                                                                   // 0x59 : 0x59             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x5A : REG_TESTPA1   // only present on RFM69HW/SX1231H
        { 0, 0 },                                                                                                   // 0x5B : 0x5B             Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x5C : REG_TESTPA2   // only present on RFM69HW/SX1231H
        { 0, 0 },                                                                                                   // 0x5D :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x5E :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x5F :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x60 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x61 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x62 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x63 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x64 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x65 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x66 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x67 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x68 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x69 :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x6A :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x6B :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x6C :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x6D :                  Maintain mapping so that we can index by register
        { 0, 0 },                                                                                                   // 0x6E :                  Maintain mapping so that we can index by register
        { RF_DAGC_IMPROVED_LOWBETA0, 1 },                                                                           // 0x6F : REG_TESTDAGC
        { 255, 255 }   // Terminator
    };

    uint16_t bitrate = 0;
    uint16_t frequencyDeviation = 0;
    uint32_t centerFrequency = 0;

    void splitWord(uint8_t* wordBytes, uint8_t wordByteCount, uint64_t word);


};

#endif