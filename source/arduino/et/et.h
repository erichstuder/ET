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

#ifndef ET_H
#define ET_H

#include "etConfig.h"

#define ET_OUTPUT_TIMEOUT 2 //s

void setupEt();

inline void toEt(byte buf[], int len){
	Serial1.write(ET_INPUT_ID);
	Serial1.write(buf, len);
	Serial1.flush();
}

inline boolean fromEt(byte buf[], int len){
	if(Serial1.available() >= len+1){
		if(Serial1.read() == ET_OUTPUT_ID){
			int n;
			for(n=0; n<len; n++){
				buf[n] = Serial1.read();		
			}
			return true;
		}
	}
	return false;
}

inline boolean syncEt(boolean (*doneFunc)(void)){
	while(Serial1.available()){
		Serial1.read();
	}
	//digitalWrite(LED_BUILTIN, HIGH);
	Serial1.write(ET_SYNC_ID);
	while(!(*doneFunc)()){
		if(Serial1.available()>0){
			//digitalWrite(LED_BUILTIN, HIGH);
			//Serial.println(Serial1.read()==ET_SYNCED_ID);
			return Serial1.read()==ET_SYNCED_ID;
		}
	}
	//digitalWrite(LED_BUILTIN, LOW);
	return false;
}

#endif //ET_H
