#ifndef PAW_H
#define PAW_H

class Paw {
public:
	Paw();		// attach 3 servos
	Paw(Servo alpha, Servo phi, Servo psi);		// attach 3 servos
	void setInitState();

private:
	double alpha_;
	double phi_;
	double psi_;
	double servoAlpha_;
	double servoPhi_;
	double servoPsi_;
};

#endif