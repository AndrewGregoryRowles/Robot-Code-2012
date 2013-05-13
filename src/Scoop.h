#ifndef _SCOOP_H_
#define _SCOOP_H_

#define DIGITAL_IO_SCOOP_DOWN   8
#define DIGITAL_IO_SCOOP_UP     9

#define RELAY_RIGHT_MOTOR       1
#define RELAY_LEFT_MOTOR        2
#define RELAY_ROLLER            3

#define JOYSTICK_CONTROLLER     2

#define IDLE                    0
#define DOWN                    1
#define UP                      2

#define ROLLER_BUTTON           10

#include "WPILib.h"

class Scoop
{
	public:
		Scoop ();

		Relay *LeftMotor;
		Relay *RightMotor;
		Relay *RollerMotor;

		DigitalInput *DownSwitch;
		DigitalInput *UpSwitch;

		Joystick *controller;
		Joystick *controller2;

		bool Update (void);

		// Limit switches
		bool IsScoopLowered (void);
		bool IsScoopRaised (void);


		// User control
		// checks joystick button
		bool IsButtonRaised (void);
		bool IsButtonLowered (void);

		// check switch
		bool IsRollerOn (void);


		// Commands
		bool RaiseScoop (void);
		bool LowerScoop (void);
		bool StopScoop  (void);
		bool SetRoller (bool state); // true == on, false == off
};

#endif

