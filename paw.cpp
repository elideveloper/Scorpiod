#include "paw.h"

#include <math.h>
#include <iostream>


// m b just receive pin numbers and attach servos inside constructor
Paw::Paw(Servo alpha, Servo phi, Servo psi) : servoAlpha(alpha), servoPhi(phi), servoPsi(psi)
{
	// set initial angles
	this->femur = femur = 120.0;
	this->tibia = 100.0;
	this->bodyHeight = 60.0;
	this->alpha = degreeToRad(90);
	this->phi = degreeToRad(120);
	this->psi = degreeToRad(85);
	this->speed = 0;
	this->dirAngle = 0.0;
}

// speed = [-5; 5]
// m b just receive values from Joystic and call function that returns angle of turn and speed - for arbitrary directions
// arbitrary directions is combine of computeStepSideway() and computeStepForward() depending on direction angle
StepAngles* Paw::computeStepForward(int joyX, int joyY)
{
	this->computeSpeedAndDirection(joyX, joyY);
	if (this->speed == 0) return nullptr;
	int speedAbs = abs(this->speed);

	double stepSemiLength = speedAbs * 5.0;		// mm
	double heightDelta = 50.0 / speedAbs;		// mm

	double hyp0 = sqrt(this->femur * this->femur + this->tibia * this->tibia - 2 * cos(this->psi) * this->tibia * this->femur);
	double pawHorizL0 = sqrt(hyp0 * hyp0 - this->bodyHeight * this->bodyHeight);
	double pawHorizL1 = sqrt(pawHorizL0 * pawHorizL0 + stepSemiLength * stepSemiLength - 2 * pawHorizL0 * stepSemiLength * cos(this->alpha + this->dirAngle));	//!!! add dir angle to find L1 in right direction
	double alphaDiff1 = acos((pawHorizL1 * pawHorizL1 + pawHorizL0 * pawHorizL0 - stepSemiLength * stepSemiLength) / (2 * pawHorizL1 * pawHorizL0));
	double pawHorizL2 = sqrt(pawHorizL1 * pawHorizL1 + stepSemiLength * stepSemiLength - 2 * pawHorizL1 * stepSemiLength * cos(alphaDiff1 + this->alpha + this->dirAngle));//!!! add dir angle to find L1 in right direction
	double alphaDiff2 = acos((pawHorizL1 * pawHorizL1 + pawHorizL2 * pawHorizL2 - stepSemiLength * stepSemiLength) / (2 * pawHorizL1 * pawHorizL2));
	
	// if speed < 0 then negative alpha
	if (this->speed < 0) {
		alphaDiff1 = -alphaDiff1;
		alphaDiff2 = -alphaDiff2;
	}

	double hyp1 = sqrt(pawHorizL1 * pawHorizL1 + (this->bodyHeight - heightDelta) * (this->bodyHeight - heightDelta));
	double psiDiff1 = acos((this->femur * this->femur + this->tibia * this->tibia - hyp1 * hyp1) / (2 * this->femur * this->tibia)) - this->psi;
	double phiDiff1 = acos((hyp1 * hyp1 + this->femur * this->femur - this->tibia * this->tibia) / (2 * this->femur * hyp1)) +
		asin(pawHorizL1 / hyp1) - this->phi;
	double hyp2 = sqrt(pawHorizL2 * pawHorizL2 + this->bodyHeight * this->bodyHeight);
	double psiDiff2 = acos((this->femur * this->femur + this->tibia * this->tibia - hyp2 * hyp2) / (2 * this->femur * this->tibia)) - psiDiff1 - this->psi;
	double phiDiff2 = acos((hyp2 * hyp2 + this->femur * this->femur - this->tibia * this->tibia) / (2 * this->femur * hyp2)) +
		asin(pawHorizL2 / hyp2) - this->phi - phiDiff1;

	StepAngles* stepAngles = new StepAngles(20);
	double alphaStep = alphaDiff1 / 10.0;
	double phiStep = phiDiff1 / 10.0;
	double psiStep = psiDiff1 / 10.0;
	stepAngles->alpha[0] = alphaStep + this->alpha;
	stepAngles->phi[0] = phiStep + this->phi;
	stepAngles->psi[0] = psiStep + this->psi;
	printf("alpha=%.2f; phi=%.2f; psi=%.2f\n", radToDegree(stepAngles->alpha[0]), radToDegree(stepAngles->phi[0]), radToDegree(stepAngles->psi[0]));
	for (register int i = 1; i < 10; i++) {
		stepAngles->alpha[i] = alphaStep + stepAngles->alpha[i - 1];
		stepAngles->phi[i] = phiStep + stepAngles->phi[i - 1];
		stepAngles->psi[i] = psiStep + stepAngles->psi[i - 1];
		printf("alpha=%.2f; phi=%.2f; psi=%.2f\n", radToDegree(stepAngles->alpha[i]), radToDegree(stepAngles->phi[i]), radToDegree(stepAngles->psi[i]));
	}

	alphaStep = alphaDiff2 / 10.0;
	phiStep = phiDiff2 / 10.0;
	psiStep = psiDiff2 / 10.0;
	stepAngles->alpha[10] = alphaStep + stepAngles->alpha[9];
	stepAngles->phi[10] = phiStep + stepAngles->phi[9];
	stepAngles->psi[10] = psiStep + stepAngles->psi[9];
	printf("alpha=%.2f; phi=%.2f; psi=%.2f\n", radToDegree(stepAngles->alpha[10]), radToDegree(stepAngles->phi[10]), radToDegree(stepAngles->psi[10]));
	for (register int i = 11; i < 20; i++) {
		stepAngles->alpha[i] = alphaStep + stepAngles->alpha[i - 1];
		stepAngles->phi[i] = phiStep + stepAngles->phi[i - 1];
		stepAngles->psi[i] = psiStep + stepAngles->psi[i - 1];
		printf("alpha=%.2f; phi=%.2f; psi=%.2f\n", radToDegree(stepAngles->alpha[i]), radToDegree(stepAngles->phi[i]), radToDegree(stepAngles->psi[i]));
	}

	return stepAngles;
}

void Paw::computeSpeedAndDirection(int joyX, int joyY)
{
	// correct values for real joystick or check internal values and do not consider little deviations
	int x = joyX - 511;
	int y = joyY - 511;
	double bound = degreeToRad(10);
	double realDirAngle = atan((double)x / y);
	printf("real_dir_angle=%.2f;\n", radToDegree(realDirAngle));

	// very little deviations does not consider
	if (realDirAngle < bound - PI / 2.0) { this->dirAngle = -PI / 2.0; this->speed = abs(x) / 100; }
	else if (realDirAngle > PI / 2.0 - bound) { this->dirAngle = PI / 2.0; this->speed = abs(x) / 100; }
	else if (abs(realDirAngle) < bound) { this->dirAngle = 0.0; this->speed = y / 100; }
	else { 
		this->dirAngle = realDirAngle; 
		this->speed = sqrt(x * x + y * y) / 150;
		if (y < 0) this->speed = -this->speed;
	}

	printf("dir_angle=%.2f; speed=%d;\n", radToDegree(this->dirAngle), this->speed);
}
