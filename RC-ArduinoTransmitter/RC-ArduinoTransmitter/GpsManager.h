// GpsManager.h

#ifndef _GPSMANAGER_h
#define _GPSMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

int GetGpsStrength();

#endif

