#ifndef UTILITY_H
#define UTILITY_H

#define MIN_FLOAT 0.00001

double radToDegree(double angle);
double degreeToRad(double angle);

void checkExternalBoundaries(double min, double max, double & val);
void checkInternalBoundaries(double min, double max, double & val, double nextVal);


// -------------

#define PI 3.1415

typedef __int8 byte;

struct Servo {

};

#endif
