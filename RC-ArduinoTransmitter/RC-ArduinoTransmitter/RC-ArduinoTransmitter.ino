#include <memorysaver.h>
#include "ScreenManager.h"

#define LOW_PRIORITY 3000
#define MEDIUM_PRIORITY 1000
#define HIGH_PRIORITY 10

int lowPriority, mediumPriority, highPriority;
void SetUpPinModes();
enum enum_menu selectedMenu, currentMenu = empty;

void setup()
{
	SetUpPinModes();
	SetUpLcdConfig();
	LoadOperatingSystem();
	ClearScreen();
	RefreshHeader(1);
	RefreshFooter(1);
	//DrawMainButtons();
	delay(100);
	currentMenu = selectedMenu = main_menu;
}

void loop()
{
	selectedMenu = ReadTouch(currentMenu);
	if (selectedMenu == main_menu && selectedMenu != currentMenu)
	{
		ClearScreen();
		RefreshHeader(1);
		RefreshFooter(1);
		DrawMainButtons();
		currentMenu = selectedMenu;
	}
	else if(selectedMenu == drone && selectedMenu != currentMenu)
	{
		ClearScreen();
		RefreshHeader(1);
		RefreshFooter(1);
		DrawDroneMenu();
		currentMenu = selectedMenu;
	}
	else if (selectedMenu == display && selectedMenu != currentMenu)
	{
		ClearScreen();
		RefreshHeader(1);
		RefreshFooter(1);
		DrawDisplayMenu();
		currentMenu = selectedMenu;
	}

	if (highPriority > HIGH_PRIORITY)
	{
		highPriority = 0;
	}
	if (mediumPriority > MEDIUM_PRIORITY)
	{
		mediumPriority = 0;
	}
	if (lowPriority > LOW_PRIORITY)
	{
		RefreshHeader(0);
		RefreshFooter(0);
		lowPriority = 0;
	}
	DongleData w = ReadDongleValues();
	// 110
	// 633
	int re = map(w.LeftX, 100, 640, 0, 100);
	PrintHeader(String(re), 150);
	DrawProgressBar(30, 30, 200, 10, re, one_sided, landscape);
	highPriority++;
	mediumPriority++;
	lowPriority++;
}

void SetUpPinModes()
{
	pinMode(20, OUTPUT);
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A4, INPUT);
	analogWrite(20, GetBacklightValue());
}
