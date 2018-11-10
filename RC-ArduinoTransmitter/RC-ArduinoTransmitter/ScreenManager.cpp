#include "BatteryManager.h"
#include "GpsManager.h"
#include "VehicleManager.h"
#include "ScreenManager.h"

#pragma region Screen variables 

int screenBacklight = 790;
int backlight = 255;
UTFT Screen(SSD1963_800480, 38, 39, 40, 41);
UTouch  Touch(43, 42, 44, 45, 46);
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

#pragma endregion

#pragma region Button positions

#pragma region Main menu

#define FIRST_COLUMN_MAIN_MENU_BEGIN_X	15 
#define FIRST_COLUMN_MAIN_MENU_END_X	255 
#define SECOND_COLUMN_MAIN_MENU_BEGIN_X 270 
#define SECOND_COLUMN_MAIN_MENU_END_X	520 
#define THIRD_COLUMN_MAIN_MENU_BEGIN_X	535 
#define THIRD_COLUMN_MAIN_MENU_END_X	785 

#define FIRST_ROW_MAIN_MENU_BEGIN_Y		35 
#define FIRST_ROW_MAIN_MENU_END_Y		100 
#define SECOND_ROW_MAIN_MENU_BEGIN_Y	117 
#define SECOND_ROW_MAIN_MENU_END_Y		182 
#define THIRD_ROW_MAIN_MENU_BEGIN_Y		199 
#define THIRD_ROW_MAIN_MENU_END_Y		264 

#pragma endregion

#pragma region Drone menu



#pragma endregion

#pragma endregion

#pragma region Initialize system

void LoadOperatingSystem()
{
	Screen.print("Loading operating system", 210, 215);
	Screen.setColor(255, 255, 255);
	for (int x = 10; x <= 790; x++)
	{
		Screen.fillRoundRect(10, 235, x, 240);
	}

	delay(500);
}

void SetUpLcdConfig()
{
	Screen.InitLCD();
	Screen.clrScr();
	Touch.InitTouch();
	Touch.setPrecision(PREC_MEDIUM);
	Screen.setFont(BigFont);
}

#pragma endregion

#pragma region Screen

void ClearScreen()
{
	Screen.clrScr();
}

#pragma endregion

#pragma region Header

void PrintHeader(String text, int x)
{
	Screen.print(text, x, 3);
}

void RefreshHeader(int refresh)
{
	if (refresh == 1)
	{
		Screen.setColor(0, 10, 255);
		Screen.setBackColor(0, 10, 255);
		Screen.fillRoundRect(0, 0, 799, 18);
		Screen.setColor(255, 255, 255);
	}

	Screen.setFont(SmallFont);
	PrintHeader("GPS " + String(GetGpsStrength()) + "%", 650);
	PrintHeader("Status: " + String(GetVehicleStatus()), 10);
	PrintHeader(String(GetBatteryPercentage()) + "%", 730);
}

#pragma endregion

#pragma region Footer

void PrintFooter(String text, int x)
{
	Screen.print(text, x, 465);
}

void RefreshFooter(int refresh)
{
	if (refresh == 1)
	{
		Screen.setColor(0, 10, 255);
		Screen.setBackColor(0, 10, 255);
		Screen.fillRoundRect(0, 462, 800, 480);
		Screen.setColor(255, 255, 255);
	}
	PrintFooter("backlight: " + String(map(backlight, 0,255 ,0, 100)) + "%", 650);
}

#pragma endregion

#pragma region Main menu

void InitializeMainMenu()
{
	RefreshHeader(1);
	RefreshFooter(1);
	DrawMainButtons();
}

#pragma endregion

enum_menu ReadTouch(enum_menu menu)
{
	enum enum_menu selectedMenu = menu;
	if (Touch.dataAvailable())
	{
		Touch.read();
		int x = Touch.getX();
		int y = Touch.getY();
		PrintFooter("X:" + String(x) + " Y:" + String(y), 30);
		if (menu == main_menu)
		{
			selectedMenu = MainMenuButtonPressed(x, y, menu);
		}
		if (menu == drone)
		{
			selectedMenu = DroneMenuButtonPressed(x, y, menu);
		}
		if (menu == display)
		{
			selectedMenu = DisplayMenuButtonPressed(x, y, menu);
		}
	}
	return selectedMenu;
}

void waitForIt(int x1, int y1, int x2, int y2)
{
	Screen.setColor(255, 0, 0);
	Screen.drawRoundRect(x1, y1, x2, y2);
	while (Touch.dataAvailable())
		Touch.read();
	Screen.setColor(255, 255, 255);
	Screen.drawRoundRect(x1, y1, x2, y2);
}

#pragma region Draw buttons

