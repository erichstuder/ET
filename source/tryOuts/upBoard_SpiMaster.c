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
#include "mraa/spi.h"
#define SPI_BUS 0


#include "upBoardLeds.h"

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
	mraa_spi_context spi;

	/* install signal handler */
	signal(SIGINT, sig_handler);

	/* initialize mraa for the platform (not needed most of the times) */
	mraa_init();

	gpio_1 = mraa_gpio_init(GPIO_PIN_1);
	if (gpio_1 == NULL) {
		fprintf(stderr, "Failed to initialize GPIO %d\n", GPIO_PIN_1);
		mraa_deinit();
		return EXIT_FAILURE;
	}

	status = mraa_gpio_dir(gpio_1, MRAA_GPIO_IN);
	if (status != MRAA_SUCCESS) {
		goto err_exit;
	}

	spi = mraa_spi_init(SPI_BUS);
	if (spi == NULL) {
		fprintf(stderr, "Failed to initialize SPI\n");
		mraa_deinit();
		return EXIT_FAILURE;
	}

	status = mraa_spi_frequency(spi, 4000); //4E6);
	if (status != MRAA_SUCCESS){
		goto err_exit;
	}

	status = mraa_spi_lsbmode(spi, 0); //0: msb first
	if (status != MRAA_SUCCESS) {
		goto err_exit;
	}

	status = mraa_spi_bit_per_word(spi, 8);
	if (status != MRAA_SUCCESS) {
		fprintf(stdout, "Failed to set SPI Device to 8Bit mode\n");
		goto err_exit;
	}

	printf("init done\n");
	
	while(flag){
		//setUpBoardLed("red", true);

		//sleep(1);

		clock_gettime(CLOCK_REALTIME, &startTime);
		//cnt=0;
		lowFound = false;
		do{
			if(lowFound && mraa_gpio_read(gpio_1)==1){
				printf("highFound\n");
				mraa_spi_transfer_buf(spi, receiveBuf, receiveBuf, receiveBufLength); 		
				//mraa_spi_write_buf(spi, receiveBuf, receiveBufLength); 		
				printf("%d\n", receiveBuf[0]);
				printf("%d\n", receiveBuf[1]);
				printf("%d\n", receiveBuf[2]);
				printf("%d\n", receiveBuf[3]);
				printf("%d\n", receiveBuf[4]);
				printf("%d\n", receiveBuf[5]);
				printf("%d\n", receiveBuf[6]);
				printf("%d\n", receiveBuf[7]);
				printf("%d\n", receiveBuf[8]);
				printf("%d\n", receiveBuf[9]);
				printf("\n");
				break;
			}
			
			if(mraa_gpio_read(gpio_1)==0){
				lowFound = true;
			}

			clock_gettime(CLOCK_REALTIME, &currentTime);
			//printf("%ld\n", currentTime.tv_nsec);
			//cnt++;
			//printf("%d\n", mraa_gpio_read(gpio_1));
		}while(nanoSecPassed(&startTime, &currentTime) < 0.2E9L);

		//printf("%d\n",cnt);
		//printf("\n");

		//setUpBoardLed("red", false);

		usleep(0.9E6);
	}

	mraa_spi_stop(spi);

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

	/* deinitialize mraa for the platform (not needed most of the times) */
	mraa_deinit();

	return EXIT_FAILURE;
}

