#include <iostream>
#include <math.h>

#include "paw.h"


// Servo class reimplement Servo including possible range
int main() {

	//computeAngles(4.0);

	Servo s1, s2, s3;
	Paw paw(s1, s2, s3);
	paw.computeStepForward(511, 1024);


	system("pause");
	return 0;
}