#ifndef ET_H
#define ET_H

#include "arduino.h"

void setupEt();

inline void toEt(byte buf[], int len){
	Serial1.write(buf, len);	
}




#endif //ET_H
