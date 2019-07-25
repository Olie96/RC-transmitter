#include "BatteryManager.h"
#include "GpsManager.h"
#include "VehicleManager.h"
#include "ScreenManager.h"
#include <UTouch.h>
#include <UTFT.h>

#pragma region Screen variables 

int screenBacklight = 790;
int backlight = 150;
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

#define LEFT_DONGLE_LR_POSITION_START_X	70
#define LEFT_DONGLE_LR_POSITION_END_X	270
#define LEFT_DONGLE_LR_POSITION_START_Y 350
#define LEFT_DONGLE_LR_POSITION_END_Y	360

#define LEFT_DONGLE_UD_POSITION_START_X 30
#define LEFT_DONGLE_UD_POSITION_END_X	40
#define LEFT_DONGLE_UD_POSITION_START_Y 120
#define LEFT_DONGLE_UD_POSITION_END_Y	320

#define RIGHT_DONGLE_LR_POSITION_START_X	529
#define RIGHT_DONGLE_LR_POSITION_END_X		729
#define RIGHT_DONGLE_LR_POSITION_START_Y	350
#define RIGHT_DONGLE_LR_POSITION_END_Y		360

#define RIGHT_DONGLE_UD_POSITION_START_X	759
#define RIGHT_DONGLE_UD_POSITION_END_X		769
#define RIGHT_DONGLE_UD_POSITION_START_Y	120
#define RIGHT_DONGLE_UD_POSITION_END_Y		320

#pragma endregion

#pragma region Back button

#define BACK_BUTTON_Y_BEGIN 420 
#define BACK_BUTTON_Y_END 450
#define BACK_BUTTON_X_BEGIN 15 
#define BACK_BUTTON_X_END 100

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

void InitializeMainMenu()
{
	RefreshHeader(1);
	RefreshFooter(1);
	DrawMainButtons();
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
	Screen.setFont(SmallFont);
	PrintFooter("backlight: " + String(map(backlight, 0,255 ,0, 100)) + "%", 650);
}

#pragma endregion

#pragma region Screen

void ClearScreen()
{
	Screen.clrScr();
}

int GetBacklightValue()
{
	return backlight;
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
	DrawButton(FIRST_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y, "DRONE", center, BigFont);
	DrawButton(SECOND_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y, "PLANE", center, BigFont);
	DrawButton(THIRD_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y, "CAR", center, BigFont);

	DrawButton(FIRST_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y, "SYSTEM", center, BigFont);
	DrawButton(SECOND_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y, "DISPLAY", center, BigFont);
	DrawButton(THIRD_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y, "CALIBRATION", center, BigFont);

	DrawButton(FIRST_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y, "GPS", center, BigFont);
	DrawButton(SECOND_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y, "TEST", center, BigFont);
	DrawButton(THIRD_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y, "TEST", center, BigFont);
}

void DrawDroneMenu()
{
	DrawBackButton();
	Screen.drawRoundRect(LEFT_DONGLE_LR_POSITION_START_X, LEFT_DONGLE_LR_POSITION_START_Y, LEFT_DONGLE_LR_POSITION_END_X, LEFT_DONGLE_LR_POSITION_END_Y);
	Screen.drawLine(LEFT_DONGLE_LR_POSITION_START_X + 100, LEFT_DONGLE_LR_POSITION_START_Y, LEFT_DONGLE_LR_POSITION_START_X + 100, LEFT_DONGLE_LR_POSITION_END_Y);

	Screen.drawRoundRect(LEFT_DONGLE_UD_POSITION_START_X, LEFT_DONGLE_UD_POSITION_START_Y, LEFT_DONGLE_UD_POSITION_END_X, LEFT_DONGLE_UD_POSITION_END_Y);
	Screen.drawLine(LEFT_DONGLE_UD_POSITION_START_X, LEFT_DONGLE_UD_POSITION_START_Y + 100, LEFT_DONGLE_UD_POSITION_END_X, LEFT_DONGLE_UD_POSITION_START_Y + 100);

	Screen.drawRoundRect(RIGHT_DONGLE_LR_POSITION_START_X, RIGHT_DONGLE_LR_POSITION_START_Y, RIGHT_DONGLE_LR_POSITION_END_X, RIGHT_DONGLE_LR_POSITION_END_Y);
	Screen.drawLine(RIGHT_DONGLE_LR_POSITION_START_X + 100, RIGHT_DONGLE_LR_POSITION_START_Y, RIGHT_DONGLE_LR_POSITION_START_X + 100, RIGHT_DONGLE_LR_POSITION_END_Y);

	Screen.drawRoundRect(RIGHT_DONGLE_UD_POSITION_START_X, RIGHT_DONGLE_UD_POSITION_START_Y, RIGHT_DONGLE_UD_POSITION_END_X, RIGHT_DONGLE_UD_POSITION_END_Y);
	Screen.drawLine(RIGHT_DONGLE_UD_POSITION_START_X, RIGHT_DONGLE_UD_POSITION_START_Y + 100, RIGHT_DONGLE_UD_POSITION_END_X, RIGHT_DONGLE_UD_POSITION_START_Y + 100);

	Screen.drawRoundRect(60, 50, 739, 330);
	DrawDrone();
}

