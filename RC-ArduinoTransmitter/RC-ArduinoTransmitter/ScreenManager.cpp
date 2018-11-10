#include <UTFT.h>
#include <UTouch.h>
#include "ScreenManager.h"

UTFT Screen(SSD1963_800480, 38, 39, 40, 41);
UTouch  myTouch(43, 42, 44, 45, 46);
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
	myTouch.InitTouch();
	myTouch.setPrecision(PREC_MEDIUM);
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

	Screen.fillRoundRect(15, 35, 255, 100);
	Screen.fillRoundRect(270, 35, 520, 100);
	Screen.fillRoundRect(535, 35, 785, 100);

	Screen.fillRoundRect(15, 117, 255, 182);
	Screen.fillRoundRect(270, 117, 520, 182);
	Screen.fillRoundRect(535, 117, 785, 182);

	Screen.fillRoundRect(15, 199, 255, 264);
	Screen.fillRoundRect(270, 199, 520, 264);
	Screen.fillRoundRect(535, 199, 785, 264);

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





