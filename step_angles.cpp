#include "step_angles.h"

StepAngles::StepAngles(int numSteps) : numSteps(numSteps)
{
	this->alpha = new double[numSteps];
	this->phi = new double[numSteps];
	this->psi = new double[numSteps];
}
