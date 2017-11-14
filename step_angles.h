#ifndef STEP_ANGLES_H
#define STEP_ANGLES_H

struct StepAngles {
	double* alpha;
	double* phi;
	double* psi;
	int numSteps;
	StepAngles(int numSteps);
};

#endif