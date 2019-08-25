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

	data.LeftX = analogRead(A1);
	data.LeftY = analogRead(A2);
	data.RightX = analogRead(A3);
	data.RightY = analogRead(A4);
	return data;
}