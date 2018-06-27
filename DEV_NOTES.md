FIXED: FXOSC = 32000000 Hz = 32MHz :        Crystal Oscillator Frequency
FIXED: FSTEP = 61 Hz               :        Frquency Synthesizer Step
FIXED: FRC   = 62500 Hz = 62.5 Khz :        RC Oscillator Frequency



Carrier frequency is specified in 3 bytes (MSB, MID, LSB)
Carrier frquency is locked in upon write LSB

VARIABLE: FRF = FSTEP * F_rf(3 bytes) :       Carrier Frequency
    EXAMPLE:    = 61 Hz * ( (uint) 0xD7C000)
                = 61 Hz * 14,139,392
                = 862,502,912 Hz
                = 862.5 MHz
    
    FOR F_rf:
        F_rf = FRF / FSTEP                              ******
    Target Freq: 916.4 Mhz
    EXAMPLE: F_rf = 916,400,000 Hz / 61 Hz (integer division, throw away modulus)
             F_rf = 15,022,950
             F_rf = 0xE53B66 =
             {
                F_rf_MSB = 0xE5
                F_rf_MID = 0x3B
                F_rf_LSB = 0x66
             }

VARIABLE:       FDEV = FSTEP * F_dev(bytes) 
 For F_dev:     F_dev = FDEV / FSTEP                    ******

VARIABLE:       BITRATE = FXOSC / bitrate(bytes)
 For bitrate:   bitrate(bytes) = FXOSC / BITRATE        ****** 

Per the datasheet: To ensure a proper modulation, the following limit applies:
                    FDEV + BITRATE/2 <= 500 kHz

                   For efficient demodulation, the following constraint applies:
                    ß : modulation index
                    ß = (2 * FDEV) / BITRATE
                    0.5 <= ß <= 10

In RFM69 base class we see:
 For read operations: SPI.transfer(REG_FIFO & 0x7F);
 For write operations: SPI.transfer(REG_FIFO | 0x80);
    These values appear to be essentially hardcoded, but handles cases where REG_FIFO changes (will it ever?)
    Why: The SPI interface of the RFM69* chips look at bit 7 (wnr) to determine if the
        incoming operations are read or write access. See: 5.2.1. SPI Interface

