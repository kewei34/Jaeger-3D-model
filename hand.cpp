#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLUT.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#include "base.h"
#include "bodyPart.h"


float lArmRtAngle = 0, lArmRt = 0;
float lPalmRtAngle = 0, lPalmRt = 0;
float lForeArmRtAngle = 0, lForeArmRtX = 0, lForeArmRtZ = 0;
float ebZoom = 0, ebRt = 0, ballAtk = 0;
bool eb = 0;

void restore() {
	lArmRtAngle = 0, lArmRt = 0;
	lPalmRtAngle = 0, lPalmRt = 0;
	lForeArmRtAngle = 0, lForeArmRtX = 0, lForeArmRtZ = 0;
	ebZoom = 0, ebRt = 0,ballAtk = 0;;
	eb = 0;
}

void thumb(float length) {

	glPushMatrix();
	//rotate to put thumb outside
	glTranslatef(-0.1, 0.7, 0);
	glRotatef(-60, 0, 1, 1);
	glTranslatef(-0.12, -0.35, 0);
	glPushMatrix();
	glTranslatef(-0.05, 0.19, 0);
	joint(0.1, 0.06);
	glPopMatrix();
	//upper thumb
	glPushMatrix();
	glTranslatef(0, 0.16, 0);
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, -0.16, 0);
	finger(0.16);
	glPopMatrix();
	//lower thumb
	glPushMatrix();
	glTranslatef(0, 0.38, 0);
	glPushMatrix();
	glTranslatef(-0.05, 0.19, 0);
	joint(0.1, 0.06);
	glPopMatrix();

	finger(0.16);
	glPopMatrix();

	glPopMatrix();

}

void lThumb() {
	glPushMatrix();
	//rotate to put thumb outside
	glTranslatef(-0.1, 0.7, 0);
	glRotatef(60, 0, 1, 1);
	glTranslatef(-0.12, -0.35, 0);
	glPushMatrix();
	glTranslatef(-0.05, 0.19, 0);
	joint(0.1, 0.06);
	glPopMatrix();
	//upper thumb
	glPushMatrix();
	glTranslatef(0, 0.16, 0);
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, -0.16, 0);
	finger(0.16);
	glPopMatrix();
	//lower thumb
	glPushMatrix();
	glTranslatef(0, 0.38, 0);
	glPushMatrix();
	glTranslatef(-0.05, 0.19, 0);
	joint(0.1, 0.06);
	glPopMatrix();

	finger(0.16);
	glPopMatrix();

	glPopMatrix();
}

void allFingers() {

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, -0.15, 0);
	upperFingers(0.15);
	glPopMatrix();

	//middle

	fingerJoint();
	//with palm
	glPushMatrix();
	glTranslatef(0, 0.45, 0);
	fingerJoint();
	glPopMatrix();

	lowerFingers();
}

bool moveLArmUp() {

	lArmRt = 1;
	if (lArmRtAngle < 90) {
		lArmRtAngle += 0.5;
	}
	else if (lArmRtAngle == 90) {
		return 0;
	}
	return 1;
}

bool moveLArmDown() {
	lArmRt = 1;
	if (lArmRtAngle > 0) {
		lArmRtAngle -= 0.5;
	}
	else if (lArmRtAngle == 0) {
		lArmRt = 0;
		return 0;
	}
	return 1;
}

bool moveLArmnPalmUp(bool attack) {
	lArmRt = 1;
	lPalmRt = 1;
	if (lArmRtAngle < 90) {
		lArmRtAngle += 0.5;
		lPalmRtAngle = lArmRtAngle;
	}
	else if (lArmRtAngle == 90) {
		if (attack) {
			eb = 1;
			ebRt += 30;
			ballAtk = 0;
			if (ebZoom < 0.4) {
				ebZoom += 0.02;
			}
		}
		return 0;
	}
	return 1;
}

bool moveLArmnPalmDown() {
	lArmRt = 1;
	lPalmRt = 1;
	if (lArmRtAngle > 0) {
		lArmRtAngle -= 0.5;
		lPalmRtAngle = lArmRtAngle;
	}
	else if (lArmRtAngle == 0) {
		lArmRt = 0;
		lPalmRt = 0;
		return 0;
	}
	return 1;
}

void moveLForeArmUp() {
	lForeArmRtX = 1;

}

bool attackBall() {
	if (ballAtk > -10) {
		ballAtk -= 0.3;
		if (ballAtk <= -5) {
			eb = 0;
			ebZoom = 0;
			return 1;
		}
	}
	
	return 0;
}

void leftHand() {

	glPushMatrix();
		glTranslatef(0.5, 0, 0);
		glRotatef(180, 0, 1, 0);
		shoulder();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.56, 3.4, 0);
		glRotatef(-lArmRtAngle, lArmRt, 0, 0);
		glTranslatef(-0.56, -3.4, 0);

		glPushMatrix();
			glTranslatef(-0.28, 0, 0);
			upperArm();

			glPushMatrix();
				//glTranslatef(-0.28, 0, 0);
				glTranslatef(0, 2.6, 0);
				glRotatef(lForeArmRtAngle, lForeArmRtX, 0, lForeArmRtZ);
				glTranslatef(0, -2.6, 0);
				upForeArm();
				foreArm();
					glPushMatrix();
						glTranslatef(0.7, 1.3, 0);
						glRotatef(-lPalmRtAngle, lPalmRt, 0, 0);
						glTranslatef(-0.7, -1.3, 0);
						palm();
						if (eb) {
							glPushMatrix();
							glTranslatef(0.35, 1.0, -0.8 + ballAtk);
							glRotatef(ebRt, 1, 1, 1);
							glScalef(0.1 + ebZoom, 0.1 + ebZoom, 0.1 + ebZoom);
							energyBall();
							glPopMatrix();
						}
						allFingers();
				
						glPushMatrix();
							glTranslatef(1.0, 0.1, -0.2);
							lThumb();
						glPopMatrix();
					glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void rightHand() {
	shoulder();
	glPushMatrix();
		glTranslatef(0.56, 3.4, 0);
		glRotatef(-lArmRtAngle, lArmRt, 0, 0);
		glTranslatef(-0.56, -3.4, 0);
		upperArm();
	
			glPushMatrix();
				glTranslatef(0.28, 0, 0);
				//glRotatef(30, 0, 1, 0);
				glTranslatef(-0.28, 0, 0);
				upForeArm();
				foreArm();
				glPushMatrix();
					glTranslatef(0.7, 1.3, 0);
					glRotatef(-lPalmRtAngle, lPalmRt, 0, 0);
					glTranslatef(-0.7, -1.3, 0);
					palm();
					if (eb) {
						glPushMatrix();
						glTranslatef(0.35, 1.0, -0.8 + ballAtk);
						glRotatef(ebRt, 1, 1, 1);
						glScalef(0.1 + ebZoom, 0.1 + ebZoom, 0.1 + ebZoom);
						energyBall();
						glPopMatrix();
					}
					thumb(0.2);
					allFingers();
				glPopMatrix();
			glPopMatrix();

	glPopMatrix();
}
