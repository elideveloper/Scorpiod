#ifndef PAW_H
#define PAW_H
//#include "Arduino.h"
//#include <Servo.h>

#include "step_angles.h"
#include "utility.h"

// paw receive type of paw to init starting position
class Paw {
public:
	Paw(Servo alpha, Servo phi, Servo psi);		// attach 3 servos
	//void setInitState();
	// func that returns speed and angle from Joystic values: x, y
	StepAngles* computeStepForward(int speed);			// forward and backward
	// StepAngles* computeStepSideway(int speed);		// crab lef-right
private:
	double femur;
	double tibia;
	double bodyHeight;
	double alpha;
	double phi;
	double psi;
	Servo servoAlpha;
	Servo servoPhi;
	Servo servoPsi;
};

#endif