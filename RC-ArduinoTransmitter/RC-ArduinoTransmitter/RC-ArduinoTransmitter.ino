#include <memorysaver.h>
#include "ScreenManager.h"

#define LOW_PRIORITY 3000
#define MEDIUM_PRIORITY 1000

int lowPriority, mediumPriority;
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
	DrawMainButtons();

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
}

void SetUpPinModes()
{
	pinMode(20, OUTPUT);
	analogWrite(20, GetBacklightValue());
	pinMode(A0, INPUT);
}
