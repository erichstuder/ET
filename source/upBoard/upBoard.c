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

#include <time.h>

/* mraa header */
#include "mraa/gpio.h"
#define GPIO_PIN_1 29
#include "mraa/uart.h"


#include "upBoardLeds.h"

#ifndef FALSE
#define FALSE 0
#define TRUE (!FALSE)
#endif

/* UART port name */
const char* dev_path = "/dev/ttyS1";

long nanoSecPassed(const struct timespec *start, const struct timespec *stop){
	return (stop->tv_sec - start->tv_sec)*1E9L + stop->tv_nsec - start->tv_nsec;
}

volatile sig_atomic_t flag = 1;

void sig_handler(int signum){
	if (signum == SIGINT) {
		fprintf(stdout, "Exiting...\n");
		flag = 0;
	}
}

#define receiveBufLength 10
uint8_t receiveBuf[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
//uint8_t dummyBuf[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

int main(void){
	int led_handle = -1;
	struct timespec startTime, currentTime;
	bool lowFound;
	//long startNanoSec, stopNanoSec;
	//int cnt=0;

	mraa_result_t status = MRAA_SUCCESS;
	mraa_gpio_context gpio_1;

	mraa_uart_context uart;
	char buffer[14];

	int baudrate = 3686400, stopbits = 1, databits = 8;
	mraa_uart_parity_t parity = MRAA_UART_PARITY_NONE;
	unsigned int ctsrts = FALSE, xonxoff = FALSE;
	const char* name = NULL;


	/* install signal handler */
	signal(SIGINT, sig_handler);

	/* initialize mraa for the platform (not needed most of the times) */
	mraa_init();

	printf("mraa_init done\n");

	gpio_1 = mraa_gpio_init(GPIO_PIN_1);
	if (gpio_1 == NULL) {
		fprintf(stderr, "Failed to initialize GPIO %d\n", GPIO_PIN_1);
		mraa_deinit();
		return EXIT_FAILURE;
	}

	printf("gpio_init done\n");

	status = mraa_gpio_dir(gpio_1, MRAA_GPIO_IN);
	if (status != MRAA_SUCCESS) {
		goto err_exit;
	}

	printf("init_raw started\n");

	/* initialize uart */
	uart = mraa_uart_init_raw(dev_path);
	if (uart == NULL) {
		fprintf(stderr, "Failed to initialize UART\n");
		return EXIT_FAILURE;
	}

	printf("init_raw done\n");

	/* set serial port parameters */
	status = mraa_uart_settings(-1, &dev_path, &name, &baudrate, &databits, &stopbits, &parity, &ctsrts, &xonxoff);
	if (status != MRAA_SUCCESS) {
		goto err_exit;
	}

	mraa_uart_set_baudrate(uart, 2000000);

	printf("init done\n");
	
	while(flag){
		if(mraa_uart_data_available(uart, 200)){
			mraa_uart_read(uart, buffer, 14);
			printf("%s\n", buffer);
		}else{
			printf("nothing\n");
		}
		mraa_uart_write(uart, "Hello Leonardo", 15);
		mraa_uart_flush(uart);

		//setUpBoardLed("red", true);
		usleep(0.9E6);
	}

	mraa_uart_stop(uart);

	/* release gpio's */
	status = mraa_gpio_close(gpio_1);
	if (status != MRAA_SUCCESS) {
		goto err_exit;
	}

	/* deinitialize mraa for the platform (not needed most of the times) */
	mraa_deinit();

	return EXIT_SUCCESS;


err_exit:
	mraa_result_print(status);

	mraa_uart_stop(uart);
	
	/* deinitialize mraa for the platform (not needed most of the times) */
	mraa_deinit();

	return EXIT_FAILURE;
}

