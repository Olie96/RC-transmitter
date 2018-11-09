#include <UTFT.h>
#include <UTouch.h>

#define LOW_PRIORITY 200
#define MEDIUM_PRIORITY 100

UTFT Screen(SSD1963_800480, 38, 39, 40, 41);  
UTouch  myTouch(43, 42, 44, 45, 46); 
extern uint8_t BigFont[];

int x, y;
int lowPriority, mediumPriority;
// config
void SetUpPinModes();
void SetUpLcdConfig();
void LoadOperatingSystem();
void InitializeMainMenu();
// header
void InitializeHeader();
void ShowBatteryPercentage();
void ShowGpsStrength();
void ShowVehicleStatus();

// footer
void InitializeFooter();

void setup()
{
	SetUpPinModes();
	SetUpLcdConfig();
	LoadOperatingSystem();
	InitializeMainMenu();
}

void loop()
{
	if (mediumPriority > MEDIUM_PRIORITY)
	{
		mediumPriority = 0;
	}
	if (lowPriority > LOW_PRIORITY)
	{
		ShowGpsStrength();
		ShowBatteryPercentage();
		ShowVehicleStatus();
		lowPriority = 0;
	}

	mediumPriority++;
	lowPriority++;
}


void LoadOperatingSystem()
{
	Screen.print("Loading operating system", 210, 215);
	Screen.setColor(255, 255, 255);
	for (x = 10; x <= 790; x++)
	{
		Screen.fillRoundRect(10, 235, x, 245);
	}
	delay(500);
	Screen.clrScr();
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

void InitializeMainMenu()
{
	InitializeHeader();
	InitializeFooter();
	ShowGpsStrength();
	ShowBatteryPercentage();
	ShowVehicleStatus();
}

// header

void InitializeHeader()
{
	Screen.setColor(0, 10, 255);
	Screen.setBackColor(0, 10, 255);
	Screen.fillRoundRect(0, 0, 799, 18);
	Screen.setColor(255, 255, 255);
}

void ShowBatteryPercentage()
{
	int batteryRead = analogRead(A0);
	batteryRead = map(batteryRead, 800,1023,0,100);
	Screen.print(String(batteryRead) + "%", 700,1);
	Screen.setColor(0, 200, 0);
	Screen.fillRoundRect(755, 4, 770, 12);
	Screen.fillRoundRect(760, 1, 798, 15);
	Screen.setColor(255, 255, 255);
}

void ShowGpsStrength()
{
	Screen.print("GPS", 580, 1);
	Screen.print("68%", 635, 1);
}

void ShowVehicleStatus()
{
	Screen.print("Status:", 10, 1);
	Screen.print("Ready", 125, 1);
}

// footer

void InitializeFooter()
{
	Screen.setColor(0, 10, 255);
	Screen.setBackColor(0, 10, 255);
	Screen.fillRoundRect(0, 462, 800, 480);
	Screen.setColor(255, 255, 255);
}
