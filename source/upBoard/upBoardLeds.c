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
