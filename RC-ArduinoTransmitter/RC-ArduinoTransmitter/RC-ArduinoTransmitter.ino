#include <memorysaver.h>
#include "ScreenManager.h"

#define LOW_PRIORITY 3000
#define MEDIUM_PRIORITY 200
#define HIGH_PRIORITY 10

int lowPriority, mediumPriority, highPriority;
void SetUpPinModes();
enum enum_menu selectedMenu, currentMenu = empty;

void setup()
{
	SetUpPinModes();
	SetUpLcdConfig();
	DrawLogo();
	LoadOperatingSystem();
	ClearScreen();
	RefreshHeader(1);
	RefreshFooter(1);
	
	DrawMainButtons();
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
		DrawDrone();
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
	DongleData result = ReadDongleValues();
	//rawProgressBar(30, 30, 200, 10, map(result.RightX, 0, 255, 0, 100), two_sided, portrait);
	//DrawProgressBar(50, 230, 200, 10, map(result.RightY, 0, 255, 0, 100), two_sided, landscape);
	
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
	analogWrite(20, GetBacklightValue());
}

