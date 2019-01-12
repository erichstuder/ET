/* standard headers */
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* mraa header */
#include "mraa/gpio.h"

#include "upBoardLeds.h"

int main(void){
	int led_handle = -1;

	while(1){
		setUpBoardLed("red", true);

		sleep(1);

		setUpBoardLed("red", false);

		sleep(1);
	}
}
