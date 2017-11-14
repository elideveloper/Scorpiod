#ifndef PAW_H
#define PAW_H
//#include "Arduino.h"
//#include <Servo.h>

#include "step_angles.h"
#include "utility.h"

class Paw {
public:
	Paw(Servo alpha, Servo phi, Servo psi);		// attach 3 servos
	//void setInitState();
	StepAngles* computeStepForward(int speed);
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