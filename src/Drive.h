#ifndef _DRIVE_H_
#define _DRIVE_H_



//Driver Station Digital In
#define DRIVE_SPEED     5  //SLOW == 0 (Button Closed)
#define DRIVE_DIRECTION	7  //REV  == 0 (Button Closed)

#define SLOW_SPEED_SCALAR  0.25  //Scalar to adjust when in slow mode
#define SPEED_AUTO         0.25    //Speed to use for autonomous mode


#define AUTO_DISTANCE     10000  //Number of counts to travel in auto mode


//Jaguar assignments
#define JAGUAR_LEFT     1
#define JAGUAR_RIGHT    2


//Joystick Assignments
#define JOYSTICK_LEFT     1
#define JOYSTICK_RIGHT    2

//Encoders
#define ID_LEFT_MOTOR_A			10
#define ID_LEFT_MOTOR_B			11
#define ID_RIGHT_MOTOR_A		12
#define ID_RIGHT_MOTOR_B		13



#include "WPILib.h"

class Drive
{
public:
	//Current speed settings.  These can be negative if in reverse mode
    float   leftSpeed;
    float   rightSpeed;


    // robot drive system object
	RobotDrive *myRobot;

	// joystick objects
	Joystick *leftDriveStick;			// joystick 1 (tank drive left stick)
	Joystick *rightDriveStick;			// joystick 2 (tank drive right stick / arcade drive stick)

public:

	// encoders
	Encoder *leftCount;
	Encoder *rightCount;




public:

	Drive ();

	//Simplified status handlers
	bool IsDriveREV   ();
	bool IsDriveSlow  ();

    //Initialization
    bool InitAuto     ();
    bool InitFunction ();
    bool Autonomous (int direction);

    bool Update       (); //Update drive speeds during teleop
    bool UpdateAuto   (); //Update during autonomous modes


};


#endif

