
#include "RFM69_GP.h"
#include <RFM69registers.h>

bool RFM69GP::initialize(RFM69Config config)
{
  _interruptNum = digitalPinToInterrupt(_interruptPin);
  if (_interruptNum == NOT_AN_INTERRUPT) return false;

#ifdef RF69_ATTACHINTERRUPT_TAKES_PIN_NUMBER
    _interruptNum = _interruptPin;
#endif

  digitalWrite(_slaveSelectPin, HIGH);
  pinMode(_slaveSelectPin, OUTPUT);
  SPI.begin();


  unsigned long start = millis();

  uint8_t timeout = 50;
  do writeReg(REG_SYNCVALUE1, 0xAA); while (readReg(REG_SYNCVALUE1) != 0xaa && millis()-start < timeout);
  start = millis();
  do writeReg(REG_SYNCVALUE1, 0x55); while (readReg(REG_SYNCVALUE1) != 0x55 && millis()-start < timeout);

  // Refactor the config storage and retrieval
  for (uint8_t i = 0; true; i++)
  {
    if (!config.getRegisterVal(i, RegisterIndex::WILL_WRITE))
      continue;
    if (config.getRegisterVal(i, RegisterIndex::WILL_WRITE) == 255)
      break;
    writeReg(i, config.getRegisterVal(i, RegisterIndex::VALUE));
  }

  // Encryption is persistent between resets and can trip you up during debugging.
  // Disable it during initialization so we always start from a known state.
  encrypt(0);

  setHighPower(_isRFM69HW); // called regardless if it's a RFM69W or RFM69HW
  setMode(RF69_MODE_STANDBY);

  start = millis();

  while (((readReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00) && millis()-start < timeout); // wait for ModeReady

  if (millis()-start >= timeout)
    return false; // Init failed. No ModeReady

  _inISR = false;
  attachInterrupt(_interruptNum, RFM69::isr0, RISING);

  selfPointer = this;
  
  _address = nodeID;

  return true;
}