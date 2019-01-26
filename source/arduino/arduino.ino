#define DATA_READY_PIN A0
#define SCLK A1
#define MISO A2

const uint8_t dummySend[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};


void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	Serial1.begin(2000000);
	while (!Serial1) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	setupTimer();
}

void loop(){
}

void setupTimer(){
  TCCR1A = 0; //for any reason, this must be done!!
  TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10); //match on value of OCR1A and divide clock by 1024
  OCR1A = 15625; //1000ms
  TIMSK1 = _BV(OCIE1A); //enable interrupt
}

ISR(TIMER1_COMPA_vect){
	char buf[15];
	Serial1.print("Hello upBoard");
	String str;
	//Serial1.write(0xAA);

//	while(Serial1.available() >= 1){
//		Serial1.read();
//		if(digitalRead(LED_BUILTIN)){
//			digitalWrite(LED_BUILTIN, LOW);
//		}else{
//			digitalWrite(LED_BUILTIN, HIGH);
//		}
//	}

	Serial.println("before loop");
	Serial.flush();
	
	if(Serial1.available() >= 15){
		//Serial1.read();
		//Serial1.readBytes(buf, 15);
		Serial.println("read string");
		Serial.flush();
		
		//str = Serial1.readString();
		Serial1.readBytes(buf ,15);
		
		Serial.println("try to print.");
		Serial.flush();
		
		Serial.println(buf);
		
		Serial.println("printed");
		Serial.flush();

//		if(Serial1.readString().equals("Hello Leonardo")){
//			if(digitalRead(LED_BUILTIN)){
//				digitalWrite(LED_BUILTIN, LOW);
//			}else{
//				digitalWrite(LED_BUILTIN, HIGH);
//			}
//		}
	}
}
