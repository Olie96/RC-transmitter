// Tst.h

#ifndef _SCREENMANAGER_h
#define _SCREENMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <UTFT.h>
	#include <UTouch.h>
#else
	#include "WProgram.h"
#endif

enum enum_menu : uint8_t
{
	main_menu = 0,
	drone = 1,
	car = 2,
	plane = 3,
	display = 4,
	system_info = 5,
	settings = 6,
	calibration = 7,
	gps = 8
};

void SetUpLcdConfig();
void LoadOperatingSystem();
void InitializeMainMenu();
void DrawMainButtons();
// header
void InitializeHeader();

void ShowVehicleStatus();
void InitializeFooter();

void waitForIt(int x1, int y1, int x2, int y2);
enum_menu ReadTouch(enum_menu menu);
enum_menu MainMenuButtonPressed(int x, int y);

#endif

