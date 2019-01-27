#include "et.h"

void setupEt(){
	Serial1.begin(2000000);
	while (!Serial1) {
		; // wait for serial port to connect. Needed for native USB port only
	}
}
