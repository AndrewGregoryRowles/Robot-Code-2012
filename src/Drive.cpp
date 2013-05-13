#include "Drive.h"

Drive:: Drive()
	{
		// create robot drive base
		myRobot         = new RobotDrive(JAGUAR_LEFT, JAGUAR_RIGHT);
    	leftDriveStick  = new Joystick (JOYSTICK_LEFT);
	    rightDriveStick = new Joystick (JOYSTICK_RIGHT);
		//Encoders
		leftCount   = new Encoder(ID_LEFT_MOTOR_A, ID_LEFT_MOTOR_B);
		rightCount  = new Encoder(ID_RIGHT_MOTOR_A, ID_RIGHT_MOTOR_B);

	}

//----------------------------
// Reverse setting
//----------------------------
bool Drive :: IsDriveREV ()
    {
    // ON (Closed) = Reverse = IO returns 0
    return (dsEIO->GetDigital(DRIVE_DIRECTION) == 0);

    }
//----------------------------
// Slow sped setting
//----------------------------
bool Drive :: IsDriveSlow ()
{
    // ON (Closed) = Slow = IO returns 0
    return (dsEIO->GetDigital(DRIVE_SPEED) == 0);
}


//----------------------------
// AutoMode Init
//----------------------------
bool Drive :: InitAuto  ()
    {

    //Reset counters to 0
	leftCount->Reset();
	rightCount->Reset();

    //Start counters
	leftCount->Start();
	rightCount->Start();

    return true;
    }

bool Drive::Autonomous(int direction)
{
    //Set jaguars at SPEED_AUTO
	myRobot->TankDrive(direction*SPEED_AUTO, direction*SPEED_AUTO);
	return true;
}

bool Drive::InitFunction()
{
	leftCount->Reset();
	rightCount->Reset();
	leftCount->Start();
	rightCount->Start();
	return true;
}

//----------------------------
// TeleOp Update
//----------------------------
bool Drive :: Update  ()
    {

    //Get the joystick values
	//By default, the values start reversed
    leftSpeed  = -1.0 * leftDriveStick ->GetY();
    rightSpeed = -1.0 * rightDriveStick->GetY();

    //If in reverse, switch values and make negative
    if (IsDriveREV())
        {
        float val   = -1.0 * rightSpeed;
        rightSpeed  =- 1.0 * leftSpeed;
        leftSpeed   = val;
        }

    //If in slow mode, then reduce speed
    if (IsDriveSlow ())
        {
        rightSpeed *= SLOW_SPEED_SCALAR;
        leftSpeed  *= SLOW_SPEED_SCALAR;
        }

    myRobot->TankDrive (rightSpeed, leftSpeed);
    return true; //Always need to keep checking
    }


//----------------------------
// AutoMode Update
//----------------------------
bool Drive :: UpdateAuto  ()
    {

        // not implemented

    return true;
    }





