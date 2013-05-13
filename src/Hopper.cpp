#include "Hopper.h"

Hopper :: Hopper () 
{
	// set relay
	HopperMotor = new Relay (RELAY_HOPPER);
	
	UpSwitch = new DigitalInput (DIGITAL_IO_BALL_IN_PLACE);
	DownSwitch = new DigitalInput (DIGITAL_IO_HOPPER_DOWN);
	
	Stage = 0; 
}
// true == on/Up

bool Hopper :: Update () 
{
	
	bool Action = true;

	if (!IsHopperOn () && Stage == 1 && IsHopperDown())
		Action = false;
	
	if (!IsHopperOn () && Stage == 0)
		Action = false;
	
	SetHopper (Action);
	
	return true;
}

bool Hopper :: IsHopperDown () 
{
	if (DownSwitch->Get() != 0)
		return true;
	return false;
}

bool Hopper :: IsBallInPlace () 
{
	//if (UpSwitch->Get() != 0)
	//	return true;
	return false;
}

bool Hopper :: IsHopperOn () // control
{		
	if (dsEIO->GetDigital(SWITCH_NUMBER) == 0) 
		return true;
	else
		return false;
}

bool Hopper :: SetHopper (bool status) // true = on/UP, false = off/DOWN
{
	if (status) {
		Stage = 1;
		HopperMotor->Set(Relay::kForward);
	} else {
		Stage = 0;
		HopperMotor->Set(Relay::kOff);
	}
	return true;
}
