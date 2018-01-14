#include "paw.h"

#include <math.h>

#ifdef DEBUG_MODE
#include <iostream>
#endif

Paw::Paw()
{
}

// m b just receive pin numbers and attach servos inside constructor
Paw::Paw(int coxaOffset, int femurLen, int tibiaLen, int verticalOffset, SmartServo coxaServo, SmartServo femurServo, SmartServo tibiaServo)
	: coxaOffset(coxaOffset), femurLen(femurLen), tibiaLen(tibiaLen), currVerticalOffset(verticalOffset), coxaServo(coxaServo), femurServo(femurServo), tibiaServo(tibiaServo)
{}

void Paw::setNeutralState()
{
	double len = this->coxaOffset + sin(deg2Rad(this->femurServo.getNeutral())) * this->femurLen
		+ sin(deg2Rad(this->tibiaServo.getNeutral() - (90 - this->femurServo.getNeutral()))) * this->tibiaLen;
	printf("\nLength of leg: %f", len); 
	this->currPos = Vec2D(len * cos(deg2Rad(this->coxaServo.getNeutral())), len * sin(deg2Rad(this->coxaServo.getNeutral())));
	this->coxaServo.stayNeutral();
	this->femurServo.stayNeutral();
	this->tibiaServo.stayNeutral();
}

void Paw::move(Vec2D displacement, int verticalOffset)
{
	Vec2D newPos = this->currPos.add(displacement);
	this->reachPosition(newPos, verticalOffset);
}

void Paw::reachPosition(Vec2D pos, int verticalOffset)
{
	this->currPos.print();
	Vec2D newPos = pos;
#ifdef DEBUG_MODE
	newPos.print();
	printf("\nLength of new pos: %f", newPos.getLength());
#endif
	this->currPos = newPos;
	double coxaAngle = newPos.getAngle();
	newPos = newPos.sub(newPos.getScaled(this->coxaOffset));
#ifdef DEBUG_MODE
	newPos.print();
	printf("\nLength of new pos: %f", newPos.getLength());
#endif
	// compute femur and tibia angles from perpend view
	double x = newPos.getLength();
	double y = verticalOffset;
	double a = -2 * x;
	double b = -2 * y;
	double c = x * x + y * y - this->tibiaLen * this->tibiaLen + this->femurLen * this->femurLen;
	double x0 = -a * c / (a * a + b * b);
	double y0 = -b * c / (a * a + b * b);
	double d = this->femurLen * this->femurLen - c * c / (a * a + b * b);
	double mult = sqrt(d / (a * a + b * b));
	Vec2D femPos;
	double ay = y0 - a * mult;
	double by = y0 + a * mult;
	if (ay > by) femPos = Vec2D(x0 + b * mult, ay);
	else femPos = Vec2D(x0 - b * mult, by);
	double femAngle = femPos.getAngle();
	double tibAngle = Vec2D(x, y).sub(femPos).getAngle() + PI * 0.5 + (PI * 0.5 - femAngle);

	this->currVerticalOffset = verticalOffset;
#ifdef DEBUG_MODE
	printf("coxaAngle: %d, femAngle: %d, tibAngle: %d\n", rad2Deg(coxaAngle), rad2Deg(femAngle), rad2Deg(tibAngle));
#endif
	this->coxaServo.reachAngle(rad2Deg(coxaAngle));
	this->femurServo.reachAngle(rad2Deg(femAngle));
	this->tibiaServo.reachAngle(90 - rad2Deg(tibAngle));			// 90 - real tibia angle
}


