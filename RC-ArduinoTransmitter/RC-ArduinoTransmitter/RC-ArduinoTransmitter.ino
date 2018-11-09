#include <UTFT.h>
#include <UTouch.h>

UTFT Screen(SSD1963_800480, 38, 39, 40, 41);  
UTouch  myTouch(43, 42, 44, 45, 46); 
extern uint8_t BigFont[];

int x, y;
void SetUpLcdConfig();
void LoadOperatingSystem();
void SetMainMenu();
String CalcutateBatteryPercentage();
void SetUpPinModes();

void setup()
{
	SetUpLcdConfig();
	LoadOperatingSystem();
	SetMainMenu();
}

void loop()
{
	//while (true)
	//{
	//	if (myTouch.dataAvailable())
	//	{
	//		myTouch.read();
	//		x = myTouch.getX();
	//		y = myTouch.getY();
	//
	//		if ((y >= 10) && (y <= 60))  // Upper row
	//		{
	//			if ((x >= 10) && (x <= 60))  // Button: 1
	//			{
	//				//waitForIt(10, 10, 60, 60);
	//				//updateStr('1');
	//			}	//
	//			
	//		}
	//	}
	//}
}

void SetUpPinModes()
{
	pinMode(8, OUTPUT);
	digitalWrite(8, HIGH);
	pinMode(A0, INPUT);
}


void SetUpLcdConfig()
{
	Screen.InitLCD();
	Screen.clrScr();
	myTouch.InitTouch();
	myTouch.setPrecision(PREC_MEDIUM);
	Screen.setFont(BigFont);
}

void LoadOperatingSystem()
{
	Screen.print("Loading operating system", 210, 215);
	Screen.setColor(0, 0, 255);
	for (x = 10; x <= 790; x++)
	{
		Screen.fillRoundRect(10, 235, x, 245);
		//Screen.setColor(255, 255, 255);
	}
	delay(500);
	Screen.clrScr();
	//	Screen.print("0", 267, 87);
	//	Screen.setColor(0, 0, 255);
	//	Screen.fillRoundRect(10, 130, 150, 180);
	//	Screen.setColor(255, 255, 255);
	//	Screen.drawRoundRect(10, 130, 150, 180);
	//	Screen.print("Clear", 40, 147);
	//	Screen.setColor(0, 0, 255);
	//	Screen.fillRoundRect(160, 130, 300, 180);
	//	Screen.setColor(255, 255, 255);
	//	Screen.drawRoundRect(160, 130, 300, 180);
	//	Screen.print("Enter", 190, 147);
	//	Screen.setBackColor(0, 0, 0);
}

void SetMainMenu()
{
	//Screen.print(CalcutateBatteryPercentage() + " V", 650, 1);

}

String CalcutateBatteryPercentage()
{
	int batteryRead = analogRead(A0);

	return String(batteryRead);
}