void DrawMainButtons()
{
	Screen.setFont(BigFont);
	Screen.setColor(0, 10, 255);

	Screen.fillRoundRect(FIRST_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
	Screen.fillRoundRect(SECOND_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
	Screen.fillRoundRect(THIRD_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);

	Screen.fillRoundRect(FIRST_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);
	Screen.fillRoundRect(SECOND_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);
	Screen.fillRoundRect(THIRD_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);

	Screen.fillRoundRect(FIRST_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y);
	Screen.fillRoundRect(SECOND_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y);
	Screen.fillRoundRect(THIRD_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y);

	Screen.setColor(255, 255, 255);
	Screen.setBackColor(0, 10, 255);
	Screen.print("DRONE", 90, 60);
	Screen.print("PLANE", 350, 60);
	Screen.print("CAR", 630, 60);
	Screen.print("SYSTEM", 80, 142);
	Screen.print("DISPLAY", 335, 142);
	Screen.print("CALIBRATION", 570, 142);
	Screen.print("GPS", 100, 224);
	Screen.print("TEST", 355, 224);
	Screen.print("TEST", 620, 224);
}

void DrawDroneMenu()
{
	DrawBackButton();
	Screen.drawRoundRect(70, 350, 270, 360);
	Screen.drawLine(170,350,170,360);

	Screen.drawRoundRect(30, 120, 40, 320);
	Screen.drawLine(30, 220, 40, 220);

	Screen.drawRoundRect(529, 350, 729, 360);
	Screen.drawLine(629, 350, 629, 360);

	Screen.drawRoundRect(769, 120, 759, 320);
	Screen.drawLine(769, 220, 759, 220);

	Screen.drawRoundRect(60, 50, 739, 330);
	DrawDrone();
}

void DrawBackButton()
{
	Screen.setColor(0, 10, 255);
	Screen.fillRoundRect(15, 420, 100, 450);
	Screen.setColor(255, 255, 255);
	Screen.setBackColor(0, 10, 255);
	Screen.setFont(SmallFont);
	Screen.print("<- Back", 27, 430);
}

void DrawDrone()
{
	//Screen.drawBitmap();
}

void DrawDisplayMenu()
{
	DrawBackButton();

	Screen.setColor(0, 10, 255);
	Screen.fillRoundRect(15, 50, 300, 100);

	Screen.fillRoundRect(15, 120, screenBacklight, 140);
	Screen.setColor(255, 255, 255);
	Screen.drawRoundRect(15, 120, 790, 140);
}

#pragma endregion

#pragma region Buttons pressed

enum_menu MainMenuButtonPressed(int x, int y, enum_menu menu)
{
	enum enum_menu selectedMenu = menu;
	if ((y >= FIRST_ROW_MAIN_MENU_BEGIN_Y) && (y <= FIRST_ROW_MAIN_MENU_END_Y))
	{
		if ((x >= FIRST_COLUMN_MAIN_MENU_BEGIN_X) && (x <= FIRST_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(FIRST_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
			selectedMenu = drone;
		}
		else if ((x >= SECOND_COLUMN_MAIN_MENU_BEGIN_X) && (x <= SECOND_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(SECOND_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
			selectedMenu = plane;
		}
		else if ((x >= THIRD_COLUMN_MAIN_MENU_BEGIN_X) && (x <= THIRD_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(THIRD_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
			selectedMenu = car;
		}
	}

	else if ((y >= SECOND_ROW_MAIN_MENU_BEGIN_Y) && (y <= SECOND_ROW_MAIN_MENU_END_Y))
	{
		if ((x >= FIRST_COLUMN_MAIN_MENU_BEGIN_X) && (x <= FIRST_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(FIRST_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);
			selectedMenu = system_info;
		}
		else if ((x >= SECOND_COLUMN_MAIN_MENU_BEGIN_X) && (x <= SECOND_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(SECOND_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);
			selectedMenu = display;
		}
		else if ((x >= THIRD_COLUMN_MAIN_MENU_BEGIN_X) && (x <= THIRD_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(THIRD_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);
			selectedMenu = calibration;
		}
	}

	else if ((y >= THIRD_ROW_MAIN_MENU_BEGIN_Y) && (y <= THIRD_ROW_MAIN_MENU_END_Y))
	{
		if ((x >= FIRST_COLUMN_MAIN_MENU_BEGIN_X) && (x <= FIRST_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(FIRST_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y);
			selectedMenu = gps;
		}
		else if ((x >= SECOND_COLUMN_MAIN_MENU_BEGIN_X) && (x <= SECOND_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(SECOND_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y);
		}
		else if ((x >= THIRD_COLUMN_MAIN_MENU_BEGIN_X) && (x <= THIRD_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(THIRD_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y);
		}
	}
	return selectedMenu;
}

enum_menu DroneMenuButtonPressed(int x, int y, enum_menu menu)
{
	enum enum_menu selectedMenu = menu;
	if ((y >= 420) && (y <= 450))
	{
		if ((x >= 15) && (x <= 100))
		{
			waitForIt(15, 420, 100, 450);
			selectedMenu = main_menu;
		}
	}
	return selectedMenu;
}

enum_menu DisplayMenuButtonPressed(int x, int y, enum_menu menu)
{
	enum enum_menu selectedMenu = menu;
	if ((y >= 50) && (y <= 100))
	{
		if ((x >= 15) && (x <= 300))
		{
			waitForIt(15, 50, 300, 100);
			selectedMenu = main_menu;
		}
	}
	else if((y >= 120) && (y <= 140))
	{
		if ((x >= 15) && (x <= 790))
		{
			SetBrightness();
		}
	}
	return selectedMenu;
}


void SetBrightness()
{
	while (Touch.dataAvailable())
	{
		Touch.read();
		screenBacklight = Touch.getX();

		if (screenBacklight > 790)
			screenBacklight = 790;
		else if (screenBacklight < 30)
			screenBacklight = 30;

		backlight = map(screenBacklight, 15,790,0,255);

		analogWrite(8, backlight);
		Screen.setColor(0,0,0);
		Screen.fillRoundRect(screenBacklight, 121, 790, 139);
		Screen.setColor(0, 10, 255);		
		Screen.fillRoundRect(12, 121, screenBacklight + 3, 139);
		delay(10);
	}
}

#pragma endregion
