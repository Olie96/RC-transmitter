#include <memorysaver.h>
#include "ScreenManager.h"

#define LOW_PRIORITY 2000
#define MEDIUM_PRIORITY 1000

int lowPriority, mediumPriority;
void SetUpPinModes();
enum enum_menu currentMenu, previousMenu;

void setup()
{
	SetUpPinModes();
	SetUpLcdConfig();
	LoadOperatingSystem();
	ClearScreen();
	InitializeMainMenu();

	delay(100);
	currentMenu = display;
}

void loop()
{
	currentMenu = ReadTouch(currentMenu);

	if (currentMenu == main_menu && currentMenu != previousMenu)
	{
		ClearScreen();
		RefreshHeader(1);
		RefreshFooter(1);
		DrawMainButtons();

	}
	else if(currentMenu == drone && currentMenu != previousMenu)
	{
		ClearScreen();
		RefreshHeader(1);
		RefreshFooter(1);
		DrawDroneMenu();
	}
	else if (currentMenu == display && currentMenu != previousMenu)
	{
		ClearScreen();
		RefreshHeader(1);
		RefreshFooter(1);
		DrawDisplayMenu();
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

	mediumPriority++;
	lowPriority++;
	previousMenu = currentMenu;
}

void SetUpPinModes()
{
	pinMode(20, OUTPUT);
	analogWrite(20, GetBacklightValue());
	pinMode(A0, INPUT);
}
