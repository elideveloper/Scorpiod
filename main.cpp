#include <iostream>
#include <math.h>

#include "paw.h"

const int A_LEG_COXA_NEUTRAL_ANGLE = 45;
const int A_LEG_FEMUR_NEUTRAL_ANGLE = 60;
const int A_LEG_TIBIA_NEUTRAL_ANGLE = 30;

// Servo class reimplement Servo including possible range
int main() {

	//computeAngles(4.0);

	SmartServo coxsServo(MAX_SERVO_ANGLE, MIN_SERVO_ANGLE, A_LEG_COXA_NEUTRAL_ANGLE, A_LEG_COXA_OFFSET, Servo());
	SmartServo femurServo(MAX_SERVO_ANGLE, MIN_SERVO_ANGLE, A_LEG_FEMUR_NEUTRAL_ANGLE, A_LEG_FEMUR_OFFSET, Servo());
	SmartServo tibiaServo(MAX_SERVO_ANGLE, MIN_SERVO_ANGLE, A_LEG_TIBIA_NEUTRAL_ANGLE, A_LEG_TIBIA_OFFSET, Servo());

	Paw paw(COXA_OFFSET, FEMUR_LEN, TIBIA_LEN, VERTICAL_OFFSET, coxsServo, femurServo, tibiaServo);
	//paw.setNeutralState();
	paw.reachPosition(Vec2D(80.0, 80.0), VERTICAL_OFFSET);
	paw.reachPosition(Vec2D(80.0, 120.0), VERTICAL_OFFSET);
	paw.reachPosition(Vec2D(80.0, 40.0), VERTICAL_OFFSET);

	system("pause");
	return 0;
}