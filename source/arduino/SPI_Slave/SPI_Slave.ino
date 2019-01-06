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
