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

#include "app/app.h"
#include "app/app.cpp"
#include "et/etDevice.h"
#include "et/etDevice.cpp" //for any reason this has to be done
#include "et/app_etDevice.h"

boolean timerEvent;
boolean etActive;
boolean etSynced;
struct appIn_T appIn;
struct appOut_T appOut;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	etActive = true;
	etSynced = false;
	setupEt();
	setupTimer();
}

void loop(){
	if(!timerEvent){
		return;
	}
	timerEvent=false;
	appIn.millis_ms = millis();
	if(!etActive){
		appTick(appIn, &appOut);
	}else{
		if(!etSynced){
			etSynced = syncEt(timerEventPending);
		}else{
			if(appTick_et(appIn, &appOut) == false){
				digitalWrite(LED_BUILTIN, HIGH);
				while(1);
			}
		}
	}
	Serial.println(appIn.millis_ms);
	Serial.println((long)appOut.squareMillis);
	Serial.println(appOut.sqrtMillis);	
	Serial.println("");
}

void setupTimer(){
	timerEvent=false;
	#if APP_SAMPLETIME==1
		TCCR1A = 0; //for any reason, this must be done!!
		TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10); //match on value of OCR1A and divide clock by 1024
		OCR1A = 15625; //1000ms
		TIMSK1 = _BV(OCIE1A); //enable interrupt
	#else
		#error APP_SAMPLETIME not supported
	#endif
}

boolean timerEventPending(){
	return timerEvent;
}

ISR(TIMER1_COMPA_vect){
	timerEvent=true;
}
