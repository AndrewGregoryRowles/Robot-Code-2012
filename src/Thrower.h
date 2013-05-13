#ifndef _THROWER_H_
#define _THROWER_H_

#include "WPILib.h"
#include "math.h"


//Joystick Assignments
#define JOYSTICK_THROWER     3 // throttle
#define JOYSTICK_ANGLE       2 // launch angle
#define JOYSTICK_BACK_SPEED  1 // kickback angle
#define JOYSTICK_BACK_ANGLE  4 // kickback throttle

#define JAGUAR_ID_THROWER		5
#define ENCODER_THROWER_A		4
#define ENCODER_THROWER_B		5
#define SWITCH_THROWER			6


#define BTN_MANUALMODE      14  //Button number 14

#define STAGE_0					0 // idle: waiting
#define STAGE_1					1 // Moving to pickup ball & calculating
#define STAGE_2					2 // accelerating to throw speed;
#define STAGE_3					3 // slowing down

#define MAX_LAUNCH_ANGLE       180
#define MIN_LAUNCH_ANGLE       0

class Thrower {
public:
	
	DigitalInput *ThrowerSenor;
	
	Thrower();

	bool Update(void);
	bool UpdateManual(void);
	float UpdateSpeed (void);
	float UpdatePower (void);
	double init(void);
	int getStage(void);
	float getTargetPower(void);
	float getSpeed(void);
	int getLaunchAngle(void);
	float getBackAngle(void);
	float getBackSpeed(void);
	bool IsTriggerPressed(void);
	bool IsStopPressed(void);
	bool IsManualMode(void);
	
	float ManageSpeedDown (void);
	float ManageSpeedUp (void);
	
	float ManageAngleUp (void);
	float ManageAngleDown (void);
	
	bool updateMotor(float POWER);
	
public:
	bool isAuto;
	
	float Power;
	float speed;
	float RPM;
	float lastSpeed;
	int   LastCount;
	int maxCount;
	int launchVariation;
	double LastTime;
	int Stage;
	int onCount;
	int launchAngle;

	int lastPowerButtonUp;
	int lastPowerButtonDown;

	int lastAngleButtonUp;
	int lastAngleButtonDown;
	
	
	Timer *ThrowerTimer;
	Timer *SpeedTimer
	Encoder *ThrowerEncoder;
	Jaguar *ThrowerMotor;
	Jaguar *ThrowerMotor2;
	Joystick *JoyKickback;
	Joystick *ThrowerStick;			// joystick 1 (tank drive left stick)
	Joystick *ThrowerStickAngle;
	Joystick *ThrowerStickBackAngle;
	
	
};

#endif
