
#include <iostream>
#include <math.h>

double radToDegree(double angle) {
	return angle * 180.0 / 3.1415;
}

double degreeToRad(double angle) {
	return angle * 3.1415 / 180.0;
}

struct Angles {
	double servoPhi;
	double servoPsi;
	double servoAlpha;
	Angles(double phi, double psi, double alpha) {
		this->servoAlpha = alpha;
		this->servoPhi = phi;
		this->servoPsi = psi;
	}
};


// нужно описать класс для управления ногой.
//для начала движение вперед-назад, далее в произвольном направлении.



double legPart1 = 120.0;
double legPart2 = 160.0;
double initLegHorizLength = 100.0;								//mm
double initBodyHeight = 200.0;									//mm
double initAlpha = degreeToRad(90);
double initPhi = degreeToRad(95);
double initPsi = degreeToRad(80);

// здесь можно не делать дискретную скорость,
// а просто передавать нормированное значение double с джойстика
// чтобы скорости плавные были
Angles computeAngles(double speed) {
	if (speed == 0.0) return Angles(initPhi, initPsi, initAlpha);
	double stepLength = speed * 10.0;						// 10, 20, 30, 40, 50 mm
	double stepSemiLength = speed * 5.0;						// 10, 20, 30, 40, 50 mm
	// добавить начальный угол отклонения лапы
	/*double legHorizL0 = (initAlpha != 0.0) ? initLegHorizLength * cos(initAlpha) : initLegHorizLength;
	double legHorizL1 = sqrt(legHorizL0*legHorizL0 + stepSemiLength*stepSemiLength);
	double alpha1 = atan(stepSemiLength / legHorizL0);
	double legHorizL2 = sqrt(legHorizL0*legHorizL0 + stepLength*stepLength);
	double alpha2 = atan(stepLength / legHorizL0);*/

	double legHorizL1 = sqrt(initLegHorizLength*initLegHorizLength + stepSemiLength*stepSemiLength - 2*initLegHorizLength*stepSemiLength*cos(initAlpha));
	double alpha1 = initAlpha + acos((legHorizL1*legHorizL1 + initLegHorizLength*initLegHorizLength - stepSemiLength*stepSemiLength) / (2*legHorizL1*initLegHorizLength));
	double legHorizL2 = sqrt(legHorizL1*legHorizL1 + stepSemiLength*stepSemiLength - 2*legHorizL1*stepSemiLength*cos(alpha1));
	double alpha2 = alpha1 + acos((legHorizL1*legHorizL1 + legHorizL2*legHorizL2 - stepSemiLength*stepSemiLength) / (2 * legHorizL1*legHorizL2));

	printf("legHorizL1=%.2f; alpha1=%.2f; \nlegHorizL2=%.2f; alpha2=%.2f; \n", legHorizL1, radToDegree(alpha1), legHorizL2, radToDegree(alpha2));

	double heightDelta = 50.0 / speed;
	double hyp1 = sqrt(legHorizL1*legHorizL1 + (initBodyHeight - heightDelta)*(initBodyHeight - heightDelta));
	double psi1 = acos((legPart1*legPart1 + legPart2*legPart2 - hyp1*hyp1) / (2*legPart1*legPart2));
	double phi1 = initPhi + acos((hyp1*hyp1 + legPart1*legPart1 - legPart2*legPart2) / (2*legPart1*hyp1));
	double hyp2 = sqrt(legHorizL2*legHorizL2 + initBodyHeight*initBodyHeight);
	double psi2 = acos((legPart1*legPart1 + legPart2*legPart2 - hyp2*hyp2) / (2 * legPart1*legPart2));
	double phi2 = initPhi + acos((hyp2*hyp2 + legPart1*legPart1 - legPart2*legPart2) / (2 * legPart1*hyp2));

	printf("hyp1=%.2f; phi2=%.2f; psi2=%.2f;\n", hyp1, radToDegree(phi1), radToDegree(psi1));
	printf("hyp2=%.2f; phi2=%.2f; psi2=%.2f;\n", hyp2, radToDegree(phi2), radToDegree(psi2));

	return Angles(phi2, psi2, alpha2);
}



int main() {

	computeAngles(5.0);


	system("pause");
	return 0;
}