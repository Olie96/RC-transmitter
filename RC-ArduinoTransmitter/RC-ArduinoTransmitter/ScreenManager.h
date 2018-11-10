// Tst.h

#ifndef _SCREENMANAGER_h
#define _SCREENMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void SetUpLcdConfig();
void LoadOperatingSystem();
void InitializeMainMenu();
void DrawMainButtons();
// header
void InitializeHeader();
void ShowBatteryPercentage();
void ShowGpsStrength();
void ShowVehicleStatus();
void InitializeFooter();

#endif

