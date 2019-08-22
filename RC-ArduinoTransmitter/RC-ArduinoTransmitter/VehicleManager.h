// VehicleManager.h

#ifndef _VEHICLEMANAGER_h
#define _VEHICLEMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


enum enum_vehicle_status : uint8_t
{
	Ready,
	Running
};

#endif

