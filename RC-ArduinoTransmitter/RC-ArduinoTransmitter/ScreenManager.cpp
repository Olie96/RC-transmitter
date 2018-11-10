#include <UTFT.h>
#include <UTouch.h>
#include "ScreenManager.h"

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

UTFT Screen(SSD1963_800480, 38, 39, 40, 41);
UTouch  Touch(43, 42, 44, 45, 46);
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

void LoadOperatingSystem()
{
	Screen.print("Loading operating system", 210, 215);
	Screen.setColor(255, 255, 255);
	for (int x = 10; x <= 790; x++)
	{
		Screen.fillRoundRect(10, 235, x, 240);
	}

	delay(500);
	Screen.clrScr();
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
	Screen.setFont(SmallFont);
	InitializeHeader();
	InitializeFooter();
	ShowGpsStrength();
	ShowBatteryPercentage();
	ShowVehicleStatus();
	DrawMainButtons();
}

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

void InitializeHeader()
{
	Screen.setColor(0, 10, 255);
	Screen.setBackColor(0, 10, 255);
	Screen.fillRoundRect(0, 0, 799, 18);
	Screen.setColor(255, 255, 255);
}

void ShowBatteryPercentage()
{
	Screen.setFont(SmallFont);
	int batteryRead = analogRead(A0);
	batteryRead = map(batteryRead, 800, 1023, 0, 100);
	Screen.print(String(batteryRead) + "%", 720, 3);
	Screen.setColor(0, 200, 0);
	Screen.fillRoundRect(755, 4, 770, 12);
	Screen.fillRoundRect(760, 1, 798, 15);
	Screen.setColor(255, 255, 255);
}

void ShowGpsStrength()
{
	Screen.setFont(SmallFont);
	Screen.print("GPS", 650, 3);
	Screen.print("68%", 680, 3);
}

void ShowVehicleStatus()
{
	Screen.setFont(SmallFont);
	Screen.print("Status:", 10, 3);
	Screen.print("Ready", 75, 3);
}

void InitializeFooter()
{
	Screen.setColor(0, 10, 255);
	Screen.setBackColor(0, 10, 255);
	Screen.fillRoundRect(0, 462, 800, 480);
	Screen.setColor(255, 255, 255);
}

void ReadTouch()
{
	if (Touch.dataAvailable())
	{
		Touch.read();
		int x = Touch.getX();
		int y = Touch.getY();
		Screen.print("X:" + String(x) + " Y:" + String(y), 30, 465);
		if ((y >= 45) && (y <= 100))
		{
			if ((x >= 20) && (x <= 255))
			{
				waitForIt(FIRST_COLUMN_MAIN_MENU_BEGIN_X, FIRST_ROW_MAIN_MENU_BEGIN_Y, FIRST_COLUMN_MAIN_MENU_END_X, FIRST_ROW_MAIN_MENU_END_Y);
			}
		}
	}
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