// -------------------------------- OLD ---------------
//
//// speed = [-5; 5]
//// m b just receive values from Joystic and call function that returns angle of turn and speed - for arbitrary directions
//// arbitrary directions is combine of computeStepSideway() and computeStepForward() depending on direction angle
//StepAngles* Paw::computeStepForward(int joyX, int joyY)
//{
//	this->computeSpeedAndDirection(joyX, joyY);
//	if (this->speed == 0) return nullptr;
//	int speedAbs = abs(this->speed);
//
//	double stepSemiLength = speedAbs * 5.0;		// mm
//	double heightDelta = 50.0 / speedAbs;		// mm
//
//	double hyp0 = sqrt(this->femur * this->femur + this->tibia * this->tibia - 2 * cos(this->psi) * this->tibia * this->femur);
//	double pawHorizL0 = sqrt(hyp0 * hyp0 - this->bodyHeight * this->bodyHeight);
//	double pawHorizL1 = sqrt(pawHorizL0 * pawHorizL0 + stepSemiLength * stepSemiLength - 2 * pawHorizL0 * stepSemiLength * cos(this->alpha + this->dirAngle));	//!!! add dir angle to find L1 in right direction
//	double alphaDiff1 = acos((pawHorizL1 * pawHorizL1 + pawHorizL0 * pawHorizL0 - stepSemiLength * stepSemiLength) / (2 * pawHorizL1 * pawHorizL0));
//	double pawHorizL2 = sqrt(pawHorizL1 * pawHorizL1 + stepSemiLength * stepSemiLength - 2 * pawHorizL1 * stepSemiLength * cos(alphaDiff1 + this->alpha + this->dirAngle));//!!! add dir angle to find L1 in right direction
//	double alphaDiff2 = acos((pawHorizL1 * pawHorizL1 + pawHorizL2 * pawHorizL2 - stepSemiLength * stepSemiLength) / (2 * pawHorizL1 * pawHorizL2));
//	
//	// if speed < 0 then negative alpha
//	if (this->speed < 0) {
//		alphaDiff1 = -alphaDiff1;
//		alphaDiff2 = -alphaDiff2;
//	}
//
//	double hyp1 = sqrt(pawHorizL1 * pawHorizL1 + (this->bodyHeight - heightDelta) * (this->bodyHeight - heightDelta));
//	double psiDiff1 = acos((this->femur * this->femur + this->tibia * this->tibia - hyp1 * hyp1) / (2 * this->femur * this->tibia)) - this->psi;
//	double phiDiff1 = acos((hyp1 * hyp1 + this->femur * this->femur - this->tibia * this->tibia) / (2 * this->femur * hyp1)) +
//		asin(pawHorizL1 / hyp1) - this->phi;
//	double hyp2 = sqrt(pawHorizL2 * pawHorizL2 + this->bodyHeight * this->bodyHeight);
//	double psiDiff2 = acos((this->femur * this->femur + this->tibia * this->tibia - hyp2 * hyp2) / (2 * this->femur * this->tibia)) - psiDiff1 - this->psi;
//	double phiDiff2 = acos((hyp2 * hyp2 + this->femur * this->femur - this->tibia * this->tibia) / (2 * this->femur * hyp2)) +
//		asin(pawHorizL2 / hyp2) - this->phi - phiDiff1;
//
//	StepAngles* stepAngles = new StepAngles(20);
//	double alphaStep = alphaDiff1 / 10.0;
//	double phiStep = phiDiff1 / 10.0;
//	double psiStep = psiDiff1 / 10.0;
//	stepAngles->alpha[0] = alphaStep + this->alpha;
//	stepAngles->phi[0] = phiStep + this->phi;
//	stepAngles->psi[0] = psiStep + this->psi;
//	printf("alpha=%.2f; phi=%.2f; psi=%.2f\n", rad2Deg(stepAngles->alpha[0]), rad2Deg(stepAngles->phi[0]), rad2Deg(stepAngles->psi[0]));
//	for (register int i = 1; i < 10; i++) {
//		stepAngles->alpha[i] = alphaStep + stepAngles->alpha[i - 1];
//		stepAngles->phi[i] = phiStep + stepAngles->phi[i - 1];
//		stepAngles->psi[i] = psiStep + stepAngles->psi[i - 1];
//		printf("alpha=%.2f; phi=%.2f; psi=%.2f\n", rad2Deg(stepAngles->alpha[i]), rad2Deg(stepAngles->phi[i]), rad2Deg(stepAngles->psi[i]));
//	}
//
//	alphaStep = alphaDiff2 / 10.0;
//	phiStep = phiDiff2 / 10.0;
//	psiStep = psiDiff2 / 10.0;
//	stepAngles->alpha[10] = alphaStep + stepAngles->alpha[9];
//	stepAngles->phi[10] = phiStep + stepAngles->phi[9];
//	stepAngles->psi[10] = psiStep + stepAngles->psi[9];
//	printf("alpha=%.2f; phi=%.2f; psi=%.2f\n", rad2Deg(stepAngles->alpha[10]), rad2Deg(stepAngles->phi[10]), rad2Deg(stepAngles->psi[10]));
//	for (register int i = 11; i < 20; i++) {
//		stepAngles->alpha[i] = alphaStep + stepAngles->alpha[i - 1];
//		stepAngles->phi[i] = phiStep + stepAngles->phi[i - 1];
//		stepAngles->psi[i] = psiStep + stepAngles->psi[i - 1];
//		printf("alpha=%.2f; phi=%.2f; psi=%.2f\n", rad2Deg(stepAngles->alpha[i]), rad2Deg(stepAngles->phi[i]), rad2Deg(stepAngles->psi[i]));
//	}
//
//	return stepAngles;
//}
//
//void Paw::computeSpeedAndDirection(int joyX, int joyY)
//{
//	// correct values for real joystick or check internal values and do not consider little deviations
//	int x = joyX - 511;
//	int y = joyY - 511;
//	double bound = deg2Rad(10);
//	double realDirAngle = atan((double)x / y);
//	printf("real_dir_angle=%.2f;\n", rad2Deg(realDirAngle));
//
//	// very little deviations does not consider
//	if (realDirAngle < bound - PI / 2.0) { this->dirAngle = -PI / 2.0; this->speed = abs(x) / 100; }
//	else if (realDirAngle > PI / 2.0 - bound) { this->dirAngle = PI / 2.0; this->speed = abs(x) / 100; }
//	else if (abs(realDirAngle) < bound) { this->dirAngle = 0.0; this->speed = y / 100; }
//	else { 
//		this->dirAngle = realDirAngle; 
//		this->speed = sqrt(x * x + y * y) / 150;
//		if (y < 0) this->speed = -this->speed;
//	}
//
//	printf("dir_angle=%.2f; speed=%d;\n", rad2Deg(this->dirAngle), this->speed);
//}
