#ifndef PAW_H
#define PAW_H

#include "utility.h"
#include "SmartServo.h"
#include "Vec2D.h"

#ifndef DEBUG_MODE
#include "Arduino.h"
#include <Servo.h>
#endif

// paw receive all angles for servos to init starting position
class Paw {
private:
	int coxaOffset;			// величина на которую выступает точка вращения femur от точки coxa
	int femurLen;
	int tibiaLen;
	int currVerticalOffset;	// величина на которую приподнято тело, или разница между высотой coxa и конца tibia (отрицательное значение для приподнятого тела)
	Vec2D currPos;
	/*double bodyHeight;
	double alpha;
	double phi;
	double psi;*/
	SmartServo coxaServo;
	SmartServo femurServo;
	SmartServo tibiaServo;
	//int speed;
	//double dirAngle;
	//void computeSpeedAndDirection(int joyX, int joyY);
public:
	Paw();
	Paw(int coxaOffset, int femurLen, int tibiaLen, int verticalOffset, SmartServo coxaServo, SmartServo femurServo, SmartServo tibiaServo);
	void setNeutralState();
	void reachPosition(Vec2D pos, int verticalOffset);
	void move(Vec2D displacement, int verticalOffset);
	
	
	//void setInitState();
	// func that returns speed and angle from Joystic values: x, y
	//StepAngles* computeStepForward(int joyX, int joyY);			// forward and backward
																// StepAngles* computeStepSideway(int speed);		// crab lef-right
};

#endif