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

#ifndef APP_ET_H
#define APP_ET_H

//#include "app.h" //for appIn_T and appOut_T
//#include "et.h"

inline boolean appTick_et(struct appIn_T appIn, struct appOut_T appOut){
	unsigned long initMillis = millis();
	boolean success = false;
	
	toEt((byte*)&appIn, sizeof(appIn));

	while(millis() - initMillis < ET_OUTPUT_TIMEOUT*1000UL){
		success = fromEt((byte*)&appOut, sizeof(appOut));	
	}
	return success;
}

#endif //APP_ET_H
