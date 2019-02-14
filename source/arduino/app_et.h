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

#include "app.h"
#include "et.h"

inline void appTick_et(struct appIn_T appIn, struct appOut_T appOut){
	toEt(appIn.byteArr, sizeof(appIn.byteArr));
	//fromEt(appOut.byteArr, sizeof(appOut.byteArr));
}

#endif //APP_ET_H
