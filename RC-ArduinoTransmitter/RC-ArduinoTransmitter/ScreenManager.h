// Tst.h

#ifndef _SCREENMANAGER_h
#define _SCREENMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
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

enum enum_text_position : uint8_t
{
	center = 0,
	left = 1,
	right = 2
};

#pragma region Initialize system

void SetUpLcdConfig();

#pragma endregion

#pragma region Main menu

void LoadOperatingSystem();
void InitializeMainMenu();

#pragma endregion

#pragma region Header / Footer

void RefreshHeader(int refresh);
void RefreshFooter(int refresh);
void PrintFooter(String text, int x);
void PrintHeader(String text, int x);

#pragma endregion

#pragma region Screen

int GetBacklightValue();
void ClearScreen();
void SetBrightness();
void DrawButton(int xBegin, int yBegin, int xEnd, int yEnd, String text, enum_text_position textPosition, uint8_t font[]);

#pragma endregion


#pragma region Touch

void waitForIt(int x1, int y1, int x2, int y2);
enum_menu ReadTouch(enum_menu menu);
enum_menu MainMenuButtonPressed(int x, int y, enum_menu menu);
enum_menu DroneMenuButtonPressed(int x, int y, enum_menu menu);
enum_menu DisplayMenuButtonPressed(int x, int y, enum_menu menu);

#pragma endregion

#pragma region Draw buttons

void DrawMainButtons();
void DrawDroneMenu();
void DrawDrone();
void DrawDisplayMenu();
void DrawBackButton();

#pragma endregion


#endif

