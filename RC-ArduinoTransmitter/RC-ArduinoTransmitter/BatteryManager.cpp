#include "BatteryManager.h"

int GetBatteryPercentage()
{
	return map(analogRead(A0), 800, 1023, 0, 100);
}


