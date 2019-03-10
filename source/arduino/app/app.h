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

#ifndef APP_H
#define APP_H

#include "arduino.h"


struct appIn_T{
	union{
		struct{
			unsigned long millis_ms;
		}data;
		byte byteArr[sizeof(data)];
	};
};

struct appOut_T{
	union{
		struct{
			unsigned long long squareMillis;
			double sqrtMillis;
		}data;
		byte byteArr[sizeof(data)];
	};
};

void appTick(struct appIn_T appIn, struct appOut_T appOut);

#endif //APP_H