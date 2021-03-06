#include "BatteryManager.h"
#include "GpsManager.h"
#include "VehicleManager.h"
#include "ScreenManager.h"
#include <UTouch.h>
#include <UTFT.h>

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

#pragma endregion

#pragma region Header

void PrintHeader(String text, int x)
{
	Screen.setColor(255, 255, 255);
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
	//Screen.setFont(SmallFont);
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

enum_menu ReadTouch(enum_menu currMenu)
{
	enum_menu menu = empty;
	if (TouchDataAvailable() > 0)
	{
		Touch.read();
		int x = Touch.getX();
		int y = Touch.getY();
		PrintFooter("X:" + String(x) + " Y:" + String(y), 30);
		if (currMenu == main_menu)
		{
			menu = MainMenuButtonPressed(x, y);
		}
		if (currMenu == drone)
		{
			menu = DroneMenuButtonPressed(x, y);
		}
		if (currMenu == display)
		{
			menu = DisplayMenuButtonPressed(x, y);
		}
	}
	else
	{
		
	}
	return menu;
}

void waitForIt(int x1, int y1, int x2, int y2)
{
	Screen.setColor(255, 0, 0);
	Screen.drawRoundRect(x1, y1, x2, y2);
	while (TouchDataAvailable() > 0) { }
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

void DrawProgressBar(int startX, int startY, int length, int debth, int value, enum_progress_bar_mode type, enum_orientation orientation)
{
	Screen.setColor(255, 255, 255);
	int xEnd = startX + length;
	int yEnd = startY + debth;
	
	if(orientation == landscape)
	{
		int endLocation;
		Screen.drawRoundRect(startX, startY, xEnd, yEnd);
		if(type == one_sided)
		{
			endLocation = map(value, 0, 100, startX, xEnd);
			Screen.fillRoundRect(startX, startY, endLocation, yEnd);
			Screen.setColor(0, 0, 0);
			Screen.fillRoundRect(endLocation, startY + 1, xEnd, yEnd - 1);
		}
		else if (type == two_sided)
		{
			Screen.drawLine(startX + (length / 2), startY, startX + (length / 2), startY + debth);
			if (value > 51)
			{
				endLocation = map(value, 52, 100, startX + (length / 2), xEnd);
				Screen.fillRoundRect(startX + (length / 2), startY, endLocation, yEnd);
				Screen.setColor(0, 0, 0);
				Screen.fillRoundRect(endLocation, startY + 1, xEnd, yEnd - 1);
			}
			else if (value < 49)
			{
				endLocation = map(value, 100, 48, startX + (length / 2), startX);
				Screen.fillRoundRect(startX + (length / 2), startY, endLocation, yEnd);
				Screen.setColor(0, 0, 0);
				Screen.fillRoundRect(endLocation, startY + 1, xEnd, yEnd - 1);
			}
			PrintFooter(String(value), 150);
		}
	}
	else
	{
		Screen.drawRoundRect(startY, startX, yEnd, xEnd);
		if(type == one_sided)
		{
			int endLocation = map(value, 100, 0, startX, xEnd);
			Screen.fillRoundRect(startY, endLocation, yEnd, xEnd);
			
			Screen.setColor(0, 0, 0);
			Screen.fillRoundRect(startY + 1, startY + 1, yEnd - 1, endLocation);
		}	
		//else if (type == two_sided)
		//{
		// int middleValue = 50;
		//	Screen.drawLine(startY, startX + (length / 2), startY + debth, startX + (length / 2));
		//	if (value > 51)
		//	{
		//		Screen.fillRoundRect(startX, startY, value, yEnd);
		//		Screen.setColor(0, 0, 0);
		//	}
		//	else if (value < 49)
		//	{
		//
		//	}
		//}
	}
}

void DrawBackButton()
{
	DrawButton(15, 420, 100, 450, "<- Back", center, SmallFont);
}

void DrawDrone()
{
	Screen.drawBitmap(295, 100, 100, 100, Drone, 2);
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
	Screen.setColor(255, 255, 255);
	Screen.drawRoundRect(xBegin, yBegin, xEnd, yEnd);

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

enum_menu MainMenuButtonPressed(int x, int y)
{
	enum_menu temp = empty;
	if ((y >= FIRST_ROW_MAIN_MENU_BEGIN_Y) && (y <= FIRST_ROW_MAIN_MENU_END_Y))
	{
		if ((x >= FIRST_COLUMN_MAIN_MENU_BEGIN_X) && (x <= FIRST_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(FIRST_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
			temp = drone;
		}
		else if ((x >= SECOND_COLUMN_MAIN_MENU_BEGIN_X) && (x <= SECOND_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(SECOND_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
			temp = plane;
		}
		else if ((x >= THIRD_COLUMN_MAIN_MENU_BEGIN_X) && (x <= THIRD_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(THIRD_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
			temp = car;
		}
	}

	else if ((y >= SECOND_ROW_MAIN_MENU_BEGIN_Y) && (y <= SECOND_ROW_MAIN_MENU_END_Y))
	{
		if ((x >= FIRST_COLUMN_MAIN_MENU_BEGIN_X) && (x <= FIRST_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(FIRST_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);
			temp = system_info;
		}
		else if ((x >= SECOND_COLUMN_MAIN_MENU_BEGIN_X) && (x <= SECOND_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(SECOND_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, SECOND_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);
			temp = display;
		}
		else if ((x >= THIRD_COLUMN_MAIN_MENU_BEGIN_X) && (x <= THIRD_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(THIRD_COLUMN_MAIN_MENU_BEGIN_X, SECOND_ROW_MAIN_MENU_BEGIN_Y, THIRD_COLUMN_MAIN_MENU_END_X, SECOND_ROW_MAIN_MENU_END_Y);
			temp = calibration;
		}
	}

	else if ((y >= THIRD_ROW_MAIN_MENU_BEGIN_Y) && (y <= THIRD_ROW_MAIN_MENU_END_Y))
	{
		if ((x >= FIRST_COLUMN_MAIN_MENU_BEGIN_X) && (x <= FIRST_COLUMN_MAIN_MENU_END_X))
		{
			waitForIt(FIRST_COLUMN_MAIN_MENU_BEGIN_X, THIRD_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, THIRD_ROW_MAIN_MENU_END_Y);
			temp = gps;
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
	return temp;
}

enum_menu DroneMenuButtonPressed(int x, int y)
{
	enum_menu temp = empty;
	if ((y >= BACK_BUTTON_Y_BEGIN) && (y <= BACK_BUTTON_Y_END))
	{
		if ((x >= BACK_BUTTON_X_BEGIN) && (x <= BACK_BUTTON_X_END))
		{
			waitForIt(BACK_BUTTON_X_BEGIN, BACK_BUTTON_Y_BEGIN, BACK_BUTTON_X_END, BACK_BUTTON_Y_END);
			temp = main_menu;
		}
	}
	return temp;
}

enum_menu DisplayMenuButtonPressed(int x, int y)
{
	enum_menu temp = empty;
	if ((y >= BACK_BUTTON_Y_BEGIN) && (y <= BACK_BUTTON_Y_END))
	{
		if ((x >= BACK_BUTTON_X_BEGIN) && (x <= BACK_BUTTON_X_END))
		{
			waitForIt(BACK_BUTTON_X_BEGIN, BACK_BUTTON_Y_BEGIN, BACK_BUTTON_X_END, BACK_BUTTON_Y_END);
			temp = main_menu;
		}
	}
	else if((y >= 360) && (y <= 380))
	{
		if ((x >= 15) && (x <= 790))
		{
			SetBrightness();
		}
	}
	return temp;
}

void SetBrightness()
{
	while (TouchDataAvailable() > 0)
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

int TouchDataAvailable()
{
	Touch.read();
	return Touch.getX() + Touch.getY();
}

#pragma endregion
