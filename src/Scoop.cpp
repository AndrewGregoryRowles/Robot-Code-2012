#include "Scoop.h"

extern DriverStationEnhancedIO *dsEIO;

int RollerState;
int State;

Scoop::Scoop() {
	RollerState = 0; // 1 = on
	State = IDLE; // 1 = DOWN, 2 = UP

	controller2 = new Joystick (JOYSTICK_CONTROLLER);
	controller = new Joystick (1);

	LeftMotor = new Relay (RELAY_LEFT_MOTOR);
	RightMotor = new Relay (RELAY_RIGHT_MOTOR);
	RollerMotor = new Relay(RELAY_ROLLER);

	UpSwitch = new DigitalInput (DIGITAL_IO_SCOOP_UP);
	DownSwitch = new DigitalInput (DIGITAL_IO_SCOOP_DOWN);
}

bool Scoop::Update() {
	//
	if (IsButtonRaised() && !IsScoopRaised()) {
		RaiseScoop();
	} else if (IsButtonLowered() && !IsScoopLowered() ) {
		LowerScoop();
	} else {
		StopScoop ();
	}

	SetRoller (IsRollerOn());

	return true;
}

bool Scoop :: IsScoopLowered (void) // check up switch
{
	// 2
	if (DownSwitch->Get()==0) return true;
	return false;
}

bool Scoop::IsScoopRaised(void) // check down switch
{
	// 1
	if (UpSwitch->Get() == 0)	return true;
	return false;
}

bool Scoop::IsButtonRaised(void) // checks button
{// 1
	if (controller->GetTrigger()) {
		//State = UP;
		return true;
	}
	return false;
}

bool Scoop::IsButtonLowered(void) // checks button (does same as above)
{
	if (controller2->GetTrigger()             ) {
		//State = DOWN;
		return true;
	}
	return false;
}

bool Scoop::IsRollerOn(void) // checks state
{
	// TODO make it check if power is applied to roller
	if (dsEIO->GetDigital(ROLLER_BUTTON) == 0) {
		RollerState = 1;
		return true;
	}
	RollerState = 0;
	return false;
}

//Raising requires reversing motors
bool Scoop::RaiseScoop(void) // raises scooper
{
	if (IsScoopRaised()) {
		return StopScoop();
	}
	LeftMotor->Set(Relay::kReverse);
	RightMotor->Set(Relay::kReverse);
	State = UP;
	return true;
}

bool Scoop::LowerScoop(void) // raises scooper
{
	if (IsScoopLowered()) {
		return StopScoop();
	}
	LeftMotor->Set(Relay::kForward);
	RightMotor->Set(Relay::kForward);
	State = DOWN;
	return true;
}

bool Scoop::StopScoop(void) // raises scooper
{
	LeftMotor->Set(Relay::kOff);
	RightMotor->Set(Relay::kOff);
	State = IDLE;
	return true;
}

bool Scoop::SetRoller(bool state) {
	if (state) {
		RollerMotor->Set(Relay::kForward);
	} else {
		RollerMotor->Set(Relay::kOff);
	}
	return true;
}

