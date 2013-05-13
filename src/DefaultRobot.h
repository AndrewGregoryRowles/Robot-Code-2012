#ifndef _DEFAULTROBOT_H_
#define _DEFAULTROBOT_H_
//

#include "WPILib.h"
#include "Drive.h"
#include "Thrower.h"
#include "Hopper.h"
#include "Scoop.h"


class DefaultRobot : public SimpleRobot
{
	// driver station object
	DriverStation *ds;					
	DriverStationLCD *dsLCD;

	
	// TESTING ONLY digital input objects
	DigitalInput *checkOne;
	DigitalInput *checkTwo;
	

	
	//Drive Mode
	Drive *drive;
	Thrower *thrower;
	Hopper *hopper;
	Scoop  *scoop;
	
	enum								// Driver Station jumpers to control program operation
	{ ARCADE_MODE = 1,					// Tank/Arcade jumper is on DS Input 1 (Jumper present is arcade)
	  ENABLE_AUTONOMOUS = 2,			// Autonomous/Teleop jumper is on DS Input 2 (Jumper present is autonomous)
	} jumpers;	                            

public:
	
	// variables
	int   Stage;                   		// Current Stage
	
	DefaultRobot(void);
	
	virtual void  Autonomous (void);
	virtual void  OperatorControl  (void);
	void ManageLCD (void);
	
};

void sendIOPortData(void);
void sendVisionData(void);


#endif

