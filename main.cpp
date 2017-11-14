
#include <iostream>
#include <math.h>

#include "paw.h"

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



double femur = 220.0;
double tibia = 350.0;
double initBodyHeight = 200.0;																					//mm
double initAlpha = degreeToRad(90);
double initPhi = degreeToRad(95);
double initPsi = degreeToRad(80);
double initHyp = sqrt(femur*femur + tibia*tibia - 2*cos(initPsi)*tibia*femur);
double initLegHorizLength = sqrt(initHyp*initHyp - initBodyHeight*initBodyHeight);								//mm

// здесь можно не делать дискретную скорость,
// а просто передавать нормированное значение double с джойстика
// чтобы скорости плавные были
Angles computeAngles(double speed) {
	if (speed == 0.0) return Angles(initPhi, initPsi, initAlpha);
	double stepLength = speed * 10.0;						// 10, 20, 30, 40, 50 mm
	double stepSemiLength = speed * 5.0;						
	// добавить начальный угол отклонения лапы
	/*double pawHorizL0 = (initAlpha != 0.0) ? initLegHorizLength * cos(initAlpha) : initLegHorizLength;
	double pawHorizL1 = sqrt(pawHorizL0*pawHorizL0 + stepSemiLength*stepSemiLength);
	double alpha1 = atan(stepSemiLength / pawHorizL0);
	double pawHorizL2 = sqrt(pawHorizL0*pawHorizL0 + stepLength*stepLength);
	double alpha2 = atan(stepLength / pawHorizL0);*/

	double pawHorizL1 = sqrt(initLegHorizLength*initLegHorizLength + stepSemiLength*stepSemiLength - 2*initLegHorizLength*stepSemiLength*cos(initAlpha));
	double alpha1 = initAlpha + acos((pawHorizL1*pawHorizL1 + initLegHorizLength*initLegHorizLength - stepSemiLength*stepSemiLength) / (2*pawHorizL1*initLegHorizLength));
	double pawHorizL2 = sqrt(pawHorizL1*pawHorizL1 + stepSemiLength*stepSemiLength - 2*pawHorizL1*stepSemiLength*cos(alpha1));
	double alpha2 = alpha1 + acos((pawHorizL1*pawHorizL1 + pawHorizL2*pawHorizL2 - stepSemiLength*stepSemiLength) / (2 * pawHorizL1*pawHorizL2));

	printf("pawHorizL1=%.2f; alpha1=%.2f; \npawHorizL2=%.2f; alpha2=%.2f; \n", pawHorizL1, radToDegree(alpha1), pawHorizL2, radToDegree(alpha2));

	double heightDelta = 50.0 / speed;
	double hyp1 = sqrt(pawHorizL1*pawHorizL1 + (initBodyHeight - heightDelta)*(initBodyHeight - heightDelta));
	double psi1 = acos((femur*femur + tibia*tibia - hyp1*hyp1) / (2*femur*tibia));
	double phi1 = initPhi + acos((hyp1*hyp1 + femur*femur - tibia*tibia) / (2*femur*hyp1));
	double hyp2 = sqrt(pawHorizL2*pawHorizL2 + initBodyHeight*initBodyHeight);
	double psi2 = acos((femur*femur + tibia*tibia - hyp2*hyp2) / (2 * femur*tibia));
	double phi2 = initPhi + acos((hyp2*hyp2 + femur*femur - tibia*tibia) / (2 * femur*hyp2));

	printf("hyp1=%.2f; phi2=%.2f; psi2=%.2f;\n", hyp1, radToDegree(phi1), radToDegree(psi1));
	printf("hyp2=%.2f; phi2=%.2f; psi2=%.2f;\n", hyp2, radToDegree(phi2), radToDegree(psi2));

	return Angles(phi2, psi2, alpha2);
}



int main() {

	computeAngles(5.0);

	Servo s1, s2, s3;
	Paw paw(s1, s2, s3);
	paw.computeStepForward(5);


	system("pause");
	return 0;
}