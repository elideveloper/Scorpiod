#include "SmartServo.h"

#ifdef DEBUG_MODE
#include <iostream>
#endif

SmartServo::SmartServo()
{
}

SmartServo::SmartServo(int max, int min, int neutral, int offset, Servo servo)
	: offset(offset), servo(servo)
{
	this->min = min + offset;
	this->max = max + offset;
	this->neutral = neutral + offset;
}

void SmartServo::reachAngle(int angle)
{
	angle += offset;
	if (angle < this->min) angle = this->min;
	else if (angle > this->max) angle = this->max;
#ifdef DEBUG_MODE
	printf("From reachAngle: angle = %d\n", angle);
#endif
	this->servo.write(angle);
}

void SmartServo::stayNeutral()
{
#ifdef DEBUG_MODE
	printf("From stayNeutral: this->neutral = %d\n", this->neutral);
#endif
	this->servo.write(this->neutral);
}

int SmartServo::getNeutral()
{
	return this->neutral - this->offset;
}
