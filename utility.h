#ifndef UTILITY_H
#define UTILITY_H

#define DEBUG_MODE

#ifndef DEBUG_MODE
#include "Arduino.h"
#endif

#define ONE_DIV_PI 0.31831
#define ONE_DIV_180 0.00555
#define MIN_FLOAT 0.00001

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

const double EPS = 1e-8;
const int COXA_OFFSET = 25;
const int FEMUR_LEN = 85;
const int TIBIA_LEN = 125;
const int VERTICAL_OFFSET = -20;			// высота на котором тело находится относительно поверхности движения ног
const int A_LEG_COXA_OFFSET = 45;
const int A_LEG_FEMUR_OFFSET = 6;
const int A_LEG_TIBIA_OFFSET = 0;
const int MIN_SERVO_ANGLE = 0;
const int MAX_SERVO_ANGLE = 90;

int rad2Deg(double angle);
double deg2Rad(double angle);



#ifdef DEBUG_MODE

const double PI = 3.1415926536;
typedef __int8 byte;

struct Servo {
public:
	inline void write(int) {}
};

#endif

#endif
