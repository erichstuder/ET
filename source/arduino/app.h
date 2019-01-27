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
