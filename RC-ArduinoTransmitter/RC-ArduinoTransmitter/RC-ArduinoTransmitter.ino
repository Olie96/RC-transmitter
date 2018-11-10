#include "ScreenManager.h"

#define LOW_PRIORITY 200
#define MEDIUM_PRIORITY 100

int lowPriority, mediumPriority;
void SetUpPinModes();

void setup()
{
	SetUpPinModes();
	SetUpLcdConfig();
	LoadOperatingSystem();
	InitializeMainMenu();
}

void loop()
{
	ReadTouch();
	if (mediumPriority > MEDIUM_PRIORITY)
	{
		mediumPriority = 0;
	}
	if (lowPriority > LOW_PRIORITY)
	{
		ShowGpsStrength();
		ShowBatteryPercentage();
		ShowVehicleStatus();
		lowPriority = 0;
	}

	mediumPriority++;
	lowPriority++;
}


void SetUpPinModes()
{
	pinMode(8, OUTPUT);
	digitalWrite(8, HIGH);
	pinMode(A0, INPUT);
}
