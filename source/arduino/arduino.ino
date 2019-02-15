/* ET - External Tracer
 * Copyright (C) 2019 Erich Studer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

boolean timerEventPending(){
	return bitRead(TIFR1, OCF1A);
}

ISR(TIMER1_COMPA_vect){
	//unsigned long time_ms = millis();
	//unsigned long long squareMillis;
	//double sqrtMillis;
	struct appIn_T appIn;
	struct appOut_T appOut;

	boolean etActive = true;
	boolean etSynced = false;

	appIn.data.millis_ms = millis();
	
	if(!etActive){
		appTick(appIn, appOut);
	}else{
		if(!etSynced){
			etSynced = syncEt(&timerEventPending);
		}else{
			if(appTick_et(appIn, appOut) == false){
				while(1);
			}
		}
	}

//		if(Serial1.readString().equals("Hello Leonardo")){
//			if(digitalRead(LED_BUILTIN)){
//				digitalWrite(LED_BUILTIN, LOW);
//			}else{
//				digitalWrite(LED_BUILTIN, HIGH);
//			}
//		}
}
