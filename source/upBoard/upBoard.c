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
#define GPIO_PIN_1 23
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
uint8_t receiveBuf[receiveBufLength];

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

	status = mraa_spi_frequency(spi, 4E6);
	if (status != MRAA_SUCCESS){
		goto err_exit;
	}

	status = mraa_spi_lsbmode(spi, 0); //0: msb first
	if (status != MRAA_SUCCESS) {
		goto err_exit;
	}

	while(flag){
		//setUpBoardLed("red", true);

		//sleep(1);

		clock_gettime(CLOCK_REALTIME, &startTime);
		//cnt=0;
		lowFound = false;
		do{
			if(lowFound && mraa_gpio_read(gpio_1)==1){
				//printf("highFound\n");
				mraa_spi_transfer_buf(spi, receiveBuf, receiveBuf, receiveBufLength); 		
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

