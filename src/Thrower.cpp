#include "Thrower.h"

Thrower::Thrower() {
	Stage = 0;
	Power = 0.5;
	isAuto = false;
	ThrowerEncoder = new Encoder (ENCODER_THROWER_A, ENCODER_THROWER_B);

	ThrowerMotor = new Jaguar (JAGUAR_ID_THROWER);
	ThrowerMotor2 = new Jaguar (6);

	ThrowerStick = new Joystick (JOYSTICK_THROWER);
	ThrowerStickAngle = new Joystick (JOYSTICK_ANGLE);
	ThrowerStickBackAngle = new Joystick (JOYSTICK_BACK_ANGLE);
	JoyKickback = new Joystick (JOYSTICK_BACK_SPEED);

	SpeedTimer = new Timer();
	SpeedTimer->Reset();
	SpeedTimer->Start();

    ThrowerSenor = new DigitalInput (6);

    LastCount = 0;
    LastTime  = 0;
    RPM       = 0;
    launchVariation = 0;
    launchAngle = 150;

    lastPowerButtonDown = 0;
    lastPowerButtonUp = 0;

    lastAngleButtonUp = 0;
    lastAngleButtonDown = 0;

    ThrowerEncoder->Start();
 }

bool Thrower::UpdateManual ()
    {
	Stage = 0;
	float power = -ThrowerStick->GetY();

	if (!ThrowerStick->GetTrigger())
		{
		ThrowerEncoder->Reset();
		ThrowerEncoder->Start();
		LastCount = 0;
		power = 0;
		SpeedTimer->Reset();
		SpeedTimer->Start();
		LastTime  = 0;
		}
	UpdateSpeed();
	updateMotor(power);
	Stage = 0;
	return true;
    }

bool Thrower::Update()
    {
	ManageSpeedDown();
	ManageSpeedUp();
	ManageAngleUp();
	ManageAngleDown();

	if (ThrowerStick->GetRawButton(10)) launchAngle -= 5;
	if (ThrowerStick->GetRawButton(11)) launchAngle += 5;

	if (IsManualMode()) {return UpdateManual ();}
	if (ThrowerStick->GetRawButton(2)) ThrowerEncoder->Reset();

	float power = 0;
	if (Stage == 0)
		{
		//Power = GetSpeed();
		ThrowerEncoder->Reset();
		ThrowerEncoder->Start();
		if (ThrowerStick->GetTrigger()) {
			Stage = 1;

			SpeedTimer->Reset();
			SpeedTimer->Start();
			LastTime  = SpeedTimer->Get();
			lastSpeed = ThrowerEncoder->Get();
			LastCount = (int)lastSpeed;
	        RPM       = 0;
		}
	if (Stage == 1)
	   {
		Stage = 2;
		if (ThrowerEncoder->Get() < getBackAngle()) Stage = 2;
	   }
	if (Stage == 2) { // acceleration
		UpdateSpeed();
		if (ThrowerEncoder->Get() >= getLaunchAngle()) Stage = 3;
	}
	if (Stage == 3) { // return to inital position
		if (ThrowerEncoder->Get() <= -3)
			Stage = 0;
	}

	power = UpdatePower();
	updateMotor(power);

	return true;
}

float Thrower::UpdatePower () {
	float power = 0.0;
	if (Stage == 0) {
		power = 0.0;
	}
	if (Stage == 1) {
		power = getBackSpeed();
	}
	if (Stage == 2) {
		power = GetSpeed();
	}
	if (Stage == 3) {
		power = .15;
		if (ThrowerEncoder->Get() < 5)
			power = .08;
	}
	return power;
}

/**
* Calculates and updates RPM counter
*/
float Thrower::UpdateSpeed(void)
    {
	int  CurrentCount  = ThrowerEncoder->Get();
	double CurrentTime = SpeedTimer->Get();

	//difference = change in Encoder counts since last pass
	int    DeltaCount = CurrentCount - LastCount;
	double DeltaTime = CurrentTime - LastTime;

	if (DeltaTime <= 0) {RPM =0 ; return RPM;}

	double rps = (DeltaCount / DeltaTime ) /360.0;


	//scale to minutes
	float newrpm = rps * 60;

	LastCount = CurrentCount;
	LastTime  = CurrentTime;
	RPM       = (2.0 * RPM + newrpm) / 3.0;

	return RPM;
    }



int Thrower::getStage() {
	return Stage;
}

float Thrower::getTargetPower() {
	return -ThrowerStick->GetThrottle();
}

float Thrower::getSpeed() {
	return -Power;
}

float Thrower::ManageSpeedUp () {
	if (lastPowerButtonUp != 0  && ThrowerStick->GetRawButton(6) == 0)
			Power -= .05;
	lastPowerButtonUp = ThrowerStick->GetRawButton(6);
	return Power;
}

float Thrower::ManageSpeedDown () {
	if (lastPowerButtonDown != 0 && ThrowerStick->GetRawButton(7) == 0)
			Power += .05;
	lastPowerButtonDown = ThrowerStick->GetRawButton(7);
	return Power;
}

float Thrower::ManageAngleUp () {
	if (lastAngleButtonUp != 0 && ThrowerStick->GetRawButton(11) == 0)
		launchAngle += 5;
	lastAngleButtonUp = ThrowerStick->GetRawButton(11);
	return launchAngle;
}

float Thrower::ManageAngleDown () {
	if (lastAngleButtonDown != 0 && ThrowerStick->GetRawButton(10) == 0)
		launchAngle -= 5;
	lastAngleButtonDown =ThrowerStick->GetRawButton(10);
	return launchAngle;
}

double Thrower::init() {
	speed = 3.0;
	LastCount = 0;

	return speed;
}

// If button is Off position, then in Manual Mode
// Off = High (1)
bool Thrower::IsManualMode() {
	  return (dsEIO->GetDigital(BTN_MANUALMODE) == 0);
}

bool Thrower::IsTriggerPressed() {
	if (ThrowerStick->GetTrigger())
		return true;
	else if (isAuto)
		return true;
	return false;
}

bool Thrower::IsStopPressed() {
	if (ThrowerStick->GetRawButton(6))
		return true;
	return false;
}

int Thrower::getLaunchAngle () {
	return launchAngle;
}

/**
* Old artifact for when the thrower used kickback first
*/
float Thrower::getBackAngle () {
	return 0;
}

/**
* Old artifact for when the thrower used kickback first
*/
float Thrower::getBackSpeed () {
	float p = -((JoyKickback->GetThrottle()-1.00)/2);

	return p;
}

bool Thrower::updateMotor (float POWER) {
	ThrowerMotor->Set(POWER);
	ThrowerMotor2->Set(POWER);
	return true;
}

