#include "utility.h"

int rad2Deg(double angle) {
	return angle * 180.0 * ONE_DIV_PI;
}

double deg2Rad(double angle) {
	return angle * PI * ONE_DIV_180;
}
//
//void checkExternalBoundaries(double min, double max, double & val)
//{
//	if (val < min) val = min;
//	else if (val > max) val = max;
//}
//
//void checkInternalBoundaries(double min, double max, double & val, double nextVal)
//{
//	if (nextVal < min || nextVal > max) val = nextVal;
//}