void DrawBackButton()
{
	DrawButton(15, 420, 100, 450, "<- Back", center, SmallFont);
}

void DrawDrone()
{
	//Screen.drawBitmap();
}

void DrawDisplayMenu()
{
	DrawBackButton();
	Screen.setColor(0, 10, 255);

	Screen.fillRoundRect(15, 360, screenBacklight, 380);
	Screen.setColor(255, 255, 255);
	Screen.drawRoundRect(15, 360, 790, 380);

}

void DrawButton(int xBegin, int yBegin, int xEnd, int yEnd, String text, enum_text_position textPosition, uint8_t font[])
{
	Screen.setColor(0, 10, 255);
	Screen.fillRoundRect(xBegin, yBegin, xEnd, yEnd);
	Screen.setColor(VGA_WHITE);
	Screen.setBackColor(0, 10, 255);

	Screen.setFont(font);
	int xFont = Screen.getFontXsize();
	int yFont = Screen.getFontYsize();
	int textOffsetX, textOffsetY;
	if (font == BigFont)
	{
		textOffsetX = (text.length() * 16) / 2;
		textOffsetY = 8;
	}
	else
	{
		textOffsetX = (text.length() * 8) / 2;
		textOffsetY = 6;
	}

	if (textPosition == center)
	{
		xBegin = (((xEnd - xBegin) / 2) + xBegin) - textOffsetX;
		yBegin = (((yEnd - yBegin) / 2) + yBegin) - textOffsetY;
		Screen.print(text, xBegin, yBegin);

	}
	else if (textPosition == left)
	{
		Screen.print(text, xBegin, yBegin);
	}
	else if (textPosition == right)
	{
		Screen.print(text, xBegin, yBegin);
	}
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
	if ((y >= BACK_BUTTON_Y_BEGIN) && (y <= BACK_BUTTON_Y_END))
	{
		if ((x >= BACK_BUTTON_X_BEGIN) && (x <= BACK_BUTTON_X_END))
		{
			waitForIt(BACK_BUTTON_X_BEGIN, BACK_BUTTON_Y_BEGIN, BACK_BUTTON_X_END, BACK_BUTTON_Y_END);
			selectedMenu = main_menu;
		}
	}
	return selectedMenu;
}

enum_menu DisplayMenuButtonPressed(int x, int y, enum_menu menu)
{
	enum enum_menu selectedMenu = menu;
	if ((y >= BACK_BUTTON_Y_BEGIN) && (y <= BACK_BUTTON_Y_END))
	{
		if ((x >= BACK_BUTTON_X_BEGIN) && (x <= BACK_BUTTON_X_END))
		{
			waitForIt(BACK_BUTTON_X_BEGIN, BACK_BUTTON_Y_BEGIN, BACK_BUTTON_X_END, BACK_BUTTON_Y_END);
			selectedMenu = main_menu;
		}
	}
	else if((y >= 360) && (y <= 380))
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

		backlight = map(screenBacklight, 15, 790, 0, 255);

		analogWrite(8, backlight);
		Screen.setColor(0,0,0);
		Screen.fillRoundRect(screenBacklight, 361, 790, 379);
		Screen.setColor(0, 10, 255);		
		Screen.fillRoundRect(12, 361, screenBacklight + 3, 379);
		delay(5);
	}
}

#pragma endregion
