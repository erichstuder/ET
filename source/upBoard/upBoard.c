/* standard headers */
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* mraa header */
#include "mraa/gpio.h"

int
main(void){
  int led_handle = -1;

  while(1){
    led_handle = open("/sys/class/leds/upboard:green:/brightness", O_WRONLY);
    write(led_handle, "1", 2*sizeof(char));
    close(led_handle);

    sleep(1);

    led_handle = open("/sys/class/leds/upboard:green:/brightness", O_WRONLY);
    write(led_handle, "0", 2* sizeof(char));
    close(led_handle);

    sleep(1);
  }
}
