#include <math.h>
#include "app.h"

void appTick(struct appIn_T appIn, struct appOut_T appOut){
	unsigned long millis_ms = appIn.data.millis_ms;
	appOut.data.squareMillis = (unsigned long long)millis_ms * (unsigned long long)millis_ms;
	appOut.data.sqrtMillis = sqrt(millis_ms);
}
