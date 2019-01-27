#include "app.h"
#include "et.h"
#include "app_et.h"

void setup() {
//	pinMode(LED_BUILTIN, OUTPUT);
	
//	Serial.begin(9600);
//	while (!Serial) {
//		; // wait for serial port to connect. Needed for native USB port only
//	}
	
	setupEt();
	
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
	//unsigned long time_ms = millis();
	//unsigned long long squareMillis;
	//double sqrtMillis;
	struct appIn_T appIn;
	struct appOut_T appOut;

	boolean etActive = true;

	appIn.data.millis_ms = millis();
	
	if(!etActive){
		appTick(appIn, appOut);
	}else{
		appTick_et(appIn, appOut);
	}
	
	
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
