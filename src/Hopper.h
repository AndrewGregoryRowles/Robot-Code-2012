#ifndef _HOPPER_H_
#define _HOPPER_H_

// for limit switches
#define DIGITAL_IO_HOPPER_DOWN      7
#define DIGITAL_IO_BALL_IN_PLACE    14


// TODO get ports
#define SWITCH_NUMBER               13

#define RELAY_HOPPER                4

#include "WPILib.h"

class Hopper
{
public:
	Hopper();

	// Members
	Relay *HopperMotor;

	DigitalInput *UpSwitch;
	DigitalInput *DownSwitch;

	int Stage;

	// Member Functions

	bool Update(void);

	// Limit switches
	bool IsHopperDown (void);
	bool IsBallInPlace (void);

	// User Control
	bool IsHopperOn (void); // button in up position

	// Commands
	bool SetHopper (bool status); // true = on, false = off

};

#endif

