#ifndef APP_ET_H
#define APP_ET_H

#include "app.h"
#include "et.h"

inline void appTick_et(struct appIn_T appIn, struct appOut_T appOut){
	toEt(appIn.byteArr, sizeof(appIn.byteArr));
	//fromEt(appOut.byteArr, sizeof(appOut.byteArr));
}

#endif //APP_ET_H
