
// Include SPI (Serial Peripheral Interface) library. Does not support SPI Slave.
//#include <SPI.h>

boolean SSlast = LOW;         // SS last flag.
const byte led = 9;           // Slave LED digital I/O pin.
boolean ledState = HIGH;      // LED state flag.
const byte cmdBtn = 1;        // SPI cmdBtn master command code.
const byte cmdLEDState = 2;   // 
void SpiSlaveInit(void) {
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT); //always an output as only one slave exists
  //pinMode(SS, INPUT); //not used as only one slave exists
  
  // Enable SPI as slave.
  SPCR = (1 << SPE);
}

byte SpiTransfer(byte value) {
  SPDR = value;
  while(!(SPSR & (1<<SPIF)));
  delay(15); //needed?
  return SPDR;
}

void setup() {
  SpiSlaveInit();
}

void loop() {
  SpiTransfer(0xAA);
}
