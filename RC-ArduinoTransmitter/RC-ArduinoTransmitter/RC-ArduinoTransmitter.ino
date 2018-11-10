#include "VehicleManager.h"
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
	InitializeMainMenu();
	currentMenu = main_menu;
}

void loop()
{
	currentMenu = ReadTouch(currentMenu);

	if (currentMenu == main_menu && currentMenu != previousMenu)
	{
		DrawMainButtons();
	}

	if (mediumPriority > MEDIUM_PRIORITY)
	{
		mediumPriority = 0;
	}
	if (lowPriority > LOW_PRIORITY)
	{
		RefreshHeader();
		RefreshFooter();
		lowPriority = 0;
	}

	mediumPriority++;
	lowPriority++;
	previousMenu = currentMenu;
}


void SetUpPinModes()
{
	pinMode(8, OUTPUT);
	digitalWrite(8, HIGH);
	pinMode(A0, INPUT);
}
