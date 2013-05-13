#include "DefaultRobot.h"

#define DEF_ROBOT_VERSION  2012.35

//35 -- Added Scoop & Hopper
//34 -- Changed release angle range from 90-160 to 110-180
//33 -- Adjusted calculation for RPM
//26 -- Changed Screen from Rotate Counts to Encoder->Get
//24 -- Changes in Field
//--------------------
// Refer to _Revision.txt for complete revision history


//These are declared globally to be available to all classes
class DefaultRobot *MainRobot= NULL;
DriverStationLCD *dsLCD;
float RPM = 0;

DefaultRobot::DefaultRobot(void) {

	// creates the driver station instances
	ds = DriverStation::GetInstance();
	dsEIO = &DriverStation::GetInstance()->GetEnhancedIO();
	dsLCD = DriverStationLCD::GetInstance();

	//creates the Drive from Drive.h
	drive = new Drive();
	thrower = new Thrower();
	scoop = new Scoop();
	hopper = new Hopper();

	//Set default stage to 0
	Stage = 0;

	//Update the motors at least every 100ms.
	GetWatchdog().SetExpiration(0.1);

	//drive->myRobot->SetExpiration(0.1);
	thrower->ThrowerMotor->SetExpiration(0.1);
}
// --------------------------------------AUTONOMOUS-------------------------------------- //
/**
* Autonomous Mode
*  - The robot shots 2 basketballs without user input
*
*/
void DefaultRobot::Autonomous(void) {
	if (IsAutonomous()) {
		GetWatchdog().SetEnabled(false);

		// sets and updates display
		dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Autonomus");
		dsLCD->UpdateLCD();

		// sets thrower mode to autonomous
		thrower->isAuto = true;

		// throws ball
		thrower->Update();

		// waits 5 seconds
		Wait (5);

		// shoots another ball
		thrower->Update();

		thrower->isAuto = false;
		Wait(0.005);
	}
}

// --------------------------------------OPERATOR CONTROL----------------------------- //
/**
* the operator control function
*  - when the robot is user controlled
*  - Updates component stages
*  - Updates LCD
*/
void DefaultRobot::OperatorControl(void) {
	GetWatchdog().SetEnabled(false);


	while (IsOperatorControl()) {
		thrower->isAuto = false;
		ManageLCD ();
		dsLCD->UpdateLCD();

		GetWatchdog().Feed();

		drive->Update();
		thrower->Update();
		scoop->Update();
		hopper->Update();

		Wait(0.01); // wait for a motor update time
	}
}

/**
* Prints data to LCD
*
*/
void DefaultRobot::ManageLCD (void) {
	// prints angle the thrower arm is at (~0 = rest)
	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Encoder:%5d", thrower->ThrowerEncoder->Get());

	if (thrower->IsManualMode())
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Throttle = %0.2f", -thrower->ThrowerStick->GetY());
		else
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Throttle = %0.2f", -thrower->GetSpeed());

	// prints the set launch angle
	dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Launch Angle = %0.2f", thrower->getLaunchAngle());

	// Prints the stage of the thrower
	dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Stage = %0.2f", thrower->getStage());
}

START_ROBOT_CLASS(DefaultRobot)
;

