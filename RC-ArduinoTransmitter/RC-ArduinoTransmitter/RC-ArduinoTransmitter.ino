#include "ScreenManager.h"

#define LOW_PRIORITY 1000
#define MEDIUM_PRIORITY 500

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
	currentMenu = main_menu;
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
	pinMode(8, OUTPUT);
	analogWrite(8, 255);
	pinMode(A0, INPUT);
}
