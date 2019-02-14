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

/* standard headers */
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* mraa header */
#include "mraa/gpio.h"

#include "upBoardLeds.h"

void setUpBoardLed(char led[], bool on){
	int led_handle = -1;

	if (strcmp(led, "green") == 0) {
		led_handle = open("/sys/class/leds/upboard:green:/brightness", O_WRONLY);
	}else if (strcmp(led, "red") == 0) {
		led_handle = open("/sys/class/leds/upboard:red:/brightness", O_WRONLY);
	}else if (strcmp(led, "yellow") == 0) {
		led_handle = open("/sys/class/leds/upboard:yellow:/brightness", O_WRONLY);
	}

	if(led_handle > 0) {
		if(on){
			write(led_handle, "1", 2*sizeof(char));
		}else{
			write(led_handle, "0", 2*sizeof(char));
		}
		close(led_handle);
	}
}
