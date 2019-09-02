// 
// 
// 

#include "VehicleManager.h"

String GetVehicleStatus()
{
	return "Ready";
}

DongleData ReadDongleValues()
{
	DongleData data;
	data.LeftX = map(analogRead(A0), 130, 880, 0, 255);
	data.LeftY = map(analogRead(A1), 130, 880, 0, 255);
	data.RightX = map(analogRead(A2), 130, 880, 0, 255);
	data.RightY = map(analogRead(A3), 130, 880, 0, 255);

	if (data.LeftX > 255)
		data.LeftX = 255;
	if (data.LeftX < 0)
		data.LeftX = 0;

	if (data.LeftY > 255)
		data.LeftY = 255;
	if (data.LeftY < 0)
		data.LeftY = 0;

	if (data.RightX > 255)
		data.RightX = 255;
	if (data.RightX < 0)
		data.RightX = 0;

	if (data.RightY > 255)
		data.RightY = 255;
	if (data.RightY < 0)
		data.RightY = 0;

	return data;
}