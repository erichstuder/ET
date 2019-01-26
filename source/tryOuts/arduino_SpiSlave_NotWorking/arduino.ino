#define DATA_READY_PIN A0
#define SCLK A1
#define MISO A2

const uint8_t dummySend[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};


void setup() {
	// Arduino leoanardo slave spi is not working as:
	// The necessary SS pin is not easily accessible.
	pinMode(DATA_READY_PIN, OUTPUT);
	pinMode(SCLK, INPUT);
	pinMode(MISO, OUTPUT);
	
	pinMode(LED_BUILTIN, OUTPUT); //debug

	setupTimer();
}

//debug
//void loop() {
//	digitalWrite(LED_BUILTIN, digitalRead(SCK));	
//}

//void loop() {
//	int cnt = 0;
//	delay(100);
//
//	digitalWrite(DATA_READY_PIN, LOW);
//	delay(900);
//}

void loop(){
}

void setupTimer(){
  TCCR1A = 0; //for any reason, this must be done!!
  TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10); //match on value of OCR1A and divide clock by 1024
  OCR1A = 15625; //1000ms
  TIMSK1 = _BV(OCIE1A); //enable interrupt
}

ISR(TIMER1_COMPA_vect){
	bool dataSent;
	
	//aktoren setzen
	
	//sensoren einlesen

	digitalWrite(DATA_READY_PIN, HIGH);

	//transmit data
	do{
		if(digitalRead(SCLK)){
			digitalWrite(MISO, );	
		}
	}while(!dataSent);
	

	if(digitalRead(LED_BUILTIN)){
		digitalWrite(LED_BUILTIN, LOW);
	}else{
		digitalWrite(LED_BUILTIN, HIGH);
	}	
}
