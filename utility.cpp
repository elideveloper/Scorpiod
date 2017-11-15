#include "utility.h"



double radToDegree(double angle) {
	return angle * 180.0 / PI;
}

double degreeToRad(double angle) {
	return angle * PI / 180.0;
}

double checkExternalBoundaries(double min, double max, double & val)
{
	if (val < min) val = min;
	else if (val > max) val = max;
}

double checkInternalBoundaries(double min, double max, double & val, double nextVal)
{
	if (val < min || val > max) val = nextVal;
}
