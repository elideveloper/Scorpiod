#include "utility.h"



double radToDegree(double angle) {
	return angle * 180.0 / PI;
}

double degreeToRad(double angle) {
	return angle * PI / 180.0;
}

void checkExternalBoundaries(double min, double max, double & val)
{
	if (val < min) val = min;
	else if (val > max) val = max;
}

void checkInternalBoundaries(double min, double max, double & val, double nextVal)
{
	if (nextVal < min || nextVal > max) val = nextVal;
}
